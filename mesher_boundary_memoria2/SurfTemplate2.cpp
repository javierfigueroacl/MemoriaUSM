#include "stdafx.h"
#include "SurfTemplate2.h"

namespace Clobscode
{
	SurfTemplate2::SurfTemplate2(){
	}
	
	SurfTemplate2::~SurfTemplate2(){
	}
	
	bool SurfTemplate2::getSubelements(vector<unsigned int> &all, 
									  vector<unsigned int> &in,
									  vector<vector<unsigned int> > &neweles){
		
		HexRotation hrot;
		vector<unsigned int> rotated;
		if(in.size()!=2)
			return false;
		
		//center all at the first node:
		rotated = hrot.rotate(all,in[0]);
		
		//Possible cases for PatternA
		if(rotated[3] == all[in[1]]){
			PatternA(rotated,neweles);
			return true;
		}
		if(rotated[1] == all[in[1]]){
			rotated = hrot.rotateNegY(rotated);
			PatternA(rotated,neweles);
			return true;
		}
		if(rotated[4] == all[in[1]]){
			rotated = hrot.rotatePosZ(rotated);
			PatternA(rotated,neweles);
			return true;
		}
		
		//Possible cases for PatternB
		if(rotated[2] == all[in[1]]){
			PatternB(rotated,neweles);
			return true;
		}
		if(rotated[5] == all[in[1]]){
			rotated = hrot.rotatePosZ(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,neweles);
			return true;
		}
		if(rotated[7] == all[in[1]]){
			rotated = hrot.rotateNegX(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,neweles);
			return true;
		}
		if(rotated[6] == all[in[1]]){
			PatternC(rotated,neweles);
			return true;
		}
		
		std::cerr << "Pattern2 not found for this configuration:\nin nodes:";
		for (unsigned int i=0;i<in.size();i++)
			std::cerr << " " << in[i];
		return false;
	}
	
	void SurfTemplate2::PatternA(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(1);
		
		vector<unsigned int> ele1 (6,0);
		
		ele1[0] = all[0];
		ele1[1] = all[4];
		ele1[2] = all[1];
		ele1[3] = all[3];
		ele1[4] = all[7];
		ele1[5] = all[2];
		
		eles.push_back(ele1);
	}
	
	void SurfTemplate2::PatternB(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(2);
		vector<unsigned int> ele1(4,0);
		vector<unsigned int> ele2(4,0);
		//vector<unsigned int> ele3(4,-1);
		
		ele1[0] = all[0];
		ele1[1] = all[1];
		ele1[2] = all[3];
		ele1[3] = all[4];
		
		ele2[0] = all[2];
		ele2[1] = all[3];
		ele2[2] = all[1];
		ele2[3] = all[6];
		
		
		/*this element might not be pertinent
		 ele3[0] = all[1];
		 ele3[1] = all[7];
		 ele3[2] = all[2];
		 ele3[3] = all[4];*/
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		//eles.push_back(new MTetrahedra(ele3));
	}
	
	void SurfTemplate2::PatternC(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(2);
		vector<unsigned int> ele1(4,0);
		vector<unsigned int> ele2(4,0);
		
		ele1[0] = all[0];
		ele1[1] = all[1];
		ele1[2] = all[3];
		ele1[3] = all[4];
		
		ele2[0] = all[6];
		ele2[1] = all[5];
		ele2[2] = all[7];
		ele2[3] = all[2];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		
	}
}