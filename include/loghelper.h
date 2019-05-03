/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PINYINIME_INCLUDE_LOGHELPER_H__
#define PINYINIME_INCLUDE_LOGHELPER_H__

#include "./dictdef.h"
#include "./spellingtable.h"
#include "./spellingtrie.h"

void LogLemma(ime_pinyin::LemmaEntry* pLemmaEntry, size_t lemmaNum);
void LogRawSpellingList(const char* pSpellingBuff, size_t splItemSize, size_t splNum);
void LogSpellingTrie(ime_pinyin::SpellingNode* root, ime_pinyin::SpellingNode** level1Sons, size_t leve1Num);
void LogH2F(ime_pinyin::uint16 *h2fStart, ime_pinyin::uint16 *h2fNum, size_t cItems);
void LogF2H(ime_pinyin::uint16 *f2h, size_t cItems);
void LogYmBuf(const char* pYmBuf, size_t ymItemSize, size_t ymNum);
void LogSplYmIds(ime_pinyin::uint8 *splYmIds, size_t cItems);
#endif
