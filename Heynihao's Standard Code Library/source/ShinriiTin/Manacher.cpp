int r[2][MAXN<<1];

inline void manacher(char*S,int n,int rx){
	register int i,j,k;
	int*R=r[rx];
	for(i=j=0;i<n;i+=k,j=max(j-k,0)){
		while(i-j>=0&&i+j+rx<n&&S[i-j]==S[i+j+rx])++j;
		R[i]=j;
		for(k=1;k<j&&R[i-k]!=R[i]-k;++k)R[i+k]=min(R[i-k],R[i]-k);
	}
}