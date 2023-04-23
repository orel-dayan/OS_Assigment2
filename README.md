# Operating System Course Assigment 2

University assignment 2 for Operating System  course
### For Computer Science B.S.c Ariel University

## Description
The task is made of 3 parts: files operations, dynamic libraries, and basic shell (see below for details).
All the code is written in C language. The code is compiled using the GNU C compiler, and the make utility.


### Task A
In this task we will implement 2 tools: cmp and copy.

- **Compare** -
 cmp tool will compare two files, and return “0” if they are equal, and “1” if not (return an INT).The tool will support -v flag for verbose output. By this we mean that the tool will print “equal” or “distinct”, in addition to returning the int value.The toll will support -i flag, that mean “ignore case” so “AAA” and “aaa” meaning equals.

-  **Copy** -
  copy tool will copy the content of file1 to file2. The tool will support -v flag for verbose output. By this we mean that the tool will print “success” or “general faliure”, in addition to returning the int value.The toll will support -f flag, that mean “force” so if file2 exists, it will be overwritten. If file2 does not exist, it will be created. If file2 exists and -f flag is not used, the tool will print “target file exists” and return 1.

## Run

```sh
 make cmp
   ./cmp <file1> <file2> -v -i
 make copy
   ./copy <file1> <file2> -v -f
   ```
## Task B

In this task we will implement a simple encoder and decoder. The encoder will get a message and a codec, and will encode the message using the codec. The decoder will get a message and a codec, and will decode the message using the codec.
we implemented 2 codecs: codecA and codecB. codecA and codecB are shared libraries (libcodecA.so and libcodecB.so). codecA  convert all lower case chars to upper case, and all upper case to lower case. All other chars will remain unchanged. codecB convert all chars to the 3-rd next char (adding a number of 3 to the ASCII value). The codecs are reversiable functions, meaning they have encoders and decoders.




## Run

```sh
 make encode decode
 ./encode <codec> <message>
 ./decode <codec> <message>

   ```

 ## Task C

In this task we will implement a simple shell. The shell will support the following features:
1. Be able to run CMD tools that exist on system (e.g. ls, cat, etc.).
2. Be able to stop running tool by pressing `Ctrl+C`, but not killing the shell itself.
3.Be able to redirect output with “>” and “>>”, and allow piping with “|” ( support more than 2 pipes)
4. Be able to stop itself by `exit` command.
5. we  also support `clear` that clear the screen .



 ## Run

```sh
   make stshell
   ./stshell
   ```


## Requirements
- Ubuntu 22.04 LTS
- GNU C compiler
- Make


## Authors

- Orel Dayan
- Evyatar Yosef

## Run Example :
all the files and the pictures in the folder "examples" in the repository.

we ran stshell, and we ran some commands, you can see the picture below.
we also ran the cmp copy decode encode in the same shell.


some comments:
- The files file1.txt and file2.txt are identical, file3.txt is identical except for changes in capital letters.
- we copied by force the content of file1.txt to copy.txt that already exists, and we can see that the content of copy.txt was overwritten.
- we copied -v the content of file1.txt to newCopy.txt that does not exist, and we can see that the content of newCopy.txt was created.
- we redirected the output of ls to file4.txt, and we can see that the content of file4.txt was created.


![Screenshot from 2023-04-22 22-55-10](https://user-images.githubusercontent.com/117816462/233805358-19f8144c-8b2d-44c4-804a-6514303d5a51.png)

![Screenshot from 2023-04-23 11-07-44](https://user-images.githubusercontent.com/117816462/233828137-1942e29b-9354-4495-aefd-568e77023c9a.png)




## Bibliography
- https://stackoverflow.com/questions/30226530/same-file-descriptor-after-fork
- https://www.qnx.com/developers/docs/6.4.0/neutrino/lib_ref/f/fork.html
- https://www.geeksforgeeks.org/making-linux-shell-c/
- https://www.geeksforgeeks.org/fork-system-call/
- https://dev.to/ifenna__/adding-colors-to-bash-scripts-48g4

