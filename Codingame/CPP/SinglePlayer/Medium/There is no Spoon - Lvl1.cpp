#include <iostream>
#include <string>

using namespace std;
 
int main()
{
    short width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    short height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    string *node = new string[height];
    short x, y;
    for (y = 0; y < height; ++y)
    {
        getline(cin, node[y]);
    }
    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            if (node[y][x] == '0')
            {
                cout << x << ' ' << y << ' ';
                short x2, y2, ansX = -1, ansY = -1;
                for (x2 = x+1; x2 < width; ++x2)
                {
                    if (node[y][x2] == '0')
                    {
                        ansX = x2;
                        ansY = y;
                        break;
                    }
                }
                cout << ansX << ' ' << ansY << ' ';
                ansX = -1; ansY = -1;
                for (y2 = y+1; y2 < height; ++y2)
                {
                    if (node[y2][x] == '0')
                    {
                        ansX = x;
                        ansY = y2;
                        break;
                    }
                }
                cout << ansX << ' ' << ansY << '\n';
                x = x2-1;
            }
        }
    }
}