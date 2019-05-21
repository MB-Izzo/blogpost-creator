// main.c
// Create a blogpost file and open it automatically.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "utils.h"

#define BUFFER_SIZE 300

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Must give a title to the blog post!\n");
        return EXIT_FAILURE;
    }

    char *arg_title;
    if (argv[1] != NULL)
    {
        arg_title = argv[1];
    }
    
    // Get our current time/date information.
    date curr_date = get_date();
    printf("%s\n", curr_date.formated_date);

    // Save the original title.
    char arg_title_original[BUFFER_SIZE];
    memset(arg_title_original, '\0', sizeof(arg_title_original));
    strcpy(arg_title_original, arg_title);

    format_argument(arg_title);

    // Concatenate to create the full title.
    char full_title[BUFFER_SIZE];
    snprintf(full_title, sizeof(full_title), "%s-%s.md", curr_date.formated_date, arg_title);

    char destination[BUFFER_SIZE];
    snprintf(destination, sizeof(destination), "/home/mathieu/Documents/mb-izzo.github.io/_posts/%s", full_title);
    
    // Open/create file
    FILE *file;
    file = fopen(destination, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to create file - %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    write_title(file, arg_title_original);
    fclose(file);

    // Launch created file with vscode.
    if (execl("/snap/bin/code", "/snap/bin/code", destination, NULL) == -1)
    {
        fprintf(stderr, "Error launching vscode: %s", strerror(errno));
        return EXIT_FAILURE;
    }

    free(curr_date.day);
    free(curr_date.year);
    free(curr_date.month);
    free(curr_date.formated_date);
    return EXIT_SUCCESS;
}