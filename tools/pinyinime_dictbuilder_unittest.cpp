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

#include <stdlib.h>
#include <stdio.h>
#include "pinyinime.h"
#include <cassert>
#include <memory.h>

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif

#include <locale.h>
#include <iostream>
#include <codecvt>

#include <gtest/gtest.h>
#include "glog/logging.h"
#include "../include/dicttrie.h"
#include "../include/matrixsearch.h"
#include <unistd.h>

using namespace ime_pinyin;

namespace googlepinyin_test{
  class PinyinImeDictBuilderTest : public testing::Test{
  protected:
    const char *mSzRawDictPath = "../../data/rawdict_utf16_65105_freq.txt";
    const char *mSzValidUtfPath = "../../data/valid_utf16.txt";
    const char *mSzDatFilePath = "../data/dict_pinyin.dat";
    char const *mSzUserDict = "";
    
  protected:
    static void SetUpTestCase(){
      setlocale(LC_ALL, "");
    }
    static void TearDownTestCase(){
      
    }
  };
  
  TEST_F(PinyinImeDictBuilderTest, TCGetcwd){
    char* szDir;
    if((szDir = (char*)getcwd(NULL, 0)) == NULL){
      printf("Failed to get cwd\n");
      return;
    }
    LOG(INFO)<<"cwd: "<< szDir;
  }

  TEST_F(PinyinImeDictBuilderTest, TCBuildDict){
    DictTrie* dict_trie = new DictTrie();
    bool success;
    
    success = dict_trie->build_dict(mSzRawDictPath, mSzValidUtfPath);
    ASSERT_EQ(success, true) << "Failed to build dict!";
    
    success = dict_trie->save_dict(mSzDatFilePath);
    ASSERT_EQ(success, true) << "Failed to save dict!";
  }
}
