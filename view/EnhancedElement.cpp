#include "EnhancedElement.h"

EnhancedElement::EnhancedElement(){
	removed = false;
}

EnhancedElement::EnhancedElement(Element *element){
	this->element = element;
	epoints = element->getPoints();
}

EnhancedElement::~EnhancedElement(){
	
}

//removes the elements outside the given range in the given axis.
void EnhancedElement::remove(int axe, double start, double end){
	if(min[axe]<start || max[axe]>end)
		removed=true;
	else
		removed=false;
}

void EnhancedElement::computeBbox(vector<Point> &points){
	
	if (epoints.empty()) {
		cout << "element with no nodes created\n";
		return;
	}
	
	//the initial values of min and max correspond to the 
	//coords of the first point.
	if (epoints[0]>=points.size()) {
		cout << "out of boundary: " << epoints[0] << "/" << points.size()<< endl;
		return;
	}
	min[0] = max[0] = points.at(epoints[0])[0];
	min[1] = max[1] = points.at(epoints[0])[1];
	min[2] = max[2] = points.at(epoints[0])[2];
	
	for(int i=1;i<epoints.size();i++){
		if (epoints[i]>=points.size()) {
			cout << "out of boundary: " << epoints[i] << "/" << points.size()<< endl;
			return;
		}
		double x = points.at(epoints[i])[0];
		double y = points.at(epoints[i])[1];
		double z = points.at(epoints[i])[2];
		if(min[0]>x)
			min[0]=x;
		if(max[0]<x)
			max[0]=x;
		if(min[1]>y)
			min[1]=y;
		if(max[1]<y)
			max[1]=y;
		if(min[2]>z)
			min[2]=z;
		if(max[2]<z)
			max[2]=z;
	}
}

void EnhancedElement::detectOnSurface(FaceContainer *fc){
	list<int>::iterator iter;
	bool surf = false;
	for(iter=faces.begin();iter!=faces.end();iter++)
		if(fc->getFace(*iter)->numberOfElements()==1){
			surf=true;
			break;
		}
	//if the element has at least one surface face all the
	//associated faces will change their colors.
	if(surf){
		for(iter=faces.begin();iter!=faces.end();iter++)
			//fc->getFace(*iter)->setColor(" 1 0.5 0.1 ");
			//fc->getFace(*iter)->setColor(" 0.7 0.7 0.7 ");
            fc->getFace(*iter)->setColor(" 1 1 1 ");
	}
	
}
