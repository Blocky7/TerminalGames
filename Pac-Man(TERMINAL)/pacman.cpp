#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <termios.h>
#include <unistd.h>
#include <random>
#include <ctime>
#include <vector>
#include <map>
#include <stdio.h>
#include <fcntl.h>
#include <struct.h>
using namespace std;
char getch()
{
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
struct Ghost {
    string dir;
    int pos;
    int line;
    char prevel;
    char Id;
    int count;
    int maxcount;
};
int main()
{
    srand(time(0));
    string dir = "left";
    string tab[25];
    bool ispu = false;
    int line = 18;
    int pos = 22;
    int score = 0;
    bool end = false;
    string highscore;
    int scg = 0;
    int count = 0;
    Ghost ghst[4] = {
        {"top",20,11,' ','G',0,rand() % 3},
        {"top",18,11,' ','G',0,rand() % 3},
        {"top",24,11,' ','G',0,rand() % 3},
        {"top",26,11,' ','G',0,rand() % 3}
    };
    ifstream stat("/Users/danik/Desktop/MyGames/Pac-Man(TERMINAL)/stat.txt");
    stat >> highscore;
    ifstream omg("/Users/danik/Desktop/MyGames/Pac-Man(TERMINAL)/map.txt");
    for(int a = 0; a < 25 and !omg.eof(); a++)
        getline(omg,tab[a]);
    char yn;
    while(yn != 'q')
    {
        if(ispu)
        {
            count++;
            if(count == 60)
                ispu = false;
        }
        system("clear");
        for(int a = 0; a < 25; a++)
        {
            if(a == 12)
                cout << tab[a] << "     " << "SCORE: " << score << " | HIGHSCORE: " << highscore << endl;
            else
                cout << tab[a] << endl;
        }
        bool stillsc = true;
        for(int a = 0; a < 25; a++)
        {
            int omg = tab[a].find("*");
            int omg2 = tab[a].find("@");
            if(omg >= 0 or omg2 >= 0)
            {
                stillsc = false;
                break;
            }
        }
        if(stillsc)
        {
            Ghost g1 = {"top",20,11,' ','G',0,rand() % 3};
            Ghost g2 = {"top",18,11,' ','G',0,rand() % 3};
            Ghost g3 = {"top",24,11,' ','G',0,rand() % 3};
            Ghost g4 = {"top",26,11,' ','G',0,rand() % 3};
            ghst[0] = g1;
            ghst[1] = g2;
            ghst[2] = g3;
            ghst[3] = g4;
            ispu = false;
            count = 0;
            scg = 0;
            end = false;
            line = 18;
            pos = 22;
            dir = "left";
            omg.close();
            omg.open("/Users/danik/Desktop/MyGames/Pac-Man(TERMINAL)/map.txt");
            for(int a = 0; a < 25 and !omg.eof(); a++)
                getline(omg,tab[a]);
            continue;
        }
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
            control = getchar();
        if(control == 'q')
            break;
        if(control == 'w' and tab[line - 1][pos] != '#')
            dir = "top";
        else if(control == 'a' and tab[line][pos - 2] != '#')
            dir = "left";
        else if(control == 'd' and tab[line][pos + 2] != '#')
            dir = "right";
        else if(control == 's' and tab[line + 1][pos] != '#')
            dir = "bottom";
        int npos = pos;
        int nline = line;
        switch(dir[0])
        {
            case 'b':
            {
                if(tab[nline + 1][pos] == ' ')
                    nline++;
                else if(tab[nline + 1][pos] == '*')
                {
                    nline++;
                    score += 10;
                }
                else if(tab[nline + 1][pos] == '@')
                {
                    nline++;
                    ispu = true;
                    score += 50;
                    count = 0;
                }
                else if(tab[nline + 1][pos] == 'G')
                {
                    end = true;
                    tab[nline][pos] = ' ';
                    nline++;
                }
                else if(tab[nline + 1][pos] == 'F')
                {
                    if(scg == 0)
                    {
                        score += 200;
                        scg++;
                    }
                    else if(scg == 1)
                    {
                        score += 400;
                        scg++;
                    }
                    else if(scg == 2)
                    {
                        score += 800;
                        scg++;
                    }
                    else if(scg == 3)
                    {
                        score += 1600;
                        scg = 0;
                    }
                    for(int a = 0; a < 4; a++)
                    {
                        if(ghst[a].line == nline + 1 and ghst[a].pos == pos)
                        {
                            Ghost g = {"top",20,11,' ','G',0,rand() % 3};
                            tab[ghst[a].line][ghst[a].pos] = ghst[a].prevel;
                            ghst[a] = g;
                            tab[11][20] = 'G';
                            break;
                        }
                    }
                    nline++;
                }
            }
            break;
            case 't':
            {
                if(tab[nline - 1][pos] == ' ')
                    nline--;
                else if(tab[nline - 1][pos] == '*')
                {
                    nline--;
                    score += 10;
                }
                else if(tab[nline - 1][pos] == '@')
                {
                    nline--;
                    ispu = true;
                    score += 50;
                    count = 0;
                }
                else if(tab[nline - 1][pos] == 'G')
                {
                    end = true;
                    tab[nline][pos] = ' ';
                    nline--;
                }
                else if(tab[nline - 1][pos] == 'F')
                {
                    if(scg == 0)
                    {
                        score += 200;
                        scg++;
                    }
                    else if(scg == 1)
                    {
                        score += 400;
                        scg++;
                    }
                    else if(scg == 2)
                    {
                        score += 800;
                        scg++;
                    }
                    else if(scg == 3)
                    {
                        score += 1600;
                        scg = 0;
                    }
                    for(int a = 0; a < 4; a++)
                    {
                        if(ghst[a].line == nline - 1 and ghst[a].pos == pos)
                        {
                            Ghost g = {"top",20,11,' ','G',0,rand() % 3};
                            tab[ghst[a].line][ghst[a].pos] = ghst[a].prevel;
                            ghst[a] = g;
                            tab[11][20] = 'G';
                            break;
                        }
                    }
                    nline--;
                }
            }
            break;
            case 'r':
            {
                if(tab[nline][pos + 2] == ' ')
                    npos += 2;
                else if(tab[nline][pos + 2] == '*')
                {
                    npos += 2;
                    score += 10;
                }
                else if(tab[nline][pos + 2] == '@')
                {
                    npos += 2;
                    ispu = true;
                    score += 50;
                    count = 0;
                }
                else if(pos == 44)
                    npos = 0;
                else if(tab[nline][pos + 2] == 'G')
                {
                    end = true;
                    tab[nline][pos] = ' ';
                    pos += 2;
                }
                else if(tab[nline][pos + 2] == 'F')
                {
                    if(scg == 0)
                    {
                        score += 200;
                        scg++;
                    }
                    else if(scg == 1)
                    {
                        score += 400;
                        scg++;
                    }
                    else if(scg == 2)
                    {
                        score += 800;
                        scg++;
                    }
                    else if(scg == 3)
                    {
                        score += 1600;
                        scg = 0;
                    }
                    for(int a = 0; a < 4; a++)
                    {
                        if(ghst[a].line == nline and ghst[a].pos == pos + 2)
                        {
                            Ghost g = {"top",20,11,' ','G',0,rand() % 3};
                            tab[ghst[a].line][ghst[a].pos] = ghst[a].prevel;
                            ghst[a] = g;
                            tab[11][20] = 'G';
                            break;
                        }
                    }
                    npos += 2;
                }
            }
            break;
            case 'l':
            {
                if(tab[nline][pos - 2] == ' ')
                    npos -= 2;
                else if(tab[nline][pos - 2] == '*')
                {
                    npos -= 2;
                    score += 10;
                }
                else if(tab[nline][pos - 2] == '@')
                {
                    npos -= 2;
                    ispu = true;
                    score += 50;
                    count = 0;
                }
                else if(pos == 0)
                    npos = 44;
                else if(tab[nline][pos - 2] == 'G')
                {
                    end = true;
                    tab[nline][pos] = ' ';
                    pos -= 2;
                }
                else if(tab[nline][pos - 2] == 'F')
                {
                    if(scg == 0)
                    {
                        score += 200;
                        scg++;
                    }
                    else if(scg == 1)
                    {
                        score += 400;
                        scg++;
                    }
                    else if(scg == 2)
                    {
                        score += 800;
                        scg++;
                    }
                    else if(scg == 3)
                    {
                        score += 1600;
                        scg = 0;
                    }
                    for(int a = 0; a < 4; a++)
                    {
                        if(ghst[a].line == nline and ghst[a].pos == pos - 2)
                        {
                            Ghost g = {"top",20,11,' ','G',0,rand() % 3};
                            tab[ghst[a].line][ghst[a].pos] = ghst[a].prevel;
                            ghst[a] = g;
                            tab[11][20] = 'G';
                            break;
                        }
                    }
                    npos -= 2;
                }
            }
            break;
        }
        if(end)
        {
            cout << "F to pay respects" << endl;
            control = getch();
            break;
        }
        tab[line][pos] = ' ';
        tab[nline][npos] = 'P';
        line = nline;
        pos = npos;
        for(int a = 0; a < 4; a++)
        {
            if(ispu)
                ghst[a].Id = 'F';
            else 
                ghst[a].Id = 'G';
            string mode;
            int lineg = ghst[a].line;
            int posg = ghst[a].pos;
            string dirg = ghst[a].dir;
            bool stillg = true;
            char prevel = ghst[a].prevel;
            int countg = ghst[a].count;
            if(ispu)
                mode = "scatter";
            else if( (line > lineg and line - lineg <= 5) and (pos > posg and pos - posg <= 5))
                mode = "chase";
            else if( (line > lineg and line - lineg <= 5) and (pos < posg and posg - pos <= 5))
                mode = "chase";
            else if( (line < lineg and lineg - line <= 5) and (pos < posg and posg - pos <= 5))
                mode = "chase";
            else if( (line < lineg and lineg - line <= 5) and (pos > posg and pos - posg <= 5))
                mode = "chase";
            else 
                mode = "scatter";
            if(mode == "scatter")
            {
                switch(dirg[0])
                {
                    case 't':
                    {
                        if(tab[lineg - 1][posg] == '#' or tab[lineg - 1][posg] == 'G' or tab[lineg - 1][posg] == 'F')
                        {
                            if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                                dirg = "right";
                            else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                                dirg = "left";
                            else if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                                dirg = "bottom";
                            else 
                                stillg = false;
                        }
                    }
                    break;
                    case 'r':
                    {
                        if(tab[lineg][posg + 2] == '#' or tab[lineg][posg + 2] == 'G' or tab[lineg][posg + 2] == 'F')
                        {
                            if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                                dirg = "bottom";
                            else if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                                dirg = "top";
                            else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                                dirg = "left";
                            else 
                                stillg = false;
                        }
                    }
                    break;
                    case 'l':
                    {
                        if(tab[lineg][posg - 2] == '#' or tab[lineg][posg - 2] == 'G' or tab[lineg][posg - 2] == 'F')
                        {
                            if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                                dirg = "bottom";
                            else if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                                dirg = "top";
                            else if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                                dirg = "right";
                            else 
                                stillg = false;
                        }
                    }
                    break;
                    case 'b':
                    {
                        if(tab[lineg + 1][posg] == '#' or tab[lineg + 1][posg] == 'G' or tab[lineg + 1][posg] == 'F')
                        {
                            if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                                dirg = "right";
                            else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                                dirg = "left";
                            else if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                                dirg = "top";
                            else 
                                stillg = false;
                        }
                    }
                    break;
                }
                if(ghst[a].count < ghst[a].maxcount and (tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F') and dirg != "bottom" and dirg != "top")
                    countg++;
                else if(ghst[a].count < ghst[a].maxcount and (tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F') and dirg != "top" and dirg != "bottom")
                    countg++;
                else if(ghst[a].count < ghst[a].maxcount and (tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F') and dirg != "right" and dirg != "left")
                    countg++;
                else if(ghst[a].count < ghst[a].maxcount and (tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F') and dirg != "left" and dirg != "right")
                    countg++;
                else if(ghst[a].count == ghst[a].maxcount and (tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F') and dirg != "bottom" and dirg != "top")
                {
                    dirg = "bottom";
                    countg = 0;
                }
                else if(ghst[a].count == ghst[a].maxcount and (tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F') and dirg != "top" and dirg != "bottom")
                {
                    dirg = "top";
                    countg = 0;
                }
                else if(ghst[a].count == ghst[a].maxcount and (tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F') and dirg != "right" and dirg != "left")
                {
                    dirg = "right";
                    countg = 0;
                }
                else if(ghst[a].count == ghst[a].maxcount and (tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F') and dirg != "left" and dirg != "right")
                {
                    dirg = "left";
                    countg = 0;
                }
            }
            else if(mode == "chase")
            {
                if(line > lineg and pos < posg)
                {
                    if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                        dirg = "bottom";
                    else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                        dirg = "left";
                    else if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                        dirg = "right";
                    else if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                        dirg = "top";
                }
                else if(line > lineg and pos > posg)
                {
                    if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                        dirg = "bottom";
                    else if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                        dirg = "right";
                    else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                        dirg = "left";
                    else if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                        dirg = "top";
                }
                else if(line < lineg and pos < posg)
                {
                    if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                        dirg = "top";
                    else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                        dirg = "left";
                    else if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                        dirg = "right";
                    else if(tab[lineg + 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                        dirg = "bottom";
                }
                else if(line < lineg and pos > posg)
                {
                    if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                        dirg = "top";
                    else if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                        dirg = "right";
                    else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                        dirg = "left";
                    else if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                        dirg = "bottom";
                }
                else if(line == lineg and pos > posg)
                {
                    if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                        dirg = "right";
                    else if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                        dirg = "top";
                    else if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                        dirg = "bottom";
                    else if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                        dirg = "left";
                }
                else if(line == lineg and pos < posg)
                {
                    if(tab[lineg][posg - 2] != '#' and tab[lineg][posg - 2] != 'G' and tab[lineg][posg - 2] != 'F')
                        dirg = "left";
                    else if(tab[lineg - 1][posg] != '#' and tab[lineg - 1][posg] != 'G' and tab[lineg - 1][posg] != 'F')
                        dirg = "top";
                    else if(tab[lineg + 1][posg] != '#' and tab[lineg + 1][posg] != 'G' and tab[lineg + 1][posg] != 'F')
                        dirg = "bottom";
                    else if(tab[lineg][posg + 2] != '#' and tab[lineg][posg + 2] != 'G' and tab[lineg][posg + 2] != 'F')
                        dirg = "right";
                }
            }
            switch(dirg[0])
            {
                case 't':
                {
                    lineg--;
                }
                break;
                case 'r':
                {
                    if(posg < 44)
                        posg += 2;
                    else 
                        posg = 0;
                }
                break;
                case 'l':
                {
                    if(posg > 0)
                        posg -= 2;
                    else 
                        posg = 44;
                }
                break;
                case 'b':
                {
                    lineg++;
                }
                break;
            }
            if(stillg and tab[lineg][posg] != 'P')
            {
                tab[ghst[a].line][ghst[a].pos] = prevel;
                ghst[a].prevel = tab[lineg][posg];
                tab[lineg][posg] = ghst[a].Id;
                ghst[a].pos = posg;
                ghst[a].line = lineg;
            }
            else if(stillg and tab[lineg][posg] == 'P' and ispu == false)
            {
                end = true;
                break;
            }
            ghst[a].dir = dirg;
            ghst[a].count = countg;
        }
        if(end)
        {
            cout << "F to pay respects" << endl;
            control = getch();
            break;
        }
    }
    if(stoi(highscore) < score)
    {
        stat.close();
        ofstream nstat("/Users/danik/Desktop/MyGames/Pac-Man(TERMINAL)/stat.txt");
        nstat << score;
    }
}