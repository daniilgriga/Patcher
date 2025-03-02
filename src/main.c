#include <stdio.h>

#include "file.h"

int main (const int argc, const char* argv[])
{
    const char* filename = (argc >= 2) ? argv[1] : NULL;

    FILE* input_file = OpenFile (filename, "rb");

    long n_symb = FileSize (input_file);

    fprintf (stderr, "FILE SIZE = %ld" "\n", n_symb);

    return 0;
}
