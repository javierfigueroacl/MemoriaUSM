#ifndef SurfTemplate3_h
#define SurfTemplate3_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
class SurfTemplate3 {
	
  public:
      SurfTemplate3();

      virtual ~SurfTemplate3();

      virtual bool getSubelements(vector<unsigned int> &all, 
								  vector<unsigned int> &in,
								  vector<MeshPoint> &pts,
								  vector<vector<unsigned int> > &neweles);

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
							vector<vector<unsigned int> > &neweles);

      virtual void swap(vector<unsigned int> &vec,int pos1, int pos2);

};
}
#endif
