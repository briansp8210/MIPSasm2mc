#include <string>
#include <fstream>
#include <iostream>
#include "parser.hpp"
#include "auxtool.hpp"
using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        error_msg("Wrong arguments number!");
    }

    ifstream assembly(argv[1]);
    ofstream machine_code(argv[2]);

    encode_instr(assembly, machine_code);

    assembly.close();
    machine_code.close();

    return 0;
}
