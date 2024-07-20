
template<typename T,const T p>
class Modint{

    private:
        T v;

    public:
        
        Modint() {}
        Modint(const T& x) : v(x%p) {}

        Modint operator+(const Modint& a) const {
            return v+a.v >= p ? v+a.v-p : v+a.v;
        }
        
        Modint operator-(const Modint& a) const {
            return v<a.v ? v - a.v + p : v - a.v;
        }
        
        Modint operator*(const Modint& a) const {
            return 1ll*v*a.v%p;
        }

        T operator()(void) const{
            return v;
        }
};

using ll = Modint<long long,998244353LL>;