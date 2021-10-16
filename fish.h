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

	// set_scale 함수를 위한 기준점 (최초에 입력받은 값)
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

	int p[4][2]; //네 꼭지점

public:
	Fish();
	Fish(string img_left, string img_right, int w, int h);

	// 물고기 접촉 여부 판단
	friend int IsContact(Fish& player_fish, Fish& obj_fish);

	// 물고기 물체 생성
	void create(string img_left, string img_right, int w, int h);

	// 물고기 분류 번호 부여
	void set_fishnum(int n);

	// 물고기 분류 번호 반환
	int get_fishnum();

	// 물고기 비율 조정
	void set_scale(double size);

	// 타 물고기와 부딪힌 걸로 인식되는 영역의 크기 조정
	void set_contact_size(int w, int h);

	// 데미지 입은 이미지 설정
	void set_damaged(string left, string right);

	// 먹고 있는 이미지 설정
	void set_eat(string left, string right);

	// 평상시 이미지 설정
	void set_normal(string left, string right);

	// 데미지 입은 이미지로 전환
	void change_damaged();

	// 먹고 있는 이미지로 전환
	void change_eat();

	// 평상시 이미지로 전환
	void change_normal();

	// 데미지 입은 상태인지
	bool is_damaged();

	// 먹고 있는 상태인지
	bool is_eating();

	// 먹으면 획득될 점수 설정
	void set_score(int n);

	// 점수 반환
	int get_score();

	// 먹이로 전환
	void make_target();

	// 적으로 전환
	void make_enemy();

	// 먹이(true)인지 적(false)인지 여부
	bool is_target();

	// 이동 속도 설정
	void set_speed(int s);

	// 설정된 속도(픽셀)만큼 우로 이동
	void move_right();
	// 설정된 속도(픽셀)만큼 좌로 이동
	void move_left();
	// 설정된 속도(픽셀)만큼 위로 이동
	void move_up();
	// 설정된 속도(픽셀)만큼 아래로 이동
	void move_down();

	// 기본 위치로 이동
	void move_home();

	// 입력한 좌표로 이동
	void move_to(int px, int py);

	// 현재 화면 상에서 이동 중인지 여부
	bool is_moving();

	// contact 영역 설정; 네 모서리의 x, y 좌표 설정
	void set_area();

	// x 좌표 반환
	int get_x();
	// y 좌표 반환
	int get_y();
	// 이미지 넓이 반환
	int get_width();
	// 이미지 높이 반환
	int get_height();

};