#include "globals.h"
#include "help.h"
#include <stdio.h>

#define VERSION "v0.1.0\n"

void
usage()
{
    printf("usage: %s -[hvdlwx] <file>\n", args[0]);
}


void
help()
{
    printf("\nVDF - View Delimited File\n");
    usage();
    printf("\nvdf is a tool for viewing delimitted files in a terminal\n\n");
    printf("\t-h\tPrint this help message and exit\n");
    printf("\t-d\tDelimitting character used by the file, comma is default\n");
    printf("\t-l\tLine range to print e.g. 3-5, -3, 3-, 3\n");
    printf("\t-x\tExclude headers from the output\n");
    printf("\t-w\tWrap fields at given width - not yet supported\n");
    printf("\t-v\tDisplay version information\n");
}


void
version()
{
    printf(VERSION);
}
