#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "errors.h"
#include "tools.h"

FILE* OpenFile (const char* filename, const char* mode)
{
    assert (filename && "filename is NULL in OpenFile" "\n");
    assert (   mode  &&  "mode " "is NULL in OpenFile" "\n");

    FILE* file = fopen (filename, mode);
    if ( file == NULL )
    {
        fprintf (stderr, "\n" "Could not find the '%s' to be opened!" "\n", filename);
        PATCHER_ERROR_CHECK (FILE_OPEN_ERR)
        return NULL;
    }

    return file;
}

#define FILE_SIZE_CHECK(status)   if ( status )                                 \
                                  {                                             \
                                      perror ("The following error occurred");  \
                                      PATCHER_ERROR_CHECK (FILE_SIZE_ERR);      \
                                      return FILE_SIZE_ERR;                     \
                                  }

long FileSize (FILE* file_ptr)
{
    assert (file_ptr && "file_ptr is NULL in FileSize" "\n");

    long curr_pos = ftell (file_ptr);
    FILE_SIZE_CHECK (curr_pos == -1L)

    FILE_SIZE_CHECK ( fseek (file_ptr, 0L, SEEK_END) )

    long number_symbols = ftell (file_ptr);
    FILE_SIZE_CHECK ( number_symbols == -1L && number_symbols <= 0 )

    FILE_SIZE_CHECK ( fseek (file_ptr, curr_pos, SEEK_SET) )

    return number_symbols;
}

#undef FILE_SIZE_CHECK

char* ReadInBuffer (FILE* file_ptr, const long numb_symb)
{
    char* buffer = (char*) calloc ( (size_t) numb_symb + 1, sizeof (char) );               // EOF -> +1
    if (buffer == NULL)
    {
        PATCHER_ERROR_CHECK (CREATE_BUF_ERR)
        return NULL;
    }

    size_t read_symb = fread (buffer, sizeof (buffer[0]), (size_t) numb_symb, file_ptr);
    if ( read_symb != (size_t) numb_symb)
    {
        perror ("The following error occurred");
        PATCHER_ERROR_CHECK (READ_BUF_ERR)
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
        PATCHER_ERROR_CHECK (FILE_CLOSE_ERR)
        return FILE_CLOSE_ERR;
    }

    return 0;
}
