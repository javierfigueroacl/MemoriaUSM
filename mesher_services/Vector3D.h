#ifndef Vector3D_h
#define Vector3D_h 1

#include "Coord3D.h"
#include <math.h>

using TxGeom::Coord3D;

namespace TxGeom {
	class Vector3D : public Coord3D
	{
	public:	
		Vector3D();
		Vector3D( double pX, double pY, double pZ );
		Vector3D( const double pV[3] );
		
		void Reset() { mV[0]=mV[1]=mV[2]=mV[3]=0.0; }
		double operator*( const Vector3D & pV ) const;
		double SquaredNorm() const;
		double Norm() const;
		void Normalize();
		Vector3D operator^( const Vector3D & pV ) const;
		Vector3D operator/( double pK ) const;
		Vector3D operator/=( double pK );
		
		Vector3D operator+() const;
		Vector3D operator-() const;
		Vector3D operator+( const Vector3D & pV ) const;
		Vector3D operator-( const Vector3D & pV ) const;
		const Vector3D & operator+=( const Vector3D & pV );
		const Vector3D & operator-=( const Vector3D & pV );
		const Vector3D & operator*=( double pK );
		
		Vector3D operator*( double pK ) const;
		friend Vector3D operator*( double pK, const Vector3D & pV );
		friend Vector3D operator/( double pK, const Vector3D & pV );
	};
}
#endif
