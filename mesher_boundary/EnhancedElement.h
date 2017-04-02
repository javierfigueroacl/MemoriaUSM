#ifndef EnhancedElement_h
#define EnhancedElement_h 1

#include <iostream>
#include <vector>
#include <list>
#include "MeshPoint.h"
#include "BoundaryTemplate1.h"
#include "BoundaryTemplate2.h"
#include "BoundaryTemplate3.h"
#include "BoundaryTemplate4.h"
#include "BoundaryTemplate5.h"
#include "BoundaryTemplate6.h"
#include "BoundaryTemplate7.h"
#include "BoundaryTemplatePyramid.h"
#include "BoundaryTemplatePrism.h"
#include "SurfTemplate1.h"
#include "SurfTemplate2.h"
#include "SurfTemplate3.h"
#include "SurfTemplate4.h"
#include "SurfTemplate5.h"
#include "SurfTemplate6.h"
#include "SurfTemplate7.h"


using Clobscode::MeshPoint;
using std::vector;
using std::list;

namespace Clobscode
{
	
	
	class EnhancedElement{
		
	public:
		
		EnhancedElement(vector<unsigned int> &epts, unsigned int n_meshes);
		
		virtual ~EnhancedElement();
		
		//important methods 		
		virtual bool applySurfaceTemplates(vector<MeshPoint> &meshpoints,
										   list<MeshPoint> &newpts,
										   vector<vector<unsigned int> > &newsub);
		
		virtual bool applyBoundaryTemplates(vector<MeshPoint> &meshpoints,
											list<MeshPoint> &newpts,
											vector<vector<unsigned int> > &newsub,
											vector<vector<unsigned int> > &newsub_out,
											const unsigned int &intersects,
											vector<vector<unsigned int> > &py_elements_face);
		
		virtual void computeMaxDistance(vector<MeshPoint> &meshpoints);
		
		virtual void setMaxDistance(double md);
		
		virtual double getMaxDistance();
		
		//access methods
		virtual void setBorderState(unsigned int idx, bool state);
		
		virtual bool outsideBorder(vector<MeshPoint> &meshpoints);
		
		virtual bool getBorderState(unsigned int idx);
		
		virtual vector<unsigned int> &getPoints();
		
		virtual unsigned int detectIntersectingSurface(vector<MeshPoint> &meshpoints);
		
		virtual bool insideBorder(vector<MeshPoint> &meshpoints);
		
		virtual bool isInside();
		
	protected:
		
		vector<unsigned int> pointindex;
		//this double is used decide if an inner node
		//of this element should be projected onto the
		//input domain in order to not produce a flat
		//element. This is done in method 
		//Clobscode::Mesher::projectCloseToBoundaryNodes.
		double maxdistance;
		//position flags
		vector<bool> border;
		
	};
	
	inline bool EnhancedElement::getBorderState(unsigned int idx){
		return border.at(idx);
	}
	
	inline void EnhancedElement::setMaxDistance(double md){
		maxdistance = md;
	}
	
	inline double EnhancedElement::getMaxDistance(){
		return maxdistance;
	}
	
	inline void EnhancedElement::setBorderState(unsigned int idx, bool state){
		border.at(idx) = state;
	}
	
	inline vector<unsigned int> &EnhancedElement::getPoints(){
		return pointindex;
	}
	
	inline bool EnhancedElement::isInside(){
		for (unsigned int i=0; i<border.size(); i++) {
			if (border[i]) {
				return false;
			}
		}
		return true;
	}
	
	std::ostream& operator<<(ostream& o,EnhancedElement &e);
}
#endif
