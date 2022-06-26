#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* cipher(char* string, char* key)
{
    int shift = 0;

    for(int i = 0; i < strlen(string); i++)
    {   
        if(string[i] == 32)
        {
            string[i] = 32;
        }else
        {
            shift = string[i] - '!';

            string[i] = key[i % strlen(key)];

            for(int j = 0; j < shift; j++)
            {
                string[i]++;
                if(string[i] == 127)
                    string[i] = 33;
            } 
        }
    }

    return string;
}

char* decipher(char* string, char* key)
{

    int shift = 0;
    int safer = 0;

    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == 32)
        {
            string[i] = 32;
        }else
        {
            safer = key[i % strlen(key)];

            while(safer != string[i])
            {
                shift++;
                safer++;
                if(safer == 127)
                    safer = 33;
            }
            string[i] = '!' + shift;
            shift = 0;
        }
    }
    return string;
}

void ftoa(float ftocon, char* string, int size_after_p)
{
    int before_point = (int)ftocon;
    float after_point = ftocon - (float)before_point;
    for(int i = 0; i < size_after_p; i++)
    {
        after_point = after_point * 10.0;
    }

    int safer = before_point;
    int space = 0;

    while (safer)
    {
        space++;
        safer = safer/10;
    }

    itoa(before_point, string, 10);
    strcat(string, ".");
    if(space == 0)
        space = 1;
    space++;
    itoa(after_point, &string[space], 10);
}

void write(float matrix[5][5], char* string, char* key, int biggest_size_after_p, FILE* fp)
{
    fp = fopen("matrica.txt", "w");

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            ftoa(matrix[i][j], string, biggest_size_after_p);
            cipher(string, key);
            fprintf(fp, "%s ", string);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void read(char* string, char* key, FILE* fp, float matrix[5][5])
{
    fp = fopen("matrica.txt", "r");

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            fscanf(fp, "%s", string);
            decipher(string, key);
            matrix[i][j] = atof(string);
        }
    }

    fclose(fp);
}

int main()
{
    FILE* fp;

    float matrix[5][5] = {
        {0,0,0,0,0},
        {0,0,0,0,1},
        {0,1,0,0.453777,0},
        {0,0,1,0,0.23232},
        {0,0,0,1,0}};

    float matrix1[5][5];

    char* string = (char*)malloc(sizeof(char)*30);
    char* key = strdup("key");

    int biggest_size_after_p = 6;

    write(matrix, string, key, biggest_size_after_p, fp);
    
    read(string, key, fp, matrix1);

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            printf("%f ", matrix1[i][j]);
        }
        printf("\n");
    }

    free(string);
    free(key);
    return 0;
}
