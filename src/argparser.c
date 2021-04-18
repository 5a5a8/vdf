#include "argparser.h"
#include "error.h"
#include "globals.h"
#include "help.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


enum
{
    LFLAG_INVALID = 1,
    WFLAG_INVALID,
    FILENOTFOUND,
};


/*
 * Global variables for user-supplied arguments
 */
bool hFlag = false;
bool vFlag = false;
bool dFlag = false;
bool lFlag = false;
bool wFlag = false;
bool xFlag = false;


/*
 * argv indices for each flag
 */
size_t dFlagindex;
size_t lFlagindex;
size_t wFlagindex;

int64_t lFlaglow  =  1;
int64_t lFlaghigh = -2;

int argi;
char **args;

char *delim = ",";


void parse_cmd_args();
void check_args_valid();
void check_l_flag_valid();
void check_w_flag_valid();
void check_d_flag_valid();
void check_file_valid();
void parse_l_flag();


void
argparser_main()
{
    parse_cmd_args();

    if (hFlag) help();
    else if (vFlag) version();
    if (hFlag || vFlag) exit(EXIT_SUCCESS);

    check_args_valid();
    if (lFlag) parse_l_flag();

    extern char *delim;
    if (dFlag) delim = args[dFlagindex];
}


void
parse_cmd_args()
{
    if (argi > 1 && !strcmp(args[1], "--help"))
    {
        hFlag = true;
        return;
    }
    else if (argi == 1)
    {
        usage();
        exit(EXIT_FAILURE);
    }

    int opt;
    while ((opt = getopt(argi, args, "hvd:l:w:x")) != -1)
    {
        switch(opt)
        {
            case 'h':
                hFlag = true;
                break;
            case 'v':
                vFlag = true;
                break;
            case 'd':
                dFlag = true;
                dFlagindex = optind - 1;
                break;
            case 'l':
                lFlag = true;
                lFlagindex = optind - 1;
                break;
            case 'w':
                wFlag = true;
                wFlagindex = optind - 1;
                break;
            case 'x':
                xFlag = true;
                break;
            case '?':
                fprintf(stderr, "unknown argument: %c\n", optopt);
                exit(EXIT_FAILURE);
                break;
        }
    }
}


void
check_args_valid()
{
    if (lFlag) check_l_flag_valid();    
    if (wFlag) check_w_flag_valid();
    if (dFlag) check_d_flag_valid();
    check_file_valid();
}


void
check_d_flag_valid()
{
    printf("warning: function called not yet implemented\n");
}


void
check_l_flag_valid()
{
    size_t i;
    char c;
    int64_t dashcount = 0;
    for (i=0; (c = args[lFlagindex][i]) != '\0'; ++i)
    {
        if ((c < '0' || c > '9') && c != '-')
        {
            fprintf(stderr, "ERROR: -l flag may only contain digits and -\n");
            exit(LFLAG_INVALID);
        }
        
        if (c == '-') ++dashcount;
    }

    if (dashcount > 1)
    {
        fprintf(stderr, "ERROR: -l flag may only contain one - symbol\n");
        exit(LFLAG_INVALID);
    }
}


void
check_w_flag_valid()
{
    size_t i;
    char c;
    for (i=0; (c = args[wFlagindex][i]) != '\0'; ++i)
    {
        if (c < '0' || c > '9')
        {
            fprintf(stderr, "ERROR: -w flag must be a positive number\n");
            exit(WFLAG_INVALID);
        }
    }
}


void
check_file_valid()
{
    extern int optind;
    FILE *fp = fopen(args[optind], "r");
    if (fp == NULL)
    {
        fprintf(stderr,
            "ERROR: The given file could not be found: %s\n", args[optind]);
        exit(FILENOTFOUND);
    }
}


void
parse_l_flag()
{
    char *arg_string = args[lFlagindex];
    size_t arg_len = strlen(arg_string);

    char *l_low = malloc(arg_len + 1);
    char *l_high = malloc(arg_len + 1);

    size_t i, j;
    for (i=0; i<arg_len && arg_string[i] != '-'; ++i)
    {
        l_low[i] = arg_string[i];
    }
    
    l_low[i] = '\0';

    if (arg_string[i] == '-') ++i;

    for (j=0; i+j < arg_len && arg_string[i+j] != '-'; ++j)
    {
        l_high[j] = arg_string[i+j];
    }

    l_high[j] = '\0';

    if (l_low[0] != '\0')
	{
		lFlaglow = strtoll(l_low, NULL, 10) - 1;
		check_strtoll_error(lFlaglow+1);
	}

    if (l_high[0] != '\0')
	{
		lFlaghigh = strtoll(l_high, NULL, 10) - 1;
		check_strtoll_error(lFlaghigh+1);
	}

    if (strstr(arg_string, "-") == NULL) lFlaghigh = lFlaglow;

    free(l_low);
    free(l_high);
}
