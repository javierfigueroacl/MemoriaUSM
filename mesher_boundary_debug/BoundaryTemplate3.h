#ifndef BoundaryTemplate3_h
#define BoundaryTemplate3_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"

using std::vector;

namespace Clobscode
{
class BoundaryTemplate3 {
	
  public:
      BoundaryTemplate3();

      virtual ~BoundaryTemplate3();

	virtual bool getSubelements(vector<unsigned int> &all, 
								vector<unsigned int> &in,
								vector<MeshPoint> &pts,
								vector<vector<unsigned int> > &newsubs_in,
								vector<vector<unsigned int> > &newsubs_out);

  protected:

      virtual void PatternA(vector<unsigned int> &all,
						 	vector<MeshPoint> &pts,  
							vector<vector<unsigned int> > &newsubs_in,
							vector<vector<unsigned int> > &newsubs_out);

      virtual void PatternB(vector<unsigned int> &all,
						 	vector<MeshPoint> &pts,  
							vector<vector<unsigned int> > &newsubs_in,
							vector<vector<unsigned int> > &newsubs_out);

      virtual void PatternC(vector<unsigned int> &all,
						 	vector<MeshPoint> &pts,  
							vector<vector<unsigned int> > &newsubs_in,
							vector<vector<unsigned int> > &newsubs_out);

      virtual void PatternD(vector<unsigned int> &all,
						 	vector<MeshPoint> &pts,  
							vector<vector<unsigned int> > &newsubs_in,
							vector<vector<unsigned int> > &newsubs_out);

      virtual void swap(vector<unsigned int> &vec,int pos1, int pos2);

};
}
#endif
