#ifndef GridMesher_h
#define GridMesher_h 1

#include "MeshPoint.h"
#include "EnhancedElement.h"

using std::vector;
using Clobscode::MeshPoint;
using Clobscode::EnhancedElement;

namespace Clobscode
{
	class GridMesher{
		
	public:
		
		GridMesher(const unsigned int &nm);
		
		virtual ~GridMesher();
		
		virtual void generatePoints(vector<double> &bounds,
									vector<double> &all_x,
									vector<double> &all_z,
									vector<double> &all_y, int rl);
		
		virtual void generateMesh(vector<double> &all_x,
								  vector<double> &all_z,
								  vector<double> &all_y,
								  vector<MeshPoint> &points,
								  vector<EnhancedElement> &elements);
		
	protected:
		
		virtual void generateVector(vector<double> &coords, double min,
									double max, double step);
		
		unsigned int n_meshes;
		
	};
	
}
#endif
