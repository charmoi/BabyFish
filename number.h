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

	// 숫자 카드 물체 생성
	void create(ScenePtr scene, int x, int y);

	// 숫자 카드 보이기
	void show();

	// 숫자 카드 숨기기
	void hide();

	// 숫자 카드 크기 조정
	void set_scale(double n);

	// 입력한 값으로 숫자 변경 (1~15까지 가능)
	void set(int n);

	// 숫자 1씩 감소
	void decrease();
};
