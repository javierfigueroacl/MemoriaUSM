#ifndef SurfTemplate6_h
#define SurfTemplate6_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
	class SurfTemplate6 {
		
	public:
		SurfTemplate6();
		
		virtual ~SurfTemplate6();
		
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &out,
							        	vector<MeshPoint> &pts,
									vector<vector<unsigned int> > &neweles);
		
	protected:
		
		virtual void PatternA(vector<unsigned int> &all, 
							  vector<MeshPoint> &pts,
							  vector<vector<unsigned int> > &neweles);
		
		virtual void PatternB(vector<unsigned int> &all, 
							  vector<MeshPoint> &pts,
							  vector<vector<unsigned int> > &neweles);
		
		virtual void PatternC(vector<unsigned int> &all, 
							  vector<MeshPoint> &pts,
							  vector<vector<unsigned int> > &neweles);
		
	};
}
#endif
