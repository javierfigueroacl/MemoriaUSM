#ifndef BoundaryTemplate1_h
#define BoundaryTemplate1_h 1

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
class BoundaryTemplate1 {
	
  public:
      BoundaryTemplate1();

      virtual ~BoundaryTemplate1();

      virtual bool getSubelements(vector<unsigned int> &all, 
								  vector<unsigned int> &in,
								  vector<MeshPoint> &pts,
								  list<MeshPoint> &newpts,
								  vector<vector<unsigned int> > &newsubs_in,
								  vector<vector<unsigned int> > &newsubs_out);

};
}
#endif
