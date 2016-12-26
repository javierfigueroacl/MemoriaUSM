#ifndef SurfPrism_h
#define SurfPrism_h 3

#include "FaceDiagonal.h"
#include "MeshPoint.h"
#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;

namespace Clobscode
{
	class SurfPrism {
		
	public:
		
		SurfPrism(vector<unsigned int> &mypoints);
		
		virtual ~SurfPrism();
		
		virtual vector<vector<unsigned int> > getSubElements(vector<bool> &inside_state);
        
        virtual double getQuality(vector<MeshPoint> &allpoints);
        
        virtual vector<vector<unsigned int> > getTetras();
        
    protected:
        
        virtual unsigned int opposite(unsigned int idx);
        
        virtual void oppositeFace(unsigned int idx, vector<unsigned int> &base);
        
        virtual bool oneRepeated(vector<unsigned int> &original, vector<unsigned int> &result);
        
        virtual vector<unsigned int> sortDiagonals(list<unsigned int> &original);
        
    protected:
        
        vector<unsigned int> points;
        
        double scaled_jac_constant;
		
	};
}
#endif
