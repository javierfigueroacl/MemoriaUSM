#include "stdafx.h"
#include "BoundaryTemplate4.h"

namespace Clobscode
{
	BoundaryTemplate4::BoundaryTemplate4(){
	}
	
	BoundaryTemplate4::~BoundaryTemplate4(){
	}
	
	bool BoundaryTemplate4::getSubelements(vector<unsigned int> &all, 
									  vector<unsigned int> &in,
										   vector<vector<unsigned int> > &newsubs_in,
										   vector<vector<unsigned int> > &newsubs_out){
		
		HexRotation hrot;
		vector<unsigned int> rotated,number (4,0);
		if((int)in.size()!=4)
			return false;
		rotated.reserve(8);
		
		//searh by edges:
		int total=0;
		for (unsigned int i=0;i<4;i++){
			vector<unsigned int> edsi = getEdges(in[i]);
			for (unsigned int j=0;j<edsi.size();j++){
				for (unsigned int k=0;k<4;k++){
					if(in[k]==edsi[j]){
						total++;
						number[i]++;
						continue;
					}
				}	
			}
		}
		//pattern A will send back the same Hexahedra
		if(total==8){
			PatternA(all,newsubs_in);
			return true;
		}
		//pattern G has only one possible configuration
		else if(total==0){
			rotated = hrot.rotate(all,in[0]);
			PatternG(rotated,newsubs_in);
			return true;
		}
		else if(total==4){
			//when 4 connections exist, Pattern F will be applied when
			//the number of connections per node is 1, otherwise Pattern
			//B is applied.
			bool twoc = true;
			int center=0;
			for (unsigned int i=0;i<4;i++){
				if(number[i]!=1){
					twoc = false;
					break;
				}
			}
			if(twoc){
				//detect possible transformation of pattern F
				rotated = hrot.rotate(all,in[0]);
				if(rotated[4]==all[in[1]] || rotated[4]==all[in[2]] 
				   || rotated[4]==all[in[3]]){
					
					rotated = hrot.rotatePosZ(rotated);
					PatternF(rotated,newsubs_in);
					return true;
				}
				if(rotated[1]==all[in[1]] || rotated[1]==all[in[2]] 
				   || rotated[1]==all[in[3]]){
					
					rotated = hrot.rotateNegY(rotated);
					PatternF(rotated,newsubs_in);
					return true;
				}
				
				PatternF(rotated,newsubs_in);
				return true;
			}
			else{
				//detect possible transformation of pattern B:
				//the most connected node must be at position 0 
				//of the transformated
				//node configuration.
				int connect2=0,one1=0,one2=0;
				for (unsigned int i=0;i<4;i++){
					if(number[i]==2){
						connect2=in[i];
					}
					else if(number[i]==1){
						if(one1==0)
							one1=in[i];
						else
							one2=in[i];
					}
				}
				
				//std::cout << " oooppsss\n";
				
				rotated = hrot.rotate(all,connect2);
				if((rotated[4]==all[one1] && rotated[3]==all[one2]) ||
				   (rotated[3]==all[one1] && rotated[4]==all[one2]) ){
					rotated = hrot.rotateNegX(rotated);
					rotated = hrot.rotateNegY(rotated);
					PatternB(rotated,newsubs_in);
					return true;
				}
				if((rotated[4]==all[one1] && rotated[1]==all[one2]) ||
				   (rotated[1]==all[one1] && rotated[4]==all[one2]) ){
					rotated = hrot.rotatePosZ(rotated);
					rotated = hrot.rotatePosY(rotated);
					PatternB(rotated,newsubs_in);
					return true;
				}
				PatternB(rotated,newsubs_in);
				return true;
			}
		}
		else if(total==6){
			//Pattern D is applied when one node present 3 connections
			//If this ain't the case, pattern C o E must be checked.
			bool D = false;
			int connect3=0;
			for (unsigned int i=0;i<4;i++){
				if(number[i]==3){
					D = true;
					connect3=i;
					break;
				}
			}
			if(D){
				rotated = hrot.rotate(all,in[connect3]);
				PatternD(rotated,newsubs_in,newsubs_out);
				return true;
			}
			else{
				int pivote1=0,pivote2=0;
				int one1=0,one2=0;
				for (unsigned int i=0;i<4;i++){
					if(number[i]==2){
						if(pivote1==0)
							pivote1=in[i];
						else{
							pivote2=in[i];
						}
					}
					else{
						if(one1==0)
							one1=in[i];
						else
							one2=in[i];
					}
				}
				
				//rotate to put pivote1 in 0
				rotated = hrot.rotate(all,pivote1);
				if(rotated[4]==all[pivote2]){
					rotated = hrot.rotatePosZ(rotated);
				}
				else if(rotated[1]==all[pivote2]){
					rotated = hrot.rotateNegY(rotated);
				}
				if(rotated[4]==all[one1] || rotated[4]==all[one2]){
					PatternE(rotated,newsubs_in);
					return true;
				}
				else{
					PatternC(rotated,newsubs_in);
					return true;
				}
			}
		}
		else{
			std::cerr << "Pattern not found for this configuration:\nin nodes:";
			for(unsigned int i=0;i<in.size();i++)
				std::cerr << " " << in[i];
		}
		
		return false;
	}
	
	vector<unsigned int> BoundaryTemplate4::getEdges(int p){
		vector<unsigned int> edges (3,0);
		if(p==0){
			edges[0]=1;
			edges[1]=3;
			edges[2]=4;
		}
		else if(p==1){
			edges[0]=0;
			edges[1]=2;
			edges[2]=5;
		}
		else if(p==2){
			edges[0]=1;
			edges[1]=3;
			edges[2]=6;
		}
		else if(p==3){
			edges[0]=2;
			edges[1]=0;
			edges[2]=7;
		}
		else if(p==4){
			edges[0]=0;
			edges[1]=5;
			edges[2]=7;
		}
		else if(p==5){
			edges[0]=1;
			edges[1]=4;
			edges[2]=6;
		}
		else if(p==6){
			edges[0]=2;
			edges[1]=7;
			edges[2]=5;
		}
		else if(p==7){
			edges[0]=3;
			edges[1]=6;
			edges[2]=4;
		}
		return edges;
	}
	
	//Pattern G in paper
	void BoundaryTemplate4::PatternA(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(1);
		eles.push_back(all);
		
	}
	
	
	//Pattern C in paper
	void BoundaryTemplate4::PatternB(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(4);
		vector<unsigned int> ele1(5,0);
		vector<unsigned int> ele2(5,0);
		vector<unsigned int> ele3(4,0);
		vector<unsigned int> ele4(4,0);
		
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
		
		ele3[0] = all[6];
		ele3[1] = all[5];
		ele3[2] = all[7];
		ele3[3] = all[2];
		
		ele4[0] = all[4];
		ele4[1] = all[7];
		ele4[2] = all[5];
		ele4[3] = all[2];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		eles.push_back(ele4);
		
	}
	
	//Pattern E in paper
	void BoundaryTemplate4::PatternC(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(4);
		
		vector<unsigned int> ele1(5,0);
		vector<unsigned int> ele2(5,0);
		vector<unsigned int> ele3(4,0);
		vector<unsigned int> ele4(4,0);
		
		ele1[0] = all[0];
		ele1[1] = all[4];
		ele1[2] = all[5];
		ele1[3] = all[1];
		ele1[4] = all[2];
		
		ele2[0] = all[7];
		ele2[1] = all[3];
		ele2[2] = all[2];
		ele2[3] = all[6];
		ele2[4] = all[4];
		
		ele3[0] = all[0];
		ele3[1] = all[2];
		ele3[2] = all[3];
		ele3[3] = all[4];
		
		ele4[0] = all[4];
		ele4[1] = all[5];
		ele4[2] = all[2];
		ele4[3] = all[6];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		eles.push_back(ele4);
		
	}
	
	//Pattern D in paper
	void BoundaryTemplate4::PatternD(vector<unsigned int> &all, 
									 vector<vector<unsigned int> > &newsubs_in,
									 vector<vector<unsigned int> > &newsubs_out){
		
		newsubs_in.reserve(4);
		
		vector<unsigned int> ele1(4,0);
		vector<unsigned int> ele2(4,0);
		vector<unsigned int> ele3(4,0);
		vector<unsigned int> ele4(4,0);
		
		ele1[0] = all[1];
		ele1[1] = all[2];
		ele1[2] = all[0];
		ele1[3] = all[5];
		
		ele2[0] = all[3];
		ele2[1] = all[0];
		ele2[2] = all[2];
		ele2[3] = all[7];
		
		ele3[0] = all[4];
		ele3[1] = all[7];
		ele3[2] = all[5];
		ele3[3] = all[0];
		
		ele4[0] = all[7];
		ele4[1] = all[2];
		ele4[2] = all[5];
		ele4[3] = all[0];
		
		newsubs_in.push_back(ele1);
		newsubs_in.push_back(ele2);
		newsubs_in.push_back(ele3);
		newsubs_in.push_back(ele4);
		
		//managing outside elements
		
		newsubs_out.reserve(1);
		vector<unsigned int> ele5(4,0);
		ele5[0] = all[2];
		ele5[1] = all[7];
		ele5[2] = all[5];
		ele5[3] = all[6];
		
		newsubs_out.push_back(ele5);
		
	}
	
	//Pattern  F in paper
	void BoundaryTemplate4::PatternE(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(4);
		
		vector<unsigned int> ele1(5,0);
		vector<unsigned int> ele2(5,0);
		vector<unsigned int> ele3(4,0);
		vector<unsigned int> ele4(4,0);
		
		ele1[0] = all[0];
		ele1[1] = all[4];
		ele1[2] = all[5];
		ele1[3] = all[1];
		ele1[4] = all[7];
		
		ele2[0] = all[2];
		ele2[1] = all[6];
		ele2[2] = all[7];
		ele2[3] = all[3];
		ele2[4] = all[1];
		
		ele3[0] = all[1];
		ele3[1] = all[7];
		ele3[2] = all[5];
		ele3[3] = all[6];
		
		ele4[0] = all[0];
		ele4[1] = all[3];
		ele4[2] = all[7];
		ele4[3] = all[1];
		
		eles.push_back(ele1);
		eles.push_back(ele2);
		eles.push_back(ele3);
		eles.push_back(ele4);
		
	}
	
	//Pattern B in paper
	void BoundaryTemplate4::PatternF(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(2);
		vector<unsigned int> pri1(6,0),pri2(6,0);
		
		pri1[0]=all[0];
		pri1[1]=all[4];
		pri1[2]=all[1];
		pri1[3]=all[3];
		pri1[4]=all[7];
		pri1[5]=all[2];
		
		pri2[0]=all[5];
		pri2[1]=all[1];
		pri2[2]=all[4];
		pri2[3]=all[6];
		pri2[4]=all[2];
		pri2[5]=all[7];
		
		eles.push_back(pri1);
		eles.push_back(pri2);
		
	}
	
	//Pattern A in paper
	void BoundaryTemplate4::PatternG(vector<unsigned int> &all, 
								vector<vector<unsigned int> > &eles){
		
		eles.reserve(5);
		vector<unsigned int> tet1(4,0),tet2(4,0),tet3(4,0),tet4(4,0),tet5(4,0);
		
		tet1[0]=all[0];
		tet1[1]=all[1];
		tet1[2]=all[3];
		tet1[3]=all[4];
		
		tet2[0]=all[2];
		tet2[1]=all[3];
		tet2[2]=all[1];
		tet2[3]=all[6];
		
		tet3[0]=all[5];
		tet3[1]=all[4];
		tet3[2]=all[6];
		tet3[3]=all[1];
		
		tet4[0]=all[7];
		tet4[1]=all[6];
		tet4[2]=all[4];
		tet4[3]=all[3];
		
		tet5[0]=all[4];
		tet5[1]=all[3];
		tet5[2]=all[6];
		tet5[3]=all[1];
		
		eles.push_back(tet1);
		eles.push_back(tet2);
		eles.push_back(tet3);
		eles.push_back(tet4);
		eles.push_back(tet5);
		
	}
	
	
	
	void BoundaryTemplate4::swap(vector<unsigned int> &vec, int pos1, int pos2){
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

