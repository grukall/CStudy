#include <stdio.h>
#include <stdlib.h>

int* filter(int* arg);
int main(void){

	int num ,hnum,check=0;
	int i,left=0,right=0;
	int* arg;
	
	printf("2���� ū ¦���� �Է��Ͻÿ� :");
	scanf("%d", &num);

	if (num <= 2 || num % 2 != 0) {     //�̻��� ���� ����
		printf("¦���� �Է����ּ���");
		return 1;
	}
	arg = (int*)malloc(sizeof(int) * 1229);  //1229���� �Ҽ��� ���� �� �ִ� �����Ҵ�
	if (arg == NULL)return 1;                

	arg = filter(arg);  //�Ҽ��� �ֱ�

	hnum = num / 2;           //������ ����
	for (i = 0; i < 1229; i++) {
		if (arg[i]<hnum && arg[i + 1]>hnum) {  //������ ���ݰ� ���� ������ ũ�ų� ���� �Ҽ� ã��
			left = i;
			right = i + 1;
			break;
		}
	}

	while (1) {
		if (arg[left] + arg[right] == num) {                      //���� ã����
			printf("%d + %d = %d", arg[left], arg[right], num);    //����ϰ� ����
			break;
		}
		else if (num < arg[left] + arg[right]) {              //���� num���� ũ��
			left--;                                           //���� �� �Ҽ��� �ٷ� ���� �Ҽ��� �ٲ�
		}
		else if(num > arg[left] + arg[right]) {             //num���� ������
			right++;                                         //ū �� �Ҽ��� �ٷ� ������ �Ҽ��� �ٲ�
		}
	}
	
	free(arg);  //arg ����
	return 0;
}

int* filter(int* arg) {   //�Ҽ�����
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
			count++;     //�Ҽ�����
		}
		nope = 0;
	}
	return arg;
}