#include "Pipeline.h"

Pipeline::Pipeline() {
	srand(time(NULL));
	
	timeOnLine0 = 0;
	timeOnLine1 = 0;
	timeOnLine2 = 0;
	numComOnLine0 = 0;
	numComOnLine1 = 0;
	numComOnLine2 = 0;

	for (int i = 0; i < 9; i++) {
		unsigned short chanceOfOp, chanceOfTy, timeOfOp, timeOfTy;
		unsigned short c;
		c = rand() % 3 + 1;
		switch (c) {
		case 1:
			chanceOfOp = 9;
			chanceOfTy = 9;
			timeOfOp = 2;
			timeOfTy = 4;
			break;
		case 2:
			chanceOfOp = 8;
			chanceOfTy = 6;
			timeOfOp = 5;
			timeOfTy = 8;
			break;
		case 3:
			chanceOfOp = 6;
			chanceOfTy = 5;
			timeOfOp = 10;
			timeOfTy = 16;
			break;
		}

		unsigned short randOp;
		unsigned short randTy;

		randOp = rand() % 10 + 1;
		randTy = rand() % 10 + 1;

		mass[i].command[0].type = '0';
		mass[i].command[0].time = 1;
		mass[i].command[1].type = '1';
		mass[i].command[1].time = 1;
		mass[i].command[2].type = '2';
		mass[i].command[3].type = '3';
		mass[i].command[4].type = '4';

		if (randOp < chanceOfOp) {
			mass[i].command[2].time = 1;
			mass[i].command[4].time = 1;
		}
		else {
			mass[i].command[2].time = timeOfOp;
			mass[i].command[4].time = timeOfOp;
		}

		if (randTy < (chanceOfTy))
			mass[i].command[3].time = 1;
		else
			mass[i].command[3].time = timeOfTy;
	}
}

void Pipeline::pipelineEmulation() {
	unsigned short val = 0;//Текущий номер команд

	bool exit = true;

	bool newComOnLine0 = true;
	bool newComOnLine1 = true;
	bool newComOnLine2 = true;//Флаги для подачи новой команды

	unsigned short numEt0 = 0;
	unsigned short numEt1 = 0;
	unsigned short numEt2 = 0;//Номер этапа команды

	char lastEt0 = NULL;
	char lastEt1 = NULL;
	char lastEt2 = NULL;//Текущение этапы команд на текущем такте

	std::cout.width(16);
	std::cout << "Ступень 1";
	std::cout.width(12);
	std::cout << "Ступень 2";
	std::cout.width(12);
	std::cout << "Ступень 3";
	//////////////////////////////////////////////////////////////////////////////////////
	while (exit) {
		if (newComOnLine0 == false) {
			if (line[0].command[numEt0].time == 0) {//Если этап команды закончен
				numEt0++;//Переходим на новый этап команды
				lastEt0 = NULL;
			}

			if (line[0].command[numEt0].type != lastEt1 && line[0].command[numEt0].type != lastEt2) {//Если не выполняется такой же этап
				lastEt0 = line[0].command[numEt0].type;//Заносим в текущий этап на этом такте
				line[0].command[numEt0].time--;//Уменьшаем кол-во тактов на 1 
				std::cout.width(12);
				std::cout << line[0].command[numEt0].type;
			}
			else {
				if (condition(line[0].command[numEt0].type, lastEt1, lastEt2)) {//Если удовлетворяет условию
					lastEt0 = line[0].command[numEt0].type;
					line[0].command[numEt0].time--;
					std::cout.width(12);
					std::cout << line[0].command[numEt0].type;
				}
				else {
					std::cout.width(12);
					std::cout << "5";
				}
			}

			timeOnLine0++;
			if (line[0].command[numEt0].time == 0 && line[0].command[numEt0].type == '4') {//Если команда полностью выполнилась
				newComOnLine0 = true;
				if (val == 9)
					lastEt0 = NULL;
			}
		}
		else if (val == 9) {
			std::cout.width(12);
			std::cout << "5";
		}

		if (newComOnLine1 == false) {
			if (line[1].command[numEt1].time == 0) {
				numEt1++;
				lastEt1 = NULL;
			}

			if (line[1].command[numEt1].type != lastEt0 && line[1].command[numEt1].type != lastEt2) {
				lastEt1 = line[1].command[numEt1].type;
				line[1].command[numEt1].time--;
				std::cout.width(12);
				std::cout << line[1].command[numEt1].type;
			}
			else {
				if (condition(line[1].command[numEt1].type, lastEt0, lastEt2)) {
					lastEt1 = line[1].command[numEt1].type;
					line[1].command[numEt1].time--;
					std::cout.width(12);
					std::cout << line[1].command[numEt1].type;
				}
				else {
					std::cout.width(12);
					std::cout << "5";
				}
			}

			timeOnLine1++;
			if (line[1].command[numEt1].time == 0 && line[1].command[numEt1].type == '4') {
				newComOnLine1 = true;
				if (val == 9)
					lastEt1 = NULL;
			}
		}
		else if (val == 9) {
			std::cout.width(12);
			std::cout << "5";
		}

		if (newComOnLine2 == false) {
			if (line[2].command[numEt2].time == 0) {
				numEt2++;
				lastEt2 = NULL;
			}

			if (line[2].command[numEt2].type != lastEt0 && line[2].command[numEt2].type != lastEt1) {
				lastEt2 = line[2].command[numEt2].type;
				line[2].command[numEt2].time--;
				std::cout.width(12);
				std::cout << line[2].command[numEt2].type;
			}
			else {
				if (condition(line[2].command[numEt2].type, lastEt0, lastEt1)) {
					lastEt2 = line[2].command[numEt2].type;
					line[2].command[numEt2].time--;
					std::cout.width(12);
					std::cout << line[2].command[numEt2].type;
				}
				else {
					std::cout.width(12);
					std::cout << "5";
				}
			}
			if (line[2].command[numEt2].time == 0) {
				lastEt2 = NULL;
			}
			timeOnLine2++;
			if (line[2].command[numEt2].time == 0 && line[2].command[numEt2].type == '4')
				newComOnLine2 = true;
		}
		std::cout << std::endl;
		//////////////////////////////////////////////////////////////////////////////////
		if (newComOnLine0 == true && val < 9) {//Новая команда в свободную ступень
			line[0] = mass[val];
			val++;
			numEt0 = 0;
			newComOnLine0 = false;
			numComOnLine0++;
		}
		if (newComOnLine1 == true && val < 9) {
			line[1] = mass[val];
			val++;
			numEt1 = 0;
			newComOnLine1 = false;
			numComOnLine1++;
		}
		if (newComOnLine2 == true && val < 9) {
			line[2] = mass[val];
			val++;
			numEt2 = 0;
			newComOnLine2 = false;
			numComOnLine2++;
		}
		if (newComOnLine0 == true && newComOnLine1 == true && newComOnLine2 == true)
			exit = false;
		
	}
}

void Pipeline::show() {
	std::cout << "-----------------------------------------------";
	std::cout << std::endl << std::endl << std::endl; 
	std::cout << "Команда/Этап";
	std::cout.width(4);
	std::cout << "ЧД";
	std::cout.width(6);
	std::cout << "ВП";
	std::cout.width(6);
	std::cout << "ВВ";
	std::cout.width(6);
	std::cout << "ВР";
	std::cout.width(6);
	std::cout << "ЗД" << std::endl;

	for (int i = 0; i < 9; i++) {
		std::cout << "Команда №" << i+1;
		for (int j = 0; j < 5; j++) {
			std::cout.width(6);
			std::cout << mass[i].command[j].time;
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------------------------------------";
	std::cout << std::endl << std::endl << std::endl;

	float res;

	std::cout << "Кол-во тактов на 1-ой ступени: " << timeOnLine0 << std::endl;
	std::cout << "Кол-во команд 1-ой ступени: " << numComOnLine0 << std::endl;
	res = (float)timeOnLine0 / (float)numComOnLine0;
	std::cout << "Среднее кол-во тактов на 1-ой ступени: " << res << std::endl << std::endl;

	std::cout << "Кол-во тактов на 2-ой ступени: " << timeOnLine1 << std::endl;
	std::cout << "Кол-во команд 2-ой ступени: " << numComOnLine1 << std::endl;
	res = (float)timeOnLine1 / (float)numComOnLine1;
	std::cout << "Среднее кол-во тактов на 2-ой ступени: " << res << std::endl << std::endl;

	std::cout << "Кол-во тактов на 3-ой ступени: " << timeOnLine2 << std::endl;
	std::cout << "Кол-во команд 3-ой ступени: " << numComOnLine2 << std::endl;
	res = (float)timeOnLine2 / (float)numComOnLine2;
	std::cout << "Среднее кол-во тактов на 3-ой ступени: " << res << std::endl << std::endl;
	std::cout << "-----------------------------------------------";
	std::cout << std::endl << std::endl << std::endl;

	unsigned short max;
	max = (timeOnLine0 > timeOnLine1) ? ((timeOnLine0 > timeOnLine2) ? timeOnLine0 : timeOnLine2) : ((timeOnLine1 > timeOnLine2) ? timeOnLine1 : timeOnLine2);
	std::cout << "Время работы конвейера: " << max << std::endl;
	std::cout << "-----------------------------------------------";
	std::cout << std::endl << std::endl << std::endl;
}

bool Pipeline::condition(char a, char b, char c) {
	bool flag;

	if (a == '0' && ((b == '2' && c == '4') || (b == '2' && c == '2') || (b == '4' && c == '2')))
		flag = true;
	else
		return false;
	if (b == '0' && ((a == '2' && c == '4') || (a == '2' && c == '2') || (a == '4' && c == '2')))
		flag = true;
	else
		return false;
	if (c == '0' && ((b == '2' && a == '4') || (b == '2' && a == '2') || (b == '4' && a == '2')))
		flag = true;
	else
		return false;

	return flag;
}