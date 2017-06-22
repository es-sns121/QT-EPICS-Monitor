EXE = qtTabularClient
OBJ = model.o monitorWorker.o moc_output.o view.o
MOC = moc_output.cpp

all: $(EXE) $(OBJ) $(MOC) 

CPP_FLAGS = -Wall -g -lpthread -lm 

# ====================   Qt includes and libs ===============================

QT_INCLUDE += -I$(QT_INC) -I$(QT_INC)/Qt -I$(QT_INC)/QtCore -I$(QT_INC)/QtGui 
QT_LIBRARY += -L$(QT_LIB) -lQtCore -lQtGui -lm -lpthread 

# ===================   EPICS V3 and V4 includes and libs ====================

EPICS_INCLUDE += -I$(EPICS_V3_DIR)/include                   \
				-I$(EPICS_V3_DIR)/include/compiler/gcc       \
				-I$(EPICS_V3_DIR)/include/valgrind           \
				-I$(EPICS_V3_DIR)/include/os/$(HOST_OS)      \
				-I$(EPICS_V4_DIR)/pvAccessCPP/include        \
				-I$(EPICS_V4_DIR)/pvDataCPP/include          \
				-I$(EPICS_V4_DIR)/normativeTypesCPP/include  \
				-I$(EPICS_V4_DIR)/pvaClientCPP/include       \
				-I$(EPICS_V4_DIR)/pvCommonCPP/include

EPICS_LIBRARY += -L$(EPICS_V3_DIR)/lib/$(EPICS_HOST_ARCH) -lCom                   \
				-L$(EPICS_V4_DIR)/pvDataCPP/lib/$(EPICS_HOST_ARCH) -lpvData       \
				-L$(EPICS_V4_DIR)/pvAccessCPP/lib/$(EPICS_HOST_ARCH) -lpvAccess   \
				-L$(EPICS_V4_DIR)/pvCommonCPP/lib/$(EPICS_HOST_ARCH) -lpvMB       \
				-L$(EPICS_V4_DIR)/pvaClientCPP/lib/$(EPICS_HOST_ARCH) -lpvaClient \
				-L$(EPICS_V4_DIR)/normativeTypesCPP/lib/$(EPICS_HOST_ARCH) -lnt   

INC += $(EPICS_INCLUDE) $(QT_INCLUDE)
LIB += $(EPICS_LIBRARY) $(QT_LIBRARY)

qtTabularClient: main.cpp $(OBJ) 
	g++ $(CPP_FLAGS) $(INC) $(LIB) -o qtTabularClient main.cpp $(OBJ) 

view.o: view.h view.cpp model.o
	g++ $(CPP_FLAGS) $(INC) $(LIB) -o view.o -c view.cpp

model.o: model.h model.cpp
	g++ $(CPP_FLAGS) $(EPICS_INCLUDE) $(EPICS_LIBRARY) -o model.o -c model.cpp

monitorWorker.o: monitorWorker.h monitorWorker.cpp
	g++ $(CPP_FLAGS) $(EPICS_INCLUDE) $(EPICS_LIBRARY) -o monitorWorker.o -c monitorWorker.cpp

moc_output.o: moc_output.cpp 
	g++ $(CPP_FLAGS) $(INC) $(LIB) -o moc_output.o -c moc_output.cpp

moc_output.cpp: view.h
	moc -o moc_output.cpp view.h

clean: 
	rm -f $(EXE) $(OBJ) $(MOC) 
