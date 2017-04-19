OBJS = main.o delaunay.o site.o quadEdge.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

dt : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o dt

main.o : main.cpp delaunay.h site.h quadEdge.h
	$(CC) $(CFLAGS) main.cpp

delaunay.o : delaunay.h delaunay.cpp
	$(CC) $(CFLAGS) delaunay.cpp

site.o : site.h site.cpp 
	$(CC) $(CFLAGS) site.cpp

quadEdge.o : quadEdge.h quadEdge.cpp
	$(CC) $(CFLAGS) quadEdge.cpp

clean:
	\rm *.o *~ dt
