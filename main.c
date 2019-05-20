// main.c
// Create a blogpost file and open it automatically.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* replace_char(char *str, char find, char replace);
void str_to_lower(char *str);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Must give a name to blog post!");
        return 1;
    }

    char *arg_title = NULL;
    if (argv[1] != NULL || argv[1] != "")
    {
        arg_title = argv[1];
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int y = tm.tm_year + 1900; 
    int length = snprintf(NULL, 0, "%d", y);
    char *year = malloc(length + 1);
    snprintf(year, length + 1, "%d", y); 
    

    int m = tm.tm_mon + 1;
    length = snprintf(NULL, 0, "%d", m);
    char *month = malloc(length + 1); 
    if (length == 1)
    {
        snprintf(month, 3, "%d", m); 
        month[1] = month[0];
        month[0] = '0';
        month[2] = '\0';
    }
    else
    {
        snprintf(month, length + 1, "%d", m);
    }


    int d = tm.tm_mday;
    length = snprintf(NULL, 0, "%d", d);
    char *day = malloc(length + 1);
    if (length == 1)
    {
        snprintf(day, 3, "%d", d);
        day[1] = day[0];
        day[0] = '0';
        day[2] = '\0';
    }
    else
    {
        snprintf(day, length + 1, "%d", d);
    }

    char date[15];
    snprintf(date, sizeof(date), "%s-%s-%s", year, month, day);
    printf("%s\n", date);
    replace_char(arg_title, ' ', '-');
    printf("%s\n", arg_title);
    str_to_lower(arg_title);
    printf("%s\n", arg_title);
    char full_title[200];
    snprintf(full_title, sizeof(full_title), "%s-%s.md", date, arg_title);
    printf("%s\n", full_title);
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