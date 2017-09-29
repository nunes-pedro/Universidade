SRC_DIR = "../"
LIB_DIR = "../../lib"

ifndef ARCH
ARCH = $(shell getconf LONG_BIT)
$(warning $(shell printf "warning: ARCH not defined, using ARCH=$(ARCH)"))
endif

CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += -I "$(SRC_DIR)/exception"
CXXFLAGS += -m$(ARCH)

VERSION = sofs17

LIB_NAME = $(VERSION)Probing

TARGET_LIB = lib$(LIB_NAME).a

OBJS = probing.o 

all:		$(TARGET_LIB) clean

$(TARGET_LIB):		$(OBJS)
	ar -r $@ $^
	cp $@ $(LIB_DIR)
	rm -f $@

clean:
	rm -f *.o $(TARGET_LIB)
	rm -f *~ 

cleanall:	clean
	rm -f $(LIB_DIR)/$(TARGET_LIB)
