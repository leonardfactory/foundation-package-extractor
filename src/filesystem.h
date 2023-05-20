#ifndef LF_FILESYSTEM
#define LF_FILESYSTEM

#include <stdint.h>

char* get_dest_folder(char *filename);
void change_dir(char *path);
uint8_t read_uint8(FILE *file);
uint32_t read_uint32(FILE *file);
uint64_t read_uint64(FILE *file);
void read_string(uint8_t* buffer, size_t len, FILE *file);
int fseek64(FILE *file, uint64_t offset, int origin);
int64_t ftell64(FILE *file);

#endif /* LF_FILESYSTEM */
