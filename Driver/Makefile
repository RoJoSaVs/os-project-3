# all:
# 	gcc Libreria_Driver.c Driver.c -o programa
# 	./programa


obj-m += kernel-driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean