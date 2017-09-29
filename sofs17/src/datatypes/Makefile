SRC_DIR = ../
LIB_DIR = ../../lib
BIN_DIR = ../../bin

ifndef ARCH
ARCH = $(shell getconf LONG_BIT)
$(warning $(shell printf "warning: ARCH not defined, using ARCH=$(ARCH)"))
endif

CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += -I $(SRC_DIR)/rawdisk
CXXFLAGS += -m$(ARCH)

TARGET_APPS = showsizes

OBJS += showsizes.o

HEADERS += superblock.h
HEADERS += inode.h
HEADERS += direntry.h
HEADERS += datatypes.h
HEADERS += $(SRC_DIR)/rawdisk/rawdisk.h

all:		$(OBJS) $(TARGET_APPS)

$(TARGET_APPS):	$(OBJS)
	$(CXX) -o $@ $^ 
	cp $@ $(BIN_DIR)
	rm -f $^ $@

$(OBJS):	$(HEADERS)

clean:
	rm -f $(TARGET_APPS) $(TARGET_APPS:%=%.o) $(OBJS)
	rm -f *~ 

cleanall:	clean
	rm -f $(BIN_DIR)/$(TARGET_APPS)
