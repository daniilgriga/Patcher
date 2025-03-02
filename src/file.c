#include <stdio.h>
#include <assert.h>

#include <file.h>

FILE* OpenFile (const char* filename, const char* mode)
{
    assert (filename && "filename is NULL in OpenFile");
    assert (   mode  &&  "mode " "is NULL in OpenFile");

    FILE* file = fopen (filename, mode);

    assert (file && "fopen error: file is NULL in OpenFile");

    return file;
}

long FileSize (FILE* file_ptr)
{
    assert (file_ptr && "file_ptr in FileSize is NULL" "\n");

    long curr_pos = ftell (file_ptr);
    assert (curr_pos != -1L && "ftell_error (-1L) in curr_pos in FileSize" "\n");

    if (fseek (file_ptr, 0L, SEEK_END))
        assert (0 && "fseek error" "\n");

    long number_symbols = ftell (file_ptr);
    assert (number_symbols != -1L && "ftell_error (-1L) in number_symbols in FileSize" "\n");
    assert (number_symbols  >  0L && "ftell_error (>0L) in number_symbols in FileSize" "\n");

    if (fseek (file_ptr, curr_pos, SEEK_SET))
        assert (0 && "fseek error" "\n");

    return number_symbols;
}

char* ReadInBuffer (FILE* file_ptr, const long number_symbols)
