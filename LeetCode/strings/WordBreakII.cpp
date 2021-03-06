//
//  WordBreakII .cpp
//  LeetCode
//
//  Created by WangJZ on 3/6/14.
//  Copyright (c) 2014 WangJZ. All rights reserved.
//  http://oj.leetcode.com/problems/word-break-ii/

/*也可以采用dp方式，具体参见http://zhaohongze.com/wordpress/2013/12/10/leetcode-word-break-ii/*/

/*
 基本上是在word break 1 上面改的，这里面用到的技巧是设置一个变量successOnce，来看该位置上是否成功过，如果成功过，说明该位置是能够找到的
 但是这种广度优先遍历的算法是不是比深度优先遍历运算次数更多一点？
 */

#include "leetcode_string.h"

bool wordBreakHelper(string &s,
                     unordered_set<string> &dict,
                     int position,
                     int max,
                     int min,
                     vector<bool> &isVisited,
                     vector<vector<string>> &retVec,
                     vector<string> &tmp)
{
    //没到一个新的位置,从最大的能匹配到的，使用backtracking技术
    //记录第x个位置开始是否可以匹配到
    if (position == (int)s.length()) {
        retVec.push_back(tmp);
        return true;
    }
    if (position+min >(int)s.length()) {
        return false;
    }
    if (isVisited[position]) {
        return false;
    }
    if (max > (int)s.length() - position) {
        max = (int)s.length() - position;
    }
    bool successOnce = false;
    for (int i = max; i >=min ;i-- ) {
        string curWord =  s.substr(position,i);//从第position个位置开始，取长度是i的字串
        unordered_set<string>::const_iterator got = dict.find(curWord);
        if (got != dict.end()) {//找到了！
            tmp.push_back(curWord);
            if(!wordBreakHelper(s, dict, position+i, max, min, isVisited,retVec,tmp)) {
                isVisited[position+i] = true;//该位置不能成功
            }else{
                successOnce = true;
            }
            tmp.pop_back();
        }
    }
    if (successOnce) {
        return true;
    }else{
        return false;
    }
}
vector<string> wordBreak2(string s, unordered_set<string> &dict){
    int max = 0;
    int min = (int)s.length();
    int cur_long;
    
    //找到字典中最大的单词数和最小的单词数
    for ( auto it = dict.begin(); it != dict.end(); ++it ){
        cur_long = (int)(*it).size();
        if (cur_long > max) {
            max = cur_long;
        }
        if (cur_long < min) {
            min = cur_long;
        }
    }
    vector<bool>isVisited = vector<bool>(s.length(),false);
    vector<vector<string>> retVec;
    vector<string>tmp;
    wordBreakHelper(s, dict, 0,max,min,isVisited,retVec,tmp);
    
    vector<string> result;
    
    for (int i = 0; i <int(retVec.size()); i++) {
        string tmpString;
        tmp = retVec[i];
        for (int j = 0; j < int(tmp.size()); j++) {
            if (j == 0) {
                tmpString += tmp[j];
            }else{
                tmpString += " " + tmp[j];
            }
        }
        result.push_back(tmpString);
    }
//    for (int i = 0; i < (int)result.size(); i++) {
//        cout << result[i] <<endl;
//    }
    return result;
}

void testWordBreak2(){
    string s = "leetcode";
    unordered_set<string> dict = {"leet","code","le","et"};
    wordBreak2(s, dict);
    printf("Finished\n");
}
