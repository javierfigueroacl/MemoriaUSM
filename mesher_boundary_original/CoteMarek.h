#ifndef CoteMarek_h
#define CoteMarek_h 1

#include <string.h>
#include <cstring>
#include "TriMesh.h"
#include "../mesher_services/Mesh.h"
#include "../mesher_services/VPoint3D.h"
#include "FEMesh.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

using TxTriModel::Mesh;
using Clobscode::Point3D;
using TxGeom::VPoint3D;
using std::vector;

namespace Clobscode
{
	
	
	//The TxTriModel are meshes used by mesher_services to detect in/outside nodes.
	//The TriMesh ares meshes (with "almost" the same information) employed by the
	//mesher class of this code.
	
	static std::vector<TxTriModel::Mesh> input_meshes;
	
	class CoteMarek
	{
	public:
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		static void setNumberOfInputs(const unsigned int &n){
			input_meshes.reserve(n);
		}
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		static Point3D GetProjection( const void *, const Point3D & pPoint, const unsigned int &i){
				
			VPoint3D TxPoint (pPoint.X(),pPoint.Y(),pPoint.Z());
			VPoint3D TxResult = input_meshes[i].GetProjection(TxPoint);
			Point3D CPoint (TxResult.X(),TxResult.Y(),TxResult.Z());

			return CPoint;
		}
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		static bool CheckIfPointInMesh( const void *, const Point3D & pPoint, const unsigned int &i ){
			VPoint3D TxPoint (pPoint.X(),pPoint.Y(),pPoint.Z());
			return input_meshes[i].PointIsInMesh_slow(TxPoint);
		}
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		static bool ReadInputMesh(std::string name, std::vector<Clobscode::TriMesh> &clobs_inputs){

			char word [256];
			int cant;
			double x,y,z;
			vector<vector<unsigned int> > allfaces;
			vector<VPoint3D> TxPoints;
			
			Clobscode::TriMesh clobs_input;
			TxTriModel::Mesh distance_input;
			
			FILE *file=fopen(name.c_str(),"r");
			
			//read number of nodes
			while(true){
				if(std::fscanf(file,"%s",word)==EOF){
					fclose(file);
					return false;
				}
				if(!strcmp(word,"ARRAY1<POINT3D>]\0"))
					break;
			}
			std::fscanf(file,"%i",&cant);
			
			if(cant<=0)
				return false;
			//read each node
			clobs_input.getPoints().reserve(cant);
			clobs_input.getPoints().clear();
			
			TxPoints.reserve(cant);
			
			for( int i=0;i<cant;i++){
				std::fscanf(file,"%s",word);
				x=atof(word);
				std::fscanf(file,"%s",word);
				y=atof(word);
				std::fscanf(file,"%s",word);
				z=atof(word);
				Point3D p (x,y,z);
				VPoint3D TxP (x,y,z);
				clobs_input.getPoints().push_back(p);
				TxPoints.push_back(TxP);
			}
			
			//read number of "triangle faces"
			cant = 0;
			while(1){
				if(std::fscanf(file,"%s",word) == EOF){
					std::cout << "didn't find faces\n";
					fclose(file);
					return false;
				}
				
				if(!std::strcmp(word,"ARRAY1<STRING>]\0")){
					//std::fscanf(file,"%s",word);
					std::fscanf(file,"%i",&cant);
					break;
				}
			}
			
			clobs_input.getFaces().reserve(cant);
			allfaces.reserve(cant);
			//read each face (assuming they are triangles
			int dust;
			for( int i=0;i<cant;i++){
				std::vector<unsigned int> fpts(3,0);
				for(unsigned int j=0;j<3;j++){
					std::fscanf(file,"%i",&fpts[j]);
				}
				//read some unnecessary integers
				for(unsigned int j=0;j<3;j++)
					std::fscanf(file,"%i",&dust);
				
				allfaces.push_back(fpts);
				clobs_input.getFaces().push_back(fpts);
			}
			fclose(file);
			
			distance_input.Init(TxPoints, allfaces);
			
			input_meshes.push_back(distance_input);
			clobs_inputs.push_back(clobs_input);
			
			return true;
		}
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		static bool WriteOutputMesh(std::string name, FEMesh &output){
			
			std::ofstream log;
			string log_name = name+".log";
			log.open(log_name.c_str());
			for (unsigned int i=0; i<input_meshes.size(); i++) {
				log << input_meshes[i];
				log << "\n\n\n--------------------\n\n";
			}
			log.close();
			
			std::vector<Point3D> points = output.getPoints();
			std::vector<std::vector<unsigned int> > elements = output.getElements();
			
			if (elements.empty()) {
				std::cout << "no output elements\n";
				return false;
			}
			
			string vol_name = name+".m3d";
			
			//write the volume mesh
			FILE *f = fopen(vol_name.c_str(),"wt");
			
			unsigned int n = points.size();
			
			fprintf(f,"%s\n","[Nodes, ARRAY1<STRING>]");
			fprintf(f,"%i\n\n",n);
			
			//write points
			for(unsigned int i=0;i<n;i++){			
				fprintf(f,"1 %+1.8E",points[i][0]);
				fprintf(f," %+1.8E",points[i][1]);
				fprintf(f," %+1.8E\n",points[i][2]);
			}
			
			n = elements.size();
			
			fprintf(f,"\n%s\n","[Elements, ARRAY1<STRING>]");
			fprintf(f,"%i\n\n",n);
			
			int idx = 0;
			//get all the elements in a std::vector
			for (unsigned int i=0; i<n; i++) {
				std::vector<unsigned int> epts = elements[i];
				unsigned int np = epts.size();
				if (np == 4) {
					fprintf(f,"T");
				}
				else if (np == 5){
					fprintf(f,"P");
				}
				else if (np == 6){
					fprintf(f,"R");
				}
				else if (np == 8){
					fprintf(f,"H");
				}
				
				for (unsigned int j= 0; j<np; j++) {
					fprintf(f," %i", epts.at(j));
				}
				
				fprintf(f," 1000.0 0.45 1.0\n");
			}
			fclose(f);
			
			//write the surface nodes:
			string surf_name = name + ".mdl";
			list<unsigned int> out_pts = output.getOutsideNodes();
			list<unsigned int>::iterator o_iter;
			n = out_pts.size();
			
			FILE *sf = fopen(surf_name.c_str(),"wt");
			fprintf(sf,"%s\n", "[Points, ARRAY1<POINT3D>]");
			fprintf(sf,"%i\n\n",n); 
			
			for (o_iter=out_pts.begin(); o_iter!=out_pts.end(); o_iter++) {
				/*fprintf(sf,"%+1.8E",points[*o_iter][0]*1000);
				fprintf(sf," %+1.8E",points[*o_iter][1]*1000);
				fprintf(sf," %+1.8E\n",points[*o_iter][2]*1000);*/
				
				fprintf(sf,"%+1.8E",points[*o_iter][0]);
				fprintf(sf," %+1.8E",points[*o_iter][1]);
				fprintf(sf," %+1.8E\n",points[*o_iter][2]);
			}
			
			fprintf(sf,"\n%s\n", "[Triangles, ARRAY1<STRING>]\n0");
			
			fclose(sf);
			
			return true;
		}
	};
}
#endif
