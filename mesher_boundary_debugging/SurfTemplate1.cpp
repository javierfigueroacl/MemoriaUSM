#include "stdafx.h"
#include "SurfTemplate1.h"

namespace Clobscode
{
	SurfTemplate1::SurfTemplate1(){
	}
	
	SurfTemplate1::~SurfTemplate1(){
	}
	
	bool SurfTemplate1::getSubelements(vector<unsigned int> &all, 
									  vector<unsigned int> &in,
								          vector<MeshPoint> &pts,
									  vector<vector<unsigned int> > &newsubs){
		
		newsubs.reserve(1);
		vector<unsigned int> tetra,rotated;
		HexRotation hrot;
		tetra.reserve(4);

		//Debugging
		int vertices_in=0;
		vector <Point3D> mpts;
		for(unsigned int i=0; i<all.size();i++)
		mpts.push_back(pts.at(all[i]).getPoint());

		for(unsigned int i=0; i<mpts.size();i++){
			if (mpts[i][0] >=-50 && mpts[i][0] <=-25) // Restriccion x
			if (mpts[i][1] >=-20 && mpts[i][1] <=10) // Restriccion y
			if (mpts[i][2] >=5 && mpts[i][2] <=30) // Restriccion z octante 1
				vertices_in++;
		}

		if (vertices_in == 8)
		cout << "1a\n";

		vertices_in=0;		
		//
		
		rotated = hrot.rotate(all,in[0]);
		
		tetra.push_back(rotated[0]);
		tetra.push_back(rotated[1]);
		tetra.push_back(rotated[3]);
		tetra.push_back(rotated[4]);
		
		newsubs.push_back(tetra);
		
		return true;
	}
}
