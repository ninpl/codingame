#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getvalue(std::vector<std::vector<std::string> >& lines,
            std::vector<std::string>& checknum, int width, int height)
{
    int value = 0;
    for (int i = 0; i < lines[0].size(); ++i) {
        
        bool match = true;
        for (int j = 0; j < height; ++j) {
            string& str = lines[j][i];
            string& check = checknum[j];
            if (str != check) {
                match = false;
                break;
            }
        }
        
        if (match) {
            value = i;
            break;
        }
    }
    
    return value;
}

std::vector<std::string> getvalue(std::vector<std::vector<std::string> >& lines,
                                    int value, int width, int height)
{
    std::vector<std::string> number;
    for (int i = 0; i < lines[0].size(); ++i) {
        for (int j = 0; j < height; ++j) {
            std::string& str = lines[j][value];
            number.push_back(str);
        }
        break;
    }
    return number;
}

int getopvalue(std::vector<std::vector<std::string> >& lines,
                std::vector<std::string> value1, 
                int valueHeight, int width, int height)
{
    int value = 0;
    int nSegment = valueHeight / height;
    int powersegment = nSegment;
    for (int i = 0; i < valueHeight; i += height) {
        std::vector<std::string> number;
        for (size_t j = i; j < i + height; ++j) {
            number.push_back(value1[j]);
        }
        int x = getvalue(lines, number, width, height);
        for (int j = powersegment - 1; j > 0; --j)
            x *= 20;
        value += x;
        powersegment--;
    }
    return value;
}
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int L;
    int H;
    cin >> L >> H; cin.ignore();
    
    std::vector<std::vector<std::string> > lines;
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
        std::vector<std::string > segment;
        for (size_t i = 0; i < numeral.size(); i += L) {
            std::string str;
            for (size_t j = i; j < i + L; ++j) {
                char c = numeral[j];
                str.append(1, c);
            }
            segment.push_back(str);
        }
        
        lines.push_back(segment);        
    }
        
    std::vector<std::string> value1;
    int S1;
    cin >> S1; cin.ignore();
    for (int i = 0; i < S1; i++) {
        string num1Line;
        cin >> num1Line; cin.ignore();
        value1.push_back(num1Line);
        cerr << num1Line << endl;
    }
    int left = getopvalue(lines, value1, S1, L, H);
    cerr << "realvalue1=" << left << endl;
    
    std::vector<std::string> value2;
    int S2;
    cin >> S2; cin.ignore();
    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();
        value2.push_back(num2Line);
        cerr << num2Line << endl;
    }
    int right = getopvalue(lines, value2, S2, L, H);
    cerr << "realvlaue2=" << right << endl;
    
    string operation;
    cin >> operation; cin.ignore();
    cerr << "op=" << operation << endl;
    
    int64_t result = 0;
    if (operation == "+") {
        result = left + right;
    } else if (operation == "-") {
        result = left - right;
    } else if (operation == "*") {
        result = left;
        result *= right;
    } else if (operation == "/") {
        if (right != 0)
            result = left / right;
    }
    
    std::vector<int> vecval;
    cerr << "result=" << result << endl;
    while (result > 0) {
        int diff = (result % 20);
        vecval.insert(vecval.begin(), diff);
        result /= 20;
    }
    if (vecval.size() == 0) {
        vecval.push_back(0);
    }
    
    for (size_t index = 0; index < vecval.size(); ++index) {
        std::vector<std::string> number = getvalue(lines, vecval[index], L, H);
        for (size_t i = 0; i < number.size(); ++i) {
            cout << number[i] << endl;
        }        
    }
}