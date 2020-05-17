compile:
	cd src && qmake -makefile ijc.pro && make

doxygen: src/Doxyfile
	doxygen src/Doxyfile

clean:
	cd src && rm *.o Makefile ijc

run:
	cd src && ./ijc
