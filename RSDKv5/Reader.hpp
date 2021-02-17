#ifndef READER_H
#define READER_H

#if RETRO_USING_SDL1 || RETRO_USING_SDL2
#define FileIO                                          SDL_RWops
#define fOpen(path, mode)                               SDL_RWFromFile(path, mode)
#define fRead(buffer, elementSize, elementCount, file)  SDL_RWread(file, buffer, elementSize, elementCount)
#define fSeek(file, offset, whence)                     SDL_RWseek(file, offset, whence)
#define fTell(file)                                     SDL_RWtell(file)
#define fClose(file)                                    SDL_RWclose(file)
#define fWrite(buffer, elementSize, elementCount, file) SDL_RWwrite(file, buffer, elementSize, elementCount)
#else
#define FileIO                                          FILE
#define fOpen(path, mode)                               fopen(path, mode)
#define fRead(buffer, elementSize, elementCount, file)  fread(buffer, elementSize, elementCount, file)
#define fSeek(file, offset, whence)                     fseek(file, offset, whence)
#define fTell(file)                                     ftell(file)
#define fClose(file)                                    fclose(file)
#define fWrite(buffer, elementSize, elementCount, file) fwrite(buffer, elementSize, elementCount, file)
#endif

#include <zlib/zlib.h>

enum Scopes {
    SCOPE_NONE,
    SCOPE_GLOBAL,
    SCOPE_STAGE,
};

struct FileInfo {
    int fileSize;
    int externalFile;
    FileIO *file;
    byte* fileData;
    int readPos;
    int fileOffset;
    byte usingFileBuffer;
    byte encrypted;
    byte eNybbleSwap;
    byte encryptionKeyA[0x10];
    byte encryptionKeyB[0x10];
    byte eKeyPosA;
    byte eKeyPosB;
    byte eKeyNo;
};

struct RSDKFileInfo {
    uint hash[0x4];
    int offset;
    int filesize;
    bool32 encrypted;
    int fileID;
};

struct RSDKContainer {
    RSDKFileInfo files[0x1000];
    int fileCount;
};

extern RSDKContainer rsdkContainer;
extern char rsdkName[0x400];

extern bool32 useDataFile;

bool32 CheckDataFile(const char *filename);
bool32 OpenDataFile(FileInfo *info, const char *filename);

inline bool32 LoadFile(FileInfo *info, const char *filename)
{
    char filePath[0x400];

    if (info->file)
        return 0;
    if (info->externalFile || !useDataFile) {
        info->file = fOpen(filename, "rb");
        if (!info->file)
            return 0;
        info->readPos = 0;
        info->fileSize = 0;
        fSeek(info->file, 0, SEEK_END);
        info->fileSize = fTell(info->file);
        fSeek(info->file, 0, SEEK_SET);
        return info->file != NULL;
    }
    else {
        return OpenDataFile(info, filename);
    }
}

inline void CloseFile(FileInfo *info)
{
    if (!info->usingFileBuffer) {
        if (info->file)
            fClose(info->file);
    }
    info->file = NULL;
}

void GenerateELoadKeys(FileInfo *info, const char *key1, int key2);
void DecryptBytes(FileInfo *info, void *buffer, int size);
void SkipBytes(FileInfo *info, int size);

inline void Seek_Set(FileInfo* info, int count) {
    if (info->readPos != count) {
        info->readPos = count;
        if (info->encrypted) {
            info->eKeyNo      = (info->fileSize / 4) & 0x7F;
            info->eKeyPosA    = 0;
            info->eKeyPosB    = 8;
            info->eNybbleSwap = false;
            SkipBytes(info, count);
        }

        if (info->usingFileBuffer) {
            info->fileData = (byte *)info->file + info->readPos;
        }
        else {
            fSeek(info->file, info->readPos + info->fileOffset, SEEK_SET);
        }
    }
}

inline void Seek_Cur(FileInfo *info, int count)
{
    if (info->readPos != count) {
        info->readPos += count;
        if (info->encrypted) {
            SkipBytes(info, count);
        }

        if (info->usingFileBuffer) {
            info->fileData += count;
        }
        else {
            fSeek(info->file, count, SEEK_CUR);
        }
    }
}

inline void ReadBytes(FileInfo *info, void* data, int count)
{
    int bytesRead = 0;
    if (info->usingFileBuffer) {
        bytesRead = count;
        memcpy(data, info->fileData, count);
        info->fileData += count;
    }
    else {
        bytesRead = fRead(data, 1, count, info->file);
    }
    if (info->encrypted)
        DecryptBytes(info, data, bytesRead);
    info->readPos += bytesRead;
}

inline byte ReadInt8(FileInfo *info)
{
    byte result = 0;
    int bytesRead = 0;
    if (info->usingFileBuffer) {
        bytesRead          = 1;
        result             = *info->fileData;
        info->fileData++;
    }
    else {
        bytesRead = fRead(&result, 1, 1, info->file);
    }
    if (info->encrypted)
        DecryptBytes(info, &result, bytesRead);
    info->readPos += bytesRead;
    return result;
}

inline short ReadInt16(FileInfo *info)
{
    short result  = 0;
    int bytesRead = 0;
    if (info->usingFileBuffer) {
        bytesRead = 2;
        result    = *info->fileData;
        info->fileData++;
    }
    else {
        bytesRead = fRead(&result, 1, 2, info->file);
    }
    if (info->encrypted)
        DecryptBytes(info, &result, bytesRead);
    info->readPos += bytesRead;
    return result;
}

inline int ReadInt32(FileInfo *info)
{
    int result   = 0;
    int bytesRead = 0;
    if (info->usingFileBuffer) {
        bytesRead = 4;
        result    = *info->fileData;
        info->fileData++;
    }
    else {
        bytesRead = fRead(&result, 1, 4, info->file);
    }
    if (info->encrypted)
        DecryptBytes(info, &result, bytesRead);
    info->readPos += bytesRead;
    return result;
}
inline int64 ReadInt64(FileInfo *info)
{
    int64 result  = 0;
    int bytesRead = 0;
    if (info->usingFileBuffer) {
        bytesRead = 8;
        result    = *info->fileData;
        info->fileData++;
    }
    else {
        bytesRead = fRead(&result, 1, 8, info->file);
    }
    if (info->encrypted)
        DecryptBytes(info, &result, bytesRead);
    info->readPos += bytesRead;
    return result;
}

inline int ReadSingle(FileInfo *info)
{
    float result    = 0;
    int bytesRead = 0;
    if (info->usingFileBuffer) {
        bytesRead = 4;
        result    = *info->fileData;
        info->fileData++;
    }
    else {
        bytesRead = fRead(&result, 1, 4, info->file);
    }
    if (info->encrypted)
        DecryptBytes(info, &result, bytesRead);
    info->readPos += bytesRead;
    return result;
}

inline void ReadString(FileInfo *info, char* buffer) { 
    byte size = ReadInt8(info);
    ReadBytes(info, buffer, size);
    buffer[size] = 0;
}

inline int ReadZLibRSDK(FileInfo *info, byte **buffer)
{
    if (!buffer)
        return 0;
    uint complen      = ReadInt32(info) - 4;
    uint decompLE     = ReadInt32(info);
    uint destLen      = (uint)((decompLE << 24) | ((decompLE << 8) & 0x00FF0000) | ((decompLE >> 8) & 0x0000FF00) | (decompLE >> 24));

    byte *compData = NULL;
    AllocateStorage(complen, (void**)&compData, DATASET_TMP, false);
    AllocateStorage(destLen, (void **)buffer, DATASET_TMP, false);
    ReadBytes(info, compData, complen);

    uncompress(*buffer, (uLongf *)&destLen, compData, complen);
    compData = NULL;
    return destLen;
}

inline int ReadZLib(FileInfo *info, byte **buffer, int cSize, int size)
{
    if (!buffer)
        return 0;
    uint complen  = cSize;
    uint decompLE = size;
    uint destLen  = (uint)((decompLE << 24) | ((decompLE << 8) & 0x00FF0000) | ((decompLE >> 8) & 0x0000FF00) | (decompLE >> 24));

    byte *compData = NULL;
    AllocateStorage(complen, (void **)&compData, DATASET_TMP, false);
    ReadBytes(info, compData, complen);

    uncompress(*buffer, (uLongf *)&destLen, compData, complen);
    compData = NULL;
    return destLen;
}

inline void ReadHash(FileInfo *info, uint *buffer)
{
    buffer[0] = ReadInt32(info);
    buffer[1] = ReadInt32(info);
    buffer[2] = ReadInt32(info);
    buffer[3] = ReadInt32(info);
}

#endif