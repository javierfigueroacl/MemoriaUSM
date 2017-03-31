#include "Mesher.h"
#include "TriMesh.h"
#include "FEMesh.h"
#include "CoteMarek.h"
#include <string>
#include <cctype>
#include <time.h>

void endMsg(){
	std::cout << "use: ./mesher input1.mdl input2.mdl ref_level output\n";
	std::cout << "where:\n";
	std::cout << "  input.mdl is the surface input mesh in mdl format\n";
	std::cout << "  ref_level is the refinement level\n";
	std::cout << "  output is the name of the output file without extension.\n";
}

void printTime(double nseconds){
	int th,tm,ts;
	th = (int)nseconds/3600;
	tm = ((int)nseconds%3600)/60;
	ts = ((int)nseconds%3600)%60;
	if(th<10) 
		std::cout << "0";
	std::cout << th << ":";
	if(tm<10)
		std::cout << "0";
	std::cout << tm << ":";
	if(ts<10)
		std::cout << "0";
	std::cout << ts << std::endl;
}

int main(int argc,char** argv){

	const int n_meshes = 2;
	
	if(argc!=n_meshes+3){
		endMsg();
		return 1;
	}
	
	time_t t1,t2;
	time(&t1);

	
	Clobscode::CoteMarek marek;
	marek.setNumberOfInputs(n_meshes);
	std::vector<Clobscode::TriMesh> inputs;
	inputs.reserve(n_meshes);
	
	for (unsigned int i=1; i<(n_meshes+1); i++) {
		if (!marek.ReadInputMesh(argv[i],inputs)) {
			std::cerr << "couldn't read file " << argv[i] << std::endl;
			return 1;
		}
	}
	
	/*
	 std::vector<double> xs(20,0),ys(20,0),zs(20,0);
	 xs[0]=ys[0]=zs[0]=-110;
	 for (unsigned int i=1; i<19; i++) {
	 xs[i]=ys[i]=zs[i]=xs[i-1]+10;
	 }
	 xs[19]=ys[19]=zs[19]=110;
	 */
	
	
	Clobscode::Mesher mesher(n_meshes);	
	
	Clobscode::FEMesh output = mesher.generateMesh(&marek, 
									Clobscode::CoteMarek::CheckIfPointInMesh,
									Clobscode::CoteMarek::GetProjection,
									inputs,std::atoi(argv[n_meshes+1]));
									//xs,ys,zs);

	std::cout << "  mesh successfully generated\n";
	marek.WriteOutputMesh(argv[n_meshes+2],output);

	
	time(&t2);
	std::cout << "  All done in ";
	printTime(difftime(t2,t1));

	return 0;
}

