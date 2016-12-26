#ifndef SurfPair_h
#define SurfPair_h 1

#include <iostream>

using std::ostream;

namespace SurfMesh {

	class SurfPair{
		
	public:
		
		SurfPair();
		
		SurfPair(unsigned int key, unsigned int val);
		
		virtual ~SurfPair();
		
		virtual unsigned int &operator[](unsigned int pos);
		
		virtual void operator=(SurfPair p2);
		
	protected:
		
		unsigned int key,val;
		
	};
	
	ostream& operator<<(ostream& o,SurfPair &p);
	
	bool operator==(SurfPair &p1,SurfPair &p2);
	
	bool operator!=(SurfPair &p1,SurfPair &p2);
}

#endif
