/*
 * Copyright (c) 2013 OSW. All rights reserved.
 * Copyright (c) 2008-2011 the MansOS team. All rights reserved.
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
 *
 * fs/block/meta.h -- control structures and root directory
 */

#ifndef _FS_BLOCK_META_H_
#define _FS_BLOCK_META_H_

#include <stdbool.h>
#include <stdint.h>

#include <defines.h>

#include "common.h"

/* Size of header data in EEPROM */
#define FS_HEADER_SIZE sizeof(uint16_t)

struct fsFileControlBlock *fsBlockOpenFile(const char *name, bool write);
void fsBlockCloseFile(struct fsFileControlBlock *file);

/* Should be called with the mutex locked */
void fsBlockSyncEntry(struct fsFileControlBlock *file);

bool fsBlockStat(const char * restrict path, struct fsStat * restrict buf);
bool fsBlockRemove(const char *path);
bool fsBlockRename(const char *old, const char *new);

#endif /* _FS_BLOCK_META_H_ */
