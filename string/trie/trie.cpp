#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define INF ((ll)1e17)

struct Trie {
    
    #define SIZE 26 + 26 + 10
    
    int toNum(char ch) {
        if ( ch >= '0' && ch <= '9' ) return ch - '0';
        if ( ch >= 'a' && ch <= 'z' ) return ch - 'a' + 10;
        return ch - 'A' + 10 + 26;
    }

    struct Node {
        int next[SIZE], cnt;
        Node() {
            for (int i=0;i<SIZE;++i) next[i] = 0;
            cnt = 0;
        }
    };

    vector<Node> trie;
    Trie() {
        trie.emplace_back( Node() );
    }

    // insert(char *s, int l)
    void insert(const string & s) {  // 插入字符串
        int p = 0;
        for (auto ch : s) {
            if (!trie[p].next[toNum(ch)]) { // 如果没有，就添加结点
                trie[p].next[toNum(ch)] = trie.size();
                trie.emplace_back( Node() );
            }    
            p = trie[p].next[toNum(ch)];
        }
        ++ trie[p].cnt;
    }

    int find(const string & s) {  // 查找字符串
        int p = 0;
        for (auto ch : s) {
            if (!trie[p].next[toNum(ch)]) return 0;
            p = trie[p].next[toNum(ch)];
        }
        return trie[p].cnt;
    }
};