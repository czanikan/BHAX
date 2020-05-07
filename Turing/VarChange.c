#include <stdio.h>
#include <stdlib.h>
int main()
{
    int a = 0;
    int b = 0;
    int tmp = 0;
    int choice;
    while(1)
    {
        printf("a = ");
        scanf("%d",&a);
        printf("\nb = ");
        scanf("%d",&b);
        printf("\n---x{[MENU]}x---\n");
        printf("1 - Seged valtozoval\n");
        printf("2 - Kivonassal\n");
        printf("3 - Osszeadassal\n");
        printf("9 - Exit\n");
        fflush(stdin);
        scanf("%d",&choice);
                
        switch(choice)
        {
            case 1:
                tmp = a;
                a = b;
                b = tmp;
                printf("a = %d, b = %d\n", a, b);
                break;
                
            case 2:
                a = a - b;
                b = a + b;
                a = b - a;
                printf("a = %d, b = %d\n", a, b);
                break;
                
            case 3:
                a = a + b;
                b = a - b;
                a = a - b;
                printf("a = %d, b = %d\n", a, b);
                break;
                
            case 9:
                break;

            default:
                printf("Invalid input!\n");
        }
        break;
    }
    return 0;
}
