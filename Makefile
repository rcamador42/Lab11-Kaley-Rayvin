AutomatedMakefile = am
CC = g++
CXXFLAGS = -Wno-deprecated-declarations -g -O0

PROJECT_PATH = $(CURRENT_DIR)
GUI_PATH = $(DRIVE_LETTER)/TDM-GCC-64/wxWidgets-3.1.0

INC_DIRS = -I./2111/CSC2110 -I./2111/GUI -I$(GUI_PATH)/include -I$(GUI_PATH)/lib/gcc510TDM_x64_dll/mswu
LIB_DIRS = -L./2111/CSC2110 -L./2111/GUI -L$(GUI_PATH)/lib/gcc510TDM_x64_dll
LDFLAGS = -Wl,-Bstatic
LIBS = $(LDFLAGS) -lCSC2110 -lrandom -lGUI -lwxmsw31u_core -lwxbase31u -lgdi32

COMPILE = $(CC) $(CXXFLAGS) $(INC_DIRS) -c 
LINK = $(CC) $(CXXFLAGS) $(LIB_DIRS)

FILES = BSTDriver.o
EXECUTABLE = BSTDriver.exe

all: BSTDriver

BSTDriver: 	$(FILES)
			$(LINK) $(FILES) $(LIBS) -o $(EXECUTABLE)
			$(EXECUTABLE)

BSTDriver.o:		
			$(COMPILE) BSTDriver.cpp