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
    int start = 0;                           // 0(��) ~ 6(��)
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
        //1������ calender->month���� ���
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
    printf("                       %d�� %d��              \n\n", calender->year, calender->month);
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

    printf("���� �Է����ּ��� : ");
    scanf("%d", &calender.year);
    printf("���� �Է����ּ��� : ");
    scanf("%d", &calender.month);
    make_calender(&calender);
    
    while (1)
    {
        print_calender(&calender);
        printf("\n\n\n\n   1.���� �Է�   2.���� ����   3.���� Ȯ��    4.����\n\n");
        printf("�޴��� �Է��ϼ��� : ");
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
            printf("�޴� ��ȣ�� �ٽ� �Է��ϼ���");
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
        printf("��¥�� �Է��ϼ��� : ");
        scanf("%d", &input_day);
        getchar();
        if (input_day == 0)
            break ;
        else if (input_day < 1 || input_day > calender->day_length)
            printf("���� ��¥�Դϴ�.");
        else if (calender->day[input_day - 1].is_schedule)
            printf("������ �ִ� ��¥�Դϴ�");
        else
        {
            calender->day[input_day - 1].schedule = (char *)calloc(10, sizeof(char));
            printf("������ �Է��ϼ��� : ");
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
        printf("��¥�� �Է��ϼ��� : ");
        scanf("%d", &input_day);
        getchar();
        if (input_day == 0)
            break ;
        else if (input_day < 1 || input_day > calender->day_length)
            printf("���� ��¥�Դϴ�.");
        else if (!calender->day[input_day - 1].is_schedule)
            printf("������ ���� ��¥�Դϴ�");
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
        printf("��¥�� �Է��ϼ��� : ");
        scanf("%d", &input_day);
        getchar();
        if (input_day == 0)
            break ;
        else if (input_day < 1 || input_day > calender->day_length)
            printf("���� ��¥�Դϴ�.\n");
        else if (!calender->day[input_day - 1].is_schedule)
            printf("������ ���� ��¥�Դϴ�\n");
        else
        {
            printf("%d�� %d�� %d�� ������ %s�Դϴ�.",calender->year, calender->month, input_day, calender->day[input_day - 1].schedule);
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
