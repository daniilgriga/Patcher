#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "patch.h"
#include "errors.h"
#include "tools.h"

int main (const int argc, const char* argv[])
{
    const char* filename = (argc >= 2) ? argv[1] : NULL;
    if (filename == NULL)
    {
        fprintf (stderr, "You don't enter file for crack in first cmd argument!" "\n");
        return NULL_PTR_ERR;
    }

    FILE* input_file = OpenFile (filename, "rb");
    if (input_file == NULL)
        return FILE_OPEN_ERR;

    long numb_symb = FileSize (input_file);
    if ( numb_symb == FILE_SIZE_ERR )
        return FILE_SIZE_ERR;

    char* buffer = ReadInBuffer (input_file, numb_symb);
    if (buffer == NULL)
        return CREATE_BUF_ERR;

    if ( CloseFile (input_file) )
        return FILE_CLOSE_ERR;

    const char* rules_filename = (argc >= 3) ? argv[2] : NULL;
    if (rules_filename == NULL)
    {
        fprintf (stderr, "You don't enter file with rules in second cmd argument!" "\n");
        return NULL_PTR_ERR;
    }

    int error_code = Patch (buffer, rules_filename);
    if (error_code != NO_ERRORS)
        return error_code;

    const char* out_filename = (argc >= 4) ? argv[3] : NULL;
    if (out_filename == NULL)
    {
        fprintf (stderr, "You don't enter output file in third cmd argument!" "\n");
        PATCHER_ERROR_CHECK (NULL_PTR_ERR)
        return NULL_PTR_ERR;
    }

    FILE* output_file = OpenFile (out_filename, "wb");
    if (output_file == NULL)
        return FILE_OPEN_ERR;

    size_t writed_symb = fwrite (buffer, sizeof (buffer[0]), (size_t) numb_symb, output_file);
    if (writed_symb != (size_t) numb_symb)
    {
        perror ("The following error occurred");
        PATCHER_ERROR_CHECK (WRITE_BUF_ERR)
        return WRITE_BUF_ERR;
    }

    if ( CloseFile (output_file) )
        return FILE_CLOSE_ERR;

    free (buffer);

    return 0;
}
