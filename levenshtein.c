
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#include"levenshtein.h"

#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
static int min(int a, int b, int c);

// --------------------------------------------------------
// FUNCTION lev_init
// --------------------------------------------------------
levenshtein* lev_init(char* source_word, char* target_word)
{
    levenshtein* lp = malloc(sizeof(levenshtein));

    if(lp != NULL)
    {
        *lp = (levenshtein){.grid = NULL,
                            .source_length = strlen(source_word),
                            .target_length = strlen(target_word),
                            .minimum_cost = 0};

        strcpy(lp->source_word, source_word);
        strcpy(lp->target_word, target_word);

        lp->grid = malloc((lp->source_length + 1) * sizeof(int*));

        if(lp->grid != NULL)
        {
            for(int r = 0; r <= lp->source_length; r++)
            {
                lp->grid[r] = malloc((lp->target_length + 1) * sizeof(int));

                if(lp->grid[r] != NULL)
                {
                    for(int c = 0; c <= lp->target_length; c++)
                    {
                        if(r == 0)
                        {
                            lp->grid[r][c] = c;
                        }
                        else if(c == 0)
                        {
                            lp->grid[r][c] = r;
                        }
                        else
                        {
                            lp->grid[r][c] = 0;
                        }
                    }
                }
                else
                {
                    lev_free(lp);

                    return NULL;
                }
            }

            return lp;
        }
        else
        {
            lev_free(lp);

            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

// --------------------------------------------------------
// FUNCTION lev_calc
// --------------------------------------------------------
int lev_calc(levenshtein* lp)
{
    int total_substitution_cost;
    int total_deletion_cost;
    int total_insertion_cost;

    for(int sourceletter = 0; sourceletter < lp->source_length; sourceletter++)
    {
        for(int targetletter = 0; targetletter < lp->target_length; targetletter++)
        {
            if(lp->target_word[targetletter] != lp->source_word[sourceletter])
            {
                total_substitution_cost = lp->grid[sourceletter][targetletter] + SUBSTITUTE_COST;
            }
            else
            {
                total_substitution_cost = lp->grid[sourceletter][targetletter];
            }

            total_deletion_cost = lp->grid[sourceletter][targetletter+1] + DELETE_COST;
            total_insertion_cost = lp->grid[sourceletter+1][targetletter] + INSERT_COST;

            lp->grid[sourceletter+1][targetletter+1] = min(total_substitution_cost, total_deletion_cost, total_insertion_cost);
        }
    }
}

// --------------------------------------------------------
// FUNCTION lev_print_grid
// --------------------------------------------------------
void lev_print_grid(levenshtein* lp)
{
    if(lp != NULL)
    {
        for(int c = 0; c <= lp->target_length; c++)
        {
            if(c > 0)
            {
                printf(GREEN "  %2c " RESET, lp->target_word[c-1]);
            }
            else
            {
                printf("          ");
            }
        }

        printf("\n\n");

        for(int r = 0; r <= lp->source_length; r++)
        {
            if(r > 0)
            {
                printf(GREEN " %2c " RESET, lp->source_word[r-1]);
            }
            else
            {
                printf("    ");
            }

            for(int c = 0; c <= lp->target_length; c++)
            {
                printf("   %2d", lp->grid[r][c]);
            }

            puts("  \n");
        }
    }
}

// --------------------------------------------------------
// FUNCTION lev_print_cost
// --------------------------------------------------------
void lev_print_cost(levenshtein* lp)
{
    if(lp != NULL)
    {
        printf("Minimum cost of transforming \"%s\" to \"%s\" = %d\n", lp->source_word, lp->target_word, lp->grid[lp->source_length][lp->target_length]);
    }
}

// --------------------------------------------------------
// FUNCTION lev_free
// --------------------------------------------------------
void lev_free(levenshtein* lp)
{
    if(lp != NULL)
    {
        if(lp->grid != NULL)
        {
            for(int r = 0; r <= lp->source_length; r++)
            {
                if(lp->grid[r] == NULL)
                {
                    printf("%d NULL\n", r);
                }

                free(lp->grid[r]);
            }

            free(lp->grid);
        }

        free(lp);
    }
}

//--------------------------------------------------------
// FUNCTION min
//--------------------------------------------------------
static int min(int a, int b, int c)
{
    int m;

    (a <= b && a <= c) ? (m = a) : (b <= a && b <= c) ? (m = b) : (m = c);

    return m;
}
