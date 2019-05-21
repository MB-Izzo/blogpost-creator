/**
 * @file utils.c
 * @author Mathieu Bouchonnet
 * @brief Contains function implementations
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "utils.h"

/**
 * @brief Buffer size for malloc.
 * 
 */
#define BUFFER_SIZE 300

struct date;
struct arg_info;

/**
 * @brief Get the current date struct
 * 
 * @return date struct 
 */
date get_date()
{

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char *year = get_formated_number(tm.tm_year + 1900);
    char *month = get_formated_number(tm.tm_mon + 1);
    char *day = get_formated_number(tm.tm_mday);

    char *full_date = malloc(sizeof(char) * 15);
    snprintf(full_date, sizeof(char) * 15, "%s-%s-%s", year, month, day);

    date curr_date = {year, month, day, full_date};
    return curr_date;
}

/**
 * @brief Format a number to a string
 * 
 * @param nbr number to format
 * @return char* formated number
 */
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

/**
 * @brief Get the arg info struct
 * 
 * @param arg_title the first argument in cmd line 
 * @param curr_date the curr_date struct
 * @return arg_info struct
 */
arg_info get_arg_info(char *arg_title, date curr_date)
{
    char *arg_title_original = malloc(sizeof(char) * BUFFER_SIZE);
    memset(arg_title_original, '\0', sizeof(char) * BUFFER_SIZE);
    strcpy(arg_title_original, arg_title);

    format_argument(arg_title);

    // Concatenate to create the full title.
    char *full_title = malloc(sizeof(char) * BUFFER_SIZE);
    snprintf(full_title, sizeof(char) * BUFFER_SIZE, "%s-%s.md", curr_date.formated_date, arg_title);

    char *destination_path = malloc(sizeof(char) * BUFFER_SIZE);
    snprintf(destination_path, sizeof(char) * BUFFER_SIZE,
    "/home/mathieu/Documents/mb-izzo.github.io/_posts/%s", full_title);

    arg_info info = {arg_title_original, full_title, destination_path};
    return info;
}

/**
 * @brief format the argument title to avoid spaces
 * and -.
 * 
 * @param argument the string to format
 */
void format_argument(char *argument)
{
    replace_char(argument, ' ', '-');
    str_to_lower(argument);
}

/**
 * @brief replace a char by another
 * 
 * @param str the string to apply the replace
 * @param find the character to replace
 * @param replace the new character
 * @return char* the formated string
 */
char* replace_char(char *str, char find, char replace)
{
    char *curr_pos = strchr(str, find);
    while (curr_pos) {
        *curr_pos = replace;
        curr_pos = strchr(curr_pos, find);
    }
    return str;
}

/**
 * @brief lower a string
 * 
 * @param str the string to lower
 */
void str_to_lower(char *str)
{
    for(int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

/**
 * @brief Create the blogpost file.
 * 
 * @param arguments arguments information
 * @return int success or failure
 */
int create_file(arg_info arguments)
{
    FILE *file;
    file = fopen(arguments.destination_path, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to create file - %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    write_title(file, arguments.original_title);
    fclose(file);

    // Launch created file with vscode.
    if (execl("/snap/bin/code", "/snap/bin/code", arguments.destination_path, NULL) == -1)
    {
        fprintf(stderr, "Error launching vscode: %s", strerror(errno));
        return EXIT_FAILURE;
    }
}

/**
 * @brief Write the title to the blogpost file.
 * 
 * @param file the file where we write the title
 * @param title title to write
 */
void write_title(FILE *file, char *title)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (i == 1)
            fprintf(file, "title: %s\n", title);
        else
            fprintf(file, "---\n");
    }
}