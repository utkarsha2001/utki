Open a file goes to sleep for 15 seconds before terminating.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *file;

    // Open the file
    file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Perform any necessary operations with the file here

    // Sleep for 15 seconds
    sleep(15);

    // Close the file
    fclose(file);

    return 0;
}
                                                  