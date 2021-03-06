// 随机数模板 

#include<bits/stdc++.h>
#define ll long long

// 产生一个 [0, n) 的随机数 
int randint(int n){
	return (rand() << 15 | rand()) % n;
}

// 产生一个 [0, n) 的随机数
ll randll(ll n){
	return (1ll * rand() << 45 | 1ll * rand() << 30 | rand() << 15 | rand()) % n;
}

// 产生一个整数部分 digit 位，小数部分 scale 位的实数 
double randdb(int digit, int scale){
	double ret = 0;
	for (int i = 0; i < digit; ++ i){
		ret = ret * 10 + randint(10);
	}
	double now = 0.1;
	for (int i = 0; i < scale; ++ i, now /= 10){
		ret = ret + randint(10) * now;
	}
	return ret;
}

// 产生一个小写字母 
char randlower(){
	return 'a' + randint(26);
}

// 产生一个大写字母 
char randupper(){
	return 'A' + randint(26);
}

// 产生一个数字字符 
char randdigit(){
	return '0' + randint(10);
}

// 产生一个字母或数字字符 
char randchar(){
	int x = randint(3);
	switch (x){
		case 0 : return randlower();
		case 1 : return randupper();
		case 2 : return randdigit();
	}
}

// 产生一个 digit 位的大整数（直接输出） 
void randBigInteger(int digit){
	for (int i = 0; i < digit; ++ i){
		putchar('0' + (i ? randint(10) : randint(9) + 1));
	}
}

int main(){
	srand((unsigned) time(NULL));
	return 0;
}