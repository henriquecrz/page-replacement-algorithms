#include <iostream>
#include <fstream>
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
