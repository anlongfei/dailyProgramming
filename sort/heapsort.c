#include <stdio.h>
//array是待调整的堆数组，i是待调整的数组元素的位置，nlength是数组的长度
//本函数功能是：根据数组array构建大根堆
void HeapAdjust(int array[],int s,int nLength)
{
	int tmp = array[s];
	int j=0;
	for(j = 2*s; j<=nLength; j*=2){
		if(j<nLength && array[j]<array[j+1])
			j = j+1;
		if(array[j] < tmp)
			break;
		array[s] = array[j];
		s = j;
	}
	array[s] = tmp;
	int i;
}
//堆排序算法
void HeapSort(int array[],int length)
{
	int i;
	//调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素
	for(i=(length-1)/2; i>0; i--)
		HeapAdjust(array,i,length-1);

	//从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
	for(i=length-1;i>0;--i)
	{
		//把第一个元素和当前的最后一个元素交换，
		//保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
		int tmp = array[i];
		array[i] = array[1];
		array[1] = tmp;
		//不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
		HeapAdjust(array,1,i-1);
		int j=0;
	}
}
int main()
{
	int i;
	int num[]={0,6,8,3,9,1,4,7,0,5,2};
	printf("before heapSort:\n");
	for(i=0;i<sizeof(num)/sizeof(int);i++)
	{
		printf("%d ",num[i]);
	}
	HeapSort(num,sizeof(num)/sizeof(int));
	printf("\nafter heapSort:\n");
	for(i=0;i<sizeof(num)/sizeof(int);i++)
	{
		printf("%d ",num[i]);
	}
	printf("\nok\n");
	return 0;
}
