#include "Pair.h"

namespace TxTriModel {
	
	Pair::Pair(){
		key=val=-1;
	}
	
	Pair::Pair(unsigned int key, unsigned int val){
		this->key=key;
		this->val=val;
	}
	
	Pair::~Pair(){
		
	}
	
	void Pair::operator=(Pair p2){
		key=p2[0];
		val=p2[1];
	}
	
	ostream& operator<<(ostream& o,Pair &p){
		o << p[0] << " ";
		o << p[1];
		return o;
	}
	
	bool operator==(Pair &p1,Pair &p2){
		if(p1[0]==p2[0] && p1[1]==p2[1])
			return true;
		return false;
	}
	
	bool operator!=(Pair &p1,Pair &p2){
		return !(p1==p2);
	}
	
	unsigned int &Pair::operator[](unsigned int pos){
		if(pos==0)
			return key;
		return val;
	}
	
}