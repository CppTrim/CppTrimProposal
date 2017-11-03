.PHONY: test clean

CXX=g++-7
EXTRACXXFLAGS=
CXXFLAGS=-std=c++1z -g $(EXTRACXXFLAGS)

TESTROOT=string_trim_tests
TESTPROPERTYROOT=string_trim_property_tests
HEADER=string_trim.hpp

test: $(TESTROOT) ${TESTPROPERTYROOT}
	./$(TESTROOT)
	./$(TESTPROPERTYROOT)

$(TESTROOT): $(TESTROOT).cpp $(HEADER) makefile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

$(TESTPROPERTYROOT): $(TESTPROPERTYROOT).cpp $(HEADER) makefile
	$(CXX) $(CXXFLAGS) -I../RapidCheck/include $(LDFLAGS) -o $@ $< -L../RapidCheckBuild -lrapidcheck

clean:
	@rm -f $(TESTROOT)
	@rm -f $(TESTPROPERTYROOT)
