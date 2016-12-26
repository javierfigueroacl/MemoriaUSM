#ifndef FEMesh_h
#define FEMesh_h 1

#include <vector>
#include "Point3D.h"

using std::vector;

namespace Clobscode
{
	class FEMesh{
		
	public:
		
		FEMesh(){};
		
		virtual void setPoints(vector<Point3D> &pts);
		
		virtual void setElements(vector<vector<unsigned int> > &els);
		
		virtual void setOutsideNodes(list<unsigned int> &outpts);
		
		virtual vector<Point3D> &getPoints();
		
		virtual vector<vector<unsigned int> > &getElements();
		
		virtual list<unsigned int> &getOutsideNodes();
		
	protected:
		
		vector<Point3D> points;
		vector<vector<unsigned int> > elements;
		list<unsigned int> outpts;
		
	};
	
	inline void FEMesh::setOutsideNodes(list<unsigned int> &outpts){
		list<unsigned int>::iterator iter;
		for (iter=outpts.begin(); iter!=outpts.end(); iter++) {
			this->outpts.push_back(*iter);
		}
	}
	
	inline void FEMesh::setElements(vector<vector<unsigned int> > &els){
		unsigned int n = els.size();
		elements.reserve(n);
		for (unsigned int i=0; i<n; i++) {
			elements.push_back(els[i]);
		}
	}
	
	inline void FEMesh::setPoints(vector<Point3D> &pts){
		unsigned int n = pts.size();
		points.reserve(n);
		for (unsigned int i=0; i<n; i++) {
			points.push_back(pts[i]);
		}
	}
	
	inline vector<Point3D> &FEMesh::getPoints(){
		return points;
	}
	
	inline vector<vector<unsigned int> > &FEMesh::getElements(){
		return elements;
	}
	
	inline list<unsigned int> &FEMesh::getOutsideNodes(){
		return outpts;
	}
}
#endif
