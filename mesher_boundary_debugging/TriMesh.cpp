#include "stdafx.h"
#include "TriMesh.h"

namespace Clobscode
{
	TriMesh::TriMesh(){
		
	}
	
	TriMesh::~TriMesh(){
		
	}
	
	
	void TriMesh::computeBounds(){
		bounds.clear();
		bounds.assign(6,-1);
		if (points.empty()) {
			return;
		}
		bounds[0]=bounds[3]=points[0][0];
		bounds[1]=bounds[4]=points[0][1];
		bounds[2]=bounds[5]=points[0][2];
		for (unsigned int i=1; i< points.size(); i++) {
			double x = points[i][0];
			double y = points[i][1];
			double z = points[i][2];
			if(bounds[0]>x)
				bounds[0]=x;
			else if(bounds[3]<x)
				bounds[3]=x;
			if(bounds[1]>y)
				bounds[1]=y;
			else if(bounds[4]<y)
				bounds[4]=y;
			if(bounds[2]>z)
				bounds[2]=z;
			else if(bounds[5]<z)
				bounds[5]=z;
		}
	}
	
	void TriMesh::toCube(double per){
		
		double x = bounds[3]-bounds[0],
		y = bounds[4]-bounds[1],
		z = bounds[5]-bounds[2];
		
		double side;
		if(x<0)
			x=-x;
		if(y<0)
			y=-y;
		if(z<0)
			z=-z;
		
		
		if(x>y && x>z){
			double a1,a2;
			a1 = bounds[1] + (y-x)/2;
			a2 = bounds[4] + (x-y)/2;
			bounds[1] = a1;
			bounds[4] = a2;
			a1 = bounds[2] + (z-x)/2;
			a2 = bounds[5] + (x-z)/2;
			bounds[2] = a1;
			bounds[5] = a2;
			side =x;
		}
		else if(y>x && y>z){
			double a1,a2;
			a1 = bounds[0] + (x-y)/2;
			a2 = bounds[0] + (x+y)/2;
			bounds[0] = a1;
			bounds[3] = a2;
			a1 = bounds[2] + (z-y)/2;
			a2 = bounds[2] + (z+y)/2;
			bounds[2] = a1;
			bounds[5] = a2;
			side =y;
		}
		else{
			double a1,a2;
			a1 = bounds[0] + (x-z)/2;
			a2 = bounds[0] + (x+z)/2;
			bounds[0] = a1;
			bounds[3] = a2;
			a1 = bounds[1] + (y-z)/2;
			a2 = bounds[1] + (y+z)/2;
			bounds[1] = a1;
			bounds[4] = a2;
			side =z;
		}
		side*=per;
		bounds[0]-=side;bounds[1]-=side;bounds[2]-=side;
		bounds[3]+=side;bounds[4]+=side;bounds[5]+=side;
	}
}
