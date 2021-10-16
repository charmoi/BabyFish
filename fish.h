#pragma once
#include <bangtal>

using namespace bangtal;
using namespace std;

class Fish {
private:
	ObjectPtr fish;
	string normal_left;
	string normal_right;
	string eat_left;
	string eat_right;
	string damaged_left;
	string damaged_right;
	string current_left;
	string current_right;

	int x, y;
	int width, height;
	int area_w, area_h;

	// set_scale �Լ��� ���� ������ (���ʿ� �Է¹��� ��)
	int true_width, true_height;
	int true_area_w, true_area_h;

	bool moving;
	bool target;
	bool player;
	bool damaged;
	bool eating;

	int score;
	int speed;
	int fish_num;

	int p[4][2]; //�� ������

public:
	Fish();
	Fish(string img_left, string img_right, int w, int h);

	// ����� ���� ���� �Ǵ�
	friend int IsContact(Fish& player_fish, Fish& obj_fish);

	// ����� ��ü ����
	void create(string img_left, string img_right, int w, int h);

	// ����� �з� ��ȣ �ο�
	void set_fishnum(int n);

	// ����� �з� ��ȣ ��ȯ
	int get_fishnum();

	// ����� ���� ����
	void set_scale(double size);

	// Ÿ ������ �ε��� �ɷ� �νĵǴ� ������ ũ�� ����
	void set_contact_size(int w, int h);

	// ������ ���� �̹��� ����
	void set_damaged(string left, string right);

	// �԰� �ִ� �̹��� ����
	void set_eat(string left, string right);

	// ���� �̹��� ����
	void set_normal(string left, string right);

	// ������ ���� �̹����� ��ȯ
	void change_damaged();

	// �԰� �ִ� �̹����� ��ȯ
	void change_eat();

	// ���� �̹����� ��ȯ
	void change_normal();

	// ������ ���� ��������
	bool is_damaged();

	// �԰� �ִ� ��������
	bool is_eating();

	// ������ ȹ��� ���� ����
	void set_score(int n);

	// ���� ��ȯ
	int get_score();

	// ���̷� ��ȯ
	void make_target();

	// ������ ��ȯ
	void make_enemy();

	// ����(true)���� ��(false)���� ����
	bool is_target();

	// �̵� �ӵ� ����
	void set_speed(int s);

	// ������ �ӵ�(�ȼ�)��ŭ ��� �̵�
	void move_right();
	// ������ �ӵ�(�ȼ�)��ŭ �·� �̵�
	void move_left();
	// ������ �ӵ�(�ȼ�)��ŭ ���� �̵�
	void move_up();
	// ������ �ӵ�(�ȼ�)��ŭ �Ʒ��� �̵�
	void move_down();

	// �⺻ ��ġ�� �̵�
	void move_home();

	// �Է��� ��ǥ�� �̵�
	void move_to(int px, int py);

	// ���� ȭ�� �󿡼� �̵� ������ ����
	bool is_moving();

	// contact ���� ����; �� �𼭸��� x, y ��ǥ ����
	void set_area();

	// x ��ǥ ��ȯ
	int get_x();
	// y ��ǥ ��ȯ
	int get_y();
	// �̹��� ���� ��ȯ
	int get_width();
	// �̹��� ���� ��ȯ
	int get_height();

};