#include <bits/stdc++.h>

#define MAXN (50010)
#define ll long long

struct node{
	int l, r, id;
}query[MAXN];
int BLOCKSIZE;
int n, m;
int c[MAXN], cnt[MAXN], bel[MAXN];
ll sum = 0;

bool cmp(const node &A, const node &B){
	return bel[A.l] == bel[B.l] ? A.r < B.r : A.l < B.l;
}

void move(int pos, int val){
	sum -= cnt[pos] * cnt[pos];
	cnt[pos] += val;
	sum += cnt[pos] * cnt[pos];
}

int main(){
	scanf("%d%d", &n, &m);
	BLOCKSIZE = (int)(ceil(sqrt(n)));
	for(int i = 1; i <= n; ++ i){
		scanf("%d", c + i);
		bel[i] = (i - 1) / BLOCKSIZE + 1;
	}
	for(int i = 1; i <= m; ++ i){
		int l, r;
		scanf("%d%d", &l, &r);
		query[i] = {l, r, i};
	}
	std::sort(query + 1, m + query + 1, cmp);
	
	int l = 1, r = 0;
	for(int i = 1; i <= m; ++ i){
		for(; r < query[i].r; ++ r) move(c[r + 1],  1);
		for(; r > query[i].r; -- r) move(c[r]    , -1); 
		for(; l < query[i].l; ++ l) move(c[l]    , -1);
		for(; l > query[i].l; -- l) move(c[l - 1],  1);
	}
	return 0;
}
