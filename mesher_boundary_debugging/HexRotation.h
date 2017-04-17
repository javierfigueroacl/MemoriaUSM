#ifndef HexRotation_h
#define HexRotation_h 1

#include <vector>

using std::vector;

namespace Clobscode
{
	class HexRotation {
		
	public:
		HexRotation();
		
		virtual ~HexRotation();
		
		virtual vector<unsigned int> rotate(vector<unsigned int> original,
											int index);
		
		virtual vector<unsigned int> rotatePosX(vector<unsigned int> original);
		
		virtual vector<unsigned int> rotateNegX(vector<unsigned int> original);
		
		virtual vector<unsigned int> rotatePosY(vector<unsigned int> original);
		
		virtual vector<unsigned int> rotateNegY(vector<unsigned int> original);
		
		virtual vector<unsigned int> rotatePosZ(vector<unsigned int> original);
		
		virtual vector<unsigned int> rotateNegZ(vector<unsigned int> original);
		
	};
}
#endif
