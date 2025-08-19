#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int has_extension(const char* filename, const char* ext);

char* read_file(const char* filename);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        char* content = read_file(argv[1]);
        if (content) {
            printf("%s\n", content);
            free(content); // free memory when done
        }
    } else {
        printf("Usage: %s <filename>\n", argv[0]);
    }
    return 0;
}

int has_extension(const char* filename, const char* ext) {
    const char *dot = strrchr(filename, '.'); // find last '.'
    if (!dot || dot == filename) return 0;    // no extension or filename starts with '.'
    return strcmp(dot + 1, ext) == 0;
}

// Function to read file contents into a string
char* read_file(const char* filename) {
    FILE *f = fopen(filename, "r+");
    if (!f) {
        printf("Could not open file: %s\n", filename);
        return NULL;
    }

    // Find file size
    fseek(f, 0, SEEK_END);
    if (has_extension(filename, "txt")) {
        fprintf(f, "%s", "\nThis file has been viewed by Cat :D\n");
    }
    else if (has_extension(filename, "py")) {
        fprintf(f, "%s", "\n#This file has been viewed by Cat :D\n");
    }
    else if (has_extension(filename, "js")) {
        fprintf(f, "%s", "\n//This file has been viewed by Cat :D\n");
    }
    if (has_extension(filename, "lua")) {
        fprintf(f, "%s",  "\n-- This file has been viewed by Cat :D\n");
    }
    long size = ftell(f);
    rewind(f);

    // Allocate buffer (+1 for null terminator)
    char *buffer = malloc(size + 1);
    if (!buffer) {
        printf("Memory allocation failed\n");
        fclose(f);
        return NULL;
    }

    // Read file into buffer
    fread(buffer, 1, size, f);
    buffer[size] = '\0'; // Null-terminate

    fclose(f);
    return buffer;
}
