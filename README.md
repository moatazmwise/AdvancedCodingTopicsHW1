# Advanced Topics in programming  hw1 

## This project is submitted by:
      
      Moataz mwise:206855835


      Hala Dabbah:322728148


## Requirements:

    c++20 or later .
      
    Standard STL libraries: <vector>, <queue>, <string>, <unordered_map>, <algorithm>, <iostream> ,<thread>, <chrono>,<fstream>.

## input file 
  
  the input file should end with .txt 

  each row that represents a row on the game board should start with ~.

  the dimensions of the game board are given to us in the input file  in the format : dimensions: y x z.

  The initial positions of the players on the board are provided in the input file, formatted as: player1: a x b, where 'a' is a value between 0 and the number of rows - 1, and 'b' is a value between 0 and the number of columns - 1."
## comipling: 
    
    the homework should compile on linux with gcc 11.4 or above, with the flags:

    ```bash

    g++ -std=c++20 -Wall -Wextra -Werror -pedantic

    ```
## General Instructions
Open a terminal and navigate to the AdvancedCodingTopicsHW1  directory:

```bash

cd /path/to/AdvancedCodingTopicsHW1
```


## to build the project , simply run

```bash

    make

```
## to run the game after building with file named "input_file.txt":

```bash

    ./tanks_game input_file.txt

```
## output files 

During execution, the program may generate the following output files:

    1: input_errors.txt , to this file we print errors we encountered during reading the input file.
    2:OutputLog.txt , this file conatins the prints that describe the behaviour of the tanks during the game.
    3:output_a.txt
    4:output_b.txt
   

