#include<stdio.h>
#include<stdlib.h>
void quicksort(int * begin,int * end){
	if(begin+1>=end){
		return;
	}
	int *left=begin;
	int *right=end-1;
	int key=*right;
	while(left<right){
		while(left<right&&key>*left){
			left++;
		}
		*right=*left;
		while(left<right&&key<=*right){
			right--;
		}
		*left=*right;
	}
	*left=key;
	quicksort(begin,left);
	quicksort(left+1,end);
}
int main(){
	int arr[100000];
	for(int i=0;i<100000;i++){
		arr[i]=rand()%100000;
	}
	quicksort(arr,arr+100000);
	for(int j=0;j<100000;j++){
		printf("%d ",arr[j]);
	}
}
