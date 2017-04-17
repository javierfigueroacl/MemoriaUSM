#include "stdafx.h"
#include "EnhancedElement.h"

namespace Clobscode
{
	EnhancedElement::EnhancedElement(vector<unsigned int> &epts, unsigned int n_meshes){
		border.assign(n_meshes,true);
		pointindex = epts;
		maxdistance = 0;
	}
	
	EnhancedElement::~EnhancedElement(){
		
	}
	
	//return true if SurfacePatterns succeded in replacing the hex element.
	bool EnhancedElement::applySurfaceTemplates(vector<MeshPoint> &meshpoints,
												list<MeshPoint> &newpts,
												vector<vector<unsigned int> > &newsub){	 
		
		//A surface template should be applyed only over elements
		//that intersect one surface or all of them. In both cases
		//at least one element node should be outside the sum of
		//input surfaces
		
		if(!outsideBorder(meshpoints)){
			return false;
		}
		
		
		
		std::vector<unsigned int> inpts, outpts;
		std::list<unsigned int> tmpin;
		std::list<unsigned int> tmpout;
		std::list<unsigned int>::iterator piter;
		
		
		for (unsigned int i=0; i<pointindex.size(); i++){
			if(meshpoints.at(pointindex[i]).isOutside())
				tmpout.push_back(i);
			else
				tmpin.push_back(i);
		}
		
		/*std::cout << "prev in " << tmpin.size() << " & out " << tmpout.size();
		//save the inner points in the std::list (local position
		//in the element array: 0 ... 7)
		
		tmpin.clear();
		tmpout.clear();
		
		for (unsigned int i=0; i<pointindex.size(); i++){
			if(meshpoints.at(pointindex[i]).isOutside()){
				tmpout.push_back(i);
			}
			else{
				bool inside_all = true;
				for (unsigned int j=0; j<border.size(); j++) {
					std::cout << " " << border[j];
					if (!border[j]) {
						continue;
					}
					if (!meshpoints.at(pointindex[i]).getIOState(j)) {
						inside_all = false;
						break;
					}
				}
				if (inside_all) {
					tmpin.push_back(i);
				}
				else {
					tmpout.push_back(i);
				}
			}
		}
		std::cout << " post in " << tmpin.size() << " & out " << tmpout.size() << "\n";
		 */
		//save the points in a std::vector for quick acces
		inpts.reserve(tmpin.size());
		for(piter=tmpin.begin();piter!=tmpin.end();piter++)
			inpts.push_back(*piter);
		outpts.reserve(tmpout.size());
		for(piter=tmpout.begin();piter!=tmpout.end();piter++)
			outpts.push_back(*piter);
				
		
		//select the patter to apply
		switch ((int)inpts.size()) {
			case 0:{
				/*If at this point, the element has 0 node inside,
				 it might be tangencial to input mesh, in which case
				 it should be invalid_elements, or represent a feature of
				 the domain (e.g. all nodes outside, but there is
				 something like a pipeline crossing it). This algorithm
				 isn't yet "future sensitive", therefore the element
				 is simply invalid_elements.
				 */
				return false;
			}
			case 1: {
				SurfTemplate1 surf_t1;
				return surf_t1.getSubelements(pointindex,inpts,newsub);
			}
			case 2: {
				SurfTemplate2 surf_t2;
				return surf_t2.getSubelements(pointindex,inpts,newsub);
			}
			case 3: {
				SurfTemplate3 surf_t3;
				return surf_t3.getSubelements(pointindex,inpts,newsub);
			}
			case 4: {
				SurfTemplate4 surf_t4;
				return surf_t4.getSubelements(pointindex,inpts,newsub);
			}
			case 5: {
				SurfTemplate5 surf_t5;
				return surf_t5.getSubelements(pointindex,inpts,meshpoints,
											  newpts,newsub);
			}
			case 6: {
				SurfTemplate6 surf_t6;
				return surf_t6.getSubelements(pointindex,outpts,newsub);
			}
			case 7: {
				SurfTemplate7 surf_t7;
				return surf_t7.getSubelements(pointindex,outpts,newsub);
			}
			case 8: {
				//If this happens the element is inside the overall
				//geometry, but intersects inner features.
				newsub.push_back(pointindex);
				break;
			}
			default: {
				cerr << " Error at EnhancedElement::applySurfacePatterns\n";
				cerr << " Number of inside nodes: " << inpts.size() << "\n";
				cerr << " Surface Patterns must be applied over elements";
				cerr << " with 1 to 7 inside nodes.\n";
				return false;
			}
		}
		
		return false;
	}
	
	
	//to be used with inner intersections. Returns true if method succeed.
	bool EnhancedElement::applyBoundaryTemplates(vector<MeshPoint> &meshpoints,
												 list<MeshPoint> &newpts,
												 vector<vector<unsigned int> > &newsub,
												 vector<vector<unsigned int> > &newsub_out,
												 vector<vector<unsigned int> > &invalid_elements,
												 const unsigned int &intersects,
										vector<vector<unsigned int> > &conflicting_elements
													){
		
		if(!insideBorder(meshpoints)){
			return false;
		}
		
		std::vector<unsigned int> inpts, outpts;
		std::list<unsigned int> tmpin;
		std::list<unsigned int> tmpout;
		std::list<unsigned int>::iterator piter;
		//save the inner points in the std::list (local position
		//in the element array: 0 ... 7)
		
		//Note: label as outside every node that is outside a given
		//input surface. Erase the parameter instersects. 
		
		for (unsigned int i=0; i<pointindex.size(); i++){
			if(meshpoints.at(pointindex[i]).getIOState(intersects))
				tmpin.push_back(i);
			else
				tmpout.push_back(i);
		}
		
		/*for (unsigned int i=0; i<pointindex.size(); i++){
			bool inside_all = true;
			for (unsigned int j=0; j<border.size(); j++) {
				//consider only input meshes this element intersect
				if (!border[j]) {
					continue;
				}
				if (!meshpoints.at(pointindex[i]).getIOState(j)) {
					inside_all = false;
				}
			}
			if (inside_all) {
				tmpin.push_back(i);
			}
			else {
				tmpout.push_back(i);
			}
		}*/
		
		//save the points in a std::vector for quick acces
		inpts.reserve(tmpin.size());
		for(piter=tmpin.begin();piter!=tmpin.end();piter++)
			inpts.push_back(*piter);
		outpts.reserve(tmpout.size());
		for(piter=tmpout.begin();piter!=tmpout.end();piter++)
			outpts.push_back(*piter);
		
		
		if (pointindex.size()==4) {
			newsub.push_back(pointindex);
			return true;
		}
		
		if (pointindex.size()==5) {
			BoundaryTemplatePyramid btpy;
			return btpy.getSubelements(pointindex,inpts,newsub,newsub_out);
		}
		
		if (pointindex.size()==6) {
			BoundaryTemplatePrism btpr;
			return btpr.getSubelements(pointindex,inpts,outpts,newsub,newsub_out);
		}
		
		//std::cout << "number of inside nodes for this element " << tmpin.size() << "\n";
		
		/*newsub.push_back(pointindex);
		 return true;*/
		
		
		//select the patter to apply
		switch ((int)inpts.size()) {
			case 0:{
				/*If at this point, the element has 0 node inside,
				 it might be tangencial to input mesh, in which case
				 it should be invalid_elements, or represent a feature of
				 the domain (e.g. all nodes outside, but there is
				 something like a pipeline crossing it). This algorithm
				 isn't yet "future sensitive", therefore the element
				 is simply invalid_elements.
				 */
				return false;
			}
			case 1: {
				//std::cout << "applying template 1\n";
				BoundaryTemplate1 boun_t1;
				return boun_t1.getSubelements(pointindex,inpts,meshpoints,newpts,newsub,newsub_out);
			}
			case 2: {
				//std::cout << "applying template 2\n";				
				BoundaryTemplate2 boun_t2;
				return boun_t2.getSubelements(pointindex,inpts,meshpoints,newpts,newsub,newsub_out,invalid_elements,conflicting_elements);
			}
			case 3: {
				//std::cout << "applying template 3\n";				
				BoundaryTemplate3 boun_t3;
				return boun_t3.getSubelements(pointindex,inpts,newsub,newsub_out);
			}
			case 4: {
				BoundaryTemplate4 boun_t4;
				return boun_t4.getSubelements(pointindex,inpts,newsub,newsub_out);
			}
			case 5: {
				BoundaryTemplate5 boun_t5;
				return boun_t5.getSubelements(pointindex,inpts,meshpoints,
											  newpts,newsub);
			}
			case 6: {
				BoundaryTemplate6 boun_t6;
				return boun_t6.getSubelements(pointindex,outpts,meshpoints,newsub,conflicting_elements);
			}
			case 7: {
				BoundaryTemplate7 boun_t7;
				return boun_t7.getSubelements(pointindex,outpts,newsub);
			}
			case 8: {
				//If this happens the element is inside the overall
				//geometry, but intersects inner features.
				newsub.push_back(pointindex);
				break;
			}
			default: {
				cerr << " Error at EnhancedElement::applySurfacePatterns\n";
				cerr << " Number of inside nodes: " << inpts.size() << "\n";
				cerr << " Surface Patterns must be applied over elements";
				cerr << " with 1 to 7 inside nodes.\n";
				return false;
			}
		}
		
		return false;
	}
	
	unsigned int EnhancedElement::detectIntersectingSurface(vector<MeshPoint> &meshpoints){
		const unsigned int n_meshes = meshpoints[pointindex[0]].getNumberOfInputMeshes();
		for (unsigned int i=0; i<pointindex.size(); i++) {
			for (unsigned int j=0; j<n_meshes; j++) {
				if (!meshpoints[pointindex[i]].getIOState(j)) {
					return j;
				}
			}
		}
		//this should never happen
		return 20;
	}
	
	bool EnhancedElement::insideBorder(vector<MeshPoint> &meshpoints){
		bool one_in = false;
		for (unsigned int i=0; i<border.size(); i++) {
			if (border[i]) {
				one_in = true;
				break;
			}
		}
		if (!one_in) {
			return false;
		}
		for (unsigned int i=0; i<pointindex.size(); i++) {
			if (meshpoints[pointindex[i]].isOutside()) {
				return false;
			}
		}
		
		return true;
	}
	
	bool EnhancedElement::outsideBorder(vector<MeshPoint> &meshpoints){
		//returns true if the element has at least one node
		//outside every input mesh
		bool one_in = false;
		for (unsigned int i=0; i<border.size(); i++) {
			if (border[i]) {
				one_in = true;
				break;
			}
		}
		if (!one_in) {
			return false;
		}
		
		//hard test: due to element intersects only one input surface,
		//check that all its nodes rely outside 
		for (unsigned int i=0; i<pointindex.size(); i++) {
			if (meshpoints[pointindex[i]].isOutside()) {
				return true;
			}
		}
		return false;
	}
	
	void EnhancedElement::computeMaxDistance(vector<MeshPoint> &meshpoints){
		Point3D p0 = meshpoints[pointindex[0]].getPoint();
		Point3D p1 = meshpoints[pointindex[1]].getPoint();
		Point3D p3 = meshpoints[pointindex[3]].getPoint();
		Point3D p4 = meshpoints[pointindex[4]].getPoint();
		double dx = (p3-p0).Norm();
		double dy = (p4-p0).Norm();
		double dz = (p1-p0).Norm();
		/*double min;
		 if (dx<dy && dx<dz) {
		 min = dx;
		 }
		 else {
		 if (dy<dz && dy<dx) {
		 min = dy;
		 }
		 else {
		 min = dz;
		 }
		 }*/
		double min;
		if (dx>dy && dx>dz) {
			min = dx;
		}
		else {
			if (dy>dz && dy>dx) {
				min = dy;
			}
			else {
				min = dz;
			}
		}
		maxdistance = min*0.3;
	}
	
	std::ostream& operator<<(std::ostream& o,EnhancedElement &e){
		std::vector<unsigned int> points = e.getPoints();
		for (unsigned int i=0; i<points.size(); i++)
			o << " " << points[i];
		/*o << " intersects: ";
		 if(e.isBorder()){
		 o << "yes";
		 }
		 else
		 o << "no";*/
		return o;
	}
}
