#include <bits/stdc++.h>;
using namespace std;

struct NOTE
{
    int row;
    int L, R;
    char duration; 
    char pitch;
};

vector<string> score;
vector<NOTE> notes;

map<int, char> pitches;
set<int> lines;              
set<int> spaces;             
    
int W, H;
int lineLength = 0, spaceLength = 0;
int lastNote = 0;   
int preLedger;

bool notesLeft = true;

void AssignPitches(set<int> &indices, int &L, string pitchName)
{
    int count = 0;
    int index = 0;
    
    for(auto it : indices)
    {
        pitches[it] = pitchName[index];
        count++;
        
        if(count == L)
        {
            count = 0;
            index++;
        }
    }
}

void MakeScore(int w, int h, vector<pair<char, int>> vals)
{
    string line = "";

    for(auto it : vals)
    {
        int pixels = it.second;
        while(pixels > 0)
        {
            line += (it.first == 'B') ? '#' : '.';
            pixels--; 
            
            if(line.length() == w)
            {
                score.push_back(line);
                line.clear();
            }
        }
    }
}
    
void FindLines()
{
    int minDepth = 99999;
    vector<int> v;
    
    for(int i=0; i<score.size(); i++)
    {
        int blackPixel = score[i].find('#');
        
        if(blackPixel != string::npos)
        {
            v.push_back(i);
            minDepth = min(blackPixel, minDepth);
        }
    }

    int low = -1, high = 0;
    
    for(int i=0; i<v.size(); i++)
    {
        int index = v[i];
        
        if(score[index].find('#') == minDepth)
        {
            if(low == -1) low = index;
            high = index;
            lines.insert(index);
        }
    }
    lineLength = lines.size()/5;
    spaceLength = 0;
    preLedger = high;

    bool first = true;
    
    for(int i=low; i<score.size(); i++)
    {
        if(!first && i > high) break;
        
        if(lines.count(i) == 0) 
        {
            if(first) spaceLength++;
            spaces.insert(i);
        }
        else if(first && spaceLength != 0) first = false; 
    }
    int index = low - spaceLength;

    for(int i=0; i < score.size(); i++)
    {
        if(i <= low-1 && i > low-spaceLength) spaces.insert(i);
        if(i >= high+1)
        {
            if(i < high + spaceLength) spaces.insert(i);
            else lines.insert(i);
        }
    }
    AssignPitches(lines, lineLength, "FDBGEC");
    AssignPitches(spaces, spaceLength, "GECAFD");
}


NOTE FindNote()
{
    NOTE note;
    int closest = 99999;
    int index = -1;
    
    for(int i=0; i<score.size(); i++)
    {
        int black = score[i].find('#', lastNote);
        if(black != string::npos)
        {
            if(lines.count(i) != 0) continue;

            if(black < closest)
            {
                closest = black;
                index = i;
            }
        }
    }    
    if(closest == 99999)
    {
        notesLeft = false;
        return note;
    }
    
    int noteEnd = score[index].find('.', closest);
    
    note.row = index;
    note.L = closest;

    if((note.row >= preLedger+spaceLength && abs(noteEnd-closest) <= 15) 
    || (abs(noteEnd-closest) < 10))
    {
        note.duration = 'H';
        int nextBlack;
     
        if(note.row > preLedger && pitches[note.row] == 'D')
        {
            for(int i=note.L; i<noteEnd - abs(noteEnd-note.L)/2; i++)
            {
                if(score[note.row][i] == '.')
                {
                    note.duration = 'H';
                    break;
                }
                else if(i == noteEnd-1) note.duration = 'Q';
            }
        }
        nextBlack = score[index].find('#', noteEnd);
        noteEnd = score[index].find('.', nextBlack);
    }
    else note.duration = 'Q';
    
    note.R = noteEnd;
    return note;
}



int main()
{
    cin >> W >> H; cin.ignore();
    string IMAGE;
    getline(cin, IMAGE);

    vector<pair<char, int>> v;

    while(IMAGE.length() > 3)
    {
        char c = IMAGE[0];
        string num = IMAGE.substr(2, IMAGE.find(' ', 2));
        v.push_back({c, stoi(num)});
        IMAGE = IMAGE.substr(num.length()+1); 
    }
    MakeScore(W, H, v);
    FindLines();
    
    while(notesLeft)
    {
        NOTE note = FindNote();
        
        if(!notesLeft) break;

        note.pitch = (note.row > preLedger) ? pitches[note.row+(lineLength/2)] : pitches[note.row+lineLength];
        notes.push_back(note);
        lastNote = note.R;
    }  
    
    for(int i=0; i<notes.size(); i++)
    {
        cout << notes[i].pitch << notes[i].duration;
        
        (i < notes.size()-1) ? cout << ' ' : cout << endl;
    }
}