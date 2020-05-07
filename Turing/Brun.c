#include<stdio.h>

int prim(int n, int *pList)
{
    int len = 1, brk = 0;
    
    for(int i = 2; i <= n; i++)
    {
        for(int j = 0; j < len; j++)
        {
            if(i % pList[j] == 0){
                brk = 1;
                break;
            }
            else
            {
                brk = 0;
            }
        }
        if(brk == 0)
        {
            pList[len]=i;
            len++;
        }
    }
    for(int i = 0; i < len; i++)
        printf("%d ",pList[i]);
}

double reciprokGen(int n, int *pList)
{
    double rList[200]= {};
    int len = 1;
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            rList[i] = 1.0f / pList[j];
        }
    }
    for(int i = 0; i <= n; i++)
        printf("%.2lf ",rList[i]);
}

int main()
{
    int pList[200] = {2};
    int n;
    scanf("%d",&n);
    prim(n, pList);
    reciprokGen(n, pList);

    return 0;
}