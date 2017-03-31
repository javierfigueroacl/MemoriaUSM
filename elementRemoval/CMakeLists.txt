# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx".  The extensions are automatically found.

add_executable (remove_elements

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/WriteM3d.o ../read_write/M3dPrinter.o
../read_write/ReadM3d.o

Main
)


