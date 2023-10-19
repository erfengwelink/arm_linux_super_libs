
CC=gcc
CFLAGES = -w -g -Wall -O2
LIBS=

INCS=
TARGET = rb-tree 
DIRS = .

FILES = $(foreach dir, $(DIRS),$(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c,%.o,$(FILES))


$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGES) $(LIBS)

$(OBJS):%.o:%.c         
	@$(CC) $(INCS) -c  $< $(CFLAGES) -o $@

clean:
	-rm -f $(TARGET) $(OBJS)
	