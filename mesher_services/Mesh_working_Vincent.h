#pragma once

#include "Triangle.h"
#include "VPoint3D.h"
#include "Vector3D.h"
#include "EdgeContainer.h"
#include <vector>
#include <list>
#include <iostream>
#include <math.h>

using TxGeom::VPoint3D;
using TxGeom::Vector3D;
using std::vector;
using std::list;
using std::cout;

namespace TxTriModel
{
	class Mesh
	{
	public:
		// Construction / destruction
		Mesh();
		virtual ~Mesh();
		
		// initialize the mesh
		virtual void Init(vector<VPoint3D> &pts, vector<vector<unsigned int> > &faces);
		
		// compute the pseudo normal at each surface node
		virtual void computeNodePseudoNormal();

		// compute the pseudo normal at each surface edge
		virtual void computeEdgePseudoNormal();
		
		// compute the shortest distance between pP and the triangle formed by pA, pB, pC
		virtual void SignedDistToTriangle( const VPoint3D & pP, double & pDist, VPoint3D & pProjP, bool & pIsIn, int & faceEdgeNode,
                               const VPoint3D & pA,  const VPoint3D & pB,  const VPoint3D & pC,
                               const Vector3D & pNA, const Vector3D & pNB, const Vector3D & pNC,
							   const Vector3D & pNab, const Vector3D & pNac, const Vector3D & pNbc);		
		
		// define if a point is inside a mesh or not
		virtual bool PointIsInMesh( const VPoint3D & pPoint );
		
		virtual VPoint3D GetProjection( const VPoint3D &pPoint );

	public:
		
		vector<VPoint3D> mVertices;
		//vector<Vector3D> mNormals;
		vector<Triangle> mTriangles;
		vector<Vector3D> mVerticePseudoNormals;		// one pseudo normal per vertices (same size)
		vector<Vector3D> mEdgePseudoNormals;		// one pseudo normal per edge, so 3 pseudo normals per triangle (3*size)

	};
	
	ostream& operator<<(ostream& o, Mesh &m);
}


