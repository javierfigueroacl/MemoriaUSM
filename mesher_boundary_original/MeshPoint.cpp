#include "stdafx.h"
#include "MeshPoint.h"

namespace Clobscode
{
	MeshPoint::MeshPoint(const unsigned int &nm){
		//we assume that every point is outisde by default.
		inside.assign(nm,false);
		//checking if a point is outside or not is a very expensive 
		//operation, so we try to do it only once
		outsidechecked = false;
		n_meshes = nm;
		
		maxdistance = 0;
	}
	
	MeshPoint::MeshPoint(Point3D &p, const unsigned int &nm){
		point = p;
		//we assume that every point is outisde by default.
		inside.assign(nm,false);
		//checking if a point is outside or not is a very expensive 
		//operation, so we try to do it only once
		outsidechecked = false;
		n_meshes = nm;
		
		maxdistance = 0;
	}
	
	MeshPoint::~MeshPoint(){
		
	}
		
	std::ostream& operator<<(std::ostream& o,MeshPoint &p){
		o << p.getPoint();
		return o;
	}
	
}
