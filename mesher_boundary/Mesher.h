#ifndef Mesher_h
#define Mesher_h 1

#include "TriMesh.h"
#include "FEMesh.h"
#include "GridMesher.h"
#include <list>
#include <vector>

using std::vector;
using std::list;

namespace Clobscode
{
	
	class Mesher{
		
	public:
		
		typedef bool (*PTRFUN_POINT_IN_MESH)( const void * pData, const Point3D & pPoint, const unsigned int &mn);
		typedef Point3D (*PTRFUN_POINT_PROJECTOR)(const void *pData, const Point3D &pPoint, const unsigned int &mn );
		
		Mesher(const unsigned int &nm);
		
		virtual ~Mesher();
		
		virtual FEMesh generateMesh( void * pClientData, 
									PTRFUN_POINT_IN_MESH pClientPointTestFunc,
									PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc, 
									std::vector<Clobscode::TriMesh> &inputs,int rl);
		
		virtual FEMesh generateMesh( void * pClientData, 
									PTRFUN_POINT_IN_MESH pClientPointTestFunc,
									PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc, 
									vector<double> &bounds,int rl);
		
		virtual FEMesh generateMesh( void * pClientData, 
									PTRFUN_POINT_IN_MESH pClientPointTestFunc,
									PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc,
									vector<double> & pGridXs, 
									vector<double> & pGridYs,
									vector<double> & pGridZs);
		
		virtual void setNumberOfInputMeshes(const unsigned int &nm);
		
	protected:
		
		virtual FEMesh generateMesh( void * pClientData, 
									PTRFUN_POINT_IN_MESH pClientPointTestFunc,
									PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc);
		
		virtual void generateGridMesh(int rl, vector<double> &bounds);
		
		virtual void labelNodesAndElements(void * pClientData, 
										   PTRFUN_POINT_IN_MESH pClientPointTestFunc);
		virtual void labelNodesAndElements2(void * pClientData, 
										   PTRFUN_POINT_IN_MESH pClientPointTestFunc);
		
		virtual void detectSurfaceElements();
		
		virtual void projectCloseToOutsideBoundaryNodes(void * pClientData, 
												 PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc);
		
		virtual void projectCloseToInsideBoundaryNodes(void * pClientData, 
												 PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc);
		
		virtual void removeOnSurface();

		virtual void applySurfaceTemplates(void * pClientData, 
										  PTRFUN_POINT_IN_MESH pClientPointTestFunc);

		virtual void applyBoundaryTemplates(void * pClientData, 
										   PTRFUN_POINT_IN_MESH pClientPointTestFunc);
		
		virtual void shrinkToBoundary( void * pClientData, 
									  PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc);
		
		virtual void linkElementsToNodes();
		
		virtual void writeOutsideNodes(FEMesh &mesh, void * pClientData, 
									   PTRFUN_POINT_IN_MESH pClientPointTestFunc);
		
		virtual void writeInsideNodes(FEMesh &mesh, void * pClientData, 
									  PTRFUN_POINT_IN_MESH pClientPointTestFunc);
		
		virtual void saveOutputMesh(FEMesh &mesh);
		
		/*start debugging*/
		virtual void debugging(void * pClientData, 
							   PTRFUN_POINT_IN_MESH pClientPointTestFunc);
		/*end debugging*/		
	protected:
		
		vector<MeshPoint> points;
		vector<EnhancedElement> elements;
		unsigned int n_meshes;
		
	};
	
	inline void Mesher::setNumberOfInputMeshes(const unsigned int &nm){
		n_meshes = nm;
	}
}
#endif
