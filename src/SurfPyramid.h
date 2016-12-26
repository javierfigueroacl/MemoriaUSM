#ifndef SurfPyramid_h
#define SurfPyramid_h 3

#include "FaceDiagonal.h"
#include "MeshPoint.h"
#include <vector>
#include <list>
#include <iostream>
#include <math.h>

using std::vector;
using std::list;

namespace Clobscode
{
	class SurfPyramid {
		
	public:
		
		SurfPyramid(vector<unsigned int> &mypoints);
		
		virtual ~SurfPyramid();
		
		virtual vector<vector<unsigned int> > getSubElements(vector<bool> &inside_state);
        
        virtual vector<vector<unsigned int> > getTetras();
        
        virtual double getQuality(vector<MeshPoint> &allpoints);
                
    protected:
        
        vector<unsigned int> points;
        
        double scaled_jac_constant;
		
	};
}
#endif
