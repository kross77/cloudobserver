TARGET = cowriter

#LIB_DIRS = /usr/local/lib 

CXX = g++
SRCS = CloudObserverWriter.cpp list.cpp LSD.cpp stdafx.cpp VideoEncoder.cpp

OBJS      = $(SRCS:%.cpp=%.o)

CXXFLAGS = -g -fPIC -pipe -O2 -MMD -MP
CXXFLAGS += -lm -lcv -lhighgui -lcvaux



LIBS = -lcv

.PHONY: clean all

all: $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
	

clean:
	rm -f $(OBJS)
