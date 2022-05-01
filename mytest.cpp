#include "Array.hpp"


using namespace cs540;


// taken
/*
a1
a2

a4
a5
a6
a7
a8
*/

bool print = false;
int main(void){
	//std::cout << std::is_convertible<int, long>::value << std::endl;

	Array<int, 6, 5, 4> a1;
	
	
	assert(typeid(Array<int, 2, 3>::ValueType) == typeid(int));
	assert(typeid(Array<long, 2>::ValueType) == typeid(long));
	
	std::cout << "assign to array--------------------------------" << std::endl;
	int k =0;
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 5; j++){
			for(int m = 0; m < 4; m++){						
				a1[i][j][m] = k++;
			}
		}
	}
	
	std::cout << "print assigned to array------------------------" << std::endl;
	k=0;
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 5; j++){
			for(int m = 0; m < 4; m++){
				k = a1[i][j][m];		
				if(print){				
					std::cout << k << std::endl;
				}
			}
		}
	}
	
	std::cout << "Exception Test---------------------------------" << std::endl;
	try{	
		k = a1[5][4][4];	
		//std::cout << a1[5][4][4] << std::endl;
	}
	catch(OutOfRange& e){
		std::cout << "Successfully caught" << std::endl;
		std::cout << e.what() << std::endl;
	}
	
	
	std::cout << "CopyCtor --------------------------------------" << std::endl;
	Array<int, 6, 5, 4> a2(a1);	
	std::cout << "print cpyConstructed----(if print==true)-------" << std::endl;
	k=0;
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 5; j++){
			for(int m = 0; m < 4; m++){
				k = a2[i][j][m];	
				if(print){
					std::cout << k << std::endl;
				}
			}
		}
	}
	
	
	std::cout << "cpyCtor equality check-------------------------" << std::endl;	
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 5; j++){
			for(int m = 0; m < 4; m++){
				assert(a1[i][j][m] == a2[i][j][m]);
			}
		}
	}
	
	std::cout << "cpyCtor success" << std::endl;
	
	std::cout << "templated cpyCtor -----------------------------" << std::endl;
	Array<long, 6, 5, 4> a4(a1);
	std::cout << "templated cpyCtor equality check---------------" << std::endl;	
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 5; j++){
			for(int m = 0; m < 4; m++){
				if(print){				
					std::cout << a4[i][j][m] << " " << a1[i][j][m] << std::endl;			
				}
				assert(a4[i][j][m] == a1[i][j][m]);
			}
		}
	}
	std::cout << "success" << std::endl;
	//return 0;
	std::cout << "operator= -------------------------------------" << std::endl;
	Array<int, 2, 3, 4> a5, a6;
	k=0;
	int z = 100;	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			for(int m = 0; m < 4; m++){
				a5[i][j][m] = k++;
				a6[i][j][m] = z--;
			}
		}
	}
	
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			for(int m = 0; m < 4; m++){
				if(print){				
					std::cout << a5[i][j][m] << " " << a6[i][j][m] << std::endl;
				}
				assert(a5[i][j][m] != a6[i][j][m]);
			}
		}
	}
	std::cout << "a5 = a6 ---------------------------------------" << std::endl;
	a5 = a6;
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			for(int m = 0; m < 4; m++){
				if(print){
					std::cout << a5[i][j][m] << " " << a6[i][j][m] << std::endl;
				}
				assert(a5[i][j][m] == a6[i][j][m]);
			}
		}
	}
	
	std::cout << "success" << std::endl;
	std::cout << "a7(long), a8(int)------------------------------" << std::endl;
	Array<long, 2, 3, 4> a7;
	Array<int, 2, 3, 4> a8;
	k=0;
	z=100;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			for(int m = 0; m < 4; m++){
				a7[i][j][m] = k++;
				a8[i][j][m] = z--;
			}
		}
	}
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			for(int m = 0; m < 4; m++){
				if(print){
					std::cout << a7[i][j][m] << " " << a8[i][j][m] << std::endl;
				}
				assert(a7[i][j][m] != a8[i][j][m]);
			}
		}
	}
	std::cout << "a7(long) = a8(int)-----------------------------" << std::endl;
	a7 = a8;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			for(int m = 0; m < 4; m++){
				if(print){
					std::cout << a7[i][j][m] << " " << a8[i][j][m] << std::endl;
				}
				assert(a7[i][j][m] == a8[i][j][m]);
			}
		}
	}
	std::cout << "success" << std::endl;

	std::cout << "FirstDimensionIterator begin()-----------------" << std::endl;
	//auto a7itBeg = a7.fmbegin(); 			//iterators are tested in provided test
	std::cout << "FirstDim operator* ----------------------------" << std::endl;


	

	//print = true;
	
	std::cout << "fmget()----------------------------------------" << std::endl;
	long a7fmg = a7.fmget((2*3*4)-1);
	if(print){
		std::cout << a7[1][2][3] << " " << a7fmg << std::endl;
	}
	assert(a7[1][2][3] == a7fmg);
	long a7idx;
	k = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			for(int m = 0; m < 4; m++){
				a7idx = a7[i][j][m];
				a7fmg = a7.fmget(k);			
				if(print){
					std::cout << a7idx << " " << a7fmg << std::endl;
				}
				assert(a7idx == a7fmg);
				k++;
			}
		}
	}
	std::cout << "success" << std::endl;

/* 				this was something used when looking into column major ordering
	k=0;
	Array<int, 2, 2, 4> zz;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			for(int m = 0; m < 4; m++){
				zz[i][j][m] = k++;
			}
		}
	}
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 2; j++){
			for(int m = 0; m < 2; m++){
				std::cout << zz[m][j][i] << std::endl;
			}
		}
	}
*/	
	return 0;
} 
