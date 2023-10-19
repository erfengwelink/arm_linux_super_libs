# CC = "gcc"
# COMPiler = /home/wangyf/workspace/whole_ssd201_iot/tools/bin/arm-linux-gnueabihf-

TAR = wrt_iot
OBJ = cson_demo.o cson.o cJSON.o
CC := /home/wangyf/workspace/whole_ssd201_iot/tools/bin/arm-linux-gnueabihf-gcc


$(TAR):$(OBJ)
	$(CC) $^ -o $@ -lm

%.o:%.c
	$(CC) -c $^ -o $@

.PHONY:
clearall:
	rm -rf $(OBJ) $(TAR)
clear:
	rm -rf $(OBJ)