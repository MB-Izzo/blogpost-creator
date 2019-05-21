/**
 * @file utils.c
 * @author Mathieu Bouchonnet
 * @brief Utils header
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

/**
 * @brief Contains date information as string.
 * 
 */
typedef struct {
    char *year;
    char *month;
    char *day;
    char *formated_date;
} date;

/**
 * @brief Contains info related to the passed argument.
 * 
 */
typedef struct {
    char *original_title;
    char *full_title;
    char *destination_path;
} arg_info;

date get_date();
char* get_formated_number(int nbr);
arg_info get_arg_info(char *arg_title, date curr_date);
void format_argument(char *argument);
char* replace_char(char *str, char find, char replace);
void str_to_lower(char *str);
int create_file();
void write_title(FILE *file, char *title);