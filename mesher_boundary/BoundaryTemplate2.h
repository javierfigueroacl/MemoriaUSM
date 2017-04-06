#ifndef BoundaryTemplate2_h
#define BoundaryTemplate2_h 3

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
class BoundaryTemplate2 {
	
  public:
	
	BoundaryTemplate2();
	
	virtual ~BoundaryTemplate2();
	
	virtual bool getSubelements(vector<unsigned int> &all, 
								vector<unsigned int> &in,
								vector<MeshPoint> &pts,
								list<MeshPoint> &newpts,
								vector<vector<unsigned int> > &newsubs_in,
								vector<vector<unsigned int> > &newsubs_out,
								vector<vector<unsigned int> > &conflicting_elements);
	
  protected:
	
	virtual void PatternA(vector<unsigned int> &all, 
						  vector<MeshPoint> &pts,
						  vector<vector<unsigned int> > &newsubs_in,
						  vector<vector<unsigned int> > &newsubs_out,
						  vector<vector<unsigned int> > &conflicting_elements);
	
	virtual void PatternB(vector<unsigned int> &all,
						  vector<MeshPoint> &pts,
						  list<MeshPoint> &newpts,
						  vector<vector<unsigned int> > &newsubs_in,
						  vector<vector<unsigned int> > &newsubs_out);
	
	virtual void PatternC(vector<unsigned int> &all,
						  vector<MeshPoint> &pts,
						  list<MeshPoint> &newpts,
						  vector<vector<unsigned int> > &newsubs_in,
						  vector<vector<unsigned int> > &newsubs_out);
	
};
}
#endif
