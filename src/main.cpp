#include "SkipTable.hpp"
#include "Grepy.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    cerr << "Usage: ./grepy <pattern> <filename>" << endl;
    return EXIT_FAILURE;
  }

  // program_options::parse(argc, argv);

  Grepy g(argv[2], argv[1]);

  g.search();
}
