#include "Grepy.h"
#include <fstream>
#include <iostream>

using namespace std;

Grepy::Grepy(char *filename, char *pattern)
{
    this->filename = filename;
    this->pattern = pattern;
    this->read_file(filename);
    this->skip_table = new SkipTable(pattern);
}

Grepy::~Grepy()
{
    delete this->skip_table;
}

void Grepy::search()
{
    size_t i = this->pattern.length() - 1;

    while (i < this->buffer.size())
    {
        int j = this->pattern.length() - 1;

        while (j >= 0 && this->buffer[i] == pattern[j])
        {
            i--;
            j--;
        }

        if (j < 0)
        {
            pair<int, int> lines = this->get_lines(i + 1);
            this->insert_occurence(lines.first, lines.second, i + 1);
            i += this->pattern.length() + 1;
        }
        else
        {
            i += max(this->skip_table->get_bc_skip(this->buffer[i]), this->skip_table->get_gs_skip(j));
        }
    }

    this->print_occurrences();
}

void Grepy::read_file(char *filename)
{
    ifstream file(filename, ios::binary);

    if (!file.is_open())
    {
        cerr << "Error: could not open file" << endl;
        exit(1);
    }

    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    file.seekg(0, ios::beg);

    this->buffer.resize(fileSize);

    file.read(this->buffer.data(), fileSize);

    file.close();
}

pair<int, int> Grepy::get_lines(int occ_index)
{
    size_t line_start = occ_index;
    size_t line_end = occ_index;

    while (line_start > 0 && this->buffer[line_start] != '\n')
    {
        line_start--;
    }

    if (line_start != 0)
    {
        line_start++;
    }

    while (line_end < this->buffer.size() && this->buffer[line_end] != '\n')
    {
        line_end++;
    }

    return make_pair(line_start, line_end);
}

void Grepy::insert_occurence(int line_start, int line_end, int occ_index)
{
    Occurrence occ;
    occ.line_start = line_start;
    occ.line_end = line_end;
    occ.occ_indexes.push_back(occ_index);

    if (!this->occurrences.empty())
    {
        Occurrence last_occ = this->occurrences.back();

        if (last_occ.line_start == line_start && last_occ.line_end == line_end)
        {
            this->occurrences.back().occ_indexes.push_back(occ_index);
            return;
        }
    }

    this->occurrences.push_back(occ);
}

void Grepy::print_occurrences()
{
    for (const auto &occ : this->occurrences)
    {
        string line(this->buffer.begin() + occ.line_start, this->buffer.begin() + occ.line_end);
        cout << this->filename << ": " << line << endl;
    }
}