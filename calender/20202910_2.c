#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_day
{
    _Bool   is_schedule;
    char    *schedule;
}t_day;

typedef struct s_calender
{
    int     year;
    _Bool   leap_year;
    int     month;
    t_day   *day;
    int     day_length;
}t_calender;

void    put_schedule(t_calender *calender);
void    delete_schedule(t_calender *calender);
void    print_schedule(t_calender *calender);
void    free_calender(t_calender *calender);
void    increase_schedule(char **schedule, int i);

void   make_calender(t_calender *calender)
{
    int *result;
    if(calender->year % 400 == 0)calender->leap_year = 1;
    else if(calender->year % 100 == 0)calender->leap_year = 0;
    else if(calender->year % 4 == 0)calender->leap_year = 1;
    else calender->leap_year = 0;

    if (calender->month == 2 && calender->leap_year)calender->day_length = 29;
    else if (calender->month == 2)calender->day_length = 28;
    else if (calender->month % 2 == 0 && calender->month < 7)calender->day_length = 30;
    else if (calender->month % 2 == 0)calender->day_length = 31;
    else if (calender->month % 2 == 1 && calender->month <= 7)calender->day_length = 31;
    else calender->day_length = 30;

    calender->day = (t_day *)malloc(sizeof(t_day) * calender->day_length);
    for (int i = 0; i < calender->day_length; i++)calender->day[i].is_schedule = 0;   
}

int find_day_of_the_week(t_calender *calender)
{
    int start = 0;                           // 0(월) ~ 6(일)
    for (int i = 2; i <= calender->year; i++)
    {
        if(i % 400 == 0)start += 2;
        else if(i % 100 == 0)start++;
        else if(i % 4 == 0)start += 2;
        else start++;
        start %= 7;
    }

    for (int i = 1; i < calender->month; i++)
    {
        //1월부터 calender->month까지 계산
        if (i == 2 && calender->leap_year)
            start += 29;
        else if (i == 2)
            start += 28;
        else if (i % 2 == 0)
            start += 30;
        else
            start += 31;
        start %= 7;
    }
    return start;
}

void    print_calender(t_calender *calender)
{
    int start_day_of_the_week;

    start_day_of_the_week = find_day_of_the_week(calender);
    printf("                       %d년 %d월              \n\n", calender->year, calender->month);
    printf("         Sun   Mon   Tue   Wen   Thu   Fri   Sat\n\n");
    //printf("%d\n", calender->leap_year);

    printf("         ");
    for (int i = 0; i <= start_day_of_the_week && start_day_of_the_week != 6; i++)
    {
        printf("      ");
    }
    
    for (int i = 1; i <= calender->day_length; i++)
    {
        if (start_day_of_the_week == 6 || i == 1)
            printf("%d", i);
        else
            printf("%6d", i);
        if (i + 1 == 10)
            printf(" ");
        if (++start_day_of_the_week == 6)
            printf("\n         ");
        start_day_of_the_week %= 7;
    }
}


int main()
{
    t_calender  calender;
    int         menu;

    printf("년을 입력해주세요 : ");
    scanf("%d", &calender.year);
    printf("월을 입력해주세요 : ");
    scanf("%d", &calender.month);
    make_calender(&calender);
    
    while (1)
    {
        print_calender(&calender);
        printf("\n\n\n\n   1.일정 입력   2.일정 삭제   3.일정 확인    4.종료\n\n");
        printf("메뉴를 입력하세요 : ");
        scanf("%d", &menu);
        getchar();
        if (menu == 4)
            break ;
        else if (menu == 1)
            put_schedule(&calender);
        else if (menu == 2)
            delete_schedule(&calender);
        else if (menu == 3)
            print_schedule(&calender);
        else
        {
            printf("메뉴 번호를 다시 입력하세요");
            while(getchar() != '\n');
        }
        system("clear");
    }
    free_calender(&calender);
}

void    put_schedule(t_calender *calender)
{
    int     input_day;
    int     i;
    char    ch;

    while (1)
    {
        i = 0;
        printf("날짜를 입력하세요 : ");
        scanf("%d", &input_day);
        getchar();
        if (input_day == 0)
            break ;
        else if (input_day < 1 || input_day > calender->day_length)
            printf("없는 날짜입니다.");
        else if (calender->day[input_day - 1].is_schedule)
            printf("일정이 있는 날짜입니다");
        else
        {
            calender->day[input_day - 1].schedule = (char *)calloc(10, sizeof(char));
            printf("일정을 입력하세요 : ");
            while((ch = getchar()) != '\n')
            {
                calender->day[input_day - 1].schedule[i++] = ch;
                if(i % 10 == 0 && ch != '\0')
                    increase_schedule(&calender->day[input_day - 1].schedule, i);
            }
            calender->day[input_day - 1].is_schedule = 1;
            break ;
        }
        while(getchar() != '\n');
    }
}

void    increase_schedule(char **schedule, int i)
{
    char    *temp = (char *)calloc(i + 10, sizeof(char));

    strncpy(temp, *schedule, i);
    free(*schedule);
    *schedule = temp;
}

void    delete_schedule(t_calender *calender)
{
    int     input_day;

    while (1)
    {
        printf("날짜를 입력하세요 : ");
        scanf("%d", &input_day);
        getchar();
        if (input_day == 0)
            break ;
        else if (input_day < 1 || input_day > calender->day_length)
            printf("없는 날짜입니다.");
        else if (!calender->day[input_day - 1].is_schedule)
            printf("일정이 없는 날짜입니다");
        else
        {
            free(calender->day[input_day - 1].schedule);
            calender->day[input_day - 1].is_schedule = 0;
            break ;
        }
        while(getchar() != '\n');
    }
}

void    print_schedule(t_calender *calender)
{
    int     input_day;

     while (1)
    {
        printf("날짜를 입력하세요 : ");
        scanf("%d", &input_day);
        getchar();
        if (input_day == 0)
            break ;
        else if (input_day < 1 || input_day > calender->day_length)
            printf("없는 날짜입니다.\n");
        else if (!calender->day[input_day - 1].is_schedule)
            printf("일정이 없는 날짜입니다\n");
        else
        {
            printf("%d년 %d월 %d일 일정은 %s입니다.",calender->year, calender->month, input_day, calender->day[input_day - 1].schedule);
            while(getchar() != '\n');
            break ;
        }
        while(getchar() != '\n');
    }
}

void    free_calender(t_calender *calender)
{
    if (calender)
    {
        for (int i = 0; i < calender->day_length; i++)
        {
            if (calender->day[i].is_schedule)
                free(calender->day[i].schedule);
        }
        free(calender->day);
    }
}
