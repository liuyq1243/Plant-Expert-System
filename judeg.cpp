#include "judge.h"

using namespace std;

Node node[N];

void init_id() {
    for (int i = 0; i < N; i++) {
        node[i].id = i;
    }
}
void add_edge(vector<int> from, int to) {
    for (int & it : from) {
        node[it].son.insert(to);
        node[to].pre.insert(it);
    }
}

void init_tree() {
    init_id();

    add_edge({10}, 18);
    add_edge({11}, 19);
    add_edge({12, 13}, 20);
    add_edge({18, 14}, 21);
    add_edge({18, 15}, 22);
    add_edge({18, 16}, 22);
    add_edge({18, 17}, 23);
    add_edge({18, 0, 21}, 24);
    add_edge({18, 1, 5, 8}, 25);
    add_edge({18, 0, 2, 23}, 26);
    add_edge({20, 1, 3, 20}, 27);
    add_edge({18, 4, 5, 8, 21}, 28);
    add_edge({18, 5, 8, 9, 22}, 29);
    add_edge({20, 1, 5, 6, 20}, 30);
    add_edge({19, 4, 7, 8, 19}, 31);
}

vector<int> judge(vector<int> in) {
    vector<int> out;
    unordered_set<int> ans;

    int t[N];
    for (int i = 0; i < N; i++) {
        t[i] = node[i].pre.size();
    }

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    for (int & it : in) {
        pq.push(make_pair(0, it));

        t[it] = 0;

        for (int i : node[it].son) {
            t[i]--;
        }
    }

    while (ans.size() < S && !pq.empty()) {
        pair<int, int> now = pq.top();
        pq.pop();

        //cout << now.second << " ";
        //cout << now.second << ":" << t[now.second] << endl;

        for (int it : node[now.second].son) {
            t[it]--;
            pq.push(make_pair(now.first + t[it], it));
        }

        if (!node[now.second].son.size()) {
            //cout << " *" << now.second << "* ";
            if (ans.find(now.second) == ans.end()) {
                ans.insert(now.second);
                out.emplace_back(now.second);
            }
        }
    }

    return out;
}

vector<Rule> rules;

void initRules(){
    rules.emplace_back(Rule({10}, 18));
    rules.push_back(Rule({11}, 19));
    rules.push_back(Rule({12, 13}, 20));
    rules.push_back(Rule({18, 14}, 21));
    rules.push_back(Rule({18, 15}, 22));
    rules.push_back(Rule({18, 16}, 22));
    rules.push_back(Rule({18, 17}, 23));
    rules.push_back(Rule({18, 0, 21}, 24));
    rules.push_back(Rule({18, 1, 5, 8}, 25));
    rules.push_back(Rule({18, 0, 2, 23}, 26));
    rules.push_back(Rule({20, 1, 3}, 27));
    rules.push_back(Rule({18, 4, 5, 8, 21}, 28));
    rules.push_back(Rule({18, 5, 8, 9, 22}, 29));
    rules.push_back(Rule({20, 1, 5, 6}, 30));
    rules.push_back(Rule({19, 4, 7, 8}, 31));

    return;
}

/* 找出某个后件的所有前件（条件） */
void func2(vector<int> &workMemory, int target){
    for(int i=0; i<rules.size(); ++i){
        if(target==rules[i].res){
            for (auto iter = rules[i].condition.begin(); iter != rules[i].condition.end(); ++iter) {
                cout << *iter << endl;
                workMemory.push_back(*iter);
            }
        }
    }
}

void func(vector<int> parm,int target,ResFeature &res_feature){
    initRules();

    /* 存储此时的工作栈 */
    vector<int> workMemory;
    /* 存储此时的工作内存 */
    vector<int> res;
    /* 用于判断工作内存中是否已经有此规则 */
    int state = 0;
    /* 找出所有匹配规则 */
    for(int i=0; i<rules.size(); ++i){
        /* 找到后件对应的规则 */
        if(target==rules[i].res){
            for (auto iter = rules[i].condition.begin(); iter != rules[i].condition.end(); ++iter) {
                workMemory.push_back(*iter);
            }
            while(!workMemory.empty()){
                int new_target = workMemory.back();
                workMemory.pop_back();
                /* 判断工作内存中是否已经有此规则 */
                for(int j=0; j<res.size(); ++j){
                    if(res[j]==new_target){
                        state = 1;
                        break;
                    }
                }
                if(state){
                    state = 0;
                    continue;
                }
                res.push_back(new_target);
                func2(workMemory,new_target);
            }
        }
    }

    /* 返回的逆向推理结果 */
    /* 将参考答案放入返回值 */
    res_feature.answer.assign(res.begin(), res.end());
    /* 找出错误的特征选项 */
    for(int i=0; i<parm.size(); ++i){
        int j;
        for(j=0; j<res.size(); ++j){
            if(parm[i]==res[j]){
                break;
            }
        }
        if(j==res.size()){
            res_feature.fail.push_back(parm[i]);
        }
    }
    /* 找出漏选的特征选项 */
    for(int i=0; i<res.size(); ++i){
        int j;
        for(j=0; j<parm.size(); ++j){
            if(parm[j]==res[i]){
                break;
            }
        }
        if(j==parm.size()){
            res_feature.lack.push_back(res[i]);
        }
    }

    return ;
}
