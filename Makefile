ifndef CXXFLAGS
	CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
endif

CXXFLAGS+= -g

wordgen: clean
	c++ ${CXXFLAGS} main.cpp -o wordGen

clean:
	rm -f wordgen
