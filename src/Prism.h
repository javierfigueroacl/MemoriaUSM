#ifndef Prism_h
#define Prism_h 3

#include "FaceDiagonal.h"
#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;

namespace Clobscode
{
	class Prism {
		
	public:
		
		Prism(vector<unsigned int> &mypoints);
		
		virtual ~Prism();
		
		virtual vector<vector<unsigned int> > getSubElements(vector<bool> &inside_state);
        
    protected:
        
        virtual unsigned int opposite(unsigned int idx);
        
        virtual void oppositeFace(unsigned int idx, vector<unsigned int> &base);
        
        virtual bool oneRepeated(vector<unsigned int> &original, vector<unsigned int> &result);
        
        virtual vector<unsigned int> sortDiagonals(list<unsigned int> &original);
        
    protected:
        
        vector<unsigned int> points;
		
	};
}
#endif
