#include <stdio.h>
#include <string.h>

struct calendar
{
    char dayName[100];
    char task[3][100];
    int filled;
};


int main() {

    int ch;
    int dayNo;
    char dayName[100];
    char task[100];
    struct calendar c[7];
    for (int i = 0; i < 7; i++) {
        c[i].filled = 0;
    }

    printf("1. Input Data for a Day in a Week\n");
    printf("2. Show Data for all Days in a Week\n");
    printf("3. Exit\n");
    printf("Enter Choice : \n");
    scanf("%d",&ch);

    while(1) {
        if (ch == 1) {
            printf("Enter Day Number (1 to 7) :\n");
            scanf("%d",&dayNo);

            if(dayNo >= 1 && dayNo <= 7) {
                c[dayNo-1].filled = 1;
                printf("Enter Day Name: \n");
                scanf("%s", dayName);
                strcpy(c[dayNo-1].dayName, dayName);
                for(int i = 0; i < 3; i++)
                {
                    printf("Enter task %d\n",i+1);
                    scanf("%s", task);
                    strcpy(c[dayNo-1].task[i], task);
                }
            }
        } else if (ch == 2) {
            for(int i = 0; i < 7; i++) {
                if (c[i].filled) {
                    printf("%s\n", c[i].dayName);
                    for(int j = 0; j < 3; j++) {
                        printf("  %s\n", c[i].task[j]);
                    }
                }
            }
        } else if (ch == 3) break;
        else printf("Invalid Choice\n");

        printf("Enter Choice: \n");
        scanf("%d", &ch);
    }


    return 0;
}