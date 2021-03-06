#include "ViewM3d.h"

ViewM3d::ViewM3d(){
	op='\0';
	all_faces = new FaceContainer();
}

ViewM3d::~ViewM3d(){
	delete all_faces;
}

bool ViewM3d::readData(char *name){
	ReadM3d *rm;
	vector<Element *> gelements;
	vector<PointM3d> gpoints;
	
	//read point and element data
	rm = new ReadM3d(name);
	rm->execute(gpoints,gelements);
	
	if ((int)gpoints.size()<3) {
		cout << "cannot display a mesh with less than 3 nodes\n";
		return false;
	}
	
	points.reserve(gpoints.size());
	
	min[0] = max[0] = gpoints[0][0];
	min[1] = max[1] = gpoints[0][1];
	min[2] = max[2] = gpoints[0][2];
	
	for (int i=0; i<(int)gpoints.size(); i++){
		
		double x = gpoints[i][0];
		double y = gpoints[i][1];
		double z = gpoints[i][2];
		
		points.push_back(Point (x,y,z,i));//gpoints[i].getIndex()));
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
	
	if ((int)gelements.size()<1) {
		cout << "mesh has no elements: nothing to display\n";
		return false;
	}
	
	elements.reserve(gelements.size());
	
	//save faces with neigbhoring information
	for(int i=0; i<(int)gelements.size(); i++){
		//An EnhancedElement is an Element with optimizations for
		//removing and visualizing.
		EnhancedElement ee(gelements[i]);
		ee.computeBbox(points);
		
		//get the element face index points and initialize it
		for(int j=0;j<gelements[i]->numberOfFaces();j++){
			vector<int> fpts = gelements[i]->getFacePoints(j);
			int fid = all_faces->addFace(new Face(fpts));
			all_faces->getFace(fid)->addElement(i);
			//add the face to the EnhancedElement
			ee.addFace(fid);
		}
		//add the enhanced element to its vector
		elements.push_back(ee);
	}    
	
	return true;
}


bool ViewM3d::execute(char *input, const bool &edge){
	string command, file, question;
	int sys=0;
	bool cont = true;
	list<Point> tmppoints;
	list<Face> tmpfaces;
	
	if (!readData(input)) {
		return false;
	}
	
	//detect surface elements (elements with at least one face
	//not shared by two elements).
	//this method will change the color of surface faces.
	for(int i=0; i<(int)elements.size(); i++){
		elements[i].detectOnSurface(all_faces);
	}
	
	question = "continue with visualization\0";
	
	while(cont){
		
		ofstream fgeom;
		//the instruction that will be executed.
		//-b is for setting the background color to white
		command = "geomview -b 1 1 1 \0";
		
		if(!newTmpFile(file,fgeom)){
			cout << "  Error: can't generate a tmp file for visualization\n";
			delete all_faces;
			return false;
		}
		FaceContainer *tfc = new FaceContainer();
		
		//askRemove returns true if the user removed some
		//faces. In that case, temporal face container (tfp)
		//will be employed, instead of all face container
		//(all_faces), to creat the list of faces to display.
		if (askRemove(tfc)) {
			if (!edge) {
				clean(tmppoints,tmpfaces,tfc);
			}
			else {
				cleanUnusedNodes(tmppoints,tmpfaces,tfc);
			}			
		}
		else {
			if (!edge) {
				clean(tmppoints,tmpfaces,all_faces);
			}
			else {
				cleanUnusedNodes(tmppoints,tmpfaces,all_faces);
			}	
		}
		
		//the tfc isn't needed anymore.
		delete tfc;
		
		headGeom(fgeom,tmppoints.size(),tmpfaces.size());
		dataGeom(fgeom,tmppoints,tmpfaces);
				
		fgeom.close();
		
		//execute geomview
		command+=file;
		sys=system(command.c_str());
		
		if(sys!=0){
			delete all_faces;
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
	}
	
	return true;
}

bool ViewM3d::askRemove(FaceContainer *tfc){//list<Point> &tpoints, list<Face> &tfaces){
	int axe;
	bool removed = false;
	string question;
	double start=0,end=0;
	
	question = "remove some faces\0";
	removed = yesOrNo(question);
	if(removed){
		printBbox();
		axe = askAxe();
		cout << "indicate range for elements to be viewed\n";
		cout << "(starting) "; 
		start = readDouble();
		cout << "(ending) ";
		end = readDouble();
		removeFaces(axe,start,end,tfc);//tpoints,tfaces);
	}
	return removed;
}


void ViewM3d::printBbox(){
	cout << "the geometry Bounding box is:\n";
	cout << "X in [" << min[0] << "," << max[0] << "]\n";
	cout << "Y in [" << min[1] << "," << max[1] << "]\n";
	cout << "Z in [" << min[2] << "," << max[2] << "]\n";
}

//save in tfaces only the faces that belong to one element from the given
//FaceContainer. Then it only save in tpoints the points used by the
//selected faces.
void ViewM3d::clean(list<Point> &tpoints, list<Face> &tfaces, 
					FaceContainer *tfc){
	
	vector<int> ptsidx (points.size(),-1);
	int usedpts = 0;
	for(int i=0;i<tfc->length();i++){
		if(tfc->getFace(i)->numberOfElements()!=1)
			continue;
		vector<int> fpts = tfc->getFace(i)->getPoints();
		for(int j=0;j<fpts.size();j++){
			if(ptsidx[fpts[j]]==-1){
				tpoints.push_back(points[fpts[j]]);
				ptsidx[fpts[j]]=usedpts;
				fpts[j]=usedpts++;
			}
			else{
				fpts[j]=ptsidx[fpts[j]];
			}
		}
		Face f(fpts);
		f.setColor(tfc->getFace(i)->getColor());
		tfaces.push_back(f);
	}
}

void ViewM3d::cleanUnusedNodes(list<Point> &tpoints,
							   list<Face> &tfaces,
							   FaceContainer *tfc){
	
	vector<int> ptsidx (points.size(),-1);
	int usedpts = 0;
	for(int i=0;i<tfc->length();i++){
		vector<int> fpts = tfc->getFace(i)->getPoints();
		for(int j=0;j<fpts.size();j++){
			if(ptsidx[fpts[j]]==-1){
				tpoints.push_back(points[fpts[j]]);
				ptsidx[fpts[j]]=usedpts;
				fpts[j]=usedpts++;
			}
			else{
				fpts[j]=ptsidx[fpts[j]];
			}
		}
		Face f(fpts);
		f.setColor(tfc->getFace(i)->getColor());
		tfaces.push_back(f);
	}
}


void ViewM3d::removeFaces(int &axe, double start, double end,
						  FaceContainer *tfc){
						  //list<Point> &tpoints, list<Face> &tfaces){
	
	cout << "removing elements outside range [";
	cout << start << "," << end <<"] in axis " << axe << " ... ";
	
	//detect elements outside the range to remove them
	for(int i=0;i<elements.size();i++){
		elements[i].remove(axe,start,end);
	}
	cout << "done\n";
	
	//FaceContainer *tfc = new FaceContainer();
	for(int i=0;i<elements.size();i++){
		if(elements[i].wasRemoved())
			continue;
		list<int>::iterator iter;
		list<int> fele = elements[i].getFaces();
		for(iter=fele.begin();iter!=fele.end();iter++){
			vector<int> tfp = all_faces->getFace(*iter)->getPoints();
			Face *f = new Face(tfp);
			f->addElement(i);
			f->setColor(all_faces->getFace(*iter)->getColor());
			tfc->addFace(f);
		}
	}
	//clean(tpoints,tfaces,tfc);
}

bool ViewM3d::yesOrNo(string &question){
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

int ViewM3d::askAxe(){
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

double ViewM3d::readDouble(){
	double coord;
	cout << "indicate coord: ";
	cin >> coord;
	return coord;
}

void ViewM3d::headGeom(ofstream &output, int np, int nf){
	
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

void ViewM3d::dataGeom(ofstream &output, list<Point> &tpoints, 
					   list<Face> &tfaces){
	
	list<Point>::iterator iterp;
	list<Face>::iterator iterf;
	//print each point
	for(iterp=tpoints.begin();iterp!=tpoints.end();iterp++){
		Point p = *iterp;
		output << p[0] << " ";
		output << p[1] << " ";
		output << p[2] << "\n";
		//cout << p << endl;
	}
	
	output << endl;
	
	//print each face
	for(iterf=tfaces.begin();iterf!=tfaces.end();iterf++){
		output << *iterf << " ";
		output << (*iterf).getColor() << endl;
	}
	//output << "}})\n";
}

bool ViewM3d::newTmpFile(string &stmp,ofstream &output){
    char tmp [16];
    int fd;
	
    strcpy(tmp,"geomviewXXXXXX\0");
    
    fd=mkstemp(tmp);
    
    if(fd==-1){
		cout << "  Error: Can't create a tmp file. Try saving";
		cout << " before viewing.\n";
		return false;
    }
    
    stmp+=tmp;
    output.open(tmp);
    return true;
}
