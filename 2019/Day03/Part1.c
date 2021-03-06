#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
    FILE *fp = fopen("input.txt", "r");
    int wireA[154000][2], wireB[154000][2], i = 1;
    int collisions[1000][2];
    wireA[0][0] = wireB[0][0] = 0;
    wireA[0][1] = wireB[0][1] = 0;
    char str[2900], *token;

    fgets(str, 1800, fp);
    token = strtok(str, ",");
    while(token != NULL)
    {
        switch (token[0])
        {
        case 'U':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireA[i][0] = wireA[i - 1][0];
                wireA[i][1] = wireA[i - 1][1] + 1;
                i++;
            }
            
            break;
        case 'D':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireA[i][0] = wireA[i - 1][0];
                wireA[i][1] = wireA[i - 1][1] - 1;
                i++;
            }
            
            break;
        case 'L':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireA[i][1] = wireA[i - 1][1];
                wireA[i][0] = wireA[i - 1][0] - 1;
                i++;
            }
            break;
        case 'R':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireA[i][1] = wireA[i - 1][1];
                wireA[i][0] = wireA[i - 1][0] + 1;
                i++;
            }
            break;
            
        default:
            break;
        }

        token = strtok(NULL, ",");
    }
    i = 1;
    fgets(str, 1600, fp);
    token = strtok(str, ",");
    
    while(token != NULL)
    {
        switch (token[0])
        {
        case 'U':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireB[i][0] = wireB[i - 1][0];
                wireB[i][1] = wireB[i - 1][1] + 1;
                i++;
            }
            
            break;
        case 'D':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireB[i][0] = wireB[i - 1][0];
                wireB[i][1] = wireB[i - 1][1] - 1;
                i++;
            }
            
            break;
        case 'L':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireB[i][1] = wireB[i - 1][1];
                wireB[i][0] = wireB[i - 1][0] - 1;
                i++;
            }
            break;
        case 'R':
            for(int j = 0; j < atoi(token + 1); j++)
            {
                wireB[i][1] = wireB[i - 1][1];
                wireB[i][0] = wireB[i - 1][0] + 1;
                i++;
            }
            break;
            
        default:
            break;
        }

        token = strtok(NULL, ",");
    }

    int collCount = 0;
    for (int j = 1; j < 154000; j++)
    {
        for (int k = 1; k < 154000; k++)
        {
            if (wireA[j][0] == 0 && wireA[j][1] == 0)
            {
                continue;
            }
            if (wireA[j][1] == 0)
            {
                continue;
            }
            if (wireA[j][0] == wireB[k][0] && wireA[j][1] == wireB[k][1])
            {
                collisions[collCount][0] = wireA[j][0];
                collisions[collCount][1] = wireA[j][1];
                collCount++;
            }
        }
    }

    int min = 9999999;
    for (int j = 0; j < collCount; j++)
    {
        if ((abs(collisions[j][0]) + abs(collisions[j][1])) < min)
        {
            min = abs(collisions[j][0]) + abs(collisions[j][1]);
        }
    }

    printf("%d\n", min);
    return 0;
}