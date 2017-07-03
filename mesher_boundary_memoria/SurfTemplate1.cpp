#include "stdafx.h"
#include "SurfTemplate1.h"

namespace Clobscode
{
	SurfTemplate1::SurfTemplate1(){
	}
	
	SurfTemplate1::~SurfTemplate1(){
	}
	
	bool SurfTemplate1::getSubelements(vector<unsigned int> &all, 
									  vector<unsigned int> &in,
									  vector<vector<unsigned int> > &newsubs){
		
		newsubs.reserve(1);
		vector<unsigned int> tetra,rotated;
		HexRotation hrot;
		tetra.reserve(4);
		
		rotated = hrot.rotate(all,in[0]);
		
		tetra.push_back(rotated[0]);
		tetra.push_back(rotated[1]);
		tetra.push_back(rotated[3]);
		tetra.push_back(rotated[4]);
		
		newsubs.push_back(tetra);
		
		return true;
	}
}
