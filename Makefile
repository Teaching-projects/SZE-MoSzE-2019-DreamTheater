
OBJS=main.o File.o Directory.o Filesystem.o
CXXFLAGS = -g -std=c++11

all: $(OBJS)
	g++ -o terminal $(OBJS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
	
File.o: File.cpp
	g++ -c File.cpp $(CXXFLAGS)

Directory.o: Directory.cpp
	g++ -c Directory.cpp $(CXXFLAGS)

Filesystem.o: Filesystem.cpp
	g++ -c Filesystem.cpp $(CXXFLAGS)
	
clean:
	rm -f *.o