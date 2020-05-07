#include <stdio.h>

int main()
{
    int wordLength = 0, word = 1;
    
    do
    {
        
        wordLength++;
        
    } while(word <<= 1);
    
    printf("A szó ezen a gépen %d bites\n", wordLength);
    
    return 0;
}

