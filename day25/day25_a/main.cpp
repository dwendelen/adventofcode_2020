#include <iostream>

//long x1=5764801;
//long x2=17807724;
long x1=8184785;
long x2=5293040;

int main(){
	long i=1;
	int j =0;
	long s=1;
	while(true){
		++j;
		i=i*7;
		i=i%20201227;
		s=s*x2;
		s=s%20201227;
		if(i== x1){
			std::cout << j << std::endl;
			break;
		}
	
	}
	//long s =x2;
	//for(int k=0;k<j;++k){
	//	s=s*7;
	//	s=s%20201227;
	//}
	std::cout << s << std::endl;
}
