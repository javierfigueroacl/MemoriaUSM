#include "Main.h"

using namespace std;

void emsg(){
	cout << "use: ./viewer -o file.m3d\n";
	cout << " where -o can be:\n";
	cout << "  -d: for mdl\n";
	cout << "  -m: for m3d\n";
}

int main(int argc,char** argv){
	string op;
	
	if(argc!=3){
		emsg();
		return 1;
	}
	
	if(argv[1][1]=='m'){
		ViewM3d vm;
		if (strlen(argv[1])==3 && argv[1][2]=='e') {
			vm.execute(argv[2],true);
		}
		else{
			vm.execute(argv[2],false);
		}
	}
	else if(argv[1][1]=='d'){
		ViewMdl vm;
		vm.execute(argv[2]);
	}
	else{
		emsg();
		return 1;
	}
	
	return 0;
}

