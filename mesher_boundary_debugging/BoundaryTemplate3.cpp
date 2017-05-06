#include "stdafx.h"
#include "BoundaryTemplate3.h"

namespace Clobscode
{
	BoundaryTemplate3::BoundaryTemplate3(){
	}
	
	BoundaryTemplate3::~BoundaryTemplate3(){
	}
	
	bool BoundaryTemplate3::getSubelements(vector<unsigned int> &all, 
										   vector<unsigned int> &in,
										   vector<MeshPoint> &pts,
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){
		
		HexRotation hrot;
		vector<unsigned int> rotated;
		vector<unsigned int> pivotes(3,0);
		if(in.size()!=3)
			return false;
		
		bool edge2 = false;
		
		//center all at the first node:
		rotated = hrot.rotate(all,in[0]);
		
		//find out if rotating we can conform an edge
		//of inner points between (0,3)
		if(rotated[3] == all[in[1]]){
			edge2 = true;
		}
		else if(rotated[3] == all[in[2]]){
			edge2 = true;
			swap(in,1,2);
		}
		else if(rotated[4] == all[in[1]]){
			edge2 = true;
			rotated = hrot.rotatePosZ(rotated);
			swap(in,0,1);
		}
		else if(rotated[4] == all[in[2]]){
			edge2 = true;
			rotated = hrot.rotatePosZ(rotated);
			swap(in,0,2);
			swap(in,1,2);
		}
		else if(rotated[1] == all[in[1]]){
			edge2 = true;
			rotated = hrot.rotateNegY(rotated);
			swap(in,0,1);
		}
		else if(rotated[1] == all[in[2]]){
			edge2 = true;
			rotated = hrot.rotateNegY(rotated);
			swap(in,0,2);
			swap(in,1,2);
		}
		
		//if edge2 is true, then the current edge (0,3) has inner points
		//and the one to test is in[2]: possible patterns: A,B,C
		if(edge2){
			if(rotated[1] == all[in[2]]){
				//the pattern is A and no rotation is needed
				PatternA(rotated,pts,newsubs_in,newsubs_out);
				return true;
			}
			else if(rotated[2] == all[in[2]]){
				//the pattern is A and Positive Y rotation is needed
				rotated = hrot.rotatePosY(rotated);
				PatternA(rotated,pts,newsubs_in,newsubs_out);
				return true;
			}
			else if(rotated[4] == all[in[2]]){
				rotated = hrot.rotateNegX(rotated);
				rotated = hrot.rotateNegY(rotated);
				PatternA(rotated,pts,newsubs_in,newsubs_out);
				return true;
			}
			else if(rotated[7] == all[in[2]]){
				rotated = hrot.rotateNegZ(rotated);
				rotated = hrot.rotateNegX(rotated);
				rotated = hrot.rotateNegY(rotated);
				PatternA(rotated,pts,newsubs_in,newsubs_out);
				return true;
			}
			else if(rotated[5] == all[in[2]]){
				PatternB(rotated,pts,newsubs_in,newsubs_out);
				return true;
			}
			else if(rotated[6] == all[in[2]]){
				PatternC(rotated,pts,newsubs_in,newsubs_out);
				return true;
			}
			else{
				std::cout << " Warning: inconsistency detected at ";
				std::cout << "BoundaryTemplate3::getSubElements\n";
				std::cout << " configuration (0,1) and no third point.\n";
				std::cout << " nodes inside";
				for (unsigned int i=0; i<in.size(); i++) {
					std::cout << " " << in[i];
				}
				std::cout << std::endl;
				return false;
			}
		}
		//if we are here, edge2 is false, therefore nodes 1,3 and 4 aren't
		//inside.
		if((rotated[5] == all[in[1]] || rotated[5] == all[in[2]]) &&
		   (rotated[6] == all[in[1]] || rotated[6] == all[in[2]])){
			rotated = hrot.rotateNegX(rotated);
			rotated = hrot.rotateNegX(rotated);
			PatternB(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		if((rotated[5] == all[in[1]] || rotated[5] == all[in[2]]) &&
		   (rotated[7] == all[in[1]] || rotated[7] == all[in[2]])){
			rotated = hrot.rotateNegX(rotated);
			rotated = hrot.rotateNegX(rotated);
			PatternD(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		if((rotated[5] == all[in[1]] || rotated[5] == all[in[2]]) &&
		   (rotated[2] == all[in[1]] || rotated[2] == all[in[2]])){
			PatternD(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		if((rotated[6] == all[in[1]] || rotated[6] == all[in[2]]) &&
		   (rotated[7] == all[in[1]] || rotated[7] == all[in[2]])){
			rotated = hrot.rotateNegZ(rotated);
			rotated = hrot.rotatePosY(rotated);
			PatternB(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		if((rotated[6] == all[in[1]] || rotated[6] == all[in[2]]) &&
		   (rotated[2] == all[in[1]] || rotated[2] == all[in[2]])){
			rotated = hrot.rotateNegZ(rotated);
			rotated = hrot.rotatePosY(rotated);
			rotated = hrot.rotatePosY(rotated);
			PatternC(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		if((rotated[7] == all[in[1]] || rotated[7] == all[in[2]]) &&
		   (rotated[2] == all[in[1]] || rotated[2] == all[in[2]])){
			rotated = hrot.rotatePosY(rotated);
			rotated = hrot.rotatePosY(rotated);
			PatternD(rotated,pts,newsubs_in,newsubs_out);
			return true;
		}
		
		std::cerr << "Pattern not found for this configuration:\nin nodes:";
		for(unsigned int i=0;i<in.size();i++)
			std::cerr << " " << in[i];
		return false;
	}
	
	
	//Pattern C in paper
	void BoundaryTemplate3::PatternA(vector<unsigned int> &all,
									 vector<MeshPoint> &pts, 
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		newsubs_in.reserve(2);
		newsubs_out.reserve(1);

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
		cout << "3a octante 1 \n";

		vertices_in=0;	
		//
		
		vector<unsigned int> pyramid1 (5,0);
		vector<unsigned int> pyramid2 (5,0);
		vector<unsigned int> pyramid3 (5,0);

		//managing inside elements
		pyramid1[0] = all[0];
		pyramid1[1] = all[4];
		pyramid1[2] = all[5];
		pyramid1[3] = all[1];
		pyramid1[4] = all[2];

		pyramid2[0] = all[0];
		pyramid2[1] = all[3];
		pyramid2[2] = all[7];
		pyramid2[3] = all[4];
		pyramid2[4] = all[2];
		
		newsubs_in.push_back(pyramid1);
		newsubs_in.push_back(pyramid2);
		
		//managing outside elements		
		pyramid2[0] = all[4];
		pyramid2[1] = all[7];
		pyramid2[2] = all[6];
		pyramid2[3] = all[5];
		pyramid2[4] = all[2];
		
		newsubs_out.push_back(pyramid3);
		
	}
	
	
	/*In the paper the following 2 patterns are sumarized in just one: 
	 pattern 3B */
	
	void BoundaryTemplate3::PatternB(vector<unsigned int> &all,
									 vector<MeshPoint> &pts, 
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		newsubs_in.reserve(3);
		
		/* this is a complex pattern that arises when no enough refinement
		 * is presented on the region. For this reason, a pyramid is added
		 * to avoid holes
		 */
		
		vector<unsigned int> prism1 (6,0);
		vector<unsigned int> pyramid1 (5,0);
		vector<unsigned int> tetra1 (4,0);

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
		cout << "3b octante 1 \n";

		vertices_in=0;	
		//
		
		//managing inside elements
		prism1[0] = all[0];
		prism1[1] = all[4];
		prism1[2] = all[1];
		prism1[3] = all[3];
		prism1[4] = all[7];
		prism1[5] = all[2];

		pyramid1[0] = all[1];
		pyramid1[1] = all[2];
		pyramid1[2] = all[7];
		pyramid1[3] = all[4];
		pyramid1[4] = all[6];
		
		tetra1[0] = all[5];
		tetra1[1] = all[1];
		tetra1[2] = all[4];
		tetra1[3] = all[6];

		
		newsubs_in.push_back(prism1);
		newsubs_in.push_back(pyramid1);
		newsubs_in.push_back(tetra1);
		
	}
	
	void BoundaryTemplate3::PatternC(vector<unsigned int> &all,
									 vector<MeshPoint> &pts, 
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		
		newsubs_in.reserve(3);
		
		/* this is a complex pattern that arises when no enough refinement
		 * is presented on the region. For this reason, a pyramid is added
		 * to avoid holes
		 */
		
		vector<unsigned int> prism1 (6,0);
		vector<unsigned int> pyramid1 (5,0);
		vector<unsigned int> tetra1 (4,0);

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
		cout << "3c octante 1 \n";

		vertices_in=0;	
		//
		
		//managing inside elements
		prism1[0] = all[0];
		prism1[1] = all[4];
		prism1[2] = all[1];
		prism1[3] = all[3];
		prism1[4] = all[7];
		prism1[5] = all[2];
		
		pyramid1[0] = all[1];
		pyramid1[1] = all[2];
		pyramid1[2] = all[7];
		pyramid1[3] = all[4];
		pyramid1[4] = all[5];
		
		tetra1[0] = all[6];
		tetra1[1] = all[7];
		tetra1[2] = all[2];
		tetra1[3] = all[5];
		
		
		newsubs_in.push_back(prism1);
		newsubs_in.push_back(pyramid1);
		newsubs_in.push_back(tetra1);
		
	}
	
	//Pattern A in paper
	void BoundaryTemplate3::PatternD(vector<unsigned int> &all,
									 vector<MeshPoint> &pts, 
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		
		newsubs_in.reserve(4);
		//newsubs_in.clear();
		newsubs_out.reserve(1);
		//newsubs_out.clear();
		
		vector<unsigned int> tetra1 (4,0);
		vector<unsigned int> tetra2 (4,0);
		vector<unsigned int> tetra3 (4,0);
		vector<unsigned int> tetra4 (4,0);
		vector<unsigned int> tetra5 (4,0);

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
		cout << "3d octante 1 \n";	
		//
		
		//managing inside elements		
		tetra1[0] = all[0];
		tetra1[1] = all[1];
		tetra1[2] = all[3];
		tetra1[3] = all[4];
		
		tetra2[0] = all[5];
		tetra2[1] = all[4];
		tetra2[2] = all[6];
		tetra2[3] = all[1];
		
		tetra3[0] = all[2];
		tetra3[1] = all[3];
		tetra3[2] = all[1];
		tetra3[3] = all[6];
		
		/* this tet is added to avoid a hole */
		tetra4[0] = all[3];
		tetra4[1] = all[6];
		tetra4[2] = all[4];
		tetra4[3] = all[1];
		
		newsubs_in.push_back(tetra1);
		newsubs_in.push_back(tetra2);
		newsubs_in.push_back(tetra3);
		newsubs_in.push_back(tetra4);
		
		//managing outside elements
		tetra5[0] = all[3];
		tetra5[1] = all[4];
		tetra5[2] = all[6];
		tetra5[3] = all[7];
		
		newsubs_out.push_back(tetra5);
		
	}
	
	void BoundaryTemplate3::swap(vector<unsigned int> &vec, int pos1, int pos2){
		int aux = vec[pos1];
		vec[pos1] = vec[pos2];
		vec[pos2] = aux;
	}
	
	/******************
	 * This class manage the different cases of 3 points inside patterns.
	 * Once the pattern is identified, the corresponding class will handle
	 * the elements to be returned (
	 *//// 
}

