#pragma once
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <locale>

struct Op {
	char type = NULL;//Тип этапа: '0' - Чтение и дешифрация кода операции; '1' - Выборка 1-го операнда;
					 //'2' - Выборка 2-го операнда; '3' - Вычисление результата; '4' - Запись результата
	unsigned short time = 0;//Такты на этап
};

struct Com {
	Op command[5];//Команда
};

class Pipeline {
	Com mass[9];//Кол-во команд
	Com line[3];//Кол-во ступеней
	unsigned short timeOnLine0;
	unsigned short timeOnLine1;
	unsigned short timeOnLine2;//Кол-во тактов на каждой ступени
	unsigned short numComOnLine0;
	unsigned short numComOnLine1;
	unsigned short numComOnLine2;//Кол-во операций на каждой ступени
public:
	Pipeline();
	void show();
	void pipelineEmulation();//Эмуляция конвейера
	bool condition(char a, char b, char c);//Условие по ТЗ
};