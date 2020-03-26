OBJS=sush.o tokenizer.o

all: sush

clean:
	rm -f *.o sush $(OBJS)
sush: $(OBJS)
	$(CC) -o sush $(OBJS)
