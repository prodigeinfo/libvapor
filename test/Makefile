CXXFLAGS=-std=c++11 -Wno-deprecated -O -I/usr/local/include -I../include
CXX=c++ -c
LDFLAGS=-L/usr/local/lib -L../src -lvapor -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time -lboost_unit_test_framework
CXXLINK=c++ $(LDFLAGS)
SRCS != ls *.cpp
OBJS=$(SRCS:.cpp=.o)
SOBJS=../src/libvapor.so
PROGNAME=runner

.ifdef DEBUG
  CXXFLAGS += -g -D__DEBUG__
. ifndef DEBUG_FLAGS
    $(FLAGS) = $(DEBUG_FLAGS)
. endif
.endif

all:: $(PROGNAME)

$(PROGNAME): $(OBJS) $(SOBJS)
	$(CXXLINK) $< $(OBJS) $(SOBJS) -o $@

.SUFFIXES: .cpp .hpp .c .h .o .sh

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: depend clean

depend::
	mkdep $(CXXFLAGS) $(SRCS)

clean::
	rm -f *.o *.core
