TARGET		= redmirror

INCLUDES	= -I/usr/local/include
CFLAGS		= -g -Wall
LFLAGS		= -static -L/usr/local/lib
LIBS		= -lkcgi -lz

SRCS = $(TARGET).c
OBJS = $(SRCS:.c=.o)

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

install:
	install -m 0555 redmirror /var/www/fcgi-bin

clean:
	rm $(TARGET) $(TARGET).o
