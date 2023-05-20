#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
    #include <direct.h>
#else
    #include <unistd.h>
#endif

/*
 * Returns the folder name of the package, replacing the extension with an underscore.
 */
char* get_dest_folder(char *filename) {
    char *folder_name = malloc(strlen(filename) + 1);
    strcpy(folder_name, filename);
    char *dot = strrchr(folder_name, '.');
    if (dot == NULL) {
        printf("Error: '%s' has no extension\n", filename);
        exit(1);
    }
    *dot = '_';
    return folder_name;
}

/*
 * Changes the current directory to the given path, both on Unix and Windows.
 */
void change_dir(char *path) {
    #ifdef _WIN32
        _chdir(path);
    #else
        chdir(path);
    #endif
}

/**
 * Reads a uint8_t from a file.
 */ 
uint8_t read_uint8(FILE *file) {
    uint8_t value;
    if (fread(&value, sizeof(uint8_t), 1, file) != 1) {
        perror("Error while reading uint8_t");
        exit(1);
    }
    return value;
}

/**
 * Reads a uint32_t from a file.
 */ 
uint32_t read_uint32(FILE *file) {
    uint32_t value;
    if (fread(&value, sizeof(uint32_t), 1, file) != 1) {
        perror("Error while reading uint32_t");
        exit(1);
    }
    return value;
}

/**
 * Reads a uint64_t from a file.
 */ 
uint64_t read_uint64(FILE *file) {
    uint64_t value;
    if (fread(&value, sizeof(uint64_t), 1, file) != 1) {
        perror("Error while reading uint64_t");
        exit(1);
    }
    return value;
}

/**
 * Reads a char (uint8_t) string from a file.
 */ 
void read_string(uint8_t* buffer, size_t len, FILE *file) {
    if (fread(buffer, sizeof(uint8_t), len, file) != len) {
        perror("Error while reading string");
        exit(1);
    }
    buffer[len] = 0;
}