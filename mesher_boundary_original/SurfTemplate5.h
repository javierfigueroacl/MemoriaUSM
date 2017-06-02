#ifndef SurfTemplate5_h
#define SurfTemplate5_h 3

#include <vector>
#include <list>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;
using std::list;
using Clobscode::MeshPoint;

namespace Clobscode
{
	class VolumePointContainer;
	
	class SurfTemplate5 {
		
	public:
		
		SurfTemplate5();
		
		virtual ~SurfTemplate5();
		
		//eventually, this pattern will add new MeshPoints. If 
		//this is the case they will be included in the list newpts.
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &in,
									vector<MeshPoint> &pts,
									list<MeshPoint> &newpts,
									vector<vector<unsigned int> > &neweles);
		
	protected:
		
		virtual void PatternA(vector<unsigned int> &all, 
							  vector<MeshPoint> &pts,
							  list<MeshPoint> &newpts,
							  vector<vector<unsigned int> > &neweles);
		
		virtual void PatternB(vector<unsigned int> &all, 
							  vector<vector<unsigned int> > &neweles);
		
		virtual void PatternC(vector<unsigned int> &all, 
							  vector<vector<unsigned int> > &neweles);
		
		virtual vector<unsigned int> searchPivote(vector<unsigned int> &doubles);
		
		virtual vector<unsigned int> getEdges(int p);
		
	};
}
#endif
