# Operating System Course Assigment 2

University assignment 2 for Operating System  course
### For Computer Science B.S.c Ariel University

## Description

The task is made of 3 parts: files operations, dynamic libraries, and basic shell.

### Task A
- **Compare** -
  cmp tool compares two files and returns 1 if they are equal or 0 if not. The tool supports additional flags (-v , -i). -v for verbose output. -i to ignore case .

-  **Copy** -
copy tool will copy a source file to a destination file. The tool supports additional flags (-v, -f). -v for verbose output. -f will force copy (will rewrite existing file if needed).


## To run

```sh
 make cmp
   ./cmp <file1> <file2> -v -i
 make copy
   ./copy <file1> <file2> -v -f
   ```
## Task B

- **Libraries :**

   **CodecA**- makes swaps every big char to small and small to big.

   **CodecB** - adds 3 to ascii of every char.

- **Tools :**

   **Encode** - gets codec name and text, prints encoded text to the console

  **Decode**  - gets codec name and text, prints decodedd text to the console



## To run

```sh
 make encode decode
 ./encode <codec> <message>
 ./decode <codec> <message>

   ```

 ## Task C
 
 To run:

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

## Run Example :
After make all , we ran ./stshell.
#### Some comments:
- The files file1.txt and file2.txt are identical, file3.txt is identical except for changes in capital letters.

![Screenshot from 2023-04-22 22-55-10](https://user-images.githubusercontent.com/117816462/233805358-19f8144c-8b2d-44c4-804a-6514303d5a51.png)


## Bibliography
- https://stackoverflow.com/questions/30226530/same-file-descriptor-after-fork
- https://www.qnx.com/developers/docs/6.4.0/neutrino/lib_ref/f/fork.html
- https://www.geeksforgeeks.org/making-linux-shell-c/
- https://www.geeksforgeeks.org/fork-system-call/
- https://dev.to/ifenna__/adding-colors-to-bash-scripts-48g4

