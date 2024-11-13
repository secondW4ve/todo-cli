#include <iostream>
#include "CliReader.h"

using namespace std;

int main(int argc, char* argv[])
{
  CliReader cliReader(argc, argv);

  cliReader.executeCommand();

  return 0;
}