std::vector<int>vec[max_N+21];

int dfn[max_N+21],low[max_N+21],cnt;

int sccno[max_N+21],scc_cnt;

std::stack<int>st;

void dfs(int x){
	st.push(x);
	dfn[x]=low[x]=++cnt;
	for(auto&y:vec[x]){
		if(!dfn[y]){
			dfs(y);
			low[x]=std::min(low[x],low[y]);
		}
		else if(!sccno[y]){
			low[x]=std::min(low[x],dfn[y]);	
		}
	}
	if(dfn[x]==low[x]){
		sccno[x]=++scc_cnt;
		while(st.top()!=x){
			sccno[st.top()]=scc_cnt;
			st.pop();
		}
		st.pop();
	}
}