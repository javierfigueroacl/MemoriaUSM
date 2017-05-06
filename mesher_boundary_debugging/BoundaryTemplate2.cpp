#include "stdafx.h"
#include "BoundaryTemplate2.h"

namespace Clobscode
{
	BoundaryTemplate2::BoundaryTemplate2(){
	}
	
	BoundaryTemplate2::~BoundaryTemplate2(){
	}
	
	bool BoundaryTemplate2::getSubelements(vector<unsigned int> &all, 
										   vector<unsigned int> &in,
										   vector<MeshPoint> &pts,
										   list<MeshPoint> &newpts,
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){
		
		HexRotation hrot;
		vector<unsigned int> rotated;
		if(in.size()!=2)
			return false;
		
		//center all at the first node:
		rotated = hrot.rotate(all,in[0]);
		
		//Possible cases for PatternA
		if(rotated[3] == all[in[1]]){
			PatternA(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		if(rotated[1] == all[in[1]]){
			rotated = hrot.rotateNegY(rotated);
			PatternA(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		if(rotated[4] == all[in[1]]){
			rotated = hrot.rotatePosZ(rotated);
			PatternA(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		
		//Possible cases for PatternB
		if(rotated[2] == all[in[1]]){
			PatternB(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		if(rotated[5] == all[in[1]]){
			rotated = hrot.rotatePosZ(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		if(rotated[7] == all[in[1]]){
			rotated = hrot.rotateNegX(rotated);
			rotated = hrot.rotateNegY(rotated);
			PatternB(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		//Possible cases for PatternC
		if(rotated[6] == all[in[1]]){
			PatternC(rotated,pts,newpts,newsubs_in,newsubs_out);
			return true;
		}
		
		std::cerr << "Pattern2 not found for this configuration:\nin nodes:";
		for (unsigned int i=0;i<in.size();i++)
			std::cerr << " " << in[i];
		return false;
	}
	
	void BoundaryTemplate2::PatternA(vector<unsigned int> &all,
									 vector<MeshPoint> &pts, 
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		newsubs_in.reserve(1);
		newsubs_out.reserve(1);		
		
		vector<unsigned int> prism1 (6,0);
		vector<unsigned int> prism2 (6,0);

		//Debugging
		int vertices_in=0;
		vector <Point3D> mpts;
		for(unsigned int i=0; i<all.size();i++)
		mpts.push_back(pts.at(all[i]).getPoint());

		for(unsigned int i=0; i<mpts.size();i++){
			if (mpts[i][0] >=-4 && mpts[i][0] <=0) // Restriccion x
			if (mpts[i][1] >=-4 && mpts[i][1] <=0) // Restriccion y
			if (mpts[i][2] >=-3 && mpts[i][2] <=2) // Restriccion z octante 1
				vertices_in++;
		}

		//cout << vertices_in << "<-  vertices octante 1 in\n";

		if (vertices_in == 8)
		cout << "2a nuevo! \n";

		vertices_in=0;		
		//
		
		//managing inside elements
		prism1[0] = all[0];
		prism1[1] = all[4];
		prism1[2] = all[1];
		prism1[3] = all[3];
		prism1[4] = all[7];
		prism1[5] = all[2];
		newsubs_in.push_back(prism1);
		
		//managing outside elements		
		prism2[0] = all[1];
        	prism2[1] = all[4];
        	prism2[2] = all[5];
        	prism2[3] = all[2];
        	prism2[4] = all[7];
        	prism2[5] = all[6]; 		
		newsubs_out.push_back(prism2);
	}
	
	void BoundaryTemplate2::PatternB(vector<unsigned int> &all,
									 vector<MeshPoint> &pts,
									 list<MeshPoint> &newpts,
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		//this template will split the hex in 6 pyramids and then
		//five of them into two tetras each.
		//Six of these ten tetras will be considered as inside 
		//and all the rest of the elements as outside.
		newsubs_in.reserve(6);
		newsubs_out.reserve(5);

		//Debugging
		int vertices_in=0;
		vector <Point3D> mpts;
		for(unsigned int i=0; i<all.size();i++)
		mpts.push_back(pts.at(all[i]).getPoint());

		for(unsigned int i=0; i<mpts.size();i++){
			if (mpts[i][0] >=-4 && mpts[i][0] <=0) // Restriccion x
			if (mpts[i][1] >=-4 && mpts[i][1] <=0) // Restriccion y
			if (mpts[i][2] >=-3 && mpts[i][2] <=2) // Restriccion z octante 1
				vertices_in++;
		}

		if (vertices_in == 8)
		cout << "2b octante 1 \n";

		vertices_in=0;	
		//
		
		//adding new hex mid node.
		Point3D middle;
		unsigned int mid=0;
		for (unsigned int i=0;i<all.size();i++){
			middle+=pts.at(all[i]).getPoint();
		}
		middle/=8;
		MeshPoint mp(middle, pts[0].getNumberOfInputMeshes());
		mid = pts.size() + newpts.size();
		newpts.push_back(mp);
		
		
		//creating element and auxiliary vectors
		vector<unsigned int> tetra1(4,0);
		vector<unsigned int> tetra2(4,0);
		vector<unsigned int> tetra3(4,0);
		vector<unsigned int> tetra4(4,0);
		vector<unsigned int> tetra5(4,0);
		vector<unsigned int> tetra6(4,0);
		vector<unsigned int> tetra7(4,0);
		vector<unsigned int> tetra8(4,0);
		vector<unsigned int> tetra9(4,0);
		vector<unsigned int> tetra10(4,0);
		vector<unsigned int> pyramid1(5,0);
		
		//Managing inside elements:	
		//Managing inside elements:				
		tetra1[0] = all[0];
		tetra1[1] = all[4];
		tetra1[2] = all[1];
		tetra1[3] = mid;
		
		tetra2[0] = all[0];
		tetra2[1] = all[1];
		tetra2[2] = all[3];
		tetra2[3] = mid;

		tetra3[0] = all[0];
		tetra3[1] = all[3];
		tetra3[2] = all[4];
		tetra3[3] = mid;
		
		tetra4[0] = all[1];
		tetra4[1] = all[2];
		tetra4[2] = all[3];
		tetra4[3] = mid;		
		
		tetra5[0] = all[1];
		tetra5[1] = all[6];
		tetra5[2] = all[2];
		tetra5[3] = mid;	
		
		tetra6[0] = all[2];
		tetra6[1] = all[6];
		tetra6[2] = all[3];
		tetra6[3] = mid;
		
		newsubs_in.push_back(tetra1);
		newsubs_in.push_back(tetra2);
		newsubs_in.push_back(tetra3);
		newsubs_in.push_back(tetra4);
		newsubs_in.push_back(tetra5);
		newsubs_in.push_back(tetra6);
		
		//Managing outside elements:
		tetra7[0] = all[1];
		tetra7[1] = all[4];
		tetra7[2] = all[5];
		tetra7[3] = mid;
		
		tetra8[0] = all[1];
		tetra8[1] = all[5];
		tetra8[2] = all[6];
		tetra8[3] = mid;
		
		tetra9[0] = all[3];
		tetra9[1] = all[6];
		tetra9[2] = all[7];
		tetra9[3] = mid;
		
		tetra10[0] = all[3];
		tetra10[1] = all[7];
		tetra10[2] = all[4];
		tetra10[3] = mid;
		
		pyramid1[0] = all[4];
		pyramid1[1] = all[7];
		pyramid1[2] = all[6];
		pyramid1[3] = all[5];		
		pyramid1[4] = mid;
		
		newsubs_out.push_back(tetra7);
		newsubs_out.push_back(tetra8);
		newsubs_out.push_back(tetra9);
		newsubs_out.push_back(tetra10);
		newsubs_out.push_back(pyramid1);
		
	}
	
	void BoundaryTemplate2::PatternC(vector<unsigned int> &all,
									 vector<MeshPoint> &pts,
									 list<MeshPoint> &newpts,
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		//this template will split the hex in 6 pyramids and then
		//each of them into two tetras each.
		//Six of these ten tetras will be considered as inside 
		//and all the rest of the elements as outside.
		newsubs_in.reserve(6);
		newsubs_out.reserve(6);

		//Debugging
		int vertices_in=0;
		vector <Point3D> mpts;
		for(unsigned int i=0; i<all.size();i++)
		mpts.push_back(pts.at(all[i]).getPoint());

		for(unsigned int i=0; i<mpts.size();i++){
			if (mpts[i][0] >=-4 && mpts[i][0] <=0) // Restriccion x
			if (mpts[i][1] >=-4 && mpts[i][1] <=0) // Restriccion y
			if (mpts[i][2] >=-3 && mpts[i][2] <=2) // Restriccion z octante 1
				vertices_in++;
		}

		if (vertices_in == 8)
		cout << "2c octante 1 \n";

		vertices_in=0;
		
		//adding new hex mid node.
		Point3D middle;
		unsigned int mid=0;
		for (unsigned int i=0;i<all.size();i++){
			middle+=pts.at(all[i]).getPoint();
		}
		middle/=8;
		MeshPoint mp(middle, pts[0].getNumberOfInputMeshes());
		mid = pts.size() + newpts.size();
		newpts.push_back(mp);
		
		
		//creating element and auxiliary vectors
		vector<unsigned int> tetra1(4,0);
		vector<unsigned int> tetra2(4,0);
		vector<unsigned int> tetra3(4,0);
		vector<unsigned int> tetra4(4,0);
		vector<unsigned int> tetra5(4,0);
		vector<unsigned int> tetra6(4,0);
		vector<unsigned int> tetra7(4,0);
		vector<unsigned int> tetra8(4,0);
		vector<unsigned int> tetra9(4,0);
		vector<unsigned int> tetra10(4,0);
		vector<unsigned int> tetra11(4,0);
		vector<unsigned int> tetra12(4,0);
		
		//Managing inside elements:	
		//Managing inside elements:				
		tetra1[0] = all[0];
		tetra1[1] = all[4];
		tetra1[2] = all[1];
		tetra1[3] = mid;
		
		tetra2[0] = all[0];
		tetra2[1] = all[1];
		tetra2[2] = all[3];
		tetra2[3] = mid;
		
		tetra3[0] = all[0];
		tetra3[1] = all[3];
		tetra3[2] = all[4];
		tetra3[3] = mid;
		
		tetra4[0] = all[5];
		tetra4[1] = all[7];
		tetra4[2] = all[6];
		tetra4[3] = mid;		
		
		tetra5[0] = all[2];
		tetra5[1] = all[6];
		tetra5[2] = all[7];
		tetra5[3] = mid;	
		
		tetra6[0] = all[2];
		tetra6[1] = all[5];
		tetra6[2] = all[6];
		tetra6[3] = mid;
		
		newsubs_in.push_back(tetra1);
		newsubs_in.push_back(tetra2);
		newsubs_in.push_back(tetra3);
		newsubs_in.push_back(tetra4);
		newsubs_in.push_back(tetra5);
		newsubs_in.push_back(tetra6);
		
		//Managing outside elements:
		tetra7[0] = all[1];
		tetra7[1] = all[4];
		tetra7[2] = all[5];
		tetra7[3] = mid;
		
		tetra8[0] = all[1];
		tetra8[1] = all[5];
		tetra8[2] = all[2];
		tetra8[3] = mid;
		
		tetra9[0] = all[2];
		tetra9[1] = all[7];
		tetra9[2] = all[3];
		tetra9[3] = mid;
		
		tetra10[0] = all[3];
		tetra10[1] = all[7];
		tetra10[2] = all[4];
		tetra10[3] = mid;

		tetra11[0] = all[4];
		tetra11[1] = all[7];
		tetra11[2] = all[5];
		tetra11[3] = mid;
		
		tetra12[0] = all[1];
		tetra12[1] = all[2];
		tetra12[2] = all[3];
		tetra12[3] = mid;
		
		newsubs_out.push_back(tetra7);
		newsubs_out.push_back(tetra8);
		newsubs_out.push_back(tetra9);
		newsubs_out.push_back(tetra10);
		newsubs_out.push_back(tetra11);
		newsubs_out.push_back(tetra12);
	}
}
