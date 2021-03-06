// 中国剩余定理模板
// 求方程组 x = remain1(mod moder1), x = remain2(mod moder2) 的解
// p.crt(q) 返回方程 p, q 的解 

#include<bits/stdc++.h>

typedef long long ll;

// 如果没有 __int128 就只能这么写啦 
ll multmod(ll a, ll b, ll moder){
	const int div = 1e9;
	typedef unsigned long long ull;
	ull c = a / div, d = a % div, e = b / div, f = b % div;
	ull ret = d * f % moder, tmp = c * e % moder;
	for (int i = 0; i < 9; ++ i){
		tmp = tmp * 10 % moder;
	}
	tmp += d * e;
	tmp -= tmp >= moder ? moder : 0;
	tmp += c * f;
	tmp -= tmp >= moder ? moder : 0;
	for (int i = 0; i < 9; ++ i){
		tmp = tmp * 10 % moder;
	}
	ret += tmp;
	ret -= ret >= moder ? moder : 0;
	return ret;
}

/* another edition
ll multmod(ll a, ll b, ll moder){
	a = (a % moder + moder) % moder, b = (b % moder + moder) % moder;
	ll ret = 0;
	for ( ; b; b >>= 1){
		if (b & 1){
			ret += a;
			ret -= ret >= moder ? moder : 0;
		}
		a <<= 1;
		a -= a >= moder ? moder : 0;
	}
	return ret;
}
*/

template <typename T> 
class modequa{
private:
	T remain, moder;
	
	ll getone(int n){return 1;}
	__int128 getone(ll n){return 1;}
	
public:
	modequa <T>(){}
	modequa <T>(T remain, T moder) : remain(remain), moder(moder){}
	T getremain(){return remain;}
	T getmoder(){return moder;}
	
	modequa <T> crt(const modequa <T> &p){
		auto one = getone(remain);
		T gcd = moder, x = 1, y = 0;
		for (T b = p.moder, x1 = 0, y1 = 1, r, s; b; ){
			r = x, s = y;
			x = x1, y = y1, x1 = r - x1 * (gcd / b), y1 = s - y1 * (gcd / b);
			r = gcd % b, gcd = b, b = r;
		}
		if ((p.remain - remain) % gcd) return modequa <T>(0, 0);
		T lcm = moder / gcd * p.moder;
		T ans = (p.remain - remain) / gcd;
		ans = one * ans * x % lcm * moder % lcm;
		ans += remain;
		ans += ans < 0 ? lcm : ans >= lcm ? -lcm : 0;
		return modequa <T>(ans, lcm);
	}
};

int main(){
	return 0;
}