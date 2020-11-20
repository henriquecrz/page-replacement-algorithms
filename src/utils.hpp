#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Utils
{
public:
    Utils();
    vector<string> split(string value, string delimiter);
    vector<int> get_int_vector(vector<string> string_vector);
    float round_2_decimal_places(float value);
    void print_results(vector<Result> results);
    void write_to_file(vector<Result> results);
};

Utils::Utils()
{

};

vector<string> Utils::split(string value, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = value.find(delimiter, pos_start)) != string::npos)
    {
        token = value.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;

        res.push_back(token);
    }

    res.push_back(value.substr(pos_start));

    return res;
}

vector<int> Utils::get_int_vector(vector<string> string_vector)
{
    vector<int> int_vector;

    for (const auto &item : string_vector)
    {
        int_vector.push_back(stoi(item));
    }

    return int_vector;
}

float Utils::round_2_decimal_places(float value)
{
    float result = (int)(value * 100 + .5);

    return (float)result / 100;
}

void Utils::print_results(vector<Result> results)
{
    for (const auto &item : results)
    {
        cout << item.algorithm << endl;
        cout << Value::EMPTY << endl;
        cout << "- Evolução: " << endl
             << item.evolution << endl;
        cout << "- Acertos: " << item.hits << endl;
        cout << "- Erros: " << item.faults << endl;
        cout << "- Total de requisições: " << item.requests << endl;
        cout << "- Taxa de erro: " << item.error_rate;
        cout << Value::EMPTY << endl;
    }
}

void Utils::write_to_file(vector<Result> results)
{
    ofstream output_file(Path::OUTPUT_FILE);

    if (output_file.is_open())
    {
        for (const auto &item : results)
        {
            output_file << item.algorithm << endl;
            output_file << Value::EMPTY << endl;
            output_file << "- Evolução: " << endl
                        << item.evolution << endl;
            output_file << "- Acertos: " << item.hits << endl;
            output_file << "- Erros: " << item.faults << endl;
            output_file << "- Total de requisições: " << item.requests << endl;
            output_file << "- Taxa de erro: " << item.error_rate;
            output_file << Value::EMPTY << endl;
        }

        output_file.close();
    }
    else
    {
        cout << "Unable to open \"" << Path::OUTPUT_FILE << endl;
    }
}
