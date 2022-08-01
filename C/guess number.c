#include<stdio.h>
#include<stdlib.h>

int menu() {
	printf("##############################\n");
	printf("### 1.开始游戏  0.退出游戏 ###\n");
	printf("##############################\n");
}

int game() {
	int ret = rand() % 100 + 1;
	int guess = 0;
	int count = 0;
	//printf("%d\n", ret);
	
	while (1)
	{
		printf("请输入:>");
		scanf_s("%d", &guess);
		if (guess > ret)
		{
			printf("臭宝，猜大啦!\n");
			count++;
		}
		else if (guess < ret)
		{
			printf("加油臭宝，猜的小啦！\n");
			count++;
		}
		else {
			printf("恭喜臭宝！猜对啦！！！\n");
			count++;
			break;
		}
	}
	printf("一共猜了%d次，继续加油哦！\n", count);
}

int main() {
	int input = 1;
	srand((unsigned int) time (NULL));
	do
	{
		menu();
		printf("请选择：");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			game();

			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误\n");
			break;
		}

	} while (input);//0为假，停止，其余数字为真继续循环

	return 1;
}
