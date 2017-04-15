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
#include <Windows.h>
#include <tchar.h>

using namespace ime_pinyin;

int main(int argc, char* argv[])
{
  char* szSysDict = "../build/data/dict_pinyin.dat";
  char* szUserDict = "";
  if (argc >= 3) {
    szSysDict = argv[1];
    szUserDict = argv[2];
  }

  bool ret = im_open_decoder(szSysDict, szUserDict);
  assert(ret);

  im_set_max_lens(32, 16);
  im_reset_search();
  size_t nr = im_search("xian'guo", 8);
  size_t size = 0;
  printf("%s", im_get_sps_str(&size));
  char16 str[64] = { 0 };
  for (auto i = 0; i < nr; i++)
  {
    im_get_candidate(i, str, 32);
    const wchar_t* szCand = (const wchar_t*)str;
    wprintf(szCand);
    int j = 0;
    j++;
  }

  im_close_decoder();

	return 0;
}