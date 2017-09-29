SRC_DIR = ../
LIB_DIR = ../../lib
BIN_DIR = ../../bin

ifndef ARCH
ARCH = $(shell getconf LONG_BIT)
$(warning $(shell printf "warning: ARCH not defined, using ARCH=$(ARCH)"))
endif

CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26
CXXFLAGS += -I $(SRC_DIR)/syscalls
CXXFLAGS += -I $(SRC_DIR)/probing
CXXFLAGS += -I $(SRC_DIR)/exception
CXXFLAGS += -I $(SRC_DIR)/datatypes
CXXFLAGS += -I $(SRC_DIR)/rawdisk

SUFFIX = $(ARCH)

VERSION = sofs17

TARGET_APP = sofsmount

OBJS = sofsmount.o

LIBS += -Wl,--start-group
LIBS += -l$(VERSION)Syscalls
LIBS += -l$(VERSION)SyscallsBin
LIBS += -l$(VERSION)Direntries
LIBS += -l$(VERSION)DirentriesBin
LIBS += -l$(VERSION)Fileclusters
LIBS += -l$(VERSION)FileclustersBin
LIBS += -l$(VERSION)Freelists
LIBS += -l$(VERSION)FreelistsBin
LIBS += -l$(VERSION)Inodeattr
LIBS += -l$(VERSION)InodeattrBin
LIBS += -l$(VERSION)OCDealer
LIBS += -l$(VERSION)ITDealer
LIBS += -l$(VERSION)ITDealerBin
LIBS += -l$(VERSION)CZDealer
LIBS += -l$(VERSION)CZDealerBin
LIBS += -l$(VERSION)SBDealer
LIBS += -l$(VERSION)SBDealerBin
LIBS += -l$(VERSION)Rawdisk
LIBS += -l$(VERSION)Probing

LFLAGS = -L $(LIB_DIR) 
LFLAGS += -L $(LIB_DIR)/lib$(ARCH)
LFLAGS += $(LIBS)
LFLAGS += -lpthread -lfuse -lrt -ldl

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

