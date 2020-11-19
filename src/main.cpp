#include <iostream>
#include <fstream>
#include <vector>
#include "constants.hpp"

using namespace std;

// Utils
vector<string> split(string value, string delimiter)
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

// Utils
vector<int> get_int_vector(vector<string> string_vector)
{
    vector<int> int_vector;

    for (const auto &item : string_vector)
    {
        int_vector.push_back(stoi(item));
    }

    return int_vector;
}

// Utils
float round_2_decimal_places(float var)
{
    float value = (int)(var * 100 + .5);

    return (float)value / 100;
}

// PageReplacementAlgorithms
struct Result
{
    string algorithm;
    string evolution;
    int hits;
    int faults;
    int requests;
    float error_rate;
};

#include <bits/stdc++.h>

// PageReplacementAlgorithms
Result fifo(vector<int> pages, int frames_quantity)
{
    // To represent set of current pages. We use
    // an unordered_set so that we quickly check
    // if a page is present in set or not
    set<int> s;

    // To store the pages in FIFO manner
    queue<int> indexes;

    // Start from initial page
    int page_faults = 0;

    int vector_length = pages.size();
    string evolution = EMPTY_STRING;

    for (int i = 0; i < vector_length; i++)
    {
        bool is_hit = false;

        // Check if the set can hold more pages
        if (s.size() < frames_quantity)
        {
            // Insert it into set if not present
            // already which represents page fault
            if (s.find(pages[i]) == s.end())
            {
                // Insert the current page into the set
                s.insert(pages[i]);

                // increment page fault
                page_faults++;

                // Push the current page into the queue
                indexes.push(pages[i]);
            }
            else
            {
                is_hit = true;
            }
        }
        // If the set is full then need to perform FIFO
        // i.e. remove the first page of the queue from
        // set and queue both and insert the current page
        else
        {
            // Check if current page is not already
            // present in the set
            if (s.find(pages[i]) == s.end())
            {
                // Store the first page in the
                // queue to be used to find and
                // erase the page from the set
                int val = indexes.front();

                // Pop the first page from the queue
                indexes.pop();

                // Remove the indexes page from the set
                s.erase(val);

                // insert the current page in the set
                s.insert(pages[i]);

                // push the current page into
                // the queue
                indexes.push(pages[i]);

                // Increment page faults
                page_faults++;
            }
            else
            {
                is_hit = true;
            }
        }

        if (is_hit)
        {
            evolution += " hit in " + to_string(pages[i]);
        }
        else
        {
            for (auto it = s.begin(); it != s.end(); ++it)
            {
                evolution += ' ' + to_string(*it);
            }
        }

        evolution += "\n";
    }

    struct Result result;

    result.algorithm = "FIFO";
    result.evolution = evolution;
    result.hits = vector_length - page_faults;
    result.faults = page_faults;
    result.requests = vector_length;
    result.error_rate = round_2_decimal_places((float)page_faults / (float)vector_length);

    return result;
}

// Function to check whether a page exists
// in a frame or not
bool search(int key, vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
    {
        if (fr[i] == key)
        {
            return true;
        }
    }

    return false;
}

// Function to find the frame that will not be used
// recently in future after given index in pg[0..pn-1]
int predict(vector<int> pg, vector<int> &fr, int pn, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;

    for (int i = 0; i < fr.size(); i++)
    {
        int j;

        for (j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }

                break;
            }
        }

        // If a page is never referenced in future,
        // return it.
        if (j == pn)
        {
            return i;
        }
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

// PageReplacementAlgorithms
Result opt(vector<int> pages, int frames_quantity)
{
    // Create an array for given number of
    // frames and initialize it as empty.
    vector<int> frames;
    int vector_length = pages.size();

    // Traverse through page reference array
    // and check for miss and hit.
    int hits = 0;

    string evolution = EMPTY_STRING;

    for (int i = 0; i < vector_length; i++)
    {
        // Page found in a frame : HIT
        if (search(pages[i], frames))
        {
            hits++;

            evolution += " hit in " + to_string(pages[i]) + "\n";

            continue;
        }

        // Page not found in a frame : MISS

        // If there is space available in frames.
        if (frames.size() < frames_quantity)
        {
            frames.push_back(pages[i]);
        }
        // Find the page to be replaced.
        else
        {
            int j = predict(pages, frames, vector_length, i + 1);
            frames[j] = pages[i];
        }

        for (const auto &item : frames)
        {
            evolution += ' ' + to_string(item);
        }

        evolution += "\n";
    }

    // cout << "No. of hits = " << hits << endl;
    // cout << "No. of misses = " << vector_length - hits << endl;

    struct Result result;

    result.algorithm = "OPT";
    result.evolution = evolution;
    result.hits = hits;
    result.faults = vector_length - hits;
    result.requests = vector_length;
    result.error_rate = round_2_decimal_places((float)(vector_length - hits) / (float)vector_length);

    return result;
}

// Utils
void print_results(vector<Result> results)
{
    for (const auto &item : results)
    {
        cout << item.algorithm << endl;
        cout << EMPTY_STRING << endl;
        cout << "- Evolução: " << endl << item.evolution << endl;
        cout << "- Acertos: " << item.hits << endl;
        cout << "- Erros: " << item.faults << endl;
        cout << "- Total de requisições: " << item.requests << endl;
        cout << "- Taxa de erro: " << item.error_rate;
        cout << EMPTY_STRING << endl;
    }
}

// Utils
void write_to_file(vector<Result> results)
{
    ofstream output_file(OUTPUT_FILE_PATH);

    if (output_file.is_open())
    {
        for (const auto &item : results)
        {
            output_file << item.algorithm << endl;
            output_file << EMPTY_STRING << endl;
            output_file << "- Evolução: " << endl << item.evolution << endl;
            output_file << "- Acertos: " << item.hits << endl;
            output_file << "- Erros: " << item.faults << endl;
            output_file << "- Total de requisições: " << item.requests << endl;
            output_file << "- Taxa de erro: " << item.error_rate;
            output_file << EMPTY_STRING << endl;
        }

        output_file.close();
    }
    else
    {
        cout << "Unable to open \"" << OUTPUT_FILE_PATH << endl;
    }
}

int main()
{
    ifstream input_file(INPUT_FILE_PATH);
    string line_content = EMPTY_STRING;
    string sequence_line = EMPTY_STRING;
    string frames_quantity_line = EMPTY_STRING;

    if (input_file.is_open())
    {
        for (size_t line = 0; line < FILE_LENGTH && getline(input_file, line_content); line += 1)
        {
            switch (line)
            {
            case SEQUENCE_LINE_INDEX:
                sequence_line = line_content;

                break;
            case FRAMES_QUANTITY_LINE_INDEX:
                frames_quantity_line = line_content;

                break;
            default:
                break;
            }
        }

        input_file.close();

        vector<string> sequence = split(sequence_line, DELIMITER);
        vector<int> formatted_sequence = get_int_vector(sequence);
        int frames_quantity = stoi(frames_quantity_line);

        Result fifo_result = fifo(formatted_sequence, frames_quantity);
        Result opt_result = opt(formatted_sequence, frames_quantity);

        vector<Result> results{fifo_result, opt_result};

        print_results(results);
        write_to_file(results);
    }
    else
    {
        cout << "Unable to open \"" << INPUT_FILE_PATH << endl;
    }

    return 0;
}
