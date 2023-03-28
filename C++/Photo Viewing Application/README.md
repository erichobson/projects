# Photo Viewing Application
---
Compilation:
make
make clean

Execution:
./a2
valgrind ./a2

Additional Details:
N/A
---
Files Submitted:
Album.cc
Album.h
- contains information about the album

AlbumArray.cc
AlbumArray.h
- data structure for Albums

Client.cc
Client.h
- 'connects' to the PhotoGram network to display Photos or download Albums

Date.cc
Date.h
- contains date information

defs.h
- contains defined MAX_ARRAY size

main.cc
- instantiates a TestControl object and call launch

Makefile

Photo.cc
Photo.h
- contains information about the photo

PhotoArray.cc
PhotoArray.h
- data structure for Photos

PhotoGram.cc
PhotoGram.h
- manages a collection of Albums

ReadMe.txt

TestControl.cc
TestControl.h
- controls the running of tests on the application

TestView.cc
TestView.h
- takes input from the user performing the tests
---