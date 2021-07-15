#pragma once
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#define BUFFSIZE 2048
#define CHARBUFF 124
#define max 100
extern int data[max][4];
extern int yourhp;
extern int enemyhp;
extern int damage;
extern int playturn;
void CSV2Array(const char* filename, int data[max][4]);
void getGurrentDirectory(char* currentDirectory);
void move(int i);
void enemy();
void hp();
void getdata();
void outputfile();

typedef struct c_data {
	int hp;
	int attack;
	int defense;
};


