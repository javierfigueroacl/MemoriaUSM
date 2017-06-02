#include "stdafx.h"
#include "BoundaryTemplatePyramid.h"

namespace Clobscode
{
	BoundaryTemplatePyramid::BoundaryTemplatePyramid(){
	}
	
	BoundaryTemplatePyramid::~BoundaryTemplatePyramid(){
	}
	
	bool BoundaryTemplatePyramid::getSubelements(vector<unsigned int> &all, 
										   vector<unsigned int> &in,
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){

		//the following should never happen, but it's better to prevent ...
		if (in.empty()) {
			newsubs_in.push_back(all);
			return true;
		}
		
		//do not take into account the top node of the pyramid if 
		//it is labeled as an in node. This is equivalent as to decrease
		//in one the number of nodes to check. Note that this is possible
		//as the "in" nodes are inserted in such a way the last node
		//will be always the top of pyrmid (by definition of a pyrmid
		//element).
		unsigned int n_base = in.size();
		if (in[n_base-1] == 4) {
			n_base--;
		}
		
		//now, the following cases do not need to split the pyramid
		//into two tetras (see the quadrilateral face convention).
		if (n_base==0 || n_base ==4) {
			//std::cout << "Unsing template 0 in pyramid: the same\n";
			newsubs_in.push_back(all);
			return true;
		}
		
		if (n_base==1) {
			vector<unsigned int> rotated, tet1(4,0), tet2(4,0);
			rotated = rotate(all,in[0]);
			
			tet1[0] = rotated[0];
			tet1[1] = rotated[1];
			tet1[2] = rotated[3];
			tet1[3] = rotated[4];
			
			tet2[0] = rotated[1];
			tet2[1] = rotated[2];
			tet2[2] = rotated[3];
			tet2[3] = rotated[4];
			
			newsubs_in.push_back(tet1);
			newsubs_out.push_back(tet2);
			
			/*std::cout << "Unsing template 1 in pyramid.\nIN:\n";
			
			for (unsigned int i=0; i<newsubs_in.size(); i++) {
				for (unsigned int j=0; j<newsubs_in[i].size(); j++) {
					std::cout << " " << newsubs_in[i][j];
				}
				std::cout << "\n";
			}
			std::cout << "OUT\n";
			
			for (unsigned int i=0; i<newsubs_out.size(); i++) {
				for (unsigned int j=0; j<newsubs_out[i].size(); j++) {
					std::cout << " " << newsubs_out[i][j];
				}
				std::cout << "\n";
			}*/
			return true;
		}
		
		if (n_base==2) {
			vector<unsigned int> rotated;
			rotated = rotate(all,in[0]);
			
			//first case: the two base nodes are connected, then
			//it's not necessary to split into two tetra
			if (rotated[1] == in[1] || rotated[3] == in[1]) {
				//std::cout << "Unsing template 2 in pyramid: the same\n";
				newsubs_in.push_back(all);
				return true;
			}
			
			//as previous case didn't happen, then the other
			//in base node must be rotate[2]
			vector<unsigned int> tet1(4,0), tet2(4,0);
			
			tet1[0] = rotated[0];
			tet1[1] = rotated[1];
			tet1[2] = rotated[3];
			tet1[3] = rotated[4];
			
			tet2[0] = rotated[1];
			tet2[1] = rotated[2];
			tet2[2] = rotated[3];
			tet2[3] = rotated[4];
		
			newsubs_in.push_back(tet1);
			newsubs_in.push_back(tet2);
			
			/*std::cout << "Unsing template 2 in pyramid.\nIN:\n";
			
			for (unsigned int i=0; i<newsubs_in.size(); i++) {
				for (unsigned int j=0; j<newsubs_in[i].size(); j++) {
					std::cout << " " << newsubs_in[i][j];
				}
				std::cout << "\n";
			}
			std::cout << "OUT\n";
			
			for (unsigned int i=0; i<newsubs_out.size(); i++) {
				for (unsigned int j=0; j<newsubs_out[i].size(); j++) {
					std::cout << " " << newsubs_out[i][j];
				}
				std::cout << "\n";
			}*/
			
			return true;
		}
		
		if (n_base==3) {
			//it is easier to find the base node that is outside.
			unsigned int out;
			for (unsigned int i=0; i<n_base; i++) {
				if (i!=in[i]) {
					out = i;
					break;
				}
			}
			
			vector<unsigned int> rotated, tet1(4,0), tet2(4,0);
			rotated = rotate(all,out);
			
			tet1[0] = rotated[0];
			tet1[1] = rotated[1];
			tet1[2] = rotated[2];
			tet1[3] = rotated[4];
			
			tet2[0] = rotated[0];
			tet2[1] = rotated[2];
			tet2[2] = rotated[3];
			tet2[3] = rotated[4];
			
			newsubs_in.push_back(tet1);
			newsubs_in.push_back(tet2);
			
			/*std::cout << "Unsing template 3 in pyramid.\nIN:\n";
			
			for (unsigned int i=0; i<newsubs_in.size(); i++) {
				for (unsigned int j=0; j<newsubs_in[i].size(); j++) {
					std::cout << " " << newsubs_in[i][j];
				}
				std::cout << "\n";
			}
			std::cout << "OUT\n";
			
			for (unsigned int i=0; i<newsubs_out.size(); i++) {
				for (unsigned int j=0; j<newsubs_out[i].size(); j++) {
					std::cout << " " << newsubs_out[i][j];
				}
				std::cout << "\n";
			}*/
			
			return true;
		}
		
		return false;
	}
	
	vector<unsigned int> BoundaryTemplatePyramid::rotate(vector<unsigned int> &original,
														 int index){
		
		vector<unsigned int> rotated(5,0);
		switch(index){
			case 0:
				return original;		  
				/*node 1 is now node 0*/
			case 1:
				rotated[0] = original[1];
				rotated[1] = original[2];
				rotated[2] = original[3];
				rotated[3] = original[0];
				rotated[4] = original[4];
				return rotated;
			case 2:
				/*node 2 is now node 0*/
				rotated[0] = original[2];
				rotated[1] = original[3];
				rotated[2] = original[0];
				rotated[3] = original[1];
				rotated[4] = original[4];
				return rotated;
				/*node 3 is now node 0*/
			case 3:
				rotated[0] = original[3];
				rotated[1] = original[0];
				rotated[2] = original[1];
				rotated[3] = original[2];
				rotated[4] = original[4];
				return rotated;
			default:
				return rotated;
		}
		
	}
}
