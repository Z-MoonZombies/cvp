#include "Game.h"
#include "pvzData.h"
#include "ui.h"
int editspeedzombie = 0;
float editzombiespeedmin = 0.23f;
float editzombiespeedmax = 0.37f;
bool zombiespeed[9]{ true,false ,false ,false ,false ,false ,false ,false ,false };
float zombiespeedmin[9]{ 0.23f, 0.66f, 0.23f, 0.23f, 0.66f, 0.23f, 0.79f, 0.23f, 0.66f };
float zombiespeedmax[9]{ 0.37f, 0.68f, 0.37f, 0.37f, 0.68f, 0.37f, 0.81f, 0.37f, 0.68f };
int puffxmin = -5;
int puffxmax = 4;
Pvz::Card::Type mousecard = Pvz::Card::Type::NIL;//crater shovel  reset hammer
bool izbuild[8]{ true,true ,true ,true ,true ,true ,true ,true };
int izflower = -1;
int mjstate = 0;
bool mjstateshow = false;
bool collect = false;
int mjclock = -1;
int shotrowmin = 1;
int shotrowmax = 5;
int copymode = 0;
void setmouse(Pvz::Card::Type type) {
	if (!Pvz::gGameApp->mBoard)return;
	mousecard = type;
	Pvz::gGameApp->mBoard->ThrowMouse();
	if (type == Pvz::Card::Type::BEGHOULED_CRATER) {
		Pvz::gGameApp->mBoard->mMouseProp->handItemType = Pvz::MouseProp::Type::SHOVEL;
	} else if (type == Pvz::Card::Type::BEGHOULED_RESET) {
		//Pvz::gGameApp->mBoard->mMouseProp->handItemType = Pvz::MouseProp::Type::HAMMER;
	} else {
		Pvz::gGameApp->mBoard->mMouseProp->handItemType = Pvz::MouseProp::Type::ITEM_CARD;
		Pvz::gGameApp->mBoard->mMouseProp->handCardType = mousecard;
	}
}

void cvp_ex_init() {
	Ui::WidgetManager::SetTab({ {u8"iz集成工具",Ui::WidgetManager::MakeTabPage({
		Ui::WidgetManager::MakeComboList(Ui::MakeRect_Combo(2,0,4),{u8"路障", u8"撑杆跑", u8"撑杆走", u8"铁桶", u8"矿工挖", u8"矿工左", u8"梯子跑", u8"梯子走", u8"橄榄"},editspeedzombie),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(14,0,8),editzombiespeedmin),
		Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(25,0,2),u8"--"),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(28,0,8),editzombiespeedmax),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(42,0,8),[]() {
			if (editzombiespeedmin == 0.0f || editzombiespeedmax == 0.0f) { zombiespeed[editspeedzombie] = false; return; }
			zombiespeed[editspeedzombie] = true;
			zombiespeedmin[editspeedzombie] = editzombiespeedmin;
			zombiespeedmax[editspeedzombie] = editzombiespeedmax;
			}, u8"修改速度"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(02, 1, 4), []() {setmouse(Pvz::Card::Type::PEASHOOTER); }, u8"豌豆"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(10, 1, 4), []() {setmouse(Pvz::Card::Type::SUNFLOWER); }, u8"小向"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(18, 1, 4), []() {setmouse(Pvz::Card::Type::WALL_NUT); }, u8"坚果"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(26, 1, 4), []() {setmouse(Pvz::Card::Type::POTATO_MINE); }, u8"土豆"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(34, 1, 4), []() {setmouse(Pvz::Card::Type::SNOW_PEA); }, u8"冰豆"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(02, 2, 4), []() {setmouse(Pvz::Card::Type::CHOMPER); }, u8"大嘴"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(10, 2, 4), []() {setmouse(Pvz::Card::Type::REPEATER); }, u8"双发"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(18, 2, 4), []() {setmouse(Pvz::Card::Type::PUFF_SHROOM); }, u8"小喷"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(26, 2, 4), []() {setmouse(Pvz::Card::Type::FUME_SHROOM); }, u8"大喷"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(34, 2, 4), []() {setmouse(Pvz::Card::Type::SCAREDY_SHROOM); }, u8"胆小"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(02, 3, 4), []() {setmouse(Pvz::Card::Type::SQUASH); }, u8"倭瓜"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(10, 3, 4), []() {setmouse(Pvz::Card::Type::THREEPEATER); }, u8"三线"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(18, 3, 4), []() {setmouse(Pvz::Card::Type::SPIKEWEED); }, u8"地刺"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(26, 3, 4), []() {setmouse(Pvz::Card::Type::TORCHWOOD); }, u8"火树"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(34, 3, 4), []() {setmouse(Pvz::Card::Type::SPLIT_PEA); }, u8"裂荚"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(02, 4, 4), []() {setmouse(Pvz::Card::Type::STARFRUIT); }, u8"杨桃"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(10, 4, 4), []() {setmouse(Pvz::Card::Type::MAGNET_SHROOM); }, u8"磁铁"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(18, 4, 4), []() {setmouse(Pvz::Card::Type::KERNEL_PULT); }, u8"玉米"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(26, 4, 4), []() {setmouse(Pvz::Card::Type::UMBRELLA_LEAF); }, u8"叶子"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(34, 4, 4), []() {setmouse(Pvz::Card::Type::BEGHOULED_CRATER); }, u8"铲子"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(02, 5, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_IMP); }, u8"小鬼"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(10, 5, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_CONEHEAD); }, u8"路障"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(18, 5, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_POLE_VAULTER); }, u8"撑杆"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(26, 5, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_BUCKEDHEAD); }, u8"铁桶"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(34, 5, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_BUNGEE); }, u8"小偷"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(02, 6, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_DIGGER); }, u8"矿工"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(10, 6, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_LADDER); }, u8"梯子"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(18, 6, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_FOOTBALL); }, u8"橄榄"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(26, 6, 4), []() {setmouse(Pvz::Card::Type::ZOMBIE_DANCER); }, u8"舞王"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(34, 6, 4), []() {if (Pvz::gGameApp->mBoard)Pvz::gGameApp->mBoard->mLevelProp->ClearBoard(); }, u8"清空"),
		Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(42, 1, 10), u8"小喷x min:"),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(42, 2, 10), puffxmin),
		Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(42, 3, 10), u8"小喷x max:"),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(42, 4, 10), puffxmax),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(42, 5, 10), []() {
			if (!Pvz::gGameApp->mBoard)return;
			for (auto&& p : Pvz::gGameApp->mBoard->mBuildingList) if (p.type == Pvz::Building::Type::BRAIN_IZ)p.Kill();
			for (int row = 0; row < 5; ++row) Pvz::gGameApp->mBoard->NewBrainIz(row);
			Pvz::gGameApp->mBoard->mLevelProp->progress = 0;
		}, u8"恢复脑子"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(42, 6, 10), []() {
			if (!Pvz::gGameApp->mBoard)return;
			for (auto&& p : Pvz::gGameApp->mBoard->mBuildingList) if (p.type == Pvz::Building::Type::BRAIN_IZ)p.Kill(), Pvz::gGameApp->mBoard->mLevelProp->IZTryAchieve(&p);
		}, u8"下一关"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(02,7,4),izbuild[0],u8"综合"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(12,7,4),izbuild[1],u8"控制"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(22,7,4),izbuild[2],u8"即死"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(02,8,4),izbuild[3],u8"输出"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(12,8,4),izbuild[4],u8"爆炸"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(22,8,4),izbuild[5],u8"倾斜"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(32,8,4),izbuild[6],u8"穿刺"),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(42,8,4),izbuild[7],u8"胆小"),
		Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(32,7,7),u8"花数:"),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(42,7,5),izflower),
		Ui::WidgetManager::MakeComboList(Ui::MakeRect_Combo(2,9,4),{u8"常规",u8"禁用",u8"前进",u8"踏步",u8"召唤"},mjstate),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(11,9,8),mjstateshow,u8"女仆显示"),
		Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(24,9,9),u8"女仆预设:"),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(34,9,5),mjclock),
		Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(42,9,8),collect,u8"自动收集"),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(2,10,1),shotrowmin),
		Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(6,10,4),u8"路至"),
		Ui::WidgetManager::MakeInput(Ui::MakeRect_Input(11,10,1),shotrowmax),
		Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(15,10,2),u8"路"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(18, 10, 4), []() {if (shotrowmin < 1)shotrowmin = 1; if (shotrowmax > 5)shotrowmax = 5; auto img = Ui::SharedImage::TakeScreenShot(); Ui::SharedImage(img.Image()->mWidth, img.Image()->mHeight, img.Image()->GetBits(), {0,shotrowmin * 100 - 40,450,(shotrowmax - shotrowmin) * 100 + 120}).SetClipBoard(); }, u8"截图"),
		Ui::WidgetManager::MakeComboList(Ui::MakeRect_Combo(26,10,6),{u8"无栈位",u8"行栈位",u8"全栈位"},copymode),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(38, 10, 4),[]() {
			if (!Pvz::gGameApp->mBoard)return;
			auto getchr = [](Pvz::Plant::Type type)->char {
				switch (type) {
				case Pvz::Plant::Type::NIL:return u8'*';
				case Pvz::Plant::Type::PEASHOOTER:return u8'1';
				case Pvz::Plant::Type::SUNFLOWER:return u8'h';
				case Pvz::Plant::Type::WALL_NUT:return u8'o';
				case Pvz::Plant::Type::POTATO_MINE:return u8't';
				case Pvz::Plant::Type::SNOW_PEA:return u8'b';
				case Pvz::Plant::Type::CHOMPER:return u8'z';
				case Pvz::Plant::Type::REPEATER:return u8'2';
				case Pvz::Plant::Type::PUFF_SHROOM:return u8'p';
				case Pvz::Plant::Type::FUME_SHROOM:return u8'd';
				case Pvz::Plant::Type::SCAREDY_SHROOM:return u8'x';
				case Pvz::Plant::Type::SQUASH:return u8'w';
				case Pvz::Plant::Type::THREEPEATER:return u8'3';
				case Pvz::Plant::Type::SPIKEWEED:return u8'_';
				case Pvz::Plant::Type::TORCHWOOD:return u8'j';
				case Pvz::Plant::Type::SPLIT_PEA:return u8'l';
				case Pvz::Plant::Type::STARFRUIT:return u8'5';
				case Pvz::Plant::Type::MAGNET_SHROOM:return u8'c';
				case Pvz::Plant::Type::KERNEL_PULT:return u8'y';
				case Pvz::Plant::Type::UMBRELLA_LEAF:return u8's';
				default:return u8' ';
				}
			};
			Pvz::Plant::Type list[25]{
				Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,
				Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,
				Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,
				Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,
				Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL ,Pvz::Plant::Type::NIL
			};
			int stack[25]{
				0x7fffffbb,0x7fffffbc,0x7fffffbd,0x7fffffbe,0x7fffffbf,
				0x7fffffcb,0x7fffffcc,0x7fffffcd,0x7fffffce,0x7fffffcf,
				0x7fffffdb,0x7fffffdc,0x7fffffdd,0x7fffffde,0x7fffffdf,
				0x7fffffeb,0x7fffffec,0x7fffffed,0x7fffffee,0x7fffffef,
				0x7ffffffb,0x7ffffffc,0x7ffffffd,0x7ffffffe,0x7fffffff
			};
			for (auto&& p : Pvz::gGameApp->mBoard->mPlantList)list[5 * p.row + p.col] = p.type, stack[5 * p.row + p.col] = Pvz::GetID(p).mIndex;
			string str;
			if (copymode == 0) {
				str.reserve(29);
				str += getchr(list[0]); str += getchr(list[1]); str += getchr(list[2]); str += getchr(list[3]); str += getchr(list[4]); str += u8'\n';
				str += getchr(list[5]); str += getchr(list[6]); str += getchr(list[7]); str += getchr(list[8]); str += getchr(list[9]); str += u8'\n';
				str += getchr(list[10]); str += getchr(list[11]); str += getchr(list[12]); str += getchr(list[13]); str += getchr(list[14]); str += u8'\n';
				str += getchr(list[15]); str += getchr(list[16]); str += getchr(list[17]); str += getchr(list[18]); str += getchr(list[19]); str += u8'\n';
				str += getchr(list[20]); str += getchr(list[21]); str += getchr(list[22]); str += getchr(list[23]); str += getchr(list[24]);
			} else if (copymode == 1) {
				str.reserve(79);
				for (int row = 0; row < 5; ++row) {
					int* rowstack = &stack[5 * row];
					Pvz::Plant::Type* rowlist = &list[5 * row];
					int sortstack[5];
					for (int i = 0; i < 5; ++i)sortstack[i] = rowstack[i];
					std::sort(&sortstack[0], &sortstack[5]);
					Pvz::Plant::Type templist[25];
					for (int i = 0; i < 25; ++i) if (rowstack[i % 5] == sortstack[i / 5])templist[i] = rowlist[i % 5]; else templist[i] = Pvz::Plant::Type::NIL;
					string temp;
					temp.reserve(25);
					for (int i = 0; i < 25; ++i) temp += getchr(templist[i]);
					while (temp.find(u8"*****") != string::npos) temp.erase(temp.find(u8"*****"), 5);
					bool a[5]{};
					for (size_t i = 0; i < temp.size(); ++i) { if (temp[i] != u8'*')a[i % 5] = true; else if (a[i % 5])temp[i] = u8' '; }
					for (size_t i = 0; i < temp.size(); ++i) if (!a[i % 5]) temp[i] = (i < 5) ? u8'.' : u8' ';
					bool b = false;
					for (char chr : temp)if (chr != u8' ')b = true, str += chr;
					if (!b)str += u8'*';
					str += '\n';
				}
				while (str.size() >= 2 && str[str.size() - 2] == u8'*' && str[str.size() - 1] == u8'\n')str.resize(str.size() - 2);
				if (str.size() >= 1 && str[str.size() - 1] == u8'\n')str.resize(str.size() - 1);
			} else if (copymode == 2) {
			bool fullgrid[25]{};
			int rowspace[5]{ 5,5,5,5,5 };
			int space = 25;
			int col = 0, row = 0;
			auto inccol = [&]()->void {	if (rowspace[row])do { ++col; col %= 5; } while (fullgrid[col + 5 * row]); };
			auto incrow = [&]()->void { col = 0; if (space)do { ++row; row %= 5; } while (!rowspace[row]); };
			int sortstack[25];
			for (int i = 0; i < 25; ++i)sortstack[i] = stack[i];
			std::sort(&sortstack[0], &sortstack[25]);
			Pvz::Plant::Type templist[625]{};
			for (int i = 0; i < 625; ++i) if (stack[i % 25] == sortstack[i / 25])templist[i] = list[i % 25]; else templist[i] = Pvz::Plant::Type::NIL;
			string temp;
			temp.reserve(625);
			for (int i = 0; i < 625; ++i) temp += getchr(templist[i]);
			while (temp.find(u8"*************************") != string::npos) temp.erase(temp.find(u8"*************************"), 25);
			bool a[25]{};
			for (size_t i = 0; i < temp.size(); ++i) { if (temp[i] != u8'*')a[i % 25] = true; else if (a[i % 25])temp[i] = u8' '; }
			for (size_t i = 0; i < temp.size(); ++i) if (!a[i % 25]) temp[i] = (i < 25) ? u8'.' : u8' ';
			str.reserve(temp.size() / 5 * 6);
			for (size_t i = 0; i < temp.size(); ++i) if (i % 5 == 4) str += temp[i], str += u8'\n'; else str += temp[i];
			while (str.find(u8" ") != string::npos) str.erase(str.find(u8" "), 1);
			while (str.find(u8"\n\n") != string::npos) str.erase(str.find(u8"\n\n"), 1);
			while (str.find(u8"*\n") != string::npos) str.erase(str.find(u8"*\n"), 1);
			while (str.find(u8"\n\n\n\n\n") != string::npos) str.erase(str.find(u8"\n\n\n\n\n"), 5);
			if (str.size() && str[1] == u8'\n')str.replace(0, 0, u8"*");
			while (str.find(u8"\n\n") != string::npos) str.replace(str.find(u8"\n\n") + 1, 0, u8"*");
			while (str.size() >= 2 && str[str.size() - 2] == u8'*' && str[str.size() - 1] == u8'\n')str.resize(str.size() - 2);
			if (str.size() >= 1 && str[str.size() - 1] == u8'\n')str.resize(str.size() - 1);
		}
		Cvp::ClipBoardWrite(str);
		}, u8"复制"),
		Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(46, 10, 4), []() {
			if (!Pvz::gGameApp->mBoard)return;
			Pvz::gGameApp->mBoard->mLevelProp->ClearBoard();
			for (int row = 0; row < 5; ++row) Pvz::gGameApp->mBoard->NewBrainIz(row);
			Pvz::gGameApp->mBoard->mPlantList.mSize = 0;
			Pvz::gGameApp->mBoard->mPlantList.mCapacity = 0;
			Pvz::gGameApp->mBoard->mPlantList.mNextIndex = 0;
			auto str = Cvp::ClipBoardRead<string>();
			bool fullgrid[25]{};
			int rowspace[5]{ 5,5,5,5,5 };
			int space = 25;
			bool prevnil = true;
			int col = 0, row = 0;
			auto plant = [&](Pvz::Plant::Type type)->void {
				if (fullgrid[col + 5 * row]) return;
				if (rowspace[row]) --rowspace[row], --space;
				fullgrid[col + 5 * row] = true;
				if (type != Pvz::Plant::Type::NIL)Pvz::gGameApp->mBoard->mLevelProp->NewPlantIZ(type, col, row);
			};
			auto inccol = [&]()->void {	if (rowspace[row])do { ++col; col %= 5; } while (fullgrid[col + 5 * row]); };
			auto incrow = [&]()->void { if (space)do { ++row; row %= 5; } while (!rowspace[row]); col = 0; while (fullgrid[col + 5 * row]) { ++col; col %= 5; } };
			for (char chr : str) switch (chr) {
			case u8'*':prevnil = false; inccol(); break;
			case u8'.':prevnil = false; plant(Pvz::Plant::Type::NIL); inccol(); break;
			case u8'1':prevnil = false; plant(Pvz::Plant::Type::PEASHOOTER); inccol(); break;
			case u8'h':prevnil = false; plant(Pvz::Plant::Type::SUNFLOWER); inccol(); break;
			case u8'o':prevnil = false; plant(Pvz::Plant::Type::WALL_NUT); inccol(); break;
			case u8't':prevnil = false; plant(Pvz::Plant::Type::POTATO_MINE); inccol(); break;
			case u8'b':prevnil = false; plant(Pvz::Plant::Type::SNOW_PEA); inccol(); break;
			case u8'z':prevnil = false; plant(Pvz::Plant::Type::CHOMPER); inccol(); break;
			case u8'2':prevnil = false; plant(Pvz::Plant::Type::REPEATER); inccol(); break;
			case u8'p':prevnil = false; plant(Pvz::Plant::Type::PUFF_SHROOM); inccol(); break;
			case u8'd':prevnil = false; plant(Pvz::Plant::Type::FUME_SHROOM); inccol(); break;
			case u8'x':prevnil = false; plant(Pvz::Plant::Type::SCAREDY_SHROOM); inccol(); break;
			case u8'w':prevnil = false; plant(Pvz::Plant::Type::SQUASH); inccol(); break;
			case u8'3':prevnil = false; plant(Pvz::Plant::Type::THREEPEATER); inccol(); break;
			case u8'_':prevnil = false; plant(Pvz::Plant::Type::SPIKEWEED); inccol(); break;
			case u8'j':prevnil = false; plant(Pvz::Plant::Type::TORCHWOOD); inccol(); break;
			case u8'l':prevnil = false; plant(Pvz::Plant::Type::SPLIT_PEA); inccol(); break;
			case u8'5':prevnil = false; plant(Pvz::Plant::Type::STARFRUIT); inccol(); break;
			case u8'c':prevnil = false; plant(Pvz::Plant::Type::MAGNET_SHROOM); inccol(); break;
			case u8'y':prevnil = false; plant(Pvz::Plant::Type::KERNEL_PULT); inccol(); break;
			case u8's':prevnil = false; plant(Pvz::Plant::Type::UMBRELLA_LEAF); inccol(); break;
			default:if (!prevnil) incrow(), prevnil = true; break;
			}
		}, u8"粘贴"),
	}) } });
	Pvz::BasicProp(Pvz::Zombie::Type::CONEHEAD_ZOMBIE).Func_resetSpeed += [](Pvz::Zombie* p) {
		if (zombiespeed[0])p->v = Pvz::rand(zombiespeedmin[0], zombiespeedmax[0]);
		else Cvp::Functor<void(Pvz::Zombie*)>::Recur(p);
	};
	Pvz::BasicProp(Pvz::Zombie::Type::POLE_VAULTING_ZOMBIE).Func_resetSpeed += [](Pvz::Zombie* p) {
		if (p->state == Pvz::Zombie::State::POLE_VAULTING_RUN && zombiespeed[1])p->v = Pvz::rand(zombiespeedmin[1], zombiespeedmax[1]);
		else if (p->state != Pvz::Zombie::State::POLE_VAULTING_RUN && zombiespeed[2])p->v = Pvz::rand(zombiespeedmin[2], zombiespeedmax[2]);
		else Cvp::Functor<void(Pvz::Zombie*)>::Recur(p);
	};
	Pvz::BasicProp(Pvz::Zombie::Type::BUCKETHEAD_ZOMBIE).Func_resetSpeed += [](Pvz::Zombie* p) {
		if (zombiespeed[3])p->v = Pvz::rand(zombiespeedmin[3], zombiespeedmax[3]);
		else Cvp::Functor<void(Pvz::Zombie*)>::Recur(p);
	};
	Pvz::BasicProp(Pvz::Zombie::Type::DIGGER_ZOMBIE).Func_resetSpeed += [](Pvz::Zombie* p) {
		if (p->state == Pvz::Zombie::State::DIGGER_DIG && zombiespeed[4])p->v = Pvz::rand(zombiespeedmin[4], zombiespeedmax[4]);
		else if (p->state != Pvz::Zombie::State::DIGGER_DIG && zombiespeed[5])p->v = Pvz::rand(zombiespeedmin[5], zombiespeedmax[5]);
		else Cvp::Functor<void(Pvz::Zombie*)>::Recur(p);
	};
	Pvz::BasicProp(Pvz::Zombie::Type::LADDER_ZOMBIE).Func_resetSpeed += [](Pvz::Zombie* p) {
		if (p->state == Pvz::Zombie::State::LADDER_RUN && zombiespeed[6])p->v = Pvz::rand(zombiespeedmin[6], zombiespeedmax[6]);
		else if (p->state != Pvz::Zombie::State::LADDER_RUN && zombiespeed[7])p->v = Pvz::rand(zombiespeedmin[7], zombiespeedmax[7]);
		else Cvp::Functor<void(Pvz::Zombie*)>::Recur(p);
	};
	Pvz::BasicProp(Pvz::Zombie::Type::FOOTBALL_ZOMBIE).Func_resetSpeed += [](Pvz::Zombie* p) {
		if (zombiespeed[8])p->v = Pvz::rand(zombiespeedmin[8], zombiespeedmax[8]);
		else Cvp::Functor<void(Pvz::Zombie*)>::Recur(p);
	};
	Pvz::BasicProp(Pvz::GameApp::Level::Type::I_ZOMBIE_ENDLESS).build = [](Pvz::LevelProp* _this) {
		_this->progress = 0;
		for (int row = 0; row < 5; ++row) _this->mBoard->NewBrainIz(row);
		_this->mBoard->backupMowerCount = 0;
		int puff_num;
		if (_this->flags >= 10) {
			puff_num = Pvz::rand(5, 8);
		} else if (_this->flags >= 2) {
			puff_num = Pvz::rand(limit(2, _this->flags / 3, 4), limit(2, _this->flags / 2, 6) + 1);
		} else {
			puff_num = _this->flags;
		}
		if (izflower >= 0 && izflower <= 8)puff_num = 8 - izflower;
		_this->NewPlantsIZ(Pvz::Plant::Type::SUNFLOWER, 8 - puff_num, -1);
		_this->NewPlantsIZ(Pvz::Plant::Type::PUFF_SHROOM, puff_num, -1);
		auto rnd = Pvz::RndSelecterF(7);
		if (izbuild[0])rnd.put(0.400f, 0);
		if (izbuild[1])rnd.put(0.267f, 1);
		if (izbuild[2])rnd.put(0.133f, 2);
		if (_this->flags >= 1) {
			if (izbuild[3])rnd.put(0.040f, 3);
			if (izbuild[4])rnd.put(0.040f, 4);
			if (izbuild[5])rnd.put(0.040f, 5);
			if (izbuild[6])rnd.put(0.040f, 6);
			if (izbuild[7])rnd.put(0.040f, 7);
		}
		switch (rnd.get()) {
		case 0:
			_this->NewPlantsIZ(Pvz::Plant::Type::WALL_NUT, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::TORCHWOOD, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::POTATO_MINE, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::CHOMPER, 2);
			_this->NewPlantsIZ(Pvz::Plant::Type::PEASHOOTER, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::SPLIT_PEA, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::KERNEL_PULT, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::THREEPEATER, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::SNOW_PEA, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::SQUASH, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::FUME_SHROOM, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::UMBRELLA_LEAF, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::STARFRUIT, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::MAGNET_SHROOM, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::SPIKEWEED, 2);
			break;
		case 1:
			_this->NewPlantsIZ(Pvz::Plant::Type::TORCHWOOD, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::SPLIT_PEA, 3);
			_this->NewPlantsIZ(Pvz::Plant::Type::REPEATER, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::KERNEL_PULT, 3);
			_this->NewPlantsIZ(Pvz::Plant::Type::THREEPEATER, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::SNOW_PEA, 3);
			_this->NewPlantsIZ(Pvz::Plant::Type::UMBRELLA_LEAF, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::MAGNET_SHROOM, 1);
			_this->NewPlantsIZ(Pvz::Plant::Type::SPIKEWEED, 3);
			break;
		case 2:
			_this->NewPlantsIZ(Pvz::Plant::Type::POTATO_MINE, 4);
			_this->NewPlantsIZ(Pvz::Plant::Type::CHOMPER, 3);
			_this->NewPlantsIZ(Pvz::Plant::Type::SQUASH, 3);
			_this->NewPlantsIZ(Pvz::Plant::Type::FUME_SHROOM, 4);
			_this->NewPlantsIZ(Pvz::Plant::Type::SPIKEWEED, 3);
			break;
		case 3:
			_this->NewPlantsIZ(Pvz::Plant::Type::SNOW_PEA, 9);
			_this->NewPlantsIZ(Pvz::Plant::Type::SPLIT_PEA, 4);
			_this->NewPlantsIZ(Pvz::Plant::Type::REPEATER, 4);
			break;
		case 4:
			_this->NewPlantsIZ(Pvz::Plant::Type::POTATO_MINE, 9);
			_this->NewPlantsIZ(Pvz::Plant::Type::CHOMPER, 8);
			break;
		case 5:
			_this->NewPlantsIZ(Pvz::Plant::Type::SPIKEWEED, 9);
			_this->NewPlantsIZ(Pvz::Plant::Type::STARFRUIT, 8);
			break;
		case 6:
			_this->NewPlantsIZ(Pvz::Plant::Type::FUME_SHROOM, 9);
			_this->NewPlantsIZ(Pvz::Plant::Type::MAGNET_SHROOM, 8);
			break;
		case 7:
			_this->NewPlantsIZ(Pvz::Plant::Type::SCAREDY_SHROOM, 12);
			_this->NewPlantsIZ(Pvz::Plant::Type::SUNFLOWER, 5);
			break;
		}
	};
	Pvz::MouseHook() += [](int x, int y, Cvp::MouseCode mouse)->bool {
		if (!Pvz::gGameApp->mBoard)return Pvz::MouseHook().Recur(x, y, mouse);
		if (mousecard == Pvz::Card::Type::NIL)return Pvz::MouseHook().Recur(x, y, mouse);
		if (mouse == Cvp::MouseCode::RIGHT) {
			mousecard = Pvz::Card::Type::NIL;
			Pvz::gGameApp->mBoard->ThrowMouse();
			return true;
		}
		if (mousecard == Pvz::Card::Type::BEGHOULED_CRATER) {
			Pvz::gGameApp->mBoard->UseTool(x, y, 1, Pvz::MouseProp::Type::SHOVEL);
			Pvz::gGameApp->mBoard->mMouseProp->handItemType = Pvz::MouseProp::Type::SHOVEL;
		} else if (mousecard == Pvz::Card::Type::BEGHOULED_RESET) {
			//Pvz::gGameApp->mBoard->mMouseProp->handItemType = Pvz::MouseProp::Type::HAMMER;
		} else {
			if (x > 800 || y > 600)return true;
			int col = Pvz::gGameApp->mBoard->GetCol(mousecard, x, y);
			int row = Pvz::gGameApp->mBoard->GetRow(mousecard, x, y);
			if (col == -1 || row == -1) {
				mousecard = Pvz::Card::Type::NIL;
				return true;
			}
			if (Pvz::BasicProp(mousecard).typeGroup == Pvz::Card::TypeGroup::ZOMBIE)Pvz::gGameApp->mBoard->mLevelProp->NewZombie(col, row, Pvz::BasicProp(mousecard).zombieType);
			if (Pvz::BasicProp(mousecard).typeGroup == Pvz::Card::TypeGroup::PLANT) {
				int i = Pvz::gGameApp->mBoard->mPlantList.mNextIndex;
				Pvz::gGameApp->mBoard->mLevelProp->NewPlantIZ(Pvz::BasicProp(mousecard).plantType, col, row);
				Pvz::Plant* p = Pvz::gGameApp->mBoard->mPlantList[i];
				if (p && p->type == Pvz::Plant::Type::PUFF_SHROOM) p->mX = Pvz::gGameApp->mBoard->GetX(p->col, p->row) + puffxmin + Pvz::rand(1 + puffxmax - puffxmin);
			}
			Pvz::gGameApp->mBoard->mMouseProp->handItemType = Pvz::MouseProp::Type::ITEM_CARD;
			Pvz::gGameApp->mBoard->mMouseProp->handCardType = mousecard;
		}
		return true;
	};
	Pvz::UpdateHook() += [mj = false]()mutable {
		if (Pvz::gGameApp->mBoard) {
			switch (mjstate) {
			case 1:Pvz::gGameApp->mUpdateClock = Pvz::gGameApp->mBoard->timeBattle; break;
			case 2:Pvz::gGameApp->mUpdateClock = 238; break;
			case 3:Pvz::gGameApp->mUpdateClock = 458; break;
			case 4:Pvz::gGameApp->mUpdateClock = 258; break;
			}
			for (auto&& p : Pvz::gGameApp->mBoard->mZombieList) if (p.type == Pvz::Zombie::Type::DANCING_ZOMBIE || p.type == Pvz::Zombie::Type::BACKUP_DANCER) {
				if (mjclock >= 0 && !mj)Pvz::gGameApp->mUpdateClock = mjclock + 459;
				mj = true;
				goto mjend;
			}
			mj = false;
		mjend:;
			if ((Pvz::gGameApp->mBoard->timeBattle & 0xf) == 0 && collect)for (auto&& p : Pvz::gGameApp->mBoard->mItemList) if (!p.collected) { p.MouseDown(); break; }
		}
		Pvz::UpdateHook().Recur();
	};
	Pvz::DrawHook() += []() {
		if (Pvz::gGameApp->mBoard) {
			if (mjstateshow) {
				int t = Pvz::gGameApp->mUpdateClock % 460;
				int r = t < 240 ? 255 : 0;
				int b = t >= 260 ? 255 : 0;
				int gg = 255 - r - b;
				Ui::Geo::DrawFullRect(Color(t < 260 ? 255 : 0, (t >= 240 && t < 260) ? 255 : 0, t >= 240 ? 255 : 0, 25).ARGB(), { 0,0,800,600 });
			}
			if (copymode) for (auto&& p : Pvz::gGameApp->mBoard->mPlantList) {
				Ui::GlobalFont().DrawStringA(p.mX, p.mY, CTformat<CTformat_buffer<string>, int>::format(Pvz::GetID(p).mIndex), 0xffffffff);
			}
		}
		Pvz::DrawHook().Recur();
	};
}