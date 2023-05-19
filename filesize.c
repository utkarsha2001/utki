#include <stdio.h>

int main() {
    FILE *file;
    char filename[100];
    long size;

    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file in binary mode
    file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Seek to the end of the file
    fseek(file, 0, SEEK_END);

    // Get the position which indicates the size of the file
    size = ftell(file);

    printf("The size of the file is %ld bytes.\n", size);

    // Close the file
    fclose(file);

    return 0;
}
