OBJS    = main.o Timer.o
CXX     = g++
DEBUG   = -g
CXXFLAGS  = -Wall $(DEBUG) -std=c++17 -pthread -fopenmp -lcrypto -lssl
LDFLAGS = -pthread

aaa: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)