CC=gcc

install: src/hmon.c include/hmon.h
	@echo "==========[ INSTALLING HMON ]=========="
	sudo cp include/hmon.h /usr/local/include/
	
	@echo "==========[ BUILDING HMON ]=========="
	$(CC) -c src/hmon.c -o src/hmon.o
	ar rcs obj/libhmon.a obj/hmon.o
	ar -t obj/libhmon.a
	sudo cp obj/libhmon.a /usr/local/lib/

	@echo "==========[ CLEANING ]=========="
	rm src/hmon.o
	@echo "==========[ DONE ]=========="

uninstall:
	@echo "==========[ UNINSTALLING HMON ]=========="
	sudo rm /usr/local/include/hmon.o
	sudo rm /usr/local/lib/libhmon.ar
	@echo "==========[ DONE ]=========="