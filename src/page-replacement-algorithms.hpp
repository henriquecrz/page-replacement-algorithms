#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

class PageReplacementAlgorithms
{
public:
    PageReplacementAlgorithms();
    Result fifo(vector<int> pages, int frames_quantity);
    bool search(int key, vector<int> &frames);
    int predict(vector<int> pages, vector<int> &frames, int index);
    Result opt(vector<int> pages, int frames_quantity);
};

PageReplacementAlgorithms::PageReplacementAlgorithms()
{

};

Result PageReplacementAlgorithms::fifo(vector<int> pages, int frames_quantity)
{
    set<int> set;
    queue<int> indexes;

    int page_faults = 0;
    string evolution = Value::EMPTY;

    int vector_length = pages.size();

    for (int i = 0; i < vector_length; i++)
    {
        bool is_hit = false;

        if (set.size() < frames_quantity)
        {
            if (set.find(pages[i]) == set.end())
            {
                set.insert(pages[i]);

                page_faults++;

                indexes.push(pages[i]);
            }
            else
            {
                is_hit = true;
            }
        }
        else
        {
            if (set.find(pages[i]) == set.end())
            {
                int val = indexes.front();

                indexes.pop();

                set.erase(val);

                set.insert(pages[i]);

                indexes.push(pages[i]);

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
            for (auto it = set.begin(); it != set.end(); ++it)
            {
                evolution += ' ' + to_string(*it);
            }
        }

        evolution += "\n";
    }

    Utils utils;
    struct Result result;

    result.algorithm = "FIFO";
    result.evolution = evolution;
    result.hits = vector_length - page_faults;
    result.faults = page_faults;
    result.requests = vector_length;
    result.error_rate = utils.round_2_decimal_places((float)page_faults / (float)vector_length);

    return result;
}

bool PageReplacementAlgorithms::search(int key, vector<int> &frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        if (frames[i] == key)
        {
            return true;
        }
    }

    return false;
}

int PageReplacementAlgorithms::predict(vector<int> pages, vector<int> &frames, int index)
{
    int res = -1;
    int farthest = index;
    int vector_length = pages.size();

    for (int i = 0; i < frames.size(); i++)
    {
        int j;

        for (j = index; j < vector_length; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }

                break;
            }
        }

        if (j == vector_length)
        {
            return i;
        }
    }

    return (res == -1) ? 0 : res;
}

Result PageReplacementAlgorithms::opt(vector<int> pages, int frames_quantity)
{
    vector<int> frames;

    int hits = 0;
    string evolution = Value::EMPTY;

    int vector_length = pages.size();

    for (int i = 0; i < vector_length; i++)
    {
        if (search(pages[i], frames))
        {
            hits++;

            evolution += " hit in " + to_string(pages[i]) + "\n";

            continue;
        }

        if (frames.size() < frames_quantity)
        {
            frames.push_back(pages[i]);
        }
        else
        {
            int j = predict(pages, frames, i + 1);
            frames[j] = pages[i];
        }

        for (const auto &item : frames)
        {
            evolution += ' ' + to_string(item);
        }

        evolution += "\n";
    }

    Utils utils;
    struct Result result;

    result.algorithm = "OPT";
    result.evolution = evolution;
    result.hits = hits;
    result.faults = vector_length - hits;
    result.requests = vector_length;
    result.error_rate = utils.round_2_decimal_places((float)(vector_length - hits) / (float)vector_length);

    return result;
}
