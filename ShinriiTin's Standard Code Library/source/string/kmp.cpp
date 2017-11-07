template<size_t size>
struct Kmp{
	//indexed from 0
	int fail[size];
	template<typename T>
	inline void get_fail(T S,int len){
		fail[0]=-1;
		for(int i=1,j;i<len;++i){
			for(j=fail[i-1];~j&&S[j+1]!=S[i];j=fail[j]);
			fail[i]= S[j+1]==S[i]?++j:-1;
		}
	}
	template<typename T>
	inline int match(T A,int lenA,T B,int lenB){
		//count how many times does B appears in A
		get_fail(B,lenB);
		int res=0;
		for(int i=0,j=-1;i<lenA;++i){
			while(~j&&B[j+1]!=A[i])j=fail[j];
			if(B[j+1]==A[i])++j;
			if(j==lenA-1)++res,j=-1;
		}
		return res;
	}
};

