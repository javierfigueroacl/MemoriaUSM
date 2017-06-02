#include "stdafx.h"
#include "SurfTemplate3.h"

namespace Clobscode
{
	SurfTemplate3::SurfTemplate3(){
	}
	
	SurfTemplate3::~SurfTemplate3(){
	}
	
	bool SurfTemplate3::getSubelements(vector<unsigned int> &all, 
									  vector<unsigned int> &in,
								          vector<MeshPoint> &pts,
									  vector<vector<unsigned int> > &neweles){
		
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
				PatternA(rotated,pts,neweles);
				return true;
			}
			else if(rotated[2] == all[in[2]]){
				//the pattern is A and Positive Y rotation is needed
				rotated = hrot.rotatePosY(rotated);
				PatternA(rotated,pts,neweles);
				return true;
			}
			else if(rotated[4] == all[in[2]]){
				rotated = hrot.rotateNegX(rotated);
				rotated = hrot.rotateNegY(rotated);
				PatternA(rotated,pts,neweles);
				return true;
			}
			else if(rotated[7] == all[in[2]]){
				rotated = hrot.rotateNegZ(rotated);
				rotated = hrot.rotateNegX(rotated);
				rotated = hrot.rotateNegY(rotated);
				PatternA(rotated,pts,neweles);
				return true;
			}
			else if(rotated[5] == all[in[2]]){
				PatternB(rotated,pts,neweles);
				return true;
			}
			else if(rotated[6] == all[in[2]]){
				PatternC(rotated,pts,neweles);
				return true;
			}
			else{
				std::cout << " Warning: inconsistency detected at ";
				std::cout << "SurfTemplate3::getSubElements\n";
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
			PatternB(rotated,pts,neweles);
			return true;
		}
		if((rotated[5] == all[in[1]] || rotated[5] == all[in[2]]) &&
		   (rotated[7] == all[in[1]] || rotated[7] == all[in[2]])){
			rotated = hrot.rotateNegX(rotated);
			rotated = hrot.rotateNegX(rotated);
			PatternD(rotated,pts,neweles);
			return true;
		}
		if((rotated[5] == all[in[1]] || rotated[5] == all[in[2]]) &&
		   (rotated[2] == all[in[1]] || rotated[2] == all[in[2]])){
			PatternD(rotated,pts,neweles);
			return true;
		}
		if((rotated[6] == all[in[1]] || rotated[6] == all[in[2]]) &&
		   (rotated[7] == all[in[1]] || rotated[7] == all[in[2]])){
			rotated = hrot.rotateNegZ(rotated);
			rotated = hrot.rotatePosY(rotated);
			PatternB(rotated,pts,neweles);
			return true;
		}
		if((rotated[6] == all[in[1]] || rotated[6] == all[in[2]]) &&
		   (rotated[2] == all[in[1]] || rotated[2] == all[in[2]])){
			rotated = hrot.rotateNegZ(rotated);
			rotated = hrot.rotatePosY(rotated);
			rotated = hrot.rotatePosY(rotated);
			PatternC(rotated,pts,neweles);
			return true;
		}
		if((rotated[7] == all[in[1]] || rotated[7] == all[in[2]]) &&
		   (rotated[2] == all[in[1]] || rotated[2] == all[in[2]])){
			rotated = hrot.rotatePosY(rotated);
			rotated = hrot.rotatePosY(rotated);
			PatternD(rotated,pts,neweles);
			return true;
		}
		
		std::cerr << "Pattern not found for this configuration:\nin nodes:";
		for(unsigned int i=0;i<in.size();i++)
			std::cerr << " " << in[i];
		return false;
	}
	
	
	//Pattern C in paper
	void SurfTemplate3::PatternA(vector<unsigned int> &all, 
							        vector<MeshPoint> &pts, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(2);

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
		cout << "3a\n";

		vertices_in=0;		
		//
		
		vector<unsigned int> ele1 (5,0);
		vector<unsigned int> ele2 (5,0);
		//vector<unsigned int> ele3 (4,-1);
		
		ele1[0] = all[0];
		ele1[1] = all[4];
		ele1[2] = all[5];
		ele1[3] = all[1];
		ele1[4] = all[2];
		
		ele2[0] = all[0];
		ele2[1] = all[3];
		ele2[2] = all[7];
		ele2[3] = all[4];
		ele2[4] = all[2];
		
		/*this element might not be pertinent
		 ele3[0] = all[3];
		 ele3[1] = all[4];
		 ele3[2] = all[5];
		 ele3[3] = all[6];*/
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		//eles.push_back(new MTetrahedra(ele3));
		
	}
	
	
	/*In the paper the following 2 patterns are sumarized in just one: 
	 pattern 3B */
	
	void SurfTemplate3::PatternB(vector<unsigned int> &all, 
							        vector<MeshPoint> &pts, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(3);
		/* this is a complex pattern that arises when no enough refinement
		 * is presented on the region. For this reason, a pyramid is added
		 * to avoid holes
		 */
		vector<unsigned int> ele1(6,0);
		vector<unsigned int> ele2(5,0);
		vector<unsigned int> ele3(4,0);

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
		cout << "3b\n";

		vertices_in=0;		
		//
		
		ele1[0] = all[0];
		ele1[1] = all[4];
		ele1[2] = all[1];
		ele1[3] = all[3];
		ele1[4] = all[7];
		ele1[5] = all[2];
		
		ele2[0] = all[1];
		ele2[1] = all[2];
		ele2[2] = all[7];
		ele2[3] = all[4];
		ele2[4] = all[6];
		
		ele3[0] = all[5];
		ele3[1] = all[1];
		ele3[2] = all[4];
		ele3[3] = all[6];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		
	}
	
	void SurfTemplate3::PatternC(vector<unsigned int> &all, 
							        vector<MeshPoint> &pts, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(3);
		/* this is a complex pattern that arises when no enough refinement
		 * is presented on the region. For this reason, a pyramid is added
		 * to avoid holes
		 */

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
		cout << "3c\n";

		vertices_in=0;		
		//
		vector<unsigned int> ele1(6,0);
		vector<unsigned int> ele2(5,0);
		vector<unsigned int> ele3(4,0);
		
		ele1[0] = all[0];
		ele1[1] = all[4];
		ele1[2] = all[1];
		ele1[3] = all[3];
		ele1[4] = all[7];
		ele1[5] = all[2];
		
		ele2[0] = all[1];
		ele2[1] = all[2];
		ele2[2] = all[7];
		ele2[3] = all[4];
		ele2[4] = all[5];
		
		ele3[0] = all[6];
		ele3[1] = all[7];
		ele3[2] = all[2];
		ele3[3] = all[5];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		
	}
	
	//Pattern A in paper
	void SurfTemplate3::PatternD(vector<unsigned int> &all, 
							        vector<MeshPoint> &pts, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(4);

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
		cout << "3d\n";

		vertices_in=0;		
		//
		
		vector<unsigned int> ele1(4,0);
		vector<unsigned int> ele2(4,0);
		vector<unsigned int> ele3(4,0);
		vector<unsigned int> ele4(4,0);
		
		ele1[0] = all[0];
		ele1[1] = all[1];
		ele1[2] = all[3];
		ele1[3] = all[4];
		
		ele2[0] = all[5];
		ele2[1] = all[4];
		ele2[2] = all[6];
		ele2[3] = all[1];
		
		ele3[0] = all[2];
		ele3[1] = all[3];
		ele3[2] = all[1];
		ele3[3] = all[6];
		
		/* this tet is added to avoid a hole */
		ele4[0] = all[3];
		ele4[1] = all[6];
		ele4[2] = all[4];
		ele4[3] = all[1];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		eles.push_back(ele4);
		
	}
	
	void SurfTemplate3::swap(vector<unsigned int> &vec, int pos1, int pos2){
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

