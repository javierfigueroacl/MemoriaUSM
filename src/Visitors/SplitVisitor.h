#ifndef SplitVisitor_h
#define SplitVisitor_h 1

#include <list>
#include <set>
#include <vector>

#include "../MeshPoint.h"
#include "../Point3D.h"
#include "../OctreeEdge.h"

#include "Visitor.h"


using Clobscode::MeshPoint;
using Clobscode::OctreeEdge;
using Clobscode::Point3D;
using std::vector;
using std::list;
using std::set;


namespace Clobscode
{
    class SplitVisitor : public Visitor {

    public:
        SplitVisitor();
        /*void VisitOctant(Octant *o,
                         vector<MeshPoint> &points,
                         list<Point3D> &new_pts,
                         set<OctreeEdge> &edges,
                         vector< vector<unsigned int> > &new_eles,
                         vector<vector<Point3D> > &clipping);*/

        bool visit(Octant *o);

        void setPoints(vector<MeshPoint> &points);
        void setNewPts(list<Point3D> &new_pts);
        void setEdges(set<OctreeEdge> &edges);
        void setNewEles(vector<vector<unsigned int> > &new_eles);
        void setClipping(vector<vector<Point3D> > &clipping);

    protected:
        //references
        vector<MeshPoint> *points;
        list<Point3D> *new_pts;
        set<OctreeEdge> *edges;
        vector<vector<unsigned int> > *new_eles;
        vector<vector<Point3D> > *clipping;

        bool splitEdge(const unsigned int &idx1,
                       const unsigned int &idx2,
                       unsigned int &c_n_pts,
                       unsigned int &mid_idx);

        bool splitFace(const unsigned int &idx1,
                       const unsigned int &idx2,
                       const unsigned int &idx3,
                       const unsigned int &idx4,
                       unsigned int &c_n_pts,
                       unsigned int &mid_idx);


    };
}



#endif //MESHER_ROI_SPLITVISITOR_H
