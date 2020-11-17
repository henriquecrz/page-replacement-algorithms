#include <iostream>
#include <fstream>
#include <vector>
#include "constants.hpp"

using namespace std;

int main()
{
    ifstream inputFile(kFilePath);
    string lineContent = kEmptyString;

    if (inputFile.is_open())
    {
        for (size_t line = 0; line < kFileLength && getline(inputFile, lineContent); line += 1)
        {
            switch (line)
            {
            case kSequenceLine:
                cout << lineContent << '\n';
                break;
            case kFramesQuantityLine:
                cout << lineContent << '\n';
                break;
            default:
                break;
            }
        }

        inputFile.close();
    }
    else
    {
        cout << "Unable to open \"" << kFilePath << "\"";
    }

    return 0;
}

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    
    return res;
}
