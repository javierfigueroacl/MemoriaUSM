#ifndef VPoint3D_h
#define VPoint3D_h 1

#include <math.h>
#include "Coord3D.h"
#include "stdafx.h"
#include "Vector3D.h"

using TxGeom::Vector3D;

namespace TxGeom
{
	//class Vector3D;

	class VPoint3D : public Coord3D
	{
	public:

		// Construction / destruction
		VPoint3D();
		VPoint3D( double pX, double pY, double pZ );

		// Operators
		void Reset() { mV[0]=mV[1]=mV[2]=0.0; mV[3]=1.0; }
		double SquaredDistanceTo( const VPoint3D & pB ) const;
		double DistanceTo( const VPoint3D & pB ) const;
		Vector3D operator-( const VPoint3D & pB ) const;
		VPoint3D operator+( const Vector3D & pV ) const;
		VPoint3D operator-( const Vector3D & pV ) const;
		const VPoint3D & operator+=( const Vector3D & pV );
		const VPoint3D & operator-=( const Vector3D & pV );
//**************************************** Move code to Coord3D ??
//**************************************** Move code to Coord3D ??
		//friend VPoint3D operator*( const Matrix & pMat, const VPoint3D & pA );
//**************************************** Move code to Coord3D ??
//**************************************** Move code to Coord3D ??
		
	public:
		double mV[4];
	};
}
#endif