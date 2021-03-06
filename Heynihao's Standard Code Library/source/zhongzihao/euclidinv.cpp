// 拓欧求逆元模板
// inv(a, moder) 表示 a 在 (mod moder) 下的逆元，如无逆元返回 -1 

#include<bits/stdc++.h>

typedef long long ll;

template <typename T>
T inv(T a, T moder){
	T gcd = a, x = 1, y = 0;
	for (T b = moder, x1 = 0, y1 = 1, r, s; b; ){
		r = x, s = y;
		x = x1, y = y1, x1 = r - x1 * (gcd / b), y1 = s - y1 * (gcd / b);
		r = gcd % b, gcd = b, b = r;
	}
	if (gcd != 1) return -1;
	return x + moder >= moder ? x : x + moder;
}