template <int mod>
unsigned int down(unsigned int x){
    return x >= mod ? x - mod : x;
}
template <int mod>
struct Modint{
    unsigned int x;
    Modint() = default;
    Modint(unsigned int x) : x(x) {}
    friend istream &operator>>(istream &in, Modint &a) { return in >> a.x; }
    friend ostream &operator<<(ostream &out, Modint a) { return out << a.x; }
    friend Modint operator+(Modint a, Modint b) { return down<mod>(a.x + b.x); }
    friend Modint operator-(Modint a, Modint b) { return down<mod>(a.x - b.x + mod); }
    friend Modint operator*(Modint a, Modint b) { return 1ULL * a.x * b.x % mod; }
    friend Modint operator/(Modint a, Modint b) { return a * ~b; }
    friend Modint operator^(Modint a, int b){
        Modint ans = 1;
        for (; b; b >>= 1, a *= a)
            if (b & 1)
                ans *= a;       
        return ans;
    }
    friend Modint operator~(Modint a) { return a ^ (mod - 2); }
    friend Modint operator-(Modint a) { return down<mod>(mod - a.x); }
    friend Modint &operator+=(Modint &a, Modint b) { return a = a + b; }
    friend Modint &operator-=(Modint &a, Modint b) { return a = a - b; }
    friend Modint &operator*=(Modint &a, Modint b) { return a = a * b; }
    friend Modint &operator/=(Modint &a, Modint b) { return a = a / b; }
    friend Modint &operator^=(Modint &a, int b) { return a = a ^ b; }
    friend Modint &operator++(Modint &a) { return a += 1; }
    friend Modint operator++(Modint &a, int){
        Modint x = a;
        a += 1;
        return x;
    }
    friend Modint &operator--(Modint &a) { return a -= 1; }
    friend Modint operator--(Modint &a, int){
        Modint x = a;
        a -= 1;
        return x;
    }
    friend bool operator==(Modint a, Modint b) { return a.x == b.x; }
    friend bool operator!=(Modint a, Modint b) { return !(a == b); }
};
typedef Modint<998244353> mint;

struct Poly(){
    const int mod = 998244353;
    const mint g = 3;
    vector<mint> f;
    Poly(vector<mint> &g){
        f = g;
    }
    Poly(int n){
        f.resize(n+1);
    }
    mint binpow(mint a,int k){
        mint res = 1;
        while(k){
            if(k&1) res = res*a;
            a = a*a;
            k >>= 1;
        }
        return res;
    }
    void transform(vector<mint> &poly,int n,int on){
        for(int i = 0,j = 0;i < n;i++){
            if(i > j) swap(poly[i],poly[j]);
            for(int l = n>>1;(j ^= l) < l;l >>= 1);
        }
        for(int l = 2;l <= n;l <<= 1){
            int m = l>>1;
            mint gn = binpow(g,(mod-1)/l);
            if (on == -1)
                gn = binpow(gn, mod - 2);
            for(int i = 0;i < n;i += l){
                mint w = 1;
                for(int j = 0;j < m;j++){
                    mint u = poly[i+j];
                    mint v = poly[i+j+m]*w;
                    poly[i+j] = u+v;
                    poly[i+j+m] = u-v;
                    w *= gn;
                }
            }
        }
        if(on == -1){
            mint inv = binpow(n,mod-2);
            for(int i = 0;i < n;i++){
                poly[i] = poly[i]*inv;
            }
        }
    }
    void dft(vector<mint> &poly,int n){
        transform(poly,n,1);
    }
    void idft(vector<mint> &poly,int n){
        transform(poly,n,-1);
    }
    friend Poly operator * (Poly a,Poly b){
        int n = a.size();
        int m = b.size();
        int k = 1;
        while(k <= n+m) k <<= 1;
        a.resize(k);
        b.resize(k);
        dft(a,k);
        dft(b,k);
        for(int i = 0;i < k;i++){
            a[i] = a[i]*b[i];
        }
        idft(a,k);
        a.resize(n+m-1);
        return a;
    }
    friend Poly operator *= (Poly &a,Poly b){
        a = a * b;
    }
    friend Poly operator + (Poly a,Poly b){
        int len = max(a.f.size(),b.f.size()) - 1;
        a.f.resize(len);
        for(int i = 0;i <= len;i++){
            a.f[i] += b.f[i];
        }
    }
    friend Poly operator 
}