#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <file.h>

FILE* OpenFile (const char* filename, const char* mode)
{
    assert (filename && "filename is NULL in OpenFile");
    assert (   mode  &&  "mode " "is NULL in OpenFile");

    FILE* file = fopen (filename, mode);
    if ( file == NULL )
    {
        fprintf (stderr, "Could not find the '%s' to be opened!" "\n", filename);
        return NULL;
    }

    return file;
}

long FileSize (FILE* file_ptr)
{
    assert (file_ptr && "file_ptr is NULL in FileSize" "\n");

    long curr_pos = ftell (file_ptr);
    if ( curr_pos == -1L )
        return -1;

    if ( fseek (file_ptr, 0L, SEEK_END) )
        return -1;

    long number_symbols = ftell (file_ptr);
    if ( number_symbols == -1L && number_symbols <= 0)
        return -1;

    if ( fseek (file_ptr, curr_pos, SEEK_SET) )
        return -1;

    return number_symbols;
}

char* ReadInBuffer (FILE* file_ptr, const long numb_symb)
{
    assert (file_ptr && "file_ptr is NULL in ReadInBuffer" "\n");
    assert (numb_symb > 0L && "numb_symb <= 0 in ReadInBuffer" "\n");

    char* buffer = (char*) calloc ((size_t)numb_symb + 1, sizeof (char));               // EOF -> +1
    if (buffer == NULL)
    {
        fprintf (stderr, "");
        return NULL;
    }

    size_t read_symb = fread (buffer, sizeof (buffer[0]), (size_t) numb_symb, file_ptr);

    assert (read_symb == (size_t) numb_symb && "fread error in ReadInBuffer");

    return buffer;
}

int CloseFile (FILE* file_ptr, const char* filename)
{
    assert (file_ptr && "file_ptr is NULL in CloseFile");
    assert (filename && "filename is NULL in CloseFile");

    fprintf (stderr, "%s is closing..." "\n", filename);

    assert ( fclose (file_ptr) == 0 && "fclose error in CloseFile");

    fprintf (stderr, "%s is closed" "\n", filename);

    return 0;
}
