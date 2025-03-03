#ifndef PATCH_H
#define PATCH_H

int Patch (char* buffer, const char* rules_filename);

int ReplaceByte (char* buffer, char** ptr_rules);

struct Byte_t GetByte (char** buffer);

char* GetHex (int* byte_param, char* buffer_ptr);

#endif // PATCH_H
