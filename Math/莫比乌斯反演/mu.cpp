vector<int> prime;
bool isprime[maxn];
int mu[maxn];
void init(int n){
    isprime[1] = 1;
    mu[1] = 1;
    for(int i = 2;i <= n;i++){
        if(!isprime[i])
            prime.push_back(i),mu[i] = -1;
        for(int j = 0;j < prime.size() && prime[j] * i <= n;j++){
            isprime[prime[j] * i] = 1;//每个数字都被最小的质因数筛掉
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0; //存在平方质因子
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}