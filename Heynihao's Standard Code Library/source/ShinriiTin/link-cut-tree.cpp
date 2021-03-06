const int max_N=1e5;//最大的节点数
namespace Link_Cut_Tree{
    #define rep(d) for(int d=0;d<2;++d)
    typedef struct node*star;
    star null,tail,rt[max_N+1];
    struct node{
        int sz;
        bool rev_flag;
        star p,ch[2];
        inline void update(){
            sz=ch[0]->sz+1+ch[1]->sz;
        }
        inline void putdown(){
            if(rev_flag){
                std::swap(ch[0],ch[1]);
                ch[0]->rev_flag^=1,ch[1]->rev_flag^=1;
                rev_flag=0;
            }
        }
        inline int dir(){
            rep(d)if(p->ch[d]==this)return d;
            return -1;
        }
        inline void set_ch(star x,int d){
            if(~d)ch[d]=x;
            if(x!=null)x->p=this;
        }
    }pool[max_N+1];
    inline star init_null(){
        star x=tail++;
        x->sz=x->rev_flag=0;
        x->ch[0]=x->ch[1]=x->p=x;
        return x;
    }
    inline star new_node(){
        star x=tail++;
        x->sz=1,x->rev_flag=0;
        x->ch[0]=x->ch[1]=x->p=null;
        return x;
    }
    inline void rot(star x){
        register int d,d1;
        star y=x->p;
        d=x->dir(),d1=y->dir();
        y->p->set_ch(x,d1);
        y->set_ch(x->ch[d^1],d),y->update();
        x->set_ch(y,d^1);
    }
    void pd(star x){
        if(~x->dir())pd(x->p); x->putdown();
    }
    inline void splay(star x){
        register int d,d1;
        for(pd(x);~(d=x->dir());rot(x))if(~(d1=x->p->dir()))rot((d^d1)?x:x->p);
        x->update();
    }
    inline void access(star x){
        register star y,rch;
        for(y=x,rch=null;y!=null;rch=y,y=y->p)splay(y),y->set_ch(rch,1),y->update();
        splay(x);
    }
    inline void evert(star x){
        access(x),x->rev_flag^=1;
    }

    inline star get_path(star x,star y){//返回包含x到y的路径上所有点的splay的根
        return evert(x),access(y),y;
    }
    inline void link(star x,star y){//添加一条x到y的边，需要保证添加后仍是树结构
        evert(x),x->p=y;
    }
    inline void cut(star x,star y){//断开x到y之间的边，需要保证这条边存在
        evert(x),access(y);
        x->p=null,y->set_ch(null,0),y->update();
    }

    inline void init(int n){//初始化n个点的森林
        tail=pool,null=init_null();
        for(int i=1;i<=n;++i)rt[i]=new_node();
    }
};