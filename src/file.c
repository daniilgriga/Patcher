#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <file.h>
#include <errors.h>

FILE* OpenFile (const char* filename, const char* mode)
{
    assert (filename && "filename is NULL in OpenFile" "\n");
    assert (   mode  &&  "mode " "is NULL in OpenFile" "\n");

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
    {
        perror ("The following error occurred");
        return NO_SYMBOLS_ERR;
    }

    if ( fseek (file_ptr, 0L, SEEK_END) )
    {
        perror ("The following error occurred");
        return NO_SYMBOLS_ERR;
    }

    long number_symbols = ftell (file_ptr);
    if ( number_symbols == -1L && number_symbols <= 0)
    {
        perror ("The following error occurred");
        return NO_SYMBOLS_ERR;
    }

    if ( fseek (file_ptr, curr_pos, SEEK_SET) )
    {
        perror ("The following error occurred");
        return NO_SYMBOLS_ERR;
    }

    return number_symbols;
}

char* ReadInBuffer (FILE* file_ptr, const long numb_symb)
{
    assert (file_ptr && "file_ptr is NULL in ReadInBuffer" "\n");
    assert (numb_symb > 0L && "numb_symb <= 0 in ReadInBuffer" "\n");

    char* buffer = (char*) calloc ( (size_t) numb_symb + 1, sizeof (char) );               // EOF -> +1
    if (buffer == NULL)
    {
        fprintf (stderr, "There's no place in the memory for your file!" "\n");
        return NULL;
    }

    size_t read_symb = fread (buffer, sizeof (buffer[0]), (size_t) numb_symb, file_ptr);
    if ( read_symb != (size_t) numb_symb)
    {
        perror ("The following error occurred");
        return NULL;
    }

    return buffer;
}

int CloseFile (FILE* file_ptr)
{
    assert (file_ptr && "file_ptr is NULL in CloseFile" "\n");

    if ( fclose (file_ptr) == EOF )
    {
        perror ("Error occured");
        return FILE_CLOSE_ERR;
    }

    return 0;
}
