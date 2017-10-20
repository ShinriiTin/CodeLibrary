#include <bits/stdc++.h>

#define MAXN (100010)
#define MAXB (18)
#define ll long long

struct qnode{ int u, v, id, t;} query[MAXN];
struct rnode{ int pos, col, pre;} revise[MAXN];
int cnt_q, cnt_r, last[MAXN];
ll ans[MAXN], sum;
int cnt[MAXN];
bool inans[MAXN];
int n, m, q;
ll v[MAXN], w[MAXN], c[MAXN];
int bel[MAXN], tot, stack[MAXN], top, dep[MAXN];
int BLOCKSIZE, blockcnt;
int f[MAXN][MAXB];
std::vector<int> vec[MAXN];

bool cmp(const struct qnode &a, const struct qnode &b){
	return bel[a.u] == bel[b.u] ? (bel[a.v] == bel[b.v] ? a.t < b.t : bel[a.v] < bel[b.v]) :
		                          bel[a.u] < bel[b.u];
}

void dfs(int u, int fa){
	int bottom = top;
	for(auto v : vec[u]){
		if(v == fa) continue;
		f[v][0] = u;
		dep[v] = dep[u] + 1;
		for(int j = 0; f[v][j + 1] = f[f[v][j]][j]; ++ j);
		dfs(v, u);
		
		if(top - bottom >= BLOCKSIZE){
			++ blockcnt;
			while(top != bottom){
				bel[stack[-- top]] = blockcnt;
			}
		}
	}
	stack[top ++] = u;
}

void change(int u){
	int col = c[u];
	if(inans[u]){
		sum -= w[cnt[col]] * v[col];
		cnt[col] --;
	}
	else{
		cnt[col] ++;
		sum += w[cnt[col]] * v[col];
	}
	inans[u] ^= 1;
}

void move(int u, int v){
	int w = lca(u, v);
	for(int i = u; i != w; i = f[i][0]){
		change(i);
	}
	for(int i = v; i != w; i = f[i][0]){
		change(i);
	}
}

void moveTime(int u, int col){
	if(inans[u]){
		change(u);
		c[u] = col;
		change(u);
	}
	else c[u] = col;
}

int main(){
	readin(n); readin(m); readin(q);
	BLOCKSIZE = (int)(ceil(pow(n, 2.0 / 3)) * 0.5);
	for(int i = 1; i <= m; ++ i){
		readin(v[i]);
	}
	for(int i = 1; i <= n; ++ i){
		readin(w[i]);
	}
	for(int i = 1; i < n; ++ i){
		int a, b;
		readin(a); readin(b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	
	dfs(1, 0);
	while(top){
		bel[stack[-- top]] = blockcnt;
	}
	
	for(int i = 1; i <= n; ++ i){
		readin(c[i]);
		last[i] = c[i];
	}
	
	for(int i = 1; i <= q; ++ i){
		int t, x, y;
		readin(t); readin(x); readin(y);
		if(t){
			query[++ cnt_q] = (qnode){x, y, cnt_q, cnt_r};
		}
		else{
			revise[++ cnt_r] = (rnode){x, y, last[x]};
			last[x] = y;
		}
	}
	
	std::sort(query + 1, cnt_q + query + 1, cmp);
	
	int u = 1, v = 1, t = 0;
	for(int i = 1; i <= cnt_q; ++ i){
		for(; t < query[i].t; ++ t) moveTime(revise[t + 1].pos, revise[t + 1].col);
		for(; t > query[i].t; -- t) moveTime(revise[t]    .pos, revise[t]    .pre);
		move(u, query[i].u);
		move(v, query[i].v);
		u = query[i].u;
		v = query[i].v;
		int w = lca(u, v);
		change(w);
		//get ans
		change(w);
	}
	return 0;
}
