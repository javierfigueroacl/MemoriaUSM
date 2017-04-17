#include "stdafx.h"
#include "GridMesher.h"

namespace Clobscode
{
	GridMesher::GridMesher(const unsigned int &nm){
		n_meshes = nm;
	}
	
	GridMesher::~GridMesher(){
		
	}
	
	
	void GridMesher::generatePoints(vector<double> &bounds,
									vector<double> &all_x,
									vector<double> &all_z,
									vector<double> &all_y, int rl){
		
		double dx = bounds[3]-bounds[0];
		double dy = bounds[4]-bounds[1];
		double dz = bounds[5]-bounds[2];
		//vector<double> boundsplus = bounds;
		//double max_d;
		
		double step;
		
		if (dx>=dy && dx>=dz) {
			step = dx/pow(2,rl);
			//max_d = dx;
		}
		else {
			if (dy>=dx && dy>=dz) {
				step = dy/pow(2,rl);
				//max_d = dy;
			}
			else {
				step = dz/pow(2,rl);
				//max_d = dz;
			}
		}
		
		generateVector(all_x,bounds[0],bounds[3],step);
		generateVector(all_y,bounds[1],bounds[4],step);
		generateVector(all_z,bounds[2],bounds[5],step);
	}
	
	void GridMesher::generateMesh(vector<double> &all_x,
								  vector<double> &all_z,
								  vector<double> &all_y,
								  vector<MeshPoint> &points,
								  vector<EnhancedElement> &elements){
	
		unsigned int nx = all_x.size();
		unsigned int ny = all_y.size();
		unsigned int nz = all_z.size();
		
		points.reserve(nx*ny*nz);
		points.clear();
		elements.reserve((nx-1)*(ny-1)*(nz-1));
		elements.clear();
		
		unsigned int one_col = nx*ny;
		
		for (unsigned int i=0; i<nz; i++) {
			for (unsigned int j=0; j<ny; j++) {
				for (unsigned int k=0; k<nx; k++) {
					
					//create the point
					Point3D p3d (all_x[k],all_y[j],all_z[i]);
					MeshPoint mp (p3d, n_meshes);
					points.push_back(mp);
					
					//create the element					
					if ((k+2)>nx || (j+2)>ny || (i+2)>nz) {
						continue;
					}

					vector<unsigned int> epts (8,0);
					epts[0] = k+j*nx+i*one_col;
					epts[1] = epts[0]+one_col;
					epts[2] = epts[1]+1;
					epts[3] = epts[0]+1;
					epts[4] = epts[0]+nx;
					epts[5] = epts[4]+one_col;
					epts[6] = epts[5]+1;
					epts[7] = epts[4]+1;
					EnhancedElement ee (epts,n_meshes);
					elements.push_back(ee);
				}
			}
		}
	}
	
	void GridMesher::generateVector(vector<double> &coords, double min,
									double max, double step){
		
		list<double> tmp_coords;
		list<double>::iterator iter;
		double last;
		//shift the start coordinate to ensure the bounding box completely 
		//encapsulates the input domain
		double start = min - step*0.4;
		for (double i=start; i<max; i+=step) {
			last = i;
			tmp_coords.push_back(i);
		}
		//add one "next" coordinate to ensure the bounding box completely 
		//encapsulates the input domain
		tmp_coords.push_back(last+step);
		
		coords.reserve(tmp_coords.size());
		coords.clear();
		for (iter=tmp_coords.begin(); iter!=tmp_coords.end(); iter++) {
			coords.push_back(*iter);
		}
	}
}
