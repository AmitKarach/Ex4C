
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum
{
    MAXC = 800,
    MAXW = 4000
};

struct freqcount
{
    int count;
    char *word;
};
int comparator(const void *pa, const void *pb)
{
    const struct freqcount *const *a = pa;
    const struct freqcount *const *b = pb;

    // or on same line:
    // const struct freqcount * const *a = pa, * const *b = pb;

    return strcmp((*a)->word, (*b)->word);
    // or return strcmp(a[0]->word, b[0]->word);
}

int main(int argc, const char *argv[])
{

    struct freqcount *words[MAXW] = {0}; // Struct INIT
    char wordstr[MAXC] = " ";
    int n = 0;

    // While < MAXW unique words, read each word in file
    // Delimiter(Format Specifier) included in this line, only english letters
    // Must be 1 less than 800 in order to avoid memory problems
    while (n < MAXW && fscanf(stdin, "%799[a-zA-Z]%*[^a-zA-Z]", wordstr) == 1)
    {

        int i;
        //LowerCase Code for everyword
        //Regardless of input because upercase is not accepted
        for (int i = 0; wordstr[i]; i++)
        {
            wordstr[i] = tolower(wordstr[i]);
        }

        for (i = 0; i < n; i++) //A check vs what already exists
            if (strcmp(words[i]->word, wordstr) == 0)
                break;

        if (i < n)
        {                      /* if exists */
            words[i]->count++; /* update frequency */
            continue;          /* get next word */
        }

        // A new word found, allocate struct and
        // allocate storage for word (+ space for nul-byte)

        words[n] = malloc(sizeof *words[n]);
        words[n]->word = malloc(strlen(wordstr) + 1);
        if (!words[n] || !words[n]->word)
        { // Validate ALL allocations for Mem
            fprintf(stderr, "error: memory exhausted, words[%d].\n", n);
            break;
        }
        words[n]->count = 0; // Count Init...
        // Copy Word and update relevant parameters
        strcpy(words[n]->word, wordstr);
        words[n]->count++;
        n++;
    }
    qsort(words, n, sizeof words[0], comparator); // Sort (in C used qsort with compare func)
    // If 'r' is passed via arg then print backwords sorted
    if (argc == 2 && (*argv[1] == 'r'))
    {
        //Finally print out the words and their occurneces
        for (int i = n - 1; i >= 0; i--)
        {
            printf("%s\t%d\n", words[i]->word, words[i]->count);
            free(words[i]->word); /* free memory when no longer needed */
            free(words[i]);
        }
    }
    else
    {
        //Finally print out the words(Regularly Sorted) and their occurneces
        for (int i = 0; i < n; i++)
        {
            printf("%s\t%d\n", words[i]->word, words[i]->count);
            free(words[i]->word); /* free memory when no longer needed */
            free(words[i]);
        }
    }

    return 0;
}
