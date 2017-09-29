SRC_DIR = ../
LIB_DIR = ../../lib
BIN_DIR = ../../bin

ifndef ARCH
ARCH = $(shell getconf LONG_BIT)
$(warning $(shell printf "warning: ARCH not defined, using ARCH=$(ARCH)"))
endif

CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += -I $(SRC_DIR)/probing
CXXFLAGS += -I $(SRC_DIR)/exception
CXXFLAGS += -I $(SRC_DIR)/rawdisk
CXXFLAGS += -I $(SRC_DIR)/datatypes
CXXFLAGS += -m$(ARCH)

VERSION = sofs17

TARGET_APP = mksofs

OBJS = mksofs_main.o
OBJS += mksofs_CS.o 
OBJS += mksofs_SB.o 
OBJS += mksofs_IT.o
OBJS += mksofs_FCT.o
OBJS += mksofs_RD.o
OBJS += mksofs_RC.o

LIBS += -l$(VERSION)MksofsBin
LIBS += -l$(VERSION)Rawdisk
LIBS += -l$(VERSION)Probing

LFLAGS = -L $(LIB_DIR) 
LFLAGS += -L $(LIB_DIR)/lib$(ARCH)
LFLAGS += $(LIBS)

all:		$(OBJS) $(TARGET_APP)

$(TARGET_APP):	$(OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)
	cp $@ $(BIN_DIR)
	rm -f $^ $@

clean:
	rm -f $(TARGET_APP) $(OBJS)
	rm -f *~ 

cleanall:	clean
	rm -f $(BIN_DIR)/$(TARGET_APP)

