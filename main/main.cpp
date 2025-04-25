#define CVP_HELP
#ifdef CVP_HELP
#undef CVP_HELP
#include "readme.h"
#else
#ifdef CVP
#include "Game.h"
#include "pvzData.h"
int sun_num = 9990;
int level_num = 100;
void cvp_ex_init() {
	Pvz::TabPageInsert([]() {Fl_Window* fwin = new Fl_Window(480, 690, u8"僵王血量");
	{
		Fl_Value_Input* value_hp = new Fl_Value_Input(20, 20, 60, 30);
		Fl_Button* button_hp = new Fl_Button(100, 20, 120, 30, u8"修改僵王血量");
		button_hp->callback([](Fl_Widget*, void* that) {  *(DWORD*)0x52361Eul = 0; *(DWORD*)0x523624ul = (DWORD)((Fl_Value_Input*)that)->value(); }, value_hp);
	}fwin->end(); return fwin; });
	*Pvz::DrawHook() += [](Pvz::Graphics* g) {
		Pvz::DrawHook()->Recur(g);
		if (!Pvz::gGameApp->mBoard)return;
		Pvz::Zombie* boss = nullptr;
		while (Pvz::gGameApp->mBoard->Next(boss)) {
			if (boss->type != Pvz::Zombie::Type::ZOMBOSS)continue;
			Pvz::DrawString(g, 600, 570, Pvz::format(u8"%d/%d", boss->hp, boss->hpMax), Pvz::FONT_DWARVENTODCRAFT18, Pvz::Color(0xffu, 0x0u, 0x0u, 0xffu));
			break;
		}
	};
	return;
	Pvz::TabPageInsert([]() {Fl_Window* fwin = new Fl_Window(480, 690, u8"布阵");
	{
		Fl_Value_Input* value_sunnum = new Fl_Value_Input(20, 20, 60, 30);
		value_sunnum->value(Cvp::RegRead<DWORD>(REG_DWORD, u8"makebuild_sunnum"));
		Fl_Button* button_sunnum = new Fl_Button(100, 20, 80, 30, u8"修改阳光");
		button_sunnum->callback([](Fl_Widget*, void* _that) {if (Pvz::gGameApp->mBoard) { Pvz::gGameApp->mBoard->sunValue = (int)((Fl_Value_Input*)_that)->value(); Cvp::RegWrite<DWORD>(REG_DWORD, (DWORD)((Fl_Value_Input*)_that)->value(), u8"makebuild_sunnum"); }}, value_sunnum);

		Fl_Value_Input* value_flags = new Fl_Value_Input(20, 70, 60, 30);
		value_flags->value(Cvp::RegRead<DWORD>(REG_DWORD, u8"makebuild_flags"));
		Fl_Button* button_flags = new Fl_Button(100, 70, 80, 30, u8"修改轮数");
		button_flags->callback([](Fl_Widget*, void* _that) {if (Pvz::gGameApp->mBoard && Pvz::gGameApp->mBoard->mLevelProp) { Pvz::gGameApp->mBoard->mLevelProp->flags = (int)((Fl_Value_Input*)_that)->value(); Cvp::RegWrite<DWORD>(REG_DWORD, (DWORD)((Fl_Value_Input*)_that)->value(), u8"makebuild_flags"); }}, value_flags);

		Fl_Button* button_finish = new Fl_Button(200, 20, 80, 30, u8"结束本关");
		button_finish->callback([](Fl_Widget*) {if (Pvz::gGameApp->mBoard) { Pvz::gGameApp->mBoard->nowwaveNum = Pvz::gGameApp->mBoard->maxWaveNum; Pvz::gGameApp->mBoard->nextwaveSpawnCountdown = 1; }});

		Fl_Check_Button* check_freeplant = new Fl_Check_Button(200, 70, 80, 30, u8"免费种植");
		check_freeplant->callback([](Fl_Widget*, void* _this) {Pvz::gGameApp->freePlant = ((Fl_Check_Button*)_this)->value(); }, check_freeplant);

		Fl_Button* button_autoladder = new Fl_Button(300, 20, 80, 30, u8"智能搭梯");
		button_autoladder->callback([](Fl_Widget*) {
			if (!Pvz::gGameApp->mBoard)return;
			Pvz::Plant* p = nullptr;
			while (Pvz::gGameApp->mBoard->Next(p))if (p->type == Pvz::Plant::Type::PUMPKIN || p->imitaterType == Pvz::Plant::Type::PUMPKIN)if (p->col >= 1 && p->col <= 3)if (Pvz::gGameApp->mBoard->gridType[p->col][p->row] != Pvz::Board::GridType::POOL)Pvz::gGameApp->mBoard->NewLadder(p->row, p->col);
			});

		Fl_Button* button_white = new Fl_Button(300, 70, 80, 30, u8"植物全白");
		button_white->callback([](Fl_Widget*) {
			if (!Pvz::gGameApp->mBoard)return;
			Pvz::Plant* p = nullptr;
			while (Pvz::gGameApp->mBoard->Next(p)) {
				if (p->type == Pvz::Plant::Type::PUMPKIN && !(p->col >= 1 && p->col <= 3 && Pvz::gGameApp->mBoard->gridType[p->col][p->row] != Pvz::Board::GridType::POOL))continue;
				if (((int)p->type) < ((int)Pvz::Plant::Type::GATLING_PEA)) {
					p->imitaterType = p->type;
					p->type = Pvz::Plant::Type::IMITATER;
					p->state = Pvz::Plant::State::IMMITATER_TURNING;
					if ((*(Pvz::gGameApp->mAnimsLists->mAnimList))[p->mAnimID])(*(Pvz::gGameApp->mAnimsLists->mAnimList))[p->mAnimID]->loopCount = 1, (*(Pvz::gGameApp->mAnimsLists->mAnimList))[p->mAnimID]->updateRate = 1.0f, (*(Pvz::gGameApp->mAnimsLists->mAnimList))[p->mAnimID]->lastUpdateRate = 0.99f;
				}
			}
			});

		Fl_Button* button_weak = new Fl_Button(20, 120, 80, 30, u8"植物残缺");
		button_weak->callback([](Fl_Widget*) {
			if (!Pvz::gGameApp->mBoard)return;
			Pvz::Plant* p = nullptr;
			while (Pvz::gGameApp->mBoard->Next(p)) {
				if (p->type == Pvz::Plant::Type::PUMPKIN && !(p->col >= 1 && p->col <= 3 && Pvz::gGameApp->mBoard->gridType[p->col][p->row] != Pvz::Board::GridType::POOL))continue;
				if (p->type == Pvz::Plant::Type::PUMPKIN || p->type == Pvz::Plant::Type::SPIKEROCK || p->type == Pvz::Plant::Type::WALL_NUT || p->type == Pvz::Plant::Type::TALL_NUT || p->type == Pvz::Plant::Type::GARLIC)p->hp = 1;
			}
			});

		Fl_Button* button_hang = new Fl_Button(120, 120, 80, 30, u8"植物悬空");
		button_hang->callback([](Fl_Widget*) {
			if (!Pvz::gGameApp->mBoard)return;
			Pvz::Plant* p = nullptr;
			while (Pvz::gGameApp->mBoard->Next(p)) {
				if (p->type == Pvz::Plant::Type::COB_CANNON) {
					auto list = Pvz::gGameApp->mBoard->GetGridPlantList(p->row, p->col + 1);
					if (list.mBottom)list.mBottom->Kill();
				}
				if (p->type == Pvz::Plant::Type::SUN_SHROOM || p->type == Pvz::Plant::Type::PUFF_SHROOM)if (Pvz::gGameApp->mBoard->gridType[p->col][p->row] == Pvz::Board::GridType::POOL) {
					auto list = Pvz::gGameApp->mBoard->GetGridPlantList(p->row, p->col);
					if (list.mBottom)list.mBottom->Kill();
				}
			}
			});
	}fwin->end(); return fwin; });
}
#endif
#endif