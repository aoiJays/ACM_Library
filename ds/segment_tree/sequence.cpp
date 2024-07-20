#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 区间加一个等差数列 区间求和
struct SegmentTree {

    #define MAXN 300005
    
    ll seg[MAXN<<2], d[MAXN<<2], s[MAXN<<2];
    int tag[MAXN<<2];
    

    #define lson (rt << 1)
    #define rson (rt << 1 | 1)

    ll sum(ll s, ll d, int len) {
        return s * len + d * (1LL*(len - 1) * (len)/2);
    }

    void pushup(int rt) {
        seg[rt] = seg[lson] + seg[rson];
    }

    void build(int rt, int l, int r) {
        seg[rt] = d[rt] = s[rt] = tag[rt] = 0;
        if ( l==r ) return;
        int mid = (l + r) >> 1;
        build(lson, l, mid); build(rson, mid + 1, r);
        pushup(rt);
    }

    void pushdown(int rt, int l, int r) {
        int mid = l + r >> 1, sizel = mid - l + 1, sizer = r - mid;
        if ( !tag[rt] ) return;

        seg[lson] = seg[lson] + sum( s[rt], d[rt], sizel );
        seg[rson] = seg[rson] + sum( s[rt] + d[rt] * sizel, d[rt], sizer );

        s[lson] = s[lson] + s[rt];
        s[rson] = s[rson] + s[rt] + d[rt] * sizel;

        d[lson] = d[lson] + d[rt];
        d[rson] = d[rson] + d[rt];

        s[rt] = d[rt] = 0;
        tag[lson] = tag[rson] = 1;
        tag[rt] = 0;        
    }

    void update(int L, int R, ll S, ll D, int rt, int l, int r) {
        if (L>r||l>R) return;
        if ( L <= l && R >= r ) {
            ll first_item = S + D*(l - L);
            s[rt] = s[rt] + first_item;
            d[rt] = d[rt] + D; tag[rt] = 1;
            seg[rt] = seg[rt] + sum(first_item, D, r - l + 1);
            return;
        }

        pushdown(rt, l, r);
        int mid = l + r >> 1;
        if (L<=mid) update(L, R, S, D, lson, l, mid);
        if (R>mid) update(L, R, S, D, rson, mid + 1, r);
        pushup(rt);
        
    }

    ll query(int L, int R, int rt, int l, int r) {
        if ( L>R ) return 0; 
        if ( L>r || l>R ) return 0;
        if ( L<=l && R >= r ) return seg[rt];
        int mid = (l + r) >> 1; ll ans = 0;
        pushdown(rt, l, r);
        if (L<=mid) ans = ans + query(L, R, lson, l, mid);
        if (R>mid) ans = ans + query(L, R, rson, mid + 1, r);
        pushup(rt); return ans;
    }
} tr;

