#include "Edge.h"

namespace TxTriModel {
	
	Edge::Edge(unsigned int point1, unsigned int point2){
		nodes.reserve(2);
		if(point1 < point2){
			nodes.push_back(point1);
			nodes.push_back(point2);
		}
		else{ 
			nodes.push_back(point2);
			nodes.push_back(point1);
		}
	}
	
	Edge::~Edge(){
		
	}
	
	ostream& operator<<(ostream& o,Edge &e){
		o << "e(" << e.getKey() << ",";
		o << e.getVal() << ")" << " f(";
		list<unsigned int> faces = e.getFaces();
		for (list<unsigned int>::iterator iter=faces.begin(); iter!=faces.end(); iter++) {
			o << " " << *iter;
		}
		o << " )";
		return o;
	}
	
	bool operator==(Edge &e1,Edge &e2){
		if(e1.getKey()==e2.getKey() && e1.getVal()==e2.getVal())
			return true;
		return false;
	}
	
	bool operator!=(Edge &p1,Edge &p2){
		return !(p1==p2);
	}
}
