#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;


#define foo(arr) (sizeof(arr)/sizeof(arr[0]))


typedef enum{
	SORT_SUCCESS = 0,
	SORT_LEN_ERR = -1,
	SORT_ARRY_ERR = -2,
}sort_status;

typedef enum{
	MIN_TO_MAX = 0,
	MAX_TO_MIN = 1,
}sort_order;

class ken_sort{
private:
	sort_order order;
	bool is_exchange_necessary(int a, int b){
		if (order == MIN_TO_MAX && a > b){
			return true;
		} else if (order == MAX_TO_MIN && a < b){
			return true;
		}
		return false;
	}
	void exchange(int *a, int *b){
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}
public:
	ken_sort(sort_order tmp=MIN_TO_MAX){
		order = tmp;
	}
	sort_status bubble_sort(int *arry, int length=0){
		if (length < 2){
			return (length==1?SORT_SUCCESS:SORT_LEN_ERR);
		}
		for (int i=0; i<length-1; i++){
			for(int j=i+1; j<length; j++){
				if (is_exchange_necessary(arry[i], arry[j])){
					exchange(&arry[i], &arry[j]);
				}
			}
		}
		return SORT_SUCCESS;
	}
	
	sort_status select_sort(int *arry, int length=0){
		if (length < 2){
			return (length==1?SORT_SUCCESS:SORT_LEN_ERR);
		}
		for (int i=0; i<length-1; i++){
			int min = i;
			for (int j=i+1; j<length; j++){
				if (is_exchange_necessary(arry[min], arry[j]))
					min = j;
			}
			if (i != min){
				exchange(&arry[i], &arry[min]);
			}
		}
		return SORT_SUCCESS;
	}
	sort_status insert_sort(int *arry, int length=0){
		if (length < 2){
			return (length==1?SORT_SUCCESS:SORT_LEN_ERR);
		}
		for (int i=1; i<length; i++){
			int j = i - 1, tmp = arry[i];
			while (j>=0 && is_exchange_necessary(arry[j], tmp)){
				arry[j + 1] = arry[j];
				j--;
			}
			arry[j + 1] = tmp;
		}
		return SORT_SUCCESS;
	}
	
	sort_status shell_sort(int *arry, int length=0){
		if (length < 2){
			return (length==1?SORT_SUCCESS:SORT_LEN_ERR);
		}
		for (int i=length/2; i>0; i/=2){
			for(int j=i; j<length; j++){
				int k = j, tmp = arry[j];
				while(k-i >= 0 && is_exchange_necessary(arry[k - i], tmp)){
					arry[k] = arry[k - i];
					k -= i;
				}
				arry[k] = tmp;
			}
		}
		return SORT_SUCCESS;
	}
	
	sort_status merge_sort(int *arry, int length=0){
		if (length < 2){
			return (length==1?SORT_SUCCESS:SORT_LEN_ERR);
		}
		
		
		return SORT_SUCCESS;
	}
};

/*
data length: 4 bytes signed int
array length: 10000
array order: rand
time costs:
	bubble_sort:  0.45s
	select_sort:  0.22s
	insert_sort:  0.13s
	shell_sort:   0.0033s

could avoid:
	is_exchange_necessary: 0.0.0006s
	exchange: 0.0008s
*/


int main(int argc, char* argv[])
{
	ken_sort sort;
	clock_t startTime,endTime;
	int gen_cnt = 10;
	int *arry = (int *)malloc(gen_cnt * sizeof(int));
	srand(clock());
	for (int i=0; i<gen_cnt; i++){
		arry[i] = rand()%100;
	}
	
	/**/
	cout<< "Origin:";
	for (int i=0; i<gen_cnt; i++)
		cout<< arry[i]<<" ";
	cout<<endl;
	
	startTime = clock();//count start
	//sort_status status = sort.bubble_sort(arry, gen_cnt);
	//sort_status status = sort.select_sort(arry, gen_cnt);
	//sort_status status = sort.insert_sort(arry, gen_cnt);
	//sort_status status = sort.shell_sort(arry, gen_cnt);
	sort_status status = sort.merge_sort(arry, gen_cnt);
	endTime = clock();//count end
	
	cout <<"Sort Res:"<<status<<" ["<< (double)(endTime-startTime)/CLOCKS_PER_SEC<<"s]"<< endl;
	/**/
	for (int i=0; i<gen_cnt; i++)
		cout<< arry[i]<<" ";
	cout<<endl;
	
	free(arry);
	return 0;
}


