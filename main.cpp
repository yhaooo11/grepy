#include "SkipTable.h"
#include "Grepy.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  Grepy g("text.txt", "text");

  g.search();
}
