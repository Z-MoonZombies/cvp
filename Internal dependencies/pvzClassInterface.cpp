#include "pvzStatic.h"


namespace Pvz {
	int getCurveValue(int curve, int x1, int x2, int y1, int y2, int x) {
		__asm {
			mov edx, x1
			mov ecx, x2
			push curve
			push y2
			push y1
			mov eax, x
			mov ebx, 0x511C40ul
			call ebx
			add esp, 0xcu
		}
	}
	float getCurveValue(int curve, int x1, int x2, float y1, float y2, int x) {
		DWORD _y1 = *(DWORD*)&y1;
		DWORD _y2 = *(DWORD*)&y2;
		DWORD ans = 0;
		__asm {
			mov edx, x1
			mov ecx, x2
			push curve
			push y2
			push y1
			mov eax, x
			mov ebx, 0x511BF0ul
			call ebx
			fstp ans
			add esp, 0xcu
		}
		return *(float*)&ans;
	}
	DDImage* ImageToDDImage(const Image* _ptr) {
		__asm {
			push 0
			push 0x6A5680ul
			push 0x6A5660ul
			push 0
			push _ptr
			mov eax, 0x61EEFCul
			call eax
			add esp, 0x14u
		}
	}
	void DDImage::Draw(DWORD theColor, const Rect& theSrcRect, const Matrix3& theTransform, bool mix, const Rect& theDestRect) {
		if (!this) return;
		D3DInterface* dinterface = gGameApp->mDDInterface->mD3DInterface;
		if (!dinterface)return;
		const Matrix3* pTrans = &theTransform;
		const Rect* pSrcRect = &theSrcRect;
		const Color color(theColor);
		const Color* pColor = &color;
		const Rect* pClipRect = &theDestRect;
		IDirect3DDevice7* pd = dinterface->mD3DDevice;
		if (dinterface->PreDraw() && dinterface->CreateImageTexture(this)) {
			//dinterface->mD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFG_LINEAR);
			dinterface->mD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
			dinterface->mD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, mix ? D3DBLEND_ONE : D3DBLEND_INVSRCALPHA);
			//dinterface->mD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, true);
			if (!dinterface->mTransformStack.empty()) {
				Matrix3 aTransform = dinterface->mTransformStack.back() * theTransform;
				pTrans = &aTransform;
			}
			void* pData = mD3DData;
			__asm {
				mov ebx, pd
				mov ecx, pColor
				push 0
				push 0
				push 0
				push pClipRect
				push pSrcRect
				push pTrans
				push pData
				mov eax, 0x566C50ul
				call eax
			}
		}
		return;
	}
	void Data::OpperateMain(Context* buffer, Board* board) {
		__asm {
			mov eax, buffer
			push board
			mov ecx, 0x4819D0ul
			call ecx
		}
	}
	void Buffer::New() {
		__asm {
			mov eax, this
			mov ecx, 0x5D60A0ul
			call ecx
		}
	}
	Graphics* Graphics::New(const Graphics& theGraphics) {
		Graphics* _this = (Graphics*)new BYTE[sizeof(Graphics)];
		const Graphics* ptheGraphics = &theGraphics;
		__asm {
			push edi
			push ptheGraphics
			mov edi, _this
			mov eax, 0x5869B0ul
			call eax
			pop edi
		}
	}
	Graphics* Graphics::New(Image* theDestImage) {
		Graphics* _this = (Graphics*)new BYTE[sizeof(Graphics)];
		__asm {
			push _this
			mov ecx, theDestImage
			mov eax, 0x586A30ul
			call eax
		}
	}

	void Graphics::DrawImage(Image* theImage, int theX, int theY) {
		__asm {
			mov eax, this
			mov ebx, theImage
			push theY
			push theX
			mov ecx, 0x587150ul
			call ecx
		}
	}


	bool ResourceManager::LoadGroup(const std_string& group) {
		const std_string* p = &group;
		__asm{
			mov ecx,this
			mov eax,p
			mov edx,0x513140ul
			call edx
		}
	}


	void SexyAppBase::RehupFocus() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x54EB80ul
			call eax
			pop esi
		}
	}

	void GardenProp::NewPlant(GardenPlant* that) {
		__asm {
			push this
			mov edx, that
			mov eax, 0x51D8C0ul
			call eax
		}
	}

	void Board::FadeOutLevel() {
		__asm {
			mov ecx, this
			mov eax, 0x40C3E0ul
			call eax
		}
	}

	void Item::Kill() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x432DD0ul
			call eax
			pop esi
		}
	}

	void Card::Shine() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x487190ul
			call eax
			pop edi
		}
	}

	void WidgetManager::FlushDeferredOverlayWidgets(int theMaxPriority) {
		__asm {
			push theMaxPriority
			push this
			mov eax, 0x538790ul
			call eax
		}
	}

	bool DDInterface::Redraw(Rect* theClipRect) {
		__asm {
			mov edx, this
			mov ecx, theClipRect
			mov eax, 0x562F60ul
			call eax
		}
	}

	void Board::SetFire(int row) {
		__asm {
			mov ebx, this
			push row
			mov eax, 0x41D450ul
			call eax
		}
	}

	int SexyAppBase::InitDDInterface() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x5521F0ul
			call eax
			pop esi
		}
	}

	void SexyAppBase::Set3DAcclerated(bool is3D, bool reinit) {
		DWORD _reinit = reinit;
		DWORD _is3D = is3D;
		__asm {
			mov ecx, this
			push _reinit
			push _is3D
			mov eax, 0x555050ul
			call eax
		}
	}

	void D3DInterface::Flush() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x568Ec0ul
			call eax
			pop esi
		}
	}

	void SexyAppBase::RestoreScreenResolution() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x54B930ul
			call eax
			pop edi
		}
	}

	void SexyAppBase::CleanSharedImages() {
		__asm {
			push this
			mov eax, 0x555850ul
			call eax
		}
	}

	void Buffer::WriteNumBits(int theNum, int theBits) {
		__asm {
			push esi
			mov esi, this
			push theBits
			push theNum
			mov eax, 0x5D62E0ul
			call eax
			pop esi
		}
	}

	void SexyAppBase::WriteDemoTimingBlock() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x54EC60ul
			call eax
			pop edi
		}
	}	

	void ParticleSystem::SetSize(float _size) {
		__asm {
			mov edx, this
			push _size
			mov eax, 0x518630ul
			call eax
		}
	}

	void SexyAppBase::ProcessDemo() {
		__asm {
			push this
			mov eax, 0x54ED70ul
			call eax
		}
	}

	void Mower::Kill() {
		__asm {
			mov eax, this
			mov ecx, 0x458D10ul
			call ecx
		}
	}

	void Board::CleanEntityNodes() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x41BAD0ul
			call eax
			pop esi
		}
	}

	void Bgm::Update() {
		__asm {
			mov eax, this
			mov ecx, 0x45B670ul
			call ecx
		}
	}

	void AnimsLists::CleanNodes() {
		__asm {
			push this
			mov eax, 0x445680ul
			call eax
		}
	}

	void GameApp::TryExitLevel() {
		__asm {
			mov eax, this
			mov ecx, 0x4524F0ul
			call ecx
		}
	}

	void AnimsLists::Update() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x445890ul
			call eax
			pop edi
		}
	}

	void SceneProp::Update() {
		__asm {
			mov eax, this
			mov ecx, 0x43C200ul
			call ecx
		}
	}

	bool SceneProp::InheritBoard() {
		__asm {
			mov edx, this
			mov eax, 0x43A710ul
			call eax
		}
	}

	void Board::UpdateCursor() {
		__asm {
			mov eax, this
			mov ecx, 0x40EAB0ul
			call ecx
		}
	}

	void Board::Save() {
		__asm {
			push this
			mov eax, 0x408c30ul
			call eax
		}
	}

	void Board::Load() {
		mApp->LoadBoard();
	}

	void GameApp::LoadBoard() {
		__asm {
			push this
			mov eax, 0x44f7a0ul
			call eax
		}
	}

	void SelectCardWnd::Rock() {
		__asm {
			mov ebx, this
			mov eax, 0x486d20ul
			call eax
		}
	}

	Plant* Board::NewPlant(int col, int row, Plant::Type _type, bool immitater) {
		if (immitater) {
			__asm {
				push _type
				push 0x30u
				mov eax, row
				push col
				push this
				mov ecx, 0x40d120ul
				call ecx
			}
		} else {
			__asm {
				push 0xfffffffful
				push _type
				mov eax, row
				push col
				push this
				mov ecx, 0x40d120ul
				call ecx
			}
		}
	}

	void LevelProp::NewPlantIZ(Plant::Type _type, int col, int row) {
		__asm {
			push edi
			mov edi, this
			mov ebx, row
			push col
			push _type
			mov eax, 0x42A660ul
			call eax
			pop edi
		}
	}

	void LevelProp::NewPlantsIZ(Plant::Type _type, int num, int row) {
		__asm {
			push num
			push _type
			push this
			mov eax,row
			mov ecx, 0x42A6C0ul
			call ecx
		}
	}

	int Board::GetNewZombieRow(Zombie::Type _type) {
		__asm {
			mov eax, this
			push _type
			mov ecx, 0x40dc50ul
			call ecx
		}
	}

	Zombie* Board::NewZombie(int row, Zombie::Type _type, int wave) {
		__asm {
			mov eax, this
			push row
			push _type
			mov ebx, wave
			mov ecx, 0x40ddc0ul
			call ecx
		}
	}

	Building* Board::NewCrater(int col, int row) {
		__asm {
			push edi
			mov eax, this
			mov edi, row
			push col
			mov ecx, 0x408F80ul
			call ecx
			pop edi
		}
	}

	Building* Board::NewLadder(int col, int row) {
		__asm {
			push edi
			mov eax, this
			mov edi, row
			push col
			mov ecx, 0x408F40ul
			call ecx
			pop edi
		}
	}

	Plant* Plant::ImitaterReborn() {
		__asm {
			mov esi, this
			mov eax, 0x466B80ul
			call eax
		}
	}

	void LevelProp::NewGrave(int col, int row) {
		__asm {
			push edi
			push this
			mov edi, row
			mov ebx, col
			mov ecx, 0x426620ul
			call ecx
			pop edi
		}
	}

	void Board::NewMower(int row) {
		__asm {
			push esi
			mov eax, this
			lea esi, [eax + 0x100u]
			mov eax, 0x41E120ul
			call eax
			mov esi, eax
			mov eax, row
			push esi
			mov ecx, 0x458000ul
			call ecx
			mov[esi + 0x2Cu], 0
			pop esi
		}
	}

	void Board::SetZombieList() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x4092e0ul
			call eax
			pop edi
		}
	}

	bool Board::IfShowCursor() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x412490ul
			call eax
			pop esi
		}
	}

	void Board::UpdateAdvice() {
		__asm {
			push this
			mov eax, 0x4144E0ul
			call eax
		}
	}

	void Board::TidyDialogList() {
		__asm {
			push this
			mov eax, 0x416080ul
			call eax
		}
	}

	void Board::UpdateRowFire() {
		__asm {
			mov ebx, this
			mov eax, 0x41D630ul
			call eax
		}
	}

	void Board::UpdateFog() {
		__asm {
			push this
			mov eax, 0x41A5D0ul
			call eax
		}
	}

	void GameApp::DaveEnter() {
		__asm {
			mov ebx, this
			mov eax, 0x4541B0ul
			call eax
		}
	}

	void GameApp::SetDave(int index) {
		__asm {
			push esi
			push index
			mov esi, this
			mov eax, 0x454430ul
			call eax
			pop esi
		}
	}

	void LevelProp::SetVBBuild() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x4286F0ul
			call eax
			pop esi
		}
	}

	void Board::KillBoardText(AdviceType _type) {
		__asm {
			push esi
			mov eax, _type
			mov esi, this
			mov ecx, 0x40CAB0ul
			call ecx
			pop esi
		}
	}

	void Board::KillBetraiedZombies() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x40DF00ul
			call eax
			pop edi
		}
	}

	void Board::NewLastWaveZombies() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x412CE0ul
			call eax
			pop edi
		}
	}

	void Board::ShowLevelEndWhiteText() {
		__asm {
			mov ecx, this
			mov eax, 0x40C3E0ul
			call eax
		}
	}

	void Board::NextWaveComing() {
		__asm {
			mov eax, this
			mov ecx, 0x413C00ul
			call ecx
		}
	}

	void Board::SpawnWave() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x412EE0ul
			call eax
			pop edi
		}
	}

	void Board::SetBoardText(const std_string& advice, BoardText::Type style, AdviceType _type) {
		const std_string* _advice = &advice;
		__asm {
			push edi
			mov edi, this
			mov edx, _advice
			mov ecx, style
			mov ebx, _type
			mov eax, 0x40CA10ul
			call eax
			pop edi
		}
		if (_type != AdviceType::NIL)AdviceShown[(int)_type] = true;
	}

	bool LevelProp::UpdateZombieSpawn() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x426580ul
			call eax
			pop esi
		}
	}

	void Board::ShowLastWaveText() {
		__asm {
			mov eax, this
			mov ecx, 0x413C00ul
			call ecx
		}
	}

	void Board::UpdateRowIce() {
		__asm {
			push this
			mov eax, 0x414100ul
			call eax
		}
	}

	void Board::UpdateProcessBar() {
		__asm {
			mov eax, this
			mov ecx, 0x414270ul
			call ecx
		}
	}

	void Anim::Kill() {
		__asm {
			mov ecx, this
			mov eax, 0x4733F0ul
			call eax
		}
	}

	void LevelProp::IZTryAchieve(Building* brain) {
		__asm {
			push esi
			push ebx
			mov esi, this
			mov ebx,brain
			mov eax, 0x42B8B0ul
			call eax
			pop ebx
			pop esi
		}
	}

	void ParticleSystem::Kill() {
		__asm {
			push this
			mov eax, 0x5160C0ul
			call eax
		}
	}

	void Plant::CanonShoot(int x, int y) {
		__asm {
			mov eax, this
			push x
			push y
			mov ecx, 0x466d50ul
			call ecx
		}
	}

	void Plant::Kill() {
		__asm {
			push this
			mov eax, 0x4679B0ul
			call eax
		}
	}

	void Attachment::Kill() {
		__asm {
			mov ecx, this
			mov eax, 0x404FC0ul
			call eax
		}
	}

	void ParticleSystem::Update() {
		__asm {
			push this
			mov eax, 0x517370ul
			call eax
		}
	}

	void Trail::Update() {
		__asm {
			mov eax, this
			mov ecx, 0x51BC00ul
			call ecx
		}
	}

	void ParticleSystem::SetPosition(float x, float y) {
		__asm {
			push edi
			mov edi, this
			push y
			push x
			mov eax, 0x518440ul
			call eax
			pop edi
		}
	}

	bool Global::LoadAnim(const std_string* theFilename, AnimDefinition* theDefinition) {
		__asm {
			mov eax, theFilename
			push theDefinition
			mov ecx, 0x4715F0ul
			call ecx
		}
	}

	void Board::Lose(Zombie* zombie) {
		__asm {
			push zombie
			push this
			mov eax, 0x413400ul
			call eax
		}
	}

	void Anim::Init(float x, float y, AnimDefinition* theDefinition) {
		__asm {
			mov eax, theDefinition
			push y
			push x
			push this
			mov ecx, 0x471B00ul
			call ecx
		}
	}

	void ParticleSystem::SetColor(Color* theColor, const char* emittername) {
		__asm {
			push theColor
			push this
			mov ebx, emittername
			mov eax, 0x518560ul
			call eax
		}
	}

	void ParticleSystem::SetShine(bool ifShine) {
		__asm {
			push esi
			mov dl, ifShine
			mov esi, this
			mov eax, 0x5185D0ul
			call eax
			pop esi
		}
	}

	void Zombie::Kill() {
		__asm {
			mov ecx, this
			mov eax, 0x530510ul
			call eax
		}
	}

	void Zombie::SecKill() {
		__asm {
			mov eax, this
			mov ecx, 0x533F10ul
			call ecx
		}
	}

	void Zombie::BreakButter() {
		__asm {
			mov eax, this
			mov ecx, 0x532570ul
			call ecx
		}
	}

	void Zombie::NewAttachedParticle(int x, int y, ParticleSystem::Type _type) {
		__asm {
			push _type
			push y
			push x
			mov eax, this
			mov ecx, 0x5321F0ul
			call ecx
		}
	}

	void Zombie::Hitted(int hp, HitType flag) {
		__asm {
			push esi
			mov esi, this
			push hp
			mov eax, flag
			mov ecx, 0x5317C0ul
			call ecx
			pop esi
		}
	}

	void Zombie::TryEnterChimney() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x534730ul
			call eax
			pop esi
		}
	}

	Building::Building() {
		__asm {
			mov eax, this
			mov ecx, 0x44CFA0ul
			call ecx
		}
	}

	void Building::Kill() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x44d000ul
			call eax
			pop esi
		}
	}

	Item* Board::NewItem(int x, int y, Item::Type _type, Item::MovementState movemantstate) {
		__asm {
			push movemantstate
			push _type
			push y
			push x
			mov eax, 0x40CB10ul
			call eax
		}
	}

	void GardenProp::UpdateMain() {
		__asm {
			mov ecx, this
			mov eax, 0x520B30ul
			call eax
		}
	}

	void GameApp::UpdateDave() {
		__asm {
			mov eax, this
			mov ecx, 0x455040ul
			call ecx
		}
	}

	void SampleManager::StopSample(Sample::Type _type) {
		__asm {
			push edi
			mov eax, _type
			mov edi, this
			mov ecx, 0x515290ul
			call ecx
			pop edi
		}
	}

	Anim* GameApp::NewAnim(Anim::Type _type, int layer, float x, float y) {
		__asm {
			push ebx
			mov eax, this
			mov ebx, _type
			push layer
			push y
			push x
			mov ecx, 0x453C30ul
			call ecx
			pop ebx
		}
	}

	ParticleSystem* GameApp::NewParticleSystem(ParticleSystem::Type _type, int layer, float x, float y) {
		__asm {
			push ebx
			mov edx, this
			mov eax, _type
			mov ecx, layer
			push y
			push x
			mov ebx, 0x453C80ul
			call ebx
			pop ebx
		}
	}

	void btn::Update() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x448330ul
			call eax
			pop esi
		}
	}

	void BoardText::Update() {
		__asm {
			mov ecx, this
			mov eax, 0x4594B0ul
			call eax
		}
	}

	void Bullet::Kill() {
		__asm {
			mov eax, this
			mov ecx, 0x46EB20ul
			call ecx
		}
	}

	void Building::PortalInit() {
		__asm {
			mov eax, this
			mov ecx, 0x44E1B0ul
			call ecx
		}
	}

	void LevelProp::ClearBoard() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x429E50ul
			call eax
			pop edi
		}
	}

	DDImage::DDImage(DDInterface* theDDInterface) {
		__asm {
			push this
			mov edi, theDDInterface
			mov eax, 0x56B890ul
			call eax
		}
	}

	void D3DInterface::BltTransformed(DDImage* theImage, const Color& theColor, const Rect& theSrcRect, const Matrix3& theTransform) {
		/*
		const Rect& theClipRect = { 0,0,gGameApp->mWidth,gGameApp->mHeight };
		const Matrix3* pTrans = &theTransform;
		const Rect* pSrcRect = &theSrcRect;
		const Color* pColor = &theColor;
		const Rect* pClipRect = &theClipRect;
		IDirect3DDevice7* pd = mD3DDevice;
		if (PreDraw() && CreateImageTexture(theImage)) {
			mD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
			mD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
			mD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, true);
			if (!mTransformStack.empty()) {
				mD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, true);
				Matrix3 aTransform = mTransformStack.back() * theTransform;
				pTrans = &aTransform;
			}
			void* pData = theImage->mD3DData;
			__asm {
				mov ebx, pd
				mov ecx, pColor
				push 0
				push 0
				push 0
				push pClipRect
				push pSrcRect
				push pTrans
				push pData
				mov eax, 0x566C50ul
				call eax
			}
		}
		*/
		return;
	}

	bool D3DInterface::CreateImageTexture(const DDImage* theImage) {
		__asm {
			push theImage
			push this
			mov eax, 0x567CF0ul
			call eax
		}
	}

	bool D3DInterface::PreDraw() {
		__asm {
			mov esi, this
			mov eax, 0x564ca0ul
			call eax
		}
	}

	void Plant::Shake() {
		__asm {
			mov eax, this
			mov ecx, 0x464DB0ul
			call ecx
		}
	}

	void SampleManager::NewSampleF(Sample::Type _type, float speed) {
		__asm {
			mov ecx, this
			mov eax, _type
			push speed
			mov edx, 0x515020ul
			call edx
		}
	}

	void SampleManager::NewSample(Sample::Type _type) {
		__asm {
			push esi
			push this
			mov esi, _type
			mov eax, 0x515240ul
			call eax
			pop esi
		}
	}

	void Plant::SetSleep(bool a) {
		DWORD _a = a;
		__asm {
			mov eax, this
			push _a
			mov ecx, 0x45E860ul
			call ecx
		}
	}

	int Board::GetNowWaveZombieHPSum() {
		int wave = this->nowwaveNum - 1;
		__asm {
			push ebx
			mov ebx, this
			push wave
			mov eax, 0x412E30ul
			call eax
			pop ebx
		}
	}
#define VF(rett,param,args,vname,name,vbase,addr);rett(__thiscall _CLASS::*& _CLASS::vname)param=*(rett(__thiscall _CLASS::**)param)(addr+_CLASS::vfAddr##vbase);rett _CLASS::name param{return(this->*(rett(__thiscall _CLASS::*)param)(((void(__thiscall _CLASS::**)())vf##vbase)[addr/4]))args;}
#define _CLASS Buffer
	VF(void, (bool free), (free), vfKill, Kill, _Buffer, 0x0000u);
#undef _CLASS
#define _CLASS Context
	VF(void, (bool free), (free), vfKill, Kill, _Buffer, 0x0000u);
#undef _CLASS
#define _CLASS ButtonListener
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS DialogListener
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonPress, DialogButtonPress, _DialogListener, 0x0000u);
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonDepress, DialogButtonDepress, _DialogListener, 0x0004u);
#undef _CLASS
#define _CLASS ScrollListener
	VF(void, (int Id, double pos), (Id, pos), vfScrollPosition, ScrollPosition, _ScrollListener, 0x0000u);
#undef _CLASS
#define _CLASS ListListener
	VF(void, (int Id, int index, int count), (Id, index, count), vfListClicked, ListClicked, _ListListener, 0x0000u);
	VF(void, (int Id), (Id), vfListClosed, ListClosed, _ListListener, 0x0004u);
	VF(void, (int Id, int oldIdx, int newIdx), (Id, oldIdx, newIdx), vfListHiliteChanged, ListHiliteChanged, _ListListener, 0x0008u);
#undef _CLASS
#define _CLASS EditListener
	VF(void, (int Id, const std_string& str), (Id, str), vfEditWidgetText, EditWidgetText, _EditListener, 0x0000u);
	VF(void, (int Id, KeyCode key), (Id, key), vfAllowKey, AllowKey, _EditListener, 0x0004u);
	VF(void, (int Id, char chr), (Id, chr), vfAllowChar, AllowChar, _EditListener, 0x0008u);
	VF(void, (int Id, const std_string& txt), (Id, txt), vfAllowText, AllowText, _EditListener, 0x000Cu);
#undef _CLASS
#define _CLASS SexyAppBase
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
	VF(bool, (bool allowSleep), (allowSleep), vfProcess, Process, _ButtonListener, 0x001Cu);
	VF(void, (void), (), vfUpdateFrames, UpdateFrames, _ButtonListener, 0x0020u);
	VF(bool, (void), (), vfDoUpdateFrames, DoUpdateFrames, _ButtonListener, 0x0024u);
	VF(void, (float theFrac), (theFrac), vfDoUpdateFramesF, DoUpdateFramesF, _ButtonListener, 0x0028u);
	VF(void, (void), (), vfMakeWindow, MakeWindow, _ButtonListener, 0x002Cu);
	VF(void, (void), (), vfEnforceCursor, EnforceCursor, _ButtonListener, 0x0030u);
	VF(void, (void), (), vfReInitImages, ReInitImages, _ButtonListener, 0x0034u);
	VF(void, (void), (), vfDeleteNativeImageData, DeleteNativeImageData, _ButtonListener, 0x0038u);
	VF(void, (void), (), vfDeleteExtraImageData, DeleteExtraImageData, _ButtonListener, 0x003Cu);
	VF(void, (void), (), vfLoadingThreadCompleted, LoadingThreadCompleted, _ButtonListener, 0x0040u);
	VF(void, (bool free), (free), vfKill, Kill, _ButtonListener, 0x0044u);
	VF(MusicInterface*, (HWND hwnd), (hwnd), vfCreateMusicInterface, CreateMusicInterface, _ButtonListener, 0x0048u);
	VF(void, (void), (), vfInitHook, InitHook, _ButtonListener, 0x004Cu);
	VF(void, (void), (), vfShutdownHook, ShutdownHook, _ButtonListener, 0x0050u);
	VF(void, (void), (), vfPreTerminate, PreTerminate, _ButtonListener, 0x0054u);
	VF(void, (void), (), vfLoadingThreadProc, LoadingThreadProc, _ButtonListener, 0x0058u);
	VF(void, (void), (), vfWriteToRegistry, WriteToRegistry, _ButtonListener, 0x005Cu);
	VF(void, (void), (), vfReadFromRegistry, ReadFromRegistry, _ButtonListener, 0x0060u);
	VF(Dialog*, (int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode), (theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode), vfNewDialog, NewDialog, _ButtonListener, 0x0064u);
	VF(void, (void), (), vfPreDisplayHook, PreDisplayHook, _ButtonListener, 0x0068u);
	VF(void, (void), (), vfBeginPopup, BeginPopup, _ButtonListener, 0x006Cu);
	VF(void, (void), (), vfEndPopup, EndPopup, _ButtonListener, 0x0070u);
	VF(void, (void), (), vfMsgBox_0, MsgBox_0, _ButtonListener, 0x0074u);
	VF(void, (void), (), vfMsgBox, MsgBox, _ButtonListener, 0x0078u);
	VF(void, (void), (), vfPopup_0, Popup_0, _ButtonListener, 0x007Cu);
	VF(void, (void), (), vfPopup, Popup, _ButtonListener, 0x0080u);
	VF(void, (const std_string& theError), (theError), vfLogScreenSaverError, LogScreenSaverError, _ButtonListener, 0x0084u);
	VF(void, (Widget* theWidget), (theWidget), vfSafeDeleteWidget, SafeDeleteWidget, _ButtonListener, 0x0088u);
	VF(void, (const std_string& theURL), (theURL), vfURLOpenFailed, URLOpenFailed, _ButtonListener, 0x008Cu);
	VF(void, (const std_string& theURL), (theURL), vfURLOpenSucceeded, URLOpenSucceeded, _ButtonListener, 0x0090u);
	VF(bool, (const std_string& theURL, bool shutdownOnOpen), (theURL, shutdownOnOpen), vfOpenURL, OpenURL, _ButtonListener, 0x0094u);
	VF(std_string, (const std_string& thePath), (thePath), vfGetProductVersion, GetProductVersion, _ButtonListener, 0x0098u);
	VF(void, (void), (), vfSEHOccured, SEHOccured, _ButtonListener, 0x009Cu);
	VF(std_string, (void), (), vfGetGameSEHInfo, GetGameSEHInfo, _ButtonListener, 0x00A0u);
	VF(void, (std_map<std::string, std::string>* theDefinesMap), (theDefinesMap), vfGetSEHWebParams, GetSEHWebParams, _ButtonListener, 0x00A4u);
	VF(void, (void), (), vfShutdown, Shutdown, _ButtonListener, 0x00A8u);
	VF(void, (void), (), vfDoParseCmdLine, DoParseCmdLine, _ButtonListener, 0x00ACu);
	VF(void, (const std_string& theCmdLine), (theCmdLine), vfParseCmdLine, ParseCmdLine, _ButtonListener, 0x00B0u);
	VF(void, (const std_string& theParamName, const std_string& theParamValue), (theParamName, theParamValue), vfHandleCmdLineParam, HandleCmdLineParam, _ButtonListener, 0x00B4u);
	VF(void, (int theType, int theParam), (theType, theParam), vfHandleNotifyGameMessage, HandleNotifyGameMessage, _ButtonListener, 0x00B8u);
	VF(void, (void), (), vfHandleGameAlreadyRunning, HandleGameAlreadyRunning, _ButtonListener, 0x00BCu);
	VF(void, (void), (), vfStart, Start, _ButtonListener, 0x00C0u);
	VF(void, (void), (), vfInit, Init, _ButtonListener, 0x00C4u);
	VF(void, (void), (), vfPreDDInterfaceInitHook, PreDDInterfaceInitHook, _ButtonListener, 0x00C8u);
	VF(void, (void), (), vfPostDDInterfaceInitHook, PostDDInterfaceInitHook, _ButtonListener, 0x00CCu);
	VF(bool, (const char* theIntendedPath), (theIntendedPath), vfChangeDirHook, ChangeDirHook, _ButtonListener, 0x00D0u);
	VF(void, (SoundId id, int pan), (id, pan), vfPlaySample_0, PlaySample, _ButtonListener, 0x00D4u);
	VF(void, (SoundId id), (id), vfPlaySample, PlaySample, _ButtonListener, 0x00D8u);
	VF(double, (void), (), vfGetMasterVolume, GetMasterVolume, _ButtonListener, 0x00DCu);
	VF(double, (void), (), vfGetMusicVolume, GetMusicVolume, _ButtonListener, 0x00E0u);
	VF(double, (void), (), vfGetSfxVolume, GetSfxVolume, _ButtonListener, 0x00E4u);
	VF(bool, (void), (), vfIsMuted, IsMuted, _ButtonListener, 0x00E8u);
	VF(void, (double theVolume), (theVolume), vfSetMasterVolume, SetMasterVolume, _ButtonListener, 0x00ECu);
	VF(void, (double theVolume), (theVolume), vfSetMusicVolume, SetMusicVolume, _ButtonListener, 0x00F0u);
	VF(void, (double theVolume), (theVolume), vfSetSfxVolume, SetSfxVolume, _ButtonListener, 0x00F4u);
	VF(void, (bool autoMute), (autoMute), vfMute, Mute, _ButtonListener, 0x00F8u);
	VF(void, (bool autoMute), (autoMute), vfUnmute, Unmute, _ButtonListener, 0x00FCu);
	VF(double, (void), (), vfGetLoadingThreadProgress, GetLoadingThreadProgress, _ButtonListener, 0x0100u);
	VF(DDImage*, (const std_string& theFileName, bool commitBits), (theFileName, commitBits), vfGetImage, GetImage, _ButtonListener, 0x0104u);
	VF(int, (SharedImageRef* a, int b, int c, int d, int e), (a, b, c, d, e), vfSetSharedImage, SetSharedImage, _ButtonListener, 0x0108u);
	VF(SharedImageRef, (const std_string& theFileName, const std::string& theVariant, bool* isNew), (theFileName, theVariant, isNew), vfGetSharedImage, GetSharedImage, _ButtonListener, 0x010Cu);
	VF(void, (bool wantWindowed, bool is3d, bool force), (wantWindowed, is3d, force), vfSwitchScreenMode_1, SwitchScreenMode, _ButtonListener, 0x0110u);
	VF(void, (bool wantWindowed), (wantWindowed), vfSwitchScreenMode_0, SwitchScreenMode, _ButtonListener, 0x0114u);
	VF(void, (void), (), vfSwitchScreenMode, SwitchScreenMode, _ButtonListener, 0x0118u);
	VF(void, (bool isDisabled), (isDisabled), vfSetAlphaDisabled, SetAlphaDisabled, _ButtonListener, 0x011Cu);
	VF(Dialog*, (int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode), (theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode), vfDoDialog, DoDialog, _ButtonListener, 0x0120u);
	VF(Dialog*, (Dialog::Type type), (type), vfGetDialog, GetDialog, _ButtonListener, 0x0124u);
	VF(void, (Dialog* theDialog), (theDialog), vfAddDialog, AddDialog, _ButtonListener, 0x0128u);
	VF(void, (int theDialogId, Dialog* theDialog), (theDialogId, theDialog), vfAddDialog_0, AddDialog, _ButtonListener, 0x012Cu);
	VF(void, (void), (), vfKillDialog_0, KillDialog_0, _ButtonListener, 0x0130u);
	VF(void, (void), (), vfKillDialog, KillDialog, _ButtonListener, 0x0134u);
	VF(void, (void), (), vfKillDialog_1, KillDialog_1, _ButtonListener, 0x0138u);
	VF(int, (void), (), vfGetDialogCount, GetDialogCount, _ButtonListener, 0x013Cu);
	VF(void, (void), (), vfModalOpen, ModalOpen, _ButtonListener, 0x0140u);
	VF(void, (void), (), vfModalClose, ModalClose, _ButtonListener, 0x0144u);
	VF(void, (void), (), vfGotFocus, GotFocus, _ButtonListener, 0x0148u);
	VF(void, (void), (), vfLostFocus, LostFocus, _ButtonListener, 0x014Cu);
	VF(bool, (WPARAM wParam), (wParam), vfIsAltKeyUsed, IsAltKeyUsed, _ButtonListener, 0x0150u);
	VF(bool, (int theKey), (theKey), vfDebugKeyDown, DebugKeyDown, _ButtonListener, 0x0154u);
	VF(bool, (int theKey, bool ctrlDown, bool altDown), (theKey, ctrlDown, altDown), vfDebugKeyDownAsync, DebugKeyDownAsync, _ButtonListener, 0x0158u);
	VF(void, (void), (), vfCloseRequestAsync, CloseRequestAsync, _ButtonListener, 0x015Cu);
	VF(void, (void), (), vfDone3dTesting, Done3dTesting, _ButtonListener, 0x0160u);
	VF(std_string, (void), (), vfNotifyCrashHook, NotifyCrashHook, _ButtonListener, 0x0164u);
	VF(void, (void), (), vfCheckSignature, CheckSignature, _ButtonListener, 0x0168u);
	VF(bool, (void), (), vfDrawDirtyStuff, DrawDirtyStuff, _ButtonListener, 0x016Cu);
	VF(void, (Rect* theClipRect), (theClipRect), vfRedraw, Redraw, _ButtonListener, 0x0170u);
	VF(void, (void), (), vfInitPropertiesHook, InitPropertiesHook, _ButtonListener, 0x0174u);
	VF(void, (void), (), vfDoMainLoop, DoMainLoop, _ButtonListener, 0x0178u);
	VF(bool, (bool* updated), (updated), vfUpdateAppStep, UpdateAppStep, _ButtonListener, 0x017Cu);
	VF(bool, (void), (), vfUpdateApp, UpdateApp, _ButtonListener, 0x0180u);
	VF(bool, (void), (), vfAppCanRestore, AppCanRestore, _ButtonListener, 0x0184u);
	VF(void, (void), (), vfreturn0, return0, _ButtonListener, 0x0188u);
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonPress, DialogButtonPress, _DialogListener, 0x0000u);
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonDepress, DialogButtonDepress, _DialogListener, 0x0004u);
#undef _CLASS
#define _CLASS SexyApp
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
	VF(bool, (bool allowSleep), (allowSleep), vfProcess, Process, _ButtonListener, 0x001Cu);
	VF(void, (void), (), vfUpdateFrames, UpdateFrames, _ButtonListener, 0x0020u);
	VF(bool, (void), (), vfDoUpdateFrames, DoUpdateFrames, _ButtonListener, 0x0024u);
	VF(void, (float theFrac), (theFrac), vfDoUpdateFramesF, DoUpdateFramesF, _ButtonListener, 0x0028u);
	VF(void, (void), (), vfMakeWindow, MakeWindow, _ButtonListener, 0x002Cu);
	VF(void, (void), (), vfEnforceCursor, EnforceCursor, _ButtonListener, 0x0030u);
	VF(void, (void), (), vfReInitImages, ReInitImages, _ButtonListener, 0x0034u);
	VF(void, (void), (), vfDeleteNativeImageData, DeleteNativeImageData, _ButtonListener, 0x0038u);
	VF(void, (void), (), vfDeleteExtraImageData, DeleteExtraImageData, _ButtonListener, 0x003Cu);
	VF(void, (void), (), vfLoadingThreadCompleted, LoadingThreadCompleted, _ButtonListener, 0x0040u);
	VF(void, (bool free), (free), vfKill, Kill, _ButtonListener, 0x0044u);
	VF(MusicInterface*, (HWND hwnd), (hwnd), vfCreateMusicInterface, CreateMusicInterface, _ButtonListener, 0x0048u);
	VF(void, (void), (), vfInitHook, InitHook, _ButtonListener, 0x004Cu);
	VF(void, (void), (), vfShutdownHook, ShutdownHook, _ButtonListener, 0x0050u);
	VF(void, (void), (), vfPreTerminate, PreTerminate, _ButtonListener, 0x0054u);
	VF(void, (void), (), vfLoadingThreadProc, LoadingThreadProc, _ButtonListener, 0x0058u);
	VF(void, (void), (), vfWriteToRegistry, WriteToRegistry, _ButtonListener, 0x005Cu);
	VF(void, (void), (), vfReadFromRegistry, ReadFromRegistry, _ButtonListener, 0x0060u);
	VF(Dialog*, (int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode), (theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode), vfNewDialog, NewDialog, _ButtonListener, 0x0064u);
	VF(void, (void), (), vfPreDisplayHook, PreDisplayHook, _ButtonListener, 0x0068u);
	VF(void, (void), (), vfBeginPopup, BeginPopup, _ButtonListener, 0x006Cu);
	VF(void, (void), (), vfEndPopup, EndPopup, _ButtonListener, 0x0070u);
	VF(void, (void), (), vfMsgBox_0, MsgBox_0, _ButtonListener, 0x0074u);
	VF(void, (void), (), vfMsgBox, MsgBox, _ButtonListener, 0x0078u);
	VF(void, (void), (), vfPopup_0, Popup_0, _ButtonListener, 0x007Cu);
	VF(void, (void), (), vfPopup, Popup, _ButtonListener, 0x0080u);
	VF(void, (const std_string& theError), (theError), vfLogScreenSaverError, LogScreenSaverError, _ButtonListener, 0x0084u);
	VF(void, (Widget* theWidget), (theWidget), vfSafeDeleteWidget, SafeDeleteWidget, _ButtonListener, 0x0088u);
	VF(void, (const std_string& theURL), (theURL), vfURLOpenFailed, URLOpenFailed, _ButtonListener, 0x008Cu);
	VF(void, (const std_string& theURL), (theURL), vfURLOpenSucceeded, URLOpenSucceeded, _ButtonListener, 0x0090u);
	VF(bool, (const std_string& theURL, bool shutdownOnOpen), (theURL, shutdownOnOpen), vfOpenURL, OpenURL, _ButtonListener, 0x0094u);
	VF(std_string, (const std_string& thePath), (thePath), vfGetProductVersion, GetProductVersion, _ButtonListener, 0x0098u);
	VF(void, (void), (), vfSEHOccured, SEHOccured, _ButtonListener, 0x009Cu);
	VF(std_string, (void), (), vfGetGameSEHInfo, GetGameSEHInfo, _ButtonListener, 0x00A0u);
	VF(void, (std_map<std::string, std::string>* theDefinesMap), (theDefinesMap), vfGetSEHWebParams, GetSEHWebParams, _ButtonListener, 0x00A4u);
	VF(void, (void), (), vfShutdown, Shutdown, _ButtonListener, 0x00A8u);
	VF(void, (void), (), vfDoParseCmdLine, DoParseCmdLine, _ButtonListener, 0x00ACu);
	VF(void, (const std_string& theCmdLine), (theCmdLine), vfParseCmdLine, ParseCmdLine, _ButtonListener, 0x00B0u);
	VF(void, (const std_string& theParamName, const std_string& theParamValue), (theParamName, theParamValue), vfHandleCmdLineParam, HandleCmdLineParam, _ButtonListener, 0x00B4u);
	VF(void, (int theType, int theParam), (theType, theParam), vfHandleNotifyGameMessage, HandleNotifyGameMessage, _ButtonListener, 0x00B8u);
	VF(void, (void), (), vfHandleGameAlreadyRunning, HandleGameAlreadyRunning, _ButtonListener, 0x00BCu);
	VF(void, (void), (), vfStart, Start, _ButtonListener, 0x00C0u);
	VF(void, (void), (), vfInit, Init, _ButtonListener, 0x00C4u);
	VF(void, (void), (), vfPreDDInterfaceInitHook, PreDDInterfaceInitHook, _ButtonListener, 0x00C8u);
	VF(void, (void), (), vfPostDDInterfaceInitHook, PostDDInterfaceInitHook, _ButtonListener, 0x00CCu);
	VF(bool, (const char* theIntendedPath), (theIntendedPath), vfChangeDirHook, ChangeDirHook, _ButtonListener, 0x00D0u);
	VF(void, (SoundId id, int pan), (id, pan), vfPlaySample_0, PlaySample, _ButtonListener, 0x00D4u);
	VF(void, (SoundId id), (id), vfPlaySample, PlaySample, _ButtonListener, 0x00D8u);
	VF(double, (void), (), vfGetMasterVolume, GetMasterVolume, _ButtonListener, 0x00DCu);
	VF(double, (void), (), vfGetMusicVolume, GetMusicVolume, _ButtonListener, 0x00E0u);
	VF(double, (void), (), vfGetSfxVolume, GetSfxVolume, _ButtonListener, 0x00E4u);
	VF(bool, (void), (), vfIsMuted, IsMuted, _ButtonListener, 0x00E8u);
	VF(void, (double theVolume), (theVolume), vfSetMasterVolume, SetMasterVolume, _ButtonListener, 0x00ECu);
	VF(void, (double theVolume), (theVolume), vfSetMusicVolume, SetMusicVolume, _ButtonListener, 0x00F0u);
	VF(void, (double theVolume), (theVolume), vfSetSfxVolume, SetSfxVolume, _ButtonListener, 0x00F4u);
	VF(void, (bool autoMute), (autoMute), vfMute, Mute, _ButtonListener, 0x00F8u);
	VF(void, (bool autoMute), (autoMute), vfUnmute, Unmute, _ButtonListener, 0x00FCu);
	VF(double, (void), (), vfGetLoadingThreadProgress, GetLoadingThreadProgress, _ButtonListener, 0x0100u);
	VF(DDImage*, (const std_string& theFileName, bool commitBits), (theFileName, commitBits), vfGetImage, GetImage, _ButtonListener, 0x0104u);
	VF(int, (SharedImageRef* a, int b, int c, int d, int e), (a, b, c, d, e), vfSetSharedImage, SetSharedImage, _ButtonListener, 0x0108u);
	VF(SharedImageRef, (const std_string& theFileName, const std::string& theVariant, bool* isNew), (theFileName, theVariant, isNew), vfGetSharedImage, GetSharedImage, _ButtonListener, 0x010Cu);
	VF(void, (bool wantWindowed, bool is3d, bool force), (wantWindowed, is3d, force), vfSwitchScreenMode_1, SwitchScreenMode, _ButtonListener, 0x0110u);
	VF(void, (bool wantWindowed), (wantWindowed), vfSwitchScreenMode_0, SwitchScreenMode, _ButtonListener, 0x0114u);
	VF(void, (void), (), vfSwitchScreenMode, SwitchScreenMode, _ButtonListener, 0x0118u);
	VF(void, (bool isDisabled), (isDisabled), vfSetAlphaDisabled, SetAlphaDisabled, _ButtonListener, 0x011Cu);
	VF(Dialog*, (int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode), (theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode), vfDoDialog, DoDialog, _ButtonListener, 0x0120u);
	VF(Dialog*, (Dialog::Type type), (type), vfGetDialog, GetDialog, _ButtonListener, 0x0124u);
	VF(void, (Dialog* theDialog), (theDialog), vfAddDialog, AddDialog, _ButtonListener, 0x0128u);
	VF(void, (int theDialogId, Dialog* theDialog), (theDialogId, theDialog), vfAddDialog_0, AddDialog, _ButtonListener, 0x012Cu);
	VF(void, (void), (), vfKillDialog_0, KillDialog_0, _ButtonListener, 0x0130u);
	VF(void, (void), (), vfKillDialog, KillDialog, _ButtonListener, 0x0134u);
	VF(void, (void), (), vfKillDialog_1, KillDialog_1, _ButtonListener, 0x0138u);
	VF(int, (void), (), vfGetDialogCount, GetDialogCount, _ButtonListener, 0x013Cu);
	VF(void, (void), (), vfModalOpen, ModalOpen, _ButtonListener, 0x0140u);
	VF(void, (void), (), vfModalClose, ModalClose, _ButtonListener, 0x0144u);
	VF(void, (void), (), vfGotFocus, GotFocus, _ButtonListener, 0x0148u);
	VF(void, (void), (), vfLostFocus, LostFocus, _ButtonListener, 0x014Cu);
	VF(bool, (WPARAM wParam), (wParam), vfIsAltKeyUsed, IsAltKeyUsed, _ButtonListener, 0x0150u);
	VF(bool, (int theKey), (theKey), vfDebugKeyDown, DebugKeyDown, _ButtonListener, 0x0154u);
	VF(bool, (int theKey, bool ctrlDown, bool altDown), (theKey, ctrlDown, altDown), vfDebugKeyDownAsync, DebugKeyDownAsync, _ButtonListener, 0x0158u);
	VF(void, (void), (), vfCloseRequestAsync, CloseRequestAsync, _ButtonListener, 0x015Cu);
	VF(void, (void), (), vfDone3dTesting, Done3dTesting, _ButtonListener, 0x0160u);
	VF(std_string, (void), (), vfNotifyCrashHook, NotifyCrashHook, _ButtonListener, 0x0164u);
	VF(void, (void), (), vfCheckSignature, CheckSignature, _ButtonListener, 0x0168u);
	VF(bool, (void), (), vfDrawDirtyStuff, DrawDirtyStuff, _ButtonListener, 0x016Cu);
	VF(void, (Rect* theClipRect), (theClipRect), vfRedraw, Redraw, _ButtonListener, 0x0170u);
	VF(void, (void), (), vfInitPropertiesHook, InitPropertiesHook, _ButtonListener, 0x0174u);
	VF(void, (void), (), vfDoMainLoop, DoMainLoop, _ButtonListener, 0x0178u);
	VF(bool, (bool* updated), (updated), vfUpdateAppStep, UpdateAppStep, _ButtonListener, 0x017Cu);
	VF(bool, (void), (), vfUpdateApp, UpdateApp, _ButtonListener, 0x0180u);
	VF(bool, (void), (), vfAppCanRestore, AppCanRestore, _ButtonListener, 0x0184u);
	VF(bool, (HWND a, unsigned int b, unsigned int c, int d, int* e), (a,b,c,d,e), vfOverrideWindowProc, OverrideWindowProc, _ButtonListener, 0x0188u);
	VF(bool, (void), (), vfShouldCheckForUpdate, ShouldCheckForUpdate, _ButtonListener, 0x018Cu);
	VF(void, (void), (), vfUpdateCheckQueried, UpdateCheckQueried, _ButtonListener, 0x0190u);
	VF(bool, (void), (), vfOpenRegisterPage, OpenRegisterPage, _ButtonListener, 0x0194u);
	VF(int, (std_map<std_string, std_string> a), (a), vfOpenRegisterPage_0, OpenRegisterPage, _ButtonListener, 0x0198u);
	VF(bool, (std_string const& a, class std::map<std_string, std_string> const& b), (a,b), vfOpenHTMLTemplate, OpenHTMLTemplate, _ButtonListener, 0x019Cu);
	VF(void, (void), (), vfOpenUpdateURL, OpenUpdateURL, _ButtonListener, 0x01A0u);
	VF(void, (char a), (a), vfKeyChar, KeyChar, _ButtonListener, 0x01A4u);
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonPress, DialogButtonPress, _DialogListener, 0x0000u);
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonDepress, DialogButtonDepress, _DialogListener, 0x0004u);
#undef _CLASS
#define _CLASS WidgetContainer
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (Graphics* g), (g), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
#undef _CLASS
#define _CLASS WidgetManager
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
#undef _CLASS
#define _CLASS Widget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char theChar), (theChar), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode theKey), (theKey), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode theKey), (theKey), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
#undef _CLASS
#define _CLASS Board
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS LoadingPage
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS MainMenu
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS SelectCardWnd
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
#undef _CLASS
#define _CLASS NotePage
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
#undef _CLASS
#define _CLASS MV
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS SelectLevelPage
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS ButtonWidget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Graphics* g, Image* theImage, const Rect& theRect, int x, int y), (g, theImage, theRect, x, y), vfDrawButtonImage, DrawButtonImage, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetFont, SetFont, _WidgetContainer, 0x011Cu);
	VF(bool, (void), (), vfIsButtonDown, IsButtonDown, _WidgetContainer, 0x0120u);
#undef _CLASS
#define _CLASS CheckBox
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0094u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (bool checked, bool tellListener), (checked, tellListener), vfSetChecked, SetChecked, _WidgetContainer, 0x0118u);
	VF(bool, (void), (), vfIsChecked, IsChecked, _WidgetContainer, 0x011Cu);
#undef _CLASS
#define _CLASS Dialog
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS EditWidget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (KeyCode theKey, char theChar), (theKey, theChar), vfProcessKey, ProcessKey, _WidgetContainer, 0x0118u);
	VF(void, (void), (), vfHiliteWord, HiliteWord, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont, Font* theWidthCheckFont), (theFont, theWidthCheckFont), vfSetFont, SetFont, _WidgetContainer, 0x0120u);
	VF(void, (const std_string& theText, bool leftPosToZero), (theText, leftPosToZero), vfSetText, SetText, _WidgetContainer, 0x0124u);
	VF(bool, (char chr), (chr), vfIsPartOfWord, IsPartOfWord, _WidgetContainer, 0x0128u);
	VF(int, (int x, int y), (x, y), vfGetCharAt, GetCharAt, _WidgetContainer, 0x012Cu);
	VF(void, (bool bigJump), (bigJump), vfFocusCursor, FocusCursor, _WidgetContainer, 0x0130u);
#undef _CLASS
#define _CLASS ListWidget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(std_string, (int theIdx), (theIdx), vfGetSortKey, GetSortKey, _WidgetContainer, 0x0118u);
	VF(void, (bool ascending), (ascending), vfSort, Sort, _WidgetContainer, 0x011Cu);
	VF(std_string, (int theIdx), (theIdx), vfGetStringAt, GetStringAt, _WidgetContainer, 0x0120u);
	VF(int, (const std_string& theLine, bool alphabetical), (theLine, alphabetical), vfAddLine, AddLine, _WidgetContainer, 0x0124u);
	VF(void, (int theIdx, const std_string& theString), (theIdx, theString), vfSetLine, SetLine, _WidgetContainer, 0x0128u);
	VF(int, (void), (), vfGetLineCount, GetLineCount, _WidgetContainer, 0x012Cu);
	VF(int, (const std_string& theLine), (theLine), vfGetLineIdx, GetLineIdx, _WidgetContainer, 0x0130u);
	VF(void, (const std_string& theLine, const Color& theColor), (theLine, theColor), vfSetColor_0, SetColor, _WidgetContainer, 0x0134u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetLineColor, SetLineColor, _WidgetContainer, 0x0138u);
	VF(void, (int theIdx), (theIdx), vfRemoveLine, RemoveLine, _WidgetContainer, 0x013Cu);
	VF(void, (void), (), vfRemoveAll, RemoveAll, _WidgetContainer, 0x0140u);
	VF(int, (void), (), vfGetOptimalWidth, GetOptimalWidth, _WidgetContainer, 0x0144u);
	VF(int, (void), (), vfGetOptimalHeight, GetOptimalHeight, _WidgetContainer, 0x0148u);
	VF(void, (int theSelectIdx), (theSelectIdx), vfSetSelect, SetSelect, _WidgetContainer, 0x014Cu);
	VF(void, (int Id, double pos), (Id, pos), vfScrollPosition, ScrollPosition, _ScrollListener, 0x0000u);
#undef _CLASS
#define _CLASS Slider
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (double theValue), (theValue), vfSetValue, SetValue, _WidgetContainer, 0x0118u);
	VF(bool, (void), (), vfHasTransparencies, HasTransparencies, _WidgetContainer, 0x011Cu);
#undef _CLASS
#define _CLASS MV_Widget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
#undef _CLASS
#define _CLASS MsgWidget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
#undef _CLASS
#define _CLASS Shop_Widget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
#undef _CLASS
#define _CLASS MainMenu_Widget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
#undef _CLASS
#define _CLASS MsgBox
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (void), (), vfSetButtonDisabled, SetButtonDisabled, _WidgetContainer, 0x0130u);
	VF(void, (void), (), vfmAppMouseDown, mAppMouseDown, _WidgetContainer, 0x0134u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS Menu
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0014u);
	VF(void, (void), (), vfSliderVal, SliderVal, _SliderListener, 0x0000u);
	VF(void, (void), (), vfCheckboxChecked, CheckboxChecked, _CheckboxListener, 0x0000u);
#undef _CLASS
#define _CLASS Shop
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS Almance
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (void), (), vfSetButtonDisabled, SetButtonDisabled, _WidgetContainer, 0x0130u);
	VF(void, (void), (), vfmAppMouseDown, mAppMouseDown, _WidgetContainer, 0x0134u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS ContinueLevelWnd
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (void), (), vfSetButtonDisabled, SetButtonDisabled, _WidgetContainer, 0x0130u);
	VF(void, (void), (), vfmAppMouseDown, mAppMouseDown, _WidgetContainer, 0x0134u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS GameOverWnd
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (void), (), vfSetButtonDisabled, SetButtonDisabled, _WidgetContainer, 0x0130u);
	VF(void, (void), (), vfmAppMouseDown, mAppMouseDown, _WidgetContainer, 0x0134u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS InputWindow
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (void), (), vfSetButtonDisabled, SetButtonDisabled, _WidgetContainer, 0x0130u);
	VF(void, (void), (), vfmAppMouseDown, mAppMouseDown, _WidgetContainer, 0x0134u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
	VF(void, (int Id, const std_string& str), (Id, str), vfEditWidgetText, EditWidgetText, _EditListener, 0x0000u);
	VF(void, (int Id, KeyCode key), (Id, key), vfAllowKey, AllowKey, _EditListener, 0x0004u);
	VF(void, (int Id, char chr), (Id, chr), vfAllowChar, AllowChar, _EditListener, 0x0008u);
	VF(void, (int Id, const std_string& txt), (Id, txt), vfAllowText, AllowText, _EditListener, 0x000Cu);
#undef _CLASS
#define _CLASS ImitaterWnd
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (void), (), vfSetButtonDisabled, SetButtonDisabled, _WidgetContainer, 0x0130u);
	VF(void, (void), (), vfmAppMouseDown, mAppMouseDown, _WidgetContainer, 0x0134u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS WhoAreYouWnd
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Font* theFont), (theFont), vfSetButtonFont, SetButtonFont, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetHeaderFont, SetHeaderFont, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont), (theFont), vfSetLinesFont, SetLinesFont, _WidgetContainer, 0x0120u);
	VF(int, (int width), (width), vfGetPreferredHeight, GetPreferredHeight, _WidgetContainer, 0x0124u);
	VF(bool, (void), (), vfIsModal, IsModal, _WidgetContainer, 0x0128u);
	VF(int, (bool autoKill), (autoKill), vfWaitForResult, WaitForResult, _WidgetContainer, 0x012Cu);
	VF(void, (void), (), vfSetButtonDisabled, SetButtonDisabled, _WidgetContainer, 0x0130u);
	VF(void, (void), (), vfmAppMouseDown, mAppMouseDown, _WidgetContainer, 0x0134u);
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
#undef _CLASS
#define _CLASS DialogButton
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Graphics* g, Image* theImage, const Rect& theRect, int x, int y), (g, theImage, theRect, x, y), vfDrawButtonImage, DrawButtonImage, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetFont, SetFont, _WidgetContainer, 0x011Cu);
	VF(bool, (void), (), vfIsButtonDown, IsButtonDown, _WidgetContainer, 0x0120u);
#undef _CLASS
#define _CLASS ImageButton
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Graphics* g, Image* theImage, const Rect& theRect, int x, int y), (g, theImage, theRect, x, y), vfDrawButtonImage, DrawButtonImage, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetFont, SetFont, _WidgetContainer, 0x011Cu);
	VF(bool, (void), (), vfIsButtonDown, IsButtonDown, _WidgetContainer, 0x0120u);
#undef _CLASS
#define _CLASS DialogBtn
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Graphics* g, Image* theImage, const Rect& theRect, int x, int y), (g, theImage, theRect, x, y), vfDrawButtonImage, DrawButtonImage, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetFont, SetFont, _WidgetContainer, 0x011Cu);
	VF(bool, (void), (), vfIsButtonDown, IsButtonDown, _WidgetContainer, 0x0120u);
#undef _CLASS
#define _CLASS HyperlinkWidget
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (Graphics* g, Image* theImage, const Rect& theRect, int x, int y), (g, theImage, theRect, x, y), vfDrawButtonImage, DrawButtonImage, _WidgetContainer, 0x0118u);
	VF(void, (Font* theFont), (theFont), vfSetFont, SetFont, _WidgetContainer, 0x011Cu);
	VF(bool, (void), (), vfIsButtonDown, IsButtonDown, _WidgetContainer, 0x0120u);
#undef _CLASS
#define _CLASS InputBox
	VF(void, (bool free), (free), vfKill, Kill, _WidgetContainer, 0x0000u);
	VF(Rect, (void), (), vfGetRect, GetRect, _WidgetContainer, 0x0004u);
	VF(bool, (WidgetContainer* theWidget), (theWidget), vfIntersects, Intersects, _WidgetContainer, 0x0008u);
	VF(void, (Widget* theWidget), (theWidget), vfAddWidget, AddWidget, _WidgetContainer, 0x000Cu);
	VF(void, (Widget* theWidget), (theWidget), vfRemoveWidget, RemoveWidget, _WidgetContainer, 0x0010u);
	VF(bool, (Widget* theWidget), (theWidget), vfHasWidget, HasWidget, _WidgetContainer, 0x0014u);
	VF(void, (Widget* theWidget), (theWidget), vfDisableWidget, DisableWidget, _WidgetContainer, 0x0018u);
	VF(void, (bool doDelete, bool recursive), (doDelete, recursive), vfRemoveAllWidgets, RemoveAllWidgets, _WidgetContainer, 0x001Cu);
	VF(void, (Widget* theWidget), (theWidget), vfSetFocus, SetFocus, _WidgetContainer, 0x0020u);
	VF(bool, (Widget* a, Widget* b), (a, b), vfIsBelow, IsBelow, _WidgetContainer, 0x0024u);
	VF(void, (void), (), vfMarkAllDirty, MarkAllDirty, _WidgetContainer, 0x0028u);
	VF(void, (Widget* theWidget), (theWidget), vfBringToFront, BringToFront, _WidgetContainer, 0x002Cu);
	VF(void, (Widget* theWidget), (theWidget), vfBringToBack, BringToBack, _WidgetContainer, 0x0030u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutBehind, PutBehind, _WidgetContainer, 0x0034u);
	VF(void, (Widget* a, Widget* b), (a, b), vfPutInfront, PutInfront, _WidgetContainer, 0x0038u);
	VF(Point<int>, (void), (), vfGetAbsPos, GetAbsPos, _WidgetContainer, 0x003Cu);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirty_0, MarkDirty, _WidgetContainer, 0x0040u);
	VF(void, (void), (), vfMarkDirty, MarkDirty, _WidgetContainer, 0x0044u);
	VF(void, (WidgetContainer* theWidget), (theWidget), vfMarkDirtyFull_0, MarkDirtyFull, _WidgetContainer, 0x0048u);
	VF(void, (void), (), vfMarkDirtyFull, MarkDirtyFull, _WidgetContainer, 0x004Cu);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfAddedToManager, AddedToManager, _WidgetContainer, 0x0050u);
	VF(void, (WidgetManager* theWidgetManager), (theWidgetManager), vfRemovedFromManager, RemovedFromManager, _WidgetContainer, 0x0054u);
	VF(void, (void), (), vfUpdate, Update, _WidgetContainer, 0x0058u);
	VF(void, (ModalFlags* theFlags), (theFlags), vfUpdateAll, UpdateAll, _WidgetContainer, 0x005Cu);
	VF(void, (float frac), (frac), vfUpdateF, UpdateF, _WidgetContainer, 0x0060u);
	VF(void, (ModalFlags* theFlags, float frac), (theFlags, frac), vfUpdateFAll, UpdateFAll, _WidgetContainer, 0x0064u);
	VF(void, (void), (), vfDraw, Draw, _WidgetContainer, 0x0068u);
	VF(void, (ModalFlags* theFlags, Graphics* g), (theFlags, g), vfDrawAll, DrawAll, _WidgetContainer, 0x006Cu);
	VF(void, (void), (), vfSysColorChangedAll, SysColorChangedAll, _WidgetContainer, 0x0070u);
	VF(void, (void), (), vfSysColorChanged, SysColorChanged, _WidgetContainer, 0x0074u);
	VF(void, (void), (), vfOrderInManagerChanged, OrderInManagerChanged, _WidgetContainer, 0x0078u);
	VF(void, (bool visible), (visible), vfSetVisible, SetVisible, _WidgetContainer, 0x007Cu);
	VF(void, (void), (), vfSetColors, SetColors, _WidgetContainer, 0x0080u);
	VF(void, (void), (), vfSetColors_0, SetColors_0, _WidgetContainer, 0x0084u);
	VF(void, (int theIdx, const Color& theColor), (theIdx, theColor), vfSetColor, SetColor, _WidgetContainer, 0x0088u);
	VF(const Color&, (int theIdx), (theIdx), vfGetColor_0, GetColor, _WidgetContainer, 0x008Cu);
	VF(Color, (int theIdx, const Color& theDefaultColor), (theIdx, theDefaultColor), vfGetColor, GetColor, _WidgetContainer, 0x0090u);
	VF(void, (bool disable), (disable), vfSetDisabled, SetDisabled, _WidgetContainer, 0x0094u);
	VF(void, (bool show), (show), vfShowFinger, ShowFinger, _WidgetContainer, 0x0098u);
	VF(void, (int x, int y, int w, int h), (x, y, w, h), vfResize_0, Resize, _WidgetContainer, 0x009Cu);
	VF(void, (const Rect& theRect), (theRect), vfResize, Resize, _WidgetContainer, 0x00A0u);
	VF(void, (int x, int y), (x, y), vfMove, Move, _WidgetContainer, 0x00A4u);
	VF(bool, (void), (), vfWantsFocus, WantsFocus, _WidgetContainer, 0x00A8u);
	VF(void, (Graphics* g, int thePriority), (g, thePriority), vfDrawOverlay_0, DrawOverlay, _WidgetContainer, 0x00ACu);
	VF(void, (Graphics* g), (g), vfDrawOverlay, DrawOverlay, _WidgetContainer, 0x00B0u);
	VF(void, (void), (), vfGotFocus, GotFocus, _WidgetContainer, 0x00B4u);
	VF(void, (void), (), vfLostFocus, LostFocus, _WidgetContainer, 0x00B8u);
	VF(void, (char chr), (chr), vfKeyChar, KeyChar, _WidgetContainer, 0x00BCu);
	VF(void, (KeyCode key), (key), vfKeyDown, KeyDown, _WidgetContainer, 0x00C0u);
	VF(void, (KeyCode key), (key), vfKeyUp, KeyUp, _WidgetContainer, 0x00C4u);
	VF(void, (void), (), vfMouseEnter, MouseEnter, _WidgetContainer, 0x00C8u);
	VF(void, (void), (), vfMouseLeave, MouseLeave, _WidgetContainer, 0x00CCu);
	VF(void, (int x, int y), (x, y), vfMouseMove, MouseMove, _WidgetContainer, 0x00D0u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseDown_0, MouseDown, _WidgetContainer, 0x00D4u);
	VF(void, (int x, int y, int theClickCount), (x, y, theClickCount), vfMouseDown, MouseDown, _WidgetContainer, 0x00D8u);
	VF(void, (int x, int y, int theBtnNum, int theClickCount), (x, y, theBtnNum, theClickCount), vfMouseUp, MouseUp, _WidgetContainer, 0x00DCu);
	VF(void, (int x, int y, int theLastDownButtonId), (x, y, theLastDownButtonId), vfMouseUp_0, MouseUp, _WidgetContainer, 0x00E0u);
	VF(void, (int x, int y), (x, y), vfMouseUp_1, MouseUp, _WidgetContainer, 0x00E4u);
	VF(void, (int x, int y), (x, y), vfMouseDrag, MouseDrag, _WidgetContainer, 0x00E8u);
	VF(void, (int theDelta), (theDelta), vfMouseWheel, MouseWheel, _WidgetContainer, 0x00ECu);
	VF(bool, (int x, int y), (x, y), vfIsPointVisible, IsPointVisible, _WidgetContainer, 0x00F0u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine, Color theColor1, Color theColor2, const Point<int>& theShadowOffset), (g, anOffset, theLine, theColor1, theColor2, theShadowOffset), vfWriteCenteredLine_0, WriteCenteredLine, _WidgetContainer, 0x00F4u);
	VF(Rect, (Graphics* g, int anOffset, const std_string& theLine), (g, anOffset, theLine), vfWriteCenteredLine, WriteCenteredLine, _WidgetContainer, 0x00F8u);
	VF(int, (Graphics* g, const std_string& theString, int theX, int theY, int theWidth, int theJustification, bool drawString, int theOffset, int theLength), (g, theString, theX, theY, theWidth, theJustification, drawString, theOffset, theLength), vfWriteString, WriteString, _WidgetContainer, 0x00FCu);
	VF(int, (Graphics* g, const Rect& theRect, const std_string& theLine, int theLineSpacing, int theJustification), (g, theRect, theLine, theLineSpacing, theJustification), vfWriteWordWrapped, WriteWordWrapped, _WidgetContainer, 0x0100u);
	VF(int, (Graphics* g, int theWidth, const std_string& theLine, int aLineSpacing), (g, theWidth, theLine, aLineSpacing), vfGetWordWrappedHeight, GetWordWrappedHeight, _WidgetContainer, 0x0104u);
	VF(int, (int theNum), (theNum), vfGetNumDigits, GetNumDigits, _WidgetContainer, 0x0108u);
	VF(void, (Graphics* g, int theNumber, int theX, int theY, Image* theNumberStrip, int aSpacing), (g, theNumber, theX, theY, theNumberStrip, aSpacing), vfWriteNumberFromStrip, WriteNumberFromStrip, _WidgetContainer, 0x010Cu);
	VF(bool, (int x, int y), (x, y), vfContains, Contains, _WidgetContainer, 0x0110u);
	VF(Rect, (void), (), vfGetInsetRect, GetInsetRect, _WidgetContainer, 0x0114u);
	VF(void, (KeyCode theKey, char theChar), (theKey, theChar), vfProcessKey, ProcessKey, _WidgetContainer, 0x0118u);
	VF(void, (void), (), vfHiliteWord, HiliteWord, _WidgetContainer, 0x011Cu);
	VF(void, (Font* theFont, Font* theWidthCheckFont), (theFont, theWidthCheckFont), vfSetFont, SetFont, _WidgetContainer, 0x0120u);
	VF(void, (const std_string& theText, bool leftPosToZero), (theText, leftPosToZero), vfSetText, SetText, _WidgetContainer, 0x0124u);
	VF(bool, (char chr), (chr), vfIsPartOfWord, IsPartOfWord, _WidgetContainer, 0x0128u);
	VF(int, (int x, int y), (x, y), vfGetCharAt, GetCharAt, _WidgetContainer, 0x012Cu);
	VF(void, (bool bigJump), (bigJump), vfFocusCursor, FocusCursor, _WidgetContainer, 0x0130u);
#undef _CLASS
#define _CLASS MusicInterface
	VF(void, (bool free), (free), vfKill, Kill, _MusicInterface, 0x0000u);
	VF(bool, (int theSongId, const std_string& theFileName), (theSongId, theFileName), vfLoadMusic, LoadMusic, _MusicInterface, 0x0004u);
	VF(void, (int theSongId, int theOffset, bool noLoop), (theSongId, theOffset, noLoop), vfPlayMusic, PlayMusic, _MusicInterface, 0x0008u);
	VF(void, (int theSongId), (theSongId), vfStopMusic, StopMusic, _MusicInterface, 0x000Cu);
	VF(void, (int theSongId), (theSongId), vfPauseMusic, PauseMusic, _MusicInterface, 0x0010u);
	VF(void, (int theSongId), (theSongId), vfResumeMusic, ResumeMusic, _MusicInterface, 0x0014u);
	VF(void, (void), (), vfStopAllMusic, StopAllMusic, _MusicInterface, 0x0018u);
	VF(void, (int theSongId), (theSongId), vfUnloadMusic, UnloadMusic, _MusicInterface, 0x001Cu);
	VF(void, (void), (), vfUnloadAllMusic, UnloadAllMusic, _MusicInterface, 0x0020u);
	VF(void, (void), (), vfPauseAllMusic, PauseAllMusic, _MusicInterface, 0x0024u);
	VF(void, (void), (), vfResumeAllMusic, ResumeAllMusic, _MusicInterface, 0x0028u);
	VF(void, (int theSongId, int theOffset, double theSpeed, bool noLoop), (theSongId, theOffset, theSpeed, noLoop), vfFadeIn, FadeIn, _MusicInterface, 0x002Cu);
	VF(void, (int theSongId, bool stopSong, double theSpeed), (theSongId, stopSong, theSpeed), vfFadeOut, FadeOut, _MusicInterface, 0x0030u);
	VF(void, (bool stopSong, double theSpeed), (stopSong, theSpeed), vfFadeOutAll, FadeOutAll, _MusicInterface, 0x0034u);
	VF(void, (int theSongId, double theVolume), (theSongId, theVolume), vfSetSongVolume, SetSongVolume, _MusicInterface, 0x0038u);
	VF(void, (int theSongId, double theMaxVolume), (theSongId, theMaxVolume), vfSetSongMaxVolume, SetSongMaxVolume, _MusicInterface, 0x003Cu);
	VF(bool, (int theSongId), (theSongId), vfIsPlaying, IsPlaying, _MusicInterface, 0x0040u);
	VF(void, (double theVolume), (theVolume), vfSetVolume, SetVolume, _MusicInterface, 0x0044u);
	VF(void, (int theSongId, double theAmp), (theSongId, theAmp), vfSetMusicAmplify, SetMusicAmplify, _MusicInterface, 0x0048u);
	VF(void, (void), (), vfUpdate, Update, _MusicInterface, 0x004Cu);
#undef _CLASS
#define _CLASS FmodMusicInterface
	VF(void, (bool free), (free), vfKill, Kill, _MusicInterface, 0x0000u);
	VF(bool, (int theSongId, const std_string& theFileName), (theSongId, theFileName), vfLoadMusic, LoadMusic, _MusicInterface, 0x0004u);
	VF(void, (int theSongId, int theOffset, bool noLoop), (theSongId, theOffset, noLoop), vfPlayMusic, PlayMusic, _MusicInterface, 0x0008u);
	VF(void, (int theSongId), (theSongId), vfStopMusic, StopMusic, _MusicInterface, 0x000Cu);
	VF(void, (int theSongId), (theSongId), vfPauseMusic, PauseMusic, _MusicInterface, 0x0010u);
	VF(void, (int theSongId), (theSongId), vfResumeMusic, ResumeMusic, _MusicInterface, 0x0014u);
	VF(void, (void), (), vfStopAllMusic, StopAllMusic, _MusicInterface, 0x0018u);
	VF(void, (int theSongId), (theSongId), vfUnloadMusic, UnloadMusic, _MusicInterface, 0x001Cu);
	VF(void, (void), (), vfUnloadAllMusic, UnloadAllMusic, _MusicInterface, 0x0020u);
	VF(void, (void), (), vfPauseAllMusic, PauseAllMusic, _MusicInterface, 0x0024u);
	VF(void, (void), (), vfResumeAllMusic, ResumeAllMusic, _MusicInterface, 0x0028u);
	VF(void, (int theSongId, int theOffset, double theSpeed, bool noLoop), (theSongId, theOffset, theSpeed, noLoop), vfFadeIn, FadeIn, _MusicInterface, 0x002Cu);
	VF(void, (int theSongId, bool stopSong, double theSpeed), (theSongId, stopSong, theSpeed), vfFadeOut, FadeOut, _MusicInterface, 0x0030u);
	VF(void, (bool stopSong, double theSpeed), (stopSong, theSpeed), vfFadeOutAll, FadeOutAll, _MusicInterface, 0x0034u);
	VF(void, (int theSongId, double theVolume), (theSongId, theVolume), vfSetSongVolume, SetSongVolume, _MusicInterface, 0x0038u);
	VF(void, (int theSongId, double theMaxVolume), (theSongId, theMaxVolume), vfSetSongMaxVolume, SetSongMaxVolume, _MusicInterface, 0x003Cu);
	VF(bool, (int theSongId), (theSongId), vfIsPlaying, IsPlaying, _MusicInterface, 0x0040u);
	VF(void, (double theVolume), (theVolume), vfSetVolume, SetVolume, _MusicInterface, 0x0044u);
	VF(void, (int theSongId, double theAmp), (theSongId, theAmp), vfSetMusicAmplify, SetMusicAmplify, _MusicInterface, 0x0048u);
	VF(void, (void), (), vfUpdate, Update, _MusicInterface, 0x004Cu);
	VF(bool, (int theSongId, const std_string& theIntroFileName, const std_string& theRepeatFileName, bool repeat), (theSongId, theIntroFileName, theRepeatFileName, repeat), vfLoadSample_0, LoadSample, _MusicInterface, 0x0050u);
	VF(bool, (int theSongId, const std_string& theFileName, bool repeat), (theSongId, theFileName, repeat), vfLoadSample, LoadSample, _MusicInterface, 0x0054u);
#undef _CLASS
#define _CLASS BassMusicInterface
	VF(void, (bool free), (free), vfKill, Kill, _MusicInterface, 0x0000u);
	VF(bool, (int theSongId, const std_string& theFileName), (theSongId, theFileName), vfLoadMusic, LoadMusic, _MusicInterface, 0x0004u);
	VF(void, (int theSongId, int theOffset, bool noLoop), (theSongId, theOffset, noLoop), vfPlayMusic, PlayMusic, _MusicInterface, 0x0008u);
	VF(void, (int theSongId), (theSongId), vfStopMusic, StopMusic, _MusicInterface, 0x000Cu);
	VF(void, (int theSongId), (theSongId), vfPauseMusic, PauseMusic, _MusicInterface, 0x0010u);
	VF(void, (int theSongId), (theSongId), vfResumeMusic, ResumeMusic, _MusicInterface, 0x0014u);
	VF(void, (void), (), vfStopAllMusic, StopAllMusic, _MusicInterface, 0x0018u);
	VF(void, (int theSongId), (theSongId), vfUnloadMusic, UnloadMusic, _MusicInterface, 0x001Cu);
	VF(void, (void), (), vfUnloadAllMusic, UnloadAllMusic, _MusicInterface, 0x0020u);
	VF(void, (void), (), vfPauseAllMusic, PauseAllMusic, _MusicInterface, 0x0024u);
	VF(void, (void), (), vfResumeAllMusic, ResumeAllMusic, _MusicInterface, 0x0028u);
	VF(void, (int theSongId, int theOffset, double theSpeed, bool noLoop), (theSongId, theOffset, theSpeed, noLoop), vfFadeIn, FadeIn, _MusicInterface, 0x002Cu);
	VF(void, (int theSongId, bool stopSong, double theSpeed), (theSongId, stopSong, theSpeed), vfFadeOut, FadeOut, _MusicInterface, 0x0030u);
	VF(void, (bool stopSong, double theSpeed), (stopSong, theSpeed), vfFadeOutAll, FadeOutAll, _MusicInterface, 0x0034u);
	VF(void, (int theSongId, double theVolume), (theSongId, theVolume), vfSetSongVolume, SetSongVolume, _MusicInterface, 0x0038u);
	VF(void, (int theSongId, double theMaxVolume), (theSongId, theMaxVolume), vfSetSongMaxVolume, SetSongMaxVolume, _MusicInterface, 0x003Cu);
	VF(bool, (int theSongId), (theSongId), vfIsPlaying, IsPlaying, _MusicInterface, 0x0040u);
	VF(void, (double theVolume), (theVolume), vfSetVolume, SetVolume, _MusicInterface, 0x0044u);
	VF(void, (int theSongId, double theAmp), (theSongId, theAmp), vfSetMusicAmplify, SetMusicAmplify, _MusicInterface, 0x0048u);
	VF(void, (void), (), vfUpdate, Update, _MusicInterface, 0x004Cu);
#undef _CLASS
#define _CLASS NativeDisplay
	VF(void, (bool free), (free), vfKill, Kill, _NativeDisplay, 0x0000u);
#undef _CLASS
#define _CLASS DDInterface
	VF(void, (bool free), (free), vfKill, Kill, _NativeDisplay, 0x0000u);
#undef _CLASS
#define _CLASS Image
	VF(void, (bool free), (free), vfKill, Kill, _Image, 0x0000u);
	VF(bool, (const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex), (theVertices, theNumVertices, theClipRect, theColor, theDrawMode, tx, ty, convex), vfPolyFill3D, PolyFill3D, _Image, 0x0004u);
	VF(void, (const Rect& theRect, const Color& theColor, int theDrawMode), (theRect, theColor, theDrawMode), vfFillRect, FillRect, _Image, 0x0008u);
	VF(void, (const Rect& theRect, const Color& theColor, int theDrawMode), (theRect, theColor, theDrawMode), vfDrawRect, DrawRect, _Image, 0x000Cu);
	VF(void, (const Rect& theRect), (theRect), vfClearRect, ClearRect, _Image, 0x0010u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode), (theStartX, theStartY, theEndX, theEndY, theColor, theDrawMode), vfDrawLine, DrawLine, _Image, 0x0014u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode), (theStartX, theStartY, theEndX, theEndY, theColor, theDrawMode), vfDrawLineAA, DrawLineAA, _Image, 0x0018u);
	VF(void, (Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode), (theSpans, theSpanCount, theColor, theDrawMode), vfFillScanLines, FillScanLines, _Image, 0x001Cu);
	VF(void, (Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight), (theSpans, theSpanCount, theColor, theDrawMode, theCoverage, theCoverX, theCoverY, theCoverWidth, theCoverHeight), vfFillScanLinesWithCoverage, FillScanLinesWithCoverage, _Image, 0x0020u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theColor, theDrawMode), vfBlt, Blt, _Image, 0x0024u);
	VF(void, (Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theClipRect, theColor, theDrawMode), vfBltF, BltF, _Image, 0x0028u);
	VF(void, (Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY), (theImage, theX, theY, theSrcRect, theClipRect, theColor, theDrawMode, theRot, theRotCenterX, theRotCenterY), vfBltRotated, BltRotated, _Image, 0x002Cu);
	VF(void, (Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch), (theImage, theDestRect, theSrcRect, theClipRect, theColor, theDrawMode, fastStretch), vfStretchBlt, StretchBlt, _Image, 0x0030u);
	VF(void, (Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend), (theImage, x, y, theMatrix, theClipRect, theColor, theDrawMode, theSrcRect, blend), vfBltMatrix, BltMatrix, _Image, 0x0034u);
	VF(void, (Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend), (theTexture, theVertices, theNumTriangles, theClipRect, theColor, theDrawMode, tx, ty, blend), vfBltTrianglesTex, BltTrianglesTex, _Image, 0x0038u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theColor, theDrawMode), vfBltMirror, BltMirror, _Image, 0x003Cu);
	VF(void, (Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch), (theImage, theDestRect, theSrcRect, theClipRect, theColor, theDrawMode, fastStretch), vfStretchBltMirror, StretchBltMirror, _Image, 0x0040u);
#undef _CLASS
#define _CLASS MemoryImage
	VF(void, (bool free), (free), vfKill, Kill, _Image, 0x0000u);
	VF(bool, (const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex), (theVertices, theNumVertices, theClipRect, theColor, theDrawMode, tx, ty, convex), vfPolyFill3D, PolyFill3D, _Image, 0x0004u);
	VF(void, (const Rect& theRect, const Color& theColor, int theDrawMode), (theRect, theColor, theDrawMode), vfFillRect, FillRect, _Image, 0x0008u);
	VF(void, (const Rect& theRect, const Color& theColor, int theDrawMode), (theRect, theColor, theDrawMode), vfDrawRect, DrawRect, _Image, 0x000Cu);
	VF(void, (const Rect& theRect), (theRect), vfClearRect, ClearRect, _Image, 0x0010u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode), (theStartX, theStartY, theEndX, theEndY, theColor, theDrawMode), vfDrawLine, DrawLine, _Image, 0x0014u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode), (theStartX, theStartY, theEndX, theEndY, theColor, theDrawMode), vfDrawLineAA, DrawLineAA, _Image, 0x0018u);
	VF(void, (Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode), (theSpans, theSpanCount, theColor, theDrawMode), vfFillScanLines, FillScanLines, _Image, 0x001Cu);
	VF(void, (Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight), (theSpans, theSpanCount, theColor, theDrawMode, theCoverage, theCoverX, theCoverY, theCoverWidth, theCoverHeight), vfFillScanLinesWithCoverage, FillScanLinesWithCoverage, _Image, 0x0020u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theColor, theDrawMode), vfBlt, Blt, _Image, 0x0024u);
	VF(void, (Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theClipRect, theColor, theDrawMode), vfBltF, BltF, _Image, 0x0028u);
	VF(void, (Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY), (theImage, theX, theY, theSrcRect, theClipRect, theColor, theDrawMode, theRot, theRotCenterX, theRotCenterY), vfBltRotated, BltRotated, _Image, 0x002Cu);
	VF(void, (Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch), (theImage, theDestRect, theSrcRect, theClipRect, theColor, theDrawMode, fastStretch), vfStretchBlt, StretchBlt, _Image, 0x0030u);
	VF(void, (Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend), (theImage, x, y, theMatrix, theClipRect, theColor, theDrawMode, theSrcRect, blend), vfBltMatrix, BltMatrix, _Image, 0x0034u);
	VF(void, (Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend), (theTexture, theVertices, theNumTriangles, theClipRect, theColor, theDrawMode, tx, ty, blend), vfBltTrianglesTex, BltTrianglesTex, _Image, 0x0038u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theColor, theDrawMode), vfBltMirror, BltMirror, _Image, 0x003Cu);
	VF(void, (Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch), (theImage, theDestRect, theSrcRect, theClipRect, theColor, theDrawMode, fastStretch), vfStretchBltMirror, StretchBltMirror, _Image, 0x0040u);
	VF(void*, (NativeDisplay* theNative), (theNative), vfGetNativeAlphaData, GetNativeAlphaData, _Image, 0x0044u);
	VF(uchar*, (void), (), vfGetRLAlphaData, GetRLAlphaData, _Image, 0x0048u);
	VF(uchar*, (NativeDisplay* theNative), (theNative), vfGetRLAdditiveData, GetRLAdditiveData, _Image, 0x0040u);
	VF(void, (void), (), vfPurgeBits, PurgeBits, _Image, 0x005Cu);
	VF(void, (void), (), vfDeleteSWBuffers, DeleteSWBuffers, _Image, 0x0054u);
	VF(void, (void), (), vfDelete3DBuffers, Delete3DBuffers, _Image, 0x0058u);
	VF(void, (void), (), vfDeleteExtraBuffers, DeleteExtraBuffers, _Image, 0x0050u);
	VF(void, (void), (), vfReInit, ReInit, _Image, 0x006Cu);
	VF(void, (void), (), vfBitsChanged, BitsChanged, _Image, 0x0064u);
	VF(void, (void), (), vfCommitBits, CommitBits, _Image, 0x0068u);
	VF(void, (void), (), vfDeleteNativeData, DeleteNativeData, _Image, 0x0060u);
	VF(void, (void), (), vfClear, Clear, _Image, 0x0070u);
	VF(void, (ulong* theBits, int theWidth, int theHeight, bool commitBits), (theBits, theWidth, theHeight, commitBits), vfSetBits, SetBits, _Image, 0x0074u);
	VF(void, (int w, int h), (w, h), vfCreate, Create, _Image, 0x0078u);
	VF(ulong*, (void), (), vfGetBits, GetBits, _Image, 0x007Cu);
	VF(void, (bool hasTrans, bool hasAlpha), (hasTrans, hasAlpha), vfSetImageMode, SetImageMode, _Image, 0x0080u);
	VF(void, (bool isVolatile), (isVolatile), vfSetVolatile, SetVolatile, _Image, 0x0084u);
	VF(bool, (void), (), vfPalletize, Palletize, _Image, 0x0088u);
#undef _CLASS
#define _CLASS DDImage
	VF(void, (bool free), (free), vfKill, Kill, _Image, 0x0000u);
	VF(bool, (const Point<int> theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty, bool convex), (theVertices, theNumVertices, theClipRect, theColor, theDrawMode, tx, ty, convex), vfPolyFill3D, PolyFill3D, _Image, 0x0004u);
	VF(void, (const Rect& theRect, const Color& theColor, int theDrawMode), (theRect, theColor, theDrawMode), vfFillRect, FillRect, _Image, 0x0008u);
	VF(void, (const Rect& theRect, const Color& theColor, int theDrawMode), (theRect, theColor, theDrawMode), vfDrawRect, DrawRect, _Image, 0x000Cu);
	VF(void, (const Rect& theRect), (theRect), vfClearRect, ClearRect, _Image, 0x0010u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode), (theStartX, theStartY, theEndX, theEndY, theColor, theDrawMode), vfDrawLine, DrawLine, _Image, 0x0014u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode), (theStartX, theStartY, theEndX, theEndY, theColor, theDrawMode), vfDrawLineAA, DrawLineAA, _Image, 0x0018u);
	VF(void, (Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode), (theSpans, theSpanCount, theColor, theDrawMode), vfFillScanLines, FillScanLines, _Image, 0x001Cu);
	VF(void, (Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight), (theSpans, theSpanCount, theColor, theDrawMode, theCoverage, theCoverX, theCoverY, theCoverWidth, theCoverHeight), vfFillScanLinesWithCoverage, FillScanLinesWithCoverage, _Image, 0x0020u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theColor, theDrawMode), vfBlt, Blt, _Image, 0x0024u);
	VF(void, (Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theClipRect, theColor, theDrawMode), vfBltF, BltF, _Image, 0x0028u);
	VF(void, (Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY), (theImage, theX, theY, theSrcRect, theClipRect, theColor, theDrawMode, theRot, theRotCenterX, theRotCenterY), vfBltRotated, BltRotated, _Image, 0x002Cu);
	VF(void, (Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch), (theImage, theDestRect, theSrcRect, theClipRect, theColor, theDrawMode, fastStretch), vfStretchBlt, StretchBlt, _Image, 0x0030u);
	VF(void, (Image* theImage, float x, float y, const Matrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, bool blend), (theImage, x, y, theMatrix, theClipRect, theColor, theDrawMode, theSrcRect, blend), vfBltMatrix, BltMatrix, _Image, 0x0034u);
	VF(void, (Image* theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color& theColor, int theDrawMode, float tx, float ty, bool blend), (theTexture, theVertices, theNumTriangles, theClipRect, theColor, theDrawMode, tx, ty, blend), vfBltTrianglesTex, BltTrianglesTex, _Image, 0x0038u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode), (theImage, theX, theY, theSrcRect, theColor, theDrawMode), vfBltMirror, BltMirror, _Image, 0x003Cu);
	VF(void, (Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch), (theImage, theDestRect, theSrcRect, theClipRect, theColor, theDrawMode, fastStretch), vfStretchBltMirror, StretchBltMirror, _Image, 0x0040u);
	VF(void*, (NativeDisplay* theNative), (theNative), vfGetNativeAlphaData, GetNativeAlphaData, _Image, 0x0044u);
	VF(uchar*, (void), (), vfGetRLAlphaData, GetRLAlphaData, _Image, 0x0048u);
	VF(uchar*, (NativeDisplay* theNative), (theNative), vfGetRLAdditiveData, GetRLAdditiveData, _Image, 0x0040u);
	VF(void, (void), (), vfPurgeBits, PurgeBits, _Image, 0x005Cu);
	VF(void, (void), (), vfDeleteSWBuffers, DeleteSWBuffers, _Image, 0x0054u);
	VF(void, (void), (), vfDelete3DBuffers, Delete3DBuffers, _Image, 0x0058u);
	VF(void, (void), (), vfDeleteExtraBuffers, DeleteExtraBuffers, _Image, 0x0050u);
	VF(void, (void), (), vfReInit, ReInit, _Image, 0x006Cu);
	VF(void, (void), (), vfBitsChanged, BitsChanged, _Image, 0x0064u);
	VF(void, (void), (), vfCommitBits, CommitBits, _Image, 0x0068u);
	VF(void, (void), (), vfDeleteNativeData, DeleteNativeData, _Image, 0x0060u);
	VF(void, (void), (), vfClear, Clear, _Image, 0x0070u);
	VF(void, (ulong* theBits, int theWidth, int theHeight, bool commitBits), (theBits, theWidth, theHeight, commitBits), vfSetBits, SetBits, _Image, 0x0074u);
	VF(void, (int w, int h), (w, h), vfCreate, Create, _Image, 0x0078u);
	VF(ulong*, (void), (), vfGetBits, GetBits, _Image, 0x007Cu);
	VF(void, (bool hasTrans, bool hasAlpha), (hasTrans, hasAlpha), vfSetImageMode, SetImageMode, _Image, 0x0080u);
	VF(void, (bool isVolatile), (isVolatile), vfSetVolatile, SetVolatile, _Image, 0x0084u);
	VF(bool, (void), (), vfPalletize, Palletize, _Image, 0x0088u);
	VF(void, (bool wantVideoMemory), (wantVideoMemory), vfSetVideoMemory, SetVideoMemory, _Image, 0x008Cu);
	VF(void, (void), (), vfRehupFirstPixelTrans, RehupFirstPixelTrans, _Image, 0x0090u);
	VF(void, (const Rect& theRect, const Color& theColor), (theRect, theColor), vfNormalFillRect, NormalFillRect, _Image, 0x0094u);
	VF(void, (const Rect& theRect, const Color& theColor), (theRect, theColor), vfAdditiveFillRect, AdditiveFillRect, _Image, 0x0098u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor), (theImage, theX, theY, theSrcRect, theColor), vfNormalBlt, NormalBlt, _Image, 0x009Cu);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor), (theImage, theX, theY, theSrcRect, theColor), vfAdditiveBlt, AdditiveBlt, _Image, 0x00A0u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor), (theStartX, theStartY, theEndX, theEndY, theColor), vfNormalDrawLine, NormalDrawLine, _Image, 0x00A4u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor), (theStartX, theStartY, theEndX, theEndY, theColor), vfAdditiveDrawLine, AdditiveDrawLine, _Image, 0x00A8u);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor), (theStartX, theStartY, theEndX, theEndY, theColor), vfNormalDrawLineAA, NormalDrawLineAA, _Image, 0x00ACu);
	VF(void, (double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor), (theStartX, theStartY, theEndX, theEndY, theColor), vfAdditiveDrawLineAA, AdditiveDrawLineAA, _Image, 0x00B0u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor), (theImage, theX, theY, theSrcRect, theColor), vfNormalBltMirror, NormalBltMirror, _Image, 0x00B4u);
	VF(void, (Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor), (theImage, theX, theY, theSrcRect, theColor), vfAdditiveBltMirror, AdditiveBltMirror, _Image, 0x00B8u);
	VF(bool, (void), (), vfLockSurface, LockSurface, _Image, 0x00BCu);
	VF(bool, (void), (), vfUnlockSurface, UnlockSurface, _Image, 0x00C0u);
	VF(void, (LPDIRECTDRAWSURFACE theSurface), (theSurface), vfSetSurface, SetSurface, _Image, 0x00C4u);
	VF(int, (std::string* a, std::string* b), (a, b), vfWriteToCache, WriteToCache, _Image, 0x00C8u);
#undef _CLASS
#define _CLASS D3DInterface
	VF(void, (bool free), (free), vfKill, Kill, _D3DInterface, 0x0000u);
#undef _CLASS
#define _CLASS D3DTestImage
	VF(void, (bool free), (free), vfKill, Kill, _D3DTestImage, 0x0000u);
#undef _CLASS
#define _CLASS D3DTester
	VF(void, (bool free), (free), vfKill, Kill, _D3DTester, 0x0000u);
#undef _CLASS
#define _CLASS Font
	VF(void, (bool free), (free), vfKill, Kill, _Font, 0x0000u);
	VF(int, (void), (), vfGetAscent, GetAscent, _Font, 0x0004u);
	VF(int, (void), (), vfGetAscentPadding, GetAscentPadding, _Font, 0x0008u);
	VF(int, (void), (), vfGetDescent, GetDescent, _Font, 0x000Cu);
	VF(int, (void), (), vfGetHeight, GetHeight, _Font, 0x0010u);
	VF(int, (void), (), vfGetLineSpacingOffset, GetLineSpacingOffset, _Font, 0x0014u);
	VF(int, (void), (), vfGetLineSpacing, GetLineSpacing, _Font, 0x0018u);
	VF(int, (const std_string& str), (str), vfStringWidth, StringWidth, _Font, 0x001Cu);
	VF(int, (char chr), (chr), vfCharWidth, CharWidth, _Font, 0x0020u);
	VF(int, (char chr, char prev), (chr, prev), vfCharWidthKern, CharWidthKern, _Font, 0x0024u);
	VF(void, (Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect), (g, theX, theY, theString, theColor, theClipRect), vfDrawString, DrawString, _Font, 0x0028u);
	VF(Font*, (void), (), vfDuplicate, Duplicate, _Font, 0x002Cu);
#undef _CLASS
#define _CLASS Graphics
	VF(void, (bool free), (free), vfKill, Kill, _Graphics, 0x0000u);
#undef _CLASS
#define _CLASS ResourceManager
	VF(bool, (XMLElement& theElement, BaseRes* theRes, std_map<std::string, BaseRes*>& theMap), (theElement, theRes, theMap), vfParseCommonResource, ParseCommonResource, _ResourceManager, 0x0000u);
	VF(bool, (XMLElement& theElement), (theElement), vfParseSoundResource, ParseSoundResource, _ResourceManager, 0x0004u);
	VF(bool, (XMLElement& theElement), (theElement), vfParseImageResource, ParseImageResource, _ResourceManager, 0x0008u);
	VF(bool, (XMLElement& theElement), (theElement), vfParseFontResource, ParseFontResource, _ResourceManager, 0x000Cu);
	VF(bool, (XMLElement& theElement), (theElement), vfParseSetDefaults, ParseSetDefaults, _ResourceManager, 0x0010u);
	VF(bool, (void), (), vfParseResources, ParseResources, _ResourceManager, 0x0014u);
	VF(void, (void), (), vfDeleteResources, DeleteResources, _ResourceManager, 0x0018u);
	VF(void, (void), (), vfDeleteResources_0, DeleteResources_0, _ResourceManager, 0x001Cu);
	VF(bool, (ImageRes* theRes), (theRes), vfDoLoadImage, DoLoadImage, _ResourceManager, 0x0020u);
	VF(bool, (FontRes* theRes), (theRes), vfDoLoadFont, DoLoadFont, _ResourceManager, 0x0024u);
	VF(bool, (SoundRes* theRes), (theRes), vfDoLoadSound, DoLoadSound, _ResourceManager, 0x0028u);
	VF(void, (bool free), (free), vfKill, Kill, _ResourceManager, 0x002Cu);
	VF(bool, (void), (), vfLoadNextResource, LoadNextResource, _ResourceManager, 0x0030u);
	VF(void, (BaseRes* theRes), (theRes), vfResourceLoadedHook, ResourceLoadedHook, _ResourceManager, 0x0034u);
	VF(void, (const std_string& theGroup), (theGroup), vfStartLoadResources, StartLoadResources, _ResourceManager, 0x0038u);
	VF(bool, (const std_string& theGroup), (theGroup), vfLoadResources, LoadResources, _ResourceManager, 0x003Cu);
	VF(SharedImageRef, (const std_string& theId), (theId), vfGetImageThrow, GetImageThrow, _ResourceManager, 0x0040u);
	VF(int, (const std_string& theId), (theId), vfGetSoundThrow, GetSoundThrow, _ResourceManager, 0x0044u);
	VF(Font*, (const std_string& theId), (theId), vfGetFontThrow, GetFontThrow, _ResourceManager, 0x0048u);
#undef _CLASS
#define _CLASS BaseRes
	VF(void, (bool free), (free), vfKill, Kill, _BaseRes, 0x0000u);
#undef _CLASS
#define _CLASS FontRes
	VF(void, (bool free), (free), vfKill, Kill, _BaseRes, 0x0000u);
#undef _CLASS
#define _CLASS ImageRes
	VF(void, (bool free), (free), vfKill, Kill, _BaseRes, 0x0000u);
#undef _CLASS
#define _CLASS SoundRes
	VF(void, (bool free), (free), vfKill, Kill, _BaseRes, 0x0000u);
#undef _CLASS
#define _CLASS GameApp
	VF(void, (int mouse, int count), (mouse, count), vfButtonPress_0, ButtonPress, _ButtonListener, 0x0000u);
	VF(void, (int mouse), (mouse), vfButtonPress, ButtonPress, _ButtonListener, 0x0004u);
	VF(void, (int mouse), (mouse), vfButtonDepress, ButtonDepress, _ButtonListener, 0x0008u);
	VF(void, (int mouse), (mouse), vfButtonDownTick, ButtonDownTick, _ButtonListener, 0x000Cu);
	VF(void, (int mouse), (mouse), vfButtonMouseEnter, ButtonMouseEnter, _ButtonListener, 0x0010u);
	VF(void, (int mouse), (mouse), vfButtonMouseLeave, ButtonMouseLeave, _ButtonListener, 0x0014u);
	VF(void, (int mouse, int x, int y), (mouse, x, y), vfButtonMouseMove, ButtonMouseMove, _ButtonListener, 0x0018u);
	VF(bool, (bool allowSleep), (allowSleep), vfProcess, Process, _ButtonListener, 0x001Cu);
	VF(void, (void), (), vfUpdateFrames, UpdateFrames, _ButtonListener, 0x0020u);
	VF(bool, (void), (), vfDoUpdateFrames, DoUpdateFrames, _ButtonListener, 0x0024u);
	VF(void, (float theFrac), (theFrac), vfDoUpdateFramesF, DoUpdateFramesF, _ButtonListener, 0x0028u);
	VF(void, (void), (), vfMakeWindow, MakeWindow, _ButtonListener, 0x002Cu);
	VF(void, (void), (), vfEnforceCursor, EnforceCursor, _ButtonListener, 0x0030u);
	VF(void, (void), (), vfReInitImages, ReInitImages, _ButtonListener, 0x0034u);
	VF(void, (void), (), vfDeleteNativeImageData, DeleteNativeImageData, _ButtonListener, 0x0038u);
	VF(void, (void), (), vfDeleteExtraImageData, DeleteExtraImageData, _ButtonListener, 0x003Cu);
	VF(void, (void), (), vfLoadingThreadCompleted, LoadingThreadCompleted, _ButtonListener, 0x0040u);
	VF(void, (bool free), (free), vfKill, Kill, _ButtonListener, 0x0044u);
	VF(MusicInterface*, (HWND hwnd), (hwnd), vfCreateMusicInterface, CreateMusicInterface, _ButtonListener, 0x0048u);
	VF(void, (void), (), vfInitHook, InitHook, _ButtonListener, 0x004Cu);
	VF(void, (void), (), vfShutdownHook, ShutdownHook, _ButtonListener, 0x0050u);
	VF(void, (void), (), vfPreTerminate, PreTerminate, _ButtonListener, 0x0054u);
	VF(void, (void), (), vfLoadingThreadProc, LoadingThreadProc, _ButtonListener, 0x0058u);
	VF(void, (void), (), vfWriteToRegistry, WriteToRegistry, _ButtonListener, 0x005Cu);
	VF(void, (void), (), vfReadFromRegistry, ReadFromRegistry, _ButtonListener, 0x0060u);
	VF(Dialog*, (int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode), (theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode), vfNewDialog, NewDialog, _ButtonListener, 0x0064u);
	VF(void, (void), (), vfPreDisplayHook, PreDisplayHook, _ButtonListener, 0x0068u);
	VF(void, (void), (), vfBeginPopup, BeginPopup, _ButtonListener, 0x006Cu);
	VF(void, (void), (), vfEndPopup, EndPopup, _ButtonListener, 0x0070u);
	VF(void, (void), (), vfMsgBox_0, MsgBox_0, _ButtonListener, 0x0074u);
	VF(void, (void), (), vfMsgBox, MsgBox, _ButtonListener, 0x0078u);
	VF(void, (void), (), vfPopup_0, Popup_0, _ButtonListener, 0x007Cu);
	VF(void, (void), (), vfPopup, Popup, _ButtonListener, 0x0080u);
	VF(void, (const std_string& theError), (theError), vfLogScreenSaverError, LogScreenSaverError, _ButtonListener, 0x0084u);
	VF(void, (Widget* theWidget), (theWidget), vfSafeDeleteWidget, SafeDeleteWidget, _ButtonListener, 0x0088u);
	VF(void, (const std_string& theURL), (theURL), vfURLOpenFailed, URLOpenFailed, _ButtonListener, 0x008Cu);
	VF(void, (const std_string& theURL), (theURL), vfURLOpenSucceeded, URLOpenSucceeded, _ButtonListener, 0x0090u);
	VF(bool, (const std_string& theURL, bool shutdownOnOpen), (theURL, shutdownOnOpen), vfOpenURL, OpenURL, _ButtonListener, 0x0094u);
	VF(std_string, (const std_string& thePath), (thePath), vfGetProductVersion, GetProductVersion, _ButtonListener, 0x0098u);
	VF(void, (void), (), vfSEHOccured, SEHOccured, _ButtonListener, 0x009Cu);
	VF(std_string, (void), (), vfGetGameSEHInfo, GetGameSEHInfo, _ButtonListener, 0x00A0u);
	VF(void, (std_map<std::string, std::string>* theDefinesMap), (theDefinesMap), vfGetSEHWebParams, GetSEHWebParams, _ButtonListener, 0x00A4u);
	VF(void, (void), (), vfShutdown, Shutdown, _ButtonListener, 0x00A8u);
	VF(void, (void), (), vfDoParseCmdLine, DoParseCmdLine, _ButtonListener, 0x00ACu);
	VF(void, (const std_string& theCmdLine), (theCmdLine), vfParseCmdLine, ParseCmdLine, _ButtonListener, 0x00B0u);
	VF(void, (const std_string& theParamName, const std_string& theParamValue), (theParamName, theParamValue), vfHandleCmdLineParam, HandleCmdLineParam, _ButtonListener, 0x00B4u);
	VF(void, (int theType, int theParam), (theType, theParam), vfHandleNotifyGameMessage, HandleNotifyGameMessage, _ButtonListener, 0x00B8u);
	VF(void, (void), (), vfHandleGameAlreadyRunning, HandleGameAlreadyRunning, _ButtonListener, 0x00BCu);
	VF(void, (void), (), vfStart, Start, _ButtonListener, 0x00C0u);
	VF(void, (void), (), vfInit, Init, _ButtonListener, 0x00C4u);
	VF(void, (void), (), vfPreDDInterfaceInitHook, PreDDInterfaceInitHook, _ButtonListener, 0x00C8u);
	VF(void, (void), (), vfPostDDInterfaceInitHook, PostDDInterfaceInitHook, _ButtonListener, 0x00CCu);
	VF(bool, (const char* theIntendedPath), (theIntendedPath), vfChangeDirHook, ChangeDirHook, _ButtonListener, 0x00D0u);
	VF(void, (SoundId id, int pan), (id, pan), vfPlaySample_0, PlaySample, _ButtonListener, 0x00D4u);
	VF(void, (SoundId id), (id), vfPlaySample, PlaySample, _ButtonListener, 0x00D8u);
	VF(double, (void), (), vfGetMasterVolume, GetMasterVolume, _ButtonListener, 0x00DCu);
	VF(double, (void), (), vfGetMusicVolume, GetMusicVolume, _ButtonListener, 0x00E0u);
	VF(double, (void), (), vfGetSfxVolume, GetSfxVolume, _ButtonListener, 0x00E4u);
	VF(bool, (void), (), vfIsMuted, IsMuted, _ButtonListener, 0x00E8u);
	VF(void, (double theVolume), (theVolume), vfSetMasterVolume, SetMasterVolume, _ButtonListener, 0x00ECu);
	VF(void, (double theVolume), (theVolume), vfSetMusicVolume, SetMusicVolume, _ButtonListener, 0x00F0u);
	VF(void, (double theVolume), (theVolume), vfSetSfxVolume, SetSfxVolume, _ButtonListener, 0x00F4u);
	VF(void, (bool autoMute), (autoMute), vfMute, Mute, _ButtonListener, 0x00F8u);
	VF(void, (bool autoMute), (autoMute), vfUnmute, Unmute, _ButtonListener, 0x00FCu);
	VF(double, (void), (), vfGetLoadingThreadProgress, GetLoadingThreadProgress, _ButtonListener, 0x0100u);
	VF(DDImage*, (const std_string& theFileName, bool commitBits), (theFileName, commitBits), vfGetImage, GetImage, _ButtonListener, 0x0104u);
	VF(int, (SharedImageRef* a, int b, int c, int d, int e), (a, b, c, d, e), vfSetSharedImage, SetSharedImage, _ButtonListener, 0x0108u);
	VF(SharedImageRef, (const std_string& theFileName, const std::string& theVariant, bool* isNew), (theFileName, theVariant, isNew), vfGetSharedImage, GetSharedImage, _ButtonListener, 0x010Cu);
	VF(void, (bool wantWindowed, bool is3d, bool force), (wantWindowed, is3d, force), vfSwitchScreenMode_1, SwitchScreenMode, _ButtonListener, 0x0110u);
	VF(void, (bool wantWindowed), (wantWindowed), vfSwitchScreenMode_0, SwitchScreenMode, _ButtonListener, 0x0114u);
	VF(void, (void), (), vfSwitchScreenMode, SwitchScreenMode, _ButtonListener, 0x0118u);
	VF(void, (bool isDisabled), (isDisabled), vfSetAlphaDisabled, SetAlphaDisabled, _ButtonListener, 0x011Cu);
	VF(Dialog*, (int theDialogId, bool isModal, const std_string& theDialogHeader, const std_string& theDialogLines, const std_string& theDialogFooter, int theButtonMode), (theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode), vfDoDialog, DoDialog, _ButtonListener, 0x0120u);
	VF(Dialog*, (Dialog::Type type), (type), vfGetDialog, GetDialog, _ButtonListener, 0x0124u);
	VF(void, (Dialog* theDialog), (theDialog), vfAddDialog, AddDialog, _ButtonListener, 0x0128u);
	VF(void, (int theDialogId, Dialog* theDialog), (theDialogId, theDialog), vfAddDialog_0, AddDialog, _ButtonListener, 0x012Cu);
	VF(void, (void), (), vfKillDialog_0, KillDialog_0, _ButtonListener, 0x0130u);
	VF(void, (void), (), vfKillDialog, KillDialog, _ButtonListener, 0x0134u);
	VF(void, (void), (), vfKillDialog_1, KillDialog_1, _ButtonListener, 0x0138u);
	VF(int, (void), (), vfGetDialogCount, GetDialogCount, _ButtonListener, 0x013Cu);
	VF(void, (void), (), vfModalOpen, ModalOpen, _ButtonListener, 0x0140u);
	VF(void, (void), (), vfModalClose, ModalClose, _ButtonListener, 0x0144u);
	VF(void, (void), (), vfGotFocus, GotFocus, _ButtonListener, 0x0148u);
	VF(void, (void), (), vfLostFocus, LostFocus, _ButtonListener, 0x014Cu);
	VF(bool, (WPARAM wParam), (wParam), vfIsAltKeyUsed, IsAltKeyUsed, _ButtonListener, 0x0150u);
	VF(bool, (int theKey), (theKey), vfDebugKeyDown, DebugKeyDown, _ButtonListener, 0x0154u);
	VF(bool, (int theKey, bool ctrlDown, bool altDown), (theKey, ctrlDown, altDown), vfDebugKeyDownAsync, DebugKeyDownAsync, _ButtonListener, 0x0158u);
	VF(void, (void), (), vfCloseRequestAsync, CloseRequestAsync, _ButtonListener, 0x015Cu);
	VF(void, (void), (), vfDone3dTesting, Done3dTesting, _ButtonListener, 0x0160u);
	VF(std_string, (void), (), vfNotifyCrashHook, NotifyCrashHook, _ButtonListener, 0x0164u);
	VF(void, (void), (), vfCheckSignature, CheckSignature, _ButtonListener, 0x0168u);
	VF(bool, (void), (), vfDrawDirtyStuff, DrawDirtyStuff, _ButtonListener, 0x016Cu);
	VF(void, (Rect* theClipRect), (theClipRect), vfRedraw, Redraw, _ButtonListener, 0x0170u);
	VF(void, (void), (), vfInitPropertiesHook, InitPropertiesHook, _ButtonListener, 0x0174u);
	VF(void, (void), (), vfDoMainLoop, DoMainLoop, _ButtonListener, 0x0178u);
	VF(bool, (bool* updated), (updated), vfUpdateAppStep, UpdateAppStep, _ButtonListener, 0x017Cu);
	VF(bool, (void), (), vfUpdateApp, UpdateApp, _ButtonListener, 0x0180u);
	VF(bool, (void), (), vfAppCanRestore, AppCanRestore, _ButtonListener, 0x0184u);
	VF(bool, (HWND a, unsigned int b, unsigned int c, int d, int* e), (a, b, c, d, e), vfOverrideWindowProc, OverrideWindowProc, _ButtonListener, 0x0188u);
	VF(bool, (void), (), vfShouldCheckForUpdate, ShouldCheckForUpdate, _ButtonListener, 0x018Cu);
	VF(void, (void), (), vfUpdateCheckQueried, UpdateCheckQueried, _ButtonListener, 0x0190u);
	VF(bool, (void), (), vfOpenRegisterPage, OpenRegisterPage, _ButtonListener, 0x0194u);
	VF(int, (std_map<std_string, std_string> a), (a), vfOpenRegisterPage_0, OpenRegisterPage, _ButtonListener, 0x0198u);
	VF(bool, (std_string const& a, class std::map<std_string, std_string> const& b), (a, b), vfOpenHTMLTemplate, OpenHTMLTemplate, _ButtonListener, 0x019Cu);
	VF(void, (void), (), vfOpenUpdateURL, OpenUpdateURL, _ButtonListener, 0x01A0u);
	VF(void, (char a), (a), vfKeyChar, KeyChar, _ButtonListener, 0x01A4u);
	VF(void, (void), (), vfLoadingCompleted, LoadingCompleted, _ButtonListener, 0x01A8u);
	VF(void, (bool exit), (exit), vfShowResourceError, ShowResourceError, _ButtonListener, 0x01ACu);
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonPress, DialogButtonPress, _DialogListener, 0x0000u);
	VF(void, (int dlgId, int btnId), (dlgId, btnId), vfDialogButtonDepress, DialogButtonDepress, _DialogListener, 0x0004u);
#undef _CLASS
#define _CLASS SoundInstance
	VF(void, (bool free), (free), vfKill, Kill, _SoundInstance, 0x0000u);
	VF(void, (void), (), vfRelease, Release, _SoundInstance, 0x0004u);
	VF(void, (double theBaseVolume), (theBaseVolume), vfSetBaseVolume, SetBaseVolume, _SoundInstance, 0x0008u);
	VF(void, (int theBasePan), (theBasePan), vfSetBasePan, SetBasePan, _SoundInstance, 0x000Cu);
	VF(void, (double theNumSteps), (theNumSteps), vfAdjustPitch, AdjustPitch, _SoundInstance, 0x0010u);
	VF(void, (double theVolume), (theVolume), vfSetVolume, SetVolume, _SoundInstance, 0x0014u);
	VF(void, (int thePosition), (thePosition), vfSetPan, SetPan, _SoundInstance, 0x0018u);
	VF(bool, (bool looping, bool autoRelease), (looping, autoRelease), vfPlay, Play, _SoundInstance, 0x001Cu);
	VF(void, (void), (), vfStop, Stop, _SoundInstance, 0x0020u);
	VF(bool, (int theSongId), (theSongId), vfIsPlaying, IsPlaying, _SoundInstance, 0x0024u);
	VF(bool, (void), (), vfIsReleased, IsReleased, _SoundInstance, 0x0028u);
	VF(double, (void), (), vfGetVolume, GetVolume, _SoundInstance, 0x002Cu);
#undef _CLASS
#define _CLASS Sysfont
	VF(void, (bool free), (free), vfKill, Kill, _Font, 0x0000u);
	VF(int, (void), (), vfGetAscent, GetAscent, _Font, 0x0004u);
	VF(int, (void), (), vfGetAscentPadding, GetAscentPadding, _Font, 0x0008u);
	VF(int, (void), (), vfGetDescent, GetDescent, _Font, 0x000Cu);
	VF(int, (void), (), vfGetHeight, GetHeight, _Font, 0x0010u);
	VF(int, (void), (), vfGetLineSpacingOffset, GetLineSpacingOffset, _Font, 0x0014u);
	VF(int, (void), (), vfGetLineSpacing, GetLineSpacing, _Font, 0x0018u);
	VF(int, (const std_string& str), (str), vfStringWidth, StringWidth, _Font, 0x001Cu);
	VF(int, (char chr), (chr), vfCharWidth, CharWidth, _Font, 0x0020u);
	VF(int, (char chr, char prev), (chr, prev), vfCharWidthKern, CharWidthKern, _Font, 0x0024u);
	VF(void, (Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect), (g, theX, theY, theString, theColor, theClipRect), vfDrawString, DrawString, _Font, 0x0028u);
	VF(Font*, (void), (), vfDuplicate, Duplicate, _Font, 0x002Cu);
#undef _CLASS
#define _CLASS ActiveFontLayer
	void(__thiscall _CLASS::*& _CLASS::vfKill)(bool free) = *(void(__thiscall _CLASS::**)(bool free))(0x0000u + _CLASS::vfAddr);
#undef _CLASS
#define _CLASS DSoundInstance
	VF(void, (bool free), (free), vfKill, Kill, _SoundInstance, 0x0000u);
	VF(void, (void), (), vfRelease, Release, _SoundInstance, 0x0004u);
	VF(void, (double theBaseVolume), (theBaseVolume), vfSetBaseVolume, SetBaseVolume, _SoundInstance, 0x0008u);
	VF(void, (int theBasePan), (theBasePan), vfSetBasePan, SetBasePan, _SoundInstance, 0x000Cu);
	VF(void, (double theNumSteps), (theNumSteps), vfAdjustPitch, AdjustPitch, _SoundInstance, 0x0010u);
	VF(void, (double theVolume), (theVolume), vfSetVolume, SetVolume, _SoundInstance, 0x0014u);
	VF(void, (int thePosition), (thePosition), vfSetPan, SetPan, _SoundInstance, 0x0018u);
	VF(bool, (bool looping, bool autoRelease), (looping, autoRelease), vfPlay, Play, _SoundInstance, 0x001Cu);
	VF(void, (void), (), vfStop, Stop, _SoundInstance, 0x0020u);
	VF(bool, (int theSongId), (theSongId), vfIsPlaying, IsPlaying, _SoundInstance, 0x0024u);
	VF(bool, (void), (), vfIsReleased, IsReleased, _SoundInstance, 0x0028u);
	VF(double, (void), (), vfGetVolume, GetVolume, _SoundInstance, 0x002Cu);
#undef _CLASS
#define _CLASS SoundManager
	VF(void, (bool free), (free), vfKill, Kill, _SoundManager, 0x0000u);
	VF(bool, (void), (), vfInitialized, Initialized, _SoundManager, 0x0004u);
	VF(bool, (const std_string& theFilename), (theFilename), vfLoadSound, LoadSound, _SoundManager, 0x0008u);
	VF(bool, (unsigned int theSfxID, const std_string& theFilename), (theSfxID, theFilename), vfLoadSound_0, LoadSound, _SoundManager, 0x000Cu);
	VF(void, (unsigned int theSfxID), (theSfxID), vfReleaseSound, ReleaseSound, _SoundManager, 0x0010u);
	VF(void, (double theVolume), (theVolume), vfSetVolume, SetVolume, _SoundManager, 0x0014u);
	VF(void, (unsigned int theSfxID, double theBaseVolume), (theSfxID, theBaseVolume), vfSetBaseVolume, SetBaseVolume, _SoundManager, 0x0018u);
	VF(void, (unsigned int theSfxID, int theBasePan), (theSfxID, theBasePan), vfSetBasePan, SetBasePan, _SoundManager, 0x001Cu);
	VF(SoundInstance*, (SoundId id), (id), vfGetSoundInstance, GetSoundInstance, _SoundManager, 0x0020u);
	VF(void, (void), (), vfReleaseSounds, ReleaseSounds, _SoundManager, 0x0024u);
	VF(void, (void), (), vfReleaseChannels, ReleaseChannels, _SoundManager, 0x0028u);
	VF(double, (void), (), vfGetMasterVolume, GetMasterVolume, _SoundManager, 0x002Cu);
	VF(void, (double theVolume), (theVolume), vfSetMasterVolume, SetMasterVolume, _SoundManager, 0x0030u);
	VF(void, (void), (), vfFlush, Flush, _SoundManager, 0x0034u);
	VF(void, (HWND theHWnd, bool isWindowed), (theHWnd, isWindowed), vfSetCooperativeWindow, SetCooperativeWindow, _SoundManager, 0x0038u);
	VF(void, (void), (), vfStopAllSounds, StopAllSounds, _SoundManager, 0x003Cu);
	VF(int, (void), (), vfGetFreeSoundId, GetFreeSoundId, _SoundManager, 0x0040u);
	VF(int, (void), (), vfGetNumSounds, GetNumSounds, _SoundManager, 0x0044u);
#undef _CLASS
#define _CLASS DSoundManager
	VF(void, (bool free), (free), vfKill, Kill, _SoundManager, 0x0000u);
	VF(bool, (void), (), vfInitialized, Initialized, _SoundManager, 0x0004u);
	VF(bool, (const std_string& theFilename), (theFilename), vfLoadSound, LoadSound, _SoundManager, 0x0008u);
	VF(bool, (unsigned int theSfxID, const std_string& theFilename), (theSfxID, theFilename), vfLoadSound_0, LoadSound, _SoundManager, 0x000Cu);
	VF(void, (unsigned int theSfxID), (theSfxID), vfReleaseSound, ReleaseSound, _SoundManager, 0x0010u);
	VF(void, (double theVolume), (theVolume), vfSetVolume, SetVolume, _SoundManager, 0x0014u);
	VF(void, (unsigned int theSfxID, double theBaseVolume), (theSfxID, theBaseVolume), vfSetBaseVolume, SetBaseVolume, _SoundManager, 0x0018u);
	VF(void, (unsigned int theSfxID, int theBasePan), (theSfxID, theBasePan), vfSetBasePan, SetBasePan, _SoundManager, 0x001Cu);
	VF(SoundInstance*, (SoundId id), (id), vfGetSoundInstance, GetSoundInstance, _SoundManager, 0x0020u);
	VF(void, (void), (), vfReleaseSounds, ReleaseSounds, _SoundManager, 0x0024u);
	VF(void, (void), (), vfReleaseChannels, ReleaseChannels, _SoundManager, 0x0028u);
	VF(double, (void), (), vfGetMasterVolume, GetMasterVolume, _SoundManager, 0x002Cu);
	VF(void, (double theVolume), (theVolume), vfSetMasterVolume, SetMasterVolume, _SoundManager, 0x0030u);
	VF(void, (void), (), vfFlush, Flush, _SoundManager, 0x0034u);
	VF(void, (void), (), vfSetCooperativeWindow, SetCooperativeWindow, _SoundManager, 0x0038u);
	VF(void, (void), (), vfStopAllSounds, StopAllSounds, _SoundManager, 0x003Cu);
	VF(int, (void), (), vfGetFreeSoundId, GetFreeSoundId, _SoundManager, 0x0040u);
	VF(int, (void), (), vfGetNumSounds, GetNumSounds, _SoundManager, 0x0044u);
#undef _CLASS
#define _CLASS FmodInstance
	VF(void, (bool free), (free), vfKill, Kill, _FmodInstance, 0x0000u);
#undef _CLASS
#define _CLASS HttpTransfer
	VF(void, (bool free), (free), vfKill, Kill, _HttpTransfer, 0x0000u);
#undef _CLASS
#define _CLASS ImageFont
	VF(void, (bool free), (free), vfKill, Kill, _Font, 0x0000u);
	VF(int, (void), (), vfGetAscent, GetAscent, _Font, 0x0004u);
	VF(int, (void), (), vfGetAscentPadding, GetAscentPadding, _Font, 0x0008u);
	VF(int, (void), (), vfGetDescent, GetDescent, _Font, 0x000Cu);
	VF(int, (void), (), vfGetHeight, GetHeight, _Font, 0x0010u);
	VF(int, (void), (), vfGetLineSpacingOffset, GetLineSpacingOffset, _Font, 0x0014u);
	VF(int, (void), (), vfGetLineSpacing, GetLineSpacing, _Font, 0x0018u);
	VF(int, (const std_string& str), (str), vfStringWidth, StringWidth, _Font, 0x001Cu);
	VF(int, (char chr), (chr), vfCharWidth, CharWidth, _Font, 0x0020u);
	VF(int, (char chr, char prev), (chr, prev), vfCharWidthKern, CharWidthKern, _Font, 0x0024u);
	VF(void, (Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect& theClipRect), (g, theX, theY, theString, theColor, theClipRect), vfDrawString, DrawString, _Font, 0x0028u);
	VF(Font*, (void), (), vfDuplicate, Duplicate, _Font, 0x002Cu);
	VF(void, (void), (), vfGenerateActiveFontLayers, GenerateActiveFontLayers, _Font, 0x0030u);
	VF(void, (Graphics* g, int theX, int theY, const std_string& theString, const Color& theColor, const Rect* theClipRect, std_list<Rect>* theDrawnAreas, int* theWidth), (g, theX, theY, theString, theColor, theClipRect, theDrawnAreas, theWidth), vfDrawStringEx, DrawStringEx, _Font, 0x0034u);
	VF(void, (int thePointSize), (thePointSize), vfSetPointSize, SetPointSize, _Font, 0x0038u);
	VF(int, (void), (), vfGetPointSize, GetPointSize, _Font, 0x003Cu);
	VF(void, (double theScale), (theScale), vfSetScale, SetScale, _Font, 0x0040u);
	VF(int, (void), (), vfGetDefaultPointSize, GetDefaultPointSize, _Font, 0x0044u);
	VF(bool, (std_string theTagName), (theTagName), vfAddTag, AddTag, _Font, 0x0048u);
	VF(bool, (std_string theTagName), (theTagName), vfRemoveTag, RemoveTag, _Font, 0x004Cu);
	VF(bool, (std_string theTagName), (theTagName), vfHasTag, HasTag, _Font, 0x0050u);
	VF(std_string, (std_string theName), (theName), vfGetDefine, GetDefine, _Font, 0x0054u);
	VF(void, (void), (), vfPrepare, Prepare, _Font, 0x0058u);
	VF(int, (std::string* a, std::string* b), (a, b), vfWriteToCache, WriteToCache, _Font, 0x005Cu);
#undef _CLASS
#define _CLASS PropertiesParser
	void(__thiscall _CLASS::*& _CLASS::vfKill)(bool free) = *(void(__thiscall _CLASS::**)(bool free))(0x0000u + _CLASS::vfAddr);
#undef _CLASS
#undef VF
}