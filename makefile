all: doc src

doc:
	cd doc && make

src:
	cd src && make

clean: clean-doc clean-src

clean-doc:
	cd doc && make clean

clean-src:
	cd src && make clean

.PHONY: all doc src clean clean-doc clean-src
