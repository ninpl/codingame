#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    int dist1 = 0, dist2 = 0, difdist = 0;
    bool isChecked1 = false; //checking direction in case You're not on the exiting floor
    bool dirLeft = false; //direction-left = false
    bool isDirWrong = false;// direction is wrong? - false
    bool isChecked = false; //checking direction in case You ARE on the exiting floor
    bool isFloorChecked = false; //cHECKING IF THERE WAS A CHECKING for clone being on the exit floor
    int currentElPos = 0; //current position of the Elevator
    bool sameFloorToEx = false; //checking if the leading clone is on the exit FLoor   
    
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    
    int elFloors[nbElevators], elPosns[nbElevators];
    
    for (int i = 0; i < nbElevators; i++) {
        
        cin >> elFloors[i] >> elPosns[i]; cin.ignore();
    }
    
    int times = 0;

    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        
        if (isFloorChecked == false)
        {   
            if (exitFloor == cloneFloor)
            {
                sameFloorToEx = true;
            }
            
            else 
            {
                for (int i = 0; i < nbElevators; i++)
                {
                    if (cloneFloor == elFloors[i])
                    {
                        currentElPos = elPosns[i];
                    }      
                }    
            }
            
            isFloorChecked = true;
        }
        
        
        
        if (sameFloorToEx == true) 
        {
            if (isChecked == false) 
            {
                dist1 = abs(exitPos - clonePos);
                if (times < 1)
                cout << "WAIT" << endl;
                if (dirLeft == false) {
                    clonePos++;    
                }
                else {
                    clonePos--;    
                }
                dist2 = abs(exitPos - clonePos);
                difdist = dist2 - dist1;
                if(difdist < 0) 
                {
                    isDirWrong = false;    
                }
                    else 
                {
                    isDirWrong = true;
                }
                isChecked = true;
                
            }
        
            if (isDirWrong == false) cout << "WAIT" << endl;
                else {
                    cout << "BLOCK" << endl;
                    if(dirLeft == false) {
                        dirLeft = true;        
                    }
                    else {
                        dirLeft = false;    
                    }
                    isDirWrong = false;
                    isChecked = false;
                }    
        }
        
        else {
            if (isChecked1 == false) 
            {
                
                dist1 = abs(currentElPos - clonePos);
                if (times < 1) cout << "WAIT" << endl;
                
                if (dirLeft == false) {
                    clonePos++;    
                }
                else {
                    clonePos--;    
                }
                dist2 = abs(currentElPos - clonePos);
                difdist = dist2 - dist1;
                if(difdist < 0) 
                {
                    isDirWrong = false;    
                }
                    else 
                {
                    isDirWrong = true;
                }
                isChecked1 = true;
                
            }
        
            if (isDirWrong == false) cout << "WAIT" << endl;
                else {
                    cout << "BLOCK" << endl;
                    if(dirLeft == false) {
                        dirLeft = true;        
                    }
                    else {
                        dirLeft = false;    
                    }
                    isDirWrong = false;
                    isChecked1 = false;
                }    
        }
        
        if (clonePos == currentElPos) {
            
            isFloorChecked = false;
            isChecked1 = false;
            times++;
        }

    }
}