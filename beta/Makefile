all: qtTabularClient moc_output.cpp model.o

CPPFLAGS = -Wall -g -m64 -fPIC 

# ====================   Qt includes and libs ===============================

INC += -I$(QT_INC) -I$(QT_INC)/Qt -I$(QT_INC)/QtCore -I$(QT_INC)/QtGui 
LIB += -L$(QT_LIB) -lQtCore -lQtGui -lm -lpthread -lcurses -lreadline

# ===================   EPICS V3 and V4 includes and libs ====================

INC +=  -I$(EPICS_V3_DIR)/include                    \
		-I$(EPICS_V3_DIR)/include/compiler/gcc       \
		-I$(EPICS_V3_DIR)/include/valgrind           \
		-I$(EPICS_V3_DIR)/include/os/$(HOST_OS)      \
		-I$(EPICS_V4_DIR)/pvAccessCPP/include        \
		-I$(EPICS_V4_DIR)/pvDataCPP/include          \
		-I$(EPICS_V4_DIR)/normativeTypesCPP/include  \
		-I$(EPICS_V4_DIR)/pvaClientCPP/include       \
		-I$(EPICS_V4_DIR)/pvCommonCPP/include

LIB +=  -L$(EPICS_V3_DIR)/lib/$(EPICS_HOST_ARCH) \
		-L$(EPICS_V4_DIR)/pvDataCPP/lib/$(EPICS_HOST_ARCH) -lpvData \
		-L$(EPICS_V4_DIR)/pvAccessCPP/lib/$(EPICS_HOST_ARCH) -lpvAccess \
		-L$(EPICS_V4_DIR)/pvCommonCPP/lib/$(EPICS_HOST_ARCH) -lpvMB \
		-L$(EPICS_V4_DIR)/pvaClientCPP/lib/$(EPICS_HOST_ARCH) -lpvaClient \
		-L$(EPICS_V4_DIR)/normativeTypesCPP/lib/$(EPICS_HOST_ARCH) -lnt \
		-rdynamic -lpthread -lm -lreadline -lrt -ldl -lgcc

qtTabularClient: main.cpp moc_output.cpp model.o
	g++ $(CPP_FLAGS) $(INC) $(LIB) -o qtTabularClient main.cpp moc_output.cpp view.cpp model.o

model.o: model.h model.cpp
	g++ $(CPP_FLAGS) $(INC) $(LIB) -c model.cpp

moc_output.cpp: view.h view.cpp
	moc -o moc_output.cpp view.h

clean: 
	rm -f moc_output.cpp qtTabularClient model.o
