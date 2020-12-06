#include <iostream>
#include <ctime>
#include <fstream>
#include <random>
#include <string>
using namespace std;
int main()
{
    srand(time(NULL));
    ofstream ftabs("tabs.txt"); 
    ofstream fdtabs("dtabs.txt"); 
    string tab[11] = {
        "___________________",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -",
        "- - - - - - - - - -"
    };
    int chance = 0;
    cout << "what chance of creation you want? (HIGHER CHANCE MEANS LOW QUANTITY OF CREATIONS)" << endl;
    cin >> chance;
    chance += 4;
    int pos = 0;
    int line = 1;
    while(line < 11)
    {
        while(pos <= 18)
        {
            int rnd = rand() % 2;
            if(rnd % 2 == true)
            {
                int rnd2 = rand() % chance;
                if(rnd2 == 0)
                    tab[line][pos] = 'D';
                else if(rnd2 == 1)
                    tab[line][pos] = 'B';
                else if(rnd2 == 2)
                    tab[line][pos] = 'T';
                else if(rnd2 == 3)
                    tab[line][pos] = 'S';
            }
            pos += 2;
        }
        pos = 0;
        while(line == 10)
        {
            int rnd = rand() % 180;
            int posp = rnd % 10;
            int linep = rnd % posp;
            linep += 1;
            if(posp % 2 == 1)
                continue;
            if((tab[linep - 1][posp] != 'D' and tab[linep + 1][posp] != 'D' and tab[linep][posp - 2] != 'D' and tab[linep][posp + 2] != 'D') == false)
                continue;
            if(tab[linep - 1][posp + 2] != 'D' and tab[linep - 1][posp - 2] != 'D' and tab[linep + 1][posp + 2] != 'D' and tab[linep + 1][posp - 2] != 'D')
            {
                tab[linep][posp] = 'P';
                break;
            }
        }
        line++;
    }
    for(int a = 0; a < 11; a++)
    {
        fdtabs << tab[a] << endl;
        ftabs << tab[a] << endl;
    }
    fdtabs.close();
    ftabs.close();
    cout << "DONE" << endl;
    return 0;
}