CXX=g++
CXXFLAGS=-Wall

all: build clean

build:
	$(CXX) *.cpp -c
	ar rvs libEngine.a *.o

clean:
	rm *.o