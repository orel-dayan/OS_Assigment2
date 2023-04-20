AR=ar
CC=gcc
FLAGS= -Wall -g
all: cmp copy encode decode stshell

clean:
	rm -f *.o *.so  *.a cmp copy encode decode stshell

cmp: cmp.o
	$(CC) $(FLAGS) -o cmp cmp.o

cmp.o: cmp.c
	$(CC) $(FLAGS) -c cmp.c


copy: copy.o
	$(CC) $(FLAGS) -o copy copy.o

copy.o: copy.c
	$(CC) $(FLAGS) -c copy.c

libcodecA: libcodecA.so
libcodecA.so: codecA.o
	$(CC) -shared -fPIC -o libcodecA.so codecA.o
codecA.o: codecA.c codec.h
	$(CC) $(FLAGS) -c codecA.c

libcodecB: libcodecB.so
libcodecB.so: codecB.o
	$(CC) -shared -fPIC  -o libcodecB.so codecB.o
codecB.o: codecB.c codec.h
	$(CC) $(FLAGS) -c codecB.c

encode: encode.o libcodecA.so libcodecB.so
	$(CC) $(FLAGS) -o encode encode.o ./libcodecA.so -ldl
	$(CC) $(FLAGS) -o encode encode.o ./libcodecB.so -ldl
encode.o: encode.c
	$(CC) $(FLAGS) -c encode.c -ldl

decode: decode.o libcodecA.so libcodecB.so
	$(CC) $(FLAGS) -o decode decode.o ./libcodecA.so -ldl
	$(CC) $(FLAGS) -o decode decode.o ./libcodecB.so -ldl
decode.o: decode.c
	$(CC) $(FLAGS) -c decode.c -ldl

stshell: stshell.o
		$(CC) $(FLAGS) -o stshell stshell.o

stshell.o: stshell.c stshell.h
	$(CC) $(FLAGS) -c stshell.c
