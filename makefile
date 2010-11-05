# Makefile
# for ECEN 4593 cache simulator project
# Fall 2010
# Danny Gale, Chris Messick
#
# Revision History:
# 11/1/2010	created	Danny Gale
#

OBJS = main.o input.o cxxcache.o cacheline.o

cachesim : $(OBJS)
	g++ -Wall -o cachesim $(OBJS)

cxxcache.o : cxxcache.cxx cacheline.h
	g++ -Wall -c cxxcache.cxx

cacheline.o : cacheline.cxx cacheline.h
	g++ -Wall -c cacheline.cxx

main.o : main.cxx input.cxx cxxcache.h
	g++ -Wall -c main.cxx

input.o : input.cxx main.cxx
	g++ -Wall -c input.cxx

clean :
	rm $(OBJS)
