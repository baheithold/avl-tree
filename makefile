OBJS = integer.o real.o string.o bst.o queue.o sll.o avl.o
OOPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g
EXECUTABLES = test-avl avl-0-0 avl-0-1 avl-0-2 avl-0-3 avl-0-4 avl-0-5 avl-0-6 \
			  avl-0-7 avl-0-8 avl-0-9 avl-0-10

all:	$(EXECUTABLES)

test-avl:	$(OBJS) test-avl.o
		gcc $(LOPTS) $(OBJS) test-avl.o -o test-avl

avl-0-0:	$(OBJS) avl-0-0.o
		gcc $(LOPTS) $(OBJS) avl-0-0.o -o avl-0-0

avl-0-1:	$(OBJS) avl-0-1.o
		gcc $(LOPTS) $(OBJS) avl-0-1.o -o avl-0-1

avl-0-2:	$(OBJS) avl-0-2.o
		gcc $(LOPTS) $(OBJS) avl-0-2.o -o avl-0-2

avl-0-3:	$(OBJS) avl-0-3.o
		gcc $(LOPTS) $(OBJS) avl-0-3.o -o avl-0-3

avl-0-4:	$(OBJS) avl-0-4.o
		gcc $(LOPTS) $(OBJS) avl-0-4.o -o avl-0-4

avl-0-5:	$(OBJS) avl-0-5.o
		gcc $(LOPTS) $(OBJS) avl-0-5.o -o avl-0-5

avl-0-6:	$(OBJS) avl-0-6.o
		gcc $(LOPTS) $(OBJS) avl-0-6.o -o avl-0-6

avl-0-7:	$(OBJS) avl-0-7.o
		gcc $(LOPTS) $(OBJS) avl-0-7.o -o avl-0-7

avl-0-8:	$(OBJS) avl-0-8.o
		gcc $(LOPTS) $(OBJS) avl-0-8.o -o avl-0-8

avl-0-9:	$(OBJS) avl-0-9.o
		gcc $(LOPTS) $(OBJS) avl-0-9.o -o avl-0-9

avl-0-10:	$(OBJS) avl-0-10.o
		gcc $(LOPTS) $(OBJS) avl-0-10.o -o avl-0-10

integer.o:	integer.c integer.h
		gcc $(OOPTS) integer.c

real.o:	real.c real.h
		gcc $(OOPTS) real.c

string.o:	string.c string.h
		gcc $(OOPTS) string.c

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

avl-0-0.o:	./Testing/0/avl-0-0.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-0.c

avl-0-1.o:	./Testing/0/avl-0-1.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-1.c

avl-0-2.o:	./Testing/0/avl-0-2.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-2.c

avl-0-3.o:	./Testing/0/avl-0-3.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-3.c

avl-0-4.o:	./Testing/0/avl-0-4.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-4.c

avl-0-5.o:	./Testing/0/avl-0-5.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-5.c

avl-0-6.o:	./Testing/0/avl-0-6.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-6.c

avl-0-7.o:	./Testing/0/avl-0-7.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-7.c

avl-0-8.o:	./Testing/0/avl-0-8.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-8.c

avl-0-9.o:	./Testing/0/avl-0-9.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-9.c

avl-0-10.o:	./Testing/0/avl-0-10.c avl.h bst.h queue.h integer.h real.h string.h
		gcc $(OOPTS) ./Testing/0/avl-0-10.c

test:	$(EXECUTABLES)
		@echo Testing avl-0-0...
		@./avl-0-0 > ./Testing/0/actual/avl-0-0.txt
		@diff ./Testing/0/expected/avl-0-0.expected ./Testing/0/actual/avl-0-0.txt
		@echo Testing avl-0-1...
		@./avl-0-1 > ./Testing/0/actual/avl-0-1.txt
		@diff ./Testing/0/expected/avl-0-1.expected ./Testing/0/actual/avl-0-1.txt
		@echo Testing avl-0-2...
		@./avl-0-2 > ./Testing/0/actual/avl-0-2.txt
		@diff ./Testing/0/expected/avl-0-2.expected ./Testing/0/actual/avl-0-2.txt
		@echo Testing avl-0-3...
		@./avl-0-3 > ./Testing/0/actual/avl-0-3.txt
		@diff ./Testing/0/expected/avl-0-3.expected ./Testing/0/actual/avl-0-3.txt
		@echo Testing avl-0-4...
		@./avl-0-4 > ./Testing/0/actual/avl-0-4.txt
		@diff ./Testing/0/expected/avl-0-4.expected ./Testing/0/actual/avl-0-4.txt
		@echo Testing avl-0-5...
		@./avl-0-5 > ./Testing/0/actual/avl-0-5.txt
		@diff ./Testing/0/expected/avl-0-5.expected ./Testing/0/actual/avl-0-5.txt
		@echo Testing avl-0-6...
		@./avl-0-6 > ./Testing/0/actual/avl-0-6.txt
		@diff ./Testing/0/expected/avl-0-6.expected ./Testing/0/actual/avl-0-6.txt
		@echo Testing avl-0-7...
		@./avl-0-7 > ./Testing/0/actual/avl-0-7.txt
		@diff ./Testing/0/expected/avl-0-7.expected ./Testing/0/actual/avl-0-7.txt
		@echo Testing avl-0-8...
		@./avl-0-8 > ./Testing/0/actual/avl-0-8.txt
		@diff ./Testing/0/expected/avl-0-8.expected ./Testing/0/actual/avl-0-8.txt
		@echo Testing avl-0-9...
		@./avl-0-9 > ./Testing/0/actual/avl-0-9.txt
		@diff ./Testing/0/expected/avl-0-9.expected ./Testing/0/actual/avl-0-9.txt
		@echo Testing avl-0-10...
		@./avl-0-10 > ./Testing/0/actual/avl-0-10.txt
		@diff ./Testing/0/expected/avl-0-10.expected ./Testing/0/actual/avl-0-10.txt

valgrind:	$(EXECUTABLES)
		@valgrind ./avl-0-0
		@valgrind ./avl-0-1
		@valgrind ./avl-0-2
		@valgrind ./avl-0-3
		@valgrind ./avl-0-4
		@valgrind ./avl-0-5
		@valgrind ./avl-0-6
		@valgrind ./avl-0-7
		@valgrind ./avl-0-8
		@valgrind ./avl-0-9
		@valgrind ./avl-0-10

clean:
		rm -f vgcore.* *.o $(EXECUTABLES)
