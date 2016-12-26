#ifndef Pair_h
#define Pair_h 1

#include <iostream>

using std::ostream;

namespace TxTriModel {

	class Pair{
		
	public:
		
		Pair();
		
		Pair(unsigned int key, unsigned int val);
		
		virtual ~Pair();
		
		virtual unsigned int &operator[](unsigned int pos);
		
		virtual void operator=(Pair p2);
		
	protected:
		
		unsigned int key,val;
		
	};
	
	ostream& operator<<(ostream& o,Pair &p);
	
	bool operator==(Pair &p1,Pair &p2);
	
	bool operator!=(Pair &p1,Pair &p2);
}

#endif
