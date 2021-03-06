namespace PST{
	struct node{
		node *ch[2];
		int sum;
		node* get_ch(int kind){ return this ? this -> ch[kind] : 0; }
		int get_sum(){ return this ? this -> sum : 0; }
	}nd_pool[MAXS * 30], *root[MAXS];
	int nd_res;
	
	void init(){ nd_res = 0; }
	
	node* newnode(){
		node *ret = nd_pool + (nd_res ++);
		ret -> sum = 0;
		ret -> ch[0] = ret -> ch[1] = 0;
		return ret;
	}
	
	node* copy(node *x){
		node *ret = newnode(); assert(x);
		*ret = *x;
		return ret;
	}
	
	void insert(node* &rt, int l, int r, int pos, int val){
		rt = rt ? copy(rt) : newnode();
		rt -> sum += val;
		if(l == r) return;
		int m = l + r >> 1;
		if(pos <= m) insert(rt -> ch[0], l, m, pos, val);
		else insert(rt -> ch[1], m + 1, r, pos, val);
	}
	
	int query(node* rt, int l, int r, int ql, int qr){
		if(ql > qr) return 0;
		if(ql <= l && r <= qr) return rt -> get_sum();
		int m = l + r >> 1, ret = 0;
		if(!(m < ql)) ret += query(rt -> get_ch(0), l, m, ql, qr);
		if(!(qr < m + 1)) ret += query(rt -> get_ch(1), m + 1, r, ql, qr);
		return ret;
	}
	
}
