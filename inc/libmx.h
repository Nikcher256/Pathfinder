#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ISLANDS 100
#define BUFFER_SIZE 1024

typedef struct {
    char island1[50];
    char island2[50];
    int length;
} Bridge;

typedef struct {
    int num_islands;
    char **island_names;                      // Array of island names
    int distances[MAX_ISLANDS][MAX_ISLANDS];  // Adjacency matrix for distances
} Graph;

// Function prototypes
size_t mx_strlen(const char *s);
char *mx_strcat(char *dst, const char *src);
long long mx_atoll(const char *str);
char *mx_strdup(const char *s1);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_isdigit(char c);
void mx_printint(int n);
char *mx_strcpy(char *dst, const char *src);
void mx_printf(const char *format, const char *arg1, const char *arg2, const char *arg3);
void *mx_realloc(void *ptr, size_t size);
char *mx_strchr(const char *s, int c);
char *mx_itoa(int number);
void mx_printstr(const char *s);
int mx_atoi(const char *str);
int mx_strcmp(const char *s1, const char *s2);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
bool is_digit_string(const char *str);

void handle_error(const char *message);
void handle_line_error(const char *message, int line);
int is_valid_bridge_line(const char *line);
void handle_file_error(const char *message, const char *filename);
void parse_file(const char *filename, Graph *graph);
int read_file(const char *filename, char **content);
int get_next_line(char **content, char **line);

// Utility functions for parsing
bool add_island(Graph *graph, const char *island, int pos);
int find_island_index(Graph *graph, const char *island);

void pathfinder(Graph *graph);
