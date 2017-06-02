#ifndef BoundaryTemplatePrism_h
#define BoundaryTemplatePrism_h 1

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
	class BoundaryTemplatePrism {
		
	public:
		BoundaryTemplatePrism();
		
		virtual ~BoundaryTemplatePrism();
		
		virtual bool getSubelements(vector<unsigned int> &all, 
									vector<unsigned int> &in,
									vector<unsigned int> &out,
									vector<vector<unsigned int> > &newsubs_in,
									vector<vector<unsigned int> > &newsubs_out);
		
	protected:
		
		virtual vector<unsigned int> rotate(vector<unsigned int> &original, 
											int idx);
		
		virtual vector<unsigned int> rotatePosX(vector<unsigned int> &original);
		
		virtual vector<unsigned int> rotateNegX(vector<unsigned int> &original);
		
		virtual void template2A(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &newsubs_in,
								vector<vector<unsigned int> > &newsubs_out);
		
		virtual void template2B(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &newsubs_in,
								vector<vector<unsigned int> > &newsubs_out);
		
		virtual void template2C(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &newsubs_in,
								vector<vector<unsigned int> > &newsubs_out);
		
		virtual void template2D(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &newsubs_in,
								vector<vector<unsigned int> > &newsubs_out);
		
		virtual bool threeInTFace(vector<bool> &inside);
	};
}
#endif
