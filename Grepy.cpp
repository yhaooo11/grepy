#include "Grepy.h"
#include <fstream>
#include <iostream>

using namespace std;

Grepy::Grepy(char *filename, char *pattern)
{
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
            cout << "Pattern found at index " << i + 1 << endl;
            // cout << text.substr(i + 1, pattern.length()) << endl;
            cout << this->buffer[i + 1] << endl;
            // return 0;
            i += this->pattern.length() + 1;
        }
        else
        {
            i += max(this->skip_table->get_bc_skip(this->buffer[i]), this->skip_table->get_gs_skip(j));
        }
    }
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