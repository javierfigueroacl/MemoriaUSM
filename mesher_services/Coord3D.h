#pragma once

#include <iostream>

using std::ostream;

namespace TxGeom
{

	class Coord3D
	{
	public:
		Coord3D( double pX, double pY, double pZ, double pW );

	public:

		// Specific access
		double X() const { return mV[0]; }
		double Y() const { return mV[1]; }
		double Z() const { return mV[2]; }
		double W() const { return mV[3]; }
		double & X() { return mV[0]; }
		double & Y() { return mV[1]; }
		double & Z() { return mV[2]; }
		double & W() { return mV[3]; }

	public:
		double mV[4];
	};
	
	ostream& operator<<(ostream& o, Coord3D &c);
	ostream& operator<<(ostream& o, const Coord3D &c);
}