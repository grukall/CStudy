#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_number t_number;
typedef struct s_number
{
    int num;
    t_number *right;
    t_number *left;
}t_number;

t_number    *make_number(int n, int *biggest_index);
int         check_index(int num, int biggest_index);
void        print_rand_number(t_number *rand_number);
void        error(void);
void        radix_sort(t_number *rand_number, int biggest_index, int n);
int         move_to_radix(t_number *rand_number, t_number *tail[], int i);
void        make_rand_number(t_number *rand_number, t_number *head[], t_number *tail[], int n);
void        free_head_tail(t_number *head[], t_number *tail[]);

int main(int argc, char **argv)
{
    if (argc != 3)
        error();

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    t_number *rand_number;
    int biggest_index = 1;

    srand(time(NULL));

    printf("------radix sort------\n");
    for (int i = 0; i < m; i++)
    {
        rand_number = make_number(n, &biggest_index); //�������� n�� ���� �� ���� �ִ� �ڸ� �� ���ϱ�
        if (!rand_number)
            error();
        printf("[%d]\n", i + 1);
        printf("before : ");
        print_rand_number(rand_number);
        radix_sort(rand_number, biggest_index, n); //�������
        printf("after : ");
        print_rand_number(rand_number);
        free(rand_number);

        printf("--------------------\n");
    }
    return (0);
}

void    radix_sort(t_number *rand_number, int biggest_index, int n)
{
    t_number    *head[10];
    t_number    *tail[10];

    for (int i = 1; i <= biggest_index; i *= 10)
    {
        if (n == 1)
            break ;
        for (int j = 0; j < 10; j++) //0���� 9������ �ڸ����� �ش��ϴ� 10���� ���Ḯ��Ʈ�� ���� �޸� �Ҵ����� �����Ѵ�
        {
            head[j] = (t_number *)malloc(sizeof(t_number) * 2);
            if (!head[j])
                error(); 
            head[j]->right = &head[j][1];
            tail[j] = head[j]->right;
            tail[j]->left = head[j];  // �� ���Ḯ��Ʈ�� ���(Head)�� ����(Tail)�� ������ �ִ�
        }
        if(move_to_radix(rand_number, tail, i)) //���ڿ� �´� ���Ḯ��Ʈ�� ����
        {
            free_head_tail(head, tail);
            free(rand_number);
            error();
        }
        free(rand_number);
        rand_number = (t_number *)malloc(sizeof(t_number) * n);
        if (!rand_number)
        {
            free_head_tail(head, tail);
            error();
        }
        make_rand_number(rand_number, head, tail, n); // ���Ḯ��Ʈ�� �ٽ� ��ġ��
    }
}

int move_to_radix(t_number *rand_number, t_number *tail[], int i)
{
    t_number    *temp = rand_number;
    t_number    *temp2;
    int index;

    while (temp != NULL)
    {
        index = (temp->num / i) % 10;
        temp2 = (t_number *)malloc(sizeof(t_number) * 1);  //�ش��ϴ� �ڸ� �� ��忡 ��带 �����Ҵ�
        if (!temp2)
            return (1);
        temp2->num = temp->num;
        temp2->right = tail[index];
        temp2->left = tail[index]->left;
        tail[index]->left->right = temp2;
        tail[index]->left = temp2;
        temp = temp->right;
    }
    return (0);
}

void    make_rand_number(t_number *rand_number, t_number *head[], t_number *tail[], int n)
{
    t_number *temp = rand_number;
    t_number *temp2;
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        while (i < 10 && head[i]->right == tail[i])
            i++;
        if (i == 10)
            break ;
        temp2 = head[i]->right;
        while (temp2 != tail[i] && j < n - 1)
        {
            temp->num = temp2->num;
            temp->right = &rand_number[j++ + 1];
            temp->right->left = temp;
            temp = temp->right;
            temp2 = temp2->right;
        }
    }
    temp->num = temp2->num;
    temp->right = NULL;
    free_head_tail(head, tail);
}

void    free_head_tail(t_number *head[], t_number *tail[])
{
    for (int i = 0; i < 10; i++)
    {
        if (head)
            free(head[i]);
        head[i] = NULL;
        if (tail)
            free(tail[i]);
        tail[i] = NULL;
    }
}

void    print_rand_number(t_number *rand_number)
{
    t_number *temp = rand_number;

    while (temp != NULL)
    {
        printf("%d ", temp->num);
        temp = temp->right;
    }
    printf("\n\n");
}

void    error(void)
{
    printf("error\n");
    exit (1);
}

t_number    *make_number(int n, int *biggest_index)
{
    t_number *rand_number = (t_number *)malloc(sizeof(t_number) * n); // n���� ������ �����ϱ� ���� ���� �޸� �Ҵ��� ���� ���Ḯ��Ʈ�� ����
    if (!rand_number)
        return (NULL);
    t_number *temp = rand_number;

    for (int i = 0; i < n - 1; i++)
    {
        temp->num = rand() % 10000;
        *biggest_index = check_index(temp->num, *biggest_index);
        temp->right = &rand_number[i + 1];
        temp->right->left = temp;
        temp = temp->right;
    }
    temp->num = rand() % 10000;
    *biggest_index = check_index(temp->num, *biggest_index);
    temp->right = NULL;
    return (rand_number);
}

int check_index(int num, int biggest_index)
{
    int index = 1;
    if (num == 0)
        return (biggest_index);
    while (1)
    {
        if (num / index < 10)
            break ;
        index *= 10;
    }
    if (biggest_index < index)
        return (index);
    return (biggest_index);
}