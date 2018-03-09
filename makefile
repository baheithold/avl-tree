OBJS = integer.o bst.o queue.o sll.o avl.o
OOPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g
EXECUTABLES = test-avl

all:	$(EXECUTABLES)

test-avl:	$(OBJS) test-avl.o
		gcc $(LOPTS) $(OBJS) test-avl.o -o test-avl

integer.o:	integer.c integer.h
		gcc $(OOPTS) integer.c

queue.o:	queue.c queue.h sll.h
		gcc $(OOPTS) queue.c

sll.o:	sll.c sll.h
		gcc $(OOPTS) sll.c

bst.o:	bst.c bst.h queue.h
		gcc $(OOPTS) bst.c

avl.o:	avl.c avl.h bst.h
		gcc $(OOPTS) avl.c

test-avl.o:	./Testing/test-avl.c avl.h bst.h queue.h integer.h
		gcc $(OOPTS) ./Testing/test-avl.c

test:	$(EXECUTABLES)
		@echo Testing test-avl...
		@./test-avl

valgrind:	$(EXECUTABLES)
		@valgrind ./test-avl

clean:
		rm -f vgcore.* *.o $(EXECUTABLES)
