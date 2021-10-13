#include "number.h"

Number::Number() {
	num = 0;
}

Number::Number(ScenePtr scene, int x, int y) {
	card = Object::create("Images/0.png", scene, x, y, true);
	num = 0;
}

void Number::create(ScenePtr scene, int x, int y) {
	card = Object::create("Images/0.png", scene, x, y, true);
}

void Number::show() {
	card->show();
}

void Number::hide() {
	card->hide();
}

void Number::set_scale(double n) {
	card->setScale(n);
}

void Number::set(int n) {
	num = n;
	char img[15];
	sprintf_s(img, "Images/%d.png", num);
	card->setImage(img);
}

void Number::decrease() {
	num--;
	if (num < 0) {
		return;
	}
	char img[15];
	sprintf_s(img, "Images/%d.png", num);
	card->setImage(img);
}

