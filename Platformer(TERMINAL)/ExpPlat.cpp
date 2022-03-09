#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <conio.h>
#include <random>
#include <ctime>
#include <vector>
#include <map>
#include <stdio.h>
#include <fcntl.h>
using namespace std;
int main()
{
    vector<string> tab(11);
    fstream ftab("tab.txt");
    for(int a = 0; !ftab.eof() and a < 11; a++)
    {
        getline(ftab,tab[a]);
    }
    int pos = -1;
    int line = 0;
    char yn;
    char prevel = '-';
    bool end = false;
    bool is_space = false;
    int length = tab[0].size();
    map<pair<int,int>,string> Ms;
    for(int lm = 0, rm = 0; lm < 11;)
    {
        int pm = tab[lm].find("M",rm);
        if(pm >= 0)
        {
            pair<int,int> omg;
            omg.first = lm;
            omg.second = pm;
            Ms[omg] = "left";
            rm = pm + 1;
        }
        else 
        {
            rm = 0;
            lm++;
            continue;
        }
    }
    while(yn != 'y')
    {
        cout << "P is you, L are ladders, M are enemies, space is for jump, a is left, d is right, w and s are up and down(if you are on ladder), C are coins - your target" << endl;
        cout << "did you understand? y/n" << endl;
        cin >> yn;
    }
    while(yn != 'q')
    {
        system("cls");
        for(int a = 0; a < 11; a++)
            cout << tab[a] << endl;
        int cpos = -1;
        for(line = 1; line < 11; line++)
        {
            pos = tab[line].find("P");
            if(pos >= 0)
                break;
        }
        for(int a = 0; a < 11; a++)
        {
            cpos = tab[a].find("C");
            if(cpos >= 0)
            {
                break;
            }
        }
        if((pos >= 0) == false)
        {
            cout << "F to pay respects" << endl;
            yn = getch();
            break;
        }
        if((cpos >= 0) == false)
        {
            cout << "You Won!" << endl;
            yn = getch();
            break;
        }
        clock_t start;
        bool still = true;
        start = clock();
        char control = 'p';
        while(!kbhit())
        {
            if(( clock() - start ) / (double) CLOCKS_PER_SEC >= 0.5)
            {
                still = false;
                break;
            }
        }
        if(still)
            control = getch();
        if(control == 'q')
            break;
        switch(control){
            case 'a':
            {
                if(tab[line][pos - 1] != 'B' and !is_space and pos - 1 >= 0 and tab[line][pos - 1] != 'M' and tab[line][pos - 1] != 'C')
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line][pos - 1];
                    tab[line][pos - 1] = 'P';
                    pos--;
                }
                else if(tab[line][pos - 1] == 'M' and !is_space and pos - 1 >= 0)
                    tab[line][pos] = prevel;
                else if(tab[line][pos - 1] == 'C' and !is_space)
                {
                    tab[line][pos] = prevel;
                    prevel = '-';
                    tab[line][pos - 1] = 'P';
                    pos--;
                }
                else if(tab[line][pos - 2] == 'C' and is_space)
                {
                    tab[line][pos] = prevel;
                    prevel = '-';
                    tab[line][pos - 2] = 'P';
                    pos--;
                    is_space = false;
                }
                else if(tab[line][pos - 2] != 'B' and is_space and tab[line][pos - 1] == '-' and pos - 2 >= 0)
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line][pos - 2];
                    tab[line][pos - 2] = 'P';
                    pos -= 2;
                    is_space = false;
                }
                else if(tab[line][pos - 1] != 'B' and is_space and pos - 1 >= 0)
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line][pos - 1];
                    tab[line][pos - 1] = 'P';
                    pos--;
                    is_space = false;
                }
            }
            break;
            case 'd':
            {
                if(tab[line][pos + 1] != 'B' and !is_space and pos + 1 <= length - 1 and tab[line][pos + 1] != 'M'  and tab[line][pos + 1] != 'C')
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line][pos + 1];
                    tab[line][pos + 1] = 'P';
                    pos++;
                }
                else if(tab[line][pos + 1] == 'M' and !is_space)
                    tab[line][pos] = prevel;
                else if(tab[line][pos + 1] == 'C' and !is_space)
                {
                    tab[line][pos] = prevel;
                    prevel = '-';
                    tab[line][pos + 1] = 'P';
                    pos++;
                }
                else if(tab[line][pos + 2] == 'C' and is_space)
                {
                    tab[line][pos] = prevel;
                    prevel = '-';
                    tab[line][pos + 2] = 'P';
                    pos += 2;
                    is_space = false;
                }
                else if(tab[line][pos + 2] != 'B' and is_space and tab[line][pos + 1] == '-'  and pos + 2 <= length - 1)
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line][pos + 2];
                    tab[line][pos + 2] = 'P';
                    pos += 2;
                    is_space = false;
                }
                else if(tab[line][pos + 1] != 'B' and is_space and pos + 1 <= length - 1)
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line][pos + 1];
                    tab[line][pos + 1] = 'P';
                    pos++;
                    is_space = false;
                }
            }
            break;
            case ' ':
            {
                if(tab[line - 1][pos] == '-' and !is_space and prevel != 'L')
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line - 1][pos];
                    tab[line - 1][pos] = 'P';
                    is_space = true;
                }
                else if(is_space)
                {
                    tab[line][pos] = prevel;
                    prevel = '-';
                    tab[line + 1][pos] = 'P';
                    is_space = false;
                }
            }
            break;
            case 's':
            {
                if(tab[line + 1][pos] == 'L' or (prevel == 'L' and tab[line + 1][pos] == '-'))
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line + 1][pos];
                    tab[line + 1][pos] = 'P';
                }
            }
            break;
            case 'w':
            {
                if(tab[line - 1][pos] == 'L' or (prevel == 'L' and tab[line - 1][pos] == '-'))
                {
                    tab[line][pos] = prevel;
                    prevel = tab[line - 1][pos];
                    tab[line - 1][pos] = 'P';
                }
            }
            break;
            case 'q': end = true; cout << "you quit" << endl;
            break;
            default: is_space = false;
            break;
        }
        if(end)
            break;
        for(int linem = 1, posrm = 0; linem < 11;)
        {
            int posm = tab[linem].find("M", posrm);
            if(posm >= 0)
            {
                pair<int,int> omg;
                omg.first = linem;
                omg.second = posm;
                if(Ms[omg] == "left")
                {
                    if((tab[linem][posm - 1] == '-' or tab[linem][posm - 1] == 'P') and tab[linem + 1][posm - 1] != '-')
                    {
                        tab[linem][posm] = '-';
                        tab[linem][posm - 1] = 'M';
                        Ms.erase(omg);
                        omg.second = posm - 1;
                        posm--;
                        Ms[omg] = "left";
                    }
                    else if(tab[linem + 1][posm - 1] == '-' and tab[linem][posm - 1] == '-')
                    {
                        bool mstill = true;
                        for(int a = linem + 1; a < 11; a++)
                        {
                            if(tab[a][posm - 1] != '-')
                            {
                                mstill = false;
                                tab[a - 1][posm - 1] = 'M';
                                tab[linem][posm] = '-';
                                Ms.erase(omg);
                                omg.second = posm - 1;
                                omg.first = a - 1;
                                posm--;
                                Ms[omg] = "left";
                                break;
                            }
                        }
                        if(mstill)
                            Ms[omg] = "right";
                    }
                    else if(tab[linem + 1][posm] == '-')
                    {
                        bool mstill = true;
                        for(int a = linem + 1; a < 11; a++)
                        {
                            if(tab[a][posm] != '-')
                            {
                                mstill = false;
                                tab[a - 1][posm] = 'M';
                                tab[linem][posm] = '-';
                                Ms.erase(omg);
                                omg.first = a - 1;
                                Ms[omg] = "left";
                                break;
                            }
                        }
                        if(mstill)
                            tab[linem][posm] = '-';
                    }
                    else
                        Ms[omg] = "right";
                }
                if(Ms[omg] == "right")
                {
                    if((tab[linem][posm + 1] == '-' or tab[linem][posm + 1] == 'P') and tab[linem + 1][posm + 1] != '-')
                    {
                        tab[linem][posm] = '-';
                        tab[linem][posm + 1] = 'M';
                        Ms.erase(omg);
                        omg.second = posm + 1;
                        posm++;
                        Ms[omg] = "right";
                    }
                    else if(tab[linem + 1][posm + 1] == '-' and tab[linem][posm + 1] == '-')
                    {
                        bool mstill = true;
                        for(int a = linem + 1; a < 11; a++)
                        {
                            if(tab[a][posm + 1] != '-')
                            {
                                mstill = false;
                                tab[a - 1][posm + 1] = 'M';
                                tab[linem][posm] = '-';
                                Ms.erase(omg);
                                omg.second = posm + 1;
                                omg.first = a - 1;
                                posm++;
                                Ms[omg] = "right";
                                break;
                            }
                        }
                        if(mstill)
                            Ms[omg] = "left";
                    }
                    else
                    {
                        Ms[omg] = "left";
                    }
                }
                posrm = posm + 1;
            }
            else
            {
                linem++;
                posrm = 0;
                continue;
            }
        }
        if((tab[line + 1][pos] == '-' and prevel == '-') or tab[line + 1][pos] == 'M' or tab[line + 1][pos] == 'C' or line == 10)
        {
            bool still = false;
            for(int lineb = line + 1; lineb < 11; lineb++)
            {
                if(tab[lineb][pos] == 'C')
                    tab[lineb][pos] = '-';
                if(tab[lineb][pos] == 'B' or tab[lineb][pos] == 'L')
                {
                    still = true;
                    tab[lineb - 1][pos] = 'P';
                    tab[line][pos] = '-';
                    is_space = false;
                    break;
                }
            }
            if(!still)
            {
                tab[line][pos] = '-';
                tab[10][pos] = 'P';
                for(int a = 0; a < 11; a++)
                    cout << tab[a] << endl;
                cout << "You fell into void" << endl;
                control = getch();
                break;
            }
        }
    }
}