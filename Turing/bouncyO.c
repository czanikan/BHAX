#include <stdio.h>
#include <curses.h>
#include <unistd.h>

//gcc bouncyO.c -o bouncyO -lncurses

int main()
{
    WINDOW *ablak;
    ablak = initscr();

    int x = 0;
    int y = 0;

    int delX = 1;
    int delY = 1;

    int mx;
    int my;
    
    while(true)
    {
        printf("\033[0;32m");

        getmaxyx(ablak, my, mx);
        mvprintw(y, x, "(DVD)");

        refresh();
        usleep(100000);
        

        clear();

        x = x + delX;
        y = y + delY;
        /*
        if(x <= 0)
        {
            delX = delX * -1;
            //printf("\033[0;31m");
        }
        if(x >= mx-1)
        {
            delX = delX * -1;
            //printf("\033[0;32m");
        }
        if(y <= 0)
        {
            delY = delY * -1;
            //printf("\033[0;33m");
        }
        if(y >= my-1)
        {
            delY = delY * -1;
            //printf("\033[0;34m");
        }
        */
       for(;x <= 0;)
       {
           delX = delX * -1;
           break;
       }
       for(;x >= mx-1;)
       {
           delX = delX * -1;
           break;
       }
       for(;y <= 0;)
       {
           delY = delY * -1;
           break;
       }
       for(;y >= my-1;)
       {
           delY = delY * -1;
           break;
       }
    }

    return 0;
}