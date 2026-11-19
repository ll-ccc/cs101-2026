#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int n;
    int group;
    int lotto[7];
    int i, j;
    int duplicate;
    int temp;

    FILE *fp;
    time_t now;
    struct tm *date;
    char dateText[40];

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩");

    if (scanf("%d", &n) != 1 || n < 1 || n > 5)
    {
        printf("Please enter 1 to 5.\n");
        return 1;
    }

    
    now = time(NULL);
    date = localtime(&now);

    if (date == NULL)
    {
        printf("Failed to get the current date.\n");
        return 1;
    }

    strftime(dateText, sizeof(dateText),
             "%Y/%m/%d %H:%M:%S", date);

   
    srand((unsigned int)now);

    
    fp = fopen("lotto.txt", "w");

    if (fp == NULL)
    {
        printf("Cannot open lotto.txt.\n");
        return 1;
    }

    
    printf("\n===== lotto 649 =====\n");
    printf("Date: %s\n", dateText);
    printf("Groups: %d\n\n", n);

    fprintf(fp, "===== lotto 649 =====");
    fprintf(fp, "Date: %s\n", dateText);
    fprintf(fp, "Groups: %d\n\n", n);

   
    for (group = 1; group <= n; group++)
    {
        
        for (i = 0; i < 7; i++)
        {
            do
            {
                lotto[i] = rand() % 69 + 1;
                duplicate = 0;

                
                for (j = 0; j < i; j++)
                {
                    if (lotto[i] == lotto[j])
                    {
                        duplicate = 1;
                        break;
                    }
                }
            } while (duplicate == 1);
        }

        
        for (i = 0; i < 6; i++)
        {
            for (j = 0; j < 6 - i; j++)
            {
                if (lotto[j] > lotto[j + 1])
                {
                    temp = lotto[j];
                    lotto[j] = lotto[j + 1];
                    lotto[j + 1] = temp;
                }
            }
        }

        
        printf("Group %d: ", group);
        fprintf(fp, "Group %d: ", group);

        for (i = 0; i < 7; i++)
        {
            printf("%02d ", lotto[i]);
            fprintf(fp, "%02d ", lotto[i]);
        }

        printf("\n");
        fprintf(fp, "\n");
    }

    if (ferror(fp))
    {
        printf("Failed to write lotto.txt.\n");
        fclose(fp);
        return 1;
    }

    if (fclose(fp) != 0)
    {
        printf("Failed to close lotto.txt.\n");
        return 1;
    }

    printf("\n===== csie@CGU =====\n");

    return 0;
}
