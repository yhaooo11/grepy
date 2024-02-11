#include <vector>
#include <unordered_map>
#include <string>
#include "SkipTable.h"

using namespace std;

class Grepy
{
public:
    Grepy(char *filename, char *pattern);
    ~Grepy();

    void search();

private:
    struct Occurrence
    {
        int line_start;
        int line_end;
        vector<int> occ_indexes;
    };

    string pattern;

    SkipTable *skip_table;

    // TODO: change to map to allow for multiple files
    vector<Occurrence> occurrences;

    vector<char> buffer;

    void read_file(char *filename);

    void print_occurrences();
};