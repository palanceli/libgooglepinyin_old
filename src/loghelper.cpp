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

#include "../include/loghelper.h"
#include "stdio.h"
#include <iostream>
#include <codecvt>
#include "glog/logging.h"


void LogLemma(ime_pinyin::LemmaEntry* pLemmaEntry, size_t lemmaNum){
  return;
  
  char szTitle[] ="idx_by_py idx_by_hz hanzi_str  hanzi_scis_ids    spl_idx_arr      \
  pinyin_str hz_str_len freq";
//  LOG(INFO)<<szTitle;
  printf("%s\n", szTitle);
  
  for(size_t i=0; i<lemmaNum; i++){
    char szLine[1024] = {0};
    int iPos = 0;
    int cMsg = 0;
    
    ime_pinyin::LemmaEntry *pLemma = pLemmaEntry + i;
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    std::string strHanzi =  convert.to_bytes((char16_t*)pLemma->hanzi_str);
    
    cMsg = sprintf(szLine + iPos, "%-9zu,%-9zu,%-10s, ", pLemma->idx_by_py, pLemma->idx_by_hz,
           strHanzi.c_str());
    iPos += cMsg;
    for(size_t j=0; j<ime_pinyin::kMaxLemmaSize; j++){
      cMsg = sprintf(szLine + iPos, "%u ", pLemma->hanzi_scis_ids[j]);
      iPos += cMsg;
    }
    cMsg = sprintf(szLine + iPos, ", ");
    iPos += cMsg;
    for(size_t j=0; j<ime_pinyin::kMaxLemmaSize + 1; j++){
      cMsg = sprintf(szLine + iPos, "%u ", pLemma->spl_idx_arr[j]);
      iPos += cMsg;
    }
    cMsg = sprintf(szLine + iPos, ", ");
    iPos += cMsg;
    for(size_t j=0; j<ime_pinyin::kMaxLemmaSize; j++){
      cMsg = sprintf(szLine + iPos, "%s ", pLemma->pinyin_str[j]);
      iPos += cMsg;
    }
    cMsg = sprintf(szLine + iPos, ", %-8u, %.2f\n", pLemma->hz_str_len, pLemma->freq);
    iPos += cMsg;
    printf("%s\n", szLine);
//    LOG(INFO)<<szLine;
  }
}

void LogRawSpellingList(const char* pSpellingBuff, size_t splItemSize, size_t splNum){
  return ;
  printf("idx    str    freq    %d\n", (unsigned char)splNum);
  for(size_t i=0; i<splNum; i++){
    char szLine[1024] = {0};
    int iPos = 0;
    int cMsg = 0;
    
    const char* pSpl = pSpellingBuff + i * splItemSize;
    cMsg = sprintf(szLine + iPos, "%3lu, %7s, %u", i, pSpl, (unsigned char)pSpl[7]);
    iPos += cMsg;
    printf("%s\n", szLine);
  }
}

int getSpellingTrieNodeCount(ime_pinyin::SpellingNode* root){
  int count = root->num_of_son;
  for(int i=0; i<root->num_of_son; i++){
    count += getSpellingTrieNodeCount(root->first_son + i);
  }
  return count;
}

void serializeSpellingNodeToBuff(ime_pinyin::SpellingNode* node,
                                 ime_pinyin::SpellingNode* serialNode,
                                 ime_pinyin::SpellingNode* &pFreeStart,
                                 ime_pinyin::SpellingNode* pFreeEnd){
  if(pFreeStart + node->num_of_son >= pFreeEnd){
    LOG(ERROR)<<"array address over bounds";
    exit(-1);
  }
  serialNode->first_son = pFreeStart;
  
  memcpy(pFreeStart, node->first_son, node->num_of_son * sizeof(ime_pinyin::SpellingNode));
  pFreeStart += node->num_of_son;
  
  for(int i=0; i<node->num_of_son; i++){
    serializeSpellingNodeToBuff(node->first_son + i,
                                serialNode->first_son + i,
                                pFreeStart, pFreeEnd);
  }
}

void walkThroughSpellingTrie(ime_pinyin::SpellingNode* root, ime_pinyin::SpellingNode* curr){
  char thisChar = ' ';
  if(curr->char_this_node != '\0'){
    thisChar = curr->char_this_node;
  }
  printf("%ld, %u, %u, %c, %u\n", curr->first_son - root, curr->spelling_idx,
         curr->num_of_son, thisChar, curr->score);
  for(int i=0; i<curr->num_of_son; i++){
    walkThroughSpellingTrie(root, curr->first_son + i);
  }
}

ime_pinyin::SpellingNode* serializeSpellingTrie(ime_pinyin::SpellingNode* root){
  int cNodes = getSpellingTrieNodeCount(root);
  cNodes *= 2;
  printf("spelling trie nodes count=%d\n", cNodes);
  
  ime_pinyin::SpellingNode* pNewRoot = (ime_pinyin::SpellingNode*)malloc(sizeof(ime_pinyin::SpellingNode) * cNodes);
  ime_pinyin::SpellingNode*pNewEnd = pNewRoot + cNodes;
  
  memcpy(pNewRoot, root, sizeof(ime_pinyin::SpellingNode));
  
  ime_pinyin::SpellingNode* pFree = pNewRoot + 1;
  serializeSpellingNodeToBuff(root, pNewRoot, pFree, pNewEnd);
  
  for(int i=0; i<cNodes; i++){
    ime_pinyin::SpellingNode* currNode = pNewRoot + i;
    if(currNode >= pFree){
      currNode->first_son = nullptr;
      break;
    }
  }
  return pNewRoot;
}

void LogSpellingTrie(ime_pinyin::SpellingNode* root, ime_pinyin::SpellingNode** level1Sons, size_t leve1Num){
  return;
  ime_pinyin::SpellingNode* newRoot = serializeSpellingTrie(root);
  
  char szTitle[] = "idx first_son   spelling_idx   num_of_son   char_this_node score";
  printf("%s\n", szTitle);

  int idx=0;
  for(ime_pinyin::SpellingNode* node=newRoot; node->first_son!=nullptr; node++){
    char thisChar = ' ';
    if(node->char_this_node != '\0'){
      thisChar = node->char_this_node;
    }
    char szFirstSon[8] = "-";
    if(node->num_of_son > 0){
      sprintf(szFirstSon, "%ld", node->first_son - newRoot);
    }
    char szLine[1024] = {0};
    sprintf(szLine, "%3d, %8s, %12u, %11u, %14c, %4u ", idx++, szFirstSon,
           node->spelling_idx, node->num_of_son,
           thisChar, node->score);
    if(idx > 1 && idx <= newRoot->num_of_son + 1){
      printf("%s level1_sons[%d]\n", szLine, idx-2);
    }else{
      printf("%s\n", szLine);
    }
  }
  
  free(newRoot);
}

void LogH2F(ime_pinyin::uint16 *h2fStart, ime_pinyin::uint16 *h2fNum, size_t cItems){
  return;
  printf("idx h2fstart  h2fnum\n");
  for(int i=0; i<cItems; i++){
    printf("%3d, %7d, %6d\n", i, h2fStart[i], h2fNum[i]);
  }
}

void LogF2H(ime_pinyin::uint16 *f2h, size_t cItems){
  return;
  printf("idx  f2h\n");
  for(int i=0; i<cItems; i++){
    printf("%3d, %3d\n", i, f2h[i]);
  }
}

void LogYmBuf(const char* pYmBuf, size_t ymItemSize, size_t ymNum){
  return;
  printf("idx    ym_buf_\n");
  for(size_t i=0; i<ymNum; i++){
    char szLine[1024] = {0};
    int iPos = 0;
    int cMsg = 0;
    
    const char* pSpl = pYmBuf + i * ymItemSize;
    cMsg = sprintf(szLine + iPos, "%3lu, %7s", i, pSpl);
    iPos += cMsg;
    printf("%s\n", szLine);
  }
}

void LogSplYmIds(ime_pinyin::uint8 *splYmIds, size_t cItems){
  printf("idx  spl_ym_ids_\n");
  for(size_t i=0; i<cItems; i++){
    printf("%3lu, %d\n", i, splYmIds[i]);
  }
}
