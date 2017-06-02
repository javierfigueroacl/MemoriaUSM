#ifndef TriMesh_h
#define TriMesh_h 1

#include "Point3D.h"

using std::vector;
using Clobscode::Point3D;

namespace Clobscode
{
	class TriMesh{
		
	public:
		TriMesh();
		
		virtual ~TriMesh();
		
		virtual vector<Point3D> &getPoints();
		
		virtual vector<vector<unsigned int> > &getFaces();
		
		virtual vector<double> &getBounds();
		
		virtual void setPoints(vector<Point3D> &pv, vector<double> &bounds);
		
		virtual void setFaces(vector<vector<unsigned int> > &fv);
		
		virtual void computeBounds();
		
	protected:
		
		virtual void toCube(double per);
		
	protected:
		
		vector<Point3D> points;
		vector<vector<unsigned int> > faces;
		vector<double> bounds;
		
	};
	
	inline vector<Point3D> &TriMesh::getPoints(){
		return points;
	}
	
	inline vector<double> &TriMesh::getBounds(){
		return bounds;
	}
	
	inline vector<vector<unsigned int> > &TriMesh::getFaces(){
		return faces;
	}
	
	inline void TriMesh::setPoints(vector<Point3D> &pts, 
								   vector<double> &bounds){
		points=pts;
		this->bounds = bounds;
	}
	
	inline void TriMesh::setFaces(vector<vector<unsigned int> > &fv){
		faces=fv;
	}
}
#endif
