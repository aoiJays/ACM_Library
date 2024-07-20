
typedef long long ll;

const ll base[2] = {233, 131};
const ll mod[2] = {(long long)1e9+7, (long long)1e9+9};

#define MAXN 2000005
ll Pow[2][MAXN];

struct StringHash {

    vector<ll> C[2];
    string str;

    void set(int n) {
        for (int i=0;i<2;++i) {
            C[i].resize(n + 1);
            C[i][0] = 0;
            for (int j=0;j<n;++j)
                C[i][j+1] = (C[i][j]*base[i] + str[j] - 'A')%mod[i];
        }
    }    

    pair<ll,ll> getHash(int l, int r) {
        ll hash0 = ((C[0][r] - C[0][l-1]*Pow[0][r-l+1]%mod[0])%mod[0] + mod[0])%mod[0];
        ll hash1 = ((C[1][r] - C[1][l-1]*Pow[1][r-l+1]%mod[1])%mod[1] + mod[1])%mod[1];
        return make_pair(hash0, hash1);
    }    
};

int main() {
    
    for (int i=0;i<2;++i) {
        Pow[i][0] = 1;
        for (int j=1;j<MAXN;++j)
            Pow[i][j] = Pow[i][j-1]*base[i]%mod[i];
    }

}