#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Check if it's a regular file
            printf("%s\n", entry->d_name);
            file_count++;
        }
    }

    closedir(dir);

    printf("Total number of files: %d\n", file_count);

    return 0;
}
