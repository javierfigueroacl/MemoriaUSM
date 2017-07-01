#ifndef MeshPoint_h
#define MeshPoint_h 1

#include <iostream>
#include <math.h>
#include "Point3D.h"
#include <vector>
#include <list>

using Clobscode::Point3D;

namespace Clobscode
{	
	class MeshPoint{
		
	public:
		
		MeshPoint(const unsigned int &nm);
		
		MeshPoint(Point3D &p, const unsigned int &nm);
		
		virtual ~MeshPoint();
		
		virtual void setPoint(Point3D &p);
		
		//acces method:
		virtual Point3D &getPoint();
		
		virtual void addElement(unsigned int idx);
		
		virtual std::vector<unsigned int> &getElements();
		
		virtual void clearElements();
		
		virtual bool wasOutsideChecked();
		
		virtual void outsideChecked();
		
		virtual void setMaxDistance(double md);
		
		virtual double getMaxDistance();
		
		//state methods
		virtual void setOutside(const unsigned int &nm);
		
		virtual void setInside(const unsigned int &nm);
		
		//returns true if node is inside any input mesh
		virtual bool isInside();
		
		//returns true if node is outside every input mesh
		virtual bool isOutside();
		
		virtual void setIOState(const unsigned int &nm, bool state);
		
		virtual bool getIOState(const unsigned int &nm);
		
		//virtual void setNumberOfInputMeshes(const unsigned int &nm);
		
		virtual const unsigned int &getNumberOfInputMeshes();
		
	protected:
		
		Point3D point;
		//this flag avoids to re-check if node is inside, 
		//which is an expensive task
		bool outsidechecked;
		//inside is a flag to shrink elements to the surface.
		//it is a vector to know the state w.r.t. every input
		//geometry
		std::vector<bool> inside;
		std::vector<unsigned int> elements;
		//avoid asking every time the number of input surface with
		//in/out method states
		unsigned int n_meshes;
		
		double maxdistance;
		
	};
	
	inline const unsigned int &MeshPoint::getNumberOfInputMeshes(){
		return n_meshes;
	}
	
	/*inline void MeshPoint::setNumberOfInputMeshes(const unsigned int &nm){
		inside.reserve(nm);
	}*/
	
	inline void MeshPoint::outsideChecked(){
		outsidechecked = true;
	}
	
	inline bool MeshPoint::wasOutsideChecked(){
		return outsidechecked;
	}
	
	inline void MeshPoint::setMaxDistance(double md){
		if (md<maxdistance) {
			return;
		}
		maxdistance = md;
	}
	
	inline double MeshPoint::getMaxDistance(){
		return maxdistance;
	}
	
	inline void MeshPoint::setOutside(const unsigned int &nm){
		inside.at(nm) = false;
	}
	
	inline void MeshPoint::setInside(const unsigned int &nm){
		inside.at(nm) = true;
	}
	
	inline void MeshPoint::setIOState(const unsigned int &nm, bool state){
		inside.at(nm) = state;
	}
	
	inline bool MeshPoint::getIOState(const unsigned int &nm){
		return inside.at(nm);
	}
	
	//returns true if node is inside any input mesh
	inline bool MeshPoint::isInside(){
		for (unsigned int i=0; i<n_meshes; i++) {
			if (inside.at(i)) {
				return true;
			}
		}
		return false;
	}
	
	//returns true if node is outside every input mesh
	inline bool MeshPoint::isOutside(){
		for (unsigned int i=0; i<n_meshes; i++) {
			if (inside.at(i)) {
				return false;
			}
		}
		return true;
	}
	
	inline Point3D &MeshPoint::getPoint(){
		return point;
	}
	
	inline void MeshPoint::setPoint(Point3D &p){
		point = p;
	}
	
	inline void MeshPoint::addElement(unsigned int e){
		elements.push_back(e);
	}
	
	inline void MeshPoint::clearElements(){
		elements.clear();
	}
	
	inline std::vector<unsigned int> &MeshPoint::getElements(){
		return elements;
	}
	
	std::ostream& operator<<(std::ostream& o,MeshPoint &p);
	
}
#endif
