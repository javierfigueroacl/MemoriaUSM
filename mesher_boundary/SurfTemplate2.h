#ifndef SurfTemplate2_h
#define SurfTemplate2_h 3

#include <vector>
#include "HexRotation.h"
#include <iostream>

using std::vector;

namespace Clobscode
{
class SurfTemplate2 {
	
  public:
	
	SurfTemplate2();
	
	virtual ~SurfTemplate2();
	
	virtual bool getSubelements(vector<unsigned int> &all, 
								vector<unsigned int> &in,
								vector<vector<unsigned int> > &neweles);
	
  protected:
	
	virtual void PatternA(vector<unsigned int> &all, 
						  vector<vector<unsigned int> > &neweles);
	
	virtual void PatternB(vector<unsigned int> &all, 
						  vector<vector<unsigned int> > &neweles);
	
	virtual void PatternC(vector<unsigned int> &all, 
						  vector<vector<unsigned int> > &neweles);
	
};
}
#endif
