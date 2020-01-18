#pragma once
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <locale>

struct Op {
	char type = NULL;//��� �����: '0' - ������ � ���������� ���� ��������; '1' - ������� 1-�� ��������;
					 //'2' - ������� 2-�� ��������; '3' - ���������� ����������; '4' - ������ ����������
	unsigned short time = 0;//����� �� ����
};

struct Com {
	Op command[5];//�������
};

class Pipeline {
	Com mass[9];//���-�� ������
	Com line[3];//���-�� ��������
	unsigned short timeOnLine0;
	unsigned short timeOnLine1;
	unsigned short timeOnLine2;//���-�� ������ �� ������ �������
	unsigned short numComOnLine0;
	unsigned short numComOnLine1;
	unsigned short numComOnLine2;//���-�� �������� �� ������ �������
public:
	Pipeline();
	void show();
	void pipelineEmulation();//�������� ���������
	bool condition(char a, char b, char c);//������� �� ��
};