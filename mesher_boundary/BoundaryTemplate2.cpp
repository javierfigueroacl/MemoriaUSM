#include "stdafx.h"
#include "BoundaryTemplate2.h"

namespace Clobscode
{
	BoundaryTemplate2::BoundaryTemplate2(){
	}
	
	BoundaryTemplate2::~BoundaryTemplate2(){
	}
	
	bool BoundaryTemplate2::getSubelements(vector<unsigned int> &all, 
										   vector<unsigned int> &in,
										   vector<MeshPoint> &pts,
										   list<MeshPoint> &newpts,
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out,
										   vector<vector<unsigned int> > &conflicting_elements){
		
		HexRotation hrot;
		vector<unsigned int> rotated;
		if(in.size()!=2)
			return false;
		
		//center all at the first node:
		rotated = hrot.rotate(all,in[0]);
		
		//Possible cases for PatternA
		if(rotated[3] == all[in[1]]){ // sin rotar?
			PatternA(rotated,pts,newsubs_in,newsubs_out,conflicting_elements);
			return true;
		}
		if(rotated[1] == all[in[1]]){ // rotacion en y en 180 grados?
			rotated = hrot.rotateNegY(rotated);
			PatternA(rotated,pts,newsubs_in,newsubs_out,conflicting_elements);
			return true;
		}
		if(rotated[4] == all[in[1]]){
			rotated = hrot.rotatePosZ(rotated);
			PatternA(rotated,pts,newsubs_in,newsubs_out,conflicting_elements);
			return true;
		}
		
		//Possible cases for PatternB
		if(rotated[2] == all[in[1]]){
			PatternB(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		if(rotated[5] == all[in[1]]){
			rotated = hrot.rotatePosZ(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		if(rotated[7] == all[in[1]]){
			rotated = hrot.rotateNegX(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		//Possible cases for PatternC
		if(rotated[6] == all[in[1]]){
			PatternC(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		
		std::cerr << "Pattern2 not found for this configuration:\nin nodes:";
		for (unsigned int i=0;i<in.size();i++)
			std::cerr << " " << in[i];
		return false;
	}
	
	void BoundaryTemplate2::PatternA(vector<unsigned int> &all, 
									 vector<MeshPoint> &pts,
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out,
									 vector<vector<unsigned int> > &conflicting_elements){
		
		newsubs_in.reserve(1);
		newsubs_out.reserve(1);		

		//Recorrer elementos conflictivos de la malla
		for(unsigned int i=0; i<conflicting_elements.size();i++){
			vector <Point3D> elepts;
			// Obtener elemento conflictivo
			for(unsigned int k=0; k<conflicting_elements[i].size();k++){
				elepts.push_back(pts.at(conflicting_elements[i][k]).getPoint());
			}
			// Obtener puntos del octante
			vector <Point3D> mpts;
			for(unsigned int j=0; j<all.size();j++)
			mpts.push_back(pts.at(all[j]).getPoint());
			int sharednode=0;

			// Recorrer nodos y comparar coordenadas xyz
			for(unsigned int j=0; j<mpts.size();j++){
			for(unsigned int k=0; k<elepts.size()-1;k++) // Se resta el ultimo nodo, que no pertenece a la cara cuadrangular
				if (mpts[j][0] == elepts[k][0]) // Restriccion x
				if (mpts[j][1] == elepts[k][1]) // Restriccion y
				if (mpts[j][2] == elepts[k][2]) // Restriccion z
				sharednode++;
			}
			// Si comparten 4 nodos en la misma posicion, significa que comparten la cara
			if (sharednode == 4){
				cout <<" --------------------- \n";
				cout <<" cara conflictiva encontrada \n";
				//print puntos
				for (unsigned int l=0; l < elepts.size()-1; l++)
				cout << elepts[l] << " <- punto xyz \n";

				//detectar plano en que se encuentra la cara
                                if(elepts[0][0] == elepts[1][0] && elepts[0][0] ==elepts[2][0] && elepts[0][0] ==elepts[3][0]){
					for (unsigned int l=0; l < mpts.size()-1; l++)
						if(mpts[l][0] < elepts[0][0])
						cout <<" cara en plano x superior \n";
						else if (mpts[l][0] > elepts[0][0])
						cout <<" cara en plano x inferior \n";
				}
				else if(elepts[0][1] == elepts[1][1] && elepts[0][1] ==elepts[2][1] && elepts[0][1] ==elepts[3][1]){
					for (unsigned int l=0; l < mpts.size()-1; l++)
						if(mpts[l][1] < elepts[0][1])
						cout <<" cara en plano y superior \n";
						else if (mpts[l][1] > elepts[0][1])
						cout <<" cara en plano y inferior \n";
				}
				else if(elepts[0][2] == elepts[1][2] && elepts[0][2] ==elepts[2][2] && elepts[0][2] ==elepts[3][2]){
					for (unsigned int l=0; l < mpts.size()-1; l++)
						if(mpts[l][2] < elepts[0][2])
						cout <<" cara en plano z superior \n";
						else if (mpts[l][2] > elepts[0][2])
						cout <<" cara en plano z inferior \n";
				}
				cout <<" --------------------- \n";
				
			}
		}
		
		vector<unsigned int> prism1 (6,0);
		vector<unsigned int> prism2 (6,0);
		
		//managing inside elements
		prism1[0] = all[0];
		prism1[1] = all[4];
		prism1[2] = all[1];
		prism1[3] = all[3];
		prism1[4] = all[7];
		prism1[5] = all[2];
		newsubs_in.push_back(prism1);
		
		//managing outside elements		
		prism2[0] = all[1];
		prism2[1] = all[4];
		prism2[2] = all[5];
		prism2[3] = all[2];
		prism2[4] = all[7];
		prism2[5] = all[6];		
		newsubs_out.push_back(prism2);
	}
	
	void BoundaryTemplate2::PatternB(vector<unsigned int> &all,
									 vector<MeshPoint> &pts,
									 list<MeshPoint> &newpts,
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		//this template will split the hex in 6 pyramids and then
		//five of them into two tetras each.
		//Six of these ten tetras will be considered as inside 
		//and all the rest of the elements as outside.
		newsubs_in.reserve(6);
		newsubs_out.reserve(5);
		
		//adding new hex mid node.
		Point3D middle;
		unsigned int mid=0;
		for (unsigned int i=0;i<all.size();i++){
			middle+=pts.at(all[i]).getPoint();
		}
		middle/=8;
		MeshPoint mp(middle, pts[0].getNumberOfInputMeshes());
		mid = pts.size() + newpts.size();
		newpts.push_back(mp);
		
		
		//creating element and auxiliary vectors
		vector<unsigned int> tetra1(4,0);
		vector<unsigned int> tetra2(4,0);
		vector<unsigned int> tetra3(4,0);
		vector<unsigned int> tetra4(4,0);
		vector<unsigned int> tetra5(4,0);
		vector<unsigned int> tetra6(4,0);
		vector<unsigned int> tetra7(4,0);
		vector<unsigned int> tetra8(4,0);
		vector<unsigned int> tetra9(4,0);
		vector<unsigned int> tetra10(4,0);
		vector<unsigned int> pyramid1(5,0);
		
		//Managing inside elements:	
		//Managing inside elements:				
		tetra1[0] = all[0];
		tetra1[1] = all[4];
		tetra1[2] = all[1];
		tetra1[3] = mid;
		
		tetra2[0] = all[0];
		tetra2[1] = all[1];
		tetra2[2] = all[3];
		tetra2[3] = mid;

		tetra3[0] = all[0];
		tetra3[1] = all[3];
		tetra3[2] = all[4];
		tetra3[3] = mid;
		
		tetra4[0] = all[1];
		tetra4[1] = all[2];
		tetra4[2] = all[3];
		tetra4[3] = mid;		
		
		tetra5[0] = all[1];
		tetra5[1] = all[6];
		tetra5[2] = all[2];
		tetra5[3] = mid;	
		
		tetra6[0] = all[2];
		tetra6[1] = all[6];
		tetra6[2] = all[3];
		tetra6[3] = mid;
		
		newsubs_in.push_back(tetra1);
		newsubs_in.push_back(tetra2);
		newsubs_in.push_back(tetra3);
		newsubs_in.push_back(tetra4);
		newsubs_in.push_back(tetra5);
		newsubs_in.push_back(tetra6);
		
		//Managing outside elements:
		tetra7[0] = all[1];
		tetra7[1] = all[4];
		tetra7[2] = all[5];
		tetra7[3] = mid;
		
		tetra8[0] = all[1];
		tetra8[1] = all[5];
		tetra8[2] = all[6];
		tetra8[3] = mid;
		
		tetra9[0] = all[3];
		tetra9[1] = all[6];
		tetra9[2] = all[7];
		tetra9[3] = mid;
		
		tetra10[0] = all[3];
		tetra10[1] = all[7];
		tetra10[2] = all[4];
		tetra10[3] = mid;
		
		pyramid1[0] = all[4];
		pyramid1[1] = all[7];
		pyramid1[2] = all[6];
		pyramid1[3] = all[5];		
		pyramid1[4] = mid;
		
		newsubs_out.push_back(tetra7);
		newsubs_out.push_back(tetra8);
		newsubs_out.push_back(tetra9);
		newsubs_out.push_back(tetra10);
		newsubs_out.push_back(pyramid1);
		
	}
	
	void BoundaryTemplate2::PatternC(vector<unsigned int> &all,
									 vector<MeshPoint> &pts,
									 list<MeshPoint> &newpts,
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		//this template will split the hex in 6 pyramids and then
		//each of them into two tetras each.
		//Six of these ten tetras will be considered as inside 
		//and all the rest of the elements as outside.
		newsubs_in.reserve(6);
		newsubs_out.reserve(6);
		
		//adding new hex mid node.
		Point3D middle;
		unsigned int mid=0;
		for (unsigned int i=0;i<all.size();i++){
			middle+=pts.at(all[i]).getPoint();
		}
		middle/=8;
		MeshPoint mp(middle, pts[0].getNumberOfInputMeshes());
		mid = pts.size() + newpts.size();
		newpts.push_back(mp);
		
		
		//creating element and auxiliary vectors
		vector<unsigned int> tetra1(4,0);
		vector<unsigned int> tetra2(4,0);
		vector<unsigned int> tetra3(4,0);
		vector<unsigned int> tetra4(4,0);
		vector<unsigned int> tetra5(4,0);
		vector<unsigned int> tetra6(4,0);
		vector<unsigned int> tetra7(4,0);
		vector<unsigned int> tetra8(4,0);
		vector<unsigned int> tetra9(4,0);
		vector<unsigned int> tetra10(4,0);
		vector<unsigned int> tetra11(4,0);
		vector<unsigned int> tetra12(4,0);
		
		//Managing inside elements:	
		//Managing inside elements:				
		tetra1[0] = all[0];
		tetra1[1] = all[4];
		tetra1[2] = all[1];
		tetra1[3] = mid;
		
		tetra2[0] = all[0];
		tetra2[1] = all[1];
		tetra2[2] = all[3];
		tetra2[3] = mid;
		
		tetra3[0] = all[0];
		tetra3[1] = all[3];
		tetra3[2] = all[4];
		tetra3[3] = mid;
		
		tetra4[0] = all[5];
		tetra4[1] = all[7];
		tetra4[2] = all[6];
		tetra4[3] = mid;		
		
		tetra5[0] = all[2];
		tetra5[1] = all[6];
		tetra5[2] = all[7];
		tetra5[3] = mid;	
		
		tetra6[0] = all[2];
		tetra6[1] = all[5];
		tetra6[2] = all[6];
		tetra6[3] = mid;
		
		newsubs_in.push_back(tetra1);
		newsubs_in.push_back(tetra2);
		newsubs_in.push_back(tetra3);
		newsubs_in.push_back(tetra4);
		newsubs_in.push_back(tetra5);
		newsubs_in.push_back(tetra6);
		
		//Managing outside elements:
		tetra7[0] = all[1];
		tetra7[1] = all[4];
		tetra7[2] = all[5];
		tetra7[3] = mid;
		
		tetra8[0] = all[1];
		tetra8[1] = all[5];
		tetra8[2] = all[2];
		tetra8[3] = mid;
		
		tetra9[0] = all[2];
		tetra9[1] = all[7];
		tetra9[2] = all[3];
		tetra9[3] = mid;
		
		tetra10[0] = all[3];
		tetra10[1] = all[7];
		tetra10[2] = all[4];
		tetra10[3] = mid;

		tetra11[0] = all[4];
		tetra11[1] = all[7];
		tetra11[2] = all[5];
		tetra11[3] = mid;
		
		tetra12[0] = all[1];
		tetra12[1] = all[2];
		tetra12[2] = all[3];
		tetra12[3] = mid;
		
		newsubs_out.push_back(tetra7);
		newsubs_out.push_back(tetra8);
		newsubs_out.push_back(tetra9);
		newsubs_out.push_back(tetra10);
		newsubs_out.push_back(tetra11);
		newsubs_out.push_back(tetra12);
	}
}
