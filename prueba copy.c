#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *palabra = (char *)malloc(2100 * sizeof(char));
    if (argc < 2)
    {
        printf("You must specify a filepath\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");

    if (!fp)
    {
        printf("Error opening the file %s\n", argv[1]);
    }

    char line[1024];
    int linecount = 0;
    int termscount = 0;
    int quantities[4];
    int numingredients = 0;
    int numOfDifferentIngredients = 0;
    char *nullchar = '\0';
    char *s;
    while (fgets(line, 1024, fp))
    {
        char *token;
        char *rest = line;
        if (linecount == 0)
        {
            while (token = strtok_r(rest, " ", &rest))
            {
                quantities[termscount] = atoi(token);
                termscount++;
            }
            linecount++;
        }
        else
        {
            token = strtok_r(rest, " ", &rest);
            numingredients = atoi(token);
            for (int i = 0; i < numingredients; i++)
            {
                token = strtok_r(rest, " ", &rest);
                if (i == numingredients - 1)
                {
                    s = token;
                    
                    while (*s != '\n')
                    {
                        ++s;
                    }
                    *s = '\0';
                }

                int comparisonSomeIsEqual = -1;
                for (int j = 0; j < numOfDifferentIngredients; j++)
                {
                    if (strcmp((palabra + (j * 21)), token) == 0)
                    {
                        comparisonSomeIsEqual = 0;
                        break;
                    }
                }

                if (comparisonSomeIsEqual == -1)
                {
                    strcpy((palabra + (numOfDifferentIngredients * 21)), token);
                    numOfDifferentIngredients++;
                }
            }
        }
    }

    fclose(fp);

    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", quantities[i]);
    }

    for (int i = 0; i < numOfDifferentIngredients; i++)
    {
        printf("ingredient: %s\n", (palabra + (i * 21)) + 0);
    }

}