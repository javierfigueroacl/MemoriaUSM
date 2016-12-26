#include "EdgeContainer.h"

namespace TxTriModel {
	
	EdgeContainer::EdgeContainer(unsigned int size){
		edgeindexer.reserve(size);
		indexed.reserve(size);
		this->size=0;
	}
	
	EdgeContainer::~EdgeContainer(){
		
	}
	
	unsigned int EdgeContainer::addEdge(unsigned int point1,
										unsigned int point2,
										unsigned int faceindex){
		Edge ne(point1,point2);
		
		if(edgeindexer.size()<ne.getKey()+1){
			//Edge first insertion.
			for(unsigned int i=edgeindexer.size(); i<ne.getKey()+1; i++){
				list<Pair> dummy;
				edgeindexer.push_back(dummy);
			}
			ne.addFace(faceindex);
			return addEdge(ne);
		}
		else{
			//at this point the edge key exists in the vector
			list<Pair> pairs = edgeindexer[ne.getKey()];
			list<Pair>::iterator iter;
			for(iter=pairs.begin();iter!=pairs.end();iter++){
				if((*iter)[0]==ne.getVal()){
					//the edge was found, so the list of faces of it is updated
					indexed[(*iter)[1]].addFace(faceindex);
					return (*iter)[1];
				}
			}
			//the edge was not found, so it must be inserted;
			ne.addFace(faceindex);
			return addEdge(ne);
		}
        return 0;
	}
	
	unsigned int EdgeContainer::addEdge(Edge &e){
		Pair np(e.getVal(),size);
		edgeindexer[e.getKey()].push_back(np);
		indexed.push_back(e);
		return size++;
	}
	
	
	Edge &EdgeContainer::getEdge(unsigned int index){
		if(index>=size)
			std::cerr << "Index out of boundary in EdgeContainer\n";
		return indexed[index];
	}
	
	ostream& operator<<(ostream& o,EdgeContainer &ec){
		for(int i=0;i<ec.length();i++){
			o << ec.getEdge(i) << " [";
			list<unsigned int> ef = ec.getEdge(i).getFaces();
			list<unsigned int>::iterator iter;
			int semicolon=0;
			for(iter=ef.begin();iter!=ef.end();iter++){
				o << *iter;
				if(semicolon++<ef.size()-1)
					o << ",";
			}
			o << "]\n";
		}
        return o;
	}
}
