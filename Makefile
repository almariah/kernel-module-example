obj-m += example.o

build:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
