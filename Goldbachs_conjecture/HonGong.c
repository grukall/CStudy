#include <stdio.h>
#include <stdlib.h>

int* filter(int* arg);
int main(void){

	int num ,hnum,check=0;
	int i,left=0,right=0;
	int* arg;
	
	printf("2보다 큰 짝수를 입력하시오 :");
	scanf("%d", &num);

	if (num <= 2 || num % 2 != 0) {     //이상한 숫자 방지
		printf("짝수를 입력해주세요");
		return 1;
	}
	arg = (int*)malloc(sizeof(int) * 1229);  //1229개의 소수를 넣응 수 있는 동적할당
	if (arg == NULL)return 1;                

	arg = filter(arg);  //소수만 넣기

	hnum = num / 2;           //숫자의 절반
	for (i = 0; i < 1229; i++) {
		if (arg[i]<hnum && arg[i + 1]>hnum) {  //숫자의 절반과 가장 가깝게 크거나 작은 소수 찾기
			left = i;
			right = i + 1;
			break;
		}
	}

	while (1) {
		if (arg[left] + arg[right] == num) {                      //만약 찾으면
			printf("%d + %d = %d", arg[left], arg[right], num);    //출력하고 끝냄
			break;
		}
		else if (num < arg[left] + arg[right]) {              //만약 num보다 크면
			left--;                                           //작은 쪽 소수를 바로 왼쪽 소수로 바꿈
		}
		else if(num > arg[left] + arg[right]) {             //num보다 작으면
			right++;                                         //큰 쪽 소수를 바로 오른쪽 소수로 바꿈
		}
	}
	
	free(arg);  //arg 해제
	return 0;
}

int* filter(int* arg) {   //소수추출
	int i,j,nope=0,count = 1;
	arg[0] = 2;
	for (i = 3; i <= 10000; i++) {

		for (j = 2; j < i; j++) {

			if (i % j == 0) {
				nope = 1;
				break;
			}

		}
		if (nope == 0) {
			arg[count] = i;
			count++;     //소수갯수
		}
		nope = 0;
	}
	return arg;
}