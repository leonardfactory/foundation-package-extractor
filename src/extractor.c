#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
// #include <unistd.h>
#include "filesystem.h"

void process_children(FILE *package, uint32_t data_offset, uint32_t children_count, uint32_t depth);

int main(int argc, char **argv) {
    // Check for arguments
    if (argv[1] == NULL) {
        printf("Usage: ./extractor.exe <package>\n");
        return 1;
    }

    // Check for file existence
    FILE *package = fopen(argv[1], "rb");
    if (package == NULL) {
        printf("An error occurred while opening '%s'\n", argv[1]);
        perror("Error");
        return 1;
    }

    char *folder_name = get_dest_folder(argv[1]);
    printf("Start extraction of '%s' in '%s'...\n", argv[1], folder_name);
    if (mkdir(folder_name) != 0) {
        printf("An error occurred while creating dest folder '%s'\n", folder_name);
        perror("Error");
        return 1;
    }

    change_dir(folder_name);
    uint32_t version_number = read_uint32(package);
    printf("(Version number: %d)\n", version_number);

    uint8_t uuid[33];
    read_string(uuid, 32, package);
    printf("(UUID: %s)\n", uuid);

    uint32_t data_offset = read_uint32(package);
    uint32_t total_files_count = read_uint32(package); // Maybe? Not used
    uint32_t root_dir_children_count = read_uint32(package);
    printf("(Data offset: %d, Files count: %d, Root dir children count: %d)\n", data_offset, total_files_count, root_dir_children_count);

    process_children(package, data_offset, root_dir_children_count, 0);
}

void process_children(FILE *package, uint32_t data_offset, uint32_t count, uint32_t depth) {
    for (uint32_t i = 0; i < count; i++) {
        uint32_t name_length = read_uint32(package);

        char *name = malloc(name_length + 1);
        read_string(name, name_length, package);

        uint8_t is_dir = read_uint8(package);
        
        if (is_dir) {
            printf("%*s%s\n", depth * 4, "", name);
            uint32_t children_count = read_uint32(package);
            read_uint32(package); // Another offset?

            mkdir(name);
            change_dir(name);
            process_children(package, data_offset, children_count, depth + 1);
            change_dir("..");
        } else {
            process_file(package, name, data_offset, depth);
        }

        free(name);
    }
}

void process_file(FILE *package, char *file_name, uint32_t data_offset, uint32_t depth) {
    uint64_t file_offset = read_uint64(package); 
    uint64_t file_size = read_uint64(package);
    printf("%*s%s (%d bytes)\n", depth * 4, "", file_name, file_size);

    int64_t saved_position = ftell64(package);
    uint64_t final_start_offset = (uint64_t)data_offset + file_offset;
    fseek64(package, final_start_offset, SEEK_SET);
    
    uint8_t *buffer = malloc(file_size);
    if (fread(buffer, file_size, 1, package) != 1 && file_size > 0) {
        printf("An error occurred while reading File '%s' buffer (Offset 0x%08X)\n", file_name, file_offset);
        perror("Error");
        exit(1);
    }

    FILE *file = fopen(file_name, "wb");
    fwrite(buffer, file_size, 1, file);
    fclose(file);

    free(buffer);
    // Reset file position
    fseek64(package, saved_position, SEEK_SET);
}

