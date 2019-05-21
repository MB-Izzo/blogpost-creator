// main.c
// Create a blogpost file and open it automatically.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 200

char* replace_char(char *str, char find, char replace);
void str_to_lower(char *str);
char* get_formated_number(int nbr);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Must give a title to the blog post!\n");
        return 1;
    }

    char *arg_title = NULL;
    if (argv[1] != NULL || argv[1] != "")
    {
        arg_title = argv[1];
    }

    // Get our current time/date information.
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char *year = get_formated_number(tm.tm_year + 1900);
    char *month = get_formated_number(tm.tm_mon + 1);
    char *day = get_formated_number(tm.tm_mday);

    // Format full date to yyyy-mm-dd
    char date[15];
    snprintf(date, sizeof(date), "%s-%s-%s", year, month, day);

    // Save the original title.
    char arg_title_original[BUFFER_SIZE];
    memset(arg_title_original, '\0', sizeof(arg_title_original));
    strcpy(arg_title_original, arg_title);

    // Format artgument
    replace_char(arg_title, ' ', '-');
    str_to_lower(arg_title);

    // Concatenate to create the full title.
    char full_title[BUFFER_SIZE];
    snprintf(full_title, sizeof(full_title), "%s-%s.md", date, arg_title);

    printf("%s\n", full_title);

    char destination[BUFFER_SIZE];
    snprintf(destination, sizeof(destination), "/home/mathieu/Documents/mb-izzo.github.io/_posts/%s", full_title);
    
    // Open/create file
    FILE *file;
    file = fopen(destination, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to create file - %s.\n", strerror(errno));
        return 1;
    }

    // Write title to file.
    int i;
    for (i = 0; i < 3; i++)
    {
        if (i == 1)
            fprintf(file, "title: %s\n", arg_title_original);
        else
            fprintf(file, "---\n");
    }
    fclose(file);

    // Launch created file with vscode.
    if (execl("/snap/bin/code", "/snap/bin/code", destination, NULL) == -1)
    {
        fprintf(stderr, "Error launching vscode: %s", strerror(errno));
        return 1;
    }

    return 0;
}

char* replace_char(char *str, char find, char replace)
{
    char *curr_pos = strchr(str, find);
    while (curr_pos) {
        *curr_pos = replace;
        curr_pos = strchr(curr_pos, find);
    }
    return str;
}

void str_to_lower(char *str)
{
    for(int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

char* get_formated_number(int nbr)
{
    int length = snprintf(NULL, 0, "%d", nbr);
    char *str = malloc(length + 1);
    if (length == 1)
    {
        snprintf(str, 3, "%d", nbr);
        str[1] = str[0];
        str[0] = '0';
        str[2] = '\0';
    }
    else
    {
        snprintf(str, length + 1, "%d", nbr);
    }
    return str;
}


