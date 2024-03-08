CFLAGS = -DRPI0 -mfpu=vfp -march=armv6zk -mtune=arm1176jzf-s -O0 -mfloat-abi=hard -nostartfiles -nostdlib -nostartfiles -ffreestanding -O2 -lgcc -lc -lm -lrdimon -g -O4
default:
	arm-none-eabi-as -o start.o start.s -mfpu=vfp -mfloat-abi=hard 
	arm-none-eabi-gcc -c -o main.o main.c ${CFLAGS}
	arm-none-eabi-gcc -c -o sys_calls.o sys_calls.c ${CFLAGS}
	arm-none-eabi-gcc -o kernel7.elf start.o sys_calls.o main.o ${CFLAGS} -flto -lnosys -specs=nano.specs -specs=nosys.specs --data-sections #-T linker.ld
	arm-none-eabi-objcopy kernel7.elf -O binary kernel7.img
