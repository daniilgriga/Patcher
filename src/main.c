#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "patch.h"

int main (const int argc, const char* argv[])
{
    const char* filename = (argc >= 2) ? argv[1] : NULL;

    FILE* input_file = OpenFile (filename, "rb");
    if (input_file == NULL)
        return 1;

    long numb_symb = FileSize (input_file);
    if ( numb_symb == -1)
    {
        fprintf (stderr, "Error with file size, check '%s'." "\n", filename);
        return 1;
    }

    char* buffer = ReadInBuffer (input_file, numb_symb);

    CloseFile (input_file, filename);

    const char* rules_filename = (argc >= 3) ? argv[2] : NULL;

    Patch (buffer, rules_filename);

    const char* out_filename = (argc >= 4) ? argv[3] : NULL;

    FILE* output_file = OpenFile (out_filename, "wb");

    fwrite (buffer, (size_t) numb_symb, sizeof (buffer[0]), output_file);

    CloseFile (output_file, out_filename);

    free (buffer);
    return 0;
}
