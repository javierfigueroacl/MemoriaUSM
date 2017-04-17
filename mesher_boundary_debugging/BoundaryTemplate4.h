#ifndef BoundaryTemplate4_h
#define BoundaryTemplate4_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
	class BoundaryTemplate4 {
		
	public:
		
		BoundaryTemplate4();
		
		virtual ~BoundaryTemplate4();
		
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &in,
									vector<MeshPoint> &pts,
									vector<vector<unsigned int> > &newsubs_in,
									vector<vector<unsigned int> > &newsubs_out);
		
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
		
		virtual void PatternD(vector<unsigned int> &all,
							  vector<MeshPoint> &pts,  
							  vector<vector<unsigned int> > &newsubs_in,
							  vector<vector<unsigned int> > &newsubs_out);
		
		virtual void PatternE(vector<unsigned int> &all,
							  vector<MeshPoint> &pts,  
							  vector<vector<unsigned int> > &neweles);
		
		virtual void PatternF(vector<unsigned int> &all,
							  vector<MeshPoint> &pts,  
							  vector<vector<unsigned int> > &neweles);
		
		virtual void PatternG(vector<unsigned int> &all,
							  vector<MeshPoint> &pts,  
							  vector<vector<unsigned int> > &neweles);
		
		virtual void swap(vector<unsigned int> &vec,int pos1, int pos2);
		
		virtual vector<unsigned int> getEdges(int p);
		
	};
}
#endif
