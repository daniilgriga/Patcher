#ifndef PATCH_H
#define PATCH_H

int Patch (char* buffer, const char* rules_filename);

struct Byte_t GetByte (char* buffer);

char* GetHex (int* byte_param, char* buffer_ptr);

#endif // PATCH_H
