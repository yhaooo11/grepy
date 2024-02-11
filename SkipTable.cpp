#include "SkipTable.h"

using namespace std;

SkipTable::SkipTable(string pattern)
{
    this->pattern = pattern;
    this->pat_len = pattern.length();
    this->init_bc_skip();
    this->init_gs_skip();
}

SkipTable::~SkipTable()
{
}

size_t SkipTable::get_bc_skip(char c)
{
    if (this->bc_skip.find(c) == this->bc_skip.end())
    {
        return this->pat_len;
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

void SkipTable::init_bc_skip()
{
    for (int i = 0; i < this->pat_len; i++)
    {
        this->bc_skip[this->pattern[i]] = this->pat_len - i - 1;
    }
}

void SkipTable::init_gs_skip()
{
    this->gs_skip.resize(this->pat_len);

    int last = this->pat_len - 1;
    int last_prefix_index = last;

    for (int i = this->pat_len; i >= 0; i--)
    {
        if (this->is_prefix(i + 1))
        {
            last_prefix_index = i + 1;
        }
        this->gs_skip[i] = last_prefix_index + (last - i);
    }

    for (int i = 0; i < this->pat_len - 1; i++)
    {
        int suffix_len = this->suffix_len(i);
        int pos = last - suffix_len;
        if (this->pattern[i - suffix_len] != this->pattern[pos])
        {
            this->gs_skip[pos] = suffix_len + (last - i);
        }
    }
}

bool SkipTable::is_prefix(int pos)
{
    int suffix_len = this->pat_len - pos;
    for (int i = 0; i < suffix_len; i++)
    {
        if (pattern[i] != pattern[pos + i])
        {
            return false;
        }
    }
    return true;
}

int SkipTable::suffix_len(int pos)
{
    int i;

    for (i = 0; (this->pattern[pos - i] == this->pattern[this->pat_len - 1 - i]) && (i < pos); i++)
        ;
    return i;
}
