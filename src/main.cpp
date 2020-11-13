#include <iostream>
#include <fstream>
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
        for (size_t i = 0; i < 2 && getline(inputFile, lineContent); i += 1)
        {
            switch (i)
            {
            case 0:
                cout << lineContent << '\n';
                break;
            case 1:
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
        cout << "Unable the path \"" << path << "\"";
    }

    return 0;
}
