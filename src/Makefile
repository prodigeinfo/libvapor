CXXFLAGS = -std=c++11 -Wno-deprecated -fPIC -O -I/usr/local/include -I../include
CXX = c++ -c
LDFLAGS=
CXXDL=c++ -fPIC -shared $(LDFLAGS)
SRCS != echo *.cpp
OBJS = $(SRCS:.cpp=.o)
LIBNAME = libvapor.so

.ifdef DEBUG
  CXXFLAGS += -g -D__DEBUG__
. ifndef DEBUG_FLAGS
    $(FLAGS) = $(DEBUG_FLAGS)
. endif
.endif

all:: $(OBJS) $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(CXXDL) $(OBJS) -o $@

.SUFFIXES: .cpp .hpp .c .h .o .sh

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: depend clean

depend::
	mkdep $(CXXFLAGS) $(SRCS)

clean::
	rm -f *.o *.core
