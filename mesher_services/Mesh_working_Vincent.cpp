#include "stdafx.h"
#include "Mesh.h"

namespace TxTriModel
{
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	Mesh::Mesh()
	{
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	Mesh::~Mesh()
	{
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	void Mesh::Init( vector<VPoint3D> &pts, vector<vector<unsigned int> > &faces )
	{
		
		mVertices.reserve(pts.size());
		// initialising the vertices
		for (unsigned int iV = 0; iV < pts.size(); iV++)
		{
			mVertices.push_back(pts[iV]);
		}
		
		mTriangles.reserve(faces.size());
		// initialising the faces
		for (unsigned int iF = 0; iF < faces.size(); iF++) {
			Triangle t;
			t.setVertices(faces[iF]);
			t.computeNormal(mVertices);
			mTriangles.push_back(t);		
		}
		
		// computing the pseudo normal at each surface node
		mVerticePseudoNormals.reserve(pts.size());
		for (unsigned int i=0; i < pts.size(); i++) {
			//insert a null normal for each node
			Vector3D fn;
			mVerticePseudoNormals.push_back(fn);
		}
		computeNodePseudoNormal();
		
		// computing the pseudo normal at each surface edge
		mEdgePseudoNormals.reserve(faces.size()*3);
		for (unsigned int i=0; i<faces.size()*3; i++) {
			//insert a null normal for each node
			Vector3D en;
			mEdgePseudoNormals.push_back(en);
		}
		computeEdgePseudoNormal();
		
		/*for (unsigned int i=0; i<faces.size(); i++) {
			std::cout << "face " << i << "\n";
			std::cout << mEdgePseudoNormals[i*3] << "   ";
			std::cout << mEdgePseudoNormals[i*3+1] << "   ";
			std::cout << mEdgePseudoNormals[i*3+2] << "\n";			
		}*/
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	void Mesh::computeNodePseudoNormal()
	{
		// compute the pseudo normal at each surface node
		
		
		for (int jN = 0; jN < mVertices.size(); jN++)
		{
			// finding the number of faces including this surface node
			int nbFaceWithNode = 0;
			
			for (int jF = 0; jF < mTriangles.size(); jF++)
			{
				// assuming that a node appears only once in a face
				int jFn;
				
				// while we don't find the node index, we increment
				bool found_vertex = false;
				for (int i=0; i<3; i++) {
					if (mTriangles[jF].mIdxV[i]==jN) {
						found_vertex = true;
						jFn = i;
						break;
					}
				}
				
				if (found_vertex)
				{
					// the node has been found
					nbFaceWithNode++;
					
					// computing the angle at this node, assuming that A is the node, using vectors AB and AC
					Vector3D vec1, vec2;
					
					if (jFn == 0) 
					{
						// the node is the first of the triangle
						vec1 = mVertices[mTriangles[jF].mIdxV[1]] - mVertices[jN];		// AB
						vec2 = mVertices[mTriangles[jF].mIdxV[2]] - mVertices[jN];		// AC
					}	
					
					else if (jFn == 1) 
					{
						// the node is the second of the triangle
						vec1 = mVertices[mTriangles[jF].mIdxV[2]] - mVertices[jN];		// BC
						vec2 = mVertices[mTriangles[jF].mIdxV[0]] - mVertices[jN];		// BA
					}	
					
					else if (jFn == 2) 
					{
						// the node is the third of the triangle
						vec1 = mVertices[mTriangles[jF].mIdxV[0]] - mVertices[jN];		// CA
						vec2 = mVertices[mTriangles[jF].mIdxV[1]] - mVertices[jN];		// CB
					}	
					
					// derivating the angle, in radians, from the dot product
					double angle = acos((vec1*vec2)/(vec1.Norm()*vec2.Norm()));
					
					// integrating the normal at this face to the node pseudo normal
					mVerticePseudoNormals[jN] += angle * mTriangles[jF].mTriangleNormal;
				}
				// else the node is not in this triangle
			}
			// normalizing the pseudo normal
			mVerticePseudoNormals[jN] = mVerticePseudoNormals[jN] / mVerticePseudoNormals[jN].Norm();
		}
	}
	
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	void Mesh::computeEdgePseudoNormal()
	{
		// compute the pseudo normal at each surface edge
		int nbSurfFace = mTriangles.size();
		
		for (int jF = 0; jF < nbSurfFace; jF++)
		{
			// browsing each edge
			for (int iE = 0; iE < 3; iE++)
			{
				// checking if this edge has already been treated
				if (mEdgePseudoNormals[jF*3+iE].Norm()<1E-6) {
					
					
					// dealing with the first edge of the triangle, between 0 and 1 (A and B)
					
					// searching in other triangles if they have this edge too (only one other should have this edge)
					int jF2, idxA = iE, idxB = (iE+1)%3, iE2;// = 0;
					bool edgeFound = false;
					
					for (int t=0; t<nbSurfFace; t++) {
					
						if (t!=jF){
							
							for (int e = 0; e < 3; e++) {
								
								int idxA2 = e, idxB2 = (e + 1)%3;
								
								if ((mTriangles[jF].mIdxV[idxA] == mTriangles[t].mIdxV[idxB2])
								 && (mTriangles[jF].mIdxV[idxB] == mTriangles[t].mIdxV[idxA2])) {
									iE2 = e;
									jF2 = t;
									edgeFound = true;
									break;
								}
							}
						}
						if (edgeFound) {
							break;
						}
					}
					
					
					if (edgeFound){
						// the edge has been found in another triangle and we can compute the pseudo normal to this edge
						mEdgePseudoNormals[jF*3+iE] = (mTriangles[jF].mTriangleNormal + mTriangles[jF2].mTriangleNormal)/2;
						mEdgePseudoNormals[jF2*3+iE2] = mEdgePseudoNormals[jF*3+iE];
						/*std::cout << " for triangle " << jF << " at edge " << iE << " neighbor is " << jF2 << " at edge " << iE2 << " result ";
						std::cout << mEdgePseudoNormals[jF*3+iE];
						std::cout << "\n************************\n";*/

						//mEdgePseudoNormals[jF*3+iE].Normalize();
					}
					else {
						std::cout << "wtf!!!!\n";
					}

				}
			}
		}
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
    void Mesh::SignedDistToTriangle( const VPoint3D & pP, double & pDist, VPoint3D & pProjP, bool & pIsIn, int & faceEdgeNode,
							  const VPoint3D & pA,  const VPoint3D & pB,  const VPoint3D & pC,
							  const Vector3D & pNA, const Vector3D & pNB, const Vector3D & pNC,
							  const Vector3D & pNab, const Vector3D & pNac, const Vector3D & pNbc)
	
    {
		// compute the shortest distance between pP and the triangle formed by pA, pB, pC
		// inputs: 
		// VPoint3D & pP, the point to be projected
		// const VPoint3D & pA,  & pB,  & pC, the vertices of the triangle
		// const Vector3D & pNA, & pNB, & pNC, the pseudo normals at each vertices of the triangle
		// const Vector3D & pNab, & pNac, & pNbc, the pseudo normals at each edges of the triangle
		// outputs
		// double & pDist, the signed distance between the point and the triangle
		// VPoint3D & pProjP, the projected point
		// bool pIsIn, boolean expressing if the node P is inside or outside the surface
		
		
        // Triangle vectors
        Vector3D AB = pB - pA;
        Vector3D AC = pC - pA;
        Vector3D BC = pC - pB;
		
        // Normal vector pointing towards positive half-space, assuming (ABC) is CCW
        Vector3D N  = AB^AC;
        double N2  = N * N;
		
		// normal used to compute the sign
		Vector3D pProjN;
		
        //------------------------------
        // Projection on plane (ABC)
        //------------------------------
		
        // P1 = P projected on plane
        VPoint3D P1;
        Vector3D AP1;
        {
            // Projection of P on ABC plane
            Vector3D AP = pP - pA;
            double k = ( AP * N ) / N2;
            P1 = pP - k*N;
			
            // Check if P1 is in triangle
            AP1 = P1 - pA;
            double x = (AP1 ^  AC) * N / N2;
            double y = (AB  ^ AP1) * N / N2;
			
            // AP1 = x*AB + y*AC
            if( x>=0 && y>=0 && x+y<=1 )
            {
                // Normal interpolation
				pProjN = (1-x-y)*pNA + x*pNB + y*pNC;		// Marek's code
				//pProjN = N;				// real normal of the triangle
				
                // Signed distance
                double lAbsDist = pP.DistanceTo(P1);
                double lSgn = pProjN * ( pP - P1 );
				
                // Projection params
                pProjP = P1;
                pDist = lSgn<0 ? -lAbsDist : +lAbsDist ;
				
				// computing if the node is inside the surface
				pIsIn = lSgn<0;
				
				faceEdgeNode = 0;
                
				return;
            }
        }
		
        //-------------------------------------------------------------------
        // P1 is out of the triangle : compute projections on triangle edges
        //-------------------------------------------------------------------
		
        //-------------------------------
        // Distance to segment AB
        //-------------------------------
        {
            double AB2 = AB * AB;
            double t = ( AP1 * AB ) / AB2;
			
            if( t < 0 )
            {
                pProjP = pA;
                pProjN = pNA;
				
				faceEdgeNode = 2;
            }
            else
				if( t > 1 )
				{
					pProjP = pB;
					pProjN = pNB;
					
					faceEdgeNode = 2;
				}
				else
				{
					pProjP = pA + t * AB;
					pProjN = (1-t) * pNA + t * pNB;		// Marek's code
					//pProjN = pNab;		// pseudo normal of the edge AB
					
					faceEdgeNode = 1;
				}
			
            pDist = pProjP.DistanceTo( pP );
        }
		
        //-------------------------------
        // Distance to segment AC
        //-------------------------------
        {
            double AC2 = AC * AC;
            double t = ( AP1 * AC ) / AC2;
			
            VPoint3D P2;
            Vector3D P2N;
            if( t < 0 )
            {
                P2 = pA;
                P2N = pNA;
            }
            else
				if( t > 1 )
				{
					P2 = pC;
					P2N = pNC;
				}
				else
				{
					P2 = pA + t * AC;
					P2N = (1-t) * pNA + t * pNC;		// Marek's code
					//P2N = pNac;			// pseudo normal of the edge AC
				}
			
            double d = P2.DistanceTo( pP );
			
            // Better ?
            if( d < pDist )
            {
                // Update
                pDist = d;
                pProjP = P2;
                pProjN = P2N;
				
				if ((t>=0) && (t<=1)) faceEdgeNode = 1;
				else faceEdgeNode = 2;
            }
        }
		
        //-------------------------------
        // Distance to segment BC
        //-------------------------------
        {
            double BC2 = BC * BC;
            double t = ( (P1-pB) * BC ) / BC2;
			
            VPoint3D P2;
            Vector3D P2N;
            if( t < 0 )
            {
                P2 = pB;
                P2N = pNB;
            }
            else
				if( t > 1 )
				{
					P2 = pC;
					P2N = pNC;
				}
				else
				{
					P2 = pB + t * BC;
					P2N = (1-t) * pNB + t * pNC;		// Marek's code
					//P2N = pNbc;			// pseudo normal of the edge BC
				}
			
            double d = P2.DistanceTo( pP );
			
            // Better ?
            if( d < pDist )
            {
                // Update
                pDist = d;
                pProjP = P2;
                pProjN = P2N;
				
				if ((t>=0) && (t<=1)) faceEdgeNode = 1;
				else faceEdgeNode = 2;
            }
        }
		
        //-------------------------------
        // Orientation
        //-------------------------------
		
        // Change distance sign
        if( pProjN * ( pP - pProjP ) < 0 )
		{
            pDist = -pDist;
			
			// the node is inside the surface
			pIsIn = true;
		}
		else {
			// the node is outside the surface
			pIsIn = false;			
		}
    }
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	bool Mesh::PointIsInMesh( const VPoint3D & pPoint )
	{
		// define if a point is inside a mesh or not
		int closestPoint = -1;		// index of the closest triangle
		VPoint3D pProjP;				// closest point on the triangle (on triangle face, on edge, or vertice)
		double pDist;				// distance to this closest point
		double closestDist = -1;	
		bool pIsIn;					// true if this node is inside the surface
		bool bIsIn = false;
		int faceEdgeNode;			// 0 if close to a face, 1 if close to an edge, 2 if close to a vertice
		int iFaceEdgeNode;
		
		if (mTriangles.empty()) {
			return false;
		}
		
		
		//compute the first distance (to have something to compare to)
		SignedDistToTriangle( pPoint, pDist, pProjP, pIsIn, faceEdgeNode,
							 mVertices[mTriangles[0].mIdxV[0]], mVertices[mTriangles[0].mIdxV[1]], mVertices[mTriangles[0].mIdxV[2]],
							 mVerticePseudoNormals[mTriangles[0].mIdxV[0]], mVerticePseudoNormals[mTriangles[0].mIdxV[1]], mVerticePseudoNormals[mTriangles[0].mIdxV[2]],
							 mEdgePseudoNormals[0*3], mEdgePseudoNormals[0*3+1], mEdgePseudoNormals[0*3+2]); 
		
		closestPoint = 0;
		closestDist = fabs(pDist);
		bIsIn = pIsIn;
		iFaceEdgeNode = faceEdgeNode;
		
		// browsing all the surface faces
		for (int iSurfF = 1; iSurfF < mTriangles.size(); iSurfF++)
		{
			// computing the distance for this face (triangle)
			SignedDistToTriangle( pPoint, pDist, pProjP, pIsIn, faceEdgeNode,
								 mVertices[mTriangles[iSurfF].mIdxV[0]], mVertices[mTriangles[iSurfF].mIdxV[1]], mVertices[mTriangles[iSurfF].mIdxV[2]],
								 mVerticePseudoNormals[mTriangles[iSurfF].mIdxV[0]], mVerticePseudoNormals[mTriangles[iSurfF].mIdxV[1]], mVerticePseudoNormals[mTriangles[iSurfF].mIdxV[2]],
								 mEdgePseudoNormals[iSurfF*3], mEdgePseudoNormals[iSurfF*3+1], mEdgePseudoNormals[iSurfF*3+2]); 
			pDist = fabs(pDist);
			
			if (pDist < closestDist) {
				closestPoint = iSurfF;
				closestDist = pDist;
				bIsIn = pIsIn;
				iFaceEdgeNode = faceEdgeNode;
			}
			/*else {
				if ((pDist == closestDist) && !pIsIn) {
					closestPoint = iSurfF;
					bIsIn = pIsIn;
					iFaceEdgeNode = faceEdgeNode;					
				}
			}*/
		}
		
		return bIsIn;
		
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	VPoint3D Mesh::GetProjection( const VPoint3D & pPoint )
	{
		// define if a point is inside a mesh or not
		int closestPoint = -1;		// index of the closest triangle
		VPoint3D pProjP_tmp,pProjP;				// closest point on the triangle (on triangle face, on edge, or vertice)
		double pDist;				// distance to this closest point
		double closestDist = -1;	
		bool pIsIn;					// true if this node is inside the surface
		bool bIsIn = false;
		int faceEdgeNode;			// 0 if close to a face, 1 if close to an edge, 2 if close to a vertice
		int iFaceEdgeNode;
		
		if (mTriangles.empty()) {
			return pProjP;
		}
		
		
		//compute the first distance (to have something to compare to)
		SignedDistToTriangle( pPoint, pDist, pProjP_tmp, pIsIn, faceEdgeNode,
							 mVertices[mTriangles[0].mIdxV[0]], mVertices[mTriangles[0].mIdxV[1]], mVertices[mTriangles[0].mIdxV[2]],
							 mVerticePseudoNormals[mTriangles[0].mIdxV[0]], mVerticePseudoNormals[mTriangles[0].mIdxV[1]], mVerticePseudoNormals[mTriangles[0].mIdxV[2]],
							 mEdgePseudoNormals[0*3], mEdgePseudoNormals[0*3+1], mEdgePseudoNormals[0*3+2]); 
		
		closestPoint = 0;
		closestDist = fabs(pDist);
		bIsIn = pIsIn;
		iFaceEdgeNode = faceEdgeNode;
		pProjP = pProjP_tmp;
		
		// browsing all the surface faces
		for (int iSurfF = 1; iSurfF < mTriangles.size(); iSurfF++)
		{
			// computing the distance for this face (triangle)
			SignedDistToTriangle( pPoint, pDist, pProjP_tmp, pIsIn, faceEdgeNode,
								 mVertices[mTriangles[iSurfF].mIdxV[0]], mVertices[mTriangles[iSurfF].mIdxV[1]], mVertices[mTriangles[iSurfF].mIdxV[2]],
								 mVerticePseudoNormals[mTriangles[iSurfF].mIdxV[0]], mVerticePseudoNormals[mTriangles[iSurfF].mIdxV[1]], mVerticePseudoNormals[mTriangles[iSurfF].mIdxV[2]],
								 mEdgePseudoNormals[iSurfF*3], mEdgePseudoNormals[iSurfF*3+1], mEdgePseudoNormals[iSurfF*3+2]); 
			pDist = fabs(pDist);
			
			if (pDist < closestDist) {
				closestPoint = iSurfF;
				closestDist = pDist;
				bIsIn = pIsIn;
				iFaceEdgeNode = faceEdgeNode;
				pProjP = pProjP_tmp;
			}
			/*else {
				if ((pDist == closestDist) && !pIsIn) {
					closestPoint = iSurfF;
					bIsIn = pIsIn;
					iFaceEdgeNode = faceEdgeNode;					
				}
			}*/
		}
		
		return pProjP;
	}
	
	ostream& operator<<(ostream& o, Mesh &m){
		unsigned int nn = m.mVertices.size();
		unsigned int nt = m.mTriangles.size();
		o << "number of nodes " << nn << "\n";
		o << "number of triangles " << nt << "\n\n\n";
		o << "list of nodes + normals\n\n";
		for (unsigned int i=0; i<nn; i++) {
			o << m.mVertices[i] << "   " << m.mVerticePseudoNormals[i] << "\n";
		}
		o << "\nlist of triangles + normals\n\n";
		for (unsigned int i=0; i<nt; i++) {
			o << m.mTriangles[i].mIdxV[0] << " ";
			o << m.mTriangles[i].mIdxV[1] << " ";
			o << m.mTriangles[i].mIdxV[2] << "   ";
			o << m.mTriangles[i].mTriangleNormal << "\n";
		}
		o << "\nlist of edge normals per face\n\n";
		for (unsigned int i=0; i<nt; i++) {
			o << "face " << i << " (";
			for (int j=0; j<3; j++) {
				o << " " << m.mTriangles[i].mIdxV[j];
			}
			o << " )\n";
			o << m.mEdgePseudoNormals[i*3] << "   ";
			o << m.mEdgePseudoNormals[i*3+1] << "   ";
			o << m.mEdgePseudoNormals[i*3+2] << "\n";			
		}
		return o;
	}
}
