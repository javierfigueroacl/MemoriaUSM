#include "stdafx.h"
#include "Mesher.h"
#include <limits>

namespace Clobscode
{
	//-----------------------------------------------------
	//-----------------------------------------------------
	Mesher::Mesher(const unsigned int &nm){
		n_meshes = nm;
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	Mesher::~Mesher(){
		
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	//Create a grid mesh and split its largest edge 2^rl times 
	//(where rl stands for Refinement Level). The bounding box
	//is computed from input TriMesh
	FEMesh Mesher::generateMesh( void * pClientData, 
								PTRFUN_POINT_IN_MESH pClientPointTestFunc,
								PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc,
								std::vector<Clobscode::TriMesh> &inputs,
								int rl){
		
		//compute input mesh exact bounds
		inputs[0].computeBounds();
		vector<double> bounds = inputs[0].getBounds();
		for (unsigned int i =1; i<inputs.size(); i++) {
			inputs[i].computeBounds();
			vector<double> c_bounds = inputs[i].getBounds();
			for (unsigned int j=0; j<3; j++) {
				if (bounds[j]>c_bounds[j]) {
					bounds[j] = c_bounds[j];
				}
			}
			for (unsigned int j=3; j<6; j++) {
				if (bounds[j]<c_bounds[j]) {
					bounds[j] = c_bounds[j];
				}
			}
		}
		//refine process
		generateGridMesh(rl,bounds);
		
		//all generate methods apply the same methods at this
		//point, so the rest of the algorithm is ecapsulated
		//in the following function
		return generateMesh(pClientData,pClientPointTestFunc,
							pClientPointProjectorFunc);
	}

	
	//-----------------------------------------------------
	//-----------------------------------------------------	
	
	//Create a grid mesh and split its largest edge 2^rl times 
	//(where rl stands for Refinement Level). The bounding box
	//is received as a parameter
	FEMesh Mesher::generateMesh( void * pClientData, 
								PTRFUN_POINT_IN_MESH pClientPointTestFunc,
								PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc,
								vector<double> &bounds,
								int rl){
		
		//refine process
		generateGridMesh(rl,bounds);
		
		//all generate methods apply the same methods at this
		//point, so the rest of the algorithm is ecapsulated
		//in the following function
		return generateMesh(pClientData,pClientPointTestFunc,
							pClientPointProjectorFunc);
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	//generate a grid (it may not be regular) using given double
	//vectors for each axis. Note: it is assumed that min and max
	//coordinates for each axis in the vectors are outside the
	//input domain. pGridXs[0]=min_x and pGridXs[n-1]=max_x
	FEMesh Mesher::generateMesh( void * pClientData, 
								PTRFUN_POINT_IN_MESH pClientPointTestFunc,
								PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc,
								vector<double> & pGridXs, 
								vector<double> & pGridYs,
								vector<double> & pGridZs){
		
		//refine process
		GridMesher gm (n_meshes);
		gm.generateMesh(pGridXs,pGridYs,pGridZs,points,elements);
		//compute maxdistance for each element
		for (unsigned int i=0; i<elements.size(); i++) {
			elements[i].computeMaxDistance(points);
		}
		
		//all generate methods apply the same methods at this
		//point, so the rest of the algorithm is ecapsulated
		//in the following function		
		return generateMesh(pClientData,pClientPointTestFunc,
							pClientPointProjectorFunc);
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	FEMesh Mesher::generateMesh(void * pClientData, 
								PTRFUN_POINT_IN_MESH pClientPointTestFunc,
								PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc){

		//the almighty output mesh
		FEMesh mesh;
		
		//label nodes and elements, then remove outside elements
		labelNodesAndElements(pClientData,pClientPointTestFunc);
		
		//move close to boundary octants (hexas at this stage)
		//that are close to be outside the overall input
		linkElementsToNodes();
		projectCloseToOutsideBoundaryNodes(pClientData,pClientPointProjectorFunc);
		detectSurfaceElements();
		removeOnSurface();
		
		//move close to boundary octants (hexas at this stage)
		//that rely inside the overall geometry, but are close
		//to an intern feature
		projectCloseToInsideBoundaryNodes(pClientData,pClientPointProjectorFunc);
		
		//apply the surface Templates
		applySurfaceTemplates(pClientData,pClientPointTestFunc);
		
		//apply boundary templates to well represent inner surfaces
		applyBoundaryTemplates(pClientData,pClientPointTestFunc);
		
		//move close to boundary octants (mixed-elements at this stage)
		detectSurfaceElements();
		removeOnSurface();
		
		//project nodes of the boundary elements into the surface
		linkElementsToNodes();
		shrinkToBoundary(pClientData,pClientPointProjectorFunc);
		 
		 
		//save the data of the mesh*/
		saveOutputMesh(mesh);
		//save outside nodes in mdl file.
		//writeOutsideNodes(mesh,pClientData,pClientPointTestFunc);
		writeOutsideNodes(mesh,pClientData,pClientPointTestFunc);
		//return final mesh
		
		//Debugging
		//debugging(pClientData,pClientPointTestFunc);
		
		
		return mesh;
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::saveOutputMesh(FEMesh &mesh){
		vector<Point3D> out_pts;
		vector<vector<unsigned int> > out_els;
		
		unsigned int n = points.size();
		out_pts.reserve(n);
		for (unsigned int i=0; i<n; i++) {
			out_pts.push_back(points[i].getPoint());
		}
		n = elements.size();
		out_els.reserve(n);
		for (unsigned int i=0; i<n; i++) {
			//if (elements[i].isInside())
			//if(elements[i].insideBorder(points))
				out_els.push_back(elements[i].getPoints());
		}
		mesh.setPoints(out_pts);
		mesh.setElements(out_els);
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::generateGridMesh(int rl, vector<double> &bounds){
		//vectors with each coordinate per axis
		vector<double> all_x, all_y, all_z;
		
		GridMesher gm (n_meshes);
		gm.generatePoints(bounds,all_x,all_y,all_z,rl);
		gm.generateMesh(all_x,all_y,all_z,points,elements);
		
		//maxdistance is used to push out inner elements. If the
		//distance of an inner node to the surface is less than
		//maxdistance, then the node is moved. This is to avoid
		//extremely distorted elements.
		if (elements.empty()) {
			return;
		}
		vector<unsigned int> pts = elements[0].getPoints();
		Point3D p1 = points.at(pts[0]).getPoint();
		Point3D p2 = points.at(pts[1]).getPoint();
		double maxdistance = (p1-p2).Norm();
		maxdistance *= 0.3;
		for (unsigned int i=0; i<elements.size(); i++) {
			elements[i].setMaxDistance(maxdistance);
		}
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::labelNodesAndElements(void * pClientData, 
									   PTRFUN_POINT_IN_MESH pClientPointTestFunc){
		
		//check status of all points in the mesh.
		unsigned int n = points.size();
		for(unsigned int i=0; i<n; i++) {
			Point3D p =points.at(i).getPoint();
			
			//-----------------------------------------------------
			//-----------------------------------------------------
			for (unsigned int j=0; j<n_meshes; j++) {
				if (pClientPointTestFunc( pClientData, p,j)) {
					points.at(i).setInside(j);
				}
			}
			//-----------------------------------------------------
			//-----------------------------------------------------
			
			
			points.at(i).outsideChecked();
		}
		
		list<EnhancedElement> newele,removed;
		list<EnhancedElement>::iterator eiter;
		
		//check status of all elements in the mesh per input surface
		n = elements.size();
		
		for (unsigned int i=0; i<n; i++) {
			//test element intersection with all input surfaces.
			//add it only once.
			bool to_add = false;
			
			//std::cout << "e" << elements[i] << " :";
			
			for (unsigned int j=0; j<n_meshes; j++) {
				bool allinside = true;
				bool alloutside = true;
				vector<unsigned int> epts = elements[i].getPoints();
				unsigned int enp = epts.size();
				for(unsigned int k=0; k<enp; k++) {
					//std::cout << " " << points.at(epts[k]).getIOState(j);
					
					
					if (points.at(epts[k]).getIOState(j)) {
						alloutside = false;
					}
					else {
						allinside = false;
					}	
				}
				if (!alloutside) {
					//assign intersection state per input surface
					if (!allinside) {
						elements[i].setBorderState(j,true);
					}
					else {
						elements[i].setBorderState(j,false);
					}
					to_add = true;
				}
			}
			
			//std::cout << "\n";
			
			//if element was not added by any input surface, then
			//the element is completely outside.
			if (to_add) {
				newele.push_back(elements[i]);
			}
			else {
				removed.push_back(elements[i]);
			}					 
		}
		
		//clear removed elements
		removed.clear();
		//now element std::list from Vomule mesh can be cleared, as all remaining
		//elements are still in use and attached to newele std::list.
		elements.clear();
		for (eiter = newele.begin(); eiter!=newele.end(); eiter++) {
			elements.push_back(*eiter);
		}
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::linkElementsToNodes(){
		//clear previous information
		for (unsigned int i=0; i<points.size(); i++) {
			points.at(i).clearElements();
		}
		
		//link element info to nodes
		for (unsigned int i=0; i<elements.size(); i++) {
			vector<unsigned int> epts = elements[i].getPoints();
			for (unsigned int j=0; j<epts.size(); j++) {
				points.at(epts[j]).addElement(i);
			}
		}
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::detectSurfaceElements(){
		for (unsigned int i=0; i<elements.size(); i++) {
			if (elements[i].isInside()) {
				continue;
			}
			vector<unsigned int> epts = elements[i].getPoints();
			for (unsigned int j=0; j<n_meshes; j++) {
				for (unsigned int k=0; k<epts.size(); k++) {
					if (!points.at(epts[k]).getIOState(j)){
						elements[i].setBorderState(j,true);
						break;
					}	
				}
			}
		}
		
	}

	//-----------------------------------------------------
	//-----------------------------------------------------
	void Mesher::projectCloseToInsideBoundaryNodes(void * pClientData, 
											 PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc){
		
		//project close to boundary nodes of elements that present
		//nodes inside the overall geometry, but are close to an intern
		//feature
		
		std::list<unsigned int> in_nodes;
		
		for (unsigned int i=0; i< elements.size(); i++) {
			if (elements[i].insideBorder(points)) {
				
				//Put in a std::list inside nodes of boundary elements that
				//may be projected to the input domain.
				vector<unsigned int> epts = elements[i].getPoints();
				for (unsigned int j=0; j < epts.size(); j++) {
					if (points.at(epts[j]).isInside()) {
						//set max distance for node
						points[epts[j]].setMaxDistance(elements[i].getMaxDistance());
						in_nodes.push_back(epts[j]);
					}
				}
			}
		}
		in_nodes.sort();
		in_nodes.unique();
		
		//move (when possible) all inner points to surface
		std::list<unsigned int>::iterator piter;
		for (piter=in_nodes.begin(); piter!=in_nodes.end(); piter++) {
			
			Point3D current = points.at(*piter).getPoint();
			
			double min_dis = std::numeric_limits<double>::max();
			
			unsigned int surf_to_project;
			bool one_found = false;
			Point3D projected_result;
			
			//-----------------------------------------------------
			//-----------------------------------------------------
			for (unsigned int i=0; i<n_meshes; i++) {
				Point3D projected = pClientPointProjectorFunc( pClientData, current, i);
				double dis = (current - projected).Norm();
				
				//-----------------------------------------------------
				//-----------------------------------------------------
				
				
				if((dis<points[*piter].getMaxDistance()) && (min_dis>dis)){
					//this node have been moved to boundary, thus every element
					//sharing this node must be set as a border element in order
					//to avoid topological problems.
					one_found = true;
					surf_to_project = i;
					min_dis = dis;
					projected_result = projected;
				}
			}
			if (one_found) {
				points.at(*piter).setOutside(surf_to_project);
				points.at(*piter).setPoint(projected_result);
				vector<unsigned int> pele = points.at(*piter).getElements();
				//each element having node *piter should be checked
				//over intersection state with surface surf_to_project
				for (unsigned int i=0; i<pele.size(); i++) {
					vector<unsigned int> pele_pts = elements[i].getPoints();
					bool allinside = true;
					bool alloutside = true;
					for (unsigned int j=0; j<pele_pts.size(); j++) {

						if (points.at(pele_pts[j]).getIOState(surf_to_project)) {
							alloutside = false;
						}
						else {
							allinside = false;
						}	
					}
					if (!alloutside) {
						//assign intersection state per input surface
						if (!allinside) {
							elements[pele[i]].setBorderState(surf_to_project,true);
						}
						else {
							elements[pele[i]].setBorderState(surf_to_project,false);
						}
					}
					else {
						elements[pele[i]].setBorderState(surf_to_project,false);
					}
				}
			}
		}
		
	}
	
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	void Mesher::projectCloseToOutsideBoundaryNodes(void * pClientData, 
											 PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc){
		
		//Slow element removed (but works): from elements intersecting the
		//input domain, detect inner nodes. Project this nodes onto the
		//surface. If after all is done, if an element counts only with "on 
		//surface" and "outside" nodes, remove it.
		
		//project close to boundary nodes of elements that present
		//nodes outside the overall geometry
		std::list<unsigned int> in_nodes;
		
		for (unsigned int i=0; i< elements.size(); i++) {
			if (elements[i].outsideBorder(points)) {
				
				//Put in a std::list inside nodes of boundary elements that
				//may be projected to the input domain.
				vector<unsigned int> epts = elements[i].getPoints();
				for (unsigned int j=0; j < epts.size(); j++) {
					if (points.at(epts[j]).isInside()) {
						//set max distance for node
						points[epts[j]].setMaxDistance(elements[i].getMaxDistance());
						in_nodes.push_back(epts[j]);
					}
				}
			}
		}
		in_nodes.sort();
		in_nodes.unique();
		
		//move (when possible) all inner points to surface
		std::list<unsigned int>::iterator piter;
		for (piter=in_nodes.begin(); piter!=in_nodes.end(); piter++) {
			
			Point3D current = points.at(*piter).getPoint();
			
			double min_dis = std::numeric_limits<double>::max();
			
			unsigned int surf_to_project;
			bool one_found = false;
			Point3D projected_result;
			
			//-----------------------------------------------------
			//-----------------------------------------------------
			for (unsigned int i=0; i<n_meshes; i++) {
				Point3D projected = pClientPointProjectorFunc( pClientData, current, i);
				double dis = (current - projected).Norm();
			
			//-----------------------------------------------------
			//-----------------------------------------------------
			
			
				if((dis<points[*piter].getMaxDistance()) && (min_dis>dis)){
					//this node have been moved to boundary, thus every element
					//sharing this node must be set as a border element in order
					//to avoid topological problems.
					one_found = true;
					surf_to_project = i;
					min_dis = dis;
					projected_result = projected;
				}
			}
			if (one_found) {
				points.at(*piter).setOutside(surf_to_project);
				points.at(*piter).setPoint(projected_result);
				vector<unsigned int> pele = points.at(*piter).getElements();
				
				for (unsigned int i=0; i<pele.size(); i++) {
					elements[pele[i]].setBorderState(surf_to_project,true);
				}
			}
		}
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::removeOnSurface(){
		
		list<EnhancedElement> newele,removed;
		list<EnhancedElement>::iterator eiter;
		//remove elements without an inside node.
		for (unsigned int i=0; i<elements.size(); i++) {
			if (elements[i].outsideBorder(points)) {
				bool onein = false;
				vector<unsigned int> epts = elements[i].getPoints();
				for (unsigned int j=0; j< epts.size(); j++) {
					if (points.at(epts[j]).isInside()) {
						onein = true;
						break;
					}
				}
				if (onein) {
					newele.push_back(elements[i]);
				}
				else {
					removed.push_back(elements[i]);
				}
			}
			else {
				newele.push_back(elements[i]);
			}
			
		}
		//std:cout << "Elements removed: " << removed.size() << "\n";
		
		//clear removed elements
		removed.clear();
		//now element std::list from Vomule mesh can be cleared, as all remaining
		//elements are still in use and attached to newele std::list.
		elements.clear();
		for (eiter = newele.begin(); eiter!=newele.end(); eiter++) {
			elements.push_back(*eiter);
		}
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::applySurfaceTemplates(void * pClientData, 
									  PTRFUN_POINT_IN_MESH pClientPointTestFunc){
		//apply patters to avoid flat, invalid and
		//poor quality elementsñ.
		list<EnhancedElement> newele,removed,tmpele;
		list<EnhancedElement>::iterator eiter;
		list<MeshPoint> tmppts;
		list<MeshPoint>::iterator piter;
		
		for (unsigned int i=0; i<elements.size(); i++) {
			if (!elements[i].outsideBorder(points)) {
				newele.push_back(elements[i]);
				continue;
			}
			
			vector<vector<unsigned int> > replace;
			double old_md = elements[i].getMaxDistance();
			
			if (!elements[i].applySurfaceTemplates(points,tmppts,replace)) {
					newele.push_back(elements[i]);
					continue;
			}
			else {
				removed.push_back(elements[i]);	
			}
			
			for (unsigned int j=0; j<replace.size(); j++) {
				EnhancedElement ee(replace[j],n_meshes);
				ee.setMaxDistance(old_md);
				tmpele.push_back(ee);
			}
		}
		
		//check in/out state of new inserted nodes.
		if (!tmppts.empty()) {
			unsigned int npts = points.size()+tmppts.size();
			points.reserve(npts);
			for (piter=tmppts.begin(); piter!=tmppts.end(); piter++) {
				
				//-----------------------------------------------------
				//-----------------------------------------------------
				for (unsigned int i=0; i<n_meshes; i++) {
					if (pClientPointTestFunc( pClientData, (*piter).getPoint(),i)) {
						(*piter).setInside(i);
					}
				}
				//-----------------------------------------------------
				//-----------------------------------------------------
				
				
				(*piter).outsideChecked();
				points.push_back(*piter);
			}
		}
		
		//check in/out/border state of new elements		
		for (eiter=tmpele.begin(); eiter!=tmpele.end(); eiter++) {

			//test element intersection with all input surfaces.
			//add it only once.
			bool added = false;
			
			for (unsigned int i=0; i<n_meshes; i++) {
				vector<unsigned int> nee_pts = (*eiter).getPoints();
				bool allinside = true;
				bool outside = true;
				for (unsigned int j=0; j<(int)nee_pts.size(); j++) {
					if (!points.at(nee_pts[j]).wasOutsideChecked()) {
						cout << "wtf!!!\n";
					}
					if (points.at(nee_pts[j]).getIOState(i)) {
						outside = false;
					}
					else {
						allinside = false;
					}
				}
				if (!outside) {
					if (!allinside) {
						(*eiter).setBorderState(i,true);
					}
					else {
						(*eiter).setBorderState(i,false);
					}

					if (!added) {
						added = true;
						newele.push_back(*eiter);
					}
				}
			}
			if (!added) {
				removed.push_back(*eiter);
			}
		}
		//clear removed elements
		removed.clear();
		//now element std::list from Vomule mesh can be cleared, as all remaining
		//elements are still in use and attached to newele std::list.
		elements.clear();
		for (eiter = newele.begin(); eiter!=newele.end(); eiter++) {
			elements.push_back(*eiter);
		}
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	void Mesher::applyBoundaryTemplates(void * pClientData, 
									   PTRFUN_POINT_IN_MESH pClientPointTestFunc){
		//apply patters to avoid flat, invalid and
		//poor quality elementsñ.
		list<EnhancedElement> newele,removed,tmpele;
		list<EnhancedElement>::iterator eiter;
		list<MeshPoint> tmppts;
		list<MeshPoint>::iterator piter;
		list<unsigned int> in_to_check;
		list<unsigned int>::iterator e_in_iter;

		//////////////////////////////////////////////////////////////////////
		// fix problem with surface pattern neightborhood with boundary patterns
		vector <EnhancedElement> tmp_elements;
		vector < vector <unsigned int> > conflicting_elements;
		// Llenar vector octantes
		for (unsigned int i=0; i<elements.size(); i++) {
			tmp_elements.push_back(elements[i]);
		}
		// Recorrer vector octantes
		for(unsigned int i=0; i<tmp_elements.size();i++){
			vector <unsigned int> points_ele = tmp_elements[i].getPoints();

			if (points_ele.size() == 5){
				conflicting_elements.push_back(points_ele);
			
			}
		}
		//Debugging
		for(unsigned int i=0; i<conflicting_elements.size();i++){
			vector <Point3D> elepts;
			for(unsigned int k=0; k<conflicting_elements[i].size();k++){
				elepts.push_back(points.at(conflicting_elements[i][k]).getPoint());
			}
			cout <<" --------------------- \n";
			//print puntos
			for (unsigned int j=0; j < elepts.size(); j++)
				cout << elepts[j] << " <- punto xyz \n";
				cout <<" --------------------- \n";
		}
		//////////////////////////////////////////////////////////////////////////////////
		
		for (unsigned int i=0; i<elements.size(); i++) {
			
			if (!elements[i].insideBorder(points)) {
				newele.push_back(elements[i]);
				continue;
			}
			
			bool found = false;
			unsigned int intersected_surf;
			for (unsigned int j=0; j<n_meshes; j++) {
				if (elements[i].getBorderState(j)) {
					intersected_surf = j;
					found = true;
					break;
				}
			}
			
			if (!found) {
				std::cout << "Warning in Mesher::applyBoundaryTemplates :";
				std::cout << " element doesn't intersect inner surface\n";
				newele.push_back(elements[i]);
				continue;
			}
			
			vector<vector<unsigned int> > replace, newinside;
			double old_md = elements[i].getMaxDistance();
			
			/*Important note: the applyBoundary function is currently considering*/
			
			// agregado conflicting_elements como parametro
			if (!elements[i].applyBoundaryTemplates(points,tmppts,replace,newinside,intersected_surf,conflicting_elements)) {
				newele.push_back(elements[i]);
				continue;
			}
			else {
				removed.push_back(elements[i]);
			}
			//new elements intersecting the input surface
			for (unsigned int j=0; j<replace.size(); j++) {
				EnhancedElement ee(replace[j],n_meshes);
				ee.setMaxDistance(old_md);
				tmpele.push_back(ee);
			}
			//new elements that do not intersect the new surface:
			//they are directly inserted to newele list.
			for (unsigned int j=0; j<newinside.size(); j++) {
				EnhancedElement ee(newinside[j],n_meshes);
				ee.setMaxDistance(old_md);
				in_to_check.push_back(newele.size());
				//std::cout << "inserting element " << newele.size() << " ";
				//std::cout << ee << "\n";
				newele.push_back(ee);
			}
		}
		
		//check in/out state of new inserted nodes.
		if (!tmppts.empty()) {
			unsigned int npts = points.size()+tmppts.size();
			points.reserve(npts);
			for (piter=tmppts.begin(); piter!=tmppts.end(); piter++) {
				
				//-----------------------------------------------------
				//-----------------------------------------------------
				for (unsigned int i=0; i<n_meshes; i++) {
					if (pClientPointTestFunc( pClientData, (*piter).getPoint(),i)) {
						(*piter).setInside(i);
					}
				}
				//-----------------------------------------------------
				//-----------------------------------------------------
				
				
				(*piter).outsideChecked();
				points.push_back(*piter);
			}
		}
		
		//check in/out/border state of new elements		
		for (eiter=tmpele.begin(); eiter!=tmpele.end(); eiter++) {
			
			//test element intersection with all input surfaces.
			//add it only once.
			bool added = false;
			
			for (unsigned int i=0; i<n_meshes; i++) {
				vector<unsigned int> nee_pts = (*eiter).getPoints();
				bool allinside = true;
				bool outside = true;
				for (unsigned int j=0; j<nee_pts.size(); j++) {
					if (!points.at(nee_pts[j]).wasOutsideChecked()) {
						cout << "wtf!!!\n";
					}
					if (points.at(nee_pts[j]).getIOState(i)) {
						outside = false;
					}
					else {
						allinside = false;
					}
				}
				if (!outside) {
					if (!allinside) {
						(*eiter).setBorderState(i,true);
					}
					else {
						(*eiter).setBorderState(i,false);
					}
					
					if (!added) {
						added = true;
						newele.push_back(*eiter);
					}
				}
			}
			if (!added) {
				removed.push_back(*eiter);
			}
		}
		//clear removed elements
		removed.clear();
		//now element std::list from Vomule mesh can be cleared, as all remaining
		//elements are still in use and attached to newele std::list.
		elements.clear();
		for (eiter = newele.begin(); eiter!=newele.end(); eiter++) {
			elements.push_back(*eiter);
		}
		
		
		//check intersection state for each new element that do not
		//intersects the inner surface "instersected_surf"
		for (e_in_iter=in_to_check.begin(); e_in_iter!=in_to_check.end(); e_in_iter++) {
			
			for (unsigned int i=0; i<n_meshes; i++) {
				
				bool allinside = true;
				bool outside = true;
				vector<unsigned int> epts = elements[*e_in_iter].getPoints();
				
				for (unsigned int j=0; j<epts.size(); j++) {
					if (!points.at(epts[j]).wasOutsideChecked()) {
						cout << "wtf!!!\n";
					}
					if (points.at(epts[j]).getIOState(i)) {
						outside = false;
					}
					else {
						allinside = false;
					}
				}
				if (!outside) {
					if (!allinside) {
						elements[*e_in_iter].setBorderState(i,true);
					}
					else {
						elements[*e_in_iter].setBorderState(i,false);
					}
				}
			}
		}		
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	//shrink elements intersecting the envelope defined by all
	//input surfaces
	void Mesher::shrinkToBoundary(void * pClientData, 
								  PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc){
		
		
		//From the list of elements intersecting any input mesh
		//select the nodes to be projected, i.e., the nodes that
		//are outside an input mesh
		list<unsigned int> out_nodes;
		for (unsigned int i=0; i<elements.size(); i++) {
			if (!elements[i].outsideBorder(points)) {
				continue;
			}
			vector<unsigned int> epts = elements[i].getPoints();
			for (unsigned int j=0; j<epts.size(); j++) {
				if (points[epts[j]].isOutside()) {
					out_nodes.push_back(epts[j]);
				}
			}
		}
		
		out_nodes.sort();
		out_nodes.unique();
		
		//project all outside nodes into the surface
		list<unsigned int>::iterator piter;
		
		for (piter=out_nodes.begin(); piter!=out_nodes.end(); piter++) {
			Point3D current = points.at(*piter).getPoint();
			
			double min_dis = std::numeric_limits<double>::max();
			
			//-----------------------------------------------------
			//-----------------------------------------------------
			for (unsigned int i=0; i<n_meshes; i++) {
				Point3D projected = pClientPointProjectorFunc( pClientData, current, i);
				double dis = (current - projected).Norm();
				
				//-----------------------------------------------------
				//-----------------------------------------------------
				
				
				if(min_dis>dis){
					//this node have been moved to boundary, thus every element
					//sharing this node must be set as a border element in order
					//to avoid topological problems.
					min_dis = dis;
					points.at(*piter).setOutside(i);
					points.at(*piter).setPoint(projected);
					vector<unsigned int> pele = points.at(*piter).getElements();
					for (unsigned int j=0; j<pele.size(); j++) {
						elements[pele[j]].setBorderState(i,true);
					}
				}
			}
		}
	}
	
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	
	//wirte outside nodes to project them with registration
	void Mesher::writeOutsideNodes(FEMesh &mesh, void * pClientData, 
								   PTRFUN_POINT_IN_MESH pClientPointTestFunc){
		
		list<unsigned int> outside;
		
		for (unsigned int i=0; i<elements.size(); i++) {
			//if the element does not intersect the domain,
			//then continue
			if (!elements.at(i).outsideBorder(points)) {
				continue;
			}
			
			vector<unsigned int> epts = elements[i].getPoints();
			for (unsigned int j=0; j<epts.size(); j++) {
				if (!points.at(epts[j]).wasOutsideChecked()) {
					Point3D p =points.at(epts[j]).getPoint();
					
					
					//-----------------------------------------------------
					//-----------------------------------------------------
					
					for (unsigned int k=0; k<n_meshes; k++) {
						if (pClientPointTestFunc( pClientData, p, k)) {
							points.at(epts[j]).setInside(k);
						}
					}
					//-----------------------------------------------------
					//-----------------------------------------------------
					
					points.at(epts[j]).outsideChecked();
				}
				if (points.at(epts[j]).isOutside()) {
					outside.push_back(epts[j]);
				}
			}
		}
		outside.sort();
		outside.unique();
		
		mesh.setOutsideNodes(outside);
	}
	
	//wirte all inside nodes for testing
	void Mesher::writeInsideNodes(FEMesh &mesh, void * pClientData, 
								  PTRFUN_POINT_IN_MESH pClientPointTestFunc){
		
		list<unsigned int> inside_only;
		
		for (unsigned int i=0; i<points.size(); i++) {
			//if the element does not intersect the domain,
			//then continue
			if (!points.at(i).wasOutsideChecked()) {
				Point3D p =points.at(i).getPoint();
				
				//-----------------------------------------------------
				//-----------------------------------------------------
				for (unsigned int j=0; j<n_meshes; j++) {
					if (pClientPointTestFunc( pClientData, p,j)) {
						points.at(i).setInside(j);
					}
				}
				//-----------------------------------------------------
				//-----------------------------------------------------
				
				points.at(i).outsideChecked();
			}
			if (points.at(i).isInside()) {
				inside_only.push_back(i);
			}
		}
		inside_only.sort();
		inside_only.unique();
		
		mesh.setOutsideNodes(inside_only);
	}
	
	
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	// Start debugging
	//-----------------------------------------------------
	//-----------------------------------------------------

	void Mesher::debugging(void * pClientData, 
						   PTRFUN_POINT_IN_MESH pClientPointTestFunc){
		vector<Point3D> deb_pts;
		deb_pts.reserve(4);
		Point3D p1(-4.2,0.8,4.3), p2(-3.7,0.8,3.8), p3(-3.7,0.8,4.3), p4(-3.7,1.3,4.3);
		deb_pts.push_back(p1);
		deb_pts.push_back(p2);
		deb_pts.push_back(p3);
		deb_pts.push_back(p4);
		
		unsigned int ele_idx;
		for (unsigned int i=0; i<elements.size(); i++) {
			bool e_found = true;
			for (unsigned int j=0; j<4; j++) {
				vector<unsigned int> epts = elements[i].getPoints();
				bool p_found = false;
				for (unsigned int k=0; k<epts.size(); k++) {
					Point3D ep = points[epts[k]].getPoint();
					if (ep == deb_pts[j]) {
						p_found = true;
						break;
					}
				}
				if (!p_found) {
					e_found = false;
					break;
				}
			}
			if (e_found) {
				ele_idx = i;
				break;
			}
		}
		
		std::cout << "Element found! Index: " << ele_idx << "\n";
		
		vector<unsigned int> bug_e_pts = elements[ele_idx].getPoints();
		for (unsigned int i=0; i<bug_e_pts.size(); i++) {
			Point3D p =points.at(bug_e_pts[i]).getPoint();
			std::cout << "point " << p << " is ";
			
			
			//-----------------------------------------------------
			//-----------------------------------------------------
			if (pClientPointTestFunc( pClientData, p, 0)) {
				std::cout << "in\n";
			}
			//-----------------------------------------------------
			//-----------------------------------------------------
			
			else {
				std::cout << "out\n";
			}
			
		}
	}
	
	//-----------------------------------------------------
	//-----------------------------------------------------
	// End debugging
	//-----------------------------------------------------
	//-----------------------------------------------------
}
