//indexed from 1
template<size_t size>
struct Manacher{
	int r[2][size];
	template<typename T>
	inline void manacher(T S,int len,int type){
		register int i,j,k;
		int*R=r[type];
		for(i=1,j=0;i<=len;i+=k,j=std::max(j-k,0)){
			while(i-j>0&&i+j+type<=len&&S[i-j]==S[i+j+type])++j;
			R[i]=j;
			for(k=1;k<j&&R[i-k]!=R[i]-k;++k)R[i+k]=std::min(R[i-k],R[i]-k);
		}
	}
};
