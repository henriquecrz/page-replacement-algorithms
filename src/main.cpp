#include <iostream>
#include <fstream>
#include <vector>
#include "constants.hpp"

using namespace std;

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

vector<int> get_int_array(vector<string> string_vector)
{
    vector<int> int_vector;

    for (const auto &item : string_vector)
    {
        int_vector.push_back(stoi(item));
    }

    return int_vector;
}

float round_2_decimal_places(float var)
{
    float value = (int)(var * 100 + .5);

    return (float)value / 100;
}

#include <bits/stdc++.h>

void fifoPageFaults(vector<int> pages, int capacity)
{
    // To represent set of current pages. We use
    // an unordered_set so that we quickly check
    // if a page is present in set or not
    unordered_set<int> s;

    // To store the pages in FIFO manner
    queue<int> indexes;

    // Start from initial page
    int page_faults = 0;

    // cout << sizeof(pages[0]);

    int vector_length = pages.size();

    for (int i = 0; i < vector_length; i++)
    {
        // Check if the set can hold more pages
        if (s.size() < capacity)
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
        }
    }

    float error_rate = (float)page_faults / (float)vector_length;

    cout << " Evolução:" << endl;

    // print evolution

    cout << " Acertos: " << vector_length - page_faults << endl;
    cout << " Erros: " << page_faults << endl;
    cout << " Total de requisições: " << vector_length << endl;
    cout << " Taxa de erro: " << round_2_decimal_places(error_rate) << endl;
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
int predict(int pg[], vector<int> &fr, int pn, int index)
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

void optimalPage(int pg[], int pn, int fn)
{
    // Create an array for given number of
    // frames and initialize it as empty.
    vector<int> fr;

    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;

    for (int i = 0; i < pn; i++)
    {
        // Page found in a frame : HIT
        if (search(pg[i], fr))
        {
            hit++;

            continue;
        }

        // Page not found in a frame : MISS

        // If there is space available in frames.
        if (fr.size() < fn)
        {
            fr.push_back(pg[i]);
        }
        // Find the page to be replaced.
        else
        {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
    }

    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}

void fifo(vector<string> sequence, int frames_quantity)
{
    int sequence_length = sequence.size();
    vector<vector<int>> evolution;
    int hits_quantity = 0;
    int errors_quantity = 0;

    for (size_t i = 0; i < sequence_length; i++)
    {
        vector<int> frame;

        if (i == 0)
        {
            /* code */
        }
        else
        {
            /* code */
        }

        evolution.push_back(frame);
    }

    cout << "Evolução";

    cout << "Acertos";

    cout << " Erros" << errors_quantity << endl;
    cout << " Total de requisições: " << sequence_length << endl;
    cout << " Taxa de erro: " << errors_quantity << endl;
}

void opt(vector<string> sequence, int frames_quantity)
{
    cout << "Evolução";

    cout << "Acertos";

    cout << "Erros";

    cout << "Total de requisições";

    cout << "Taxa de erro";
}

int main()
{
    ifstream input_file(FILE_PATH);
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
        int frames_quantity = stoi(frames_quantity_line);

        vector<int> formatted_sequence = get_int_array(sequence);
        // int int_sequence[sequence.size()];
        // copy(sequence.begin(), sequence.end(), int_sequence);

        fifoPageFaults(formatted_sequence, frames_quantity);        
        // fifo(sequence, frames_quantity);
        // opt(sequence, frames_quantity);
    }
    else
    {
        cout << "Unable to open \"" << FILE_PATH << endl;
    }

    return 0;
}
