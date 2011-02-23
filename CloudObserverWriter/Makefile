TARGET = cowriter



CXX = g++
SRCS = CloudObserverWriter.cpp VideoEncoder.cpp LSD.cpp linux/list.cpp

OBJS      = $(SRCS:%.cpp=%.o)

CXXFLAGS = -g -fPIC -pipe -O2 -MMD -MP -c
LIBS = -lm -lcv -lhighgui 
LIBS += -lboost_system -lboost_regex -lboost_serialization -lboost_thread
LIBS += -lavcodec -lavdevice -lavformat -lavutil -lswscale -lcxcore -lopenal 
LDFLAGS = -L/usr/lib -L/usr/local/lib 

.PHONY: clean all

all: $(OBJS)
	$(CXX)  $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@
	
clean:
	rm -f $(OBJS)
