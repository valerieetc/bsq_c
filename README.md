# Welcome to My Bsq
***

## Description
The program finds the biggest square on a map consisting of free spaces '.' and obstacles 'o'.
When the biggest square is found, the map gets printed with the square filled in with 'x'.
The biggest square calculation uses the principles of dynamic programming that ensures that nothing 
gets calculated twice.

## Installation
You can install the program by running make.
As a prerequisite you need to have a GCC compiler and the Make utility.

## Usage
To run the program you first need to generate a map with the script which is stored in map.pl.
You can run the script the following way:
```
perl map.pl [width] [height] [density] > [filename]
```
The width and height should be equal as per the task requirements.
You can then run the My Bsq program the following way:
```
./my_bsq [name of file with map]
```
