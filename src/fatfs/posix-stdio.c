/*
 * Copyright (c) 2013 OSW. All rights reserved.
 * Copyright (c) 2012-2013 the MansOS team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of  conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <defines.h>

#if OSW_STDIO

#include "fatfs.h"
#include "posix-stdio.h"
#include <errors.h>
#include <lib/dprint.h>

// flush a file
int fflush(FILE *fp)
{
#if USE_FATFS && USE_SDCARD
    fatFsFileFlush(fp);
#endif
    return 0;
}

// open a file
FILE *fopenEx(const char *restrict filename,
              const char *restrict modes,
              FILE *restrict result)
{
#if USE_FATFS && USE_SDCARD
    // user must provide his own buffer for the file
    if (!result || result->isOpened) return NULL;

    result->flags = 0;
    while (*modes) {
        switch (*modes) {
        case 'r':
            result->flags |= O_RDONLY;
            break;
        case 'w':
            result->flags |= O_WRONLY | O_TRUNC | O_CREAT;
            break;
        case 'a':
            result->flags |= O_WRONLY | O_CREAT | O_APPEND;
            break;
        case '+':
            result->flags &= ~(O_WRONLY | O_RDONLY);
            result->flags |= O_RDWR;
            break;
        case 't':
        case 'b':
            break;
        }
        modes++;
    }

    // open it on file system
    DirectoryEntry_t *de = fatFsFileSearch(filename, &result->directoryEntry);
    if (de == NULL) {
        if (result->flags & O_CREAT) {
            de = fatFsFileCreate(filename, &result->directoryEntry);
        }
    }

    if (de == NULL) {
        return NULL;
    }

#if FAT32_SUPPORT
    result->firstCluster = de->startClusterHiword;
    result->firstCluster <<= 16;
#else
    result->firstCluster = 0;
#endif
    result->firstCluster |= de->startClusterLoword;
    result->currentCluster = result->firstCluster;
    result->position = 0;
    if (result->flags & O_TRUNC) {
        // resize the file to zero
        result->fileSize = 0;
        if (de->fileSize != 0) {
            // write the new size to disk
            result->dirEntryDirty = true;
            fatFsFileFlush(result);
        }
    } else {
        result->dirEntryDirty = false;
        result->fileSize = de->fileSize;
    }
    // PRINTF("file opened, size=%lu\n", result->fileSize);
    result->isOpened = true;

    // TODO: truncate if needed

    return result;
#else
    return NULL;
#endif
}

// close a file
int fclose(FILE *fp)
{
#if USE_FATFS && USE_SDCARD
    // close it on the file system
    fatFsFileClose(fp);
#endif

    fp->isOpened = false;

    return 0;
}

char *fgets(char *restrict s, int size, FILE *restrict fp)
{
    uint16_t i;
    if (size == 0) return s;
    for (i = 0; i < size - 1; ++i) {
        uint8_t b = 0;
        fread(&b, 1, 1, fp);
        if (b == EOF) {
            if (i == 0) return NULL;
            break;
        }
        s[i] = b;
        if (b == '\n') break;
    }
    i++;
    s[i] = '\0';
    return s;
}

// delete a file
int remove(const char *filename)
{
#if USE_FATFS && USE_SDCARD
    fatFsFileRemove(filename);
#endif
    return 0;
}

// go to a specific position in the file
int fseek(FILE *fp, long offset, int whence)
{
    uint32_t newPos;
    switch (whence) {
    case SEEK_SET:
        newPos = 0;
        break;
    case SEEK_CUR:
        newPos = fp->position;
        break;
    case SEEK_END:
    default:
        newPos = fp->fileSize;
        break;
    }
    if (offset < 0 && newPos < -offset) {
        // wants before the start of the file
        return -1;
    }
    if (offset > 0 && newPos + offset > fp->fileSize) {
        // wants after the end of the file
        return -1;
    }
    // fine; do it!
    newPos += offset;
#if USE_FATFS && USE_SDCARD
    fatfsGoToPosition(fp, newPos);
#endif
    return 0;
}

#endif // OSW_STDIO
