#ifndef ViewM3d_h
#define ViewM3d_h 1

#include <fstream>
#include "../geometry/FaceContainer.h"
#include "../geometry/PointM3d.h"
#include "EnhancedElement.h"
#include "../read_write/ReadM3d.h"

using namespace std;

class ViewM3d{
	
  public:
	
	ViewM3d();
	
	virtual ~ViewM3d();
	
	virtual bool execute(char *input, const bool &edge);
	
  protected:
	
	virtual bool yesOrNo(string &question);
	
	virtual bool askRemove(FaceContainer *tfc);// list<Point> &tpoints, list<Face> &tfaces); 
	
	virtual void removeFaces(int &axe, double start, double end,
							 FaceContainer *tfc);
							 //list<Point> &tpoints, list<Face> &tfaces);
	
	virtual void clean(list<Point> &tpoints, list<Face> &tfaces, 
					   FaceContainer *tfc);
	
	virtual void cleanUnusedNodes(list<Point> &tpoints, 
								  list<Face> &tfaces,
								  FaceContainer *tfc);
	
	virtual int askAxe();
	
	virtual double readDouble();
	
	virtual bool newTmpFile(string &stmp,ofstream &output);
	
	virtual bool readData(char *name);
	
	virtual void headGeom(ofstream &output, int np, int nf);
	
	virtual void dataGeom(ofstream &output, list<Point> &tpoints, 
						  list<Face> &tfaces);
	
	virtual void printBbox(); 
	
  protected:
	
	char op;
	vector<Point> points;
	FaceContainer *all_faces;
	vector<EnhancedElement> elements;
	Point min, max;
};

#endif
