CC=cc

install: src/hmon.c include/hmon.h
	@echo "==========[ INSTALLING HMON ]=========="
	sudo cp include/hmon.h /usr/local/include/
	
	@echo "==========[ BUILDING HMON ]=========="
	$(CC) -c src/hmon.c -o src/hmon.o
	ar rcs src/libhmon.a src/hmon.o
	ar -t src/libhmon.a
	sudo cp src/libhmon.a /usr/local/lib/

	@echo "==========[ CLEANING ]=========="
	rm src/hmon.o
	rm src/libhmon.a
	@echo "==========[ DONE ]=========="

uninstall:
	@echo "==========[ UNINSTALLING HMON ]=========="
	sudo rm /usr/local/include/hmon.o
	sudo rm /usr/local/lib/libhmon.ar
	@echo "==========[ DONE ]=========="