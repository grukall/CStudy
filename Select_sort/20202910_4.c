#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <windows.h>

int     select_v1(int A[], int p, int r, int i);
int     partition_v1(int A[], int p, int r);
int     select_v2(int A[], int p, int r, int i);
int     partition_v2(int A[], int first_index, int last_index, int M);
int     find_index(int A[], int length, int value);
int     **make_groups(int A[], int group_count, int length);
int     *make_middle_array(int **groups, int group_count, int last_group_count);
void    heapify(int A[], int k, int n);
void    heap_sort(int A[], int n);
void    buildHeap(int A[], int n);

void	*ft_memcpy(int *dest, const int *source, size_t num)
{
	if (!source && !dest)
		return (dest);
	if (num)
	{
		while (num--)
		dest[num] = source[num];
	}
	return (dest);
}

void    print_arr(int A[], int size)
{
    for(int i = 0; i < size - 1; i++)
        printf("%-2d ", A[i]);
    printf("%-2d\n", A[size - 1]);
}

int second_version_select_Alogrithm(int A[], int p, int r, int i)
{
    return select_v2(A, p, r, i - 1);
}

int select_v2(int A[], int p, int r, int i)
{
    int length = r - p + 1;
    int group_count;
    int last_group_count = 0;
    int **groups;
    int *middle_arr;
    int M;
    int M_index;
    int M_how_small_is_it;

    //print_arr(&A[p], length);
    //print_arr(&A[p], length);
     if (length <= 5)
        return select_v1(A, p, r, i);

    if (length % 5 == 0)
        group_count = length / 5;
    else
    {
        group_count = length / 5 + 1;
        last_group_count = length % 5;
    }

    groups = make_groups(&A[p], group_count, length);

    middle_arr = make_middle_array(groups, group_count, last_group_count);

    M = select_v2(middle_arr, 0, group_count - 1, group_count / 2);
    free(middle_arr);

    M_index = partition_v2(A, p, r, M);
    M_how_small_is_it = M_index - p;

//    printf("M : A[%d], %dth, i = %d\n", M_index, M_how_small_is_it, i);
//    print_arr(&A[p], length);

    if (i < M_how_small_is_it)
        return select_v2(A, p, M_index - 1, i);
    else if (i == M_how_small_is_it)
        return A[p + M_index];
    else
        return select_v2(A, M_index + 1, r, i - (M_how_small_is_it + 1));
}

int partition_v2(int A[], int first_index, int last_index, int M)
{
    int standard_value = M;
    int length = last_index - first_index + 1;
    int standard_value_index = first_index + find_index(&A[first_index], length, standard_value);
    int least_index;
    int temp;

    if (standard_value_index == -1)
    {
        printf("someting wrong.. cant find index, value = %d\n", standard_value);
        exit(1);
    }
    least_index = first_index - 1;      //첫 번째 구역의 index
    for(int j = first_index; j <= last_index; j++)
    {
        if (A[j] <= standard_value && j != standard_value_index)     // A[j]가 standard_value보다 작으면,
        {
            temp = A[++least_index];    //least_index의 값과 서로 바꾼다.
            A[least_index] = A[j];
            A[j] = temp;
        }
    }
    temp = A[standard_value_index];               //마지막으로 standard_value와 첫 번째 구역의 값과 바꾼다.
    A[standard_value_index] = A[least_index + 1];
    A[least_index + 1] = temp;
    return least_index + 1;             //첫 번째 구역의 값 리턴
}

int find_index(int A[], int length, int value)
{
    for (int i = 0; i < length; i++)
    {
        if (A[i] == value)
            return i;
    }

    return -1;
}

int *make_middle_array(int **groups, int group_count, int last_group_count)
{
    int *temp = (int *)malloc(sizeof(int) * group_count);
    int middle_value;

    for (int i = 0; i < group_count; i++)
    {
        if (i == group_count - 1 && last_group_count)
        {
            heap_sort(groups[i], last_group_count - 1);
            middle_value = last_group_count / 2;
        }
        else
        {
            heap_sort(groups[i], 4);
            middle_value = 2;
        }
        temp[i] = groups[i][middle_value];
        free(groups[i]);
    }
    free(groups);
    return temp;
}

int **make_groups(int A[], int group_count, int length)
{
    int **groups;
    groups = (int **)malloc(sizeof(int *) * group_count);

    for (int i = 0; i < group_count; i++)
    {
        groups[i] = (int *)calloc(5, sizeof(int));
        for (int j = 0; j < 5 && ((i * 5 + j) < length); j++)
            groups[i][j] = A[i * 5 + j];
    }
    return groups;
}

int first_version_select_Algorithm(int A[], int p, int r, int i) // 1 ~ n 의 i번째
{
    return select_v1(A, p, r, i - 1);  // 0 ~ n - 1 의 i - 1번째 -> 배열 index 그대로 쓸 수 있음
}

int select_v1(int A[], int p, int r, int i)
{

    int length = r - p + 1;
    int q;
    int k;

    if (p == r) return A[p];

    q = partition_v1(A, p, r);
    k = q - p;

    if (i < k)
        return select_v1(A, p, q - 1, i);
    else if (i == k)
        return A[q];
    else
        return select_v1(A, q + 1, r, i - (k + 1));
}

int partition_v1(int A[], int first_index, int last_index)
{
    int length = last_index - first_index + 1;
    int standard_value;
    int least_index;
    int temp;

    standard_value = A[last_index];     //배열의 맨 마지막 숫자를 기준잡기
    least_index = first_index - 1;      //첫 번째 구역의 index
    for(int j = first_index; j <= last_index - 1; j++)  //standard_value 전까지 검사
    {
        if (A[j] <= standard_value)     // A[j]가 standard_value보다 작으면,
        {
            // printf("A[%d](%d) <= A[%d](%d), change A[%d] A[%d]\n", j, A[j], last_index, standard_value, least_index + 1, j);
            // print_arr(&A[first_index], length);
            temp = A[++least_index];    //least_index의 값과 서로 바꾼다.
            A[least_index] = A[j];
            A[j] = temp;
        }
    }
    // printf("change A[%d] A[%d]\n", last_index, least_index + 1);
    // print_arr(&A[first_index], length);
    temp = A[last_index];               //마지막으로 standard_value와 첫 번째 구역의 값과 바꾼다.
    A[last_index] = A[least_index + 1];
    A[least_index + 1] = temp;
    return least_index + 1;             //첫 번째 구역의 값 리턴
}

void    heapify(int A[], int k, int n)
{
    int left = 2 * k + 1;
    int right = 2 * k + 2;
    int bigger;
    int temp;

    if (right <= n)
    {
        if (A[left] < A[right])
            bigger = right;
        else
            bigger = left;
    }
    else if (left <= n)
        bigger = left;
    else return;

    if (A[bigger] > A[k])
    {
        temp = A[k];
        A[k] = A[bigger];
        A[bigger] = temp;
        heapify(A, bigger, n);
    }
}

void    buildHeap(int A[], int n)
{
    for (int i = n / 2; i >= 0; i--)
        heapify(A, i, n);
}

void    heap_sort(int A[], int n)
{
    int temp;
    int m = n - 1;

    buildHeap(A, m);
    for (int i = m; i >= 1; i--)
    {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        heapify(A, 0, i - 1);
    }
}

void fill_array_with_random_value(int A[], int length)
{
    for (int i = 0; i < length; i++)
        A[i] = rand() % length;

}

void	cycle_select_sort(int cycle, int select_sort_number)
{
    int A[20];

    int length = 500;
    int result;
    int before_result;
    int copy[500];

    srand(time(NULL));

    int select;
	clock_t clock_cycle_start, clock_cycle_end;
	int	(*f)(int *A, int p, int r, int i);

	if (select_sort_number == 1)
		f = first_version_select_Algorithm;
	else if (select_sort_number == 2)
		f = second_version_select_Alogrithm;

	clock_cycle_start = clock();
	for (int i = 1; i <= cycle; i++)
	{
		fill_array_with_random_value(A, length);
        ft_memcpy(copy, A, length);
        heap_sort(copy, length);
		for (select = 1; select <= length / 2; select++)
			f(A, 0, length - 1, select);
	}
	clock_cycle_end = clock();
	if (select_sort_number == 1)
		printf("first_version_select_Algorithm");
	else if (select_sort_number == 2)
		printf("second_version_select_Algorithm");
	printf(" performed total %d cycle in %.2f seconds.\n\n", cycle, (float)(clock_cycle_end - clock_cycle_start)/CLOCKS_PER_SEC);
}

int main(void)
{
	cycle_select_sort(100, 1);
	cycle_select_sort(200, 1);
	cycle_select_sort(300, 1);
	cycle_select_sort(400, 1);
	cycle_select_sort(500, 1);
	cycle_select_sort(600, 1);
	cycle_select_sort(700, 1);
	cycle_select_sort(800, 1);
	cycle_select_sort(900, 1);
	cycle_select_sort(1000, 1);

	cycle_select_sort(100, 2);
	cycle_select_sort(200, 2);
	cycle_select_sort(300, 2);
	cycle_select_sort(400, 2);
	cycle_select_sort(500, 2);
	cycle_select_sort(600, 2);
	cycle_select_sort(700, 2);
	cycle_select_sort(800, 2);
	cycle_select_sort(900, 2);
	cycle_select_sort(1000, 2);
}