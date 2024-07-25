// 带权并查集

auto find = [&](auto && find, int x) -> int {		
	if (x==fa[x]) return x;
	int root = find(find, fa[x]);		
	sum[x] = sum[x] + sum[fa[x]]; // sum 表示到父亲节点的间隔
	fa[x] = root;
	return root;
};

auto merge = [&](int u, int v) {		
	// u is v's father
	int root_u = find(find, u);
	// int root_v = find(find, v);
	sum[v] = sum[u] + 1;
	// v must be root
	fa[v] = root_u;
};

// -------------------------

// 维护和的关系 
// 给定多个 a-b=c的关系

#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

#define MAXN 200005
int fa[MAXN];
long long sum[MAXN];

int find(int x) {
    if(x==fa[x]) return x;
    int temp = find(fa[x]);
    sum[x] = sum[fa[x]] + sum[x];
    fa[x] = temp;
}

int N,M; 
inline void solve() {
    
    for(int i=0;i<=N;++i) fa[i] = i,sum[i] = 0;

    int res = 0;

    for(int i=1;i<=M;++i) {
        int u,v; long long c; cin >> u >> v >> c; --u;
        int fu = find(u),fv = find(v);
        if(fu==fv) res += ((sum[v]-sum[u])==c?0:1);
        else {
            fa[fv] = fu; sum[fv] = c + sum[u] - sum[v];
        }
    }

    cout << res << "\n";
}
int main() {

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(cin >> N >> M) solve();
    return 0;
}