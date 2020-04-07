OBJS=sush.o tokenizer.o
CFLAGS=-ggdb

all: sush

clean:
	rm -f *.o sush $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

sush: $(OBJS)
	$(CC) -ggdb -o sush $(OBJS)
