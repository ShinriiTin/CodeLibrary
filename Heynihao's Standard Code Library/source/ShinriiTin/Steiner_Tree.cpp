//Steiner-Tree O(m3^k)
#include <bits/stdc++.h>

const int max_N=200,max_S=1<<7,inf=0x3f3f3f3f;

#define id(i,j) ((i-1)*m+j)
#define rpt(i,l,r) for(int i=(l),R=(r);i<=R;++i)

const int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int n,m,k,map[max_N+21];

int f[max_S][max_N+21];

std::pair<int,int>pre[max_S][max_N+21];

std::queue<int>queue;

bool vis[max_N+21];

inline void spfa(int set){
	while(!queue.empty()){
		int index=queue.front(),x,y;
		x=index/m;
		if(index%m!=0)++x;
		y=index-(x-1)*m;
		rpt(i,0,3){
			int nx=x+dir[i][0],ny=y+dir[i][1];
			if(!nx||nx>n||!ny||ny>m)continue;
			int nindex=id(nx,ny);
			if(f[set][index]+map[nindex]<f[set][nindex]){
				f[set][nindex]=f[set][index]+map[nindex];
				pre[set][nindex]={set,index};
				if(!vis[nindex]){
					queue.push(nindex);
					vis[nindex]=1;
				}
			}
		}
		queue.pop();
		vis[index]=0;
	}
}

int ans,ans_index;

bool concrete[max_N+21];

void dfs(int set,int index){
	if(!set||!index)return;
	concrete[index]=1;
	auto&prev=pre[set][index];
	int pset=prev.first,pindex=prev.second;
	dfs(pset,pindex);
	if(index==pindex)dfs(set^pset,pindex);
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	rpt(i,1,n*m)scanf("%d",map+i);
	memset(f,0x3f,sizeof(f));
	rpt(i,1,n*m)f[0][i]=0;
	rpt(i,1,k){
		int x,y,index;
		scanf("%d%d",&x,&y);
		index=id(x,y);
		f[1<<(i-1)][index]=map[index];
	}
	rpt(set,1,(1<<k)-1){
		rpt(index,1,n*m){
			for(int s=(set-1)&set;s;(--s)&=set){
				if(f[set][index]>f[s][index]+f[set^s][index]-map[index]){
					f[set][index]=f[s][index]+f[set^s][index]-map[index];
					pre[set][index]={s,index};
				}
			}
			if(f[set][index]<inf){
				queue.push(index);
				vis[index]=1;
			}
		}
		spfa(set);
	}
	ans=inf;
	int set=(1<<k)-1;
	rpt(index,1,n*m)if(ans>f[set][index]){
		ans=f[set][index],ans_index=index;
	}
    printf("%d\n",ans);
    dfs(set,ans_index);
    rpt(i,1,n){
		rpt(j,1,m)putchar(concrete[id(i,j)]?'X':'.');
		puts("");
    }
	return 0;
}