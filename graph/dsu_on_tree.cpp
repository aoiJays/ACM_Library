//  n个节点有根树，每个节点有自己的颜色
// 查询任一子树里一共出现了多少种不同的颜色

#include <bits/stdc++.h>
using namespace std;

#define MAXN 200005

/*
    计算种类数
*/
int col[MAXN];
int cnt[MAXN], tot = 0;
void update(int u, int c) {
    int x = col[u]; cnt[x] += c;
    if ( cnt[x] == 0 && c == -1 ) --tot;
    else if ( cnt[x] == 1 && c == 1 ) ++ tot;
}


vector<int > G[MAXN]; 
int L[MAXN], R[MAXN]; // 子树dfs序范围
int cur[MAXN]; // dfs->u
int dfntot = 0;

// 重儿子 子树大小
int son[MAXN], sz[MAXN];
int ans[MAXN];

void dfs1(int u, int fa) {
    L[u] = ++dfntot; cur[dfntot] = u;
    sz[u] = 1;
    for (auto v: G[u]) {
        if (v==fa) continue;
        dfs1(v, u);
        if ( !son[u] || sz[v] > sz[son[u]] ) son[u] = v;
        sz[u] += sz[v];
    }
    R[u] = dfntot;
}

void dfs2(int u, int fa, bool record) {

    // 计算轻儿子答案
    for (auto v : G[u]) {
        if ( v==fa || v==son[u] ) continue;
        dfs2(v, u, false); 
    }

    // 计算重儿子答案
    if (son[u]) dfs2(son[u], u, true);

    // 计算自己答案
    for (auto v: G[u]) {
        if (v==fa || v==son[u]) continue;
        for (int i=L[v];i<=R[v];++i) update(cur[i], 1);
    }

    update(u, 1);
    ans[u] = tot;

    // 撤销整棵子树
    if (!record)
        for (int i=L[u];i<=R[u];++i) update(cur[i], -1);
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    for (int i=1;i<n;++i) {
        int u, v; cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    for (int i=1;i<=n;++i) cin >> col[i];

    dfs1(1, 0);
    dfs2(1, 0, true);

    int Q; cin >> Q;
    for (int i=1;i<=Q;++i) {
        int u; cin >> u;
        cout << ans[u] << "\n";
    }
    return 0;
}