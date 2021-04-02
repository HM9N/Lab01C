#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************************************* 
  **********************************************************************************************
Código realizado por Jhon Vásquez para el curso de Sistemas Operativos de la Universidad de Antioquia 
  **********************************************************************************************
**************************************************************************************************/

/* Método para llenar la matriz con los ingredientes de cada plato */
void fillMatrix(int **matriz, int rows, char *token, int index, char *ingredients)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (strcmp((ingredients + (j * 21)), (token + (i * 21))) == 0)
            {
                matriz[index][j] = 1;
            }
        }
    }
}

/* Método para imprimir la matriz */
void printMatrix(int **matriz, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matriz[j][i]);
        }
        printf("\n");
    }
}

// Método para intercambiar de posición dos números
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Método parar maximizar la función
void maxFunction(int *quantities, int **matriz, int numIngredients)
{
    /* quantities[0] == PP
        quantities[1] == P2
        quantities[2] == P3
        quantities[3] == P4 */
    for (int i = 0; i < quantities[1]; i++)
    {
        for (int i = 0; i < numIngredients; i++)
        {
        }
    }
}

// devuelve una permutación del array
void getPermutation(int *solutionArray, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", solutionArray[i]);
    }

    printf("\n");
}

// Algoritmo para realizar las permutaciones del array
void arrayPermutation(int *solutionArray, int size, int n, int quantites, int **matriz, int numIngredients)
{
    if (size == 1)
    {
        getPermutation(solutionArray, n);
        return;
    }

    for (int i = 0; i < size; i++)
    {
        arrayPermutation(solutionArray, size - 1, n);

        if (size % 2 == 1)
        {
            swap(&solutionArray[0], &solutionArray[size - 1]);
        }
        else
        {
            swap(&solutionArray[i], &solutionArray[size - 1]);
        }
    }
}

/* Inicia el método main */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must specify a filepath\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[1], "r");

    if (!fp)
    {
        printf("Error opening the file %s\n", argv[1]);
    }

    char *palabra = malloc(2100 * sizeof(char));
    char *ingredientsByPlate;
    int **P;
    int *ApToPermutation;
    int *AP;
    int Op3 = 0;
    int Op4 = 0;
    char line[1024];
    char lineIngredients[1024];
    int NTPP = 0;
    int linecount = 0;
    int rowsCount = 0;
    int termscount = 0;
    int quantities[4];
    int numingredients = 0;
    int numOfDifferentIngredients = 0;
    char *nullchar = '\0';
    while (fgets(line, 1024, fp))
    {
        char *token;
        char *rest = line;

        if (linecount == 0)
        {
            /* Donde quantities es un arreglo con los números de la primera linea:
               quantities[0] == PP
               quantities[1] == P2
               quantities[2] == P3
               quantities[3] == P4
            */

            while (token = strtok_r(rest, " ", &rest))
            {
                quantities[termscount] = atoi(token);
                termscount++;
                if (termscount > 1)
                {
                    NTPP = NTPP + termscount * atoi(token);
                }
            }

            // Se le asigna espacio en la memoria dinámica a el vector AP y al vector auxiliar para la permutación
            ApToPermutation = malloc(NTPP * sizeof(int));
            AP = malloc(NTPP * sizeof(int));

            // Se inicializa el vector auxiliar
            for (int i = 0; i < NTPP; i++)
            {
                ApToPermutation[i] = i;
            }

            if (termscount != 4)
            {
                printf("El archivo tiene mal la estructura, la primera linea debe tener cuatro números en el siguiente orden:\n -Cantidad de platos\n "
                       "-Número de pedidos de dos platos\n -Número de pedidos de tres platos\n - Número de pedidos de cuatro platos\n");
                return EXIT_FAILURE;
            }

            if (NTPP != quantities[0])
            {
                printf("Los cálculos no coinciden, revisa la primera línea del archivo de texto\n");
                return EXIT_FAILURE;
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
                    char *s = token;
                    while (*s != '\n')
                    {
                        //printf("%s", s);
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
    /* fin while */

    /* Se crea la matriz de platos */
    P = malloc(quantities[0] * sizeof(int *));
    for (int i = 0; i < quantities[0]; i++)
    {
        P[i] = malloc(numOfDifferentIngredients * sizeof(int));
    }

    linecount = 0;

    fclose(fp);

    /*  While para agregar los ingredientes de cada plato */
    while (fgets(lineIngredients, 1024, fp2))
    {
        char *token2;
        char *rest2 = lineIngredients;

        if (linecount == 0)
        {
            token2 = strtok_r(rest2, " ", &rest2);
            linecount++;
        }
        else
        {
            token2 = strtok_r(rest2, " ", &rest2);
            numingredients = atoi(token2);
            ingredientsByPlate = malloc((numingredients * 100) * sizeof(char));
            for (int i = 0; i < numingredients; i++)
            {
                token2 = strtok_r(rest2, " ", &rest2);
                if (i == numingredients - 1)
                {
                    char *s = token2;
                    while (*s != '\n')
                    {
                        ++s;
                    }
                    *s = '\0';
                }
                strcpy((ingredientsByPlate + (i * 21)), token2);
            }

            /* Se le pasan los argumentos a la matriz */
            fillMatrix(P, numOfDifferentIngredients, ingredientsByPlate, rowsCount, palabra);
            free(ingredientsByPlate);
            rowsCount++;
        }
    }
    /* Fin while */

    fclose(fp2);

    // Ejecutar el algoritmo de permutación

    printf("Las filas de la matriz corresponden a los siguientes ingredientes (en ese orden):\n");

    for (int i = 0; i < numOfDifferentIngredients; i++)
    {
        printf("Fila %d: %s\n", i + 1, (palabra + (i * 21)) + 0);
    }

    printMatrix(P, numOfDifferentIngredients, quantities[0]);

    arrayPermutation(ApToPermutation, NTPP, NTPP);

    free(palabra);
    free(ApToPermutation);
}