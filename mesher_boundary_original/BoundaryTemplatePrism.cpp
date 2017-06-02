#include "stdafx.h"
#include "BoundaryTemplatePrism.h"

namespace Clobscode
{
	BoundaryTemplatePrism::BoundaryTemplatePrism(){
	}
	
	BoundaryTemplatePrism::~BoundaryTemplatePrism(){
	}
	
	bool BoundaryTemplatePrism::getSubelements(vector<unsigned int> &all, 
											   vector<unsigned int> &in,
											   vector<unsigned int> &out,
											   vector<vector<unsigned int> > &newsubs_in,
											   vector<vector<unsigned int> > &newsubs_out){
		
		//the following should never happen, but it's better to prevent ...
		if (in.empty()) {
			newsubs_in.push_back(all);
			return true;
		}
		
		unsigned int n_base = in.size();
		
		std::cout << "Prism in nodes " << n_base << "\n";
		
		if (n_base==1) {
			vector<unsigned int> rotated, tet1(4,0), pyr1(5,0);
			rotated = rotate(all,in[0]);
			
			tet1[0] = rotated[0];
			tet1[1] = rotated[2];
			tet1[2] = rotated[3];
			tet1[3] = rotated[1];
			
			pyr1[0] = rotated[1];
			pyr1[1] = rotated[4];
			pyr1[2] = rotated[5];
			pyr1[3] = rotated[2];
			pyr1[4] = rotated[3];
			
			newsubs_in.push_back(tet1);
			newsubs_out.push_back(pyr1);
			
			return true;
		}
		
		if (n_base==2) {
			vector<unsigned int> rotated;
			rotated = rotate(all,in[0]);
			
			//first case: the two base nodes are connected, then
			//it's not necessary to split into two tetra
			if (rotated[1] == in[1]) {
				template2A(rotated,newsubs_in,newsubs_out);
				return true;
			}
			else if (rotated[2] == in[1]) {
				rotated = rotatePosX(rotated);
				template2A(rotated,newsubs_in,newsubs_out);
				return true;
			}
			
			else if (rotated[3] == in[1]) {
				template2B(rotated,newsubs_in,newsubs_out);
				return true;
			}
			else if (rotated[4] == in[1]) {
				template2C(rotated,newsubs_in,newsubs_out);
				return true;
			}
			else if (rotated[5] == in[1]) {
				rotated = rotatePosX(rotated);
				template2D(rotated,newsubs_in,newsubs_out);
				return true;
			}
			
			return true;
		}
		
		//for case 3 it's easier to detect the cases with a vector
		//of booleans
		vector<bool> inside (6,false);
		for (unsigned int i=0; i<in.size(); i++) {
			inside[in[i]]=true;
		}
		
		if (n_base==3) {
			
			if (threeInTFace(inside)) {
				newsubs_in.push_back(all);
				return true;
			}
			cout << "not mannaged case with 3 nodes\n";
		}
		
		
		if (n_base==5) {
			vector<unsigned int> rotated, tet1(4,0), pyr1(5,0);
			rotated = rotate(all,out[0]);
			
			tet1[0] = rotated[3];
			tet1[1] = rotated[5];
			tet1[2] = rotated[4];
			tet1[3] = rotated[0];
			
			pyr1[0] = rotated[1];
			pyr1[1] = rotated[4];
			pyr1[2] = rotated[5];
			pyr1[3] = rotated[2];
			pyr1[4] = rotated[0];
			
			newsubs_in.push_back(tet1);
			newsubs_in.push_back(pyr1);
			
			return true;
		}
		
		if (n_base==6) {
			newsubs_in.push_back(all);
			return true;
		}
		
		cout << "not mannaged case with 4 nodes\n";
		return false;
	}
	
	
	void BoundaryTemplatePrism::template2A(vector<unsigned int> &rotated, 
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){
		
		vector<unsigned int> tet1(4,0), pyr1(5,0);
		
		tet1[0] = rotated[3];
		tet1[1] = rotated[5];
		tet1[2] = rotated[4];
		tet1[3] = rotated[2];
		
		pyr1[0] = rotated[0];
		pyr1[1] = rotated[3];
		pyr1[2] = rotated[4];
		pyr1[3] = rotated[1];
		pyr1[4] = rotated[2];
		
		newsubs_in.push_back(pyr1);
		newsubs_out.push_back(tet1);
	}
	
	void BoundaryTemplatePrism::template2B(vector<unsigned int> &rotated, 
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){
		
		newsubs_in.push_back(rotated);
	}
	
	void BoundaryTemplatePrism::template2C(vector<unsigned int> &rotated, 
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){
		
		vector<unsigned int> tet1(4,0), tet2(4,0), tet3(4,0);
		
		tet1[0] = rotated[0];
		tet1[1] = rotated[2];
		tet1[2] = rotated[3];
		tet1[3] = rotated[1];
		
		tet2[0] = rotated[2];
		tet2[1] = rotated[5];
		tet2[2] = rotated[3];
		tet2[3] = rotated[4];
		
		tet3[0] = rotated[2];
		tet3[1] = rotated[4];
		tet3[2] = rotated[3];
		tet3[3] = rotated[1];
		
		newsubs_in.push_back(tet1);
		newsubs_in.push_back(tet2);
		newsubs_out.push_back(tet3);
	}
	
	void BoundaryTemplatePrism::template2D(vector<unsigned int> &rotated, 
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){
		
		vector<unsigned int> tet1(4,0), tet2(4,0), tet3(4,0);
		
		tet1[0] = rotated[0];
		tet1[1] = rotated[2];
		tet1[2] = rotated[3];
		tet1[3] = rotated[1];
		
		tet2[0] = rotated[1];
		tet2[1] = rotated[5];
		tet2[2] = rotated[3];
		tet2[3] = rotated[4];
		
		tet3[0] = rotated[1];
		tet3[1] = rotated[2];
		tet3[2] = rotated[3];
		tet3[3] = rotated[5];
		
		newsubs_in.push_back(tet1);
		newsubs_in.push_back(tet2);
		newsubs_out.push_back(tet3);
	}
	
	
	vector<unsigned int> BoundaryTemplatePrism::rotate(vector<unsigned int> &original,
													   int index){
		
		vector<unsigned int> rotated(6,0);
		switch(index){
			case 0:
				return original;		  
				/*node 1 is now node 0*/
			case 1:
				rotated[0] = original[1];
				rotated[1] = original[2];
				rotated[2] = original[0];
				rotated[3] = original[4];
				rotated[4] = original[5];
				rotated[5] = original[3];
				return rotated;
			case 2:
				/*node 2 is now node 0*/
				rotated[0] = original[2];
				rotated[1] = original[0];
				rotated[2] = original[1];
				rotated[3] = original[5];
				rotated[4] = original[3];
				rotated[5] = original[4];
				return rotated;
				/*node 3 is now node 0*/
			case 3:
				rotated[0] = original[3];
				rotated[1] = original[5];
				rotated[2] = original[4];
				rotated[3] = original[0];
				rotated[4] = original[2];
				rotated[5] = original[1];
				return rotated;
				/*node 4 is now node 0*/
			case 4:
				rotated[0] = original[4];
				rotated[1] = original[3];
				rotated[2] = original[5];
				rotated[3] = original[1];
				rotated[4] = original[0];
				rotated[5] = original[2];
				return rotated;
				/*node 5 is now node 0*/
			case 5:
				rotated[0] = original[5];
				rotated[1] = original[4];
				rotated[2] = original[3];
				rotated[3] = original[2];
				rotated[4] = original[1];
				rotated[5] = original[0];
				return rotated;
			default:
				return rotated;
		}
	}
	
	vector<unsigned int> BoundaryTemplatePrism::rotatePosX(vector<unsigned int> &original){
		
		vector<unsigned int> rotated(6,0);
		
		rotated[0] = original[2];
		rotated[1] = original[0];
		rotated[2] = original[1];
		rotated[3] = original[5];
		rotated[4] = original[3];
		rotated[5] = original[4];
		return rotated;
	}
	
	vector<unsigned int> BoundaryTemplatePrism::rotateNegX(vector<unsigned int> &original){
		
		vector<unsigned int> rotated(6,0);
		
		rotated[0] = original[1];
		rotated[1] = original[2];
		rotated[2] = original[0];
		rotated[3] = original[4];
		rotated[4] = original[5];
		rotated[5] = original[3];
		return rotated;
	}
	
	bool BoundaryTemplatePrism::threeInTFace(vector<bool> &inside){
		if (inside[0] && inside[1] && inside[2]) {
			return true;
		}
		if (inside[3] && inside[4] && inside[5]) {
			return true;
		}
		return false;
	}
}
