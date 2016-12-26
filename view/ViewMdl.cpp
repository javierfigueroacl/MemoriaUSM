#include "ViewMdl.h"

ViewMdl::ViewMdl(){
	op='\0';
	fc = new FaceContainer();
}

ViewMdl::~ViewMdl(){
	delete fc;
}

bool ViewMdl::readData(char *name){
	ReadMdl *rm;
	
	//read point and element data
	rm = new ReadMdl(name);
	rm->execute(points,fc);
	//this vector will hold the information of removed
	//faces. This is to avoid creating an enhancedFace object
	//just to know this info.
	removedfaces.assign(fc->length(),false);
	
	if ((int)points.size()<3) {
		cout << "cannot display a mesh with less than 3 nodes\n";
		return false;
	}
	
	if (fc->length()<1) {
		cout << "mesh has no faces: nothing to display\n";
		return false;
	}
	
	min[0] = max[0] = points[0][0];
	min[1] = max[1] = points[0][1];
	min[2] = max[2] = points[0][2];
	
	for(int i=1;i<points.size();i++){
		
		double x = points[i][0];
		double y = points[i][1];
		double z = points[i][2];
		
		//compute Bbox
		if(min[0]>x)
			min[0]=x;
		if(max[0]<x)
			max[0]=x;
		if(min[1]>y)
			min[1]=y;
		if(max[1]<y)
			max[1]=y;
		if(min[2]>z)
			min[2]=z;
		if(max[2]<z)
			max[2]=z;
	}
	
	return true;
}


bool ViewMdl::execute(char *input){
	string command,file,question;
	int sys=0;
	bool cont = true;
	list<Point> tmppoints;
	list<Face> tmpfaces;
	//FaceContainer *tmpf;
	
	if (!readData(input)) {
		return false;
	}
	
	question = "continue with visualization\0";
	
	while(cont){
		
		ofstream fgeom;
		//the instruction that will be executed.
		command = "geomview -b 1 1 1 \0";
		
		if(!newTmpFile(file,fgeom)){
			cout << "  Error: can't generate a tmp file for visualization\n";
			delete fc;
			return false;
		}
		
		askRemove(tmppoints,tmpfaces);
		
		headGeom(fgeom,tmppoints.size(),(int)tmpfaces.size());
		dataGeom(fgeom,tmppoints,tmpfaces);
		
		fgeom.close();
		
		//execute geomview
		command+=file;
		sys=system(command.c_str());
		
		if(sys!=0){
			delete fc;
			return false;
		}
		
		command.clear();
		command = "rm \0";
		command += file;
		system(command.c_str());
		cont = yesOrNo(question);
		command.clear();
		file.clear();
		
		tmpfaces.clear();
		tmppoints.clear();
		//clear removing information
		removedfaces.clear();
		removedfaces.assign(fc->length(),false);
		
	}
	
	return true;
}

bool ViewMdl::askRemove(list<Point> &tpoints, list<Face> &tfaces){
	int axe;
	bool removed = false;
	string question;
	double start=0,end=0;
	
	question = "remove some faces\0";
	removed = yesOrNo(question);
	if(removed){
		printBbox();
		axe = askAxe();
		cout << "indicate range for faces to be viewed\n";
		cout << "(starting) "; 
		start = readDouble();
		cout << "(ending) ";
		end = readDouble();
		removeFaces(axe,start,end,tpoints,tfaces);
	}
	else{
		clean(tpoints,tfaces,fc);
	}
	return removed;
}

void ViewMdl::printBbox(){
	cout << "the geometry Bounding box is:\n";
	cout << "X in [" << min[0] << "," << max[0] << "]\n";
	cout << "Y in [" << min[1] << "," << max[1] << "]\n";
	cout << "Z in [" << min[2] << "," << max[2] << "]\n";
}

//save in tfaces only the faces that belong to one element from the given
//FaceContainer. Then it only save in tpoints the points used by the
//selected faces.
void ViewMdl::clean(list<Point> &tpoints, list<Face> &tfaces, 
					FaceContainer *tfc){
	
	vector<int> ptsidx (points.size(),-1);
	int usedpts = 0;
	for(int i=0;i<tfc->length();i++){
		vector<int> fpts = tfc->getFace(i)->getPoints();
		vector<int> nfpts (fpts.size(),-1);
		for(int j=0;j<fpts.size();j++){
			if(ptsidx[fpts[j]]==-1){
				tpoints.push_back(points[fpts[j]]);
				ptsidx[fpts[j]]=usedpts;
				nfpts[j]=usedpts++;
			}
			else{
				nfpts[j]=ptsidx[fpts[j]];
			}
		}
		Face f(nfpts);
		tfaces.push_back(f);
	}
}

void ViewMdl::removeFaces(int &axe, double start, double end,
						  list<Point> &tpoints, list<Face> &tfaces){
	
	cout << "removing faces outside range [";
	cout << start << "," << end <<"] in axis " << axe << " ... ";
	
	FaceContainer *tfc = new FaceContainer();
	//detect faces outside the range to remove them
	for (int i=0; i<fc->length(); i++){
		vector<int> fpts = fc->getFace(i)->getPoints();
		for (int j=0; j<(int)fpts.size(); j++) {
			if (points[fpts[j]][axe]<start || points[fpts[j]][axe]>end) {
				removedfaces[i] = true;
				break;
			}
		}
		if (!removedfaces[i]) {
			Face *f = new Face(fpts);
			tfc->addFace(f);
		}
	}
	clean(tpoints,tfaces,tfc);
	cout << "done\n";
}


bool ViewMdl::yesOrNo(string &question){
	char cont;
	cout << question << "[y/n]? ";
	cin >> cont;
	while(cont!='y' && cont!='n'){  
		cout << question << "[y/n]? ";
		cin >> cont;
	}
	if(cont=='y')
		return true;
	return false;
}

int ViewMdl::askAxe(){
	char axe;
	cout << "indicate axe[x/y/z]: ";
	cin >> axe;
	while(true){
		if(axe=='x')
			return 0;
		else if(axe=='y')
			return 1;
		else if(axe=='z')
			return 2;
		cout << "invalid. indicate axe[x/y/z]: ";
		cin >> axe;
	}
}

double ViewMdl::readDouble(){
	double coord;
	cout << "indicate coord: ";
	cin >> coord;
	return coord;
}

void ViewMdl::headGeom(ofstream &output, int np, int nf){
	
	/*bool transparent = false;
	string question;
	output << "(geometry main { : foo })\n";
	output << "(read geometry { define foo {\n";
	output << "INST\n";
	output << "geom";
	output << " appearance {\n";
	output << "   +face\n";
	output << "   +edge\n";
	question = "view transparent\0";
    transparent = yesOrNo(question);
	if(transparent)
		output << "   +transparent\n";
	output << "   -vect\n";
	output << "   +concave\n";
	output << "   shading flat\n";
	output << " }\n";*/
	output << "OFF\n";
	//print number of points, faces and edges.
	output << np << " " << nf << " 0\n\n";
}

void ViewMdl::dataGeom(ofstream &output, list<Point> &tpoints, 
					   list<Face> &tfaces){
	
	list<Point>::iterator iterp;
	list<Face>::iterator iterf;
	//print each point
	for(iterp=tpoints.begin();iterp!=tpoints.end();iterp++){
		Point p = *iterp;
		output << p[0] << " ";
		output << p[1] << " ";
		output << p[2] << "\n";
	}
	
	output << endl;
	
	//print each face
	for(iterf=tfaces.begin();iterf!=tfaces.end();iterf++){
		output << *iterf << endl;
	}
	//output << "}})\n";
}

bool ViewMdl::newTmpFile(string &stmp,ofstream &output){
    char tmp [16];
    int fd;
	
    strcpy(tmp,"geomviewXXXXXX\0");
    
    fd=mkstemp(tmp);
    
    if(fd==-1){
		cout << "  Error: Can't create a tmp file. Try saving before";
		cout << " viewing.\n";
		return false;
    }
    
    stmp+=tmp;
    output.open(tmp);
    return true;
}
