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
        "로얄 스트레이트 플러쉬",
        "백 스트레이트 플러쉬",
        "스트레이트 플러쉬",
        "포 카드",
        "풀 하우스",
        "플러쉬",
        "마운틴",
        "백 스트레이트",
        "스트레이트",
        "트리플",
        "투 페어",
        "원 페어"
    };

    srand(time(NULL));

    printf("1. 직접 입력    2. 랜덤 생성\n\n");
    while (1)
    { 
        printf("번호를 입력하세요 : ");
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
            printf("잘못된 메뉴번호 입니다\n");
            continue;
        }
        printf("===========================================================\n");
        printf("1. 직접 입력    2. 랜덤 생성    3. 종료\n\n");
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
        printf("\n무슨 족보로 생성할까요? ");
        scanf("%d", &menu);
        if (menu >= 1 && menu <= 12)
            break ;
        printf("잘못된 메뉴번호 입니다.\n");
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
    printf("생성된 카드 : ");
    for (int i = 0; i < 5; i++)
    {
        if (i != 0)
            printf(", ");
        printf("%c %s", copy_card[i].shape, copy_card[i].num);
    }
    printf("\n%d번 족보를 생성하기 위한 카드 생성 시도 : %d번\n", menu, count);
}

void    input_directly(struct card mycard[], _Bool(*pocker_hands[12])(struct card mycard[]), char **pocker_hands_name_ko)
{
    int i;

    printf("\n5개의 카드 정보를 입력하세요\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d번 무늬와 숫자 : ", i + 1);
        scanf("%c %s", &mycard[i].shape, mycard[i].num);
        getchar();
    }

    printf("\n");

    for (i = 0; i < 12; i++)
    {
        if (pocker_hands[i](mycard))
        {
            printf("결과 : %s\n", pocker_hands_name_ko[i]);
            break ;
        }
    }
    if (i == 12)
        printf("결과 : 노 페어\n");
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
        royal_straight_number = 8 + i;  //로얄 스트레이트 플러쉬면 가져야 할 *number[13] index
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
        back_straight_number = i - 1;   //백 스트레이트 플러쉬면 가져야 할 *number[13] index
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
            straight_flush_number = i + 1; //스트레이트 플러쉬면 가져야 할 *number[13] index
    }
    
    for (int i = 1; i < 5; i++)
    {
        if (straight_flush_number > 12)    //연속되지 않는 number는 스트레이트가 아니다.
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

    if (strcmp(num, mycard[1].num)) //첫 번째 카드와 두 번째 카드의 숫자가 다르면,
        num = mycard[2].num;        //세 번째 카드를 기준으로 같은 카드의 갯수를 찾는다.
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

    if (!strcmp(first_num, mycard[1].num)) //첫 번째 카드와 두 번째 카드의 숫자가 같고,
    {
        if (!strcmp(first_num, mycard[2].num)) //세 번째 카드와도 같다면,
        {
            second_num = mycard[0].num;         //중복갯수가 3인 카드의 number이고
            first_num = mycard[3].num;         //네 번째 카드가 중복갯수가 2인 카드의 number이다.
        }
        else                            // 세 번째 카드와 다르다면,
        {
            first_num = mycard[0].num;         //중복갯수가 2인 카드의 number이고,
            second_num = mycard[2].num;         //세 번째 카드가 중복갯수가 3인 카드의 number이다.
        }
    }
    for (int i = 0; i < 5; i++) //5개 카드 검사
    {
        if (!strcmp(first_num, mycard[i].num))
            first_num_count++;
        if (!strcmp(second_num, mycard[i].num))
            second_num_count++;
    }
    if ((first_num_count >= 3 && second_num_count >= 2) || (first_num_count >= 2 && second_num_count >= 3))  //만족하면 풀하우스
        return (1);
    return (0);
}

_Bool flush(struct card mycard[])
{
    char shape = mycard[0].shape;

    for (int i = 1; i < 5; i++)
    {
        if (shape != mycard[i].shape) // 모양이 다르면 플러쉬가 아니다.
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
        mountain_number = 8 + i;  //마운틴이면 가져야 할 *number[13] index
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
        back_straight_number = i - 1;  //백 스트레이트 플러쉬면 가져야 할 *number[13] index
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
            straight_number = i + 1; //스트레이트면 가져야 할 *number[13] index
    }
    
    for (int i = 1; i < 5; i++)
    {
        if (straight_number > 12)    //연속되지 않는 number는 스트레이트가 아니다.
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
    if (count >= 3)  //같은 숫자 3개면 트리플
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
