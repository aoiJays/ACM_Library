template<class T>
struct Fenwick {
    
    vector<T> a;
    Fenwick(int n) {
        a.resize(n + 1);
        fiil(a.begin(), a.end(), 0);
    }

    #define lowbit(x) (x&(-x))
    void update(int x, T c) {
        for (;x<a.size();x+=lowbit(x))
            a[x] += c;
    }

    T query(int x) {
        T ans = 0;
        for (;x;x-=lowbit(x))
            ans += a[x];
        return ans;
    }
};