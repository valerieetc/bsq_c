#ifndef MY_BSQ_H
#define MY_BSQ_H

typedef struct {
    int size;
    char** array;
} string_array;

//struct for storing coordinates of bottom right point of biggest square
typedef struct {
    int value;
    int row;
    int col;
} square_coord;

int my_strlen(char* str);
int my_atoi(char* str);
void copy_int_arr(int* current, int* prev, int m_size);
int smallest_cell(int num1, int num2, int num3);
void print_row(char* arr, int coord, int size);
void print_map(string_array* map_array, int m_size, square_coord max_square);
void find_biggest_square(string_array* map_array, int m_size, square_coord* max_square);

#endif