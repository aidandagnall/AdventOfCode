#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int intcode(int, int);
void decodeInstruction(int, int [5]);

int main(int argc, char **argv)
{
    int max = 0, output;

    for (int a = 0; a < 5; a++)
    {
        for (int b = 0; b < 5; b++)
        {
            if (a == b)
                continue;
            
            for (int c = 0; c < 5; c++)
            {
                if (a == c || b == c)
                    continue;
                
                for (int d = 0; d < 5; d++)
                {
                    if (a == d || b == d || c == d)
                        continue;

                    for (int e = 0; e < 5; e++)
                    {
                        if (a == e || b == e || c == e || d == e)
                            continue;
                        
                        output = intcode(a, 0);
                        output = intcode(b, output);
                        output = intcode(c, output);
                        output = intcode(d, output);
                        output = intcode(e, output);

                        if (output > max)
                            max = output;
                    }
                } 
            }
        }    
    }
    
    printf("%d\n", max);
    return 0;
}

int intcode(int phase, int signal)
{
    FILE *fp = fopen("input.txt", "r");
    char fullInput[3000], *token;
    int intcode[250], ins[5] = {0,0,0,0,0};
    int par1, par2, par3, opcode, position = 0, input = phase;

    fgets(fullInput, sizeof(fullInput), fp);
    token = strtok(fullInput, ",");
    while(token != NULL)
    {
        intcode[position] = atoi(token);
        position++;
        token = strtok(NULL, ",");
    }

    position = 0;

    while (intcode[position] != 99)
    {
        decodeInstruction(intcode[position], ins);
        opcode = ins[3] * 10 + ins[4];

        par1 = ins[2] ?  intcode[position + 1] : intcode[intcode[position + 1]];
        par2 = ins[1] ? intcode[position + 2] : intcode[intcode[position + 2]];
        par3 = ins[0] ? position + 3 : intcode[position + 3];

        switch (opcode)
        {
        case 1:
            intcode[par3] = par1 + par2;
            position += 4;
            break;
        case 2:
            intcode[par3] = par1 * par2;
            position += 4;
            break;
        case 3:
            par1 = intcode[position + 1];
            intcode[par1] = input;
            input = signal;
            position += 2;
            break;
        case 4:
            return par1;
            position += 2;
            break;
        
        case 5:
            if (par1 != 0)
            {
                position = par2;
                break;
            }
            position += 3;
            break;
        case 6:
            if (par1 == 0)
            {
                position = par2;
                break;
            }
            position += 3;
            break;
        case 7:
            if (par1 < par2)
                intcode[par3] = 1;
            else
                intcode[par3] = 0;
            position += 4;
            break;
        
        case 8:
            if (par1 == par2)
                intcode[par3] = 1;
            else
                intcode[par3] = 0;
            position += 4;
            break;

        default:
            printf("Something went wrong... \n");
            return 1;
            break;
        }
    }

    return 0;
}

void decodeInstruction(int a, int ins[5])
{
    char str[5];
    int j = 4;
    sprintf(str, "%d", a);

    for(int i = 0; i < 5; i++)
        ins[i] = 0;

    for(int i = strlen(str) - 1; i >= 0; i--)
        ins[j--] = str[i] - '0';
}