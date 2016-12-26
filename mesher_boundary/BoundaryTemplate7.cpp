#include "stdafx.h"
#include "BoundaryTemplate7.h"

namespace Clobscode
{
	BoundaryTemplate7::BoundaryTemplate7(){
	}
	
	BoundaryTemplate7::~BoundaryTemplate7(){
	}
	
	bool BoundaryTemplate7::getSubelements(vector<unsigned int> &all, 
									  vector<unsigned int> &out,
									  vector<vector<unsigned int> > &newsubs){
		
		newsubs.reserve(3);
		vector<unsigned int> rotated,py1(5,0),py2(5,0),py3(5,0);
		HexRotation hrot;
		if(out.size()!=1)
			return false;
		
		rotated = hrot.rotate(all,out[0]);
		
		py1[0] = rotated[1];
		py1[1] = rotated[5];
		py1[2] = rotated[6];
		py1[3] = rotated[2];
		py1[4] = rotated[0];
		
		py2[0] = rotated[2];
		py2[1] = rotated[6];
		py2[2] = rotated[7];
		py2[3] = rotated[3];
		py2[4] = rotated[0];
		
		py3[0] = rotated[4];
		py3[1] = rotated[7];
		py3[2] = rotated[6];
		py3[3] = rotated[5];
		py3[4] = rotated[0];
		
		newsubs.push_back(py1);
		newsubs.push_back(py2);
		newsubs.push_back(py3);
		
		return true;
	}
}
