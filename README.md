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


## Requirements
- Ubuntu 22.04 LTS
- GNU C compiler
- Make


## Authors

- Orel Dayan

## Stshell Example :


