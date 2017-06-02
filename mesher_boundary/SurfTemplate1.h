#ifndef SurfTemplate1_h
#define SurfTemplate1_h 1

#include <vector>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
class SurfTemplate1 {
	
  public:
      SurfTemplate1();

      virtual ~SurfTemplate1();

      virtual bool getSubelements(vector<unsigned int> &all, 
								  vector<unsigned int> &in,
								  vector<MeshPoint> &pts,
								  vector<vector<unsigned int> > &newsubs);

};
}
#endif
