#Flags: 
CC=g++
ALL = Coord3D.o Vector3D.o VPoint3D.o Pair.o Edge.o EdgeContainer.o Triangle.o Mesh.o

all: *.cpp *.h
	make $(ALL)

Coord3D.o: Coord3D.cpp Coord3D.h
	$(CC) -g -c Coord3D.cpp

Vector3D.o: Vector3D.cpp Vector3D.h Coord3D.o
	$(CC) -g -c Vector3D.cpp

VPoint3D.o: VPoint3D.cpp VPoint3D.h Coord3D.o Vector3D.o
	$(CC) -g -c VPoint3D.cpp

Pair.o: Pair.cpp Pair.h
	$(CC) -g -c Pair.cpp

Edge.o: Edge.cpp Edge.h
	$(CC) -g -c Edge.cpp

EdgeContainer.o: EdgeContainer.cpp EdgeContainer.h Edge.o Pair.o
	$(CC) -g -c EdgeContainer.cpp

Triangle.o: Triangle.cpp Triangle.h VPoint3D.o
	$(CC) -g -c Triangle.cpp

Mesh.o: Mesh.cpp Mesh.h Triangle.o EdgeContainer.o
	$(CC) -g -c Mesh.cpp

clean:
	rm *.o
