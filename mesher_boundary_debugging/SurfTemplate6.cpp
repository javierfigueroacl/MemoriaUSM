#include "stdafx.h"
#include "SurfTemplate6.h"

namespace Clobscode
{
	SurfTemplate6::SurfTemplate6(){
	}
	
	SurfTemplate6::~SurfTemplate6(){
	}
	
	bool SurfTemplate6::getSubelements(vector<unsigned int> &all, 
									  vector<unsigned int> &out,
								          vector<MeshPoint> &pts,
									  vector<vector<unsigned int> > &neweles){
		
		HexRotation hrot;
		vector<unsigned int> rotated;
		if(out.size()!=2)
			return false;
		
		//center all at the first node:
		rotated = hrot.rotate(all,out[0]);
		
		//Possible cases for PatternA
		if(rotated[3] == all[out[1]]){
			PatternA(rotated,pts,neweles);
			return true;
		}
		if(rotated[1] == all[out[1]]){
			rotated = hrot.rotateNegY(rotated);
			PatternA(rotated,pts,neweles);
			return true;
		}
		if(rotated[4] == all[out[1]]){
			rotated = hrot.rotatePosZ(rotated);
			PatternA(rotated,pts,neweles);
			return true;
		}
		
		//Possible cases for PatternB
		if(rotated[2] == all[out[1]]){
			PatternB(rotated,pts,neweles);
			return true;
		}
		if(rotated[5] == all[out[1]]){
			rotated = hrot.rotatePosZ(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,pts,neweles);
			return true;
		}
		if(rotated[7] == all[out[1]]){
			rotated = hrot.rotateNegX(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,pts,neweles);
			return true;
		}
		if(rotated[6] == all[out[1]]){
			PatternC(rotated,pts,neweles);
			return true;
		}
		
		std::cerr << "Pattern not found for this configuration:\nout nodes:";
		for(unsigned int i=0;i<out.size();i++)
			std::cerr << " " << out[i];
		return false;
	}
	
	//w.r.t paper, this configuration counts with outside nodes 0 and 3
	void SurfTemplate6::PatternA(vector<unsigned int> &all, 
							        vector<MeshPoint> &pts,
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(2);
		
		vector<unsigned int> ele1 (6,0);
		vector<unsigned int> ele2 (6,0);

		//Debugging
		int vertices_in=0;
		vector <Point3D> mpts;
		for(unsigned int i=0; i<all.size();i++)
		mpts.push_back(pts.at(all[i]).getPoint());

		for(unsigned int i=0; i<mpts.size();i++){
			if (mpts[i][0] >=-6 && mpts[i][0] <=0) // Restriccion x
			if (mpts[i][1] >=2 && mpts[i][1] <=4.8) // Restriccion y
			if (mpts[i][2] >=-5 && mpts[i][2] <=-2) // Restriccion z octante 1
				vertices_in++;
		}

		if (vertices_in == 8){
		cout << "6a externo \n";
		for(unsigned int i=0; i<mpts.size();i++)
			cout << mpts[i] << "<- puntos xyz \n";
		}

		vertices_in=0;		
		//
		
		ele1[0] = all[4];
		ele1[1] = all[5];
		ele1[2] = all[0];
		ele1[3] = all[7];
		ele1[4] = all[6];
		ele1[5] = all[3];
		
		ele2[0] = all[1];
		ele2[1] = all[0];
		ele2[2] = all[5];
		ele2[3] = all[2];
		ele2[4] = all[3];
		ele2[5] = all[6];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		
	}
	
	//w.r.t paper, this configuration counts with outside nodes 0 and 2
	void SurfTemplate6::PatternB(vector<unsigned int> &all, 
							        vector<MeshPoint> &pts,
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(5);
		vector<unsigned int> ele1(5,0);
		vector<unsigned int> ele2(4,0);
		vector<unsigned int> ele3(4,0);
		vector<unsigned int> ele4(4,0);
		vector<unsigned int> ele5(4,0);

		//Debugging
		int vertices_in=0;
		vector <Point3D> mpts;
		for(unsigned int i=0; i<all.size();i++)
		mpts.push_back(pts.at(all[i]).getPoint());

		for(unsigned int i=0; i<mpts.size();i++){
			if (mpts[i][0] >=-6 && mpts[i][0] <=0) // Restriccion x
			if (mpts[i][1] >=2 && mpts[i][1] <=4.8) // Restriccion y
			if (mpts[i][2] >=-5 && mpts[i][2] <=-2) // Restriccion z octante 1
				vertices_in++;
		}

		if (vertices_in == 8)
		cout << "6b\n";

		vertices_in=0;		
		//
		
		ele1[0] = all[4];
		ele1[1] = all[7];
		ele1[2] = all[6];
		ele1[3] = all[5];
		ele1[4] = all[2];
		
		ele2[0] = all[0];
		ele2[1] = all[5];
		ele2[2] = all[1];
		ele2[3] = all[2];
		
		ele3[0] = all[0];
		ele3[1] = all[4];
		ele3[2] = all[5];
		ele3[3] = all[2];
		
		ele4[0] = all[0];
		ele4[1] = all[3];
		ele4[2] = all[7];
		ele4[3] = all[2];
		
		ele5[0] = all[0];
		ele5[1] = all[7];
		ele5[2] = all[4];
		ele5[3] = all[2];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		eles.push_back(ele4);
		eles.push_back(ele5);
		
	}
	
	void SurfTemplate6::PatternC(vector<unsigned int> &all, 
							        vector<MeshPoint> &pts,
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(6);
		vector<unsigned int> ele1(4,0);
		vector<unsigned int> ele2(4,0);
		vector<unsigned int> ele3(4,0);
		vector<unsigned int> ele4(4,0);
		vector<unsigned int> ele5(4,0);
		vector<unsigned int> ele6(4,0);

		//Debugging
		int vertices_in=0;
		vector <Point3D> mpts;
		for(unsigned int i=0; i<all.size();i++)
		mpts.push_back(pts.at(all[i]).getPoint());

		for(unsigned int i=0; i<mpts.size();i++){
			if (mpts[i][0] >=-6 && mpts[i][0] <=0) // Restriccion x
			if (mpts[i][1] >=2 && mpts[i][1] <=4.8) // Restriccion y
			if (mpts[i][2] >=-5 && mpts[i][2] <=-2) // Restriccion z octante 1
				vertices_in++;
		}

		if (vertices_in == 8)
		cout << "6c\n";

		vertices_in=0;		
		//
		
		ele1[0] = all[0];
		ele1[1] = all[5];
		ele1[2] = all[1];
		ele1[3] = all[6];
		
		ele2[0] = all[0];
		ele2[1] = all[1];
		ele2[2] = all[2];
		ele2[3] = all[6];
		
		ele3[0] = all[0];
		ele3[1] = all[4];
		ele3[2] = all[5];
		ele3[3] = all[6];
		
		ele4[0] = all[0];
		ele4[1] = all[7];
		ele4[2] = all[4];
		ele4[3] = all[6];
		
		ele5[0] = all[0];
		ele5[1] = all[2];
		ele5[2] = all[3];
		ele5[3] = all[6];
		
		ele6[0] = all[0];
		ele6[1] = all[3];
		ele6[2] = all[7];
		ele6[3] = all[6];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		eles.push_back(ele4);
		eles.push_back(ele5);
		eles.push_back(ele6);
		
	}
}
