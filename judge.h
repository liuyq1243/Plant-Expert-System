#pragma once
//
// Created by 27801 on 2022/11/27.
//

#ifndef PLANT_JUDGE_H
#define PLANT_JUDGE_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

const int N = 100000;
const int S = 3;

class Node {
public:
    int id;

    unordered_set<int> son;
    unordered_set<int> pre;

    Node(){}
};

/* 逆向推理返回结果类型 */
class ResFeature{
public:
    /* 选错的特征 */
    vector<int> fail;
    /* 少选的特征 */
    vector<int> lack;
    /* 正确的参考答案 */
    vector<int> answer;

    ResFeature(){}
    ResFeature(vector<int> a, vector<int> b, vector<int> c): fail(a), lack(b), answer(c){}
};

/* 规则类 */
class Rule{
public:
    /* 规则的条件，if */
    unordered_set<int> condition;
    /* 规则的结果 then */
    int res;

    Rule(unordered_set<int> a, int b):condition(a), res(b){}
};


extern vector<Rule> rules;
void init_id();
void add_edge(vector<int> from, int to);
void init_tree();
void func(vector<int> parm,int target,ResFeature &res_feature);
void func2(vector<int> &workMemory, int target);

vector<int> judge(vector<int> in);

#endif //PLANT_JUDGE_H
