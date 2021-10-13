#pragma once
#include <bangtal>

using namespace bangtal;

class Number {
private:
	ObjectPtr card;
	int num;

public:
	Number();
	Number(ScenePtr scene, int x, int y);

	// ���� ī�� ��ü ����
	void create(ScenePtr scene, int x, int y);

	// ���� ī�� ���̱�
	void show();

	// ���� ī�� �����
	void hide();

	// ���� ī�� ũ�� ����
	void set_scale(double n);

	// �Է��� ������ ���� ���� (1~15���� ����)
	void set(int n);

	// ���� 1�� ����
	void decrease();
};
