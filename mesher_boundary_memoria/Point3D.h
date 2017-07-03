#ifndef Point3D_h
#define Point3D_h 1

#include <iostream>
#include <sstream>
#include <math.h>
#include <list>
#include <vector>

namespace Clobscode
{
using namespace std;

class Point3D{
	
public:
	Point3D();
	
	Point3D(double x, double y, double z);
	
	virtual ~Point3D();
	
	virtual double X() const;
	
	virtual double Y() const;
	
	virtual double Z() const;
	
	virtual void normalize();
	
	virtual double Norm();
	
	virtual Point3D cross(Point3D p);
	
	//cross product operator
	virtual Point3D operator^(Point3D p);
	
	virtual double dot(Point3D p);
	
	//dot product operator
	virtual double operator*(Point3D p);
	
	virtual double distance(Point3D p);
	
	virtual double DistanceTo(Point3D p);
	
	virtual Point3D operator-(Point3D p2);
	
	virtual Point3D operator-();
	
	virtual Point3D operator+(Point3D p2);
	
	virtual void operator+=(Point3D p2);
	
	virtual void operator/=(double div);
	
	virtual double &operator[](int pos);
	
	virtual void operator=(Point3D p);
	
	virtual Point3D operator*(double escalar);
	
	
	virtual void update(Point3D *Point3D);
	
	virtual void update(Point3D Point3D);
		
	virtual string print();
	
protected:
	
	double x,y,z;
	
};

inline double Point3D::X() const {
	return x;
}

inline double Point3D::Y() const {
	return y;
}

inline double Point3D::Z() const {
	return z;
}

inline void Point3D::update(Point3D *Point3D){
	x = (*Point3D)[0];
	y = (*Point3D)[1];
	z = (*Point3D)[2]; 
}

inline void Point3D::update(Point3D Point3D){
	x = Point3D[0];
	y = Point3D[1];
	z = Point3D[2]; 
}

std::ostream& operator<<(std::ostream& o,Point3D &p);

bool operator==(Point3D &p1,Point3D &p2);

bool operator!=(Point3D &p1,Point3D &p2); 
}
#endif
