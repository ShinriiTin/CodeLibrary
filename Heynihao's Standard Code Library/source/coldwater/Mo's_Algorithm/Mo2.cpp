#include <bits/stdc++.h>

#define MAXN (40010)
#define MAXM (100010)
#define MAXB (16)

struct qnode{ int u, v, id;}query[MAXM];
int BLOCKSIZE;
int n, m, now;
int col[MAXN], bel[MAXN], dep[MAXN];
int dfn[MAXN], tot, stack[MAXN], top, blockcnt;
int f[MAXN][MAXB], ans[MAXM];
int cnt[MAXN];
bool inans[MAXN];
std::vector<int> vec[MAXN];

bool cmp(const struct qnode &a, const struct qnode &b){
	return bel[a.u] == bel[b.u] ? dfn[a.v] < dfn[b.v] : bel[a.u] < bel[b.u];
}

void dfs(int u, int fa){
	dfn[u] = ++ tot;
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
	if(inans[u]){
		cnt[col[u]] --;
		if(!cnt[col[u]]) now --;
	}
	else{
		if(!cnt[col[u]]) now ++;
		cnt[col[u]] ++;
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

int main(){
	scanf("%d%d", &n, &m);
	BLOCKSIZE = n / (int)sqrt(m);
	
	dfs(1, 0);
	while(top){
		bel[stack[-- top]] = blockcnt;
	}
	
	for(int i = 1; i <= m; ++ i){
		scanf("%d%d", &query[i].u, &query[i].v);
		if(dfn[query[i].u] > dfn[query[i].v]){
			std::swap(query[i].u, query[i].v);
		}
		query[i].id = i;
	}
	
	std::sort(query + 1, m + query + 1, cmp);
	
	int u = 1, v = 1;
	for(int i = 1; i <= m; ++ i){
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
