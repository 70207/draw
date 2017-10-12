SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRC))

CXXFLAGS += -std=c++11 -g -O0
LDFLAGS += ../lib/libwmd.a -L/lib64 -pthread

APP=./hello.out

default:$(APP)

clean:
		-rm -rf $(OBJS)
		-rm -rf $(APP)

$(APP): $(OBJS)
		$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.cpp:
		$(CXX) -g -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LIBRARY) $(LIBS)
