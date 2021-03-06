#--- google test framework
INCL =		gtest/include
TLIBPATH =	-Lgtest/lib
TLIBS =		-pthread -lgtest

CXXFLAGS =	-O2 -g3 -Wall -Wextra -fmessage-length=0 -fstack-protector-all -std=c++11 -I$(INCL)

OBJS =		MetroNet.o Station.o MetroStation.o Halte.o Tram.o PCC.o Albatros.o Passagier.o MetroNetImporter.o MetroNetUtils.o
SRCS =		MetroNetMain \
			Station.cpp \
			MetroStation.cpp \
			Halte.cpp \
			Tram.cpp \
			Albatros.cpp \
			PCC.cpp \
			MetroNet.cpp \
			Passagier.cpp \
			MetroNetImporter.cpp \
			MetroNetUtils.cpp

TSTSRCS =	MetroNetTests.cpp \
			ClassTestsTram.cpp \
			ClassTestsStation.cpp \
			ClassTestsMetroNet.cpp \
			ClassTestsPassagier.cpp \
			MetroNetInputTests.cpp \
			MetroNetOutputTests.cpp \
			PassagierInputTests.cpp

TINYOBJS =	tinystr.o \
			tinyxml.o \
			tinyxmlerror.o \
			tinyxmlparser.o
TINYSRCS =	tinystr.h \
			tinyxml.cpp \
			tinyxmlerror.cpp \
			tinyxmlparser.cpp
TARGET =	MetroNetMain	MetroNetTests

#--- primary target
.PHONY : all
all : $(TARGET)

#--- compiler targets
MetroNetMain : $(OBJS) $(TINYOBJS) tinyxml.h MetroNetMain.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(TINYOBJS) MetroNetMain.o

MetroNetTests : $(OBJS) $(TSTSRCS) $(TINYOBJS) tinyxml.h MetroNetTests.o
	$(CXX) $(CXXFLAGS) $(TLIBPATH) -o $@ $(OBJS) $(TINYOBJS) MetroNetTests.o $(TLIBS)

MetroNetTests.o : $(TSTSRCS)
	$(CXX) $(CXXFLAGS) -c -o $@ MetroNetTests.cpp

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY : depend
depend :
	g++ -MM -I $(INCL) $(SRCS)

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	find . -name '*~'  -delete
	rm $(TARGET)

.PHONY: clearOutput
clearOutput:
	rm -r _testOutput/*.*
	rm -r _output/*.*
