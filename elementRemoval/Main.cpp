#ifndef Main_h
#define Main_h 1

#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <list>

#include "../read_write/ReadM3d.h"
#include "../read_write/WriteM3d.h"

using namespace std;

//-------------------------------------------------------------------
//-------------------------------------------------------------------

bool ReadSurf(string name, vector<vector<unsigned int> > &faces,
			  vector<vector<double> > &points){
	
	char word [256];
	int np, nf, npf,pi;
	double x,y,z;
	
	FILE *file = fopen(name.c_str(),"r");
	
	if (file==NULL) {
		cout << "File " << name << " doesn't exist\n";
		return false;
	}
	
	//read number of nodes
	while(true){
		if(std::fscanf(file,"%s",word)==EOF){
			fclose(file);
			return false;
		}
		if(!strcmp(word,"OFF\0"))
			break;
	}
	
	fscanf(file,"%i",&np);
	fscanf(file,"%i",&nf);
	fgets(word,256,file);

	
	if(np<=0) {
		return false;
	}
	
	//read each node
	points.reserve(np);
	
	for (int i=0; i<np; i++){
		vector<double> thispoint;
		thispoint.reserve(3);
		
		fscanf(file,"%s",word);
		thispoint.push_back(atof(word));
		
		fscanf(file,"%s",word);
		thispoint.push_back(atof(word));
		
		fscanf(file,"%s",word);
		thispoint.push_back(atof(word));
		
		fgets(word,256,file);
		
		points.push_back(thispoint);
	}
	
	//read the faces
	faces.reserve(nf);	
	
	for (int i=0; i<nf; i++){
		
		fscanf(file,"%i",&npf);
		vector<unsigned int> indexes;
		indexes.reserve(npf);
		
		for(int j=0;j<npf;j++){
			fscanf(file,"%i",&pi);
			indexes.push_back(pi);
		}
		fgets(word,256,file);
		faces.push_back(indexes);
	}
	fclose(file);

	
	return true;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

bool ReadHex(string name, vector<vector<double> > &points){
	
	char word [256];
	int cant;
	double x,y,z;
	
	FILE *file = fopen(name.c_str(),"r");
	
	if (file==NULL) {
		cout << "File " << name << " doesn't exist\n";
		return false;
	}
	
	//read number of nodes
	while(true){
		if(std::fscanf(file,"%s",word)==EOF){
			fclose(file);
			return false;
		}
		if(!strcmp(word,"n_regions\0"))
			break;
	}
	fscanf(file,"%i",&cant);
	
	if(cant<=0)
		return false;
	
	//read each node
	points.reserve(cant*2);
	
	for( int i=0;i<cant*2;i++){
		vector<double> thispoint;
		thispoint.reserve(3);
		
		fscanf(file,"%s",word);
		thispoint.push_back(atof(word));
		
		fscanf(file,"%s",word);
		thispoint.push_back(atof(word));
		
		fscanf(file,"%s",word);
		thispoint.push_back(atof(word));
		
		points.push_back(thispoint);
	}
	
	fclose(file);
	return true;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

void LinkNodesAndElements(vector<Element *> &elements,
					   vector<list<unsigned int> > &links){
	
	for (unsigned int i=0; i<elements.size(); i++) {
		vector<int> e_idx = elements[i]->getPoints();
		for (unsigned int j=0; j<e_idx.size(); j++) {
			links[e_idx[j]].push_back(i);
		}
	}
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

int main(int argc,char** argv){
	
	vector<vector<double> > hexs;
	vector<list<unsigned int> > links;
    
    vector<PointM3d> vm_points;
    vector<Element *> vm_elements, outelements;
	
	if (argc!=4) {
		cout << "use: ./removefaces input.m3d hexas.txt output\n";
		return 1;
	}
	
	//read volume mesh
	ReadM3d rm(argv[1]);
    rm.execute(vm_points,vm_elements);
	
	//read hex coords.
	ReadHex(argv[2],hexs);
	
	//link faces to nodes
	links.reserve(vm_points.size());
	for (unsigned int i=0; i<vm_points.size(); i++) {
		list<unsigned int> void_list;
		links.push_back(void_list);
	}
	
	LinkNodesAndElements(vm_elements,links);

	
	//label "removed" all faces with a node that
	//intersects at least one hexahedrons.
	
	vector<bool> elementsIO (vm_elements.size(),false);
    
    bool update_mesh = false;
	
	for (unsigned int i=0; i<hexs.size(); i+=2) {
		for (unsigned int j=0; j<vm_points.size(); j++) {

			if (vm_points[j][0]<hexs[i][0] ||
				hexs[i+1][0]<vm_points[j][0]) {
				continue;
			}
			if (vm_points[j][1]<hexs[i][1] ||
				hexs[i+1][1]<vm_points[j][1]) {
				continue;
			}
			if (vm_points[j][2]<hexs[i][2] ||
				hexs[i+1][2]<vm_points[j][2]) {
				continue;
			}
            
			
            update_mesh = true;
            
			//there is intersection
			list<unsigned int>::iterator iter;
			list<unsigned int> to_remove = links[j];
			for (iter=to_remove.begin(); iter!=to_remove.end(); iter++) {
                elementsIO[*iter] = true;
			}
			
		}
	}
	
	if (update_mesh) {
		cout << "removed elements:\n";
		for (unsigned int i=0; i<elementsIO.size(); i++) {
			if (!elementsIO[i]) {
				outelements.push_back(vm_elements[i]);
			}
			else {
				vector<int> e_pts = vm_elements[i]->getPoints();
				cout << e_pts.size();
				for (int j=0; j<e_pts.size(); j++) {
					cout << " " << e_pts[j];
				}
				cout << "\n";
			}
			
		}
		
		//write output file (with unused nodes).
		WriteM3d wm(argv[3]);
        wm.execute(vm_points,outelements);
	}
	else {
		cout << "no elements to remove\n";
	}

	return 0;
}

#endif
