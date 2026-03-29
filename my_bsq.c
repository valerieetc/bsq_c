#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_bsq.h"


int main(int argc, char** argv) {

    if (argc != 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        printf("File '%s' does not exist\n", argv[1]);
        return 1;
    }

    //gets size of the map from the first line of file
    char mapsize[10000];
    mapsize[0] = '\0';
    char c = 0;
    int i = 0;
    read(fd, &c, 1);
    while (c != '\n') {
        mapsize[i] = c;
        i++;
        read(fd, &c, 1);
    }
    mapsize[i] = '\0';

    //converts map size to int
    int m_size = my_atoi(mapsize);

    //copies map to string array
    string_array* map_array = malloc(sizeof(string_array));
    map_array->size = m_size;
    map_array->array = malloc(m_size * sizeof(char*));

    for (int row = 0; row < m_size; row++) {
        map_array->array[row] = malloc((m_size + 1) * sizeof(char));
        read(fd, map_array->array[row], m_size + 1);
        map_array->array[row][m_size] = '\0';
    }

    //struct to save bottom right point of biggest square
    square_coord max_square;
    max_square.value = 0;
    max_square.row = 0;
    max_square.col = 0;

    find_biggest_square(map_array, m_size, &max_square);

    //gets top left point of biggest square instead of bottom right
    max_square.row = max_square.row - (max_square.value - 1);
    max_square.col = max_square.col - (max_square.value - 1);

    //prints result
    print_map(map_array, m_size, max_square);

    for (int j = 0; j < map_array->size; j++) {
        free(map_array->array[j]);
    }
    free(map_array->array);
    free(map_array);

    close(fd);
}

//custom implementation of strlen from string.h
int my_strlen(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

//transforms number as string to int
int my_atoi(char* str) {
    int len = my_strlen(str);
    int result = 0;
    for (int i = 0; i < len; i++) {
        result *= 10;
        int n = str[i] - 48;
        result += n;
    }
    return result;
}

//copies one int array into another
void copy_int_arr(int* current, int* prev, int m_size) {
    for (int i = 0; i < m_size; i++) {
        prev[i] = current[i];
    }
}

//gets the smallest int of three
int smallest_cell(int num1, int num2, int num3) {
    if (num1 <= num2 && num1 <= num3) {
        return num1;
    } else if (num2 <= num1 && num2 <= num3) {
        return num2;
    } else {
        return num3;
    }
}

//calculates size of square in current position
//positions are evaluated left to right, top to bottom
//every position is evaluated as a bottom right corner of a square 
void find_biggest_square(string_array* map_array, int m_size, square_coord* max_square) {
    int* prev = malloc((m_size) * sizeof(int));
    for (int j = 0; j < m_size; j++) {
        prev[j] = 0;
    }

    int* current = malloc((m_size) * sizeof(int));
    
    for (int row = 0; row < m_size; row++) {
        for (int j = 0; j < m_size; j++) {
            if (map_array->array[row][j] == '.') {
                if (j == 0) {
                    current[j] = smallest_cell(0, prev[j], 0) + 1;
                } else {
                    current[j] = smallest_cell(current[j - 1], prev[j], prev[j - 1]) + 1;
                }
            } else if (map_array->array[row][j] == 'o') {
                current[j] = 0;
            }

            if (current[j] > max_square->value) {
                max_square->value = current[j];
                max_square->row = row;
                max_square->col = j;
            }
        }
        copy_int_arr(current, prev, m_size);
    }

    free(prev);
    free(current);
}

//prints one row with '.' replaced by 'x'
void print_row(char* arr, int coord, int size) {
    for (int i = 0; i < coord; i++) {
        printf("%c", arr[i]);
    }

    for (int i = coord; i < coord + size; i++) {
        printf("x");
    }

    for (int i = coord + size; i < my_strlen(arr); i++) {
        printf("%c", arr[i]);
    }

    printf("\n");
}

//prints all map
void print_map(string_array* map_array, int m_size, square_coord max_square) {
    for (int row = 0; row < max_square.row; row++) {
        printf("%s\n", map_array->array[row]);    
    }

    for (int row = max_square.row; row < max_square.row + max_square.value; row++) {
        print_row(map_array->array[row], max_square.col, max_square.value);

    }

    for (int row = max_square.row + max_square.value; row < m_size; row++) {
        printf("%s\n", map_array->array[row]); 
    }
}
