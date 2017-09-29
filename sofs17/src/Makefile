subdirs += probing
subdirs += rawdisk
subdirs += datatypes
subdirs += mksofs
subdirs += dealers/sbdealer
subdirs += dealers/itdealer
subdirs += dealers/czdealer
subdirs += dealers/ocdealer
subdirs += ilayers/inodeattr
subdirs += ilayers/freelists
subdirs += ilayers/fileclusters
subdirs += ilayers/direntries
subdirs += syscalls
subdirs += tools/showblock
subdirs += tools/testtool
subdirs += sofsmount

ifndef ARCH
ARCH = $(shell getconf LONG_BIT)
$(warning $(shell printf "warning: ARCH not defined, using ARCH=$(ARCH)"))
endif

.PHONY: $(subdirs)

all:	$(subdirs)

$(subdirs):
	@echo -e '\e[34;1;40;1mMaking $@...\e[m'
	@make -C $@ ARCH:=$(ARCH)

clean:
	@echo -e '\e[31;1;40;1mCleaning...\e[m'
	@for dir in $(subdirs) ; do make -C $$dir clean; done

cleanall:
	@echo -e '\e[31;1;40;1mCleaning all...\e[m'
	@for dir in $(subdirs) ; do make -C $$dir cleanall; done

