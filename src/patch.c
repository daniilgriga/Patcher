#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "file.h"
#include "patch.h"

struct Byte_t
{
    int address;
    int curr_value;
    int next_value;
};

int Patch (char* buffer, const char* rules_filename)
{
    assert (buffer && "buffer is NULL in Patch" "\n");
    assert (rules_filename && "rules_filename is NULL in Patch" "\n");

    FILE* rules_file = OpenFile (rules_filename, "rb");

    long numb_symb = FileSize (rules_file);

    char* rules_buffer = ReadInBuffer (rules_file, numb_symb);

    char* ptr_rules = rules_buffer;

    ReplaceByte (buffer, &ptr_rules);

    while (true)
        if (strchr (ptr_rules, '<'))
            ReplaceByte (buffer, &ptr_rules);
        else
            break;

    free (rules_buffer);

    return 0;
}

int ReplaceByte (char* buffer, char** ptr_rules)
{
    struct Byte_t byte = GetByte (ptr_rules);

    if ((int) buffer[byte.address] == byte.curr_value)
              buffer[byte.address] = (char) byte.next_value;
    else
        fprintf (stderr, "oh.. maybe this program already patched.. :(" "\n\n");

    return 0;
}

struct Byte_t GetByte (char** buffer_ptr)
{
    assert (buffer_ptr && "buffer_ptr is NULL in GetByte" "\n");

    struct Byte_t byte = {};

    *buffer_ptr = GetHex (&byte.address   , *buffer_ptr);
    *buffer_ptr = GetHex (&byte.curr_value, *buffer_ptr);
    *buffer_ptr = GetHex (&byte.next_value, *buffer_ptr);

    return byte;
}

char* GetHex (int* byte_param, char* buffer_ptr)
{
    assert (byte_param && "byte_param is NULL in GetHex" "\n");
    assert (buffer_ptr && "buffer_ptr is NULL in GetHex" "\n");

    char temp[8] = {};                                                  // 8 for stack protector
    size_t i = 0;

    while (true)
    {
        if (*buffer_ptr == '<')
        {
            buffer_ptr += 3;                                            // skip "<0x"

            i = 0;
            while (*buffer_ptr != '>')
            {
                temp[i] = *buffer_ptr;
                buffer_ptr++;
                i++;
            }

            break;
        }
        else
            buffer_ptr++;
    }

    fprintf (stderr, "i = %zu >>> byte.param = %s"   "\n", i, temp);

    char* end_p = NULL;
    *byte_param = (int) strtol (temp, &end_p, 16);

    fprintf (stderr, "i = %zu >>> byte.param = %d" "\n\n", i, *byte_param);

    return buffer_ptr;
}
