OBJS = integer.o bst.o queue.o sll.o avl.o
OOPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g
EXECUTABLES = test-avl avl-0-0

all:	$(EXECUTABLES)

test-avl:	$(OBJS) test-avl.o
		gcc $(LOPTS) $(OBJS) test-avl.o -o test-avl

avl-0-0:	$(OBJS) avl-0-0.o
		gcc $(LOPTS) $(OBJS) avl-0-0.o -o avl-0-0

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

avl-0-0.o:	./Testing/avl-0-0.c avl.h bst.h queue.h integer.h
		gcc $(OOPTS) ./Testing/avl-0-0.c

test:	$(EXECUTABLES)
		@echo Testing avl-0-0...
		@./avl-0-0 > ./Testing/myresults/avl-0-0.txt
		@diff ./Testing/expectedresults/avl-0-0.expected ./Testing/myresults/avl-0-0.txt

valgrind:	$(EXECUTABLES)
		@valgrind ./avl-0-0

clean:
		rm -f vgcore.* *.o $(EXECUTABLES)
