SRC_DIR = ..
LIB_DIR = ../../lib

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
CXXFLAGS += -I $(SRC_DIR)/dealers/sbdealer
CXXFLAGS += -I $(SRC_DIR)/dealers/itdealer
CXXFLAGS += -I $(SRC_DIR)/dealers/czdealer
CXXFLAGS += -I $(SRC_DIR)/dealers/ocdealer
CXXFLAGS += -I $(SRC_DIR)/ilayers/freelists
CXXFLAGS += -I $(SRC_DIR)/ilayers/inodeattr
CXXFLAGS += -I $(SRC_DIR)/ilayers/fileclusters
CXXFLAGS += -I $(SRC_DIR)/ilayers/direntries
CXXFLAGS += -m$(ARCH)

VERSION = sofs17

SUFFIX = $(ARCH)

LIB_NAME = $(VERSION)Syscalls

TARGET_LIB = lib$(LIB_NAME).a

OBJS =
OBJS += read.o
OBJS += write.o
OBJS += mkdir.o
OBJS += rmdir.o
OBJS += readdir.o
OBJS += rename.o
OBJS += mknod.o
OBJS += symlink.o
OBJS += readlink.o
OBJS += truncate.o
OBJS += unlink.o
OBJS += link.o

all:			$(TARGET_LIB)

all:			$(TARGET_LIB)

$(TARGET_LIB):		$(OBJS)
	ar -r $(TARGET_LIB) $^
	cp $@ $(LIB_DIR)
	rm -f $^ $(TARGET_LIB)

clean:
	rm -f $(OBJS) $(TARGET_LIB)
	rm -f *~ 

cleanall:	clean
	rm -f $(LIB_DIR)/$(TARGET_LIB)
