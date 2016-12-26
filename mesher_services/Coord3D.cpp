#include "stdafx.h"
#include "Coord3D.h"

namespace TxGeom
{

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	Coord3D::Coord3D( double pX, double pY, double pZ, double pW )
	{
		/*double epsilon = 1e-6;
		if (pX<epsilon && pX>-epsilon) {
			mV[0] = 0;
		}
		else {
			mV[0] = pX;
		}
		
		if (pY<epsilon && pY>-epsilon) {
			mV[1] = 0;
		}
		else {
			mV[1] = pY;
		}

		if (pZ<epsilon && pZ>-epsilon) {
			mV[2] = 0;
		}
		else {
			mV[2] = pZ;
		}*/

		mV[0] = pX;
		mV[1] = pY;
		mV[2] = pZ;
		mV[3] = pW;
	}

		
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	ostream& operator<<(ostream& o,Coord3D &c){
		o << c.mV[0] << " " << c.mV[1] << " " << c.mV[2];
		return o;
	}
	
	ostream& operator<<(ostream& o,const Coord3D &c){
		o << c.X() << " " << c.Y() << " " << c.Z();
		return o;
	}
}