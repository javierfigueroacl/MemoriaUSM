#include "stdafx.h"
#include "Triangle.h"

namespace TxTriModel
{
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	Triangle::Triangle()
	{
		mIdxV[0] = mIdxV[1] = mIdxV[2] = -1;
		//mIdxN[0] = mIdxN[1] = mIdxN[2] = -1;
	}

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	Triangle::~Triangle()
	{
	}

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	void Triangle::computeNormal(vector<VPoint3D> &pts) 
	{
		// triangle normal computation
		// vector between A and B
		Vector3D  vec01;
		vec01 = pts[mIdxV[1]] - pts[mIdxV[0]];

		// vector between A and C
		Vector3D  vec02;
		vec02 = pts[mIdxV[2]] - pts[mIdxV[0]];

		Vector3D N  = vec01^vec02;

		mTriangleNormal = N/N.Norm();
		
		onepoint = pts[mIdxV[0]];
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	double Triangle::distance(const VPoint3D &p){
		Vector3D vd = p - onepoint;
		return vd*mTriangleNormal;
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	
	VPoint3D Triangle::projection(const VPoint3D &p1, const VPoint3D &p2){
		
		
		double d1 = distance(p1), d2 = distance(p2), s;
		s = d1/(d1-d2);
		
		Vector3D dif = p2 - p1;
		dif *= s;
		
		return p1 - dif;
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	Vector3D Triangle::computeNormalAtNode(unsigned int nidx, 
										   vector<VPoint3D> &pts ) 
	{
		//return mTriangleNormal;
		unsigned int lidx = 0;
		bool found = true;
		
		if (nidx == mIdxV[0]) {
			lidx = 0;
		}
		else {
			if (nidx == mIdxV[1]) {
				lidx = 1;
			}
			else {
				if (nidx == mIdxV[2]) {
					lidx = 2;
				}
				else {
					found = false;
				}
			}
		}

		if (!found) {
			Vector3D v;
			std::cerr << "warning at TxTriModel::Triangle::computeNormalAtNode";
			std::cerr << " node index not found in triangle\n";
			return v;
		}
		
		// triangle normal computation
		// vector between A and B
		Vector3D  vec1;
		vec1 = pts[mIdxV[(lidx+1)%3]] - pts[mIdxV[lidx]];
		
		// vector between A and C
		Vector3D  vec2;
		vec2 = pts[mIdxV[(lidx+2)%3]] - pts[mIdxV[lidx]];
		double angle = acos((vec1*vec2)/(vec1.Norm()*vec2.Norm()));
		return angle * mTriangleNormal;
	}
}