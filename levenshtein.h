
#include<stdlib.h>
#include<stdio.h>

#define INSERT_COST 1
#define DELETE_COST 1
#define SUBSTITUTE_COST 1

// --------------------------------------------------------
// STRUCT levenshtein
// --------------------------------------------------------
typedef struct levenshtein
{
    int** grid;
    char source_word[64];
    char target_word[64];
    int source_length;
    int target_length;
    int minimum_cost;
} levenshtein;

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
levenshtein* lev_init(char source_word[64], char target_word[64]);
int lev_calc(levenshtein* lp);
void lev_free(levenshtein* lp);
void lev_print_grid(levenshtein* lp);
void lev_print_cost(levenshtein* lp);
