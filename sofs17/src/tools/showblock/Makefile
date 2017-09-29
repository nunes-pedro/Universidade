SRC_DIR = ../../
LIB_DIR = ../../../lib
BIN_DIR = ../../../bin

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
CXXFLAGS += -m$(ARCH)

SUFFIX = $(ARCH)

VERSION = sofs17

LIB_NAME = $(VERSION)Blockviews

TARGET_APP = showblock

TARGET_LIB = lib$(LIB_NAME).a

APP_OBJS = showblock.o

LIB_OBJS = blockviews.o

LIBS += -l$(VERSION)Rawdisk
LIBS += -l$(VERSION)Probing

LFLAGS = -L $(LIB_DIR) $(LIBS)

all:		$(LIB_OBJS) $(APP_OBJS) $(TARGET_LIB) $(TARGET_APP) clean

$(TARGET_APP):	$(APP_OBJS) $(LIB_OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)
	cp $@ $(BIN_DIR)

$(TARGET_LIB):		$(LIB_OBJS)
	ar -r $(TARGET_LIB) $^
	cp $(TARGET_LIB) $(LIB_DIR)

clean:
	rm -f $(TARGET_LIB) $(TARGET_APP) $(LIB_OBJS) $(APP_OBJS)
	rm -f *~ 

cleanall:	clean
	rm -f $(LIB_DIR)/$(TARGET_LIB)
	rm -f $(BIN_DIR)/$(TARGET_APP)

