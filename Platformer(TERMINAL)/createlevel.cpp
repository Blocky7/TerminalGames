#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    int length = 0;
    cout << "What length of level you want?" << endl;
    cin >> length;
    ofstream omg("tab.txt");
    string top(length,'|');
    string other(length,'-');
    omg << top << endl;
    for(int a = 0; a < 10; a++)
        omg << other << endl;
    cout << "DONE" << endl;
}