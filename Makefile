AR=ar
CC=gcc
FLAGS= -Wall -g
SRC_DIR=sources
OBJ_DIR=objects

all: cmp copy encode decode stshell

clean:
	rm -rf $(OBJ_DIR)/*.o *.so *.a cmp copy encode decode stshell

stshell: $(OBJ_DIR)/stshell.o
	$(CC) $(FLAGS) -o stshell $(OBJ_DIR)/stshell.o

$(OBJ_DIR)/stshell.o: $(SRC_DIR)/stshell.c $(SRC_DIR)/stshell.h
	$(CC) $(FLAGS) -c $(SRC_DIR)/stshell.c -o $(OBJ_DIR)/stshell.o

cmp: $(OBJ_DIR)/cmp.o
	$(CC) $(FLAGS) -o cmp $(OBJ_DIR)/cmp.o

$(OBJ_DIR)/cmp.o: $(SRC_DIR)/cmp.c
	$(CC) $(FLAGS) -c $(SRC_DIR)/cmp.c -o $(OBJ_DIR)/cmp.o

copy: $(OBJ_DIR)/copy.o
	$(CC) $(FLAGS) -o copy $(OBJ_DIR)/copy.o

$(OBJ_DIR)/copy.o: $(SRC_DIR)/copy.c
	$(CC) $(FLAGS) -c $(SRC_DIR)/copy.c -o $(OBJ_DIR)/copy.o

libcodecA: libcodecA.so
libcodecA.so: $(OBJ_DIR)/codecA.o
	$(CC) -shared -fPIC -o libcodecA.so $(OBJ_DIR)/codecA.o

$(OBJ_DIR)/codecA.o: $(SRC_DIR)/codecA.c $(SRC_DIR)/codec.h
	$(CC) $(FLAGS) -c $(SRC_DIR)/codecA.c -o $(OBJ_DIR)/codecA.o

libcodecB: libcodecB.so
libcodecB.so: $(OBJ_DIR)/codecB.o
	$(CC) -shared -fPIC -o libcodecB.so $(OBJ_DIR)/codecB.o

$(OBJ_DIR)/codecB.o: $(SRC_DIR)/codecB.c $(SRC_DIR)/codec.h
	$(CC) $(FLAGS) -c $(SRC_DIR)/codecB.c -o $(OBJ_DIR)/codecB.o

encode: $(OBJ_DIR)/encode.o libcodecA.so libcodecB.so
	$(CC) $(FLAGS) -o encode $(OBJ_DIR)/encode.o ./libcodecA.so -ldl
	$(CC) $(FLAGS) -o encode $(OBJ_DIR)/encode.o ./libcodecB.so -ldl

$(OBJ_DIR)/encode.o: $(SRC_DIR)/encode.c
	$(CC) $(FLAGS) -c $(SRC_DIR)/encode.c -o $(OBJ_DIR)/encode.o -ldl

decode: $(OBJ_DIR)/decode.o libcodecA.so libcodecB.so
	$(CC) $(FLAGS) -o decode $(OBJ_DIR)/decode.o ./libcodecA.so -ldl
	$(CC) $(FLAGS) -o decode $(OBJ_DIR)/decode.o ./libcodecB.so -ldl

$(OBJ_DIR)/decode.o: $(SRC_DIR)/decode.c
	$(CC) $(FLAGS) -c $(SRC_DIR)/decode.c -o $(OBJ_DIR)/decode.o -ldl
