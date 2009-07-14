all:
	scons -C src

doxygen:
	doxygen doc/Doxyfile

dpkg:
	dpkg-buildpackage -rfakeroot

install:
	scons -C src install

clean:
	scons -C src -c

sense:
	@fortune
