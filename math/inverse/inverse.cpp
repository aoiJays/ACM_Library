const long long MOD = 998244353LL;
const int N = 10000000 + 10;

vector <long long> fac(N), ifac(N);
fac[0] = ifac[0] = 1;
for (int i=1;i<N;++i) {
    fac[i] = fac[i-1] * i % MOD;
}

auto qpow = [&](long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD; b >>= 1;
    }
    return res;
};

// 阶乘逆元的递推
ifac[N - 1] = qpow(fac[N - 1], MOD - 2);
for (int i=N-2;i>=1;--i) {
    ifac[i] = ifac[i + 1] * (i + 1) % MOD;
    // assert( qpow(fac[i], MOD - 2) == ifac[i] );
}

// 线性求逆元
vector <long long> inv(N + 1);
inv[0] = 0; inv[1] = 1;

for(int i=2;i<=N;++i) {
    inv[i] = - (MOD / i) * inv[MOD % i];
    inv[i] = (inv[i] % MOD + MOD) % MOD;
}

// 拓展欧几里得 逆元
void Exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) x = 1, y = 0;
    else Exgcd(b, a % b, y, x), y -= a / b * x;
}
vector <long long> inv(N + 1);
inv[0] = 0; 

for(int i=1;i<=N;++i) {
    long long x, y;
    Exgcd(i, MOD, x, y);
    x = (x % MOD + MOD) % MOD;
    inv[i] = x;
}