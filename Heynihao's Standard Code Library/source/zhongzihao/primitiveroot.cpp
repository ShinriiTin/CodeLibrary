// Ô­¸ùÄ£°å
// checkroot() ·µ»Ø rt ÊÇ·ñÊÇ a µÄÔ­¸ù£¬solve() ·µ»Ø a ×îÐ¡µÄÔ­¸ù£¬Èç a ÎÞÔ­¸ù£¬²»±£Ö¤½á¹ûÕýÈ· 

#include<bits/stdc++.h>
#include"pollardrho.cpp"
#define ll long long

template <typename T>
class root{
private:
	T a, ans;
	std::vector <T> fact;
	
	void solve(){
		pollardrho <T> p(a - 1);
		fact = p.solve();
		std::sort(fact.begin(), fact.end());
		fact.erase(std::unique(fact.begin(), fact.end()), fact.end());
		for (T i = 1; i < a; ++ i){
			if (checkroot(i)){
				ans = i;
				return;
			}
		}
	}

public:
	root(){}
	
	root(T a):a(a){
		solve();
	}
	
	bool checkroot(T rt){
		for (auto u : fact){
			if (powermod(rt, a / u, a) == 1) return false;
		}
		return true;
	}
	
	T minroot(){
		return ans;
	}
};
