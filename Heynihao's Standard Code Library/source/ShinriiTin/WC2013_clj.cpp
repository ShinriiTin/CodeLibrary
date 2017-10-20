#include<set>
#include<cstdio>
#include<queue>
#include<vector>
#include<cmath>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
const int MAXN=100010,MAXM=300010;
inline int gint(const int& flag){
    int x=0;char a;while(a=getchar(),a<48||a>57);
    for(;a>47&&a<58;a=getchar())x=10*x+a-48;
    if(flag){x<<=1;if(a=='.')++x,a=getchar();}
    return x;
}
struct Point{
    int x,y;
    inline Point(){}
    inline Point(const int& x,const int& y):x(x),y(y){}
    inline Point operator - (const Point& a){return Point(x-a.x,y-a.y);}
    inline LL det(const Point& a){return 1LL*x*a.y-1LL*y*a.x;}
    inline void Init(){x=gint(1);y=gint(1);}
    inline double alpha(){return atan2(y,x);}
    inline bool operator == (const Point& a)const{return x==a.x&&y==a.y;}
}p[MAXN];
inline int dcmp(const LL& x){return x<0?-1:x>0;}
inline LL cross(Point p1,Point p2,Point p3){return (p2-p1).det(p3-p1);}
int n,m,q;
typedef struct Edge* EStar;
vector<EStar>ALLE;
struct Edge{
    double alpha;
    int s,t,d,id;
    EStar rev,nex,pre;
    inline Edge(){}
    inline Edge(const int& s,const int& t,const int& d):s(s),t(t),d(d),id(-1){alpha=(p[t]-p[s]).alpha();}
}pool[MAXM];
vector<EStar>ES[MAXN];
EStar tail=pool;
inline EStar MakeEdge(const int& s,const int& t,const int& d){
    EStar x=tail++;*x=Edge(s,t,d);ALLE.push_back(x);ES[s].push_back(x);return x;
}
inline void AddEdge(const int& s,const int& t,const int& d){
    EStar st=MakeEdge(s,t,d),ts=MakeEdge(t,s,d);st->rev=ts;ts->rev=st;
}
inline bool cmp(Edge* a,Edge* b){return a->alpha<b->alpha;}
inline void Init(){
    n=gint(0);m=gint(0);
    for(int i=1;i<=n;++i)p[i].Init();
    for(int i=1,s,t,d;i<=m;++i){
        s=gint(0);t=gint(0);d=gint(0);
        AddEdge(s,t,d);
    }
}
int nId,BanId=-1;
inline void BuildGraph(){
    for(int i=1;i<=n;++i){
        vector<EStar>& arr=ES[i];
        if(arr.empty())continue;
        sort(arr.begin(),arr.end(),cmp);
        for(int j=0,siz=arr.size();j<siz;++j){
            arr[j]->nex=arr[(j+1)%siz];
            arr[j]->nex->pre=arr[j];
        }
    }
    for(int i=0,s=ALLE.size();i<s;++i){
        EStar e=ALLE[i];
        if(e->id!=-1)continue;
        LL area=0;
        while(e->id==-1){
            area+=p[e->s].det(p[e->t]);
            e->id=nId;
            e=e->rev->pre;
        }
        if(area<0)BanId=nId;
        ++nId;
    }
}
struct Dual{
    int s,t,d;
    inline Dual(){}
    inline Dual(const int& s,const int& t,const int& d):s(s),t(t),d(d){}
    inline bool operator < (const Dual& a)const{return d<a.d;}
};
vector<Dual>DES;
struct UFS{
    int fa[MAXM];
    inline void Init(const int& n){for(int i=0;i<n;++i)fa[i]=i;}
    int find(const int& x){return x==fa[x]?x:fa[x]=find(fa[x]);}
    inline bool Unite(const int& a,const int& b){
        int x=find(a),y=find(b);fa[x]=y;return x!=y;
    } 
}UF;
struct MST{
    static const int N=MAXM,H=20;
    struct Edge{
        int t,d,n;
        inline Edge(){}
        inline Edge(const int& t,const int& d,const int& n):t(t),d(d),n(n){}
    }e[N];
    int Head[N],Etot;
    inline void AddEdge(const int& s,const int& t,const int& d){
        e[++Etot]=Edge(t,d,Head[s]);Head[s]=Etot;
        e[++Etot]=Edge(s,d,Head[t]);Head[t]=Etot;
    }
    int anc[N][H],Max[N][H],dep[N],n;
    inline void Init(const int& N){
        n=N;Etot=0;
        memset(Head,0,sizeof(Head));
    }
    inline void Bfs(const int& rt){
        queue<int>Q;  
        Q.push(rt);
        memset(anc[rt],-1,sizeof(anc[rt]));
        memset(Max[rt],-1,sizeof(Max[rt]));
        dep[rt]=0;
        while(!Q.empty()){
            int x=Q.front(),y;Q.pop();
            for(int i=Head[x];i;i=e[i].n)
                if((y=e[i].t)!=anc[x][0]){
                    dep[y]=dep[x]+1;
                    anc[y][0]=x;
                    Max[y][0]=e[i].d;
                    for(int j=1;j<H;++j)
                        if(anc[y][j-1]==-1)
                            anc[y][j]=Max[y][j]=-1;
                        else
                            anc[y][j]=anc[anc[y][j-1]][j-1],
                            Max[y][j]=max(Max[y][j-1],Max[anc[y][j-1]][j-1]);
                    Q.push(y);
                }
        }
    }
    inline int Query(int x,int y){
        int ans=-1;
        if(dep[x]>dep[y])swap(x,y);
        for(int i=0,h=dep[y]-dep[x];h;++i,h>>=1)
            if(h&1)ans=max(ans,Max[y][i]),y=anc[y][i];
        if(x==y)return ans;
        for(int i=H-1;i>=0;--i)
            if(anc[x][i]!=anc[y][i]){
                ans=max(ans,Max[x][i]);
                ans=max(ans,Max[y][i]);
                x=anc[x][i];y=anc[y][i];
            }
        ans=max(ans,Max[x][0]);
        ans=max(ans,Max[y][0]);
        return ans;
    }
}Mst;
inline void Kruskal(){
    for(int i=0,siz=ALLE.size(),u,v;i<siz;++i){
        EStar e=ALLE[i];
        if((u=e->id)!=BanId&&(v=e->rev->id)!=BanId)DES.push_back(Dual(u,v,e->d));
    }
    sort(DES.begin(),DES.end());
    UF.Init(nId);Mst.Init(nId);
    for(int i=0,siz=DES.size();i<siz;++i)
        if(UF.Unite(DES[i].s,DES[i].t))Mst.AddEdge(DES[i].s,DES[i].t,DES[i].d);
    Mst.Bfs(BanId?0:1);
}
const int ADD=0,QRY=1,DEL=2;
struct Event{
    int type;
    EStar e;
    int x,y,*ptr;
    inline Event(){}
    inline Event(const int& x,const int& y,int* ptr):type(QRY),x(x),y(y),ptr(ptr){}
    inline Event(const int& x,const EStar& e,const int& type):type(type),e(e),x(x){}
    inline bool operator < (const Event& a)const{return x!=a.x?x<a.x:type<a.type;}
};
vector<Event>events;
const int P=0,S=1;
struct Stuff{
    int type,id;
    Point p1,p2;
    inline Stuff(){}
    inline Stuff(const Point& p):type(P),p1(p){}
    inline Stuff(const Point& p1,const Point& p2):type(S),p1(p1),p2(p2){}
};
inline bool CmpSP(const Point& p1,const Point& p2,const Point& q){return p1.x<=q.x&&q.x<=p2.x;}
inline bool CmpSS(const Point& p1,const Point& p2,const Point& q1,const Point& q2){
    if(p2==q1)return 1;if(q2==p1)return 0;
    int op;
    if(CmpSP(p1,p2,q1))if((op=dcmp(cross(p1,p2,q1)))!=0)return op<0;
    if(CmpSP(p1,p2,q2))if((op=dcmp(cross(p1,p2,q2)))!=0)return op<0;
    if(CmpSP(q1,q2,p1))if((op=dcmp(cross(q1,q2,p1)))!=0)return op>0;
    if(CmpSP(q1,q2,p2))if((op=dcmp(cross(q1,q2,p2)))!=0)return op>0;
    return 0;
}
inline bool operator < (const Stuff& a,const Stuff& b){
    if(a.type==P&&b.type==S)return dcmp(cross(b.p1,b.p2,a.p1))>0;
    if(a.type==S&&b.type==P)return !(b<a);
    return CmpSS(a.p1,a.p2,b.p1,b.p2);
}
struct Query{
    Point p1,p2;
    int s,t;
    inline void Init(){p1.Init();p2.Init();}
}qs[MAXN];
inline void Scanning(){
    q=gint(0);
    for(int i=1;i<=q;++i)qs[i].Init();
    for(int i=0,siz=ALLE.size();i<siz;++i){
        EStar e=ALLE[i];
        Point p1=p[e->s],p2=p[e->t];
        if(p1.x<p2.x){
            events.push_back(Event(p1.x,e,ADD));
            events.push_back(Event(p2.x,e,DEL));
        }
    }
    for(int i=1;i<=q;++i){
        Query& Q=qs[i];
        events.push_back(Event(Q.p1.x,Q.p1.y,&Q.s));
        events.push_back(Event(Q.p2.x,Q.p2.y,&Q.t));
    }
    sort(events.begin(),events.end());
    set<Stuff>Stf;
    set<Stuff>::iterator it;
    for(int i=0,siz=events.size();i<siz;++i){
        Event& e=events[i];
        if(e.type!=QRY){
            EStar ep=e.e;
            Stuff st(p[ep->s],p[ep->t]);
            st.id=ep->id;
            if(e.type==ADD)Stf.insert(st);
            else Stf.erase(st);
        }else{
            Stuff st(Point(e.x,e.y));
            it=Stf.lower_bound(st);
            *e.ptr=it!=Stf.end()?it->id:BanId;
        }
    }
}
inline void AnswerQueries(){
    for(int i=1;i<=q;++i){
        Query& Q=qs[i];
        if(Q.s==BanId||Q.t==BanId)puts("-1");
        else if(Q.s==Q.t)puts("0");
        else printf("%d\n",Mst.Query(Q.s,Q.t));
    }
}
int main(){
    Init();
    BuildGraph();
    Kruskal();
    Scanning();
    AnswerQueries();
    return 0;
}