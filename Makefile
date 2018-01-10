CC		= clang
TARGET		= redmirror

INCLUDES	= -I/usr/local/include
CFLAGS		= -Wall
LFLAGS		= -static -L/usr/local/lib
LIBS		= -lkcgi -lz -lmemcached

SRCS = $(TARGET).c
OBJS = $(SRCS:.c=.o)

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

install:
	install -m 0555 redmirror /var/www/cgi-bin
	pkill -SIGHUP kfcgi

clean:
	rm $(TARGET) $(OBJS)
