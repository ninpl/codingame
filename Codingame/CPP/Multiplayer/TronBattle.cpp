// Rank: 17/1,315 - Bronze League 

#include <iostream>
#include <string>

using namespace std;

// Size of the map
const int WIDTH = 30;
const int HEIGHT = 20;

// Map
int Map[HEIGHT][WIDTH] = {0};

// Current position
int mx, my;

// Last direction
int lastDirection = 0;

// Record the visited nodes in the map
bool writeInMap(int x0, int y0, int x1, int y1);

// Get distance for continuous unvisited nodes
void getDistance(int mx, int my, int * left, int * right, int * up, int * down);

// Get the direction with longest continuous unvisited nodes
int max(int left, int right, int up, int down);

int main()
{
    
    int n, p, x0, y0, x1, y1, no;
    int left, right, up, down;
    
    
    
    while (1) {
        
        // Read information from standard input
        cin >> n;
        cin >> p;
        
        cin >> no >> no >> x0 >> y0 >> no >> no >> x1 >> y1;
        
        if (p == 0) {
            mx = x0;
            my = y0;
        } else {
            mx = x1;
            my = y1;
        }
        
        // Record the visited nodes in the map
        writeInMap(x0, y0, x1, y1);
        
        // Get distance for continuous unvisited nodes
        getDistance(mx, my, &left, &right, &up, &down);
        
        // Get the direction with longest continuous unvisited nodes
        int x = max(left, right, up, down);
        
        // output control varialbe
        if (x == 1) {
            cout << "LEFT" << endl;
            lastDirection = 1;
        }else{
            if (x == 2) {
                cout << "RIGHT" << endl;
                lastDirection = 2;
            } else {
                if (x == 3) {
                    cout << "UP" << endl;
                    lastDirection = 3;
                } else {
                    if (x == 4) {
                        cout << "DOWN" << endl;
                        lastDirection = 4;
                    }else{
                        cout << "LEFT" << endl;
                    }
                }
            }
        }
        
        // for debuging
        cerr << "mx: " << mx << endl;
        cerr << "my: " << my << endl;
        
        cerr << "x0: " << x0 << endl;
        cerr << "y0: " << y0 << endl;
        cerr << "x1: " << x1 << endl;
        cerr << "y1: " << y1 << endl;
        
        cerr << "left:" << left << endl;
        cerr << "right:" << right << endl;
        cerr << "up:" << up << endl;
        cerr << "down:" << down << endl;
        
    }
    
    return 0;
}

// Record the visited nodes in the map
bool writeInMap(int x0, int y0, int x1, int y1)
{
    if (x0 < 30 && x1 < 30 && y0 < 20 && y1 < 20) {
        
        Map[y0][x0] = 1;
        Map[y1][x1] = 1;
        
        return true;
    } else {
        return false;
    }
}

// Get distance for continuous unvisited nodes
void getDistance(int mx, int my, int * left, int * right, int * up, int * down)
{
    *left = *right = *up = *down = 0;
    
    
    //get left distance
    for (int i = mx - 1; i > 0 && Map[my][i] == 0; i--) {
        cerr << "for left i is: " << i << endl;
        cerr << "for left Map[my][i] is: " << Map[my][i] << endl;
        *left = mx - i;
    }

    //get right distance
    for (int i = mx + 1; i > 0 && i < 30 && Map[my][i] == 0; i++) {
        cerr << "for right i is: " << i << endl;
        *right = i - mx;
    }

    //get up distance
    for (int i = my - 1; i > 0 && Map[i][mx] == 0; i--) {
        *up = my - i;
    }

    //get down distance
    for (int i = my + 1; i > 0 && i < 20 && Map[i][mx] == 0; i++) {
        *down = i - my;
    }

}

// Get the direction with longest continuous unvisited nodes
int max(int left, int right, int up, int down)
{
    if (lastDirection == 1 && left > 0) {
        return 1;
    } else {
        if (lastDirection == 2 && right >0) {
            return 2;
        } else {
            if (lastDirection == 3 && up > 0) {
                return 3;
            } else {
                if (lastDirection == 4 && down >0) {
                    return 4;
                }
            }
        }
    }
    
    if (left >= right && left >= up && left >= down ) {
        return 1;
    } else {
        if (right >= left && right >= up && right >= down ){
            return 2;
        }else{
            if (up >= left && up >= right && up >= down ){
                return 3;
            }else{
                if (down >= left && down >= right && down >= up) {
                    return 4;
                }
            }
        }
    }
}