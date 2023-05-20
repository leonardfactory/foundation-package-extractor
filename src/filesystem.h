#ifndef LF_FILESYSTEM
#define LF_FILESYSTEM

#include <stdint.h>

char* get_dest_folder(char *filename);
void change_dir(char *path);
uint8_t read_uint8(FILE *file);
uint32_t read_uint32(FILE *file);
uint64_t read_uint64(FILE *file);
void read_string(uint8_t* buffer, size_t len, FILE *file);

#endif /* LF_FILESYSTEM */
