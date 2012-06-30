#ifndef FILE_H
#define FILE_H

namespace File
{
    bool Load(const char* fileName, char*& buffer, int& size);
    bool Save(const char* fileName, const char* buffer, int size);
    bool Append(const char* fileName, const char* buffer, int size);
}

#endif // FILE_H
