# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx".  The extensions are automatically found.

add_executable (viewer

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o ../geometry/FaceContainer.o 
../geometry/Face.o

../read_write/ReadM3d.o  ../read_write/ReadMdl.o 

#../Math/Matrix.o ../Math/Polynom.o ../Math/PolyMatrix.o ../Math/Vector.o

Main ViewM3d ViewMdl EnhancedElement
)


