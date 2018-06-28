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
#include <unistd.h>

using namespace ime_pinyin;

namespace googlepinyin_test{
  class PinyinImeTest : public testing::Test{
  protected:
    const char* mSzRawDictPath = "../../data/rawdict_utf16_65105_freq.txt";
    const char* mSzValidUtfPath = "../../data/valid_utf16.txt";
    const char* mSzDatFilePath = "../data/dict_pinyin.dat";
    
  protected:
    static void SetUpTestCase(){
    }
    static void TearDownTestCase(){
      
    }
  };
  
  TEST_F(PinyinImeTest, TCGetcwd){
    char* szDir;
    if((szDir = (char*)getcwd(NULL, 0)) == NULL){
      printf("Failed to get cwd\n");
      return;
    }
    LOG(INFO)<<"cwd: "<< szDir;
  }
  
  TEST_F(PinyinImeTest, TCBuildDict){
    setlocale(LC_ALL, "");
    DictTrie* dict_trie = new DictTrie();
    bool success;
    
    success = dict_trie->build_dict(mSzRawDictPath, mSzValidUtfPath);
    ASSERT_EQ(success, true) << "Failed to build dict!";
    
    success = dict_trie->save_dict(mSzDatFilePath);
    ASSERT_EQ(success, true) << "Failed to save dict!";
  }
  
  TEST_F(PinyinImeTest, TC2){
    setlocale(LC_ALL, "");
    char const *szUserDict = "";
    
    bool ret = im_open_decoder(mSzDatFilePath, szUserDict);  // 加载
    ASSERT_EQ(ret, true) << "Failed to load dict!";
    
    im_set_max_lens(32, 16);
    char szLine[256] = "a";
    
    im_reset_search();
    size_t nr = im_search(szLine, strlen(szLine)); // 查询
    size_t size = 0;
    LOG(INFO)<<"输入串："<<im_get_sps_str(&size)<<"\n候选串：";  // 返回拼音串
    char16 str[64] = { 0 };
    for (auto i = 0; i < nr; i++)
    {
      im_get_candidate(i, str, 32);         // 获取查询候选
      if(i > 5)
        break;

      std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
      std::string strCand = convert.to_bytes((char16_t*)str);
      LOG(INFO)<< i << "." << strCand << "";
    }
    if(nr>5)
      LOG(INFO)<<"...";
    LOG(INFO)<<" 共"<< nr << "个候选\n";
    
    im_close_decoder();                 // 关闭
    
  }
}
