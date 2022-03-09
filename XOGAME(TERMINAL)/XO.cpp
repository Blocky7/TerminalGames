#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <unistd.h>
#include <conio.h>
using namespace std;
int main()
{
    cout << "q to quit and numbers to control" << endl;
    string table[4];
    ifstream omg("table.txt");
    char cube = ' ';
    for(int a = 0; !omg.eof() and a < 5; a++)
    {
        if(a != 4)
            getline(omg,table[a]);
        else
            omg >> cube;
    }
    char control;
    bool draw = false;
    int sc = 0;
    while(cube == ' ')
    {
        char first = ' ';
        cout << "who goes first? X or O?" << endl;
        first = getch();
        if(first == 'x' or first == 'X')
        {
            cube = 'X';
            break;
        }
        else if(first == 'o' or first == 'O')
        {
            cube = 'O';
            break;
        }
        else
            cout << "THIS IS NOT X OR O!!! TRY AGAIN PLEASE" << endl;
    }
    while(control != 'q')
    {
        system("cls");
        for(int a = 0; a < 4; a++)
            cout << table[a] << endl;
        cout << cube << " IS GOING RIGHT NOW" << endl;
        cout << "Where the symbol is going to be?" << endl;
        control = getch();
        if(isdigit(control))
        {
            switch(control)
            {
                case '1':
                {
                    if(isalpha(table[1][0]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[1][0] = cube;
                        sc++;
                    }
                }
                break;
                case '2':
                {
                    if(isalpha(table[1][3]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[1][3] = cube;
                        sc++;
                    }
                }
                break;
                case '3':
                {
                    if(isalpha(table[1][6]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[1][6] = cube;
                        sc++;
                    }
                }
                break;
                case '4':
                {
                    if(isalpha(table[2][0]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[2][0] = cube;
                        sc++;
                    }
                }
                break;
                case '5':
                {
                    if(isalpha(table[2][3]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[2][3] = cube;
                        sc++;
                    }
                }
                break;
                case '6':
                {
                    if(isalpha(table[2][6]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[2][6] = cube;
                        sc++;
                    }
                }
                break;
                case '7':
                {
                    if(isalpha(table[3][0]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[3][0] = cube;
                        sc++;
                    }
                }
                break;
                case '8':
                {
                    if(isalpha(table[3][3]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[3][3] = cube;
                        sc++;
                    }
                }
                break;
                case '9':
                {
                    if(isalpha(table[3][6]))
                        cout << "THERE IS ALREADY A SYMBOL" << endl;
                    else
                    {
                        table[3][6] = cube;
                        sc++;
                    }
                }
                break;
            }
        }
        else if(control != 'q')
        {
            cout << "THIS IS NOT A NUMBER!!!! TRY AGAIN!!!" << endl;
            continue;
        }
        else
            break;
        if(table[1][0] == table[1][3] and table[1][3] == table[1][6])
            break;
        if(table[2][0] == table[2][3] and table[2][3] == table[2][6])
            break;
        if(table[3][0] == table[3][3] and table[3][3] == table[3][6])
            break;
        
        if(table[1][0] == table[2][0] and table[2][0] == table[3][0])
            break;
        if(table[1][3] == table[2][3] and table[2][3] == table[3][3])
            break;
        if(table[1][6] == table[2][6] and table[2][6] == table[3][6])
            break;
        
        if(table[1][0] == table[2][3] and table[2][3] == table[3][6])
            break;
        if(table[1][6] == table[2][3] and table[2][3] == table[3][0])
            break;
        if(sc == 9)
        {
            draw = true;
            break;
        }
        cube = cube == 'X'? 'O' : 'X';
        system("clear");
    }
    omg.close();
    ofstream omg2("/Users/danik/Desktop/XOGAME/table.txt");
    for(int a = 0; a < 4; a++)
        cout << table[a] << endl;
    if(draw)
    {
        cout << "DRAW" << endl;
        omg2 << "_______" << endl;
        omg2 << "1  2  3" << endl;
        omg2 << "4  5  6" << endl;
        omg2 << "7  8  9" << endl;
        omg2 << " " << endl;
    }
    else if(control != 'q')
    {
        cout << cube << " HAS WON!!!!!" << endl;
        omg2 << "_______" << endl;
        omg2 << "1  2  3" << endl;
        omg2 << "4  5  6" << endl;
        omg2 << "7  8  9" << endl;
        omg2 << " " << endl;
    }
    else
    {
        cout << "quit from game" << endl;
        omg2 << table[0] << endl;
        omg2 << table[1] << endl;
        omg2 << table[2] << endl;
        omg2 << table[3] << endl;
        omg2 << cube << endl;
    }
    cout << "to end press something on keyboard" << endl;
    control = getch();
    return 0;
}   