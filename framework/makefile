BUSI_SRC=$(wildcard busi/*.cpp)
NET_SRC=$(wildcard net/*.cpp)
PACKAGE_SRC=$(wildcard package/*.cpp)
UTIL_SRC=$(wildcard util/*.cpp)


SRC=$(BUSI_SRC) $(NET_SRC) $(PACKAGE_SRC) $(UTIL_SRC)
OBJS=$(patsubst %.cpp, %.o, $(SRC))

CXXFLAGS += -D_WMD -pthread -std=c++11 -g -O0
LDFLAGS += -L/lib64 -pthread

LIB=../lib/libwmd.a 

default: $(LIB)

$(LIB): $(OBJS)
		rm -rf $@
		ar -rs $@ $(OBJS)

clean:
		-rm -rf $(OBJS)

.cpp:
		$(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LIBRARY) $(LIBS)