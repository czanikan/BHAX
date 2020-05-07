#include <omp.h>

int main()
{
    /*	
    while(1)
	{
    	sleep(1);
	}*/

    #pragma omp parallel
    {
        for(;;);
    }
    return 0;
}