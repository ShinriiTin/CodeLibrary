//indexed from 1
template<size_t size>
struct Kmp{
	int fail[size];
	template<typename T>
	inline void get_fail(T S,int len){
		fail[1]=0;
		for(int i=2,j;i<=len;++i){
			for(j=fail[i-1];j&&S[j+1]!=S[i];j=fail[j]);
			fail[i]= S[j+1]==S[i]?++j:0;
		}
	}
	template<typename T>
	inline int match(T A,int lenA,T B,int lenB){
		//count how many times does B appear in A
		get_fail(B,lenB);
		int res=0;
		for(int i=1,j=0;i<=lenA;++i){
			while(j&&B[j+1]!=A[i])j=fail[j];
			if(B[j+1]==A[i])++j;
			if(j==lenB)++res,j=fail[j];
		}
		return res;
	}
};
