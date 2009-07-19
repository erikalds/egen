all:
	scons -C src

doxygen:
	doxygen doc/Doxyfile

dpkg:
	git-buildpackage

install:
	scons -C src install

configure:
	scons -C src --config=auto

clean:
	scons -C src -c

sense:
	@fortune
