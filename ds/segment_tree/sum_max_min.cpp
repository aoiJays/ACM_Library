#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 区间加法 最大值 最小值 和
struct SegmentTree {

    #define MAXN 500005
    
    ll seg[MAXN<<2], add[MAXN<<2];
    ll Max[MAXN<<2], Min[MAXN<<2];

    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    #define INF ((long long)1e17)
    
    void pushup(int rt) {
        seg[rt] = seg[lson] + seg[rson];
        Max[rt] = max(Max[lson], Max[rson]);
        Min[rt] = min(Min[lson], Min[rson]);
    }

    void build(int rt, int l, int r) {
        Min[rt] = Max[rt] = seg[rt] = add[rt] = 0;
        if ( l==r ) return;
        int mid = (l + r) >> 1;
        build(lson, l, mid); build(rson, mid + 1, r);
        pushup(rt);
    }

    void pushdown(int rt, int l, int r) {
        int mid = l + r >> 1, sizel = mid - l + 1, sizer = r - mid;
        seg[lson] += add[rt] * sizel; seg[rson] += add[rt] * sizer;
        add[lson] += add[rt]; add[rson] += add[rt];
        Min[lson] += add[rt]; Max[lson] += add[rt];
        Min[rson] += add[rt]; Max[rson] += add[rt];
        add[rt] = 0;
    }

    void update(int L, int R, ll C, int rt, int l, int r) {
        if (L>R) return;
        if (L>r||l>R) return;
        if ( L <= l && R >= r ) {
            seg[rt] += C*(r-l+1); add[rt] += C;
            Max[rt] += C; Min[rt] += C;
            return;
        }

        pushdown(rt, l, r);
        int mid = l + r >> 1;
        if (L<=mid) update(L, R, C, lson, l, mid);
        if (R>mid) update(L, R, C, rson, mid + 1, r);
        pushup(rt);
        
    }

    ll querySum(int L, int R, int rt, int l, int r) {
        if ( L>R ) return 0; 
        if ( L>r || l>R ) return 0;
        if ( L<=l && R >= r ) return seg[rt];
        int mid = (l + r) >> 1; ll ans = 0;
        pushdown(rt, l, r);
        if (L<=mid) ans = ans + querySum(L, R, lson, l, mid);
        if (R>mid) ans = ans + querySum(L, R, rson, mid + 1, r);
        pushup(rt); return ans;
    }

    
    ll queryMax(int L, int R, int rt, int l, int r) {
        if ( L>R ) return -INF; 
        if ( L>r || l>R ) return -INF;
        if ( L<=l && R >= r ) return Max[rt];
        int mid = (l + r) >> 1; ll ans = -INF;
        pushdown(rt, l, r);
        if (L<=mid) ans = max( ans, queryMax(L, R, lson, l, mid) );
        if (R>mid) ans = max( ans,queryMax(L, R, rson, mid + 1, r) );
        pushup(rt); return ans;
    }

    ll queryMin(int L, int R, int rt, int l, int r) {
        if ( L>R ) return INF; 
        if ( L>r || l>R ) return INF;
        if ( L<=l && R >= r ) return Min[rt];
        int mid = (l + r) >> 1; ll ans = INF;
        pushdown(rt, l, r);
        if (L<=mid) ans = min( ans, queryMin(L, R, lson, l, mid) );
        if (R>mid) ans = min( ans,queryMin(L, R, rson, mid + 1, r) );
        pushup(rt); return ans;
    }
} trF, trS;
