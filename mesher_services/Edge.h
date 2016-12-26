#ifndef Edge_h
#define Edge_h 1

#include <iostream>
#include <vector>
#include <list>

using std::list;
using std::vector;
using std::ostream;

namespace TxTriModel {

	class Edge{
		
	public:
		
		Edge();
		
		Edge(unsigned int point1, unsigned int point2);
		
		virtual ~Edge();
		
		virtual unsigned int getKey();
		
		virtual unsigned int getVal();
		
		virtual unsigned int numberOfFaces();
		
		virtual void addFace(unsigned int faceindex);
		
		virtual list<unsigned int> &getFaces();
		
		virtual unsigned int getOtherFace(unsigned int vf);
		
	protected:
		
		vector<unsigned int> nodes;
		list<unsigned int> faces;
		
	};
	
	inline unsigned int Edge::getKey(){
		return nodes[0];
	}
	
	inline unsigned int Edge::getVal(){
		return nodes[1];
	}
	
	inline unsigned int Edge::numberOfFaces(){
		return faces.size();
	}
	
	inline void Edge::addFace(unsigned int faceindex){
		list<unsigned int>::iterator iter;
		for(iter=faces.begin();iter!=faces.end(); iter++){
			if(faceindex==*iter)
				return;
		}
		faces.push_back(faceindex);
	}
	
	inline list<unsigned int> &Edge::getFaces(){
		return faces;
	}
		
	inline unsigned int Edge::getOtherFace(unsigned int vf){
		list<unsigned int>::iterator iter;
		for(iter=faces.begin();iter!=faces.end(); iter++){
			if (*iter!=vf) {
				return *iter;
			}
		}
        return 0;
	}
		
	ostream& operator<<(ostream& o,Edge &p);
	
	bool operator==(Edge &p1,Edge &p2);
	
	bool operator!=(Edge &p1,Edge &p2); 
}
#endif
