#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"

struct date;

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

date get_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char *year = get_formated_number(tm.tm_year + 1900);
    char *month = get_formated_number(tm.tm_mon + 1);
    char *day = get_formated_number(tm.tm_mday);

    date curr_date = {year, month, day};
    return curr_date;
}

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

void format_argument(char *argument)
{
    replace_char(argument, ' ', '-');
    str_to_lower(argument);
}