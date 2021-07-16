#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "setting.h"
#define CHARBUFF 124
#define max 100
int data[max][4];
int yourhp;
int enemyhp;
int playturn = 0;		//ターンカウント

int main()
{

	getdata();

	hp();

	while (1) {
		playturn++;
		printf("ターン:%d\n", playturn);
		printf("yourHP:%d\n", yourhp);
		printf("enemyHP:%d\n", enemyhp);
		int i;
		printf("行動を数字で入力してください\n");
		printf("attack:1\ndeffense:2\nheal:3\n");
		if (fscanf_s(stdin, "%d", &i) == 0) {		//入力のフィールドの整合確認
			printf("数字ではありません。エラーです。");
			break;
		}
		if (i > 3) {								//適性の数字化を判断
			printf("表示されている数字を入力してください\n");
			continue;
		}
		move(i);			//自分と敵の行動を呼び出し
		enemy();

		if (yourhp <= 0) {				//ループ毎にHP判定
			printf("あなたは力尽きた\n");
			outputfile();
			return 0;			
		}
		else if (enemyhp <= 0) {
			printf("あなたは戦いに勝利した\n");
			outputfile();
			return 0;
		}
	}
}

