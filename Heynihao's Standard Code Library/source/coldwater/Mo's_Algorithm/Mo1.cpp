#include <bits/stdc++.h>

#define MAXN (10010)
#define MAXR (1010)
#define MAXC (1000010)

struct qnode{ int l, r, id, t;}query[MAXN];
struct rnode{ int pos, col, pre;}revise[MAXR];
int BLOCKSIZE;
int n, m, cnt_r, cnt_q, sum;
int bel[MAXN], col[MAXN], num[MAXC], last[MAXN], ans[MAXN];
bool inseg[MAXN];

inline bool cmp(const qnode &A, const qnode &B){
	return bel[A.l] == bel[B.l] ? (bel[A.r] == bel[B.r] ? A.t < B.t : A.r < B.r) :
		                          A.l < B.l;
}

inline void cal(int pos){
	if(inseg[pos]){
		num[col[pos]] --;
		sum -= !num[col[pos]];
	}
	else{
		sum += !num[col[pos]];
		num[col[pos]] ++;
	}
	inseg[pos] ^= 1;
}

inline void change(int pos, int c){
	if(inseg[pos]){
		cal(pos);
		col[pos] = c;
		cal(pos);
	}
	else col[pos] = c;
}

int main(){
	scanf("%d%d", &n, &m);
	BLOCKSIZE = (int)(ceil(pow(n, 2.0 / 3)));
	for(int i = 1; i <= n; ++ i){
		scanf("%d", col + i);
		last[i] = col[i];
		bel[i] = (i - 1) / BLOCKSIZE + 1;
	}
	for(int i = 1; i <= m; ++ i){
		char op[3];
		int l, r;
		scanf("%s%d%d", op, &l, &r);
		if(op[0] == 'R') revise[++ cnt_r] = {l, r, last[l]}, last[l] = r;
		else query[++ cnt_q] = {l, r, cnt_q, cnt_r};
	}
		
	std::sort(query + 1, cnt_q + query + 1, cmp);
	
	int l = 1, r = 0, t = 0;
	for(int i = 1; i <= cnt_q; ++ i){
		for(; t < query[i].t; ++ t) change(revise[t + 1].pos, revise[t + 1].col);
		for(; t > query[i].t; -- t) change(revise[t]    .pos, revise[t]    .pre);
		for(; r < query[i].r; ++ r) cal(r + 1);
		for(; r > query[i].r; -- r) cal(r    );
		for(; l < query[i].l; ++ l) cal(l    );
		for(; l > query[i].l; -- l) cal(l - 1);
	}
	return 0;
}
