all:
	scons -C src

doxygen:
	doxygen doc/Doxyfile

dpkg:
	dpkg-buildpackage -rfakeroot

install:
	scons -C src install

configure:
	scons -C src --config=auto

clean:
	scons -C src -c

sense:
	@fortune
