#include <stdio.h>

void converter(int dec)
{
    if (dec != 0)
    {
        converter(dec - 1);
        printf("1");
    }
}

int main() 
{
    int dec;

    printf("Ird be a valtani kivant decimalis szamot: \n");
    scanf("%d", &dec);

    converter(dec);

    return 0;
}
