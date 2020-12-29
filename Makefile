ccflags-y := -I$(PWD)/inc
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello11.o hello22.o
ccflags-y += -g -DDEBUG
else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build
default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello11.ko hello11.ko.unstripped
	cp hello22.ko hello22.ko.unstripped
	$(CROSS_COMPILE)strip -g hello11.ko
	$(CROSS_COMPILE)strip -g hello22.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
%.s %.i: %.c
	$(MAKE) -C $(KDIR) M=$$PWD $@
endif
