#ifndef SurfEdgeContainer_h
#define SurfEdgeContainer_h 1

#include <iostream>
#include <vector>
#include <list>
#include "SurfEdge.h"
#include "SurfPair.h"

using std::vector;
using std::list;
using std::ostream;

namespace SurfMesh
{
	class SurfEdgeContainer{
		
	public:
		
		SurfEdgeContainer(unsigned int size);
		
		virtual ~SurfEdgeContainer();
		
		virtual unsigned int addEdge(unsigned int point1,
									 unsigned int point2,
									 unsigned int faceindex);
		
		virtual SurfEdge &getEdge(unsigned int index);
		
		virtual unsigned int length();
		
	protected:
		
		virtual unsigned int addEdge(SurfEdge &e);
		
	protected:
		
		vector<list<SurfPair> > edgeindexer;
		vector<SurfEdge> indexed;
		unsigned int size;
		
	};
	
	inline unsigned int SurfEdgeContainer::length(){
		return size;
	}
	
	ostream& operator<<(ostream& o,SurfEdgeContainer &ec);
}
#endif
