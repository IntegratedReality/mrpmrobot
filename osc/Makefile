# should be either OSC_HOST_BIG_ENDIAN or OSC_HOST_LITTLE_ENDIAN
# Apple Mac OS X: OSC_HOST_BIG_ENDIAN
# Win32: OSC_HOST_LITTLE_ENDIAN
# i386 GNU/Linux: OSC_HOST_LITTLE_ENDIAN
ENDIANESS=OSC_HOST_LITTLE_ENDIAN

CXX = g++
INCLUDES = -I./
COPTS  = -Wall -O3
CDEBUG = -Wall -g 
CXXFLAGS = $(COPTS) $(INCLUDES) -D$(ENDIANESS)

#Name definitions
UNITTESTS=OscUnitTests
SEND=OscSendTest
RECEIVE=OscReceiveTest
DUMP=OscDump

INCLUDEDIR = oscpack
LIBNAME = liboscpack
LIBSONAME = $(LIBNAME).so
LIBFILENAME = $(LIBSONAME).1.0.2

#Test and example source
SENDSOURCES = ./OscSendTest.cpp ./OscSender.cpp ./osc/OscOutboundPacketStream.cpp ./osc/OscTypes.cpp ./ip/posix/NetworkingUtils.cpp ./ip/posix/UdpSocket.cpp ./ip/IpEndpointName.cpp
SENDOBJECTS = $(SENDSOURCES:.cpp=.o)

RECEIVESOURCES = ./tests/OscReceiveTest.cpp ./osc/OscTypes.cpp ./osc/OscReceivedElements.cpp ./osc/OscPrintReceivedElements.cpp ./ip/posix/NetworkingUtils.cpp ./ip/posix/UdpSocket.cpp
RECEIVEOBJECTS = $(RECEIVESOURCES:.cpp=.o)

#Library sources
LIBSOURCES = ./ip/IpEndpointName.cpp \
	./ip/posix/NetworkingUtils.cpp ./ip/posix/UdpSocket.cpp\
	./osc/OscOutboundPacketStream.cpp ./osc/OscPrintReceivedElements.cpp ./osc/OscReceivedElements.cpp ./osc/OscTypes.cpp
LIBOBJECTS = $(LIBSOURCES:.cpp=.o)

all:	send receive

send : $(SENDOBJECTS)
	$(CXX) -o $(SEND) $+ $(LIBS) 
receive : $(RECEIVEOBJECTS)
	$(CXX) -o $(RECEIVE) $+ $(LIBS) 

clean:
	rm -rf ./OscSendTest $(SENDOBJECTS) $(RECEIVEOBJECTS) $(LIBOBJECTS) $(LIBFILENAME) include lib oscpack &> /dev/null

$(LIBFILENAME): $(LIBOBJECTS)
	@#GNU/Linux case
	$(CXX) -shared -Wl,-soname,$(LIBSONAME) -o $(LIBFILENAME) $(LIBOBJECTS) -lc
	@#Mac OS X case
	@#$(CXX) -dynamiclib -Wl,-install_name,$(LIBSONAME) -o $(LIBFILENAME) $(LIBOBJECTS) -lc
	
