#include <ctime>
#include <cstdlib>

#include "fish.h"
#include "number.h"

ScenePtr home;
ScenePtr gameplay;
ScenePtr howtoplay;
ScenePtr gameover;
ScenePtr gameclear;

ObjectPtr start_button;
ObjectPtr play_button;
ObjectPtr quit_button1, quit_button2;
ObjectPtr tryagain_button, playagain_button;

Number yourscore_card_gameover[7];
Number highscore_card_gameover[7];
Number yourscore_card_gameclear[7];
Number highscore_card_gameclear[7];

SoundPtr home_s;
SoundPtr ingame_s;
SoundPtr gameover_s;
SoundPtr gameclear_s;
SoundPtr button_s;
SoundPtr damaged_s;
SoundPtr eat_s;
SoundPtr levelup_s;
SoundPtr warning_s;
SoundPtr heal_s;
SoundPtr grow_s;

bool playinggame = false;

ObjectPtr heart1, heart2, heart3;
ObjectPtr fish1_mini, fish2_mini, fish3_mini, fish4_mini, fish5_mini, fish6_mini;
ObjectPtr level_badge;
ObjectPtr upper_bar;

ObjectPtr word_life, word_level, word_score, word_mission;

Number score_card[7];
Number f1_counter, f2_counter, f3_counter, f4_counter, f5_counter, f6_counter;

Fish fish1[20];
Fish fish2[20];
Fish fish3[20];
Fish fish4[20];
Fish fish5[20];
Fish fish6[15];
Fish player;
Fish healpack;

TimerPtr leftT, rightT, upT, downT;
TimerPtr respawn_t;
TimerPtr move_t;
TimerPtr damaged_t;
TimerPtr eat_t;

int mission_n = 1;
int life_count = 3;
int gamescore = 0;
int highscore = 0;
int fish1_count = 0;
int fish2_count = 0;
int fish3_count = 0;
int fish4_count = 0;
int fish5_count = 0;
//int fish6_count = 0;

bool fish1_show = true;
bool fish2_show = true;
bool fish3_show = false;
bool fish4_show = false;
bool fish5_show = false;
bool fish6_show = false;

int fish1_prob = 90;
int fish2_prob = 70;
int fish3_prob = 0;
int fish4_prob = 0;
int fish5_prob = 0;
int fish6_prob = 0;

// 게임에 필요한 object와 timer를 생성 및 설정
void InitGame();
// 물고기와 player 원위치, 초기 설정 복구
void InitObj();
// 점수판에 점수 업데이트
void UpdateScore(int, Number*);
// 물고기 분류 번호 별로 먹은 물고기 count
void FishCount(int);
// 물고기와 player 접촉 여부 판단
int IsContact(Fish&, Fish&);
// 물고기 시작 위치 랜덤 지정 후, 출발
void RandomStart(Fish&);
// 입력받은 값을 확률로 계산하여 리스폰 여부 반환
bool RespawnChance(int);
// 스테이지별 미션, player 크기 및 속도, 아이템 출현 등을 설정
void SetStage(int);
// 미션 완료 여부 판별
void CheckMission(int&);

void InitGame() {

	life_count = 3;
	gamescore = 0;
	mission_n = 1;

	for (int i = 0; i < 15; i++) {
		fish6[i].create("Images/fish6_L.png", "Images/fish6_R.png", 793, 289);
		fish6[i].set_contact_size(705, 164);
		fish6[i].set_speed(9);
		fish6[i].make_enemy();
		fish6[i].set_score(100);
		fish6[i].move_home();
		fish6[i].set_fishnum(6);
		fish6[i].set_scale(0.55f);
	}

	for (int i = 0; i < 20; i++) {
		fish5[i].create("Images/fish5_L.png", "Images/fish5_R.png", 345, 186);
		fish5[i].set_contact_size(276, 128);
		fish5[i].set_speed(10);
		fish5[i].make_enemy();
		fish5[i].set_score(100);
		fish5[i].move_home();
		fish5[i].set_fishnum(5);
		fish5[i].set_scale(0.75f);
	}

	for (int i = 0; i < 20; i++) {
		fish4[i].create("Images/fish4_L.png", "Images/fish4_R.png", 163, 77);
		fish4[i].set_contact_size(141, 68);
		fish4[i].set_speed(7);
		fish4[i].make_enemy();
		fish4[i].set_score(50);
		fish4[i].move_home();
		fish4[i].set_fishnum(4);
		//fish4[i].set_scale(0.9f);
	}

	for (int i = 0; i < 20; i++) {
		fish3[i].create("Images/fish3_L.png", "Images/fish3_R.png", 72, 56);
		fish3[i].set_contact_size(60, 41);
		fish3[i].set_speed(8);
		fish3[i].make_enemy();
		fish3[i].set_score(20);
		fish3[i].move_home();
		fish3[i].set_fishnum(3);
		fish3[i].set_scale(1.2f);
	}

	for (int i = 0; i < 20; i++) {
		fish2[i].create("Images/fish2_L.png", "Images/fish2_R.png", 58, 32);
		fish2[i].set_contact_size(48, 22);
		fish2[i].set_speed(6);
		fish2[i].make_enemy();
		fish2[i].set_score(10);
		fish2[i].move_home();
		fish2[i].set_fishnum(2);
		fish2[i].set_scale(1.1f);
	}

	for (int i = 0; i < 20; i++) {
		fish1[i].create("Images/fish1_L.png", "Images/fish1_R.png", 35, 8);
		fish1[i].set_contact_size(35, 8);
		fish1[i].set_speed(9);
		fish1[i].make_target();
		fish1[i].set_score(5);
		fish1[i].move_home();
		fish1[i].set_fishnum(1);
	}

	healpack.create("Images/heal.png", "Images/heal.png", 157, 121);
	healpack.set_contact_size(157, 121);
	healpack.set_speed(2);
	healpack.make_target();
	healpack.set_score(50);
	healpack.move_home();
	healpack.set_fishnum(10);
	healpack.set_scale(0.5f);

	player.create("Images/P_L.png", "Images/P_R.png", 185, 153);
	player.set_damaged("Images/P_damaged_L.png", "Images/P_damaged_R.png");
	player.set_eat("Images/P_eat_L.png", "Images/P_eat_R.png");
	player.set_contact_size(158, 107);
	player.move_to(600, 300);
	player.set_area();
	player.set_speed(6);

	//player.set_scale(0.4f);

	// 게임 화면 상단 바
	upper_bar = Object::create("Images/game_board.png", gameplay, 0, 600);

	word_life = Object::create("Images/life_w.png", gameplay, 228, 670);
	heart1 = Object::create("Images/life.png", gameplay, 180, 625);
	heart2 = Object::create("Images/life.png", gameplay, 240, 625);
	heart3 = Object::create("Images/life.png", gameplay, 300, 625);

	word_score = Object::create("Images/score.png", gameplay, 440, 670);
	score_card[6].create(gameplay, 400, 620);
	score_card[5].create(gameplay, 425, 620);
	score_card[4].create(gameplay, 450, 620);
	score_card[3].create(gameplay, 475, 620);
	score_card[2].create(gameplay, 500, 620);
	score_card[1].create(gameplay, 525, 620);
	score_card[0].create(gameplay, 550, 620);

	word_level = Object::create("Images/level.png", gameplay, 35, 670);
	level_badge = Object::create("Images/level1.png", gameplay, 47, 610);
	level_badge->setScale(0.9f);

	word_mission = Object::create("Images/mission.png", gameplay, 605, 670);
	fish1_mini = Object::create("Images/mission1.png", gameplay, 740, 685);
	fish2_mini = Object::create("Images/mission2.png", gameplay, 855, 680);
	fish3_mini = Object::create("Images/lock3.png", gameplay, 985, 675);
	fish4_mini = Object::create("Images/lock4.png", gameplay, 1115, 675);
	fish5_mini = Object::create("Images/lock5.png", gameplay, 730, 615);
	fish6_mini = Object::create("Images/lock6.png", gameplay, 935, 615);

	fish1_mini->setScale(0.8f);
	fish2_mini->setScale(0.8f);
	fish3_mini->setScale(0.8f);
	fish4_mini->setScale(0.8f);
	fish5_mini->setScale(0.8f);
	fish6_mini->setScale(0.8f);

	f1_counter.create(gameplay, 785, 670);
	f2_counter.create(gameplay, 908, 670);
	f3_counter.create(gameplay, 1042, 670);
	f4_counter.create(gameplay, 1200, 670);
	f5_counter.create(gameplay, 840, 620);
	f6_counter.create(gameplay, 1100, 620);

	f2_counter.hide();
	f3_counter.hide();
	f4_counter.hide();
	f5_counter.hide();
	f6_counter.hide();

	// player 키조작
	leftT = Timer::create(0.01f);
	rightT = Timer::create(0.01f);
	upT = Timer::create(0.01f);
	downT = Timer::create(0.01f);

	leftT->setOnTimerCallback([&](TimerPtr timer)->bool {
		if (player.get_x() < 0)
			return true;
		if (life_count <= 0)
			return true;
		if (!playinggame)
			return true;
		player.move_left();
		timer->set(0.01f);
		timer->start();

		return true;
		});

	rightT->setOnTimerCallback([&](TimerPtr timer)->bool {
		if (player.get_x() > 1280 - player.get_width())
			return true;
		if (life_count <= 0)
			return true;
		if (!playinggame)
			return true;
		player.move_right();
		timer->set(0.01f);
		timer->start();

		return true;
		});

	upT->setOnTimerCallback([&](TimerPtr timer)->bool {
		if (player.get_y() > 600 - player.get_height())
			return true;
		if (life_count <= 0)
			return true;
		if (!playinggame)
			return true;
		player.move_up();
		timer->set(0.01f);
		timer->start();

		return true;
		});

	downT->setOnTimerCallback([&](TimerPtr timer)->bool {
		if (player.get_y() < 0)
			return true;
		if (life_count <= 0)
			return true;
		if (!playinggame)
			return true;
		player.move_down();
		timer->set(0.01f);
		timer->start();

		return true;
		});

	gameplay->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		if (key == KeyCode::KEY_A || key == KeyCode::KEY_CAPITAL_A || key == KeyCode::KEY_LEFT_ARROW) {
			if (pressed)
				leftT->start();
			else
				leftT->stop();
		}

		if (key == KeyCode::KEY_W || key == KeyCode::KEY_CAPITAL_W || key == KeyCode::KEY_UP_ARROW) {
			if (pressed)
				upT->start();
			else
				upT->stop();
		}

		if (key == KeyCode::KEY_D || key == KeyCode::KEY_CAPITAL_D || key == KeyCode::KEY_RIGHT_ARROW) {
			if (pressed)
				rightT->start();
			else
				rightT->stop();
		}

		if (key == KeyCode::KEY_S || key == KeyCode::KEY_CAPITAL_S || key == KeyCode::KEY_DOWN_ARROW) {
			if (pressed)
				downT->start();
			else
				downT->stop();
		}


		return true;
		});

	respawn_t = Timer::create(0.5f);

	respawn_t->setOnTimerCallback([&](TimerPtr timer)->bool {
		if (fish1_show && RespawnChance(fish1_prob))
			for (int i = 0; i < 20; i++) {
				if (!fish1[i].is_moving()) {
					RandomStart(fish1[i]);
					break;
				}
				else continue;
			}

		if (fish2_show && RespawnChance(fish2_prob))
			for (int i = 0; i < 20; i++) {
				if (!fish2[i].is_moving()) {
					RandomStart(fish2[i]);
					break;
				}
				else continue;
			}


		if (fish3_show && RespawnChance(fish3_prob))
			for (int i = 0; i < 20; i++) {
				if (!fish3[i].is_moving()) {
					RandomStart(fish3[i]);
					break;
				}
				else continue;
			}

		if (fish4_show && RespawnChance(fish4_prob))
			for (int i = 0; i < 20; i++) {
				if (!fish4[i].is_moving()) {
					RandomStart(fish4[i]);
					break;
				}
				else continue;
			}

		if (fish5_show && RespawnChance(fish5_prob))
			for (int i = 0; i < 20; i++) {
				if (!fish5[i].is_moving()) {
					RandomStart(fish5[i]);
					break;
				}
				else continue;
			}

		if (fish6_show && RespawnChance(fish6_prob))
			for (int i = 0; i < 15; i++) {
				if (!fish6[i].is_moving()) {
					RandomStart(fish6[i]);
					break;
				}
				else continue;
			}

		timer->set(0.5f);
		timer->start();

		return true;
		});

	damaged_t = Timer::create(1.5f);
	damaged_t->setOnTimerCallback([&](TimerPtr timer)->bool {
		player.change_normal();

		timer->set(1.5f);
		return true;
		});
	eat_t = Timer::create(2.f);
	eat_t->setOnTimerCallback([&](TimerPtr timer)->bool {
		player.change_normal();

		timer->set(2.f);
		return true;
		});

	SetStage(mission_n); // 시작할 스테이지

}

void InitObj() {
	player.move_to(2000, 1000);
	
	respawn_t->stop();
	move_t->stop();

	for (int i = 0; i < 10; i++) {
		if (fish1[i].is_moving())
			fish1[i].move_home();
		if (fish2[i].is_moving())
			fish2[i].move_home();
		if (fish3[i].is_moving())
			fish3[i].move_home();
		if (fish4[i].is_moving())
			fish4[i].move_home();
		if (fish5[i].is_moving())
			fish5[i].move_home();
		if (fish6[i].is_moving())
			fish6[i].move_home();
	}

	for (int i = 0; i < 10; i++) {
		fish1[i].make_target();
		fish2[i].make_enemy();
		fish3[i].make_enemy();
		fish4[i].make_enemy();
		fish5[i].make_enemy();
		fish6[i].make_enemy();
	}

	player.move_to(600, 300);
	//player.set_scale(player_size1);
	player.change_normal();

	fish1_show = true;
	fish2_show = true;
	fish3_show = false;
	fish4_show = false;
	fish5_show = false;
	fish6_show = false;

	fish3_mini->setImage("Images/lock3.png");
	fish4_mini->setImage("Images/lock4.png");
	fish5_mini->setImage("Images/lock5.png");
	fish6_mini->setImage("Images/lock6.png");

	f1_counter.show();
	f2_counter.hide();
	f3_counter.hide();
	f4_counter.hide();
	f5_counter.hide();
	f6_counter.hide();
}

void UpdateScore(int score, Number *card) {
	for (int i = 0; i < 7; i++) {
		card[i].set(score % 10);
		score /= 10;
	}
}

void FishCount(int fishnum) {
	switch (fishnum) {
	case 1:
		fish1_count--;
		f1_counter.decrease();
		return;
	case 2:
		fish2_count--;
		f2_counter.decrease();
		return;
	case 3:
		fish3_count--;
		f3_counter.decrease();
		return;
	case 4:
		fish4_count--;
		f4_counter.decrease();
		return;
	case 5:
		fish5_count--;
		f5_counter.decrease();
		return;
	case 10:
		life_count = 3;
		heart1->setImage("Images/life.png");
		heart2->setImage("Images/life.png");
		heart3->setImage("Images/life.png");
		heal_s->play();
		return; // 힐팩
	default:
		return;
	}
}

// 물고기의 네 꼭지점 중 하나의 좌표가 player의 area 영역 안에 들어오거나,
// player의 네 꼭지점 중 하나가 물고기의 area 영역 안에 들어가면 접촉한 것으로 판단
int IsContact(Fish& player_fish, Fish& obj_fish) {
	for (int i = 0; i < 4; i++) {
		if (player_fish.p[i][0] > obj_fish.p[0][0] && player_fish.p[i][0] < obj_fish.p[1][0]) //객체의 x좌표 fish area_w 내 확인
			if (player_fish.p[i][1] > obj_fish.p[0][1] && player_fish.p[i][1] < obj_fish.p[2][1]) {
				if (obj_fish.is_target()) {
					eat_s->play();
					obj_fish.move_home();
					if (!player_fish.is_damaged()) {
						player_fish.change_eat();
						eat_t->start();
					}
					gamescore += obj_fish.get_score();
					UpdateScore(gamescore, score_card);
					FishCount(obj_fish.get_fishnum());
					CheckMission(mission_n);
					return 1; // 먹이와 접촉
				}
				else if (!player_fish.is_damaged()) {
					damaged_s->play();
					if (player_fish.is_eating()) {
						eat_t->stop();
						eat_t->set(2.0f);
					}
					player_fish.change_damaged();
					damaged_t->start();
					life_count--;
					switch (life_count) {
					case 2:
						heart3->setImage("Images/life_off.png");
						break;
					case 1:
						heart2->setImage("Images/life_off.png");
						break;
					case 0:		//gameover
						ingame_s->stop();
						heart1->setImage("Images/life_off.png");
						playinggame = false;
						InitObj();
						if (gamescore > highscore) {
							highscore = gamescore;
						}
						UpdateScore(gamescore, yourscore_card_gameover);
						UpdateScore(highscore, highscore_card_gameover);
						gameover->enter();
						gameover_s->play();

						break;
					default:
						break;
					return -1;
					} 
				} // 적과 접촉
			} //객체의 y좌표 fish area_h 내 확인

		if (obj_fish.p[i][0] > player_fish.p[0][0] && obj_fish.p[i][0] < player_fish.p[1][0])//fish의 x좌표 객체의 area_w 내 확인
			if (obj_fish.p[i][1] > player_fish.p[0][1] && obj_fish.p[i][1] < player_fish.p[2][1]) {
				if (obj_fish.is_target()) {
					eat_s->play();
					obj_fish.move_home();
					if (!player_fish.is_damaged()) {
						player_fish.change_eat();
						eat_t->start();
					}
					gamescore += obj_fish.get_score();
					UpdateScore(gamescore, score_card);
					FishCount(obj_fish.get_fishnum());
					CheckMission(mission_n);
					return 1;
				}
				else if (!player_fish.is_damaged()) {
					damaged_s->play();
					if (player_fish.is_eating()) {
						eat_t->stop();
						eat_t->set(2.0f);
					}
					player_fish.change_damaged();
					damaged_t->start();
						life_count--;
					switch (life_count) {
					case 2:
						heart3->setImage("Images/life_off.png");
						break;
					case 1:
						heart2->setImage("Images/life_off.png");
						break;
					case 0:		//gameover
						ingame_s->stop();
						heart1->setImage("Images/life_off.png");
						playinggame = false;
						InitObj();
						if (gamescore > highscore) {
							highscore = gamescore;
						}
						UpdateScore(gamescore, yourscore_card_gameover);
						UpdateScore(highscore, highscore_card_gameover);
						gameover->enter();
						gameover_s->play();

						break;
					default:
						break;
						return -1; 
					}
				} // 적과 접촉
			} //fish의 y좌표 객체의 area_h 내 확인
	}
	return 0; //접촉하지 않음

}

void RandomStart(Fish& fish) {
	move_t = Timer::create(0.01f);
	int rn = rand() % 40; // 40가지 경우의 수 (좌 20, 우 20)

	if (rn < 20) {
		fish.move_to(-10 - fish.get_width(), rn * 30); // x: 왼쪽 끝, y: 20군데 중 하나
		move_t->setOnTimerCallback([&](TimerPtr t)->bool {
			if (IsContact(player, fish) == 1) {
				return true;
			} // '먹이'일 경우, 움직임 종료

			if (fish.get_x() > 1290) {
				fish.move_home();
				return true;
			} // 오른쪽 끝 도달 시 움직임 종료
				
			fish.move_right();
			t->set(0.01f);
			t->start();

			return true;
			});
		move_t->start();
	}
	if (rn >= 20) {
		fish.move_to(1290, rn % 20 * 30); // x: 오른쪽 끝, y: 20군데 중 하나
		move_t->setOnTimerCallback([&](TimerPtr t)->bool {
			if (IsContact(player, fish) == 1) {
				return true;
			} // '먹이'일 경우, 움직임 종료

			if (fish.get_x() < -10 - fish.get_width()) {
				fish.move_home();
				return true;
			} // 왼쪽 끝 도달 시 움직임 종료

			fish.move_left();
			t->set(0.01f);
			t->start();

			return true;
			});
		move_t->start();
	}
}

bool RespawnChance(int p) {
	char pool[100] = {0, };

	for (int i = 0; i < p; i++)
		pool[i] = 1;

	int rn = rand() % 100;

	if (pool[rn] == 1)
		return true;
	else
		return false;
}

void SetStage(int n) {
	const float player_size1 = 0.2;
	const float player_size2 = 0.32;
	const float player_size3 = 0.48;
	const float player_size4 = 0.68;
	const float player_size5 = 0.84;
	
	char img[20];
	sprintf_s(img, "Images/level%d.png", n);
	level_badge->setImage(img);

	switch (n) {
	case 1:
		life_count = 3;
		heart1->setImage("Images/life.png");
		heart2->setImage("Images/life.png");
		heart3->setImage("Images/life.png");

		gamescore = 0;
		UpdateScore(gamescore, score_card);
		fish1_prob = 70;
		fish2_prob = 90;
		fish1_show = true;
		fish2_show = true;

		fish1_count = 5;
		f1_counter.set(5);

		fish2_count = 0;
		fish3_count = 0;
		fish4_count = 0;
		fish5_count = 0;

		player.set_scale(player_size1);

		return;
	case 2:
		fish1_count = 10;
		f1_counter.set(10);

		levelup_s->play();

		return;
	case 3:
		fish1_prob = 70;
		fish2_prob = 50;
		fish3_prob = 100;

		fish3_show = true;
		fish3_mini->setImage("Images/mission3.png");

		fish1_count = 10;
		fish2_count = 5;
		f1_counter.set(10);
		f2_counter.set(5);

		f2_counter.show();

		for (int i = 0; i < 10; i++) {
			fish2[i].make_target();
		}

		grow_s->play();
		player.set_scale(player_size2);

		levelup_s->play();

		return;
	case 4:
		fish1_count = 10;
		fish2_count = 10;
		f1_counter.set(10);
		f2_counter.set(10);

		levelup_s->play();

		return;
	case 5:
		fish1_prob = 50;
		fish2_prob = 70;
		fish3_prob = 40;
		fish4_prob = 85;

		fish4_show = true;
		fish4_mini->setImage("Images/mission4.png");

		fish1_count = 7;
		fish2_count = 7;
		fish3_count = 7;
		f1_counter.set(7);
		f2_counter.set(7);
		f3_counter.set(7);

		f3_counter.show();

		for (int i = 0; i < 10; i++) {
			fish3[i].make_target();
		}

		grow_s->play();
		player.set_scale(player_size3);
		RandomStart(healpack);

		levelup_s->play();

		return;
	case 6:
		f1_counter.hide();

		fish2_count = 10;
		fish3_count = 7;
		f2_counter.set(10);
		f3_counter.set(7);

		levelup_s->play();

		return;
	case 7:
		fish2_count = 7;
		fish3_count = 13;
		f2_counter.set(7);
		f3_counter.set(13);

		levelup_s->play();

		return;
	case 8:
		f2_counter.hide();

		fish3_count = 15;
		f3_counter.set(15);

		levelup_s->play();

		return;
	case 9:
		fish1_prob = 0;
		fish2_prob = 5;
		fish3_prob = 50;
		fish4_prob = 30;
		fish5_prob = 60;

		fish1_show = false;
		fish5_show = true;
		fish5_mini->setImage("Images/mission5.png");

		fish3_count = 7;
		fish4_count = 10;
		f3_counter.set(7);
		f4_counter.set(10);

		f4_counter.show();

		for (int i = 0; i < 10; i++) {
			fish4[i].make_target();
		}

		grow_s->play();
		player.set_scale(player_size4);
		player.set_speed(7);
		RandomStart(healpack);

		levelup_s->play();

		return;
	case 10:
		fish3_count = 5;
		fish4_count = 13;
		f3_counter.set(5);
		f4_counter.set(13);

		levelup_s->play();

		return;
	case 11:
		f3_counter.hide();

		fish4_count = 15;
		f4_counter.set(15);

		levelup_s->play();

		return;
	case 12:
		fish2_prob = 0;
		fish3_prob = 5;
		fish4_prob = 40;
		fish5_prob = 35;
		fish6_prob = 45;

		fish2_show = false;
		fish6_show = true;
		fish6_mini->setImage("Images/mission6.png");

		for (int i = 0; i < 10; i++) {
			fish5[i].make_target();
		}

		fish4_count = 7;
		fish5_count = 10;
		f4_counter.set(7);
		f5_counter.set(10);

		f5_counter.show();

		grow_s->play();
		player.set_scale(player_size5);
		player.set_speed(8);
		RandomStart(healpack);

		warning_s->play();

		return;
	case 13:
		fish4_count = 7;
		fish5_count = 12;
		f4_counter.set(7);
		f5_counter.set(12);

		levelup_s->play();

		return;
	case 14:
		fish4_count = 7;
		fish5_count = 14;
		f4_counter.set(7);
		f5_counter.set(14);

		levelup_s->play();

		return;
	case 15:
		f4_counter.hide();

		fish5_count = 15;
		f5_counter.set(15);

		levelup_s->play();

		return;
	case 16:
		ingame_s->stop();
		playinggame = false;
		InitObj();
		if (gamescore > highscore) {
			highscore = gamescore;
		}
		UpdateScore(gamescore, yourscore_card_gameclear);
		UpdateScore(highscore, highscore_card_gameclear);

		gameclear->enter();
		gameclear_s->play();
		home_s->play(true);

		return;
	}
}

void CheckMission(int& n) {
	if (fish1_count <= 0 && fish2_count <= 0 && fish3_count <= 0 && fish4_count <= 0 && fish5_count <= 0) {
		n++;
		SetStage(n);
	}
}



int main() {
	srand((unsigned int)time(NULL));

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	home = Scene::create(" ", "Images/home.png");
	howtoplay = Scene::create(" ", "Images/howtoplay.png");
	gameplay = Scene::create(" ", "Images/background.png");
	gameover = Scene::create(" ", "Images/gameover.png");
	gameclear = Scene::create(" ", "Images/clear.png");

	home_s = Sound::create("Sounds/Theme.mp3");
	ingame_s = Sound::create("Sounds/Ingame.mp3");
	gameover_s = Sound::create("Sounds/gameover.mp3");
	gameclear_s = Sound::create("Sounds/gameclear.mp3");
	button_s = Sound::create("Sounds/button.mp3");
	damaged_s = Sound::create("Sounds/damaged.mp3");
	eat_s = Sound::create("Sounds/eat.mp3");
	levelup_s = Sound::create("Sounds/levelup.mp3");
	warning_s = Sound::create("Sounds/warning.mp3");
	heal_s = Sound::create("Sounds/heal.mp3");
	grow_s = Sound::create("Sounds/grow.mp3");

	home_s->play(true);

	start_button = Object::create("Images/start.png", home, 565, 70);
	start_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		button_s->play();
		InitGame();
		howtoplay->enter();

		return true;
		});

	play_button = Object::create("Images/play.png", howtoplay, 565, 70);
	play_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		home_s->stop();
		button_s->play();
		ingame_s->play(true);
		playinggame = true;
		gameplay->enter();
		respawn_t->start();

		return true;
		});

	tryagain_button = Object::create("Images/tryagain.png", gameover, 435, 40);
	quit_button1 = Object::create("Images/quit.png", gameover, 670, 40);
	playagain_button = Object::create("Images/playagain.png", gameclear, 435, 40);
	quit_button2 = Object::create("Images/quit.png", gameclear, 670, 40);

	tryagain_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		gameover_s->stop();
		button_s->play();
		mission_n = 1;
		SetStage(mission_n);
		playinggame = true;
		gameplay->enter();
		respawn_t->start();
		ingame_s->play(true);

		return true;
		});

	quit_button1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();

		return true;
		});

	playagain_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		gameclear_s->stop();
		button_s->play();
		home_s->stop();
		mission_n = 1;
		SetStage(mission_n);
		playinggame = true;
		gameplay->enter();
		respawn_t->start();
		ingame_s->play(true);

		return true;
		});

	quit_button2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();

		return true;
		});

	for (int i = 0; i < 7; i++) {
		yourscore_card_gameover[i].create(gameover, 360 + 25 * (6 - i), 140);
		highscore_card_gameover[i].create(gameover, 745 + 25 * (6 - i), 140);
		yourscore_card_gameclear[i].create(gameclear, 360 + 25 * (6 - i), 140);
		highscore_card_gameclear[i].create(gameclear, 745 + 25 * (6 - i), 140);
	}

	startGame(home);

	return 0;
}