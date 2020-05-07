    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    
    double distance (double PR[], double PRv[], int db)
    {
        double dist = 0.0;
        for(int i = 0; i < db; i++)
        {
            dist += pow((PRv[i] - PR[i]), 2);
        }
        return sqrt(dist);
    }
    
    void kiir (double list[], int db)
    {
        for(int i = 0; i < db; i++)
        {
            printf("PageRank [%d]: %lf\n", i, list[i]);
        }
    }
    
    int main(void)
    {
        double L[4][4] = 
        {
        {0.0, 0.0, 1.0/3.0, 0.0},
        {1.0, 1.0/2.0, 1.0/3.0, 1.0},
        {0.0, 1.0/2.0, 0.0, 0.0},
        {0.0, 0.0, 1.0/3.0, 0.0}
        };
    
        double PR[4] = {0.0, 0.0, 0.0, 0.0};
        double PRv[4] = {1.0/4.0, 1.0/4.0, 1.0/4.0, 1.0/4.0};
    
        for(;;)
        {
            for(int i = 0; i < 4; i++)
            {
                PR[i] = PRv[i];
            }
            for(int i = 0; i < 4; i++)
            {
                PRv[i] = 0;
                for(int j = 0; j < 4; j++)
                {
                    PRv[i] += L[i][j] * PR[j];                
                }
            }
            if(distance(PR, PRv, 4) < 0.00001)
            {
                break;
            }
        }
        kiir (PR, 4);
        return 0;
    }