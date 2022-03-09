#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <unistd.h>
#include <random>
#include <ctime>
#include <vector>
#include <map>
#include <stdio.h>
#include <fcntl.h>
#include <conio.h>
using namespace std;
struct PartS {
    int line;
    int pos;
    string dir;
    string pdir;
};
int main()
{
    string rec;
    int size = 3;
    ifstream stat("stat.txt");
    stat >> rec;
    srand( time(0) );
    string tab[11] = {
        "||||||||||",
        "----------",
        "----------",
        "----------",
        "----------",
        "----------",
        "----------",
        "-----S----",
        "-----S----",
        "-----S----",
        "-----S----"
    };
    vector<PartS> snake;
    for(int a = 7; a < 11; a++)
    {
        struct PartS omg = {a,5,"top","top"};
        snake.push_back(omg);
        cout << snake[a - 7].line << " " << snake[a - 7].pos << endl;
    }
    char yn;
    while(yn != 'q')
    {
        bool ishere = false;
        for(int a = 1; a < 11; a++)
        {
            int F = tab[a].find('F');
            if(F >= 0)
            {
                ishere = true;
                break;
            }
        }
        if(!ishere)
        {
            size++;
            int fpos = 0;
            int fline = 0;
            while(tab[fline][fpos] == 'P' or tab[fline][fpos] == '|')
            {
                int where = rand() % 100;
                fline = int(where / 10) + 1;
                fpos = where % 10;
            }
            tab[fline][fpos] = 'F';
        }
        bool yes = false;
        system("cls");
        for(int a = 0; a < 11; a++)
            cout << tab[a] << endl;
        cout << "Current size: " << size << " | " << "Record: " << rec << endl;
        clock_t start;
        bool still = true;
        start = clock();
        char control = 'p';
        while(!kbhit())
        {
            if(( clock() - start ) / (double) CLOCKS_PER_SEC >= 0.25)
            {
                still = false;
                break;
            }
        }
        if(still)
            control = getch();
        if(control == 'q')
            break;
        for(int a = 0; a < snake.size(); a++)
        {
            snake[a].pdir = snake[a].dir;
            if(a == 0)
            {
                if(control == 'w' and snake[a].dir != "bottom")
                    snake[a].dir = "top";
                else if(control == 'a' and snake[a].dir != "right")
                    snake[a].dir = "left";
                else if(control == 'd' and snake[a].dir != "left")
                    snake[a].dir = "right";
                else if(control == 's' and snake[a].dir != "top")
                    snake[a].dir = "bottom";
            }
            else
                snake[a].dir = snake[a - 1].pdir;
        }
        int csize = snake.size();
        bool isit = false;
        for(int a = 0; a < csize; a++)
        {
            int pos = snake[a].pos;
            char dir = snake[a].dir[0];
            int line = snake[a].line;
            int npos = pos;
            int nline = line;
            switch(dir)
            {
                case 'b':
                {
                    if(line < 10)
                        nline++;
                    else
                        nline = 1;
                }
                break;
                case 't':
                {
                    if(line > 1)
                        nline--;
                    else 
                        nline = 10;
                }
                break;
                case 'r':
                {
                    if(pos < 9)
                        npos++;
                    else 
                        npos = 0;
                }
                break;
                case 'l':
                {
                    if(pos > 0)
                        npos--;
                    else 
                        npos = 9;
                }
                break;
            }
            if(tab[nline][npos] == 'F' and a == 0)
            {
                PartS omg = {0,0," "," "};
                snake.push_back(omg);
                yes = true;
            }
            if(tab[nline][npos] == 'S' and a == 0)
            {
                tab[line][pos] = 'D';
                for(int b = 0; b < 11; b++)
                    cout << tab[b] << endl;
                cout << "Current size: " << size << " | " << "Record: " << rec << endl;
                cout << "Game Over" << endl;
                isit = true;
                break;
            }
            tab[nline][npos] = 'S';
            tab[line][pos] = '-';
            snake[a].line = nline;
            snake[a].pos = npos;
            if(yes and a == csize - 1)
            {
                if(dir == 'l')
                {
                    if(npos < 9)
                    {
                        tab[nline][npos + 1] = 'S';
                        snake[a + 1].line = nline;
                        snake[a + 1].dir = "left";
                        snake[a + 1].pdir = "left";
                        snake[a + 1].pos = npos + 1;
                    }
                    else
                    {
                        tab[nline][0] = 'S';
                        snake[a + 1].line = nline;
                        snake[a + 1].dir = "left";
                        snake[a + 1].pdir = "left";
                        snake[a + 1].pos = 0;
                    }
                }
                else if(dir == 'r')
                {
                    if(npos > 0)
                    {
                        tab[nline][npos - 1] = 'S';
                        snake[a + 1].line = nline;
                        snake[a + 1].dir = "right";
                        snake[a + 1].pdir = "right";
                        snake[a + 1].pos = npos - 1;
                    }
                    else
                    {
                        tab[nline][9] = 'S';
                        snake[a + 1].line = nline;
                        snake[a + 1].dir = "right";
                        snake[a + 1].pdir = "right";
                        snake[a + 1].pos = 9;
                    }
                }
                else if(dir == 'b')
                {
                    if(nline > 1)
                    {
                        tab[nline][npos] = 'S';
                        snake[a + 1].line = nline - 1;
                        snake[a + 1].dir = "bottom";
                        snake[a + 1].pdir = "bottom";
                        snake[a + 1].pos = npos;
                    }
                    else
                    {
                        tab[nline][npos] = 'S';
                        snake[a + 1].line = 10;
                        snake[a + 1].dir = "bottom";
                        snake[a + 1].pdir = "bottom";
                        snake[a + 1].pos = npos;
                    }
                }
                else if(dir == 't')
                {
                    if(nline < 10)
                    {
                        tab[nline][npos] = 'S';
                        snake[a + 1].line = nline + 1;
                        snake[a + 1].dir = "top";
                        snake[a + 1].pdir = "top";
                        snake[a + 1].pos = npos;
                    }
                    else
                    {
                        tab[nline][npos] = 'S';
                        snake[a + 1].line = 1;
                        snake[a + 1].dir = "top";
                        snake[a + 1].pdir = "top";
                        snake[a + 1].pos = npos;
                    }
                }
            }
        }
        if(isit)
            break;
    }
    if(size > stoi(rec))
    {
        stat.close();
        ofstream nstat("stat.txt");
        nstat << size;
        nstat.close();
    }
}