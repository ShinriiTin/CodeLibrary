const int max_N=300,inf=0x7f7f7f7f;

namespace dinic{
    #define pb push_back
    struct edge{int v,c,f;};
    std::vector<edge>G;
    std::vector<int>vec[max_N+21];
    int n,s,t,cnt;
    int d[max_N+21],cur[max_N+21],q[max_N+21];
    inline bool bfs(){
        int tail=1;
        for(int i=1;i<=n;++i)d[i]=cur[i]=0;
        d[s]=1,q[1]=s;
        for(int j=1;j<=tail;++j){
            int x=q[j];
            for(auto&i:vec[x]){
                auto&e=G[i];
                if(e.c==e.f||d[e.v])continue;
                d[e.v]=d[x]+1;
                q[++tail]=e.v;
            }
        }
        return d[t];
    }
    int dfs(int x,int a){
        if(x==t||!a)return a;
        int flow=0,f;
        for(int&i=cur[x];i<vec[x].size();++i){
                auto&e=G[vec[x][i]];
                auto&re=G[vec[x][i]^1];
                if(e.c==e.f||d[e.v]!=d[x]+1)continue;
                f=dfs(e.v,std::min(a,e.c-e.f));
                if(f){
                    flow+=f,e.f+=f,re.f-=f;
                    if(!(a-=f))break;
                }
            }
        if(!flow)d[x]=0;
        return flow;
    }
    inline int max_flow(int S,int T){
        s=S,t=T;
        int flow=0;
        while(bfs())flow+=dfs(s,inf);
        return flow;
    }
    inline void add_edge(int u,int v,int c){
        if(!c)return;
        vec[u].pb(cnt++),G.pb({v,c,0});
        vec[v].pb(cnt++),G.pb({u,0,0});
    }
    inline void init(int N){
        n=N;
        for(int i=1;i<=n;++i)vec[i].clear();
        G.clear();
        cnt=0;
    }
};