#include "SkipTable.hpp"

using namespace std;

SkipTable::SkipTable(string pattern)
{
    this->init_bc_skip(pattern);
    this->init_gs_skip(pattern);
}

SkipTable::~SkipTable()
{
}

size_t SkipTable::get_bc_skip(char c, int pat_len)
{
    if (this->bc_skip.find(c) == this->bc_skip.end())
    {
        return pat_len;
    }
    else
    {
        return this->bc_skip[c];
    }
}

size_t SkipTable::get_gs_skip(int j)
{
    return this->gs_skip[j];
}

void SkipTable::init_bc_skip(string pattern)
{
    size_t pat_len = pattern.length();
    for (int i = 0; i < pat_len; i++)
    {
        this->bc_skip[pattern[i]] = pat_len - i - 1;
    }
}

void SkipTable::init_gs_skip(string pattern)
{
    size_t pat_len = pattern.length();

    this->gs_skip.resize(pat_len);

    int last = pat_len - 1;
    int last_prefix_index = last;

    for (int i = pat_len; i >= 0; i--)
    {
        if (this->is_prefix(pattern, i + 1))
        {
            last_prefix_index = i + 1;
        }
        this->gs_skip[i] = last_prefix_index + (last - i);
    }

    for (int i = 0; i < pat_len - 1; i++)
    {
        int suffix_len = this->suffix_len(pattern, i);
        int pos = last - suffix_len;
        if (pattern[i - suffix_len] != pattern[pos])
        {
            this->gs_skip[pos] = suffix_len + (last - i);
        }
    }
}

bool SkipTable::is_prefix(string pattern, int pos)
{
    int suffix_len = pattern.length() - pos;
    for (int i = 0; i < suffix_len; i++)
    {
        if (pattern[i] != pattern[pos + i])
        {
            return false;
        }
    }
    return true;
}

int SkipTable::suffix_len(string pattern, int pos)
{
    int i;

    for (i = 0; (pattern[pos - i] == pattern[pattern.length() - 1 - i]) && (i < pos); i++)
        ;
    return i;
}
