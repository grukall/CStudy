#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int partition(int A[], int p, int r);
int select(int A[], int p, int r, int i);
int linearSelect(int A[], int p, int r, int i);
void heapSort(int A[], int n);
void buildHeap(int A[], int n);
void heapify(int A[], int k, int n);


int A[50000];

int main(void) {
   int i;
   int n = 20; //�ݺ�Ƚ�� ������ ��
   clock_t start_clock, end_clock, diff_clock;
   double ex_time;

   srand(time(NULL));
   for (int i = 0; i < 50000; i++) { //�迭�� ������ �� ����
      A[i] = rand() % 50000;
   }

   start_clock = clock(); //����ð� ���� ����
   for (i = 0; i < n; i++) { 
       int total = select(A, 0, 49999, 10);
       printf("���� �˰��� ��� : %d\n", total);
   }
   end_clock = clock();

   diff_clock = end_clock - start_clock;
   printf("%d�� �ݺ��ϴµ� �ɸ� �ð� : %dŬ��\n", n, diff_clock);
   ex_time = (double)(diff_clock) / CLOCKS_PER_SEC;
   printf("���� �˰��� ��� ����ð� : %lf��\n", ex_time);

   return 0;
}


/*
int A[13]={3,11,7,8,9,1,2,0,5,6,10,15,16};
int B[5] = { 99,55,77,22,11 };
int C[7] = { 8,7,6,4,3,2,1};

int main(void) {

   int total2 = linearSelect(C, 0, 6, 3);
   printf("B[5] ��� : %d\n", total2);

   return 0;
}
*/

//å�� ��Ƽ��(����)�Լ�
int partition(int A[], int p, int r) {
   int x = A[r];
   int i = p - 1;
   int temp;
   for (int j = p; j < r; j++) {
      if (A[j] <= x) {
         i++;
         temp = A[i];
         A[i] = A[j];
         A[j] = temp;
      }
   }
   temp = A[i + 1];
   A[i + 1] = A[r];
   A[r] = temp;
   return i + 1;
}


//(5-1)��� �����ð� ���� �˰���
int select(int A[], int p, int r, int i) {
   if (p == r) return A[p];
   int q = partition(A, p, r);
   int k = q - p + 1;
   if (i == k) return A[q];
   else if (i < k) return select(A, p, q - 1, i);
   else return select(A, q + 1, r, i - k);
}

//(5-2)�־��� ��쿡�� �����ð��� �����ϴ� �˰���
int linearSelect(int A[], int p, int r, int i) {
   int n = r - p + 1; //������ �� ��
   if (n <= 5) return select(A, p, r, i);

   int groupNum = (n + 4) / 5; //�׷� ����

   int* m = (int*)calloc(groupNum, sizeof(int)); //�߾Ӱ��� ������ 1���� �迭
   int** groups = (int**)calloc(groupNum, sizeof(int*)); //�׷�� ������ 2���� �迭


      for (int i = 0; i < groupNum; i++) { //������ �׷쿡 ���� ����ŭ �迭ũ�� �Ҵ�
         if (i < groupNum - 1) { 
            groups[i] = (int*)calloc(5, sizeof(int));
         }
         else { //������ �׷츸 ��������ŭ ũ�� �Ҵ�
            groups[i] = (int*)calloc(n % 5, sizeof(int));
         }
      }

      for (int i = 0; i < n; i++) { //���� ������ �Ҵ��� ������ ���� ä�� ����
         int group_Index = i / 5;
         int element_Index = i % 5;
         groups[group_Index][element_Index] = A[i]; 
      }

      for (int i = 0; i < groupNum; i++) { //�� �׷���� ������
         if (i < groupNum - 1) {
            heapSort(groups[i], 5);
         }
         else {
            heapSort(groups[i], n % 5);
         }
      }

      for (int i = 0; i < groupNum; i++) { //�� �׷���� �߾Ӱ����� m�迭�� ����
         if (i < groupNum - 1) {
            m[i] = groups[i][2];
         }
         else {
            int groupElements = n % 5;
            m[i] = groups[i][groupElements / 2];
         }
      }
   

   int M = linearSelect(m, 0, groupNum - 1, (groupNum + 1) / 2); //�߾Ӱ����� �߾Ӱ�
   int q= partition(A, 0, M);
   int k= q - p + 1; //���ؿ��Ұ� ��ü���� k��° ���� �������� �ǹ�

   if (i == k) return A[q];
   else if (i < k) return linearSelect(A, p, q - 1, i); 
   else return linearSelect(A, q + 1, r, i - k);

   //�޸� ����
   free(m);
   for (int i = 0; i < groupNum; i++) 
      free(groups[i]);
   free(groups);
}


void heapSort(int A[], int n) {
   buildHeap(A, n);

   for (int i = n - 1; i > 0; i--) {
      int temp = A[0];
      A[0] = A[i];
      A[i] = temp;

      heapify(A, 0, i);
   }
}

void buildHeap(int A[], int n) {
   for (int i = n / 2-1 ; i >= 0; i--) {
      heapify(A, i, n);
   }
}

void heapify(int A[], int k, int n) {
   int left = 2 * k + 1; 
   int right = 2 * k + 2; 
   int smaller = k;

   if (left < n && A[left] > A[smaller]) {
      smaller = left;
   }
   if (right < n && A[right] > A[smaller]) {
      smaller = right;
   }

   if (smaller != k) {
      int temp = A[k];
      A[k] = A[smaller];
      A[smaller] = temp;
      heapify(A, smaller, n);
   }
}
