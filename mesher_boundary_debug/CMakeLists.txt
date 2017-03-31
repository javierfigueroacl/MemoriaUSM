# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx".  The extensions are automatically found.
add_executable (mesher_boundary

../mesher_services/Coord3D.o
../mesher_services/Vector3D.o
../mesher_services/VPoint3D.o
../mesher_services/Pair.o
../mesher_services/Edge.o
../mesher_services/EdgeContainer.o
../mesher_services/Triangle.o
../mesher_services/Mesh.o


#classes
Main MeshPoint Point3D TriMesh EnhancedElement HexRotation
BoundaryTemplate1 BoundaryTemplate2 BoundaryTemplate3 BoundaryTemplate4
BoundaryTemplate5 BoundaryTemplate6 BoundaryTemplate7
BoundaryTemplatePyramid
BoundaryTemplatePrism
SurfTemplate1 SurfTemplate2 SurfTemplate3 SurfTemplate4
SurfTemplate5 SurfTemplate6 SurfTemplate7
Mesher GridMesher
)
