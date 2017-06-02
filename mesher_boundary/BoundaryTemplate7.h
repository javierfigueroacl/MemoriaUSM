#ifndef BoundaryTemplate7_h
#define BoundaryTemplate7_h 1

#include <vector>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
	class BoundaryTemplate7 {
		
	public:
		BoundaryTemplate7();
		
		virtual ~BoundaryTemplate7();
		
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &in,
									vector<MeshPoint> &pts,
									vector<vector<unsigned int> > &neweles);
		
	};
}
#endif
