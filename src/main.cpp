#include <iostream>
#include <fstream>
// #include "index.cpp"
using namespace std;

class Index
{
public:
    int kSequence = 0;
    int kFramesQuantity = 1;
};

int main()
{
    string path = "..\\assets\\entrada.txt";
    ifstream inputFile(path);
    string lineContent;
    Index index;

    if (inputFile.is_open())
    {
        // while (getline(inputFile, lineContent))
        // {
        //     cout << lineContent << '\n';
        // }

        for (size_t i = 0; i < 2 && getline(inputFile, lineContent); i += 1)
        {
            switch (i)
            {
            case 0:
                cout << lineContent;
                break;
            case 1:
                cout << lineContent;
                break;
            default:
                break;
            }
        }

        inputFile.close();
    }
    else
    {
        cout << "Unable the path \"" << path << "\"";
    }

    // for (size_t i = 0; i < 2 && getline(inputFile, lineContent); i += 1)
    // {
    //     switch (i)
    //     {
    //     case 0:
    //         cout << lineContent;
    //         break;
    //     case 1:
    //         cout << lineContent;
    //         break;
    //     default:
    //         break;
    //     }
    // }

    // inputFile.close();

    return 0;
}
