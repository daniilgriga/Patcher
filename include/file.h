#ifndef PATCHER_H
#define PATCHER_H

FILE* OpenFile (const char* filename, const char* mode);

long FileSize (FILE* file_ptr);

char* ReadInBuffer (FILE* file_ptr, const long numb_symb);

int CloseFile (FILE* file_ptr, const char* filename);

#endif // PATCHER_H
