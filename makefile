# Makefile
# for ECEN 4593 cache simulator project
# Fall 2010
# Danny Gale, Chris Messick
#
# Revision History:
# 11/1/2010	created	Danny Gale
#

OBJS = main.o input.o cxxcache.o

cachesim : $(OBJS)
	g++ -o cachesim $(OBJS)

cxxcache.o : cxxcache.cxx
	g++ -c cxxcache.cxx

main.o : main.cxx input.cxx cache.h
	g++ -c main.cxx

input.o : input.cxx main.cxx
	g++ -c input.cxx

clean :
	rm $(OBJS)
