#ifndef SurfHexahedron_h
#define SurfHexahedron_h 3

#include <vector>
#include <list>
#include <iostream>
#include "MeshPoint.h"
#include "TriMesh.h"
#include "SurfTemplate1.h"
#include "SurfTemplate2.h"
#include "SurfTemplate3.h"
#include "SurfTemplate4.h"
#include "SurfTemplate5.h"
#include "SurfTemplate6.h"
#include "SurfTemplate7.h"


using std::vector;
using std::list;
using Clobscode::MeshPoint;
using Clobscode::TriMesh;

namespace Clobscode
{
	class SurfHexahedron {
		
	public:
		
		SurfHexahedron(vector<unsigned int> &mypoints);
		
		virtual ~SurfHexahedron();
		
        virtual vector<vector<unsigned int> > getSubElements(vector<MeshPoint> &meshpoints, list<MeshPoint> &newpts,
                                                             TriMesh &input, unsigned int &e_idx,
                                                             vector<vector<unsigned int> > &possibles,
                                                             vector<vector<unsigned int> > &continuity,
                                                             list<unsigned int> &intersected_faces);        
    protected:
        
        vector<unsigned int> points;
		
	};
}
#endif
