all:: src test doc

doc:
	doxygen Doxyfile

.PHONY: src test run-test depend-src depend-test depend clean-src clean-test clean-doc clean

src::
	cd src;make

test::
	cd test;make

run-test::
	cd test;runner

depend-src::
	cd src; make depend

depend-test::
	cd test; make depend

depend:: depend-src depend-test

clean-src::
	cd src;make clean

clean-test::
	cd test;make clean

clean-doc::
	rm -Rf doc

clean:: clean-src clean-test clean-doc
