# Pathfinder
## Description: 
A C-based application that finds the shortest path between islands, reading from a file, and includes error handling for file operations and input validation.
## Features:
- Efficient memory management using custom mx_memcpy, mx_realloc, and mx_memset functions.
- Error handling for invalid file content and incorrect formatting.
- Custom string manipulation functions (mx_strlen, mx_strcpy, etc.).
- Functionality to find multiple shortest paths between islands.
- Custom error messages for invalid lines and bridge formats.
## How to Build:
### Requirements: 
A C compiler (e.g., gcc), Makefile support, and optionally clang for warnings.
### Build the project using the command:
```
make
```

## Usage:
### Run the application:
```
./pathfinder <file>
```
Where <file> is the input file containing island and bridge data.
### Example Input File:
```
3
Island1-Island2,10
Island2-Island3,15
Island1-Island3,20
```
