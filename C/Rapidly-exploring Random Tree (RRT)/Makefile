rrtTester: display.o rrtMaker.o rrtTester.o 
	gcc -o rrtTester rrtMaker.o rrtTester.o display.o -lX11 -lm

display.o: display.h display.c obstacles.h
	gcc -c display.c

rrtMaker.o: obstacles.h display.h rrtMaker.c
	gcc -c rrtMaker.c

rrtTester.o: obstacles.h display.h rrtTester.c
	gcc -c rrtTester.c

clean:
	rm -f *.o rrtTester
