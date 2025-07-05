#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct card
{
    char shape;
    char num[3];
};

void    input_directly(struct card mycard[], _Bool(*pocker_hands[12])(struct card mycard[]), char **pocker_hands_name_ko);
void    make_randomly(struct card mycard[], char **number, char *shape_ar, _Bool(*pocker_hands[12])(struct card mycard[]), char **pocker_hands_name);
_Bool   check_card(struct card mycard[], int i);

_Bool royal_straight_flush(struct card mycard[]);
_Bool back_straight_flush(struct card mycard[]);
_Bool straight_flush(struct card mycard[]);
_Bool four_card(struct card mycard[]);
_Bool full_house(struct card mycard[]);
_Bool flush(struct card mycard[]);
_Bool mountain(struct card mycard[]);
_Bool back_straight(struct card mycard[]);
_Bool straight(struct card mycard[]);
_Bool triple(struct card mycard[]);
_Bool two_pair(struct card mycard[]);
_Bool one_pair(struct card mycard[]);

int main()
{
    int         menu;
    struct card mycard[5];
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    char shape_ar[5] = "CHDS";
    _Bool   (*pocker_hands[12])(struct card mycard[]) = {
        royal_straight_flush,
        back_straight_flush,
        straight_flush,
        four_card,
        full_house,
        flush,
        mountain,
        back_straight,
        straight,
        triple,
        two_pair,
        one_pair
    };

    char    *pocker_hands_name[12] = {
        "royal_straight_flush",
        "back_straight_flush",
        "straight_flush",
        "four_card",
        "full_house",
        "flush",
        "mountain",
        "back_straight",
        "straight",
        "triple",
        "two_pair",
        "one_pair"
    };

    char    *pocker_hands_name_ko[12] = {
        "�ξ� ��Ʈ����Ʈ �÷���",
        "�� ��Ʈ����Ʈ �÷���",
        "��Ʈ����Ʈ �÷���",
        "�� ī��",
        "Ǯ �Ͽ콺",
        "�÷���",
        "����ƾ",
        "�� ��Ʈ����Ʈ",
        "��Ʈ����Ʈ",
        "Ʈ����",
        "�� ���",
        "�� ���"
    };

    srand(time(NULL));

    printf("1. ���� �Է�    2. ���� ����\n\n");
    while (1)
    { 
        printf("��ȣ�� �Է��ϼ��� : ");
        scanf("%d", &menu);
        getchar();                     //???? ????
        if (menu == 1)
            input_directly(mycard, pocker_hands, pocker_hands_name_ko);
        else if (menu == 2)
            make_randomly(mycard, number, shape_ar, pocker_hands, pocker_hands_name);
        else if (menu == 3)
            break;
        else
        {
            printf("�߸��� �޴���ȣ �Դϴ�\n");
            continue;
        }
        printf("===========================================================\n");
        printf("1. ���� �Է�    2. ���� ����    3. ����\n\n");
    }
    return 0;
}

_Bool   check_card(struct card mycard[], int i)
{
    for (int j = 0; j < i; j++)
    {
        if (mycard[i].shape == mycard[j].shape && !strcmp(mycard[i].num, mycard[j].num))
            return (0);
    }
    return (1);
}

void	change_card(struct card mycard[], int first, int second)
{
	char	num_tmp[3];
	int		shape_tmp;

	strcpy(num_tmp, mycard[first].num);
	strcpy(mycard[first].num, mycard[second].num);
	strcpy(mycard[second].num, num_tmp);

	shape_tmp = mycard[first].shape;
	mycard[first].shape = mycard[second].shape;
	mycard[second].shape = shape_tmp;
}

_Bool	cmp_card(struct card mycard[], int first, int second)
{
	char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	char shape_ar[5] = "CHDS";
	int	first_num_idx;
	int	first_shape_idx;
	int	second_num_idx;
	int	second_shape_idx;

	for (int i = 0; i < 13; i++)
	{
		if (!strcmp(mycard[first].num, number[i]))
			first_num_idx = i;
		if (!strcmp(mycard[second].num, number[i]))
			second_num_idx = i;
	}
	for (int i = 0; i < 5; i++)
	{
		if (mycard[first].shape == shape_ar[i])
			first_shape_idx = i;
		if (mycard[second].shape == shape_ar[i])
			second_shape_idx = i;
	}
	if (first_shape_idx < second_shape_idx)
		return 0;
	else
	{
		if (first_num_idx > second_num_idx)
			return 1;
	}
	return 0;
}

void	sort_cards(struct card mycard[])
{
	for (int i = 1; i < 5; i++)
	{
		for(int j = 0; j < i - 1; j++)
		{
			if (cmp_card(mycard, j, j + 1))
				change_card(mycard, j, j + 1);
		}
	}
}

void    make_randomly(struct card mycard[], char **number, char *shape_ar, _Bool(*pocker_hands[12])(struct card mycard[]), char **pocker_hands_name)
{  
    int     menu;
    int     count = 1;
    _Bool   (*func)(struct card mycard[]);
    struct card copy_card[5];

    printf("\n");
    for (int i = 0; i < 12; i++)
    {
        printf("%-2d. %-20s", i + 1, pocker_hands_name[i]);
        if (i % 2 == 0)
            printf("      ");
        else
            printf("\n");
    }
    
    while (1)
    {
        printf("\n���� ������ �����ұ��? ");
        scanf("%d", &menu);
        if (menu >= 1 && menu <= 12)
            break ;
        printf("�߸��� �޴���ȣ �Դϴ�.\n");
    }

    func = pocker_hands[menu - 1];
    
    while (1)
    {
        for (int i = 0; i < 5; i++)
        {
            mycard[i].shape = shape_ar[rand() % 4];
            strcpy(mycard[i].num, number[rand() % 13]);
            if (!check_card(mycard, i))
                i--;
        }
        for (int i = 0; i < 5; i++)
		{
			strcpy(copy_card[i].num, mycard[i].num);
			copy_card[i].shape = mycard[i].shape;
		}
		sort_cards(mycard);
        if ((*func)(mycard))
            break ;
        count++;
        if (count == INT_MAX)
            break ;
    }
    printf("������ ī�� : ");
    for (int i = 0; i < 5; i++)
    {
        if (i != 0)
            printf(", ");
        printf("%c %s", copy_card[i].shape, copy_card[i].num);
    }
    printf("\n%d�� ������ �����ϱ� ���� ī�� ���� �õ� : %d��\n", menu, count);
}

void    input_directly(struct card mycard[], _Bool(*pocker_hands[12])(struct card mycard[]), char **pocker_hands_name_ko)
{
    int i;

    printf("\n5���� ī�� ������ �Է��ϼ���\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d�� ���̿� ���� : ", i + 1);
        scanf("%c %s", &mycard[i].shape, mycard[i].num);
        getchar();
    }

    printf("\n");

    for (i = 0; i < 12; i++)
    {
        if (pocker_hands[i](mycard))
        {
            printf("��� : %s\n", pocker_hands_name_ko[i]);
            break ;
        }
    }
    if (i == 12)
        printf("��� : �� ���\n");
}

_Bool royal_straight_flush(struct card mycard[])
{
    char shape = mycard[0].shape;
    char *num = mycard[0].num;
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int  royal_straight_number;

    if (strcmp("10", num))
        return (0);
    for (int i = 1; i < 5; i++)
    {
        royal_straight_number = 8 + i;  //�ξ� ��Ʈ����Ʈ �÷����� ������ �� *number[13] index
        if (shape != mycard[i].shape)
            return (0);
        if (strcmp(number[royal_straight_number], mycard[i].num))
            return (0);
    }
    return (1);
}

_Bool back_straight_flush(struct card mycard[])
{
    char shape = mycard[0].shape;
    char *num = mycard[0].num;
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int  back_straight_number;

    if (strcmp("A", num))
        return (0);
    for (int i = 1; i < 5; i++)
    {
        back_straight_number = i - 1;   //�� ��Ʈ����Ʈ �÷����� ������ �� *number[13] index
        if (shape != mycard[i].shape)
            return (0);
        if (strcmp(number[back_straight_number], mycard[i].num))
            return (0);
    }
    return (1);
}

_Bool straight_flush(struct card mycard[])
{
    char shape = mycard[0].shape;
    char *num = mycard[0].num;
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int  straight_flush_number;

    for (int i = 0; i < 13; i++)
    {
        if (!strcmp(number[i], num))
            straight_flush_number = i + 1; //��Ʈ����Ʈ �÷����� ������ �� *number[13] index
    }
    
    for (int i = 1; i < 5; i++)
    {
        if (straight_flush_number > 12)    //���ӵ��� �ʴ� number�� ��Ʈ����Ʈ�� �ƴϴ�.
        return (0);
        if (shape != mycard[i].shape)
            return (0);
        if (strcmp(number[straight_flush_number], mycard[i].num))
            return (0);
        straight_flush_number++;
    }
    return (1);
}
_Bool four_card(struct card mycard[])
{
    char *num = mycard[0].num;
    int  count = 0;

    if (strcmp(num, mycard[1].num)) //ù ��° ī��� �� ��° ī���� ���ڰ� �ٸ���,
        num = mycard[2].num;        //�� ��° ī�带 �������� ���� ī���� ������ ã�´�.
    for (int i = 0; i < 5; i++)
    {
        if (!strcmp(num, mycard[i].num))
            count++;
    }
    if (count >= 4)  //???? ???? 4???? ?? ???
        return (1);
    return (0);
}

_Bool full_house(struct card mycard[])
{
    char *first_num = mycard[0].num;
    char *second_num = mycard[1].num;
    int  first_num_count = 0;
    int  second_num_count = 0;

    if (!strcmp(first_num, mycard[1].num)) //ù ��° ī��� �� ��° ī���� ���ڰ� ����,
    {
        if (!strcmp(first_num, mycard[2].num)) //�� ��° ī��͵� ���ٸ�,
        {
            second_num = mycard[0].num;         //�ߺ������� 3�� ī���� number�̰�
            first_num = mycard[3].num;         //�� ��° ī�尡 �ߺ������� 2�� ī���� number�̴�.
        }
        else                            // �� ��° ī��� �ٸ��ٸ�,
        {
            first_num = mycard[0].num;         //�ߺ������� 2�� ī���� number�̰�,
            second_num = mycard[2].num;         //�� ��° ī�尡 �ߺ������� 3�� ī���� number�̴�.
        }
    }
    for (int i = 0; i < 5; i++) //5�� ī�� �˻�
    {
        if (!strcmp(first_num, mycard[i].num))
            first_num_count++;
        if (!strcmp(second_num, mycard[i].num))
            second_num_count++;
    }
    if ((first_num_count >= 3 && second_num_count >= 2) || (first_num_count >= 2 && second_num_count >= 3))  //�����ϸ� Ǯ�Ͽ콺
        return (1);
    return (0);
}

_Bool flush(struct card mycard[])
{
    char shape = mycard[0].shape;

    for (int i = 1; i < 5; i++)
    {
        if (shape != mycard[i].shape) // ����� �ٸ��� �÷����� �ƴϴ�.
            return (0);
    }
    return (1);
}

_Bool mountain(struct card mycard[])
{
    char *num = mycard[0].num;
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int  mountain_number;

    if (strcmp("10", num))
        return (0);
    for (int i = 1; i < 5; i++)
    {
        mountain_number = 8 + i;  //����ƾ�̸� ������ �� *number[13] index
        if (strcmp(number[mountain_number], mycard[i].num))
            return (0);
    }
    return (1);
}

_Bool back_straight(struct card mycard[])
{
    char *num = mycard[0].num;
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int  back_straight_number;

    if (strcmp("A", num))
        return (0);
    for (int i = 1; i < 5; i++)
    {
        back_straight_number = i - 1;  //�� ��Ʈ����Ʈ �÷����� ������ �� *number[13] index
        if (strcmp(number[back_straight_number], mycard[i].num))
            return (0);
    }
    return (1);
}

_Bool straight(struct card mycard[])
{
    char *num = mycard[0].num;
    char *number[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int  straight_number;

    for (int i = 0; i < 13; i++)
    {
        if (!strcmp(number[i], num))
            straight_number = i + 1; //��Ʈ����Ʈ�� ������ �� *number[13] index
    }
    
    for (int i = 1; i < 5; i++)
    {
        if (straight_number > 12)    //���ӵ��� �ʴ� number�� ��Ʈ����Ʈ�� �ƴϴ�.
        return (0);
        if (strcmp(number[straight_number], mycard[i].num))
            return (0);
        straight_number++;
    }
    return (1);
}

_Bool triple(struct card mycard[])
{
    char *num;
    int  count = 0;
    int j;

    for (int i = 0; i < 5; i++)
    {
        num = mycard[i].num;
        for (j = i + 1; j < 5; j++)
        {
            if (!strcmp(num, mycard[j].num))
            {
                num = mycard[j].num;
                break;
            }
        }
        if (j != 5)
            break ;
    }

    for (int i = 0; i < 5; i++)
    {
        if (!strcmp(num, mycard[i].num))
            count++;
    }
    if (count >= 3)  //���� ���� 3���� Ʈ����
        return (1);
    return (0);
}

_Bool two_pair(struct card mycard[])
{
    char *num = mycard[0].num;
    int count = 0;
    int j;
    for (int i = 0; i < 5; i++)
    {
        num = mycard[i].num;
        for (j = i + 1; j < 5; j++)
        {
            if (!strcmp(num, mycard[j].num))
                count++;
        }
    }
    if (count >= 2)
        return (1);
    return (0);
}

_Bool one_pair(struct card mycard[])
{
    char *num = mycard[0].num;
    int count = 0;
    int j;
    for (int i = 0; i < 5; i++)
    {
        num = mycard[i].num;
        for (j = i + 1; j < 5; j++)
        {
            if (!strcmp(num, mycard[j].num))
            {
                count++;
                break;
            }
        }
    }
    if (count >= 1)
        return (1);
    return (0);
}
