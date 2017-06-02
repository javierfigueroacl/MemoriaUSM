#include "stdafx.h"
#include "BoundaryTemplate1.h"

namespace Clobscode
{
	BoundaryTemplate1::BoundaryTemplate1(){
	}
	
	BoundaryTemplate1::~BoundaryTemplate1(){
	}
	
	bool BoundaryTemplate1::getSubelements(vector<unsigned int> &all, 
										   vector<unsigned int> &in,
										   vector<MeshPoint> &pts,
										   list<MeshPoint> &newpts,
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){		
		if (in.size()!=1) {
			return false;
		}
		
		
		//this template will split the hex in 6 pyramids and then
		//three of them into two tetras each.
		//Three of these six tetras will be considered as inside 
		//and all the rest of the elements as outside.
		newsubs_in.reserve(3);
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
		vector<unsigned int> tetra1(4,0),rotated;
		vector<unsigned int> tetra2(4,0);
		vector<unsigned int> tetra3(4,0);
		vector<unsigned int> tetra4(4,0);
		vector<unsigned int> tetra5(4,0);
		vector<unsigned int> tetra6(4,0);
		vector<unsigned int> pyramid1(5,0);
		vector<unsigned int> pyramid2(5,0);
		vector<unsigned int> pyramid3(5,0);

		//Rotating to manage any equivalent cases
		HexRotation hrot;
		rotated = hrot.rotate(all,in[0]);
		
		/*std::cout << "all size " << all.size() << " rotated";
		for (unsigned int j=0; j<rotated.size(); j++) {
			std::cout << " " << rotated[j];
		}
		std::cout << "\n";*/

		
		//Managing inside elements:				
		tetra1[0] = rotated[0];
		tetra1[1] = rotated[4];
		tetra1[2] = rotated[1];
		tetra1[3] = mid;

		tetra2[0] = rotated[0];
		tetra2[1] = rotated[1];
		tetra2[2] = rotated[3];
		tetra2[3] = mid;
		
		tetra3[0] = rotated[0];
		tetra3[1] = rotated[3];
		tetra3[2] = rotated[4];
		tetra3[3] = mid;
		
		newsubs_in.push_back(tetra1);
		newsubs_in.push_back(tetra2);
		newsubs_in.push_back(tetra3);
		
		/*for (unsigned int i=0; i<newsubs_in.size(); i++) {
			for (unsigned int j=0; j<newsubs_in[i].size(); j++) {
				std::cout << " " << newsubs_in[i][j];
			}
			std::cout << "\n";
		}*/
		
		//Managing outside elements:
		tetra4[0] = rotated[1];
		tetra4[1] = rotated[4];
		tetra4[2] = rotated[5];
		tetra4[3] = mid;		

		tetra5[0] = rotated[1];
		tetra5[1] = rotated[2];
		tetra5[2] = rotated[3];
		tetra5[3] = mid;	
		
		tetra6[0] = rotated[3];
		tetra6[1] = rotated[7];
		tetra6[2] = rotated[4];
		tetra6[3] = mid;	
		
		pyramid1[0] = rotated[1];
		pyramid1[1] = rotated[5];
		pyramid1[2] = rotated[6];
		pyramid1[3] = rotated[2];		
		pyramid1[4] = mid;

		pyramid2[0] = rotated[2];
		pyramid2[1] = rotated[6];
		pyramid2[2] = rotated[7];
		pyramid2[3] = rotated[3];		
		pyramid2[4] = mid;
		
		pyramid3[0] = rotated[4];
		pyramid3[1] = rotated[7];
		pyramid3[2] = rotated[6];
		pyramid3[3] = rotated[5];		
		pyramid3[4] = mid;
		
		newsubs_out.push_back(tetra4);
		newsubs_out.push_back(tetra5);
		newsubs_out.push_back(tetra6);
		newsubs_out.push_back(pyramid1);
		newsubs_out.push_back(pyramid2);
		newsubs_out.push_back(pyramid3);
		
		/*std::cout << "outside \n";
		for (unsigned int i=0; i<newsubs_out.size(); i++) {
			for (unsigned int j=0; j<newsubs_out[i].size(); j++) {
				std::cout << " " << newsubs_out[i][j];
			}
			std::cout << "\n";
		}*/
		
		return true;
	}
}
