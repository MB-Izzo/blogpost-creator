/**
 * @file main.c
 * @author Mathieu Bouchonnet
 * @brief main file
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Must give a title to the blog post!\n");
        return EXIT_FAILURE;
    }

    char *arg_title;
    if (argv[1] != NULL)
        arg_title = argv[1];
    
    date curr_date = get_date();

    arg_info arguments = get_arg_info(arg_title, curr_date);

    create_file(arguments);

    free(curr_date.day);
    free(curr_date.year);
    free(curr_date.month);
    free(curr_date.formated_date);
    free(arguments.full_title);
    free(arguments.original_title);
    free(arguments.destination_path);

    return EXIT_SUCCESS;
}