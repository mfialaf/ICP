subsystem:
	cd src && $(MAKE)

doxygen: src/Doxyfile
	doxygen src/Doxyfile

clean:
	cd src && make clean

run:
	cd src && make run
