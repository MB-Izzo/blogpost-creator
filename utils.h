typedef struct {
    char *year;
    char *month;
    char *day;
} date;

char* replace_char(char *str, char find, char replace);
void str_to_lower(char *str);
char* get_formated_number(int nbr);
date get_date();
void write_title(FILE *file, char *title);
void format_argument(char *argument);