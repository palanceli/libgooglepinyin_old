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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//#*#*#include <unistd.h>
//#*#*{{
#ifdef WIN32
#   include <windows.h>
#   include <io.h>  
#   include <process.h>  
#else
#   include <sys/time.h>
#   include <unistd.h>
#endif
//#*#*}}
#include "../include/dicttrie.h"
#include "glog/logging.h"

#include <locale.h>


using namespace ime_pinyin;

/**
 * Build binary dictionary model. Make sure that ___BUILD_MODEL___ is defined
 * in dictdef.h.
 */
int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "");
  FLAGS_log_dir = "/Users/palance/Desktop/log";
  google::InitGoogleLogging(argv[0]);
  google::SetLogDestination(google::GLOG_INFO, "/Users/palance/Desktop/log/lblog");
  google::SetLogFilenameExtension(".lblog");
  LOG(INFO)<<"test";
  
  DictTrie* dict_trie = new DictTrie();
  bool success;
  
  char buffer[1024] = {0};
  char *cwd = getwd(buffer);
  
  if (argc >= 3)
     success = dict_trie->build_dict(argv[1], argv[2]);
  else
     success = dict_trie->build_dict("../../../data/rawdict_utf16_65105_freq.txt",
                                     "../../../data/valid_utf16.txt");

  if (success) {
    printf("Build dictionary successfully.\n");
  } else {
    printf("Build dictionary unsuccessfully.\n");
    return -1;
  }

  if (argc >= 4)
	success = dict_trie->save_dict(argv[3]);
  else
	success = dict_trie->save_dict("../../data/dict_pinyin.dat");

  if (success) {
    printf("Save dictionary successfully.\n");
  } else {
    printf("Save dictionary unsuccessfully.\n");
    return -1;
  }

  google::ShutdownGoogleLogging();
  return 0;
}
