#ifndef BoundaryTemplate6_h
#define BoundaryTemplate6_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
	class BoundaryTemplate6 {
		
	public:
		BoundaryTemplate6();
		
		virtual ~BoundaryTemplate6();
		
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &out,
									vector<MeshPoint> &pts,
									vector<vector<unsigned int> > &neweles,
									vector<vector<unsigned int> > &newsubs_out);
		
	protected:
		
		virtual void PatternA(vector<unsigned int> &all, 
							  vector<MeshPoint> &pts,
							  vector<vector<unsigned int> > &neweles,
							  vector<vector<unsigned int> > &newsubs_out);
		
		virtual void PatternB(vector<unsigned int> &all, 
							  vector<vector<unsigned int> > &neweles);
		
		virtual void PatternC(vector<unsigned int> &all, 
							  vector<vector<unsigned int> > &neweles);
		
	};
}
#endif
