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
												 const unsigned int &intersects
													){
		
		std::vector<unsigned int> inpts, outpts;
		std::list<unsigned int> tmpin;
		std::list<unsigned int> tmpout;
		std::list<unsigned int>::iterator piter;
		//save the inner points in the std::list (local position
		//in the element array: 0 ... 7)
		
		//Note: label as outside every node that is outside a given
		//input surface. Erase the parameter instersects. 
	
// Por Javier	
		for (unsigned int i=0; i<pointindex.size(); i++){
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
		}

// Fin Por Javier
		
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
		//Agregado por Javier
		if (pointindex.size()==5 or pointindex.size()==6) return false;
		
		//std::cout << "number of inside nodes for this element " << tmpin.size() << "\n";
		
		/*newsub.push_back(pointindex);
		 return true;*/
		
		
		//select the patter to apply
		switch ((int)inpts.size()) {
			case 0:{
				/*If at this point, the element has 0 node inside,
				 it might be tangencial to input mesh, in which case
				 it should be invalid, or represent a feature of
				 the domain (e.g. all nodes outside, but there is
				 something like a pipeline crossing it). This algorithm
				 isn't yet "future sensitive", therefore the element
				 is simply invalid.
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
				return boun_t2.getSubelements(pointindex,inpts,meshpoints,newpts,newsub,newsub_out);
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
				return boun_t6.getSubelements(pointindex,outpts,meshpoints,newsub,newsub_out);
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

	bool EnhancedElement::fixconflictingelements(vector <unsigned int> &points_ele,unsigned int &i,vector<MeshPoint> &points,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes){

			if (points_ele.size() == 5){
			//Antes de agregar, filtrar con IOState para obtener solo las piramides que compartiran cara con un patron interno
			int tnode=0,innode=0,outnode=0;
			for(unsigned int k=0; k<points_ele.size()-1;k++){
				unsigned int tintersects=0;

				for(unsigned int j=0;j<n_meshes;j++)
				if(points.at(points_ele[k]).getIOState(j) == true) tintersects++;

				if(tintersects == n_meshes){
				innode=k;
				tnode++;
				}
				else{
				outnode=k;
				}
			}
			vector<unsigned int> tetra1 (4,0);
			vector<unsigned int> tetra2 (4,0);

			if (tnode == 1){
				if (innode == 0 or innode == 2)
				fixpyrPatternA(points_ele,tmpele,old_md,n_meshes);
				else
				fixpyrPatternB(points_ele,tmpele,old_md,n_meshes);
				return true;

			}
			else if (tnode == 2){
				unsigned int stnode[4],okcon=0;

				for(unsigned int k=0; k<points_ele.size()-1;k++){
				unsigned int tintersects=0;

				for(unsigned int j=0;j<n_meshes;j++)
				if(points.at(points_ele[k]).getIOState(j) == true) tintersects++;

				if(tintersects == n_meshes){
				stnode[k]=1;
				}
				else{
				stnode[k]=0;
				}
				}

				if (stnode[0]==1 and stnode[2]==1){
				fixpyrPatternA(points_ele,tmpele,old_md,n_meshes);
				okcon=1;
				}
				else if (stnode[1]==1 and stnode[3]==1){
				fixpyrPatternB(points_ele,tmpele,old_md,n_meshes);
				okcon=1;
				}
				if (okcon==1)
				return true;

			}
			else if (tnode == 3){
				if (outnode == 1 or outnode == 3)
				fixpyrPatternA(points_ele,tmpele,old_md,n_meshes);
				else
				fixpyrPatternB(points_ele,tmpele,old_md,n_meshes);
				return true;
				}
			
			}

			else if (points_ele.size() == 6){
				unsigned int stnode[6],okcon=0,tnode1=0,tnode2=0,tnode=0;

				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> tetra3 (4,0);
				vector<unsigned int> tetra4 (4,0);
				vector<unsigned int> tetra5 (4,0);
				vector<unsigned int> tetra6 (4,0);
				vector<unsigned int> pyr (5,0);

				// label nodes
				for(unsigned int k=0; k<points_ele.size();k++){
				unsigned int tintersects=0;

				for(unsigned int j=0;j<n_meshes;j++)
				if(points.at(points_ele[k]).getIOState(j) == true) tintersects++;

				if(tintersects == n_meshes){
				stnode[k]=1;
				}
				else{
				stnode[k]=0;
				}
				}
				
				tnode= stnode[0]+stnode[1]+stnode[2]+stnode[3]+stnode[4]+stnode[5];

				if (tnode == 1){	

				unsigned int mid=0;
				if (stnode[0] == 1)
				fixprismPatternA(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
				else if (stnode[1] == 1)
				fixprismPatternF(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
				else if (stnode[2] == 1)
				fixprismPatternH(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);	
				else if (stnode[3] == 1)
				fixprismPatternD(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
				else if (stnode[4] == 1)
				fixprismPatternE(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
				else if (stnode[5] == 1)
				fixprismPatternG(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

				fixprismMandatoryElements(points_ele,tmpele,old_md,n_meshes,mid);

				return true;
				} 
				if (tnode == 2){
				bool ck_invalid=false;
				unsigned int mid=0;
					/* Case /|\ (Caso A) */ 
					if((stnode[0] == 1 and stnode[4]==1) or 
					(stnode[0] == 1 and stnode[5]==1) or
					(stnode[5] == 1 and stnode[4]==1)){

					fixprismPatternA(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;

					}

					/* Case /|/ */ 
					else if((stnode[4] == 1 and stnode[2] == 1)){
					fixprismPatternB(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}
					/* Case \|\ */ 
					else if((stnode[5] == 1 and stnode[1] == 1)){
					fixprismPatternC(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}
					/* Case \|/ */ 
					else if ((stnode[3]== 1 and stnode[1]== 1) or
					(stnode[3]== 1 and stnode[2]== 1) or
					(stnode[1]== 1 and stnode[2]== 1)){
					fixprismPatternD(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;

					}
					/* Case /| */
					else if (stnode[0] == 1 and stnode[2] == 1){
					fixprismPatternE(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;

					}

					/* Case \| */
					else if (stnode[3] == 1 and stnode[5] == 1){
					fixprismPatternF(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;

					}
					/* Case |\ */
					else if (stnode[0] == 1 and stnode[1] == 1){
					fixprismPatternG(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;

					}
					/* Case |/ */
					else if (stnode[4] == 1 and stnode[3] == 1){
					fixprismPatternH(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;

					}

				if (ck_invalid==true){
					fixprismMandatoryElements(points_ele,tmpele,old_md,n_meshes,mid);
					return true;
					}

				}

				if (tnode == 3){
				bool ck_invalid = false;
				unsigned int mid=0;
				/* Case /|\ */
				if ((stnode[0] == 1 and stnode[4] == 1 and stnode[1] == 1) or (stnode[0] == 1 and stnode[5] == 1 and stnode[2] == 1) or (stnode[4] == 1 and stnode[0] == 1 and stnode[5] == 1)){
					fixprismPatternA(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}
				/* Case \|/ */
				if ((stnode[1] == 1 and stnode[4] == 1 and stnode[3] == 1) or (stnode[3] == 1 and stnode[5] == 1 and stnode[2] == 1) or (stnode[1] == 1 and stnode[3] == 1 and stnode[2] == 1)){
					fixprismPatternD(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}
				/* Case \| */
				if ((stnode[0] == 1 and stnode[1] == 1 and stnode[3] == 1) or (stnode[5] == 1 and stnode[2] == 1 and stnode[1] == 1) or (stnode[3] == 1 and stnode[5] == 1 and stnode[1] == 1)){
					fixprismPatternF(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}
				/* Case |/ */
				if ((stnode[0] == 1 and stnode[2] == 1 and stnode[3] == 1) or (stnode[4] == 1 and stnode[1] == 1 and stnode[2] == 1) or (stnode[4] == 1 and stnode[3] == 1 and stnode[2] == 1)){
					fixprismPatternH(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}
				/* Case /| */
				if ((stnode[0] == 1 and stnode[3] == 1 and stnode[4] == 1) or (stnode[5] == 1 and stnode[2] == 1 and stnode[4] == 1) or (stnode[0] == 1 and stnode[2] == 1 and stnode[4] == 1)){
					fixprismPatternE(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}
				/* Case |\ */
				if ((stnode[0] == 1 and stnode[3] == 1 and stnode[5] == 1) or (stnode[4] == 1 and stnode[1] == 1 and stnode[5] == 1) or (stnode[0] == 1 and stnode[1] == 1 and stnode[5] == 1)){
					fixprismPatternG(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}

				if (ck_invalid==true){
					fixprismMandatoryElements(points_ele,tmpele,old_md,n_meshes,mid);
					return true;
					}
				}
				if (tnode == 4){
				bool ck_invalid=false;
				unsigned int mid=0;

					/* Case \| */
					if(stnode[0]== 0 and stnode[2]== 0){
					fixprismPatternF(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}
					/* Case /| */
					if(stnode[3]== 0 and stnode[5]== 0){
					fixprismPatternE(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}

					/* Case |/ */
					else if (stnode[0] == 0 and stnode[1] == 0){
					fixprismPatternH(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;

					}

					/* Case |\ */
					else if (stnode[3] == 0 and stnode[4] == 0){
					fixprismPatternG(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;

					}

					/* Case /|\ */ 
					if((stnode[1] == 0 and stnode[3]==0) or (stnode[2] == 0 and stnode[3]==0)){
					fixprismPatternA(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}

					/* Case \|/ */ 
					else if ((stnode[0]== 0 and stnode[4]== 0) or (stnode[0]== 0 and stnode[5]== 0)){
					fixprismPatternD(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;

					}

					/* Case \|\ */ 
					else if((stnode[2] == 0 and stnode[4] == 0)){
					fixprismPatternC(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);

					ck_invalid=true;
					}

					/* Case /|/ */ 
					else if((stnode[1] == 0 and stnode[5] == 0)){
					fixprismPatternB(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}


				if (ck_invalid==true){
					fixprismMandatoryElements(points_ele,tmpele,old_md,n_meshes,mid);
					return true;
					}

				}
				if (tnode == 5){
				bool ck_invalid=false;
				unsigned int mid=0;
					if(stnode[0] == 0){
					fixprismPatternD(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}
					else if(stnode[1] == 0){
					fixprismPatternE(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}
					else if(stnode[2] == 0){
					fixprismPatternG(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}
					else if(stnode[3] == 0){
					fixprismPatternA(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}
					else if(stnode[4] == 0){
					fixprismPatternF(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}
					else if(stnode[5] == 0){
					fixprismPatternH(points,points_ele,tmpele,tmppts,old_md,n_meshes,mid);
					ck_invalid=true;
					}

				if (ck_invalid==true){
					fixprismMandatoryElements(points_ele,tmpele,old_md,n_meshes,mid);
					return true;
					}
				}

			}

			return false;

	}

	void EnhancedElement::fixpyrPatternA(vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele, double &old_md, unsigned int &n_meshes){
				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);

				tetra1[0] = points_ele[0];
				tetra1[1] = points_ele[1];
				tetra1[2] = points_ele[3];
				tetra1[3] = points_ele[4];

				tetra2[0] = points_ele[2];
				tetra2[1] = points_ele[1];
				tetra2[2] = points_ele[3];
				tetra2[3] = points_ele[4];

				EnhancedElement ee1(tetra1,n_meshes);
				ee1.setMaxDistance(old_md);
				tmpele.push_back(ee1);
				EnhancedElement ee2(tetra2,n_meshes);
				ee2.setMaxDistance(old_md);
				tmpele.push_back(ee2);

	}

	void EnhancedElement::fixpyrPatternB(vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele, double &old_md, unsigned int &n_meshes){
				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);

				tetra1[0] = points_ele[0];
				tetra1[1] = points_ele[1];
				tetra1[2] = points_ele[2];
				tetra1[3] = points_ele[4];

				tetra2[0] = points_ele[0];
				tetra2[1] = points_ele[3];
				tetra2[2] = points_ele[2];
				tetra2[3] = points_ele[4];

				EnhancedElement ee1(tetra1,n_meshes);
				ee1.setMaxDistance(old_md);
				tmpele.push_back(ee1);
				EnhancedElement ee2(tetra2,n_meshes);
				ee2.setMaxDistance(old_md);
				tmpele.push_back(ee2);

	}

	void EnhancedElement::fixprismMandatoryElements(vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele, double &old_md, unsigned int &n_meshes, unsigned int &mid){
				vector<unsigned int> tetra5 (4,0);
				vector<unsigned int> tetra6 (4,0);
				vector<unsigned int> pyr (5,0);

					// two tetras that are always generated and are the same
					tetra5[0] = points_ele[3];
					tetra5[1] = points_ele[4];
					tetra5[2] = points_ele[5];
					tetra5[3] = mid;

					tetra6[0] = points_ele[0];
					tetra6[1] = points_ele[1];
					tetra6[2] = points_ele[2];
					tetra6[3] = mid;

					// last pyramid to keep consistency in diagonal face

					pyr[0] = points_ele[1];
					pyr[1] = points_ele[2];
					pyr[2] = points_ele[5];
					pyr[3] = points_ele[4];
					pyr[4]= mid;

					EnhancedElement ee5(tetra5,n_meshes);
					ee5.setMaxDistance(old_md);
					tmpele.push_back(ee5);
					EnhancedElement ee6(tetra6,n_meshes);
					ee6.setMaxDistance(old_md);
					tmpele.push_back(ee6);
					EnhancedElement ee7(pyr,n_meshes);
					ee7.setMaxDistance(old_md);
					tmpele.push_back(ee7);

	}

	void EnhancedElement::fixprismPatternA(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){
				/* Case /|\ */
				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> tetra3 (4,0);
				vector<unsigned int> tetra4 (4,0);

					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[3];
					tetra1[2] = points_ele[1];
					tetra1[3] = mid;

					tetra2[0] = points_ele[3];
					tetra2[1] = points_ele[4];
					tetra2[2] = points_ele[1];
					tetra2[3] = mid;

					tetra3[0] = points_ele[0];
					tetra3[1] = points_ele[2];
					tetra3[2] = points_ele[3];
					tetra3[3] = mid;

					tetra4[0] = points_ele[2];
					tetra4[1] = points_ele[3];
					tetra4[2] = points_ele[5];
					tetra4[3] = mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(tetra3,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);
					EnhancedElement ee4(tetra4,n_meshes);
					ee4.setMaxDistance(old_md);
					tmpele.push_back(ee4);

	}

	void EnhancedElement::fixprismPatternB(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){
				/* Case /|/ */ 
				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> tetra3 (4,0);
				vector<unsigned int> tetra4 (4,0);
					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[3];
					tetra1[2] = points_ele[1];
					tetra1[3] = mid;

					tetra2[0] = points_ele[3];
					tetra2[1] = points_ele[4];
					tetra2[2] = points_ele[1];
					tetra2[3] = mid;

					tetra3[0] = points_ele[0];
					tetra3[1] = points_ele[3];
					tetra3[2] = points_ele[5];
					tetra3[3] = mid;

					tetra4[0] = points_ele[0];
					tetra4[1] = points_ele[2];
					tetra4[2] = points_ele[5];
					tetra4[3] = mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(tetra3,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);
					EnhancedElement ee4(tetra4,n_meshes);
					ee4.setMaxDistance(old_md);
					tmpele.push_back(ee4);


	}

	void EnhancedElement::fixprismPatternC(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){
				/* Case \|\ */ 
				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> tetra3 (4,0);
				vector<unsigned int> tetra4 (4,0);

					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[1];
					tetra1[2] = points_ele[4];
					tetra1[3] = mid;

					tetra2[0] = points_ele[0];
					tetra2[1] = points_ele[3];
					tetra2[2] = points_ele[4];
					tetra2[3] = mid;

					tetra3[0] = points_ele[0];
					tetra3[1] = points_ele[2];
					tetra3[2] = points_ele[3];
					tetra3[3] = mid;

					tetra4[0] = points_ele[2];
					tetra4[1] = points_ele[3];
					tetra4[2] = points_ele[5];
					tetra4[3] = mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(tetra3,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);
					EnhancedElement ee4(tetra4,n_meshes);
					ee4.setMaxDistance(old_md);
					tmpele.push_back(ee4);

	}

	void EnhancedElement::fixprismPatternD(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){

				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> tetra3 (4,0);
				vector<unsigned int> tetra4 (4,0);

					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[1];
					tetra1[2] = points_ele[4];
					tetra1[3] = mid;

					tetra2[0] = points_ele[0];
					tetra2[1] = points_ele[3];
					tetra2[2] = points_ele[4];
					tetra2[3] = mid;

					tetra3[0] = points_ele[0];
					tetra3[1] = points_ele[3];
					tetra3[2] = points_ele[5];
					tetra3[3] = mid;

					tetra4[0] = points_ele[0];
					tetra4[1] = points_ele[2];
					tetra4[2] = points_ele[5];
					tetra4[3] = mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(tetra3,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);
					EnhancedElement ee4(tetra4,n_meshes);
					ee4.setMaxDistance(old_md);
					tmpele.push_back(ee4);

	}

	void EnhancedElement::fixprismPatternE(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){

				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> pyr (5,0);

					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[3];
					tetra1[2] = points_ele[1];
					tetra1[3] = mid;

					tetra2[0] = points_ele[3];
					tetra2[1] = points_ele[4];
					tetra2[2] = points_ele[1];
					tetra2[3] = mid;

					pyr[0] = points_ele[0];
					pyr[1] = points_ele[2];
					pyr[2] = points_ele[5];
					pyr[3] = points_ele[3];
					pyr[4]= mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(pyr,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);

	}

	void EnhancedElement::fixprismPatternF(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){

				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> pyr (5,0);

					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[1];
					tetra1[2] = points_ele[4];
					tetra1[3] = mid;

					tetra2[0] = points_ele[0];
					tetra2[1] = points_ele[3];
					tetra2[2] = points_ele[4];
					tetra2[3] = mid;

					pyr[0] = points_ele[0];
					pyr[1] = points_ele[2];
					pyr[2] = points_ele[5];
					pyr[3] = points_ele[3];
					pyr[4]= mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(pyr,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);

}

	void EnhancedElement::fixprismPatternG(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){

				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> pyr (5,0);

					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[2];
					tetra1[2] = points_ele[3];
					tetra1[3] = mid;

					tetra2[0] = points_ele[2];
					tetra2[1] = points_ele[3];
					tetra2[2] = points_ele[5];
					tetra2[3] = mid;

					pyr[0] = points_ele[0];
					pyr[1] = points_ele[1];
					pyr[2] = points_ele[4];
					pyr[3] = points_ele[3];
					pyr[4]= mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(pyr,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);

}

	void EnhancedElement::fixprismPatternH(vector<MeshPoint> &points,vector <unsigned int> &points_ele,list<EnhancedElement> &tmpele,list<MeshPoint> &tmppts, double &old_md, unsigned int &n_meshes, unsigned int &mid){

				vector<unsigned int> tetra1 (4,0);
				vector<unsigned int> tetra2 (4,0);
				vector<unsigned int> pyr (5,0);

					//adding new mid node.
					Point3D middle;
					mid=0;
					middle=points.at(points_ele[0]).getPoint()+points.at(points_ele[1]).getPoint()+points.at(points_ele[2]).getPoint()+points.at(points_ele[3]).getPoint()+points.at(points_ele[4]).getPoint()+points.at(points_ele[5]).getPoint();
					middle/=6;
					MeshPoint mp(middle, points[0].getNumberOfInputMeshes());
					mid = points.size() + tmppts.size();
					tmppts.push_back(mp);

					tetra1[0] = points_ele[0];
					tetra1[1] = points_ele[3];
					tetra1[2] = points_ele[5];
					tetra1[3] = mid;

					tetra2[0] = points_ele[0];
					tetra2[1] = points_ele[2];
					tetra2[2] = points_ele[5];
					tetra2[3] = mid;

					pyr[0] = points_ele[0];
					pyr[1] = points_ele[1];
					pyr[2] = points_ele[4];
					pyr[3] = points_ele[3];
					pyr[4]= mid;

					EnhancedElement ee1(tetra1,n_meshes);
					ee1.setMaxDistance(old_md);
					tmpele.push_back(ee1);
					EnhancedElement ee2(tetra2,n_meshes);
					ee2.setMaxDistance(old_md);
					tmpele.push_back(ee2);
					EnhancedElement ee3(pyr,n_meshes);
					ee3.setMaxDistance(old_md);
					tmpele.push_back(ee3);

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
