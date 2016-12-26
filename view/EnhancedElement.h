#ifndef EnhancedElementr_h
#define EnhancedElementr_h 1

#include <string>
#include <cctype>
#include <iostream>
#include <list>
#include <math.h>
//#include "EnhancedPoint.h"
#include "../geometry/Element.h"
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

using namespace std;

class EnhancedElement {
	
public:
	EnhancedElement();
	
	EnhancedElement(Element *element);
	
	virtual ~EnhancedElement();
	
	virtual void setElement(Element *element);
	
	virtual Element *getElement();
	
	virtual void computeBbox(vector<Point> &points);
	
	virtual void detectOnSurface(FaceContainer *fc);
	
	virtual void remove(int axe, double start, double end);
	
	virtual bool wasRemoved();
	
	virtual void addFace(int idx);
	
	virtual list<int> getFaces();
	
protected:
	
	Element *element;
	Point min,max;
	list<int> faces;
	vector<int> epoints;
	bool removed;
};

inline list<int> EnhancedElement::getFaces(){
	return faces;
}

inline bool EnhancedElement::wasRemoved(){
	return removed;
}

inline Element *EnhancedElement::getElement(){
	return element;
}

inline void EnhancedElement::setElement(Element *element){
	this->element = element;
}

inline void EnhancedElement::addFace(int id){
	faces.push_back(id);
}

#endif

