all: a2

a2: main.o TestView.o TestControl.o Client.o PhotoGram.o AlbumArray.o PhotoArray.o Album.o Photo.o Date.o
	g++ -o a2 main.o TestView.o TestControl.o Client.o PhotoGram.o AlbumArray.o PhotoArray.o Album.o Photo.o Date.o

main.o: main.cc
	g++ -c main.cc

TestView.o: TestView.cc TestView.h
	g++ -c TestView.cc

TestControl.o: TestControl.cc TestControl.h
	g++ -c TestControl.cc

Client.o: Client.cc Client.h
	g++ -c Client.cc

PhotoGram.o: PhotoGram.cc PhotoGram.h
	g++ -c PhotoGram.cc

AlbumArray.o: AlbumArray.cc AlbumArray.h
	g++ -c AlbumArray.cc

PhotoArray.o: PhotoArray.cc PhotoArray.h
	g++ -c PhotoArray.cc
	
Album.o: Album.h Album.cc 
	g++ -c Album.cc 

Photo.o: Photo.h Photo.cc
	g++ -c Photo.cc

Date.o: Date.h Date.cc
	g++ -c Date.cc
	
clean:
	rm -f a2 *.o
