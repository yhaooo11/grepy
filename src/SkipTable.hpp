#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

#pragma once

class SkipTable
{
public:
    SkipTable(string pattern);
    ~SkipTable();

    size_t get_bc_skip(char c, int pat_len);
    size_t get_gs_skip(int j);

    void printData()
    {
        cout << "Boyer-Moore Bad Character Skip Table:" << endl;
        for (const auto &entry : bc_skip)
        {
            cout << "Character: " << entry.first << ", Skip: " << entry.second << endl;
        }

        cout << "Boyer-Moore Good Suffix Skip Table:" << endl;
        for (size_t i = 0; i < gs_skip.size(); ++i)
        {
            cout << "Index " << i << ", Skip: " << gs_skip[i] << endl;
        }
    }

private:
    unordered_map<char, size_t> bc_skip;
    vector<size_t> gs_skip;

    void init_bc_skip(string pattern);
    void init_gs_skip(string pattern);

    bool is_prefix(string pattern, int pos);
    int suffix_len(string pattern, int pos);
};