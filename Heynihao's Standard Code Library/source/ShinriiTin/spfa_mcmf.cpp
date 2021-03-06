namespace MCMF{
	#define pb push_back
	const int max_N=500,inf=0x7f7f7f7f;
	struct edge{int v,w,c,f;};
	std::vector<edge>G;
	std::vector<int>vec[max_N+21];
	int n,s,t;
	int d[max_N+21],p[max_N+21];
	bool vis[max_N+21];
	inline bool spfa(){
		std::queue<int>q;
		rpt(i,1,n)d[i]=inf,p[i]=-1;
		d[s]=0;
		q.push(s),vis[s]=1;
		while(!q.empty()){
			int x=q.front();
			for(auto&i:vec[x]){
				auto&e=G[i];
				if(e.c==e.f)continue;
				if(d[e.v]>d[x]+e.w){
					d[e.v]=d[x]+e.w;
					p[e.v]=i;
					if(vis[e.v])continue;
					q.push(e.v),vis[e.v]=1;
				}
			}
			q.pop(),vis[x]=0;
		}
		return ~p[t];
	}
	inline int mcmf(){
		int ans=0,x,a;
		while(spfa()){
			a=inf;
			for(x=t;x!=s;x=G[p[x]^1].v)a=std::min(a,G[p[x]].c-G[p[x]].f);
			for(x=t;x!=s;x=G[p[x]^1].v)G[p[x]].f+=a,G[p[x]^1].f-=a;
			ans+=d[t]*a;
		}
		return ans;	
	}
	inline void init(int N,int S,int T){
		n=N,s=S,t=T;
		rpt(i,1,n)vec[i].clear();
		G.clear();
	}
	inline void add_edge(int u,int v,int w,int c){
		if(!c)return;
		vec[u].pb(G.size()),G.pb({v,w,c,0});
		vec[v].pb(G.size()),G.pb({u,-w,0,0});
	}
};