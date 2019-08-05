
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"levenshtein.h"

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(int argc, char* argv[])
{
    puts("-----------------------------");
    puts("| codedrome.com             |");
    puts("| Levenshtein Word Distance |");
    puts("-----------------------------\n");

    levenshtein* lp = NULL;

    lp = lev_init("banama", "banana");
    lp = lev_init("banama", "elephant");
    // lp = lev_init("levinstein", "levenshtein");

    if(lp != NULL)
    {
        lev_calc(lp);

        lev_print_grid(lp);

        lev_print_cost(lp);

        lev_free(lp);

        return EXIT_SUCCESS;
    }
    else
    {
        puts("Cannot create Levenshtein :(");

        return EXIT_FAILURE;
    }
}
