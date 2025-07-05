#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;
//평균 선형시간 선택 알고리즘 코드이다. 총 수가 5개 이하라면 이 함수를 사용한다.
int five_1_partition(int[], int, int);
int five_1_select(int[], int, int, int);
//최악의 경우 선형시간 선택 알고리즘 코드이다.
void five_2_heapify(int [], int, int);
void five_2_buildHeap(int[], int);
void five_2_heapSort(int[], int);
int getMIndex(int[], int, int);
int five_2_select(int[], int, int, int);
int five_2_partition(int[], int, int, int);



int main(void){
    srand(time(NULL));
    int A[100];
    int length = 100;
    for(int i=0; i<length; i++){
        A[i] = i;
    }

    for(int i=0; i<length; i++){
        cout<<A[i]<<'\n';
    }
    cout<<'\n';
    cout<<'\n';
    cout<<'\n';
    cout<<'\n';
    int k = five_2_select(A, 0, length-1, 15);

    for(int i=0; i<length; i++){
        cout<<A[i]<<'\n';
    }
    
    cout<<'\n';
    cout<<'\n';

    cout<<k<<'\n';
    
    return 0;
}





int five_1_partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            ++i;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}

int five_1_select(int A[], int p, int r, int i)
{ 
    if (p == r)
    {
        return A[p];
    }
    int q = five_1_partition(A, p, r);
    int k = q - p + 1;

    if (i < k)
    {
        five_1_select(A, p, q - 1, i);
    }
    else if (i == k)
    {
        return A[q];
    }
    else
    {
        return five_1_select(A, q + 1, r, i - k);
    }
}





void five_2_heapify(int A[], int k, int n){
    
    int left = 2*k+1;
    int right = 2*k +2;
    
    int bigger;
    if(right <= n){
        if(A[left] > A[right]){
            bigger = left;
        }
        else{
            bigger = right;
        }
    }
    else if(left <= n){
        bigger = left;
    }
    else return;

    if(A[bigger] > A[k]){
        int tmp = A[k];
        A[k] = A[bigger];
        A[bigger] = tmp;

        five_2_heapify(A, bigger, n);
    }
}

void five_2_buildHeap(int A[], int n){
    for(int i=(n)/2; i>= 0; i--){
        five_2_heapify(A, i, n);
    }
}

void five_2_heapSort(int A[], int n){
    five_2_buildHeap(A, n-1);
    for(int i=n-1; i>0; i--){
        int tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        five_2_heapify(A, 0, i-1);
    }
}

int five_2_select(int A[], int p, int r, int i){
    //r-p 가 5개 이하라면, 기존 1번 알고리즘을 수행한다.
    //5개의 원소를 가지는 그룹들로 분할을 한다.
    //각 그룹을 힙정렬해주고, 힙정렬을 통해서 중간값(3번째 값) 을 구한다.
    //중간값들의 중간값을 재귀적으로 구해준다.
    //그 중간값으로 전체 배열을 나눠주고, 나눠진 곳 중에서 옳바론 쪽을 선택한다.

    int length = r-p+1;
    int midGroupLength = (length+4)/5;
    int groupMod = length%5;

    if(length <= 5){ // 1번식
       return five_1_select(A, p, r, i);
    }
    
    for(int j=0; j<length; j+= 5){ // 그룹에 따른 분배 및 힙정렬
        if(j/5 == midGroupLength-1){ //마지막 그룹이라면, 
            if(groupMod == 0){ // 5개짜리 묶음이라면,
                five_2_heapSort(&A[j], 5);
            }
            else{ // 그게 아니라면, 남은 갯수를 가지고 정렬한다.
                five_2_heapSort(&A[j], groupMod);
            }
        }
        else{
            five_2_heapSort(&A[j], 5);
        }
    }
    int midGroup[midGroupLength];
    //여기까지는 잘 수행된다.
    
    for(int j=0; j<midGroupLength; j++){
        
        if(j == midGroupLength-1){ //마지막 요소라면,
            if(groupMod != 0){ // 그 중에서 5개짜리가 아니라면,
                if(groupMod >= 3){ // 3 개 이상짜리의 묶음이라면,
                    midGroup[j] = A[j*5 + 2];
                }
                else{ // 그보다 적게 남았다면,
                    midGroup[j] = A[j*5 + groupMod];
                }
            }
            else{
                midGroup[j] = A[j*5 + 2];
            }
        } 
        else{
            midGroup[j] = A[j*5 + 2];
        }
    }
    //여기까지 중간값 배열 선정.
    int M = five_2_select(midGroup, 0, midGroupLength-1, midGroupLength/2); //파티션에 사용할 중간값
    
    int M_index = getMIndex(A, length, M); //M값의 인덱스를 찾아냄.

    //파티션 구성
    int afterP_1 = five_2_partition(A, p, r, M_index);
    int afterP_2 = afterP_1 -p+1;
    //if 문을 재귀 돌림
    if(i<afterP_1){
        return five_2_select(A, p,afterP_1 -1, i);
    }
    else if(i == afterP_2){
        return A[afterP_1];
    }
    else{
        return five_2_select(A,afterP_1+1, r, i-afterP_2);
    }
}

int five_2_partition(int A[], int p, int r, int M){
    int tem = M;
    M = r;
    r = tem;
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            ++i;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}

int getMIndex(int A[], int length, int M){
    for(int i=0; i<length; i++){
        if(A[i] == M){
            return i;
        }
    }
    cout<<"getMIndex error"<<'\n';
    return -1;
}