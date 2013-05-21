
obj-m	+= w1-sun4i/w1-sun4i.o

all:
	make -j3 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ../linux-sunxi M=$(PWD) modules

clean:
	make -j3 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ../linux-sunxi M=$(PWD) clean
