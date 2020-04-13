#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
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
				if (arry[i] > arry[j]){
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
				if (arry[min] > arry[j])
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
			while (j>=0 && arry[j] > tmp){
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
				while(k-i >= 0 && arry[k - i] > tmp){
					arry[k] = arry[k - i];
					k -= i;
				}
				arry[k] = tmp;
			}
		}
		return SORT_SUCCESS;
	}
	
	sort_status merge_sort(int *left_array, int left_len, int *right_array, int right_len) {
		merge_sort(left_array, left_len);
		merge_sort(right_array, right_len);
		int tmp_left = left_len, tmp_right = right_len, sum_length = right_len + left_len;
		int *tmp_point = new int[sum_length];

		while(tmp_left > 0 && tmp_right > 0) {
			if (left_array[tmp_left-1] > right_array[tmp_right-1]){
				tmp_point[sum_length - 1] = left_array[tmp_left - 1];
				tmp_left--;
			} else {
				tmp_point[sum_length - 1] = right_array[tmp_right - 1];
				tmp_right--;
			}
			sum_length--;
		}
		while(tmp_left > 0){
			tmp_point[sum_length - 1] = left_array[tmp_left - 1];
			tmp_left--;
			sum_length--;
		}
		while(tmp_right > 0){
			tmp_point[sum_length - 1] = right_array[tmp_right - 1];
			tmp_right--;
			sum_length--;
		}

		memcpy(left_array, tmp_point, (right_len + left_len) * sizeof(int));

		free(tmp_point);
		return SORT_SUCCESS;
	}
	sort_status merge_sort(int *arry, int length=0){
		if (length < 2){
			return (length==1?SORT_SUCCESS:SORT_LEN_ERR);
		}
		int middle = length / 2;
		merge_sort(&arry[0], middle, &arry[middle], length - middle);

		return SORT_SUCCESS;
	}


	int paritition(int A[], int low, int high) {
		int pivot = A[low];
		while (low < high) {
			while (low < high && A[high] >= pivot) {
				--high;
			}
			A[low] = A[high];
			while (low < high && A[low] <= pivot) {
				++low;
			}
			A[high] = A[low];
		}
		A[low] = pivot;
		return low;
	}
	void quick_sort_sub(int A[], int low, int high)	{
		if (low < high) {
			int pivot = paritition(A, low, high);
			quick_sort_sub(A, low, pivot - 1);
			quick_sort_sub(A, pivot + 1, high);
		}
	}
	sort_status quick_sort(int *arry, int length=0){
		if (length < 2){
			return (length==1?SORT_SUCCESS:SORT_LEN_ERR);
		}
		quick_sort_sub(arry, 0, length);

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
	int gen_cnt = 1000000;
	int *arry = new int[gen_cnt];
	srand(clock());
	for (int i=0; i<gen_cnt; i++){
		arry[i] = rand();
	}
	 w3ee q4
	/*
	cout<< "Origin:";
	for (int i=0; i<gen_cnt; i++)
		cout<< arry[i]<<" ";
	cout<<endl;*/
	
	sort_status status;
	int *tmp = new int[gen_cnt];
	
	memcpy(tmp, arry, gen_cnt * sizeof(int));
	startTime = clock();//count start
	//status = sort.bubble_sort(tmp, gen_cnt);
	endTime = clock();//count end
	cout <<"bubble_sort Res:"<<status<<" ["<< (double)(endTime-startTime)/CLOCKS_PER_SEC*1000<<"ms]"<< endl;

	memcpy(tmp, arry, gen_cnt * sizeof(int));
	startTime = clock();//count start
	//status = sort.select_sort(tmp, gen_cnt);
	endTime = clock();//count end
	cout <<"select_sort Res:"<<status<<" ["<< (double)(endTime-startTime)/CLOCKS_PER_SEC*1000<<"ms]"<< endl;

	memcpy(tmp, arry, gen_cnt * sizeof(int));
	startTime = clock();//count start
	//status = sort.insert_sort(tmp, gen_cnt);
	endTime = clock();//count end
	cout <<"insert_sort Res:"<<status<<" ["<< (double)(endTime-startTime)/CLOCKS_PER_SEC*1000<<"ms]"<< endl;

	memcpy(tmp, arry, gen_cnt * sizeof(int));
	startTime = clock();//count start
	status = sort.shell_sort(tmp, gen_cnt);
	endTime = clock();//count end
	cout <<"shell_sort Res:"<<status<<" ["<< (double)(endTime-startTime)/CLOCKS_PER_SEC*1000<<"ms]"<< endl;

	memcpy(tmp, arry, gen_cnt * sizeof(int));
	startTime = clock();//count start
	status = sort.merge_sort(tmp, gen_cnt);
	endTime = clock();//count end
	cout <<"merge_sort Res:"<<status<<" ["<< (double)(endTime-startTime)/CLOCKS_PER_SEC*1000<<"ms]"<< endl;

	memcpy(tmp, arry, gen_cnt * sizeof(int));
	startTime = clock();//count start
	status = sort.quick_sort(tmp, gen_cnt);
	endTime = clock();//count end
	cout <<"quick_sort Res:"<<status<<" ["<< (double)(endTime-startTime)/CLOCKS_PER_SEC*1000<<"ms]"<< endl;

	/*
	for (int i=0; i<gen_cnt; i++)
		cout<< tmp[i]<<" ";
	cout<<endl;*/
	
	free(arry);
	free(tmp);
	return 0;
}


