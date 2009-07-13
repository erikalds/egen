all:
	scons -C src

dpkg:
	dpkg-buildpackage -rfakeroot

install:
	scons -C src install

clean:
	scons -C src -c

sense:
	@fortune
