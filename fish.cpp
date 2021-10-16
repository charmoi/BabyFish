#include "fish.h"

extern ScenePtr gameplay;

Fish::Fish()
	: normal_left("\0"), normal_right("\0"), true_width(0), true_height(0) {
	true_area_w = true_width;
	true_area_h = true_height;
	width = true_width;
	height = true_height;
	area_w = true_area_w;
	area_h = true_area_h;
	current_right = normal_right;
	current_left = normal_left;

	x = 0 - width;
	y = 680;

	eat_left = "\0";
	eat_right = "\0";
	damaged_left = "\0";
	damaged_right = "\0";
	moving = false;
	target = false;
	player = false;
	damaged = false;
	eating = false;
	score = 0;
	speed = 5;
	fish_num = 0;
}

Fish::Fish(string img_left, string img_right, int w, int h)
	: normal_left(img_left), normal_right(img_right), true_width(w), true_height(h) {
	true_area_w = true_width;
	true_area_h = true_height;
	width = true_width;
	height = true_height;
	area_w = true_area_w;
	area_h = true_area_h;
	current_right = normal_right;
	current_left = normal_left;

	x = 0 - width;
	y = 680;
	fish = Object::create(current_right, gameplay, x, y);

	eat_left = "\0";
	eat_right = "\0";
	damaged_left = "\0";
	damaged_right = "\0";
	moving = false;
	target = false;
	player = false;
	damaged = false;
	eating = false;
	score = 0;
	speed = 5;
	fish_num = 0;
}

void Fish::create(string img_left, string img_right, int w, int h) {
	normal_left = img_left;
	normal_right = img_right;
	true_width = w;
	true_height = h;
	true_area_w = w;
	true_area_h = h;
	width = true_width;
	height = true_height;
	area_w = true_area_w;
	area_h = true_area_h;
	current_right = normal_right;
	current_left = normal_left;

	x = 0 - width;
	y = 680;
	fish = Object::create(current_right, gameplay, x, y);

	moving = false;
	target = false;
	player = false;
}

void Fish::set_fishnum(int n) {
	fish_num = n;
}

int Fish::get_fishnum() {
	return fish_num;
}

void Fish::set_scale(double size) {
	fish->setScale(size);
	width = true_width * size;
	height = true_height * size;
	area_w = true_area_w * size;
	area_h = true_area_h * size;
}

void Fish::set_contact_size(int w, int h) {
	true_area_w = w;
	true_area_h = h;
	area_w = true_area_w;
	area_h = true_area_h;
}

void Fish::set_damaged(string left, string right) {
	damaged_left = left;
	damaged_right = right;
}

void Fish::set_eat(string left, string right) {
	eat_left = left;
	eat_right = right;
}

void Fish::set_normal(string left, string right) {
	normal_left = left;
	normal_right = right;
}

void Fish::change_damaged() {
	damaged = true;
	eating = false;
	current_left = damaged_left;
	current_right = damaged_right;
}

void Fish::change_eat() {
	damaged = false;
	eating = true;
	current_left = eat_left;
	current_right = eat_right;
}

void Fish::change_normal() {
	damaged = false;
	eating = false;
	current_left = normal_left;
	current_right = normal_right;
}

bool Fish::is_damaged() {
	return damaged;
}

bool Fish::is_eating() {
	return eating;
}

void Fish::set_score(int n) {
	score = n;
}

int Fish::get_score() {
	return score;
}

void Fish::make_target() {
	target = true;
}

void Fish::make_enemy() {
	target = false;
}

bool Fish::is_target() {
	return target;
}

void Fish::set_speed(int s) {
	speed = s;
}

void Fish::move_right() {
	moving = true;
	fish->setImage(current_right);
	x += speed;
	fish->locate(gameplay, x, y);
	set_area();
}

void Fish::move_left() {
	moving = true;
	fish->setImage(current_left);
	x -= speed;
	fish->locate(gameplay, x, y);
	set_area();
}

void Fish::move_up() {
	moving = true;
	y += speed;
	fish->locate(gameplay, x, y);
	set_area();
}

void Fish::move_down() {
	moving = true;
	y -= speed;
	fish->locate(gameplay, x, y);
	set_area();
}

void Fish::move_home() {
	moving = false;
	x = 0 - width;
	y = 680;
	fish->locate(gameplay, x, y);
	set_area();
}

void Fish::move_to(int px, int py) {
	moving = false;
	x = px;
	y = py;
	fish->locate(gameplay, x, y);
	set_area();
}

bool Fish::is_moving() {
	return moving;
}

void Fish::set_area() {
	p[0][0] = x + width / 2 - area_w / 2; // 좌하단 x
	p[0][1] = y + height / 2 - area_h / 2; // 좌하단 y
	p[1][0] = x + width / 2 + area_w / 2; // 우하단 x
	p[1][1] = y + height / 2 - area_h / 2; // 우하단 y
	p[2][0] = x + width / 2 - area_w / 2; // 좌상단 x
	p[2][1] = y + height / 2 + area_h / 2; // 좌상단 y
	p[3][0] = x + width / 2 + area_w / 2; // 우상단 x
	p[3][1] = y + height / 2 + area_h / 2; // 우상단 y
}

int Fish::get_x() {
	return x;
}

int Fish::get_y() {
	return y;
}

int Fish::get_width() {
	return width;
}

int Fish::get_height() {
	return height;
}