#ifndef BoundaryTemplatePyramid_h
#define BoundaryTemplatePyramid_h 1

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
	class BoundaryTemplatePyramid {
		
	public:
		BoundaryTemplatePyramid();
		
		virtual ~BoundaryTemplatePyramid();
		
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &in,
									vector<vector<unsigned int> > &newsubs_in,
									vector<vector<unsigned int> > &newsubs_out);
	
	protected:
		
		virtual vector<unsigned int> rotate(vector<unsigned int> &original, 
											int idx);
	};
}
#endif
