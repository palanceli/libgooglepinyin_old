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
  class MatrixSearchTest : public testing::Test{
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
  
  TEST_F(MatrixSearchTest, TCInit){
    MatrixSearch* matrix_search = new MatrixSearch();
    bool ret = matrix_search->init(mSzDatFilePath, mSzUserDict);
    ASSERT_TRUE(ret)<<"Faile to init";
  }
  
  TEST_F(MatrixSearchTest, TCSearch){
    MatrixSearch* matrix_search = new MatrixSearch();
    bool ret = matrix_search->init(mSzDatFilePath, mSzUserDict);
    ASSERT_TRUE(ret)<<"Faile to init";
    
    matrix_search->set_max_lens(32, 16);
    matrix_search->reset_search();
    const char *szInput = "a";
    matrix_search->search(szInput, strlen(szInput));
  }
}
