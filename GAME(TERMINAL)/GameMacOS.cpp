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
using namespace std;
char getch();
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
int main()
{
    srand(time(NULL));
    //connecting saves
    fstream ftabs("/Users/danik/Desktop/MyGames/GAME(TERMINAL)/tabs.txt"); 
    fstream fdtabs("/Users/danik/Desktop/MyGames/GAME(TERMINAL)/dtabs.txt"); 
    //connecting saves

    //providing arguments
    char chs;
    int eat = 0;
    int push = 0;
    int str;
    int loc;
    int countturn = 1;
    vector<string> dtab(11);
    for(int a = 0; !fdtabs.eof() and a < 11; a++)
    {
        getline(fdtabs, dtab[a]);
    }
    vector<string> tab(11);
    for(int a = 0; !ftabs.eof() and a < 11; a++)
    {
        getline(ftabs, tab[a]);
    }
    int found = 0;
    int nstr = 0;
    int pos = -2;
    int num = -1;
    int target = found;
    int pos1 = 0;
    int pos2 = 0;
    //providing arguments

    //instruction
    while(chs != 'y')
    {
            cout << "to use this programm, use english keyboard" << endl;
            cout << "let's start! w for up, s for down, a for left, d for right, q for quit, r for restart \n";
            cout << "To win, eat all T letters. You can also eat D letters, but they can eat you too. S are like D but mory slowly. You can't go through B letters." << endl;
            cout << "did you understand? y/n" << endl;
            cin >> chs;
    }
    //instruction
    chs = 0;
    char control;
    //the game itself
    while(control != 'q')
    {
        found = 0;
        nstr = 0;
        eat = 0;
        while(nstr < 11 and pos < 18)
        {
            pos = pos + 2;
            num = tab[nstr].find('T', pos);
            if(num >= 0)
            {
                found++;
                if(num == 18)
                {
                    nstr++;
                    num = -2;
                }
            }
            else
            {
                nstr++;
                num = -2;
            }
            pos = num;
        }
        target = found;
        //showing table
        push = 0;
        system("clear");
        for(int a = 0; a < 11; a++)
        {
            cout << tab[a] << endl;
        }
        //showing table
        //finding P
        for(str = 1; str < 11; str++)
        {
            loc = tab[str].find('P');
            if(loc >= 0)
                break;
            else if((loc >= 0) == false and str == 10)
                push = 1;
        }
        if(push == 1)
            break;
        //finding P
        clock_t start;
        double duration;
        start = clock();
        while(!kbhit())
        {
            duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
            if(duration >= 1)
                break;
        }
        if(duration < 1)
            control = getchar();
        else
            control = 'p';
        int posd = 0;
        int lined = 1;
        //moving and setting
        switch (control)
        {
            case 'd' : 
            {
                if(loc < 18)
                {
                    if(tab[str][loc + 2] == 'B')
                        break;
                    else if(tab[str][loc + 2] == 'T')
                        eat++;
                    tab[str][loc + 2] = 'P';
                    tab[str][loc] = '-';
                }
            }
            break;
            case 'a' :
            {
                if(loc > 0)
                {
                    if(tab[str][loc - 2] == 'B')
                        break;
                    else if(tab[str][loc - 2] == 'T')
                        eat++;
                    tab[str][loc - 2] = 'P';
                    tab[str][loc] = '-';
                }
            }
            break;
            case 'w' : 
            {
                if(str > 1)
                {
                    if(tab[str - 1][loc] == 'B')
                        break;
                    else if(tab[str - 1][loc] == 'T')
                        eat++;
                    tab[str - 1][loc] = 'P';
                    tab[str][loc] = '-';
                }
            }
            break;
            case 's' : 
            {
                if(str < 10)
                {
                    if(tab[str + 1][loc] == 'B')
                        break;
                    else if(tab[str + 1][loc] == 'T')
                        eat++;
                    tab[str + 1][loc] = 'P';
                    tab[str][loc] = '-';
                }
            }
            break;
            case 'r' :
            {
                cout << "do you really want to restart game? r for accept" << endl;
                control = getch();
                if(control == 'r')
                    break;
            }
            break;
        }
        //moving and setting
        if(control == 'r' or control == 'q')
            break;
        while(lined <= 10 and countturn != 1)
        {
            if(push == 1)
                break;
            int posdd = tab[lined].find('D',posd);
            if((posdd >= 0) == false)
            {
                lined++;
                posd = 0;
                continue;
            }
            posd = posdd + 2;
            if(str > lined)
            {
                if((tab[lined + 1][posdd] != '-' and tab[lined + 1][posdd] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 18 and tab[lined][posdd + 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd + 2] = 'D';
                    }
                    else if(rnd == 1 and posdd != 0 and tab[lined][posdd - 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd - 2] = 'D';
                    }
                    else if(rnd == 2 and lined != 1 and tab[lined - 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined - 1][posdd] = 'D';
                    }
                    continue;
                }
                tab[lined][posdd] = '-';
                tab[lined + 1][posdd] = 'D';
            }
            else if(str < lined)
            {
                if((tab[lined - 1][posdd] != '-' and tab[lined - 1][posdd] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 18 and tab[lined][posdd + 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd + 2] = 'D';
                    }
                    else if(rnd == 1 and lined != 10 and tab[lined + 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined + 1][posdd] = 'D';
                    }
                    else if(rnd == 2 and posdd != 0 and tab[lined][posdd - 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd - 2] = 'D';
                    }
                    continue;
                }
                tab[lined][posdd] = '-';
                tab[lined - 1][posdd] = 'D';
            }
            else if(str == lined and loc < posdd)
            {
                if((tab[lined][posdd - 2] != '-' and tab[lined][posdd - 2] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 18 and tab[lined][posdd + 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd + 2] = 'D';
                    }
                    else if(rnd == 1 and lined != 10 and tab[lined + 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined + 1][posdd] = 'D';
                    }
                    else if(rnd == 2 and lined != 1 and tab[lined - 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined - 1][posdd] = 'D';
                    }
                    continue;
                }
                tab[lined][posdd] = '-';
                tab[lined][posdd - 2] = 'D';
            }
            else if(str == lined and posdd < loc)
            {
                if((tab[lined][posdd + 2] != '-' and tab[lined][posdd + 2] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 0 and tab[lined][posdd - 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd - 2] = 'D';
                    }
                    else if(rnd == 1 and lined != 10 and tab[lined + 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined + 1][posdd] = 'D';
                    }
                    else if(rnd == 2 and lined != 1 and tab[lined - 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined - 1][posdd] = 'D';
                    }
                    continue;
                }
                tab[lined][posdd] = '-';
                tab[lined][posdd + 2] = 'D';
            }
            if(posd == 20)
            {
                lined++;
                posd = 0;
                continue;
            }
        }
        if(eat == target)
            break;
        if(push == 1)
            break;
        if(control == 'r')
            break;
        lined = 1;
        posd = 0;
        while(lined <= 10 and countturn % 2 == 0)
        {
            if(push == 1)
                break;
            int posdd = tab[lined].find('S',posd);
            if((posdd >= 0) == false)
            {
                lined++;
                posd = 0;
                continue;
            }
            posd = posdd + 2;
            if(str > lined)
            {
                if((tab[lined + 1][posdd] != '-'  and tab[lined + 1][posdd] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 18 and tab[lined][posdd + 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd + 2] = 'S';
                    }
                    else if(rnd == 1 and posdd != 0 and tab[lined][posdd - 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd - 2] = 'S';
                    }
                    else if(rnd == 2 and lined != 1 and tab[lined - 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined - 1][posdd] = 'S';
                    }
                    continue;
                }
                if(tab[lined + 1][posdd] == 'P')
                    push = 1;
                tab[lined][posdd] = '-';
                tab[lined + 1][posdd] = 'S';
            }
            else if(str < lined)
            {
                if((tab[lined - 1][posdd] != '-' and tab[lined - 1][posdd] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 18 and tab[lined][posdd + 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd + 2] = 'S';
                    }
                    else if(rnd == 1 and lined != 10 and tab[lined + 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined + 1][posdd] = 'S';
                    }
                    else if(rnd == 2 and posdd != 0 and tab[lined][posdd - 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd - 2] = 'S';
                    }
                    continue;
                }
                tab[lined][posdd] = '-';
                tab[lined - 1][posdd] = 'S';
            }
            else if(str == lined and loc < posdd)
            {
                if((tab[lined][posdd - 2] != '-' and tab[lined][posdd - 2] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 18 and tab[lined][posdd + 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd + 2] = 'S';
                    }
                    else if(rnd == 1 and lined != 10 and tab[lined + 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined + 1][posdd] = 'S';
                    }
                    else if(rnd == 2 and lined != 1 and tab[lined - 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined - 1][posdd] = 'S';
                    }
                    continue;
                }
                tab[lined][posdd] = '-';
                tab[lined][posdd - 2] = 'S';
            }
            else if(str == lined and posdd < loc)
            {
                if((tab[lined][posdd + 2] != '-' and tab[lined][posdd + 2] != 'P') or ((lined == 1 or lined == 10) and (posdd == 0 or posdd == 18)))
                {
                    int rnd = rand() % 3;
                    if(rnd == 0 and posdd != 0 and tab[lined][posdd - 2] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined][posdd - 2] = 'S';
                    }
                    else if(rnd == 1 and lined != 10 and tab[lined + 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined + 1][posdd] = 'S';
                    }
                    else if(rnd == 2 and lined != 1 and tab[lined - 1][posdd] == '-')
                    {
                        tab[lined][posdd] = '-';
                        tab[lined - 1][posdd] = 'S';
                    }
                    continue;
                }
                tab[lined][posdd] = '-';
                tab[lined][posdd + 2] = 'S';
            }
            if(posd == 20)
            {
                lined++;
                posd = 0;
                continue;
            }
        }
        //checking
        if(eat == target)
            break;
        if(push == 1)
            break;
        if(control == 'r')
            break;
        //checking
        control = '`';
        countturn++;
    }
    //the game itself

    //final table showing
    for(int a = 0; a < 11; a++)
        {
            cout << tab[a] << endl;
        }
    //final table showing

    //connecting file for saving
    ftabs.close();
    ofstream fotabs("/Users/danik/Desktop/MyGames/GAME(TERMINAL)/tabs.txt");
    //connecting file for saving

    //final message depending on the control set
    if(push == 1 and chs != 'f')
    {
        for(int a = 0; a < 11; a++)
            fotabs << dtab[a] << endl;
        cout << "Game Over!" << endl;
        cout << "to end press f" << endl;
        chs = getch();
    }
    else if(push == 0 and eat != target and control != 'r')
    {
        for(int a = 0; a < 11; a++)
            fotabs << tab[a] << endl;
        cout << "saved the game!" << endl;
        cout << "to end press f" << endl;
        chs = getch();
    }
    else if(eat == target and chs != 'f')
    {
        for(int a = 0; a < 11; a++)
            fotabs << dtab[a] << endl;
        cout << "Nice Work!" << endl;
        cout << "to end press f" << endl;
        chs = getch();
    }
    else if(control == 'r' and chs != 'f')
    {
        for(int a = 0; a < 11; a++)
            fotabs << dtab[a] << endl;
        cout << "the game is restarted" << endl;
        cout << "to play again, close and open the game" << endl;
        cout << "to end press f" << endl;
        chs = getch();
    }
    //final message depending on the control set
    return 0;
}

//getch function for Mac
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
//getch function for Mac