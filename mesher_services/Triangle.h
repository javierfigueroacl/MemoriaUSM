#include "Vector3D.h"
#include "VPoint3D.h"
#include <vector>
#include <iostream>

using TxGeom::Vector3D;
using TxGeom::VPoint3D;
using std::vector;

namespace TxTriModel
{
	class Triangle
	{
	public:
		
		// Construction / destruction
		Triangle();
		virtual ~Triangle();

		virtual void setVertices(vector<unsigned int> &fpts);
		
		virtual void computeNormal(vector<VPoint3D> &pts);
		
		virtual Vector3D computeNormalAtNode(unsigned int nidx, 
											 vector<VPoint3D> &pts);
		
		virtual VPoint3D projection(const VPoint3D &p1, const VPoint3D &p2);
	
		//computes the distant of pPoint to the plane formed by this triangle.
		virtual double distance(const VPoint3D &pPoint);
		
		// Data
		unsigned int mIdxV[3];
		Vector3D mTriangleNormal;
		VPoint3D onepoint;
	};
	
	inline void Triangle::setVertices(vector<unsigned int> &fpts){
		mIdxV[0] = fpts[0];
		mIdxV[1] = fpts[1];
		mIdxV[2] = fpts[2];
	}
}