#include <iostream>
#include <fstream>
#include <vector>
#include "result.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "page-replacement-algorithms.hpp"

using namespace std;

int main()
{
    ifstream input_file(Path::INPUT_FILE);
    string line_content = Value::EMPTY;
    string sequence_line = Value::EMPTY;
    string frames_quantity_line = Value::EMPTY;

    if (input_file.is_open())
    {
        for (size_t line = 0; line < File::LENGTH && getline(input_file, line_content); line += 1)
        {
            switch (line)
            {
            case LineIndex::SEQUENCE:
                sequence_line = line_content;

                break;
            case LineIndex::FRAMES_QUANTITY:
                frames_quantity_line = line_content;

                break;
            default:
                break;
            }
        }

        input_file.close();

        Utils utils;
        PageReplacementAlgorithms pageReplacementAlgorithms;

        vector<string> sequence = utils.split(sequence_line, Delimiter::COMMA);
        vector<int> formatted_sequence = utils.get_int_vector(sequence);
        int frames_quantity = stoi(frames_quantity_line);
        Result fifo_result = pageReplacementAlgorithms.fifo(formatted_sequence, frames_quantity);
        Result opt_result = pageReplacementAlgorithms.opt(formatted_sequence, frames_quantity);

        vector<Result> results{fifo_result, opt_result};

        utils.print_results(results);
        utils.write_to_file(results);
    }
    else
    {
        cout << "Unable to open \"" << Path::INPUT_FILE << endl;
    }

    return 0;
}
