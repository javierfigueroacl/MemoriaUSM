#ifndef EdgeContainer_h
#define EdgeContainer_h 1

#include <iostream>
#include <vector>
#include <list>
#include "Edge.h"
#include "Pair.h"

using std::vector;
using std::list;
using std::ostream;

namespace TxTriModel
{
	class EdgeContainer{
		
	public:
		
		EdgeContainer(unsigned int size);
		
		virtual ~EdgeContainer();
		
		virtual unsigned int addEdge(unsigned int point1,
									 unsigned int point2,
									 unsigned int faceindex);
		
		virtual Edge &getEdge(unsigned int index);
		
		virtual unsigned int length();
		
	protected:
		
		virtual unsigned int addEdge(Edge &e);
		
	protected:
		
		vector<list<Pair> > edgeindexer;
		vector<Edge> indexed;
		unsigned int size;
		
	};
	
	inline unsigned int EdgeContainer::length(){
		return size;
	}
	
	ostream& operator<<(ostream& o,EdgeContainer &ec);
}
#endif
