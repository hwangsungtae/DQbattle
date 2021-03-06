#include <stdio.h>
#include "setting.h"
int damage;
int defenseflag=0;
int num_yakusou = 5;
errno_t error;
FILE* fp;
struct c_data you, monster;

void move(int i) {      //プレイヤーの行動
    if (i == 1) {
        damage = you.attack;
        Sleep(500);
        printf("相手に%dのダメージ\n", damage);
        Sleep(500);
        enemyhp -= damage;
    }
    else if (i == 2) {
        defenseflag = 1;
        Sleep(500);
        printf("守りを固めた\n");
        Sleep(500);

    }
    else {
        Sleep(500);
        printf("薬草を使った\n");
        num_yakusou--;
        Sleep(500);
        printf("あなたは100回復\n");
        Sleep(500);
        printf("残り薬草は%d個\n", num_yakusou);
        yourhp += 100;
        Sleep(500);

    }
}

void enemy() {          //敵の行動
    int moveflag;
    moveflag = (rand() % 5 + 1);
    if (moveflag == 1|| moveflag == 2 || moveflag == 3 ) {

        if (defenseflag == 1) {
            damage = monster.attack - you.attack;
            Sleep(500);
            printf("あなたに%dのダメージ\n", damage);
            Sleep(500);
            yourhp -= damage;
            defenseflag = 0;
        }
        else {
            damage = monster.attack;
            Sleep(500);
            printf("あなたに%dのダメージ\n", damage);
            Sleep(500);
            yourhp -= damage;
        }
    }
    else if (moveflag == 4) {
        if (defenseflag == 1) {
            damage = 120 - you.defense;
            Sleep(500);
            printf("あなたに%dのダメージ\n", damage);
            Sleep(500);
            yourhp -= damage;
            defenseflag = 0;
        }
        else {
            damage = 120;
            printf("あいては炎を吐いた");
            Sleep(500);
            printf("あなたに%dのダメージ\n", damage);
            Sleep(500);
            yourhp -= damage;
        }
    }
    else {
        Sleep(500);
        printf("あいてはボーっとしている\n");
        Sleep(500);
        defenseflag = 0;
    }
}

void CSV2Array(const char* filename, int data[max][4]) {        //CSVのデータを構造体に格納

    
    char s[BUFFSIZE];
    
    char delim[] = ",";//デリミタ（複数渡せる）ここではカンマと空白
    char* ctx;
    char* ary[6];
    char* a;
    int i = 0;
    int index = 0;

    error = fopen_s(&fp, filename, "r");
    if (error != 0)
        fprintf_s(stderr, "failed to open");
    else {
        while (fgets(s, BUFFSIZE, fp) != NULL) {
            ary[0] = strtok_s(s, ",", &ctx);
            ary[1] = strtok_s(NULL, ",", &ctx);
            ary[2] = strtok_s(NULL, ",", &ctx);
            if (index > 0) {
                data[i][0] = atoi(ary[0]);
                data[i][1] = atoi(ary[1]);
                data[i][2] = atoi(ary[2]);

                i++;
            }
            index++;




        }
        fclose(fp);


    }
    you.hp = data[0][0];
    you.attack = data[0][1];
    you.defense = data[0][2];
    monster.hp = data[1][0];
    monster.attack = data[1][1];
    monster.defense = data[1][2];

}
void getGurrentDirectory(char* currentDirectory) {      //パス取得
    GetCurrentDirectory(CHARBUFF, currentDirectory);
}

void hp() {         //HPの設定
    yourhp = you.hp;
    enemyhp = monster.hp;
}

void getdata() {            //iniファイルからデータ取り出し
    char currentDirectory[CHARBUFF];
    getGurrentDirectory(currentDirectory);
    char section[CHARBUFF];
    sprintf_s(section, "section");
    char keyWord[CHARBUFF];
    sprintf_s(keyWord, "keyword");
    char settingFile[CHARBUFF];
    sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
    char keyValue[CHARBUFF];
    if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile) != 0) {
        fprintf(stdout, "%s , %s\n", settingFile, keyValue);
    }
    else {
        fprintf(stdout, "%s doesn't contain [$s] %s\n", settingFile, section, keyWord);
    }

    CSV2Array(keyValue, data);
}

void outputfile() {             //CSVファイル出力
    error = fopen_s(&fp, "playturn.csv", "w");
    if (error != 0)
        fprintf_s(stderr, "failed to open");
    else {
        fprintf_s(fp, "掛かったターン数：%d\n", playturn);
        }
        fclose(fp);
        printf("ファイルに結果が出力されました\n");
    }

