#ifndef SurfTemplate7_h
#define SurfTemplate7_h 1

#include <vector>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
	class SurfTemplate7 {
		
	public:
		SurfTemplate7();
		
		virtual ~SurfTemplate7();
		
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &in,
								          vector<MeshPoint> &pts,
									vector<vector<unsigned int> > &neweles);
		
	};
}
#endif
