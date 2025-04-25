#include "pvzData.h"
#include "ui.h"


namespace Pvz {
	int rand(int n, MTRand& rand) {
		return rand.NextNoAssert() % n;
	}
	int rand(int min, int max, MTRand& rand) {
		if (min == max)return min;
		return rand.NextNoAssert() % (max - min) + min;
	}
	float rand(float n, MTRand& rand) {
		return(float)rand.NextNoAssert() / 2147483648.0f * n;
	}
	float rand(float min, float max, MTRand& rand) {
		if (min == max)return min;
		return(float)defaultRand.NextNoAssert() / 2147483648.0f * (max - min) + min;
	}



	void Zombie::iztUpdate() {
		Anim* a = (*mApp)[mAnimId];
		if (state == State::DYING)UpdateFallGround(), Move();
		else {
			if (propCountdown > 0 && butterCountdown == 0)--propCountdown;
			if (slowCountdown > 0 && --slowCountdown == 0) {
				if (butterCountdown > 0)SetAnimSpeed(0.0f);
				else if (isDying() || isStopped())SetAnimSpeed(mAnimSpeed);
				else if (!eating) {
					PartProp* ground = a->GetPart(u8"_ground");
					if (ground) {
						float len = ground->mTransforms[a->initFrame + a->frameCount - 1].mTransX - ground->mTransforms[a->initFrame].mTransX;
						if (len >= 0.000001f)SetAnimSpeed(v * (float)a->frameCount * 47.0f / len);
					}
				}
			}
			if (butterCountdown > 0 && --butterCountdown == 0)BreakButter();
			if (butterCountdown == 0) {
				if (movementState == MovementState::ENTER_LADDER)UpdateUpLadder();
				if (movementState == MovementState::LEAVE_LADDER)UpdateDownLadder();
				if (type == Type::LADDER_ZOMBIE)UpdateLadder();
				else if (type == Type::IMP)UpdateIMP();
				else if (type == Type::POLE_VAULTING_ZOMBIE)UpdatePole();
				if (type != Type::BUNGEE_ZOMBIE)Move();
				if (or (
					type == Type::BUNGEE_ZOMBIE,
					inrange(state,
						State::POLE_VAULTING_JUMP,
						State::POLE_VAULTING_RUN,
						State::DIGGER_JUMP,
						State::DIGGER_DOUBT,
						State::DIGGER_ATTRACTED,
						State::DIGGER_DASE,
						State::BACKUP_DANCER_SPAWN,
						State::MJ_PREPARE,
						State::MJ_TURN,
						State::MJ_SUMMON,
						State::LADDER_PLACING)
					, movementState == MovementState::ENTER_LADDER,
					movementState == MovementState::LEAVE_LADDER,
					!haveHead,
					(existTime % (slowCountdown > 0 ? 8 : 4) != 0)
					));
				else {
					Plant* plant = GetTargetPlant(ZombieHitType::BITE);
					if (plant) {
						if (state == State::MJ_ENTER)propCountdown = 1;
						if (mBoard->GetGridBuilding(plant->col, plant->row, Building::Type::LADDER) && type != Type::DIGGER_ZOMBIE) {
							eating = false;
							AnimStartWalk(0);
							if (butterCountdown > 0)SetAnimSpeed(0.0f);
							else if (isDying() || isStopped())SetAnimSpeed(mAnimSpeed);
							if (movementState == MovementState::NIL && lastLadderCol != plant->col) {
								movementState = MovementState::ENTER_LADDER;
								lastLadderCol = plant->col;
							}
						} else {
							eating = true;
							if (state == State::LADDER_RUN) {
								AnimSetSegment(u8"anim_laddereat", Anim::LoopType::LOOP, 0);
							} else if (state == State::NEWSPAPER_ANGRY) {
								AnimSetSegment(u8"anim_eat_nopaper", Anim::LoopType::LOOP, 0);
							} else {
								AnimSetSegment(u8"anim_eat", Anim::LoopType::LOOP, 0);
							}
							if (inrange(plant->state,
								Plant::State::SQUASH_LOOK,
								Plant::State::SQUASH_PREPARE
							) || (plant->type == Plant::Type::POTATO_MINE && plant->state != Plant::State::NIL));
							else {
								plant->eatenCountdown = 50;
								if (lastHittedCount < -500 && plant->type == Plant::Type::WALL_NUT)plant->hp -= 8;
								else plant->hp -= 4;
								if (plant->hp <= 0)plant->Kill();
							}
						}
					} else if (eating) {
						eating = false;
						AnimStartWalk(0);
					}
				}
			}
			if (isDying())return;
		}
		if (type == Type::BUNGEE_ZOMBIE)UpdateBungee();
		UpdateAnimate();
		--lastHittedCount;
		if (shieldHittedCount > 0)--shieldHittedCount;
		if (shieldShakedCount > 0)--shieldShakedCount;
		if (vanishCountdown > 0 && --vanishCountdown == 0)Kill();
		mX = (int)x;
		mY = (int)y;
		Attachment* at = (*mApp)[mAttachmentID];
		if (at) {
			at->Update();
			at->SetPosition(x, y + h);
		}
		UpdateAnim();
	}

	void Plant::iztUpdate() {
		if (bungeeProp != Plant::BungeeProp::NORMAL)return;
		UpdateAnim();
		if (propCountdown > 0)--propCountdown;
		if (type == Plant::Type::POTATO_MINE)UpdatePotatomone();
		else if (type == Plant::Type::CHOMPER)UpdateChomper();
		if (canAttack)UpdateAttack();
		Shake();
		Anim* a = (*mApp)[mAnimID];
		if (a)a->iztUpdate();
	}

	void Anim::iztUpdate() {
		if (frameCount == 0 || vanished)return;
		lastUpdateRate = updateRate;
		updateRate += 0.01f * updateV / (float)frameCount;
		if (updateV > 0.0f) {
			switch (loopType) {
			case LoopType::PLAY_ONCE:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME:
				if (updateRate >= 1.0f) {
					updateRate = 1.0f;
					loopCount = 1;
					vanished = true;
				}
				break;
			case LoopType::PLAY_ONCE_AND_HOLD:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD:
				if (updateRate >= 1.0f) {
					loopCount = 1;
					updateRate = 1.0f;
				}
				break;
			default:
				while (updateRate >= 1.0f) {
					++loopCount;
					updateRate -= 1.0f;
				}
				break;
			}
		} else {
			switch (loopType) {
			case LoopType::PLAY_ONCE:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME:
				if (updateRate < 0.0f) {
					updateRate = 0.0f;
					loopCount = 1;
					vanished = true;
				}
				break;
			case LoopType::PLAY_ONCE_AND_HOLD:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD:
				if (updateRate < 0.0f) {
					loopCount = 1;
					updateRate = 0.0f;
				}
				break;
			default:
				while (updateRate < 0.0f) {
					++loopCount;
					updateRate += 1.0f;
				}
				break;
			}
		}
	}

	void Board::iztUpdate() {
		for (auto p = mPlantList.begin(); p != mPlantList.end(); ++p)p->iztUpdate();
		for (auto p = mZombieList.begin(); p != mZombieList.end(); ++p)p->iztUpdate();
		for (auto p = mBulletList.begin(); p != mBulletList.end(); ++p)p->Update();
	}


	void SexyAppBase::UpdateAppOnce(int millisecond) {
		int temp = mFrameTime;
		mFrameTime = millisecond;
		bool a = false;
		while (!a)UpdateAppStep(&a);
		mFrameTime = temp;
	}

	void GameApp::UpdateAppOnce(int millisecond) {
		int temp = mFrameTime;
		mFrameTime = millisecond;
		bool a = false;
		while (!a)UpdateAppStep(&a);
		mFrameTime = temp;
	}

	void WidgetManager::InitModalFlags(ModalFlags* theModalFlags) {
		theModalFlags->mIsOver = !mBaseModalWidget;
		theModalFlags->mOverFlags = GetWidgetFlags();
		theModalFlags->mUnderFlags = GetModFlags(theModalFlags->mOverFlags, mBelowModalFlagsMod);
	}

	int WidgetManager::GetWidgetFlags() {
		return mHasFocus ? mWidgetFlags : GetModFlags(mWidgetFlags, mLostFocusFlagsMod);
	}

	bool WidgetManager::UpdateFrame() {
		ModalFlags aModalFlags;
		InitModalFlags(&aModalFlags);
		mUpdateCnt++;
		mLastWMUpdateCount = mUpdateCnt;
		UpdateAll(&aModalFlags);
		return mDirty;
	};

	AutoModalFlags::AutoModalFlags(ModalFlags* theModalFlags, const FlagsMod& theFlagMod) {
		mModalFlags = theModalFlags;
		mOldOverFlags = theModalFlags->mOverFlags;
		mOldUnderFlags = theModalFlags->mUnderFlags;
		theModalFlags->ModFlags(theFlagMod);
	}

	void ModalFlags::ModFlags(const FlagsMod& theFlagsMod) {
		Pvz::ModFlags(mOverFlags, theFlagsMod);
		Pvz::ModFlags(mUnderFlags, theFlagsMod);
	}

	int ModalFlags::GetFlags() {
		return mIsOver ? mOverFlags : mUnderFlags;
	}

	int Buffer::ReadNumBits(int theBits, bool isSigned) {
		int aByteLength = (int)mData.size();
		int theNum = 0;
		bool bset = false;
		for (int aBitNum = 0; aBitNum < theBits; aBitNum++) {
			int aBytePos = mReadBitPos / 8;
			if (aBytePos >= aByteLength)break;
			if (bset = (mData[aBytePos] & (1 << (mReadBitPos % 8))) != 0)theNum |= 1 << aBitNum;
			mReadBitPos++;
		}
		if ((isSigned) && (bset))for (int aBitNum = theBits; aBitNum < 32; aBitNum++)theNum |= 1 << aBitNum;
		return theNum;
	}

	bool SexyAppBase::PrepareDemoCommand() {
		if (mDemoNeedsCommand) {
			mDemoCmdBitPos = mDemoBuffer.mReadBitPos;
			mLastDemoUpdateCnt += mDemoBuffer.ReadNumBits(4, false);
			mDemoIsShortCmd = mDemoBuffer.ReadNumBits(1, false) == 1;
			if (mDemoIsShortCmd)mDemoCmdNum = mDemoBuffer.ReadNumBits(1, false);
			else mDemoCmdNum = mDemoBuffer.ReadNumBits(5, false);
			mDemoNeedsCommand = false;
			mDemoCmdOrder++;
		}
		return mUpdateCount == mLastDemoUpdateCnt;
	}

	std_string RemoveTrailingSlash(const std_string& theDirectory) {
		int aLen = theDirectory.length();

		if ((aLen > 0) && ((theDirectory[aLen - 1] == u8'\\') || (theDirectory[aLen - 1] == u8'/')))return theDirectory.substr(0, aLen - 1);
		else
			return theDirectory;
	}

	bool SexyAppBase::RegistryWrite(const std_string& theValueName, ulong theType, const uchar* theValue, ulong theLength) {
		if (mRegKey.length() == 0)return false;
		if (mPlayingDemoBuffer) {
			if (mManualShutdown)return true;
			PrepareDemoCommand();
			mDemoNeedsCommand = true;
			return mDemoBuffer.ReadNumBits(1, false) != 0;
		}
		HKEY aGameKey;
		std_string aKeyName = RemoveTrailingSlash(u8"SOFTWARE\\" + mRegKey);
		std_string aValueName;
		int aSlashPos = (int)theValueName.rfind(u8'\\');
		if (aSlashPos != -1) {
			aKeyName += u8"\\" + theValueName.substr(0, aSlashPos);
			aValueName = theValueName.substr(aSlashPos + 1);
		} else {
			aValueName = theValueName;
		}
		int aResult = ::RegOpenKeyExA(HKEY_CURRENT_USER, aKeyName.data(), 0, KEY_WRITE, &aGameKey);
		if (aResult != ERROR_SUCCESS) {
			ulong aDisp;
			aResult = ::RegCreateKeyExA(HKEY_CURRENT_USER, aKeyName.data(), 0, (LPSTR)u8"Key", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &aGameKey, &aDisp);
		}
		if (aResult != ERROR_SUCCESS) {
			if (mRecordingDemoBuffer) {
				WriteDemoTimingBlock();
				mDemoBuffer.WriteNumBits(0, 1);
				mDemoBuffer.WriteNumBits(DEMO_REGISTRY_WRITE, 5);
				mDemoBuffer.WriteNumBits(0, 1);
			}
			return false;
		}
		::RegSetValueExA(aGameKey, aValueName.data(), 0, theType, theValue, theLength);
		::RegCloseKey(aGameKey);
		if (mRecordingDemoBuffer) {
			WriteDemoTimingBlock();
			mDemoBuffer.WriteNumBits(0, 1);
			mDemoBuffer.WriteNumBits(DEMO_REGISTRY_WRITE, 5);
			mDemoBuffer.WriteNumBits(1, 1);
		}
		return true;
	}

	bool SexyAppBase::RegistryWriteInteger(const std_string& theValueName, int theValue) {
		return RegistryWrite(theValueName, REG_DWORD, (UCHAR*)&theValue, sizeof(int));
	}

	bool SexyAppBase::RegistryWriteBoolean(const std_string& theValueName, bool theValue) {
		int aValue = theValue ? 1 : 0;
		return RegistryWrite(theValueName, REG_DWORD, (UCHAR*)&aValue, sizeof(int));
	}

	void Pvz::CloseJPEG2000() {
		if (gJ2KCodec) {
			::FreeLibrary(gJ2KCodec);
			gJ2KCodec = nullptr;
		}
	}

	void SexyAppBase::ClearUpdateBacklog(bool relaxForASecond) {
		mLastTimeCheck = ::timeGetTime();
		mUpdateFTimeAcc = 0;
		if (relaxForASecond)mRelaxUpdateBacklogCount = 1000;
	}

	MTRand::MTRand(const std_string& theSerialData) {
		SRand(theSerialData);
		mti = MTRAND_N + 1;
	}

	MTRand::MTRand(unsigned long seed) {
		SRand(seed);
	}

	MTRand::MTRand() {
		SRand(4357);
	}

	void MTRand::SetRandAllowed(bool allowed) {
		if (allowed)--gRandAllowed;
		else ++gRandAllowed;
	}

	void MTRand::SRand(const std_string& theSerialData) {
		if (theSerialData.size() == MTRAND_N * 4)memcpy(mt, theSerialData.data(), MTRAND_N * 4);
		else SRand(4357);
	}

	void MTRand::SRand(unsigned long seed) {
		if (seed == 0)seed = 4357;
		mt[0] = seed & 0xfffffffful;
		for (mti = 1; mti < MTRAND_N; mti++) {
			mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
			mt[mti] &= 0xfffffffful;
		}
	}

	unsigned long MTRand::Next() {
		return NextNoAssert();
	}

	unsigned long MTRand::NextNoAssert() {
		unsigned long y;
		static unsigned long mag01[2] = { 0x0u,MATRIX_A };
		if (mti >= MTRAND_N) {
			int kk;
			for (kk = 0; kk < MTRAND_N - MTRAND_M; kk++) {
				y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
				mt[kk] = mt[kk + MTRAND_M] ^ (y >> 1) ^ mag01[y & 0x1ul];
			}
			for (; kk < MTRAND_N - 1; kk++) {
				y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
				mt[kk] = mt[kk + (MTRAND_M - MTRAND_N)] ^ (y >> 1) ^ mag01[y & 0x1ul];
			}
			y = (mt[MTRAND_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
			mt[MTRAND_N - 1] = mt[MTRAND_M - 1] ^ (y >> 1) ^ mag01[y & 0x1ul];
			mti = 0;
		}
		y = mt[mti++];
		y ^= TEMPERING_SHIFT_U(y);
		y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
		y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
		y ^= TEMPERING_SHIFT_L(y);
		y &= 0x7FFFFFFFul;
		return y;
	}

	unsigned long MTRand::NextNoAssert(unsigned long range) {
		return NextNoAssert() % range;
	}

	unsigned long MTRand::Next(unsigned long range) {
		return NextNoAssert(range);
	}

	float MTRand::NextNoAssert(float range) {
		return(float)((double)NextNoAssert() / (double)0x7FFFFFFFul * range);
	}

	float MTRand::Next(float range) {
		return NextNoAssert(range);
	}

	std_string MTRand::Serialize() {
		std_string aString;
		aString.resize(MTRAND_N * 4);
		memcpy((char*)aString.data(), mt, MTRAND_N * 4);
		return aString;
	}

	void SexyAppBase::ProcessSafeDeleteList() {
		MTAutoDisallowRand aDisallowRand;
		std_list<WidgetSafeDeleteInfo>::iterator anItr = mSafeDeleteList.begin();
		while (anItr != mSafeDeleteList.end()) {
			WidgetSafeDeleteInfo* aWidgetSafeDeleteInfo = &(*anItr);
			if (mUpdateAppDepth <= aWidgetSafeDeleteInfo->mUpdateAppDepth) {
				delete aWidgetSafeDeleteInfo->mWidget;
				anItr = mSafeDeleteList.erase(anItr);
			} else ++anItr;
		}
	}

	void SexyAppBase::UpdateFTimeAcc() {
		DWORD aCurTime = ::timeGetTime();
		if (mLastTimeCheck != 0) {
			int aDeltaTime = aCurTime - mLastTimeCheck;
			mUpdateFTimeAcc = min(mUpdateFTimeAcc + aDeltaTime, 200);
			if (mRelaxUpdateBacklogCount > 0)mRelaxUpdateBacklogCount = max(mRelaxUpdateBacklogCount - aDeltaTime, 0);
		}
		mLastTimeCheck = aCurTime;
	}

	bool SexyAppBase::Is3DAccelerated() {
		return mDDInterface->mIs3D;
	}

	DDImage* DDInterface::GetScreenImage() {
		return mScreenImage;
	}

	bool DDImage::Check3D(Image* theImage) {
		DDImage* p = ImageToDDImage(theImage);
		return p && Check3D(p);
	}

	bool DDImage::Check3D(DDImage* theImage) {
		return theImage->mDDInterface->mIs3D && theImage->mSurface == theImage->mDDInterface->mDrawSurface;
	}

	int Image::GetWidth() {
		return mWidth;
	}

	int	Image::GetHeight() {
		return mHeight;
	}

	void Graphics::CopyStateFrom(const Graphics* theState) {
		mDestImage = theState->mDestImage;
		mTransX = theState->mTransX;
		mTransY = theState->mTransY;
		mClipRect = theState->mClipRect;
		mFont = theState->mFont;
		mColor = theState->mColor;
		mDrawMode = theState->mDrawMode;
		mColorizeImages = theState->mColorizeImages;
		mFastStretch = theState->mFastStretch;
		mWriteColoredString = theState->mWriteColoredString;
		mLinearBlend = theState->mLinearBlend;
		mScaleX = theState->mScaleX;
		mScaleY = theState->mScaleY;
		mScaleOrigX = theState->mScaleOrigX;
		mScaleOrigY = theState->mScaleOrigY;
		mIs3D = theState->mIs3D;
	}

	void Graphics::Translate(int theTransX, int theTransY) {
		mTransX += theTransX;
		mTransY += theTransY;
	}

	void Graphics::SetFastStretch(bool fastStretch) {
		mFastStretch = fastStretch;
	}

	void Graphics::SetLinearBlend(bool linear) {
		mLinearBlend = linear;
	}

	mState Graphics::mmState() {
		return mState(*(mState*)((DWORD)this + 4));
	}

	void Graphics::PushState() {
		mStateStack.push_back(mmState());
	}

	void Graphics::PopState() {
		if (mStateStack.size() > 0) {
			memcpy(&mStateStack.back(), (LPVOID)((DWORD)this + 4), sizeof(mState));
			mStateStack.pop_back();
		}
	}

	void Graphics::ClipRect(int theX, int theY, int theWidth, int theHeight) {
		mClipRect = mClipRect.Intersection(Rect(theX + (int)mTransX, theY + (int)mTransY, theWidth, theHeight));
	}

	bool WidgetManager::DrawScreen() {
		ModalFlags aModalFlags;
		InitModalFlags(&aModalFlags);
		bool drewStuff = false;
		int aDirtyCount = 0;
		bool hasTransients = false;
		bool hasDirtyTransients = false;
		std_list<Widget*>::iterator anItr = mWidgets.begin();
		while (anItr != mWidgets.end()) {
			Widget* aWidget = *anItr;
			if (aWidget->mDirty)++aDirtyCount;
			++anItr;
		}
		mMinDeferredOverlayPriority = 0x7FFFFFFFul;
		mDeferredOverlayWidgets.clear();
		mCurG = Graphics::New(mImage);
		DDImage* aDDImage = ImageToDDImage(mImage);
		bool surfaceLocked = false;
		if (aDDImage)surfaceLocked = aDDImage->LockSurface();
		if (aDirtyCount > 0) {
			Graphics* g = Graphics::New(*mCurG);
			g->Translate(-mMouseDestRect.mX, -mMouseDestRect.mY);
			bool is3D = mApp->Is3DAccelerated();
			std_list<Widget*>::iterator anItr = mWidgets.begin();
			while (anItr != mWidgets.end()) {
				Widget* aWidget = *anItr;
				if (aWidget == mWidgetManager->mBaseModalWidget)aModalFlags.mIsOver = true;
				if ((aWidget->mDirty) && (aWidget->mVisible)) {
					Graphics* aClipG = Graphics::New(*g);
					aClipG->SetFastStretch(!is3D);
					aClipG->SetLinearBlend(is3D);
					aClipG->Translate(aWidget->mX, aWidget->mY);
					aWidget->DrawAll(&aModalFlags, aClipG);
					aDirtyCount++;
					drewStuff = true;
					aWidget->mDirty = false;
					aClipG->Kill();
				}
				++anItr;
			}
			g->Kill();
		}
		FlushDeferredOverlayWidgets(0x7FFFFFFFul);
		if (aDDImage && surfaceLocked)aDDImage->UnlockSurface();
		if (mCurG)mCurG->Kill();
		mCurG = nullptr;
		return drewStuff;
	}

	void WidgetManager::RemapMouse(int& theX, int& theY) {
		theX = (theX - mMouseSourceRect.mX) * mMouseDestRect.mW / mMouseSourceRect.mW + mMouseDestRect.mX;
		theY = (theY - mMouseSourceRect.mY) * mMouseDestRect.mH / mMouseSourceRect.mH + mMouseDestRect.mY;
	}

	bool WidgetManager::MouseMove(int x, int y) {
		mLastInputUpdateCnt = mUpdateCnt;
		if (mDownButtons)return MouseDrag(x, y);
		mMouseIn = true;
		MousePosition(x, y);
		return true;
	}

	Widget* WidgetContainer::GetWidgetAtHelper(int x, int y, int theFlags, bool* found, int* theWidgetX, int* theWidgetY) {
		bool belowModal = false;
		ModFlags(theFlags, mWidgetFlagsMod);
		std_list<Widget*>::reverse_iterator anItr = mWidgets.rbegin();
		while (anItr != mWidgets.rend()) {
			Widget* aWidget = *anItr;
			int aCurFlags = theFlags;
			ModFlags(aCurFlags, aWidget->mWidgetFlagsMod);
			if (belowModal)ModFlags(aCurFlags, mWidgetManager->mBelowModalFlagsMod);
			if (aCurFlags & WIDGETFLAGS_ALLOW_MOUSE) {
				if (aWidget->mVisible) {
					bool childFound;
					Widget* aCheckWidget = aWidget->GetWidgetAtHelper(x - aWidget->mX, y - aWidget->mY, aCurFlags, &childFound, theWidgetX, theWidgetY);
					if ((aCheckWidget) || (childFound)) {
						*found = true;
						return aCheckWidget;
					}
					if ((aWidget->mMouseVisible) && (aWidget->GetInsetRect().Contains(x, y))) {
						*found = true;
						if (aWidget->IsPointVisible(x - aWidget->mX, y - aWidget->mY)) {
							if (theWidgetX)*theWidgetX = x - aWidget->mX;
							if (theWidgetY)*theWidgetY = y - aWidget->mY;
							return aWidget;
						}
					}
				}
			}
			belowModal |= (aWidget == mWidgetManager->mBaseModalWidget);
			++anItr;
		}
		*found = false;
		return nullptr;
	}

	Widget* WidgetManager::GetAnyWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY) {
		bool found;
		return GetWidgetAtHelper(x, y, GetWidgetFlags(), &found, theWidgetX, theWidgetY);
	}

	Widget* WidgetManager::GetWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY) {
		Widget* aWidget = GetAnyWidgetAt(x, y, theWidgetX, theWidgetY);
		if ((aWidget) && (aWidget->mDisabled))aWidget = nullptr;
		return aWidget;
	}

	bool DDInterface::SetCursorImage(Image* theImage) {
		AutoCrit anAutoCrit(mCritSect);
		if (mCursorImage != theImage) {
			mCursorImage = theImage;
			return true;
		} else return false;
	}

	void SexyAppBase::SetCursor(int theCursorNum) {
		mCursorNum = theCursorNum;
		EnforceCursor();
	}

	void WidgetManager::MouseLeave(Widget* theWidget) {
		theWidget->mIsOver = false;
		theWidget->MouseLeave();
		if (theWidget->mDoFinger)theWidget->ShowFinger(false);
	}

	void WidgetManager::MouseEnter(Widget* theWidget) {
		theWidget->mIsOver = true;
		theWidget->MouseEnter();
		if (theWidget->mDoFinger)theWidget->ShowFinger(true);
	}

	void WidgetManager::MousePosition(int x, int y) {
		int aLastMouseX = mLastMouseX;
		int aLastMouseY = mLastMouseY;
		mLastMouseX = x;
		mLastMouseY = y;
		int aWidgetX;
		int aWidgetY;
		Widget* aWidget = GetWidgetAt(x, y, &aWidgetX, &aWidgetY);
		if (aWidget != mOverWidget) {
			Widget* aLastOverWidget = mOverWidget;
			mOverWidget = nullptr;
			if (aLastOverWidget)MouseLeave(aLastOverWidget);
			mOverWidget = aWidget;
			if (aWidget) {
				MouseEnter(aWidget);
				aWidget->MouseMove(aWidgetX, aWidgetY);
			}
		} else if ((aLastMouseX != x) || (aLastMouseY != y)) {
			if (aWidget)aWidget->MouseMove(aWidgetX, aWidgetY);
		}
	}

	bool WidgetManager::MouseDrag(int x, int y) {
		mLastInputUpdateCnt = mUpdateCnt;
		mMouseIn = true;
		mLastMouseX = x;
		mLastMouseY = y;
		if ((mOverWidget) && (mOverWidget != mLastDownWidget)) {
			Widget* anOverWidget = mOverWidget;
			mOverWidget = nullptr;
			MouseLeave(anOverWidget);
		}
		if (mLastDownWidget) {
			Point anAbsPos = mLastDownWidget->GetAbsPos();
			int aWidgetX = x - anAbsPos.mX;
			int aWidgetY = y - anAbsPos.mY;
			mLastDownWidget->MouseDrag(aWidgetX, aWidgetY);
			Widget* aWidgetOver = GetWidgetAt(x, y, nullptr, nullptr);
			if ((aWidgetOver == mLastDownWidget) && (aWidgetOver)) {
				if (mOverWidget == nullptr) {
					mOverWidget = mLastDownWidget;
					MouseEnter(mOverWidget);
				}
			} else {
				if (mOverWidget) {
					Widget* anOverWidget = mOverWidget;
					mOverWidget = nullptr;
					MouseLeave(anOverWidget);
				}
			}
		}
		return true;
	}

	void WidgetManager::RemovePopupCommandWidget() {
		if (mPopupCommandWidget) {
			Widget* aWidget = mPopupCommandWidget;
			mPopupCommandWidget = nullptr;
			RemoveWidget(aWidget);
		}
	}

	void WidgetManager::DoMouseUps(Widget* theWidget, ulong theDownCode) {
		int aClickCountTable[3] = { 1,-1,3 };
		for (int i = 0; i < 3; i++) {
			if ((theDownCode & (1 << i)) != 0) {
				theWidget->mIsDown = false;
				theWidget->MouseUp(mLastMouseX - theWidget->mX, mLastMouseY - theWidget->mY, aClickCountTable[i]);
			}
		}
	}

	void Widget::WidgetRemovedHelper() {
		if (mWidgetManager == nullptr)return;
		for (auto&& aWidgetItr : mWidgets) aWidgetItr->WidgetRemovedHelper();
		mWidgetManager->DisableWidget(this);
		std_list<PreModalInfo>::iterator anItr = mWidgetManager->mPreModalInfoList.begin();
		while (anItr != mWidgetManager->mPreModalInfoList.end()) {
			PreModalInfo* aPreModalInfo = &(*anItr);
			if (aPreModalInfo->mPrevBaseModalWidget == this)aPreModalInfo->mPrevBaseModalWidget = nullptr;
			if (aPreModalInfo->mPrevFocusWidget == this)aPreModalInfo->mPrevFocusWidget = nullptr;
			++anItr;
		}
		RemovedFromManager(mWidgetManager);
		MarkDirtyFull(this);
		mWidgetManager = nullptr;
	}

	bool WidgetManager::MouseDown(int x, int y, int theClickCount) {
		mLastInputUpdateCnt = mUpdateCnt;
		if (theClickCount < 0)mActualDownButtons |= 0x02u;
		else if (theClickCount == 3)mActualDownButtons |= 0x04u;
		else mActualDownButtons |= 0x01u;
		MousePosition(x, y);
		if ((mPopupCommandWidget) && (!mPopupCommandWidget->Contains(x, y)))RemovePopupCommandWidget();
		int aWidgetX;
		int aWidgetY;
		Widget* aWidget = GetWidgetAt(x, y, &aWidgetX, &aWidgetY);
		if (mLastDownWidget)aWidget = mLastDownWidget;
		if (theClickCount < 0) {
			mLastDownButtonId = -1;
			mDownButtons |= 0x02u;
		} else if (theClickCount == 3) {
			mLastDownButtonId = 2;
			mDownButtons |= 0x04u;
		} else {
			mLastDownButtonId = 1;
			mDownButtons |= 0x01u;
		}
		mLastDownWidget = aWidget;
		if (aWidget) {
			if (aWidget->WantsFocus())SetFocus(aWidget);
			aWidget->mIsDown = true;
			aWidget->MouseDown(aWidgetX, aWidgetY, theClickCount);
		}
		return true;
	}

	bool WidgetManager::MouseUp(int x, int y, int theClickCount) {
		mLastInputUpdateCnt = mUpdateCnt;
		int aMask;
		if (theClickCount < 0)aMask = 0x02u;
		else if (theClickCount == 3)aMask = 0x04u;
		else aMask = 0x01u;
		mActualDownButtons &= ~aMask;
		if ((mLastDownWidget) && ((mDownButtons & aMask) != 0)) {
			Widget* aLastDownWidget = mLastDownWidget;
			mDownButtons &= ~aMask;
			if (mDownButtons == 0)mLastDownWidget = nullptr;
			aLastDownWidget->mIsDown = false;
			aLastDownWidget->MouseUp(x - aLastDownWidget->mX, y - aLastDownWidget->mY, theClickCount);
		} else mDownButtons &= ~aMask;
		MousePosition(x, y);
		return true;
	}

	void WidgetManager::MouseWheel(int theDelta) {
		mLastInputUpdateCnt = mUpdateCnt;
		if (mFocusWidget)mFocusWidget->MouseWheel(theDelta);
	}

	void SexyAppBase::ClearKeysDown() {
		if (mWidgetManager)for (int aKeyNum = 0; aKeyNum < 0xFFu; aKeyNum++)mWidgetManager->mKeyDown[aKeyNum] = false;
		mCtrlDown = false;
		mAltDown = false;
	}

	bool WidgetManager::KeyDown(KeyCode key) {
		mLastInputUpdateCnt = mUpdateCnt;
		mKeyDown[(int)key] = true;
		if (mFocusWidget)mFocusWidget->KeyDown(key);
		return true;
	}

	bool WidgetManager::KeyUp(KeyCode key) {
		mLastInputUpdateCnt = mUpdateCnt;
		mKeyDown[(int)key] = false;
		if ((key == KeyCode::TAB) && (mKeyDown[(int)KeyCode::CONTROL]))return true;
		if (mFocusWidget)mFocusWidget->KeyUp(key);
		return true;
	}

	bool WidgetManager::KeyChar(char theChar) {
		mLastInputUpdateCnt = mUpdateCnt;
		if (theChar == (int)KeyCode::TAB) {
			if (mKeyDown[(int)KeyCode::CONTROL]) {
				if (mDefaultTab)mDefaultTab->KeyChar(theChar);
				return true;
			}
		}
		if (mFocusWidget)mFocusWidget->KeyChar(theChar);
		return true;
	}

	bool WidgetManager::MouseExit(int x, int y) {
		mLastInputUpdateCnt = mUpdateCnt;
		mMouseIn = false;
		if (mOverWidget) {
			MouseLeave(mOverWidget);
			mOverWidget = nullptr;
		}
		return true;
	}

	extern void WndTrans();
	bool SexyAppBase::ProcessDeferredMessages(bool singleMessage) {
		while (mDeferredMessages.size() > 0) {
			MSG aMsg = mDeferredMessages.front();
			mDeferredMessages.pop_front();
			UINT uMsg = aMsg.message;
			LPARAM lParam = aMsg.lParam;
			WPARAM wParam = aMsg.wParam;
			HWND hWnd = aMsg.hwnd;
			if (!mPlayingDemoBuffer) {

				switch (uMsg) {
				case WM_CREATE:
					break;
				case WM_ACTIVATEAPP:
					if ((hWnd == mHWnd) && (!gInAssert) && (!mSEHOccured) && (!mShutdown)) {
						RehupFocus();
						if ((mActive) && (!mIsWindowed))mWidgetManager->MarkAllDirty();
						if ((mIsOpeningURL) && (!mActive))URLOpenSucceeded(mOpeningURL);
					}
					break;
				case WM_MOVE:
					if ((hWnd == mHWnd) && (mIsWindowed)) {
						WINDOWPLACEMENT aWindowPlacment{};
						aWindowPlacment.length = sizeof(aWindowPlacment);
						::GetWindowPlacement(hWnd, &aWindowPlacment);
						if ((aWindowPlacment.showCmd == SW_SHOW) || (aWindowPlacment.showCmd == SW_SHOWNORMAL)) {
							mPreferredX = aWindowPlacment.rcNormalPosition.left;
							mPreferredY = aWindowPlacment.rcNormalPosition.top;
						}
					}
					break;
				case WM_SIZE:
				{
					bool isMinimized = (wParam == SIZE_MINIMIZED);
					if ((hWnd == mHWnd) && (!mShutdown) && (isMinimized != mMinimized)) {
						mMinimized = isMinimized;
						if (mMinimized) {
							if (mMuteOnLostFocus)Mute(true);
						} else {
							if (mMuteOnLostFocus)Unmute(true);
							mWidgetManager->MarkAllDirty();
						}
					}
					RehupFocus();
					if (wParam == SIZE_MAXIMIZED)SwitchScreenMode(false);
				}
				break;
				case WM_SYSCOLORCHANGE:
				case WM_DISPLAYCHANGE:
					mWidgetManager->SysColorChangedAll();
					mWidgetManager->MarkAllDirty();
					break;
				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
					mLastUserInputTick = mLastTimerTime;
#ifndef CVP
					if (!Pvz::gGameApp->mLoadingPage && Ui::WidgetManager::KeyDown((KeyCode)wParam)) break;
#endif
					if (wParam == VK_RETURN && uMsg == WM_SYSKEYDOWN && !mForceFullscreen && !mForceWindowed) {
						SwitchScreenMode(!mIsWindowed);
						ClearKeysDown();
						break;
					} else if ((wParam == u8'D') && (mWidgetManager) && (mWidgetManager->mKeyDown[(int)KeyCode::CONTROL]) && (mWidgetManager->mKeyDown[(int)KeyCode::MENU])) {
						PlaySoundA(u8"c:\\windows\\media\\Windows XP Menu Command.wav", nullptr, SND_ASYNC);
						mDebugKeysEnabled = !mDebugKeysEnabled;
					} else if (mDebugKeysEnabled && DebugKeyDown(wParam))break;
					else mWidgetManager->KeyDown((KeyCode)wParam);
					break;
				case WM_KEYUP:
				case WM_SYSKEYUP:
					mLastUserInputTick = mLastTimerTime;
#ifndef CVP
					if (!Pvz::gGameApp->mLoadingPage && Ui::WidgetManager::KeyUp((KeyCode)wParam)) break;
#endif
					mWidgetManager->KeyUp((KeyCode)wParam);
					break;
				case WM_CHAR:
					mLastUserInputTick = mLastTimerTime;
					if (!isprint(wParam)) break;
#ifndef CVP
					if (!Pvz::gGameApp->mLoadingPage && Ui::WidgetManager::KeyChar((char)wParam)) break;
#endif
					mWidgetManager->KeyChar((char)wParam);
					break;
				case WM_TIMER:
					if ((!gInAssert) && (!mSEHOccured) && (mRunning)) {
						DWORD aTimeNow = (DWORD)GetTickCount64();
						if (aTimeNow - mLastTimerTime > 500)mLastBigDelayTime = aTimeNow;
						mLastTimerTime = aTimeNow;
						if ((mIsOpeningURL) && (aTimeNow - mLastBigDelayTime > 5000)) {
							if ((aTimeNow - mOpeningURLTime > 8000) && (!mActive)) {
								URLOpenSucceeded(mOpeningURL);
							} else if ((aTimeNow - mOpeningURLTime > 12000) && (mActive)) {
								URLOpenFailed(mOpeningURL);
							}
						}
						POINT aULCorner = { 0,0 };
						::ClientToScreen(hWnd, &aULCorner);
						POINT aBRCorner = { mDDInterface->mDisplayWidth,mDDInterface->mDisplayHeight };
						::ClientToScreen(hWnd, &aBRCorner);
						POINT aPoint;
						::GetCursorPos(&aPoint);
						HWND aWindow = ::WindowFromPoint(aPoint);
						bool isMouseIn = (aWindow == hWnd) && (aPoint.x >= aULCorner.x) && (aPoint.y >= aULCorner.y) && (aPoint.x < aBRCorner.x) && (aPoint.y < aBRCorner.y);
						if (mMouseIn != isMouseIn) {
							if ((mRecordingDemoBuffer) && (!mShutdown)) {
								WriteDemoTimingBlock();
								mDemoBuffer.WriteNumBits(0, 1);
								if (isMouseIn)mDemoBuffer.WriteNumBits(DEMO_MOUSE_ENTER, 5);
								else mDemoBuffer.WriteNumBits(DEMO_MOUSE_EXIT, 5);
							}
							if (!isMouseIn) {
								int x = aPoint.x - aULCorner.x;
								int y = aPoint.y - aULCorner.y;
								mWidgetManager->RemapMouse(x, y);
								mWidgetManager->MouseExit(x, y);
							}
							mMouseIn = isMouseIn;
							EnforceCursor();
						}
					}
					break;
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_LBUTTONDBLCLK:
				case WM_RBUTTONDBLCLK:
				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
				case WM_MBUTTONUP:
				case WM_MOUSEMOVE:
					if ((!gInAssert) && (!mSEHOccured)) {
						int x = (short)LOWORD(lParam);
						int y = (short)HIWORD(lParam);
						mWidgetManager->RemapMouse(x, y);
						mLastUserInputTick = mLastTimerTime;
#ifndef CVP
						if (uMsg == WM_LBUTTONDOWN && Pvz::MouseHook()(x, y, Cvp::MouseCode::LEFT))break;
						if (uMsg == WM_RBUTTONDOWN && Pvz::MouseHook()(x, y, Cvp::MouseCode::RIGHT))break;
						if (uMsg == WM_LBUTTONDBLCLK && Pvz::MouseHook()(x, y, Cvp::MouseCode::LEFT))break;
						if (uMsg == WM_RBUTTONDBLCLK && Pvz::MouseHook()(x, y, Cvp::MouseCode::RIGHT))break;
						if (uMsg == WM_MBUTTONDOWN && Pvz::MouseHook()(x, y, Cvp::MouseCode::MID))break;
						bool intercept = !(mWidgetManager->mActualDownButtons & 0x7u) && !Pvz::gGameApp->mLoadingPage && Ui::WidgetManager::MouseMove(x, y);
						if (intercept) {
							mWidgetManager->MouseMove(0x3ffffffful, 0x3ffffffful);
							switch (uMsg) {
							case WM_LBUTTONDOWN:
								::SetCapture(hWnd);
								Ui::WidgetManager::MouseDown(x, y, 1);
								break;
							case WM_RBUTTONDOWN:
								::SetCapture(hWnd);
								Ui::WidgetManager::MouseDown(x, y, -1);
								break;
							case WM_MBUTTONDOWN:
								::SetCapture(hWnd);
								Ui::WidgetManager::MouseDown(x, y, 3);
								break;
							case WM_LBUTTONDBLCLK:
								::SetCapture(hWnd);
								Ui::WidgetManager::MouseDown(x, y, 1);
								break;
							case WM_RBUTTONDBLCLK:
								::SetCapture(hWnd);
								Ui::WidgetManager::MouseDown(x, y, -1);
								break;
							case WM_LBUTTONUP:
								Ui::WidgetManager::MouseUp(x, y, 1);
								break;
							case WM_RBUTTONUP:
								Ui::WidgetManager::MouseUp(x, y, -1);
								break;
							case WM_MBUTTONUP:
								Ui::WidgetManager::MouseUp(x, y, 3);
								break;
							}
							break;
						}
						if (uMsg != WM_MOUSEMOVE)Ui::WidgetManager::FocusWidget(nullptr);
#endif
						mWidgetManager->MouseMove(x, y);
						if (!mMouseIn) {
							mMouseIn = true;
							EnforceCursor();
						}
						switch (uMsg) {
						case WM_LBUTTONDOWN:
							::SetCapture(hWnd);
							mWidgetManager->MouseDown(x, y, 1);
							break;
						case WM_RBUTTONDOWN:
							::SetCapture(hWnd);
							mWidgetManager->MouseDown(x, y, -1);
							break;
						case WM_MBUTTONDOWN:
							::SetCapture(hWnd);
							mWidgetManager->MouseDown(x, y, 3);
							break;
						case WM_LBUTTONDBLCLK:
							::SetCapture(hWnd);
							mWidgetManager->MouseDown(x, y, 2);
							break;
						case WM_RBUTTONDBLCLK:
							::SetCapture(hWnd);
							mWidgetManager->MouseDown(x, y, -2);
							break;
						case WM_LBUTTONUP:
							if ((mWidgetManager->mDownButtons & ~1) == 0)::ReleaseCapture();
							mWidgetManager->MouseUp(x, y, 1);
							break;
						case WM_RBUTTONUP:
							if ((mWidgetManager->mDownButtons & ~2) == 0)::ReleaseCapture();
							mWidgetManager->MouseUp(x, y, -1);
							break;
						case WM_MBUTTONUP:
							if ((mWidgetManager->mDownButtons & ~4) == 0)::ReleaseCapture();
							mWidgetManager->MouseUp(x, y, 3);
							break;
						}
					}
					break;
				case WM_MOUSEWHEEL:
					char aZDelta = ((short)HIWORD(wParam)) / 120;
#ifndef CVP
					if (!Pvz::gGameApp->mLoadingPage && Ui::WidgetManager::MouseWheel(aZDelta)) break;
#endif
					mWidgetManager->MouseWheel(aZDelta);
					break;
				}
			}
			if (uMsg == WM_CLOSE) {
				if ((hWnd == mHWnd) || (hWnd == mInvisHWnd)) {
					mManualShutdown = true;
					Shutdown();
				}
			}
			if (singleMessage)break;
		}
		return(mDeferredMessages.size() > 0);
	}

	int Board::GetNoFogColNum() {
		GameApp::Level::Type level = mApp->level;
		if (level == GameApp::Level::Type::AIR_RAID)return 6;
		if (level != GameApp::Level::Type::ADVENTURE)return 5;
		int rank = adventureLevelRank;
		if (rank == 31)return 6;
		if (rank <= 36)return 5;
		if (rank <= 40)return 4;
		return rank;
	}

	void Board::UpdateMain() {
		UpdateMainMain();
		if ((mApp->isStorm()) || (mApp->level == GameApp::Level::Type::INVISIBLE) || (yard != Yard::Type::FOG) || (fogCountdown <= 0));
		else {
			float fogX = 1065 - 80 * float(GetNoFogColNum());
			if (mApp->gameState == GameApp::State::SELECT_CARD) {
				float temp = (float)fogCountdown / 200;
				temp = limit(0.0f, temp, 1.0f);
				temp = temp * temp;
				fogOffset = cut(1.0f, temp, fogX);
			} else {
				if (fogCountdown < 2000) {
					fogOffset = getCurveValue(3, 2000, 0, fogX, 0.0f, fogCountdown);
				} else if (fogOffset < fogX) {
					fogOffset = getCurveValue(1, -5, (int)fogX, 0.0f, fogX, (int)(fogOffset * 1.1f));
				}
			}
		}
		if (!mApp->isBattle())return;
		++timeBattle;
		UpdateSunDrop();
		UpdateZombieSpawn();
		UpdateRowIce();
		if (poolFreezeCountdown > 0 && --poolFreezeCountdown == 0 && (*mApp)[particleSystem]) {
			(*mApp)[particleSystem]->freezed = false;
		}
		if (fogCountdown > 0)--fogCountdown;
		//AdviceLogic
		//0x415B97ul
		/*do{
					if(timeBattle != 1)break;
				} while(false);
		 */
		UpdateProcessBar();
	}

	Plant* Board::GetGridPlant(int col, int row, Plant::Type type) {
		for (auto&& p : mPlantList)if (p.isInYard() && p.col == col && p.row == row && p.type == type)return &p;
		return nullptr;
	}

	Plant* Board::GetGridUmbrella(int col, int row) {
		for (auto&& p : mPlantList)if (p.isInYard() && p.col >= col - 1 && p.row >= row - 1 && p.col <= col + 1 && p.row <= row + 1 && p.type == Plant::Type::UMBRELLA_LEAF)return &p;
		return nullptr;
	}

	void Board::UpdateMainMain() {
		for (auto&& p = mPlantList.begin(); p != mPlantList.end(); ++p)p->Update();
		for (auto&& p = mZombieList.begin(); p != mZombieList.end(); ++p)p->Update();
		for (auto&& p = mBulletList.begin(); p != mBulletList.end(); ++p)p->Update();
		for (auto&& p = mItemList.begin(); p != mItemList.end(); ++p)p->Update();
		for (auto&& p = mMowerList.begin(); p != mMowerList.end(); ++p)p->Update();
		mMouseAddProp->Update();
		mMouseProp->Update();
		for (int i = 0; i < mSlot->SlotCount; ++i) {
			mSlot->mCards[i].Update();
		}
	}

	void Board::UpdateBuildings() {
		for (auto&& p = mBuildingList.begin(); p != mBuildingList.end(); ++p) {
			if (graveGrow && p->type == Building::Type::GRAVE && p->mProp < 100)++p->mProp;
			if (mApp->gameState == GameApp::State::BATTLE && p->type == Building::Type::CRATER && (p->mProp == 0 || --p->mProp == 0)) p->Kill();
			p->Update();
		}
	}

	void Plant::Update() {
		Anim* a = (*mApp)[shooterHead[0]];
		if (this->canAct && (mApp->gameState != GameApp::State::SELECT_CARD || mApp->mBoard == nullptr || !mApp->isBowling())) {
			if (!mApp->isGarden() && !mApp->isBattle())return;
		}
		UpdateMain();
		Shake();
		if (hp < 0)Kill();
		UpdateVideo();
	}

	void GameApp::NewSampleF(Sample::Type type, float speed) {
		if (mNoSample)return;
		if (speed > 0)speed = rand(speed, RandSample);
		else speed = 0;
		mSampleManagers->NewSampleF(type, speed);
	}

	void GameApp::NewSampleF(Sample::Type type) {
		if (mNoSample)return;
		float speed = gSampleInfoList[(int)type].speed;
		if (speed > 0)speed = rand(speed, RandSample);
		else speed = 0;
		mSampleManagers->NewSampleF(type, speed);
	}

	void GameApp::NewSample(Sample::Type type) {
		if (mNoSample)return;
		mSampleManagers->NewSample(type);
	}

	Building* Board::NewPortal(int col, int row, bool black) {
		Building* _this = mBuildingList.New();
		_this->row = row;
		_this->col = col;
		_this->type = black ? Building::Type::PORTAL_BLACK : Building::Type::PORTAL_WHITE;
		_this->layer = 307000 + 10000 * row;
		_this->PortalInit();
		return _this;
	}

	Building* Board::NewBrainIz(int row) {
		Building* _this = mBuildingList.New();
		_this->type = Building::Type::BRAIN_IZ;
		_this->row = row;
		_this->col = 0;
		_this->layer = 302000 + 10000 * row;
		_this->mProp = 70;
		_this->x = (float)(GetX(0, 0) - 40);
		_this->y = (float)(GetY(0, row) + 40);
		return _this;
	}

	Building* Board::NewVase(int col, int row, Plant::Type _type, Building::State state) {
		Building* _this = mBuildingList.New();
		_this->type = Building::Type::VASE;
		_this->state = state;
		_this->row = row;
		_this->col = col;
		_this->layer = 302000 + 10000 * row;
		_this->vaseContain = Building::VaseContain::PLANT;
		_this->vasePlantType = _type;
		return _this;
	}

	Building* Board::NewVase(int col, int row, Zombie::Type _type, Building::State state) {
		Building* _this = mBuildingList.New();
		_this->type = Building::Type::VASE;
		_this->state = state;
		_this->row = row;
		_this->col = col;
		_this->layer = 302000 + 10000 * row;
		_this->vaseContain = Building::VaseContain::ZOMBIE;
		_this->vaseZombieType = _type;
		return _this;
	}

	Building* Board::NewVase(int col, int row, int sunnum, Building::State state) {
		Building* _this = mBuildingList.New();
		_this->type = Building::Type::VASE;
		_this->state = state;
		_this->row = row;
		_this->col = col;
		_this->layer = 302000 + 10000 * row;
		_this->vaseContain = Building::VaseContain::SUN;
		_this->vaseSunCount = sunnum;
		return _this;
	}

	void Plant::UpdateMain() {
		if (!canAct)return;
		if (mApp->isGardenTree())return;
		if ((state == State::EXPLODE || smashed) && !~--vanishCountdown)return Kill();
		if (wakeupCountdown > 0 && --wakeupCountdown == 60) {
			mApp->NewSampleF(Sample::Type::PLANT_WAKE);
			SetSleep(false);
		}
		if (slept || smashed || bungeeProp != BungeeProp::NORMAL)return;
		UpdateAnim();
		if (propCountdown > 0)--propCountdown;
		if (mApp->isBowling())return UpdateBowling();
		BasicProp(type).Func_update(this);
		if (canAttack)UpdateAttack();
		if (suicideCountdown > 0 && --suicideCountdown == 0)Suicide();
	}

	void Plant::UpdateVideo() {
		Anim* theAnim = (*mApp)[mAnimID];
		if (!theAnim)return;
		UpdateShine();
		float x = mXOffset;
		float y = mYOffset + GetDrawOffsetY();
		float xStrech = 1;
		float yStrech = 1;
		float rate;
		if (mApp->level == GameApp::Level::Type::BIG_TIME && inrange(type,
			Type::SUNFLOWER,
			Type::WALL_NUT,
			Type::MARIGOLD
		)) {
			yStrech = 1.5f, xStrech = 1.5f;
			x -= 20;
			y -= 40;
		}
		if (type == Type::GIANT_WALL_NUT) {
			yStrech = 2.0f, xStrech = 2.0f;
			x -= 76;
			y -= 64;
		}
		if (type == Type::COFFEE_BEAN) {
			yStrech = 0.8f, xStrech = 0.8f;
			x += 12;
			y += 10;
		}
		if (type == Type::POTATO_MINE) {
			yStrech = 0.8f, xStrech = 0.8f;
			x += 12;
			y += 12;
		}
		if (state == State::GRAVE_BUSTER_IDLE) {
			rate = 1 - (float)propCountdown / 400;
			rate = limit(0.0f, rate, 1.0f);
			rate *= 30;
			y += rate;
		}
		if (wakeupCountdown > 0) {
			rate = 1 - (float)wakeupCountdown / 70;
			rate = limit(0.0f, rate, 1.0f);
			rate = 1 - 0.2f * (sin(2 * Pi * (3 * rate * rate - 2 * rate * rate * rate)));
			yStrech *= rate;
			y += 80 * (1 - rate);
		}
		theAnim->Update();
		if (type == Type::REPEATER_LEFT) {
			x += 80 * xStrech;
			xStrech = -xStrech;
		}
		if (gardenRank != -1) {
			float grow_rate, rate_target, yDiff, yDiff_target, xDiff, xDiff_target;
			GardenPlant* theGardenPlant = &mApp->mUserData->mGardenPlant[gardenRank];
			if (theGardenPlant->left) {
				x += 80 * xStrech;
				xStrech = -xStrech;
			}
			switch (theGardenPlant->state) {
			case GardenPlant::State::SPROUT:
			{
				xDiff = 20, xDiff_target = 20;
				yDiff = 40, yDiff_target = 40;
				rate = 0.5f, rate_target = 0.5f;
			}break;
			case GardenPlant::State::SMALL:
			{
				xDiff = 20, xDiff_target = 20;
				yDiff = 40, yDiff_target = 40;
				rate = 0.5f, rate_target = 0.5f;
			}break;
			case GardenPlant::State::MEDIUM:
			{
				xDiff = 20, xDiff_target = 10;
				yDiff = 40, yDiff_target = 20;
				rate = 0.5f, rate_target = 0.75f;
			}break;
			default:
			{
				xDiff = 10, xDiff_target = 0;
				yDiff = 20, yDiff_target = 0;
				rate = 0.75f, rate_target = 1;
			}break;
			}
			grow_rate = 1 - (float)propCountdown / 100;
			grow_rate = limit(0.0f, grow_rate, 1.0f);
			xDiff = cut(xDiff, grow_rate, xDiff_target);
			yDiff = cut(yDiff, grow_rate, yDiff_target);
			rate = cut(rate, grow_rate, rate_target);
			y += yDiff * yStrech;
			x += xDiff * xStrech;
			yStrech *= rate;
			xStrech *= rate;
			if (theGardenPlant->left && type != Type::POTATO_MINE)x -= 6;
			y += GetDrawOffsetYDiff(yStrech);
		}
		theAnim->mPosition.x = x;
		theAnim->mPosition.y = y;
		theAnim->mPosition.xStrech = xStrech;
		theAnim->mPosition.yStrech = yStrech;
	}

	float Plant::GetDrawOffsetY() {
		float offY = 0;
		if (type != Type::COFFEE_BEAN) {
			int clock;
			if (!mBoard && BasicProp(type).inWater) {
				clock = gGameApp->mUpdateClock;
				offY += 2.0f * sin(col * Pi / 4.0f + row * Pi + (float)clock * Pi / 100.0f);
			} else if (mBoard && mBoard->gridType[col][row] == Board::GridType::POOL
				|| this && mBoard->yard == Board::Yard::Type::AQUARIUM && col < 5) {
				clock = mBoard->timeBattle;
				offY += 2.0f * sin(col * Pi / 4.0f + row * Pi + (float)clock * Pi / 100.0f);
			}
		}
		if (mBoard && !smashed) {
			Plant* thePot = mBoard->GetGridPlant(col, row, Plant::Type::FLOWER_POT);
			if (thePot && !thePot->smashed) {
				if (type == Type::FLOWER_POT)return offY + 26.0f;
				offY += GetOnPotOffset(1.0f);
			}
		}
		switch (type) {
		case Type::FLOWER_POT:		return offY + 26.0f;
		case Type::LILY_PAD:		return offY + 25.0f;
		case Type::STARFRUIT:		return offY + 10.0f;
		case Type::TANGLE_KELP:		return offY + 24.0f;
		case Type::SEA_SHROOM:		return offY + 28.0f;
		case Type::COFFEE_BEAN:		return offY - 20.0f;
		case Type::PUMPKIN:			return offY + 15.0f;
		case Type::PUFF_SHROOM:		return offY + 5.0f;
		case Type::SCAREDY_SHROOM:	return offY - 14.0f;
		case Type::GRAVE_BUSTER:	return offY - 40.0f;
		case Type::SPIKEWEED:
		case Type::SPIKEROCK:
			int row_bottom;
			if (mBoard && BasicProp(mBoard->yard).havePool)row_bottom = 5;
			else row_bottom = 4;
			if (type == Type::SPIKEROCK)offY += 6.0f;
			if (mBoard) {
				if (mBoard->GetGridPlant(col, row, Plant::Type::FLOWER_POT) && mApp->level != GameApp::Level::Type::GARDEN)return offY + 5.0f;
				if (BasicProp(mBoard->yard).onRoof)return offY + 15.0f;
				if (mBoard->gridType[col][row] == Board::GridType::POOL)return offY;
			}
			if (row == row_bottom) {
				if (col < 7)return offY + 12.0f;
				if (BasicProp(mBoard->yard).havePool)return offY + 1.0f;
			}
			return offY + 15.0f;
		default:return offY;
		}

	}

	float Plant::GetOnPotOffset(float basic) {
		switch (type) {
		case Type::CHOMPER:
		case Type::PLANTERN:
			return -5 * basic - 5;
		case Type::SCAREDY_SHROOM:
			return -13 * basic + 13;
		case Type::PUFF_SHROOM:
		case Type::SUN_SHROOM:
		case Type::POTATO_MINE:
		case Type::SEA_SHROOM:
			return -9 * basic + 4;
		case Type::PEASHOOTER:
		case Type::SUNFLOWER:
		case Type::SNOW_PEA:
		case Type::REPEATER:
		case Type::HYPNO_SHROOM:
		case Type::THREEPEATER:
		case Type::TANGLE_KELP:
		case Type::SPIKEWEED:
		case Type::BLOVER:
		case Type::MAGNET_SHROOM:
		case Type::CABBAGE_PULT:
		case Type::MARIGOLD:
		case Type::MELON_PULT:
		case Type::REPEATER_LEFT:
			return -13 * basic + 8;
		case Type::LILY_PAD:
			return -21 * basic + 16;
		case Type::COFFEE_BEAN:
			return -25 * basic + 20;
		default:
			return -5 * basic;
		}
	}

	float Plant::GetDrawOffsetYDiff(float yStrech) {
		float v4 = 0, v8 = 0;
		switch (type) {
		case Type::STARFRUIT:
		case Type::PUFF_SHROOM:v4 = 10; v8 = 24; break;
		case Type::SUN_SHROOM:v4 = 10; v8 = 17; break;
		case Type::GRAVE_BUSTER:v4 = 50; v8 = 15; break;
		case Type::PEASHOOTER:
		case Type::REPEATER:
		case Type::REPEATER_LEFT:
		case Type::SNOW_PEA:
		case Type::THREEPEATER:
		case Type::SUNFLOWER:
		case Type::MARIGOLD:
		case Type::BLOVER:
		case Type::HYPNO_SHROOM:
		case Type::MAGNET_SHROOM:v4 = 0; v8 = 10; break;
		case Type::SCAREDY_SHROOM:v4 = 5; v8 = 5; break;
		case Type::LILY_PAD:v4 = -10; v8 = 30; break;
		case Type::TANGLE_KELP:v4 = -18; v8 = 20; break;
		case Type::SEA_SHROOM:v4 = -20; v8 = 15; break;
		case Type::CABBAGE_PULT:
		case Type::MELON_PULT:v4 = 3; v8 = 10; break;
		case Type::POTATO_MINE:v4 = 0; v8 = 5; break;
		case Type::TORCHWOOD:v4 = 0; v8 = 3; break;
		case Type::SPIKEWEED:v4 = -13; v8 = 10; break;
		case Type::PUMPKIN:v4 = 0; v8 = 20; break;
		case Type::PLANTERN:v4 = 0; v8 = -1; break;
		}
		return v4 + v8 * (yStrech - 1);
	}

	void Zombie::Update() {
		++existTime;
		if (or (
			mApp->gameState == GameApp::State::SELECT_CARD && type == Type::ZOMBOSS,
			isOnBoard() && mApp->upsellBattle(),
			mApp->gameState == GameApp::State::BATTLE,
			inrange(spawnWave, -4, -3, -2)
			));
		else return;
		if (state == State::ASHED) {
			if (--propCountdown == 0)Kill(), DropItem();
		} else if (state == State::MOWERED)SecKill();
		else if (state == State::DYING)UpdateFallGround(), Move();
		else {
			if (propCountdown > 0 && !isFreezedButtered())--propCountdown;
			if (mApp->gameState == GameApp::State::LOSE) {
				if (mBoard->mSceneProp->sceneTime > 1500)TryEnterChimney(), Move();
			} else if (spawnWave != -2 && spawnWave != -3)UpdateMain();
		}
		if (type == Type::BUNGEE_ZOMBIE)UpdateBungee();
		if (type == Type::POGO_ZOMBIE)UpdatePogo();
		UpdateAnimate();
		--lastHittedCount;
		if (shieldHittedCount > 0)--shieldHittedCount;
		if (shieldShakedCount > 0)--shieldShakedCount;
		if (vanishCountdown > 0 && --vanishCountdown == 0)Kill();
		mX = (int)x;
		mY = (int)y;
		Attachment* a = (*mApp)[mAttachmentID];
		if (a) {
			a->Update();
			a->SetPosition(x, y + h);
		}
		UpdateAnim();
	}

	void Pvz::Zombie::UpdateMain() {
		if (--sloganCountdown == 0 && rand(mBoard->mZombieList.mSize) == 0 && haveHead && type != Type::ZOMBOSS && !mBoard->isLevelEnding()) {
			if (type == Type::GARGANTUAR)mApp->NewSample(Sample::Type::ZOMBIE_CRY_GARGANTUAR);
			else {
				if (tongue)mApp->NewSampleF(Sample::Type::ZOMBIE_CRY_TONGUE, mApp->isLittleZombie() ? (rand(10.0f) + 40.0f) : 0.0f);
				else if (mApp->sukhbir)mApp->NewSampleF(Sample::Type::ZOMBIE_CRY_SUKHBIR, mApp->isLittleZombie() ? (rand(10.0f) + 40.0f) : 0.0f);
				else mApp->NewSampleF(Sample::Type::ZOMBIE_CRY_NORMAL, mApp->isLittleZombie() ? (rand(10.0f) + 40.0f) : 0.0f);
			}
		}
		if (freezeCountdown > 0 && --freezeCountdown == 0)BreakIce(), NewAttachedParticle(75, 106, ParticleSystem::Type::ICE_TRAP_RELEASE);
		if (slowCountdown > 0 && --slowCountdown == 0)AnimInitSpeed();
		if (butterCountdown > 0 && --butterCountdown == 0)BreakButter();
		if (state == State::CORAL_RISE)return UpdateRise();
		if (butterCountdown || freezeCountdown);
		else {
			UpdateAct();
			UpdateMove();
			UpdateEat();
			UpdateEnterWater();
			UpdateHighGridEnterLeave();
			UpdateLeave();
		}
		if (type == Type::ZOMBOSS)UpdateZomboss();
		if (isDying() || spawnWave == -4)return;
		if ((!haveHead) || (hp < 200 && (type == Type::ZOMBONI || type == Type::CATAPULT_ZOMBIE))) {
			int temp = 1;
			if (type == Type::YETI_ZOMBIE)temp = 10;
			if (hpMax >= 500)temp = 3;
			if (rand(5) == 0)Hitted(temp, HitType::SIDE | HitType::NO_FLASH);
		}
	}

	void Zombie::UpdateAct() {
		if (movementState == MovementState::ENTER_LADDER)UpdateUpLadder();
		if (movementState == MovementState::AQ)UpdateAQ();
		if (movementState == MovementState::ENTER_WATER || movementState == MovementState::LEAVE_WATER || inWater)UpdateWater();
		if (movementState == MovementState::ENTER_HIGHLAND || movementState == MovementState::LEAVE_HIGHLAND)UpdateHighGrid();
		if (movementState == MovementState::LEAVE_LADDER)UpdateDownLadder();
		if (movementState == MovementState::ENTER_CHIMNEY)UpdateEnterChimney();
		BasicProp(type).Func_act(this);
	}

	void Board::UpdateLevelEndProcess() {
		if (nextLevelCountdown > 0) {
			if ((!mApp->isVB()) || mApp->DaveState == GameApp::DaveState::NIL) {
				--nextLevelCountdown;
				if (mApp->level == GameApp::Level::Type::ADVENTURE && mApp->isVB() && nextLevelCountdown == 300) {
					mApp->DaveEnter();
					mApp->SetDave(mLevelProp->flags ? 2800 : 2700);
					mLevelProp->ClearBoard();
					nextLevelCountdown = 100;
				}
			}
			if (nextLevelCountdown == 1 && mApp->isSurvival())Save();
			if (nextLevelCountdown == 0) {
				if (mApp->isVB() && mApp->level == GameApp::Level::Type::ADVENTURE)return;
				if (mApp->isVB() && !mApp->isVBWillEnd()) {
					mLevelProp->ClearBoard();
					mLevelProp->SetVBBuild();
					return;
				}
				if (mApp->level == GameApp::Level::Type::I_ZOMBIE_ENDLESS) {
					mLevelProp->ClearBoard();
					mLevelProp->SetIZBuild();
					return;
				}
				if (mApp->level == GameApp::Level::Type::LAST_STAND) {
					KillBoardText(AdviceType::NIL);
					return;
				}
				exitLevel = true;
				KillBetraiedZombies();
				return;
			}
		}
		if (exitLevelCountdown < 0)return;
		if (--exitLevelCountdown == 0) {
			exitLevel = true;
			return;
		}
		if (exitLevelCountdown == 300 && mApp->isSurvivalWontEnd() && (adventureLevelRank + 1) % 10)mApp->PlaySample(SOUND_LIGHTFILL);
		if (sellMowerCountdown > 0 && --sellMowerCountdown)return;
		if (!mApp->isHaveMoney() || mApp->isSurvivalWontEnd())return;
		sellMowerCountdown = 40;
		Mower* temp = Board::GetFirstMower();
		if (!temp)return;
		NewItem(40 + (int)temp->x, 40 + (int)temp->y, Item::Type::GOLD_COIN, Item::MovementState::FROM_MOWER);
		SoundInstance* soundinstance = mApp->mSoundManager->GetSoundInstance(SOUND_POINTS);
		if (soundinstance) {
			soundinstance->Play(false, true);
			soundinstance->AdjustPitch(limit(0, 6 - GetStopMowerCount(), 6));
		}
		temp->Kill();
	}

	Mower* Board::GetFirstMower() {
		Mower* ans = nullptr;
		for (auto&& p : mMowerList)if (!ans || ans->row > p.row)ans = &p;
		return ans;
	}

	int Board::GetStopMowerCount() {
		int ans = 0;
		for (auto&& p : mMowerList)if (p.state != Mower::State::WORK && p.state != Mower::State::SMASHED)++ans;
		return ans;
	}

	void Bgm::Burst() {
		if (BurstStage) {
			BurstStage = 1;
			BurstCountdown = 200;
		}
	}

	void Board::UpdateZombieSpawn() {
		if (mApp->level == GameApp::Level::Type::UPSELL || mApp->level == GameApp::Level::Type::INTRO)return;
		if (finalWaveSoundCountdown > 0 && --finalWaveSoundCountdown == 0)mApp->PlaySample(SOUND_FINALWAVE);
		if (inrange(tutorial,
			Tutorial::LEVEL1_PLANT_PEASHOOTER,
			Tutorial::LEVEL1_REFRESH_PEASHOOTER,
			Tutorial::SLOTMACHINE_PULL
		) || isLevelEnding())return;
		if (levelendZombieSpawnCountdown > 0 && --levelendZombieSpawnCountdown == 0)NewLastWaveZombies();
		if (hugewaveSpawnCountdown) {
			if (--hugewaveSpawnCountdown == 0)KillBoardText(AdviceType::HUGE_WAVE), ShowLastWaveText(), nextwaveSpawnCountdown = 1;
			else if (hugewaveSpawnCountdown == 725)mApp->PlaySample(SOUND_HUGE_WAVE);
			else if (hugewaveSpawnCountdown == 700) {
				if (inrange(mApp->mBgm->type,
					Bgm::Type::DAY_GRASSWALK,
					Bgm::Type::POOL_WATERYGRAVES,
					Bgm::Type::FOG_RIGORMORMIST,
					Bgm::Type::ROOF_GRAZETHEROOF
				))mApp->mBgm->Burst();
				return;
			} else if (hugewaveSpawnCountdown == 400) {
				if (mApp->mBgm->type == Bgm::Type::NIGHT_MOONGRAINS)mApp->mBgm->Burst();
				return;
			} else return;
		}
		if (mLevelProp->UpdateZombieSpawn())return;
		if (nowwaveNum == maxWaveNum && (mApp->isSurvivalWillEnd() || mApp->level == GameApp::Level::Type::LAST_STAND || (!mApp->isSurvival() && !mApp->isLevelEndlessWave())))return;
		--nextwaveSpawnCountdown;
		if (nowwaveNum == maxWaveNum && mApp->isSurvival()) {
			if (nextwaveSpawnCountdown == 0)ShowLevelEndWhiteText();
			return;
		}
		if (nextwaveSpawnCountdownMax - nextwaveSpawnCountdown > 400 && nextwaveSpawnCountdown > 201 && GetNowWaveZombieHPSum() <= nowwaveRefreshHP)nextwaveSpawnCountdown = 201;
		if (nextwaveSpawnCountdown == 5) {
			if (isHugeWave()) {
				KillBoardText();
				SetBoardText(u8"[ADVICE_HUGE_WAVE]", BoardText::Type::HUGE_WAVE, AdviceType::HUGE_WAVE);
				hugewaveSpawnCountdown = 750;
				return;
			}
			NextWaveComing();
		}
		if (nextwaveSpawnCountdown == 0) {
			SpawnWave();
			nowwaveFullHP = GetNowWaveZombieHPSum();
			if (nowwaveNum == maxWaveNum && mApp->isSurvival()) {
				nowwaveRefreshHP = 0;
				nextwaveSpawnCountdown = 5500;
			} else if (isHugeWave() && !(mApp->isBowling() || mApp->level == GameApp::Level::Type::LAST_STAND)) {
				nowwaveRefreshHP = 0;
				nextwaveSpawnCountdown = 4500;
			} else {
				nowwaveRefreshHP = (int)(rand(0.5f, 0.65f) * (float)nowwaveFullHP);
				if (mApp->isLittleZombie() || mApp->level == GameApp::Level::Type::COLUMN || mApp->level == GameApp::Level::Type::LAST_STAND) {
					nextwaveSpawnCountdown = 750;
				} else {
					nextwaveSpawnCountdown = 2500 + rand(600);
				}
			}
			nextwaveSpawnCountdownMax = nextwaveSpawnCountdown;
		}
	}

	void LevelProp::UpdateEffect() {
		if (mApp->isStorm())UpdateThunderEffect();
		if (mBoard->pause) {
			if (mApp->level == GameApp::Level::Type::BEJEVELED2)col = -1, row = -1;
			return;
		}
		if (mApp->isRain())UpdateRain();
		if (mApp->gameState != GameApp::State::BATTLE)return;
		if (mApp->isBelt())UpdateBelt();
		if (mApp->isBejeveled())UpdateBejeveled();
		if (mApp->isVB())UpdateVB();
		if ((mApp->isVB() || mApp->isIZ()) && mBoard->mSlot->mY < 0) {
			if (mBoard->sunValue + mBoard->GetCollectingSunValue() > 0 || mBoard->mSlot->mY > -IMAGE_SEEDBANK->GetHeight()) {
				mBoard->mSlot->mY += 2;
				if (mBoard->mSlot->mY > 0)mBoard->mSlot->mY = 0;
			}
		}
		if (mApp->isHammer())UpdateHammer();
		if (mApp->isIZ())UpdateIZ();
		if (mApp->isSlotMachine())UpdateSlotMachine();
		if (mApp->isQuick())mBoard->UpdateMain();
		if (mApp->isSeedrain())UpdateSeedRain();
		if (mApp->isPortal())UpdatePortal();
		if (mApp->isSquirrel())UpdateSquirrel();
		if (mApp->isZombieAQ())UpdateZombieAQ();
		if (mApp->isWT())UpdateWT();
		if (mApp->isIce() && mBoard->timeBattle == 3000) {
			mApp->NewSampleF(Sample::Type::BEJEVELED_FAIL);
			mApp->PlaySample(SOUND_LOSEMUSIC);
		}
		if (mApp->isLS())UpdateLS();
		Anim* a = (*mApp)[mainAnim];
		if (a && a->isAttachment)a->Update();
	}

	int Board::GetCollectingSunValue() {
		int ans = 0;
		for (auto&& p : mItemList) if (p.collected)ans += BasicProp(p.type).sunValue;
		return ans;
	}

	int Board::GetCollectingCoinValue() {
		int ans = 0;
		for (auto&& p : mItemList) if (p.collected)ans += BasicProp(p.type).coinValue;
	}

	void Board::UpdateSunDrop() {
		if (BasicProp(yard).isNight)return;
		if (isLevelEnding())return;
		if (inrange(mApp->level,
			GameApp::Level::Type::ICE_LEVEL,
			GameApp::Level::Type::UPSELL,
			GameApp::Level::Type::INTRO,
			GameApp::Level::Type::ZOMBIE_AQ,
			GameApp::Level::Type::GARDEN,
			GameApp::Level::Type::WISDOM_TREE,
			GameApp::Level::Type::LAST_STAND
		) || mApp->isIZ() || mApp->isVB() || mApp->isSquirrel() || mApp->isBelt())return;
		if (tutorial == Tutorial::SLOTMACHINE_PULL)return;
		if ((tutorial == Tutorial::LEVEL1_PICK_PEASHOOTER || tutorial == Tutorial::LEVEL1_PLANT_PEASHOOTER) && mPlantList.mSize == 0)return;
		if (--sunDropCountdown == 0) {
			++sunDropCount;
			sunDropCountdown = min(950, 425 + sunDropCount * 10) + rand(275);
			if (mApp->level != GameApp::Level::Type::BIG_TIME)NewItem(rand(100, 650), 60, Item::Type::SUN, Item::MovementState::FALL_QUICK);
			else NewItem(rand(100, 650), 60, Item::Type::SUN_LARGE, Item::MovementState::FALL_QUICK);
		}
	}

	void Zombie::UpdateMove() {
		if (type == Type::BUNGEE_ZOMBIE || type == Type::ZOMBOSS || state == State::CORAL_RISE || movementState == MovementState::AQ)return;
		Move();
		if (type == Type::ZOMBONI || type == Type::CATAPULT_ZOMBIE)if (!zomboniDying)UpdateSmash();
		if (blew) {
			x += 10.0f;
			if (x > 850.0f)KillWithItem();
		}
		if (movementState != MovementState::NIL)return;
		float targety = GetYBase();
		if (y + 1.0f < targety)y += 1.0f;
		else if (y - 1.0f > targety)y -= 1.0f;
		else y = targety;
	}

	float Zombie::GetYBase() {
		if (!isOnBoard())return 0.0f;
		if (isInHighgrid()) {
			if (h < 30.0f)movementState = MovementState::ENTER_HIGHLAND;
			inHighgrid = true;
		}
		float ans = mBoard->GetY(x + 40.0f, row) - 30.0f;
		if (type == Type::BALLOON_ZOMBIE)ans -= 30.0f;
		if (type == Type::POGO_ZOMBIE)ans -= 16.0f;
		return ans;
	}

	float Board::GetY(float x, int row) {
		if (yard != Yard::Type::ROOF && yard != Yard::Type::MOON)return(float)GetY(0, row);
		float num = 0.0f;
		float num2 = 440.0f;
		if (x < num2) {
			num = (num2 - x) * 0.25f;
		}
		return(float)GetY(8, row) + num;
	}

	int Board::GetX(int col, int row) {
		if (mApp->level == GameApp::Level::Type::GARDEN && inrange(yard,
			Yard::Type::MUSHOOM_GARDEN,
			Yard::Type::AQUARIUM,
			Yard::Type::GREENHOUSE
		))return mApp->mGardenProp->GetX(col, row);
		return col * 80 + 40;
	}

	int Board::GetY(int col, int row) {
		if (mApp->level == GameApp::Level::Type::GARDEN && inrange(yard,
			Yard::Type::MUSHOOM_GARDEN,
			Yard::Type::AQUARIUM,
			Yard::Type::GREENHOUSE
		))return mApp->mGardenProp->GetY(col, row);
		int ans = 0;
		if (yard == Yard::Type::ROOF || yard == Yard::Type::MOON) {
			if (col < 5)ans = (5 - col) * 20;
			ans = row * 85 + 70 + ans;
		} else if (yard == Yard::Type::POOL || yard == Yard::Type::FOG) {
			ans = row * 85 + 80;
		} else {
			ans = row * 100 + 80;
		}
		if (col != -1 && gridType[col][row] == GridType::HIGHLAND) {
			ans -= 30;
		}
		return ans;
	}

	int Board::GetCol(int x, int y) {
		if (mApp->level == GameApp::Level::Type::GARDEN && inrange(yard,
			Yard::Type::GREENHOUSE,
			Yard::Type::MUSHOOM_GARDEN,
			Yard::Type::AQUARIUM
		))return mApp->mGardenProp->GetCol(x, y);
		return limit(-1, (x - 40) / 80, 8);
	}

	int Board::GetRow(int x, int y) {
		if (mApp->level == GameApp::Level::Type::GARDEN && inrange(yard,
			Yard::Type::GREENHOUSE,
			Yard::Type::MUSHOOM_GARDEN,
			Yard::Type::AQUARIUM
		))return mApp->mGardenProp->GetRow(x, y);
		int col = GetCol(x, y);
		if (col == -1 || y < 80)return -1;
		if (yard == Yard::Type::ROOF || yard == Yard::Type::MOON) {
			int temp = 0;
			if (col < 5)temp = (5 - col) * 20 - 20;
			return limit(0, (y - 80 - temp) / 85, 4);
		} else if (yard == Yard::Type::POOL || yard == Yard::Type::FOG) {
			return limit(0, (y - 80) / 85, 5);
		} else {
			return limit(0, (y - 80) / 100, 4);
		}
	}

	int GardenProp::GetX(int col, int row) {
		int count = 0;
		GridPlacement* list = nullptr;
		switch (mBoard->yard) {
		case Board::Yard::Type::MUSHOOM_GARDEN:
			count = 8;
			list = gridListMG;
			break;
		case Board::Yard::Type::AQUARIUM:
			count = 8;
			list = gridListAQ;
			break;
		case Board::Yard::Type::GREENHOUSE:
			count = 32;
			list = gridListGH;
			break;
		}
		for (int i = 0; i < count; ++i)if (col == list[i].col && row == list[i].row)return list[i].x;
		return -1;
	}

	int GardenProp::GetY(int col, int row) {
		int count = 0;
		GridPlacement* list = nullptr;
		switch (mBoard->yard) {
		case Board::Yard::Type::MUSHOOM_GARDEN:
			count = 8;
			list = gridListMG;
			break;
		case Board::Yard::Type::AQUARIUM:
			count = 8;
			list = gridListAQ;
			break;
		case Board::Yard::Type::GREENHOUSE:
			count = 32;
			list = gridListGH;
			break;
		}
		for (int i = 0; i < count; ++i)if (col == list[i].col && row == list[i].row)return list[i].y;
		return -1;
	}

	int GardenProp::GetCol(int x, int y) {
		int count = 0;
		GridPlacement* list = nullptr;
		switch (mBoard->yard) {
		case Board::Yard::Type::MUSHOOM_GARDEN:
			count = 8;
			list = gridListMG;
			break;
		case Board::Yard::Type::AQUARIUM:
			count = 8;
			list = gridListAQ;
			break;
		case Board::Yard::Type::GREENHOUSE:
			count = 32;
			list = gridListGH;
			break;
		}
		for (int i = 0; i < count; ++i)if (x >= list[i].x && x <= list[i].x + 80 && y >= list[i].y && y <= list[i].y + 85)return list[i].col;
		return -1;
	}

	int GardenProp::GetRow(int x, int y) {
		int count = 0;
		GridPlacement* list = nullptr;
		switch (mBoard->yard) {
		case Board::Yard::Type::MUSHOOM_GARDEN:
			count = 8;
			list = gridListMG;
			break;
		case Board::Yard::Type::AQUARIUM:
			count = 8;
			list = gridListAQ;
			break;
		case Board::Yard::Type::GREENHOUSE:
			count = 32;
			list = gridListGH;
			break;
		}
		for (int i = 0; i < count; ++i)if (x >= list[i].x && x <= list[i].x + 80 && y >= list[i].y && y <= list[i].y + 85)return list[i].row;
		return -1;
	}

	bool Zombie::isInHighgrid() { return isOnBoard() && mBoard->gridType[max(0, mBoard->GetCol(mX + 75, mY))][row] == Board::GridType::HIGHLAND; }

	bool Zombie::isInWater() { return mBoard->gridType[max(0, mBoard->GetCol(mX + 75, mY))][row] == Board::GridType::POOL && mBoard->gridType[max(0, mBoard->GetCol(mX + 45, mY))][row] == Board::GridType::POOL && x < 800.0f; }

	void Zombie::KillWithItem() {
		Kill();
		DropItem();
	}

	void Zombie::DropItem() {
		if (!isOnBoard())return;
		zombieDefeated[(int)type] = true;
		if (type == Type::YETI_ZOMBIE)mBoard->killedYeti = true;
		DieTryEndGame();
		if (droppedItem || mBoard->isLevelEnding() || !mApp->isHaveMoney())return;
		droppedItem = true;
		if (mApp->isLittleZombie() && rand(4) != 0)return;
		if (mApp->isIZ())return;
		Rect rect = GetDefRect();
		int ax = rect.mX + rect.mW / 2;
		int ay = rect.mY + rect.mH / 4;
		if (type == Type::YETI_ZOMBIE) {
			mApp->NewSample(Sample::Type::ITEM_SUN_INIT);
			mBoard->NewItem(ax - 20, ay, Item::Type::DIAMOND, Item::MovementState::DROPPED);
			mBoard->NewItem(ax - 30, ay, Item::Type::DIAMOND, Item::MovementState::DROPPED);
			mBoard->NewItem(ax - 40, ay, Item::Type::DIAMOND, Item::MovementState::DROPPED);
			mBoard->NewItem(ax - 50, ay, Item::Type::DIAMOND, Item::MovementState::DROPPED);
			return;
		}
		mBoard->DropItem(ax, ay, BasicProp(type).value);
	}

	int Board::GetItemCount(Item::Type _type) {
		int ans = 0;
		for (auto&& p : mItemList) if (p.type == _type)++ans;
		return ans;
	}

	bool GardenProp::isFull(bool includeDroppedPresentd) {
		int num = 32;
		if (mBoard && includeDroppedPresentd) {
			num -= mBoard->GetItemCount(Item::Type::PRESENT_PLANT_AWARD);
			num -= mBoard->GetItemCount(Item::Type::PRESENT_PLANT);
		}
		for (int i = 0; i < mApp->mUserData->gardenPlantCount; ++i)if (mApp->mUserData->mGardenPlant[i].gardenYard == YardType::GREENHOUSE)--num;
		return num <= 0;
	}

	bool GardenProp::canDropPresent() { return mApp->isFinishedAdventure() && !isFull(true); }

	bool GardenProp::canDropChocolate() { return mApp->mUserData->shopItemBought[(int)Shop::ItemType::SNAIL] && mApp->mUserData->shopItemBought[(int)Shop::ItemType::CHOCOLATE] < 1010; }

	void Board::DropItem(int x, int y, int rate) {
		if (mApp->isFirseTimeAdventure() && adventureLevelRank == 22 && nowwaveNum > 5 && !mApp->mUserData->minigamePresentCollected && GetItemCount(Item::Type::PRESENT_MINIGAME) == 0) {
			mApp->NewSample(Sample::Type::ITEM_SUN_INIT);
			NewItem(x - 40, y, Item::Type::PRESENT_MINIGAME, Item::MovementState::DROPPED);
			return;
		}
		if (mApp->isFirseTimeAdventure() && adventureLevelRank == 36 && nowwaveNum > 5 && !mApp->mUserData->minigamePresentCollected && GetItemCount(Item::Type::PRESENT_PUZZLE) == 0) {
			mApp->NewSample(Sample::Type::ITEM_SUN_INIT);
			NewItem(x - 40, y, Item::Type::PRESENT_PUZZLE, Item::MovementState::DROPPED);
			return;
		}
		int ans = rand(30000);
		if (mApp->isFirseTimeAdventure() && adventureLevelRank == 11 && !dropppedFirstCoin && nowwaveNum > 5) {
			ans = 1000;
		}
		if (mApp->isColumn()) {
			ans *= 5;
		}
		if (mApp->isHammer()) {
			int max;
			if (sunValue > 500) {
				max = 2500 + 300;
			} else if (sunValue > 350) {
				max = 2500 + 600;
			} else if (sunValue > 200) {
				max = 2500 + 1200;
			} else {
				max = 2500 + 2500;
			}
			if (ans >= 2500 * rate && ans < max * rate) {
				mApp->NewSampleF(Sample::Type::ITEM_SUN_INIT);
				NewItem(x - 20, y, Item::Type::SUN, Item::MovementState::DROPPED);
				NewItem(x - 40, y, Item::Type::SUN, Item::MovementState::DROPPED);
				NewItem(x - 60, y, Item::Type::SUN, Item::MovementState::DROPPED);
				return;
			}
		}
		if (refreshedWaveNum > 70)return;
		int level_present;
		if (!mApp->mGardenProp->canDropPresent()) {
			level_present = 0;
		} else if (mApp->isAdventure() && !mApp->isFirseTimeAdventure()) {
			level_present = 24;
		} else if (mApp->isSurvivalEndless()) {
			level_present = 3;
		} else {
			level_present = 12;
		}
		int level_chocolate = level_present;
		if (!mApp->mGardenProp->canDropChocolate()) {
			level_chocolate += 0;
		} else if (mApp->isAdventure() && !mApp->isFirseTimeAdventure()) {
			level_chocolate += 72;
		} else if (mApp->isSurvivalEndless()) {
			level_chocolate += 9;
		} else {
			level_chocolate += 36;
		}
		int level_diamond = 14 + level_chocolate;
		int level_gold = 250 + level_chocolate;
		int level_silver = 2500 + level_chocolate;
		Item::Type thetype;
		if (ans < level_present * rate) {
			thetype = Item::Type::PRESENT_PLANT;
		} else if (ans < level_chocolate * rate) {
			thetype = Item::Type::CHOCOLATE;
		} else if (ans < level_diamond * rate) {
			thetype = Item::Type::DIAMOND;
		} else if (ans < level_gold * rate) {
			thetype = Item::Type::GOLD_COIN;
		} else if (ans < level_silver * rate) {
			thetype = Item::Type::SILVER_COIN;
		} else return;
		if (thetype == Item::Type::DIAMOND && mApp->mUserData->shopItemBought[(int)Shop::ItemType::SLOT] < 1) {
			thetype = Item::Type::GOLD_COIN;
		}
		if (mApp->isBowling() && (thetype == Item::Type::SILVER_COIN || thetype == Item::Type::GOLD_COIN || thetype == Item::Type::DIAMOND)) {
			return;
		}
		mApp->NewSampleF(Sample::Type::ITEM_SUN_INIT);
		NewItem(x - 40, y, thetype, Item::MovementState::DROPPED);
		dropppedFirstCoin = true;
	}

	bool Zombie::isFacingRight() {
		if (betray)return true;
		if (movementState == MovementState::AQ && (dh < 1.5707964f || dh > 4.712389f))return true;
		if (type == Type::DIGGER_ZOMBIE) {
			return inrange(state,
				State::DIGGER_JUMP,
				State::DIGGER_DASE,
				State::DIGGER_WALKRIGHT
			) || (isDying() && stage1);
		}
		return type == Type::YETI_ZOMBIE && !stage1;
	}

	ZombieDrawPosition* Zombie::GetDrawPosition(ZombieDrawPosition* ans) {
		ans->mImageOffsetX = x - (float)mX;
		ans->mImageOffsetY = y - (float)mY;
		if (eating) {
			ans->mHeadX = 47;
			ans->mHeadY = 4;
		} else {
			switch (noAnimShakeFrameIndex) {
			case 0: ans->mHeadX = 50; ans->mHeadY = 2; break;
			case 1: ans->mHeadX = 49; ans->mHeadY = 1; break;
			case 2: ans->mHeadX = 49; ans->mHeadY = 2; break;
			case 3: ans->mHeadX = 48; ans->mHeadY = 4; break;
			case 4: ans->mHeadX = 48; ans->mHeadY = 5; break;
			case 5: ans->mHeadX = 48; ans->mHeadY = 4; break;
			case 6: ans->mHeadX = 48; ans->mHeadY = 2; break;
			case 7: ans->mHeadX = 49; ans->mHeadY = 1; break;
			case 8: ans->mHeadX = 49; ans->mHeadY = 2; break;
			case 9: ans->mHeadX = 50; ans->mHeadY = 4; break;
			case 10: ans->mHeadX = 50; ans->mHeadY = 5; break;
			default:ans->mHeadX = 50; ans->mHeadY = 4; break;
			}
		}
		ans->mArmY = ans->mHeadY / 2;
		switch (type) {
		case Type::DOLPHIN_RIDER_ZOMBIE:break;
		case Type::FOOTBALL_ZOMBIE:ans->mImageOffsetY += -16.0f; break;
		case Type::YETI_ZOMBIE:ans->mImageOffsetY += -20.0f; break;
		case Type::CATAPULT_ZOMBIE:ans->mImageOffsetX += -25.0f; ans->mImageOffsetY += -18.0f; break;
		case Type::POGO_ZOMBIE:ans->mImageOffsetY += 16.0f; break;
		case Type::BALLOON_ZOMBIE:ans->mImageOffsetY += 17.0f; break;
		case Type::POLE_VAULTING_ZOMBIE:ans->mImageOffsetX += -6.0f; ans->mImageOffsetY += -11.0f; break;
		case Type::ZOMBONI:ans->mImageOffsetX += 68.0f; ans->mImageOffsetY += -23.0f; break;
		case Type::GARGANTUAR:ans->mImageOffsetY += -8.0f; break;
		case Type::GIGA_GARGANTUAR:ans->mImageOffsetY += -8.0f; break;
		case Type::ZOMBIE_BOBSLED_TEAM:ans->mImageOffsetY += -12.0f; break;
		case Type::DANCING_ZOMBIE:ans->mImageOffsetY += 15.0f; break;
		case Type::BACKUP_DANCER:ans->mImageOffsetY += 15.0f; break;
		}
		if (state == State::CORAL_RISE) {
			ans->mBodyY = -h;
			if (inWater) {
				ans->mClipHeight = ans->mBodyY;
			} else {
				ans->mClipHeight = ans->mBodyY + (float)min(propCountdown, 40);
			}
			if (isInHighgrid()) {
				ans->mBodyY -= 30.0f;
			}
		} else if (type == Type::DOLPHIN_RIDER_ZOMBIE) {
			ans->mBodyY = -h;
			ans->mClipHeight = -200.0f;
			if (state == State::DOLPHIN_DIVE) {
				Anim* reanimation = (*mApp)[mAnimId];
				if (reanimation->updateRate >= 0.56f && reanimation->updateRate <= 0.65f) {
					ans->mClipHeight = 0.0f;
				} else if (reanimation->updateRate >= 0.75f) {
					ans->mClipHeight = -h - 10.0f;
				}
			} else if (state == State::DOLPHIN_SPRINT) {
				ans->mImageOffsetX += 70.0f;
				if (movementState == MovementState::DRAGGED_UNDER) {
					ans->mClipHeight = -h - 15.0f;
				} else {
					ans->mClipHeight = -h - 10.0f;
				}
			} else if (state == State::DOLPHIN_JUMP) {
				ans->mImageOffsetX += 70.0f + h;
				Anim* reanimation = (*mApp)[mAnimId];
				if (reanimation->updateRate <= 0.06f) {
					ans->mClipHeight = -h - 10.0f;
				} else if (reanimation->updateRate >= 0.5f && reanimation->updateRate <= 0.76f) {
					ans->mClipHeight = -13.0f;
				}
			} else if (state == State::DOLPHIN_WALK_EMPTY_HAND || state == State::DYING) {
				ans->mImageOffsetY += 50.0f;
				if (state == State::DYING) {
					ans->mClipHeight = -h + 44.0f;
				} else if (movementState == MovementState::DRAGGED_UNDER) {
					ans->mClipHeight = -h + 36.0f;
				}
			} else {
				if (state == State::DOLPHIN_WALK && movementState == MovementState::LEAVE_WATER) {
					ans->mClipHeight = -h;
				} else if (state == State::DOLPHIN_WALK_EMPTY_HAND && movementState == MovementState::LEAVE_WATER) {
					ans->mClipHeight = -h;
				}
			}
		} else if (type == Type::SNORKEL_ZOMBIE) {
			ans->mBodyY = -h;
			ans->mClipHeight = -200.0f;
			if (state == State::SNORKEL_DIVE) {
				Anim* reanimation = (*mApp)[mAnimId];
				if (reanimation->updateRate >= 0.8f) {
					ans->mClipHeight = -10.0f;
				}
			} else if (inWater) {
				ans->mClipHeight = -h - 5.0f;
				ans->mClipHeight += 20.0f - 20.0f * size;
			}
		} else if (inWater) {
			ans->mBodyY = -h;
			ans->mClipHeight = -h - 7.0f;
			ans->mClipHeight += 10.0f - 10.0f * size;
			if (eating) {
				ans->mClipHeight += 7.0f;
			}
		} else if (state == State::BACKUP_DANCER_SPAWN) {
			ans->mBodyY = -h;
			ans->mClipHeight = -h;
			if (isInHighgrid()) {
				ans->mBodyY -= 30.0f;
			}
		} else if (state == State::DIGGER_JUMP || state == State::DIGGER_ATTRACTED) {
			ans->mBodyY = -h;
			if (propCountdown > 20) {
				ans->mClipHeight = -h;
			} else {
				ans->mClipHeight = -200.0f;
			}
		} else if (type == Type::BUNGEE_ZOMBIE) {
			ans->mBodyY = -h;
			ans->mImageOffsetX += -18.0f;
			if (isInHighgrid()) {
				ans->mBodyY -= 30.0f;
			}
			ans->mClipHeight = -200.0f;
		} else {
			ans->mBodyY = -h;
			ans->mClipHeight = -200.0f;
		}
		return ans;
	}

	int Zombie::GetBodyY() {
		if ((state == State::CORAL_RISE || state == State::BACKUP_DANCER_SPAWN || type == Type::BUNGEE_ZOMBIE) && isInHighgrid())return(int)-h - 30;
		else return(int)-h;
	}

	int Zombie::GetClipHeight() {
		if (state == State::CORAL_RISE) {
			if (inWater) {
				return(int)-h;
			} else {
				return(int)-h + min(propCountdown, 40);
			}
		} else if (type == Type::DOLPHIN_RIDER_ZOMBIE) {
			if (state == State::DOLPHIN_DIVE) {
				Anim* reanimation = (*mApp)[mAnimId];
				if (reanimation->updateRate >= 0.56f && reanimation->updateRate <= 0.65f)return 0;
				else if (reanimation->updateRate >= 0.75f)return(int)-h - 10;
				else return -200;
			} else if (state == State::DOLPHIN_SPRINT) {
				if (movementState == MovementState::DRAGGED_UNDER)return(int)-h - 15;
				else return(int)-h - 10;
			} else if (state == State::DOLPHIN_JUMP) {
				Anim* reanimation = (*mApp)[mAnimId];
				if (reanimation->updateRate <= 0.06f)return(int)-h - 10;
				else if (reanimation->updateRate >= 0.5f && reanimation->updateRate <= 0.76f)return -13;
				else return -200;
			} else if (state == State::DOLPHIN_WALK_EMPTY_HAND || state == State::DYING) {
				if (state == State::DYING)return(int)-h + 44;
				else if (movementState == MovementState::DRAGGED_UNDER)return(int)-h + 36;
				else return -200;
			} else {
				return(int)-h;
			}
		} else if (type == Type::SNORKEL_ZOMBIE) {
			if (state == State::SNORKEL_DIVE) {
				Anim* reanimation = (*mApp)[mAnimId];
				if (reanimation->updateRate >= 0.8f)return -10;
				else return -200;
			} else if (inWater) {
				return(int)(-h - 20 * size) + 15;
			} else {
				return -200;
			}
		} else if (inWater) {
			if (eating)return(int)(-h - 10 * size) + 3;
			else return(int)(-h - 10 * size) + 10;
		} else if (state == State::BACKUP_DANCER_SPAWN) {
			return(int)-h;
		} else if (state == State::DIGGER_JUMP || state == State::DIGGER_ATTRACTED) {
			if (propCountdown > 20)return(int)-h;
			else return -200;
		} else {
			return -200;
		}
	}

	Rect Zombie::GetDefRect() {
		Rect ans = defRect;
		if (isFacingRight()) {
			ans.mX = mW - ans.mX - ans.mW;
		}
		ans.mX += mX;
		ans.mY += (mY + GetBodyY());
		if (GetClipHeight() > -100)ans.mH -= GetClipHeight();
		return ans;
	}

	Rect Zombie::GetAtkRect() {
		Rect ans = atkRect;
		if (state == State::POLE_VAULTING_JUMP || state == State::DOLPHIN_JUMP) {
			ans = Rect(-40, 0, 100, 115);
		}
		if (isFacingRight()) {
			ans.mX = mW - ans.mX - ans.mW;
		}
		ans.mX += mX;
		ans.mY += (mY + GetBodyY());
		if (GetClipHeight() > -100)ans.mH -= GetClipHeight();
		return ans;
	}

	Rect Plant::GetAtkRect(bool split) {
		if (mApp->isBowling())return Rect(mX, mY, mW - 20, mH);
		if (split && type == Type::SPLIT_PEA) return Rect(0, mY, mX + 16, mH);
		switch (type) {
		case Type::REPEATER_LEFT:return Rect(0, mY, mX, mH);
		case Type::SQUASH:return Rect(mX + 20, mY, mW - 35, mH);
		case Type::CHOMPER:return Rect(mX + 80, mY, 40, mH);
		case Type::SPIKEWEED:
		case Type::SPIKEROCK:return Rect(mX + 20, mY, mW - 50, mH);
		case Type::POTATO_MINE:return Rect(mX, mY, mW - 25, mH);
		case Type::TORCHWOOD:return Rect(mX + 50, mY, 30, mH);
		case Type::PUFF_SHROOM:
		case Type::SEA_SHROOM:return Rect(mX + 60, mY, 230, mH);
		case Type::FUME_SHROOM:return Rect(mX + 60, mY, 340, mH);
		case Type::GLOOM_SHROOM:return Rect(mX - 80, mY - 80, 240, 240);
		case Type::TANGLE_KELP:return Rect(mX, mY, mW, mH);
		case Type::CATTAIL:return Rect(-800, -600, 1600, 1200);
		default:return Rect(mX + 60, mY, 800, mH);
		}
	}

	Rect Plant::GetDefRect() {
		switch (type) {
		case Pvz::Plant::Type::TALL_NUT:return Rect(mX + 10, mY, mW, mH);
		case Pvz::Plant::Type::PUMPKIN:return Rect(mX, mY, mW - 20, mH);
		case Pvz::Plant::Type::COB_CANNON:return Rect(mX, mY, 140, 80);
		default:return Rect(mX + 10, mY, mW - 20, mH);
		}
	}

	Building* Board::GetGridBuilding(int col, int row, Building::Type theType) {
		for (auto&& p : mBuildingList) if (p.col == col && p.row == row && p.type == theType)return &p;
		return nullptr;
	}

	Plant* Board::GetGridPlant(int col, int row, PlantPriority priority) {
		if (col < 0 || col >= 9 || row < 0 || row >= 6)return nullptr;
		if (mApp->isBowling() && !isTeachinfBowling())return nullptr;
		GridPlantList list = GetGridPlantList(col, row);
		if (priority == PlantPriority::TOP)return list.mTop;
		if (priority == PlantPriority::BOTTOM)return list.mBottom;
		if (priority == PlantPriority::MIDDLE)return list.mMiddle;
		if (priority == PlantPriority::MAIN)return list.mMain;
		if (priority == PlantPriority::BITE) {
			if (list.mMiddle)return list.mMiddle;
			if (list.mMain)return list.mMain;
			if (list.mBottom)return list.mBottom;
			return nullptr;
		} else if (priority == PlantPriority::DIG) {
			if (list.mMain)return list.mMain;
			if (list.mBottom)return list.mBottom;
			return nullptr;
		} else if (priority == PlantPriority::BUNGEE || priority == PlantPriority::CATAPULT || priority == PlantPriority::ANY) {
			if (list.mTop)return list.mTop;
			if (list.mMain)return list.mMain;
			if (list.mMiddle)return list.mMiddle;
			if (list.mBottom)return list.mBottom;
			return nullptr;
		} else if (priority != PlantPriority::TOOL) {
			return nullptr;
		} else {
			if (list.mTop)return list.mTop;
			if (list.mMiddle)return list.mMiddle;
			if (list.mMain)return list.mMain;
			if (list.mBottom)return list.mBottom;
			return nullptr;
		}
	}

	bool Zombie::canGetPlant(Plant* that, ZombieHitType atkType) {
		if (mApp->isBowling() && atkType != ZombieHitType::VAULT)return false;
		if (that->isFlying())return false;
		if (that->type == Plant::Type::TANGLE_KELP)return false;
		if (!inWater && mBoard->gridType[that->col][that->row] == Board::GridType::POOL)return false;
		if (state == State::DIGGER_DIG)return that->type == Plant::Type::POTATO_MINE && that->state == Plant::State::NIL;
		if (that->type == Plant::Type::SPIKEWEED || that->type == Plant::Type::SPIKEROCK)return or (
			inrange(type,
				Type::GARGANTUAR,
				Type::GIGA_GARGANTUAR,
				Type::ZOMBIE
			),
			mBoard->gridType[that->col][that->row] == Board::GridType::POOL,
			mBoard->GetGridPlant(that->col, that->row, Plant::Type::FLOWER_POT)
			);
		if (atkType == ZombieHitType::SMASH) {
			if (inrange(that->type, Plant::Type::CHERRY_BOMB, Plant::Type::JALAPENO, Plant::Type::BLOVER, Plant::Type::SQUASH))return false;
			if (that->type == Plant::Type::DOOM_SHROOM || that->type == Plant::Type::ICE_SHROOM)return that->slept;
		}
		if (state == State::LADDER_RUN || state == State::LADDER_PLACING) {
			bool canLadder = false;
			if (inrange(that->type,
				Plant::Type::WALL_NUT,
				Plant::Type::TALL_NUT,
				Plant::Type::PUMPKIN
			))canLadder = true;
			if (mBoard->GetGridBuilding(that->col, that->row, Building::Type::LADDER))canLadder = false;
			if (atkType == ZombieHitType::BITE && canLadder)return false;
			if (atkType == ZombieHitType::LADDER && !canLadder)return false;
		}
		if (atkType == ZombieHitType::BITE) {
			Plant* target = mBoard->GetGridPlant(that->col, that->row, PlantPriority::BITE);
			if (target && target != that && canGetPlant(target, atkType))return false;
		}
		if (atkType == ZombieHitType::VAULT) {
			Plant* target = mBoard->GetGridPlant(that->col, that->row, PlantPriority::MAIN);
			if (target && target != that && canGetPlant(target, atkType))return false;
		}
		return true;
	}

	void Plant::RemoveEffects() {
		ParticleSystem* p = (*mApp)[mParticleSystemID];
		if (p)p->Kill();
		Anim* a;
		a = (*mApp)[mAnimID];
		if (a)a->Kill();
		a = (*mApp)[shooterHead[0]];
		if (a)a->Kill();
		a = (*mApp)[shooterHead[1]];
		if (a)a->Kill();
		a = (*mApp)[shooterHead[2]];
		if (a)a->Kill();
		a = (*mApp)[eye];
		if (a)a->Kill();
		a = (*mApp)[potatoGlow];
		if (a)a->Kill();
		a = (*mApp)[sleep];
		if (a)a->Kill();
	}

	void Plant::DropIZRemainSun() {
		if (type != Type::SUNFLOWER)return;
		for (int i = hp / 40; i >= 0; i--)mBoard->NewItem(mX + 5 * i, mY, Item::Type::SUN, Item::MovementState::FROM_PLANT);
	}

	void Plant::Smash() {
		if (isFlying())return;
		if (!slept) {
			if (inrange(type,
				Type::CHERRY_BOMB,
				Type::JALAPENO,
				Type::DOOM_SHROOM,
				Type::ICE_SHROOM
			) || (type == Type::POTATO_MINE && state != State::NIL)) {
				Suicide();
				return;
			}
		}
		if (type == Type::SQUASH && state != State::NIL) {
			return;
		}
		layer = 301008 + 10000 * row;
		smashed = true;
		vanishCountdown = 500;
		mApp->NewSampleF(Sample::Type::PLANT_SMASHED);
		RemoveEffects();
		Building* ladder = mBoard->GetGridBuilding(col, row, Building::Type::LADDER);
		if (ladder)ladder->Kill();
		if (mApp->isIZ())DropIZRemainSun();
	}

	void Zombie::SmashGrid(int col, int row) {
		for (auto p = mBoard->mPlantList.begin(); p != mBoard->mPlantList.end(); ++p) if (row == p->row && col == p->col && p->type != Plant::Type::SPIKEROCK)++mBoard->atePlantCount, p->Smash();
	}

	Building* Zombie::GetTargetIZBrain() {
		if (type == Type::BUNGEE_ZOMBIE)return nullptr;
		if (isFacingRight())return nullptr;
		Rect atkRect = GetAtkRect();
		if (state == State::POLE_VAULTING_RUN)atkRect = Rect(50 + mX, 0, 20, 115);
		if (type == Type::BALLOON_ZOMBIE)atkRect.mX += 15;
		if (atkRect.mX > 20)return nullptr;
		Building* target = mBoard->GetGridBuilding(0, row, Building::Type::BRAIN_IZ);
		if (target == nullptr)return nullptr;
		if (target->state == Building::State::BRAIN_SMASHED)return nullptr;
		return target;
	}

	void Zombie::UpdateSmash() {
		Rect zombieAttackRect = GetAtkRect();
		for (auto&& p : mBoard->mPlantList) if (row == p.row) {
			int rectOverlap = zombieAttackRect.IntersectWidth(p.GetDefRect());
			if (rectOverlap >= 20 && canGetPlant(&p, ZombieHitType::SMASH) && p.type != Plant::Type::SPIKEWEED && p.type != Plant::Type::SPIKEROCK) {
				SmashGrid(p.col, p.row);
				break;
			}
		}
		if (mApp->isIZ()) {
			Building* target = GetTargetIZBrain();
			if (target)target->Smash();
		}
	}

	void Building::Smash() {
		layer = 301000 + 10000 * row;
		state = State::BRAIN_SMASHED;
		mProp = 500;
		mApp->NewSampleF(Sample::Type::PLANT_SMASHED);
		mBoard->mLevelProp->IZTryAchieve(this);
	}

	HitRange Plant::GetHitRange() {
		switch (type) {
		case Type::CACTUS:if (state == State::CACTUS_DOWN)return HitRange::GROUND; else return HitRange::AIR;
		case Type::CHERRY_BOMB:
		case Type::JALAPENO:
		case Type::COB_CANNON:
		case Type::DOOM_SHROOM:return HitRange::GROUND | HitRange::AIR | HitRange::SUBMERGE | HitRange::DOG | HitRange::OFF_GROUND | HitRange::DYING | HitRange::UNDERGROUND;
		case Type::MELON_PULT:
		case Type::CABBAGE_PULT:
		case Type::KERNEL_PULT:
		case Type::WINTER_MELON:
		case Type::SQUASH:return HitRange::GROUND | HitRange::SUBMERGE | HitRange::DOG;
		case Type::POTATO_MINE:return HitRange::GROUND | HitRange::SUBMERGE | HitRange::DOG | HitRange::UNDERGROUND;
		case Type::PUFF_SHROOM:
		case Type::SEA_SHROOM:
		case Type::FUME_SHROOM:
		case Type::GLOOM_SHROOM:
		case Type::CHOMPER:return HitRange::GROUND | HitRange::DOG;
		case Type::CATTAIL:return HitRange::GROUND | HitRange::AIR | HitRange::DOG;
		case Type::TANGLE_KELP:return HitRange::GROUND | HitRange::SUBMERGE;
		case Type::GIANT_WALL_NUT:return HitRange::GROUND | HitRange::OFF_GROUND;
		default:return HitRange::GROUND;
		}
	}

	int Zombie::GetTeamRank() {
		if (type != Type::ZOMBIE_BOBSLED_TEAM)return -1;
		if (mPartners[0] == 0 && mPartners[1] == 0)return -1;
		if (mPartners[0] == 0)return 0;
		Zombie* leader = mBoard->mZombieList[mPartners[0]];
		if (leader)for (int i = 1; i <= 3; ++i)if (leader->mPartners[i] == GetID(*this))return i;
		return -1;
	}

	bool Zombie::inRange(HitRange range) {
		if (((range & HitRange::DYING) == HitRange::NIL) && isDying())return false;
		if (((range & HitRange::BETRAYED) == HitRange::NIL) && betray)return false;
		if (((range & HitRange::BETRAYED) != HitRange::NIL) && !betray)return false;
		if (type == Type::BUNGEE_ZOMBIE && state != State::BUNGEE_WAIT && state != State::BUNGEE_GRAB)return false;
		if (movementState == MovementState::AIRBORNE)return false;
		if (type == Type::ZOMBOSS) {
			Anim* theAnim = (*mApp)[mAnimId];
			if (state == State::ZOMBOSS_FALL && theAnim->updateRate < 0.5f)return false;
			if (state == State::ZOMBOSS_RISE && theAnim->updateRate > 0.5f)return false;
			if (state != State::ZOMBOSS_DOWN && state != State::ZOMBOSS_PREPARE_RISE && state != State::ZOMBOSS_BALL)return false;
		}
		if (type == Type::ZOMBIE_BOBSLED_TEAM && GetTeamRank() > 0)return  false;
		if (inrange(state,
			State::POLE_VAULTING_JUMP,
			State::IMP_THREW,
			State::DIGGER_JUMP,
			State::DIGGER_DOUBT,
			State::DIGGER_ATTRACTED,
			State::DOLPHIN_DIVE,
			State::DOLPHIN_JUMP,
			State::SNORKEL_DIVE,
			State::BALLOON_FALL,
			State::CORAL_RISE,
			State::BOBSLED_GETOFF,
			State::BACKUP_DANCER_SPAWN
		)) {
			return(range & HitRange::OFF_GROUND) != HitRange::NIL;
		}
		if (type != Type::ZOMBIE_BOBSLED_TEAM && type != Type::ZOMBOSS) {
			if (GetDefRect().mX > 800)return false;
		}
		if (type == Type::SNORKEL_ZOMBIE && inWater && !eating)return((range & HitRange::OFF_GROUND) != HitRange::NIL);
		else if (state == State::DIGGER_DIG)return((range & HitRange::UNDERGROUND) != HitRange::NIL);
		else if (isFlying())return((range & HitRange::AIR) != HitRange::NIL);
		else return((range & HitRange::GROUND) != HitRange::NIL);
	}

	void Board::Explode(int row, int x, int y, int r, int rowDiff, bool bomb, HitRange range) {
		for (auto p = mZombieList.begin(); p != mZombieList.end(); ++p) if (p->inRange(range) && (p->type == Zombie::Type::ZOMBOSS || (p->row - row >= -rowDiff && p->row - row <= rowDiff)) && p->GetDefRect().Intersects(x, y, r)) {
			if (bomb)p->Bombed();
			else p->Hitted(1800, HitType::SPLASH | HitType::NO_LEAVEBODY);
		}
		int thecol = GetCol(x, y);
		int therow = GetRow(x, y);
		if (thecol < 0)thecol = 0;
		if (therow < 0)therow = 0;
		for (auto p = mBuildingList.begin(); p != mBuildingList.end(); ++p) if (p->type == Building::Type::LADDER && p->row - therow >= -rowDiff && p->row - therow <= rowDiff && p->col - thecol >= -rowDiff && p->col - thecol <= rowDiff)p->Kill();
	}

	void Plant::Blow() {
		for(auto p = mBoard->mZombieList.begin(); p != mBoard->mZombieList.end();++p)if (!p->isDying() && (p->state == Zombie::State::BALLOON_FLY))p->blew = true;
		mApp->PlaySample(SOUND_BLOVER);
		mBoard->fogCountdown = 4000;
	}

	void Board::Shake(int x, int y) {
		shakeCountdown = 12;
		shakeOffset = Point<int>(x, y);
	}

	Zombie* Board::GetZomboss() {
		for (auto&& p : mZombieList)if (p.type == Zombie::Type::ZOMBOSS)return &p;
		return nullptr;
	}

	void GameApp::KillParticleSystem(ParticleSystem::Type type) {
		for (auto p = mAnimsLists->mParticlesLists->mParticleSystemList.begin(); p != mAnimsLists->mParticlesLists->mParticleSystemList.end(); ++p)if (p->type == type)p->Kill();
	}

	void Zombie::Zomboss_Killball(bool fireball) {
		if (fireball != zombossFireBall)return;
		Anim* ball = (*mApp)[zombossBall];
		if (!ball)return;
		mApp->NewParticleSystem(ParticleSystem::Type::ICEBALL_DEATH, 400000, ball->mPosition.xDiff + 80.0f, ball->mPosition.yDiff + 80.0f);
		ball->Kill();
		zombossBall = 0;
		mApp->KillParticleSystem(ParticleSystem::Type::ICEBALL_TRAIL);
	}

	void Plant::BurnRow() {
		HitRange range = GetHitRange(); 
		for (auto p = mBoard->mZombieList.begin(); p != mBoard->mZombieList.end(); ++p) {
			if (p->type != Zombie::Type::ZOMBOSS && p->row != row)continue;
			if (!p->inRange(range))continue;
			if (p->freezeCountdown > 0)p->BreakIce();
			if (p->slowCountdown > 0)p->AnimInitSpeed();
			p->Bombed();
		}
		for (auto p = mBoard->mBuildingList.begin(); p != mBoard->mBuildingList.end(); ++p)if (p->type == Building::Type::LADDER && p->row == row)p->Kill();
		Zombie* boss = mBoard->GetZomboss();
		if (boss && boss->zombossBallRow == row) {
			boss->Zomboss_Killball(false);
		}
	}

	void Plant::FreezeYard() {
		for (auto p = mBoard->mZombieList.begin(); p != mBoard->mZombieList.end(); ++p)p->Freezed();
		mBoard->poolFreezeCountdown = 300;
		ParticleSystem* poolEffect = (*mApp)[mBoard->particleSystem];
		if (poolEffect)poolEffect->freezed = true;
		Zombie* boss = mBoard->GetZomboss();
		if (boss) {
			boss->Zomboss_Killball(true);
		}
	}

	int Anim::GetPartIndex(const char* name) {
		/*
				int* ans = Anim_PartIndex::Get(type,name);
				if(ans)return *ans;
				for(int i = 0; i < reAnim->mTrackCount; ++i)if(strcmp(reAnim->mTracks[i].name,name)== 0)return *(ans = new int(i));
				return *(ans = new int(-1));
		 */
		for (int i = 0; i < reAnim->mTrackCount; ++i)if (strcmp(reAnim->mTracks[i].name, name) == 0)return i;
		return -1;
	}

	PartProp* Anim::GetPart(const char* name) {
		int i = GetPartIndex(name);
		if (i == -1)return nullptr;
		return reAnim->mTracks + i;
	}

	AnimAttachment* Anim::GetPartAttachment(const char* name) {
		int i = GetPartIndex(name);
		if (i == -1)return nullptr;
		return mAttachment + i;
	}

	void Anim::GetSegment(const char* name, int& fBegin, int& fSize) {
		if (reAnim->mTrackCount == 0) {
			fBegin = 0;
			fSize = 0;
			return;
		}
		PartProp* reanimatorTrack = GetPart(name);
		fBegin = 0;
		fSize = 1;
		int num2;
		for (num2 = 0; num2 < reanimatorTrack->mTransformCount; ++num2) {
			if (reanimatorTrack->mTransforms[num2].mFrame != -1.0f) {
				fBegin = num2;
				break;
			}
		}
		for (int i = reanimatorTrack->mTransformCount - 1; i >= num2; --i) {
			if (reanimatorTrack->mTransforms[i].mFrame != -1.0f) {
				fSize = i - (int)fBegin + 1;
				return;
			}
		}
	}

	void Anim::SetSegment(const char* name) {
		if (updateV >= 0.0f)updateRate = 0.0f;
		else updateRate = 0.9999999f;
		lastUpdateRate = -1.0f;
		GetSegment(name, initFrame, frameCount);
	}

	AnimFrameTime Anim::GetFrameTime() {
		int frameMax;
		if (inrange(loopType,
			LoopType::PLAY_ONCE_FULL_LAST_FRAME,
			LoopType::LOOP_FULL_LAST_FRAME,
			LoopType::PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD
		))frameMax = frameCount;
		else frameMax = frameCount - 1;
		float framePos = (float)initFrame + (float)frameMax * updateRate;
		AnimFrameTime ans;
		ans.mAnimFrameBeforeInt = (int)framePos;
		ans.mFraction = framePos - (float)ans.mAnimFrameBeforeInt;
		if (ans.mAnimFrameBeforeInt >= initFrame + frameCount - 1) {
			ans.mAnimFrameAfterInt = ans.mAnimFrameBeforeInt = initFrame + frameCount - 1;
		} else {
			ans.mAnimFrameAfterInt = ans.mAnimFrameBeforeInt + 1;
		}
		return ans;
	}

	FramePartProp Anim::GetCurrentFramePart(int index, const AnimFrameTime& time) {
		FramePartProp& frameBegin = reAnim->mTracks[index].mTransforms[(int)time.mAnimFrameBeforeInt];
		FramePartProp& frameEnd = reAnim->mTracks[index].mTransforms[(int)time.mAnimFrameAfterInt];
		FramePartProp ans;
		ans.mTransX = cut(frameBegin.mTransX, time.mFraction, frameEnd.mTransX);
		ans.mTransY = cut(frameBegin.mTransY, time.mFraction, frameEnd.mTransY);
		ans.mSkewX = cut(frameBegin.mSkewX, time.mFraction, frameEnd.mSkewX);
		ans.mSkewY = cut(frameBegin.mSkewY, time.mFraction, frameEnd.mSkewY);
		ans.mScaleX = cut(frameBegin.mScaleX, time.mFraction, frameEnd.mScaleX);
		ans.mScaleY = cut(frameBegin.mScaleY, time.mFraction, frameEnd.mScaleY);
		ans.mAlpha = cut(frameBegin.mAlpha, time.mFraction, frameEnd.mAlpha);
		ans.mFont = frameEnd.mFont;
		ans.mText = frameEnd.mText;
		ans.mImage = frameEnd.mImage;
		if (frameBegin.mFrame != -1.0f && frameEnd.mFrame == -1.0f && time.mFraction > 0.0f && mAttachment[index].mTruncateDisappearingFrames)ans.mFrame = -1.0f;
		else ans.mFrame = frameBegin.mFrame;
		return ans;
	}

	FramePartProp Anim::GetCurrentFramePart(float rate, const FramePartProp& begin, const FramePartProp& end) {
		FramePartProp ans;
		ans.mTransX = cut(begin.mTransX, rate, end.mTransX);
		ans.mTransY = cut(begin.mTransY, rate, end.mTransY);
		ans.mScaleX = cut(begin.mScaleX, rate, end.mScaleX);
		ans.mScaleY = cut(begin.mScaleY, rate, end.mScaleY);
		ans.mAlpha = cut(begin.mAlpha, rate, end.mAlpha);
		float targetX = end.mSkewX;
		float targetY = end.mSkewY;
		while (targetX > begin.mSkewX + 180.0f)targetX -= 360.0f;
		while (targetX < begin.mSkewX - 180.0f)targetX += 360.0f;
		while (targetY > begin.mSkewY + 180.0f)targetY -= 360.0f;
		while (targetY < begin.mSkewY - 180.0f)targetY += 360.0f;
		ans.mSkewX = cut(begin.mSkewX, rate, targetX);
		ans.mSkewY = cut(begin.mSkewY, rate, targetY);
		ans.mFrame = begin.mFrame;
		ans.mFont = begin.mFont;
		ans.mText = begin.mText;
		ans.mImage = begin.mImage;
		return ans;
	}

	FramePartProp Anim::GetCurrentFramePart(int index) {
		AnimFrameTime time = GetFrameTime();
		FramePartProp ans = GetCurrentFramePart(index, time);
		AnimAttachment attachment = mAttachment[index];
		if (ans.mFrame != -1.0f && attachment.mBlendCountdown > 0) {
			float theBlendFactor = (float)attachment.mBlendCountdown / (float)attachment.mBlendCountdownMax;
			ans = GetCurrentFramePart(theBlendFactor, ans, mAttachment[index].mFrame);
		}
		return ans;
	}

	void Anim::StartBlend(int blend) {
		for (int i = 0; i < reAnim->mTrackCount; ++i) {
			FramePartProp theFramePart = GetCurrentFramePart(i);
			if (theFramePart.mFrame != -1.0f) {
				mAttachment[i].mFrame = theFramePart;
				mAttachment[i].mBlendCountdown = blend;
				mAttachment[i].mBlendCountdownMax = blend;
				mAttachment[i].mFrame.mFont = nullptr;
				mAttachment[i].mFrame.mText = u8"\0";
				mAttachment[i].mFrame.mImage = nullptr;
			}
		}
	}

	void Anim::SetSegment(const char* name, LoopType loop, int blend, float speed) {
		if (blend > 0)StartBlend(blend);
		if (speed > 0.0f)updateV = speed;
		loopType = loop;
		loopCount = 0;
		SetSegment(name);
	}

	void Plant::Suicide() {
		int midX = mX + mW / 2;
		int midY = mY + mH / 2;
		HitRange range = GetHitRange();
		switch (type) {
		case Type::BLOVER:
		{
			if (state == State::EXPLODE)return;
			state = State::EXPLODE;
			Blow();
			return;
		}case Type::CHERRY_BOMB:
		{
			mApp->NewSampleF(Sample::Type::PLANT_CHERRYBOMB_EXPLODE);
			mApp->NewSampleF(Sample::Type::SUICIDE);
			mBoard->Explode(row, midX, midY, 115, 1, true, range);
			mApp->NewParticleSystem(ParticleSystem::Type::POWIE, 400000, (float)midX, (float)midY);
			mBoard->Shake(3, -4);
			Kill();
			return;
		}case Type::DOOM_SHROOM:
		{
			mApp->PlaySample(SOUND_DOOMSHROOM);
			mBoard->Explode(row, midX, midY, 250, 3, true, range);
			for (auto p = mBoard->mPlantList.begin(); p != mBoard->mPlantList.end(); ++p)if (p->col == col && p->row == row)p->Kill();
			mApp->NewParticleSystem(ParticleSystem::Type::DOOM, 400000, (float)midX, (float)midY);
			mBoard->NewCrater(col, row)->mProp = 18000;
			mBoard->Shake(3, -4);
			Kill();
			return;
		}case Type::JALAPENO:
		{
			mApp->NewSampleF(Sample::Type::PLANT_JALAPENO_EXPLODE);
			mApp->NewSampleF(Sample::Type::SUICIDE);
			mBoard->SetFire(row);
			mBoard->Shake(3, -4);
			BurnRow();
			if (mBoard->rowIceCountdown[row] > 20)mBoard->rowIceCountdown[row] = 20;
			Kill();
			return;
		}case Type::UMBRELLA_LEAF:
		{
			if (state == State::UMBRELLA_RISE || state == State::UMBRELLA_UP)return;
			state = State::UMBRELLA_RISE;
			propCountdown = 5; (*mApp)[mAnimID]->SetSegment(u8"anim_block", Anim::LoopType::PLAY_ONCE_AND_HOLD, 0, 22.0f);
			return;
		}case Type::ICE_SHROOM:
		{
			mApp->NewSampleF(Sample::Type::ZOMBIE_FREEZED);
			FreezeYard();
			mApp->NewParticleSystem(ParticleSystem::Type::ICE_TRAP, 400000, (float)midX, (float)midY);
			Kill();
			return;
		}case Type::POTATO_MINE:
		{
			mApp->PlaySample(SOUND_POTATO_MINE);
			mBoard->Explode(row, midX - 20, midY, 60, 0, false, range);
			int aRenderOrder = 307000 + 10000 * row;
			mApp->NewParticleSystem(ParticleSystem::Type::POTATO_MINE, 307000 + 10000 * row, (float)midX, (float)midY);
			mBoard->Shake(3, -4);
			Kill();
			return;
		}case Type::COFFEE_BEAN:
		{
			Plant* target = mBoard->GetGridPlant(col, row, PlantPriority::MAIN);
			if (target && target->slept)target->wakeupCountdown = 100;
			state = State::EXPLODE; (*mApp)[mAnimID]->SetSegment(u8"anim_crumble", Anim::LoopType::PLAY_ONCE_AND_HOLD, 20, 22.0f);
			mApp->NewSampleF(Sample::Type::PLANT_CRUMBLE);
		}
		}
	}

	void Attachment::RemoveAttacher(ParticleSystem::Type type) {
		if (!this)return;
		//ParticleSystemInfo info = gParticleSystemInfoList[(int)type];
		for (int i = 0; i < listSize; ++i) {
			if (Attachers[i].type != Attacher::Type::PARTICLESYSTEM)continue;
			ParticleSystem* p = (*gGameApp)[(ID<ParticleSystem>)Attachers[i].ID];
			if (p)p->Kill();
		}
	}

	Anim* Attachment::GetFirstAnim() {
		if (!this)return nullptr;
		for (int i = 0; i < listSize; ++i) {
			if (Attachers[i].type != Attacher::Type::ANIM)continue;
			Anim* ans = (*gGameApp)[(ID<Anim>)Attachers[i].ID];
			if (ans)return ans;
		}
		return nullptr;
	}

	void Zombie::KillBungeePlant() {
		if (state != State::BUNGEE_GRAB)return;
		Plant* p = mBoard->mPlantList[bungeeHandPlant];
		if (!p)return;
		if (p->bungeeProp == Plant::BungeeProp::GRABBED)p->bungeeProp = Plant::BungeeProp::NORMAL;
		else if (p->bungeeProp == Plant::BungeeProp::RAISE)p->Kill();
		bungeeHandPlant = 0;
	}

	void Zombie::SetAnimSpeed(float speed) {
		Anim* p = (*mApp)[mAnimId];
		if (p)p->updateV = isSlowed() ? speed * 0.5f : speed;
	}

	void Anim::SetPartImage(const char* name, Image* image) {
		GetPartAttachment(name)->mImage = image;
	}

	void Zombie::BombedTeam() {
		if (GetTeamRank() == -1)return;
		if (mPartners[0]) {
			Zombie* leader = mBoard->mZombieList[mPartners[0]];
			if (leader)leader->BombedTeam();
		} else {
			Bombed();
			for (int i = 1; i <= 3; ++i) {
				Zombie* p = mBoard->mZombieList[mPartners[i]];
				if (p)p->Bombed();
			}
		}
	}

	void Zombie::Bombed() {
		if (vanished || state == State::ASHED)return;
		if (hp >= 1800 || type == Type::ZOMBOSS) {
			Hitted(1800, HitType::SPLASH | HitType::NO_LEAVEBODY);
			return;
		}
		if (type == Type::SQUASH && !haveHead && (*mApp)[addHead]) {
			(*mApp)[addHead]->Kill();
			addHead = 0;
		}
		if (freezeCountdown > 0)BreakIce();
		if (butterCountdown > 0)butterCountdown = 0;
		if ((*mApp)[mAttachmentID])(*mApp)[mAttachmentID]->RemoveAttacher(ParticleSystem::Type::ZOMBONI_SMOKE);
		KillBungeePlant();
		if (inrange(state,
			State::DYING,
			State::POLE_VAULTING_JUMP,
			State::IMP_THREW,
			State::CORAL_RISE,
			State::BACKUP_DANCER_SPAWN,
			State::DOLPHIN_DIVE,
			State::DOLPHIN_JUMP,
			State::DOLPHIN_SPRINT,
			State::SNORKEL_DIVE,
			State::DIGGER_DIG,
			State::DIGGER_DOUBT,
			State::DIGGER_JUMP,
			State::DIGGER_ATTRACTED,
			State::MOWERED
		) || inWater) {
			KillWithItem();
		} else if (inrange(type,
			Type::BUNGEE_ZOMBIE,
			Type::YETI_ZOMBIE,
			Type::PEASHOOTER,
			Type::WALL_NUT,
			Type::JALAPENO,
			Type::GATLING_PEA,
			Type::SQUASH,
			Type::TALL_NUT
		) || GetTeamRank() != -1 || isFlying() || !haveHead) {
			SetAnimSpeed(0.0f);
			Anim* head = (*mApp)[addHead];
			if (head)head->updateV = 0.0f;
			state = State::ASHED;
			propCountdown = 300;
			lastHittedCount = 0;
			DropItem();
			if (type == Type::BALLOON_ZOMBIE) {
				Anim* p = (*mApp)[(*mApp)[mAnimId]->GetPartAttachment(u8"hat")->mAttachmentID]->GetFirstAnim();
				if (p)p->updateV = 0.0f;
			}
		} else {
			Anim::Type theReanimationType = Anim::Type::ZOMBIE_CHARRED;
			float theX = x + 22.0f;
			float theY = y - 10.0f;
			switch (type) {
			case Type::BALLOON_ZOMBIE:theY += 31.0f; break;
			case Type::IMP:theX -= 6.0f; theReanimationType = Anim::Type::ZOMBIE_CHARRED_IMP; break;
			case Type::DIGGER_ZOMBIE:theReanimationType = Anim::Type::ZOMBIE_CHARRED_DIGGER; if (isFacingRight())theX += 14.00f; break;
			case Type::ZOMBONI:theX += 61.0f; theY -= 16.0f; theReanimationType = Anim::Type::ZOMBIE_CHARRED_ZOMBONI; break;
			case Type::CATAPULT_ZOMBIE:theX -= 36.0f; theY -= 20.0f; theReanimationType = Anim::Type::ZOMBIE_CHARRED_CATAPULT; break;
			case Type::GARGANTUAR:
			case Type::GIGA_GARGANTUAR:theX -= 15.0f; theY -= 10.0f; theReanimationType = Anim::Type::ZOMBIE_CHARRED_GARGANTUAR; break;
			}
			Anim* charred = mApp->NewAnim(theReanimationType, layer, theX, theY);
			charred->updateV *= rand(0.9f, 1.1f);
			if (state == State::DIGGER_WALKLEFT)charred->SetSegment(u8"anim_crumble_noaxe");
			else if (type == Type::DIGGER_ZOMBIE)charred->SetSegment(u8"anim_crumble");
			else if ((type == Type::GARGANTUAR || type == Type::GIGA_GARGANTUAR) && !stage1) {
				charred->SetPartImage(u8"impblink", IMAGE_BLANK);
				charred->SetPartImage(u8"imphead", IMAGE_BLANK);
			}
			if (size != 1.0f) {
				charred->mPosition.xStrech = charred->mPosition.yStrech = size;
				charred->mPosition.xDiff += (20.0f - size * 20.0f);
				charred->mPosition.yDiff += (20.0f - size * 20.0f);
			}
			if (isFacingRight()) {
				charred->mPosition.xStrech = -charred->mPosition.xStrech;
				charred->mPosition.xDiff += size * 60.0f;
			}
			KillWithItem();
		}
		if (type == Type::ZOMBIE_BOBSLED_TEAM)BombedTeam();
		return;
	}

	void Zombie::Slowed(int t) {
		if (!isSlowable())return;
		if (slowCountdown == 0)mApp->NewSampleF(Sample::Type::ZOMBIE_FREEZED);
		if (t > slowCountdown)slowCountdown = t;
		AnimInitSpeed();
	}

	void Zombie::StopUniqueSample() {
		if (type == Type::DANCING_ZOMBIE || type == Type::BACKUP_DANCER) {
			bool unique = true;
			if (mBoard) {
				for (auto&& p : mBoard->mZombieList) {
					if (and (
						p.haveHead,
						!p.isDying(),
						p.isOnBoard(),
						p.type == Type::DANCING_ZOMBIE || p.type == Type::BACKUP_DANCER
						)) {
						unique = false;
						break;
					}
				}
			}
			if (unique)mApp->mSampleManagers->StopSample(Sample::Type::ZOMBIE_MJ_INIT);
		}
		if (!haveUniqueSample)return;
		haveUniqueSample = false;
		if (type == Type::JACK_IN_THE_BOX_ZOMBIE)mApp->mSampleManagers->StopSample(Sample::Type::ZOMBIE_JACK_MUSIC_BOX);
		else if (type == Type::DIGGER_ZOMBIE)mApp->mSampleManagers->StopSample(Sample::Type::ZOMBIE_DIGGER_DIG);
	}

	void Zombie::StartUniqueSample() {
		if (haveUniqueSample)return;
		if (state == State::JACK_CLOCKWORK && haveHead) {
			mApp->NewSampleF(Sample::Type::ZOMBIE_JACK_MUSIC_BOX);
			haveUniqueSample = true;
		} else if (state == State::DIGGER_DIG) {
			mApp->NewSampleF(Sample::Type::ZOMBIE_DIGGER_DIG);
			haveUniqueSample = true;
		}
	}

	void Zombie::Freezed() {
		bool slown = false;
		if (slowCountdown > 0 || freezeCountdown != 0)slown = true;
		Slowed(2000);
		if (!isFreezeable())return;
		if (inWater)freezeCountdown = 300;
		else if (slown)freezeCountdown = rand(300, 401);
		else freezeCountdown = rand(400, 601);
		StopUniqueSample();
		if (type == Type::BALLOON_ZOMBIE) {
			Anim* p = (*mApp)[(*mApp)[mAnimId]->GetPartAttachment(u8"hat")->mAttachmentID]->GetFirstAnim();
			if (p)p->updateV = 0.0f;
		} else if (state == State::ZOMBOSS_BALL)mApp->KillParticleSystem(ParticleSystem::Type::ZOMBIE_BOSS_FIREBALL);
		Hitted(20, HitType::SPLASH | HitType::NO_FLASH);
		AnimInitSpeed();
	}

	bool Zombie::isSlowed() {
		if (slowCountdown > 0)return true;
		if (type == Type::DANCING_ZOMBIE) {
			for (int i = 1; i <= 4; i++) {
				Zombie* p = mBoard->mZombieList[mPartners[i]];
				if (p && p->slowCountdown > 0)return true;
			}
		} else if (type == Type::BACKUP_DANCER) {
			Zombie* leader = mBoard->mZombieList[mPartners[0]];
			if (leader)return leader->isSlowed();
		}
		return false;
	}

	bool Zombie::isStopped() {
		if (eating || freezeCountdown > 0 || butterCountdown > 0 ||
			inrange(state,
				State::JACK_SURPRISE,
				State::NEWSPAPER_DASE,
				State::GARGANTUAR_THROW,
				State::GARGANTUAR_SMASH,
				State::CATAPULT_ATTACK,
				State::CATAPULT_PREPARE,
				State::DIGGER_JUMP,
				State::DIGGER_DOUBT,
				State::DIGGER_ATTRACTED,
				State::DIGGER_DASE,
				State::MJ_TURN,
				State::MJ_PREPARE,
				State::MJ_SUMMON,
				State::BACKUP_DANCER_SPAWN,
				State::IMP_THREW,
				State::IMP_LANDDING,
				State::LADDER_PLACING,
				State::MJ_DANCE1,
				State::MJ_DANCE2,
				State::MJ_DANCE3,
				State::MJ_DANCE4,
				State::MJ_DANCE5
			) || inrange(movementState,
				MovementState::ENTER_CHIMNEY,
				MovementState::AIRBORNE,
				MovementState::AQ
			) || inrange(type,
				Type::BUNGEE_ZOMBIE,
				Type::ZOMBOSS
			))return true;
		if (type == Type::DANCING_ZOMBIE) {
			for (int i = 1; i <= 4; i++) {
				Zombie* p = mBoard->mZombieList[mPartners[i]];
				if (p && (p->eating || p->freezeCountdown > 0 || p->butterCountdown > 0))return true;
			}
		} else if (type == Type::BACKUP_DANCER) {
			Zombie* leader = mBoard->mZombieList[mPartners[0]];
			if (leader)return leader->isStopped();
		}
		return false;
	}

	void Zombie::AnimInitSpeed() {
		if (!isOnBoard())return;
		Anim* reanimation = (*mApp)[mAnimId];
		if (!reanimation)return;
		if (freezeCountdown > 0 || butterCountdown > 0 || (ateGarlic && ateGarlicTime < 170))return SetAnimSpeed(0.0f);
		if (state == State::SNORKEL_RISE || state == State::SNORKEL_FALL || isDying())return SetAnimSpeed(mAnimSpeed);
		if (eating) {
			if (inrange(type,
				Type::POLE_VAULTING_ZOMBIE,
				Type::BALLOON_ZOMBIE,
				Type::IMP,
				Type::DIGGER_ZOMBIE,
				Type::JACK_IN_THE_BOX_ZOMBIE,
				Type::SNORKEL_ZOMBIE,
				Type::YETI_ZOMBIE
			))return SetAnimSpeed(20.0f);
			else return SetAnimSpeed(36.0f);
		} else {
			if (or (
				isStopped(),
				GetTeamRank() != -1,
				type == Type::CATAPULT_ZOMBIE,
				state == State::DOLPHIN_SPRINT,
				state == State::SNORKEL_SWIM
				))return SetAnimSpeed(mAnimSpeed);
			Anim* p = (*mApp)[mAnimId];
			PartProp* ground = p->GetPart(u8"_ground");
			if (!ground)return;
			float len = ground->mTransforms[p->initFrame + p->frameCount - 1].mTransX - ground->mTransforms[p->initFrame].mTransX;
			if (len < 0.000001f)return;
			SetAnimSpeed(v * (float)p->frameCount * 47.0f / len / size);
		}
	}

	float Anim::GetZombieDX() {
		PartProp* ground = GetPart(u8"_ground");
		if (!ground)return 0.0f;
		AnimFrameTime time = GetFrameTime();
		return(ground->mTransforms[time.mAnimFrameAfterInt].mTransX - ground->mTransforms[time.mAnimFrameBeforeInt].mTransX) * 0.01f * updateV;
	}

	float Anim::GetZombieDX(PartProp* ground) {
		AnimFrameTime time = GetFrameTime();
		return(ground->mTransforms[time.mAnimFrameAfterInt].mTransX - ground->mTransforms[time.mAnimFrameBeforeInt].mTransX) * 0.01f * updateV;
	}

	bool Anim::isRateEqls(float rate) {
		if (frameCount == 0)return false;
		if (lastUpdateRate < 0.0f)return false;
		if (updateV <= 0.0f)return false;
		if (updateRate >= lastUpdateRate) {
			if (rate >= lastUpdateRate && rate < updateRate)return true;
		} else {
			if (rate >= lastUpdateRate || rate < updateRate)return true;
		}
		return false;
	}

	void Zombie::Move() {
		if (isStopped())return;
		Anim* reanimation = (*mApp)[mAnimId];
		if (reanimation) {
			float xdiff;
			if (isPogoJumping() || inrange(state,
				State::BALLOON_FLY,
				State::DOLPHIN_SPRINT,
				State::SNORKEL_SWIM
			) || type == Type::CATAPULT_ZOMBIE)xdiff = isSlowed() ? v * 0.4f : v;
			else if (type == Type::ZOMBONI || inrange(state,
				State::DIGGER_DIG,
				State::DOLPHIN_JUMP,
				State::POLE_VAULTING_JUMP,
				State::SNORKEL_DIVE
			) || GetTeamRank() != -1)xdiff = v;
			else {
				Anim* p = (*mApp)[mAnimId];
				PartProp* ground = p->GetPart(u8"_ground");
				if (ground)xdiff = reanimation->GetZombieDX(ground);
				else xdiff = isSlowed() ? v * 0.4f : v;
			}
			if (isFacingRight() || state == State::MJ_ENTER)x += xdiff;
			else x -= xdiff;
			if (type == Type::FOOTBALL_ZOMBIE && spawnWave != WAVE_WINNER) {
				if (reanimation->isRateEqls(0.03f))mApp->NewParticleSystem(ParticleSystem::Type::DUST_FOOT, layer - 1, (float)(mX + 81), (float)(mY + 106));
				else if (reanimation->isRateEqls(0.61f))mApp->NewParticleSystem(ParticleSystem::Type::DUST_FOOT, layer - 1, (float)(mX + 87), (float)(mY + 110));
			} else if (state == State::POLE_VAULTING_RUN) {
				if (reanimation->isRateEqls(0.16f))mApp->NewParticleSystem(ParticleSystem::Type::DUST_FOOT, layer - 1, (float)(mX + 81), (float)(mY + 106));
				else if (reanimation->isRateEqls(0.67f))mApp->NewParticleSystem(ParticleSystem::Type::DUST_FOOT, layer - 1, (float)(mX + 87), (float)(mY + 110));
			}
		} else if (state == State::POLE_VAULTING_JUMP || state == State::DIGGER_DIG || inrange(type,
			Type::DANCING_ZOMBIE,
			Type::BACKUP_DANCER,
			Type::ZOMBIE_BOBSLED_TEAM,
			Type::POGO_ZOMBIE,
			Type::DOLPHIN_RIDER_ZOMBIE,
			Type::BALLOON_ZOMBIE
		) || (type == Type::SNORKEL_ZOMBIE && inWater) || (noAnimShakeFrameIndex >= 0 && noAnimShakeFrameIndex) || (noAnimShakeFrameIndex >= 6 && noAnimShakeFrameIndex <= 8)) {
			float xdiff = isSlowed() ? v * 0.4f : v;
			if (isFacingRight())x += xdiff;
			else x -= xdiff;
		}
	}

	void Zombie::BreakIce() {
		freezeCountdown = 0;
		if (type == Type::BALLOON_ZOMBIE) {
			Anim* reanimation = (*mApp)[mAnimId];
			Anim* p = (*mApp)[(*mApp)[mAnimId]->GetPartAttachment(u8"hat")->mAttachmentID]->GetFirstAnim();
			if (p) {
				p->updateV = p->reAnim->mFPS;
			}
		}
		AnimInitSpeed();
		StartUniqueSample();
	}

	bool Zombie::isTangleTarget() {
		if (!BasicProp(mBoard->yard).havePool)return false;
		if (movementState == MovementState::DRAGGED_UNDER)return true;
		return false;
		for (auto&& p : mBoard->mPlantList)if (p.type == Plant::Type::TANGLE_KELP && p.mTargetZombieID == GetID(this))return true;
		return false;
	}

	Zombie* Zombie::GetTargetZombie() {
		if (state == State::DIGGER_DIG)return nullptr;
		Rect atk = GetAtkRect();
		for (auto&& p : mBoard->mZombieList) {
			if (betray != p.betray && !p.isFlying() && !inrange(p.state,
				State::DIGGER_DIG,
				State::BUNGEE_AIM,
				State::BUNGEE_FALL,
				State::BUNGEE_RISE
			) && p.movementState != MovementState::AIRBORNE && !p.isDying() && row == p.row) {
				int cover = atk.IntersectWidth(p.GetDefRect());
				if (cover >= 20 || (cover >= 0 && p.eating))return &p;
			}
		}
		return nullptr;
	}

	Plant* Zombie::GetTargetPlant(ZombieHitType atktype) {
		Rect atk = GetAtkRect();
		for (auto&& p : mBoard->mPlantList) if (row == p.row && atk.IntersectWidth(p.GetDefRect()) >= 20 && canGetPlant(&p, atktype))return &p;
		return nullptr;
	}

	void Zombie::Eat(Building* that) {
		StartEating();
		if (--that->mProp <= 0) {
			mApp->PlaySample(SOUND_GULP);
			that->Kill();
			mBoard->mLevelProp->IZTryAchieve(that);
		}
	}

	void Zombie::Eat(Zombie* that) {
		that->Hitted(4, HitType::SIDE | HitType::NO_FLASH);
		StartEating();
		if (that->hp <= 0)mApp->PlaySample(SOUND_GULP);
	}

	void Card::Init(Type rtype, Type itype) {
		type = rtype;
		imitaterType = itype;
		CDAcc = 0;
		CDTarget = 0;
		inCD = false;
		useable = true;
		Type thetype = (rtype == Type::IMITATER ? itype : rtype);
		if (or (
			mApp->isBejeveled(),
			mApp->isLS(),
			mApp->isIZ(),
			mApp->isVB(),
			mApp->isHammer(),
			mApp->isSurvival() && mBoard->mLevelProp->flags > 0
			))return;
		if (BasicProp(thetype).CD >= 5000) {
			CDTarget = 3500;
			inCD = true;
			useable = false;
		} else if (BasicProp(thetype).CD >= 3000) {
			CDTarget = 2000;
			inCD = true;
			useable = false;
		}
	}

	PlantMatrix LevelProp::GetPlantMatrix() {
		PlantMatrix ans;
		memset(&ans, -1, sizeof(PlantMatrix));
		for (auto&& p : mBoard->mPlantList)ans.val[p.col][p.row] = p.type;
		ans.mParent = this;
		return ans;
	}

	int PlantMatrix::GetMatchLength(int col, int row, bool vertical) {
		if (val[col][row] == Plant::Type::NIL)return 0;
		int ans = 1;
		Plant::Type t = val[col][row];
		if (vertical)while (row < 4 && val[col][++row] == t)++ans;
		else while (col < 8 && val[++col][row] == t)++ans;
		return ans;
	}

	bool PlantMatrix::isHaveMatch() {
		for (int i = 0; i < 9; i++)for (int j = 0; j < 3; j++)if (GetMatchLength(i, j, true) >= 3)return true;
		for (int i = 0; i < 7; i++)for (int j = 0; j < 5; j++)if (GetMatchLength(i, j, false) >= 3)return true;
		return false;
	}

	bool PlantMatrix::CheckPossibleMove(int col, int row) {
		if (col < 0 || col>7 || row < 0 || row>3)return false;
		if (mParent->bejeveledCrater[col][row] || mParent->bejeveledCrater[col + 1][row] || mParent->bejeveledCrater[col][row + 1] || mParent->bejeveledCrater[col + 1][row + 1])return false;
		if (val[col][row] == val[col][row + 1] && val[col][row] == val[col + 1][row] && val[col][row] == val[col + 1][row + 1])return false;
		if (val[col][row] == Plant::Type::NIL || val[col + 1][row] == Plant::Type::NIL || val[col][row + 1] == Plant::Type::NIL || val[col + 1][row + 1] == Plant::Type::NIL)return false;
		Plant::Type t;
		t = val[col][row];
		val[col][row] = val[col][row + 1];
		val[col][row + 1] = val[col + 1][row + 1];
		val[col + 1][row + 1] = val[col + 1][row];
		val[col + 1][row] = t;
		bool ans = isHaveMatch();
		t = val[col][row];
		val[col][row] = val[col + 1][row];
		val[col + 1][row] = val[col + 1][row + 1];
		val[col + 1][row + 1] = val[col][row + 1];
		val[col][row + 1] = t;
		return ans;
	}

	bool PlantMatrix::CheckPossibleMove(int col, int row, bool vertical) {
		int col2, row2;
		if (vertical) {
			col2 = col;
			row2 = row + 1;
			if (col < 0 || col2>8 || row < 0 || row2>4)return false;
		} else {
			col2 = col + 1;
			row2 = row;
			if (col < 0 || col2>8 || row < 0 || row2>4)return false;
		}
		if (mParent->bejeveledCrater[col][row] || mParent->bejeveledCrater[col2][row2] || val[col][row] == val[col2][row2] || val[col][row] == Plant::Type::NIL || val[col2][row2] == Plant::Type::NIL)return false;
		Plant::Type t;
		t = val[col][row];
		val[col][row] = val[col2][row2];
		val[col2][row2] = t;
		bool ans = isHaveMatch();
		t = val[col][row];
		val[col][row] = val[col2][row2];
		val[col2][row2] = t;
		return ans;
	}

	bool PlantMatrix::CheckPossibleMove(bool twist) {
		if (twist) {
			for (int i = 0; i < 9; i++)for (int j = 0; j < 4; j++)if (CheckPossibleMove(i, j, true))return true;
			for (int i = 0; i < 8; i++)for (int j = 0; j < 5; j++)if (CheckPossibleMove(i, j, false))return true;
		} else {
			for (int i = 0; i < 9; i++)for (int j = 0; j < 5; j++)if (CheckPossibleMove(i, j))return true;
		}
		return false;
	}

	void LevelProp::BejeveledCheckStuck() {
		if (state != State::NIL || mBoard->isLevelEnding())return;
		if (!GetPlantMatrix().CheckPossibleMove(mApp->level == GameApp::Level::Type::BEJEVELED2)) {
			state = State::BEGHOULED_NO_MATCHES;
			mainCountdown = 500;
			mBoard->SetBoardText(u8"[ADVICE_BEGHOULED_NO_MOVES]", BoardText::Type::HINT_FAST, Board::AdviceType::BEGHOULED_NO_MOVES);
		}
	}

	bool LevelProp::haveCrater() {
		for (int i = 0; i < 9; i++)for (int j = 0; j < 5; j++)if (bejeveledCrater[i][j])return true;
		return false;
	}

	void Card::Active() {
		useable = true;
	}

	void Card::DeActive() {
		useable = false;
		CDAcc = 0;
		CDTarget = 0;
		inCD = false;
	}

	void LevelProp::UpdateCraterCard() {
		if (mBoard->mSlot->SlotCount != 5 || mBoard->mSlot->mCards[4].type != Card::Type::BEGHOULED_CRATER)return;
		if (haveCrater())mBoard->mSlot->mCards[4].Active();
		else mBoard->mSlot->mCards[4].DeActive();
	}

	void LevelProp::ZombieAtePlant(Zombie* z, Plant* p) {
		if (!mApp->isBejeveled())return;
		bejeveledCrater[p->col][p->row] = true;
		if (mBoard->mSlot->SlotCount == 4) {
			mBoard->mSlot->mCards[4].Init(Card::Type::BEGHOULED_CRATER);
			mBoard->mSlot->SlotCount = 5;
			mBoard->SetBoardText(u8"[ADVICE_BEGHOULED_USE_CRATER_1]", BoardText::Type::HINT_FAST, Board::AdviceType::BEGHOULED_USE_CRATER_1);
		}
		BejeveledCheckStuck();
		UpdateCraterCard();
	}

	void Zombie::Eat(Plant* that) {
		if (state == State::MJ_ENTER)propCountdown = 1;
		if (ateGarlic)return;
		if (mBoard->GetGridBuilding(that->col, that->row, Building::Type::LADDER) && type != Type::DIGGER_ZOMBIE) {
			StopEating();
			if (movementState == MovementState::NIL && lastLadderCol != that->col) {
				movementState = MovementState::ENTER_LADDER;
				lastLadderCol = that->col;
			}
			return;
		}
		StartEating();
		if ((inrange(that->type,
			Plant::Type::JALAPENO,
			Plant::Type::CHERRY_BOMB,
			Plant::Type::DOOM_SHROOM,
			Plant::Type::ICE_SHROOM,
			Plant::Type::HYPNO_SHROOM
		) || inrange(that->state,
			Plant::State::FLOWERPOT_INVULNERABLE,
			Plant::State::LILYPAD_INVULNERABLE,
			Plant::State::SQUASH_LOOK,
			Plant::State::SQUASH_PREPARE
		)) && !that->slept)return;
		if (that->type == Plant::Type::POTATO_MINE && that->state != Plant::State::NIL)return;
		bool flag = false;
		if (that->type == Plant::Type::BLOVER || (that->type == Plant::Type::ICE_SHROOM && !that->slept))that->Suicide();
		if (mApp->isIZ() && that->type == Plant::Type::SUNFLOWER && (that->hp / 40 > (that->hp - 4) / 40 || that->hp - 4 == 0))mBoard->NewItem(that->mX, that->mY, Item::Type::SUN, Item::MovementState::DROPPED);
		that->hp -= 4;
		that->eatenCountdown = 50;
		if (mApp->isIZ() && lastHittedCount < -500 && inrange(that->type,
			Plant::Type::WALL_NUT,
			Plant::Type::TALL_NUT,
			Plant::Type::PUMPKIN
		))that->hp -= 4;
		if (that->hp <= 0) {
			mApp->PlaySample(SOUND_GULP);
			++mBoard->atePlantCount;
			that->Kill();
			mBoard->mLevelProp->ZombieAtePlant(this, that);
			if (mBoard->adventureLevelRank >= 2 && mBoard->adventureLevelRank <= 4 && mApp->isFirseTimeAdventure() && that->col > 4 && mBoard->mPlantList.mSize < 15 && that->type == Plant::Type::PEASHOOTER) {
				mBoard->SetBoardText(u8"[ADVICE_PEASHOOTER_DIED]", BoardText::Type::HINT_FAST, Board::AdviceType::PEASHOOTER_DIED);
			}
		}

	}

	void Zombie::AnimSetSegment(const char* name, Anim::LoopType loop, int blend, float speed) {
		Anim* a = (*mApp)[mAnimId];
		if (!a)return;
		a->SetSegment(name, loop, blend, speed);
		if (speed != 0.0f)mAnimSpeed = speed;
		AnimInitSpeed();
	}

	void Anim::SetPartGroup(const char* name, int _group) {
		size_t len = strlen(name);
		for (int i = 0; i < reAnim->mTrackCount; ++i)if (strlen(reAnim->mTracks[i].name) >= len && strncmp(reAnim->mTracks[i].name, name, len) == 0)mAttachment[i].group = _group;
	}

	void Zombie::ShowDoorArm(bool show) {
		Anim* a = (*mApp)[mAnimId];
		if (!a)return;
		int group_hand;
		int group_arm;
		int group_door;
		if (show) {
			group_arm = -1;
			group_door = 0;
		} else {
			group_arm = 0;
			group_door = -1;
		}
		if (haveArm) {
			group_hand = group_arm;
		} else {
			group_hand = -1;
		}
		a->SetPartGroup(u8"Zombie_outerarm_upper", group_arm);
		a->SetPartGroup(u8"anim_innerarm", group_arm);
		a->SetPartGroup(u8"Zombie_outerarm_screendoor", group_door);
		a->SetPartGroup(u8"Zombie_innerarm_screendoor", group_door);
		a->SetPartGroup(u8"Zombie_innerarm_screendoor_hand", group_door);
		a->SetPartGroup(u8"Zombie_outerarm_lower", group_hand);
		a->SetPartGroup(u8"Zombie_outerarm_hand", group_hand);
	}

	void Zombie::StartEating() {
		if (eating)return;
		eating = true;
		if (state == State::DIGGER_DIG)return;
		if (state == State::LADDER_RUN) {
			AnimSetSegment(u8"anim_laddereat", Anim::LoopType::LOOP, 20);
			return;
		}
		if (state == State::NEWSPAPER_ANGRY) {
			AnimSetSegment(u8"anim_eat_nopaper", Anim::LoopType::LOOP, 20);
			return;
		}
		if (type != Type::SNORKEL_ZOMBIE) {
			AnimSetSegment(u8"anim_eat", Anim::LoopType::LOOP, 20);
		}
		if (shieldType == ShieldType::SCREEN_DOOR) {
			ShowDoorArm(false);
		}
	}

	void Zombie::ResetSpeed() {
		BasicProp(type).Func_resetSpeed(this);
		AnimInitSpeed();
	}

	void Zombie::AnimStartWalk(int blend) {
		Anim* a = (*mApp)[mAnimId];
		if (!a)return;
		ResetSpeed();
		if (state == State::LADDER_RUN) {
			AnimSetSegment(u8"anim_ladderwalk", Anim::LoopType::LOOP, blend);
		} else if (state == State::NEWSPAPER_ANGRY) {
			AnimSetSegment(u8"anim_walk_nopaper", Anim::LoopType::LOOP, blend);
		} else if (inWater && movementState != MovementState::ENTER_WATER && movementState != MovementState::LEAVE_WATER && a->GetPart(u8"anim_swim")) {
			AnimSetSegment(u8"anim_swim", Anim::LoopType::LOOP, blend);
		} else if (inrange(type,
			Type::ZOMBIE,
			Type::CONEHEAD_ZOMBIE,
			Type::BUCKETHEAD_ZOMBIE
		) && mBoard->dance) {
			AnimSetSegment(u8"anim_dance", Anim::LoopType::LOOP, blend);
		} else {
			int num = rand(2);
			if (type == Type::ZOMBONI || type == Type::FLAG_ZOMBIE)num = 0;
			if (num == 0 && a->GetPart(u8"anim_walk2")) {
				AnimSetSegment(u8"anim_walk2", Anim::LoopType::LOOP, blend);
			} else if (a->GetPart(u8"anim_walk")) {
				AnimSetSegment(u8"anim_walk", Anim::LoopType::LOOP, blend);
			}
		}
	}

	void Zombie::StopEating() {
		if (!eating)return;
		eating = false;
		Anim* a = (*mApp)[mAnimId];
		if (state == State::DIGGER_DIG)return;
		if (a && type != Type::SNORKEL_ZOMBIE) {
			AnimStartWalk(20);
		}
		if (shieldType == ShieldType::SCREEN_DOOR) {
			ShowDoorArm(true);
		}
		AnimInitSpeed();
	}

	void Zombie::UpdateEat() {
		if (inrange(type,
			Type::BUNGEE_ZOMBIE,
			Type::GARGANTUAR,
			Type::GIGA_GARGANTUAR,
			Type::ZOMBONI,
			Type::CATAPULT_ZOMBIE,
			Type::ZOMBOSS
		) || inrange(state,
			State::POLE_VAULTING_JUMP,
			State::POLE_VAULTING_RUN,
			State::NEWSPAPER_DASE,
			State::DIGGER_JUMP,
			State::DIGGER_DOUBT,
			State::DIGGER_ATTRACTED,
			State::DIGGER_DASE,
			State::CORAL_RISE,
			State::IMP_THREW,
			State::IMP_LANDDING,
			State::BACKUP_DANCER_SPAWN,
			State::MJ_PREPARE,
			State::MJ_TURN,
			State::MJ_SUMMON,
			State::DOLPHIN_WALK,
			State::DOLPHIN_WALK_EMPTY_HAND,
			State::DOLPHIN_DIVE,
			State::DOLPHIN_SPRINT,
			State::DOLPHIN_JUMP,
			State::SNORKEL_DIVE,
			State::SNORKEL_WALK,
			State::LADDER_PLACING
		) || inrange(movementState,
			MovementState::AIRBORNE,
			MovementState::ENTER_LADDER,
			MovementState::ENTER_WATER,
			MovementState::LEAVE_WATER
			, MovementState::LEAVE_LADDER
		) || isPogoJumping() || GetTeamRank() != -1 || isTangleTarget() || !haveHead || isFlying())return;
		if (existTime % (slowCountdown > 0 ? 8 : 4) != 0)return;
		Zombie* zombie = GetTargetZombie();
		if (zombie) {
			Eat(zombie);
			return;
		}
		if (!betray) {
			Plant* plant = GetTargetPlant(ZombieHitType::BITE);
			if (plant) {
				Eat(plant);
				return;
			}
		}
		if (mApp->isIZ()) {
			Building* building = GetTargetIZBrain();
			if (building) {
				Eat(building);
				return;
			}
		}
		if (eating)StopEating();
	}

	void Anim::Update() {
		if (frameCount == 0 || vanished)return;
		lastUpdateRate = updateRate;
		updateRate += 0.01f * updateV / (float)frameCount;
		if (updateV > 0.0f) {
			switch (loopType) {
			case LoopType::PLAY_ONCE:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME:
				if (updateRate >= 1.0f) {
					updateRate = 1.0f;
					loopCount = 1;
					vanished = true;
				}
				break;
			case LoopType::PLAY_ONCE_AND_HOLD:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD:
				if (updateRate >= 1.0f) {
					loopCount = 1;
					updateRate = 1.0f;
				}
				break;
			default:
				while (updateRate >= 1.0f) {
					++loopCount;
					updateRate -= 1.0f;
				}
				break;
			}
		} else {
			switch (loopType) {
			case LoopType::PLAY_ONCE:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME:
				if (updateRate < 0.0f) {
					updateRate = 0.0f;
					loopCount = 1;
					vanished = true;
				}
				break;
			case LoopType::PLAY_ONCE_AND_HOLD:
			case LoopType::PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD:
				if (updateRate < 0.0f) {
					loopCount = 1;
					updateRate = 0.0f;
				}
				break;
			default:
				while (updateRate < 0.0f) {
					++loopCount;
					updateRate += 1.0f;
				}
				break;
			}
		}
		int mTrackCount = reAnim->mTrackCount;
		for (int i = 0; i < mTrackCount; i++) {
			AnimAttachment& aat = mAttachment[i];
			if (aat.mBlendCountdown > 0)--aat.mBlendCountdown;
			if (aat.diffRange != 0.0f) {
				aat.xDiff = rand(-aat.diffRange, aat.diffRange);
				aat.yDiff = rand(-aat.diffRange, aat.diffRange);
			}
			PartProp pp = reAnim->mTracks[i];
			if (pp.isAttacher()) {
				UpdateAttacher(i);
			}
			if (aat.mAttachmentID) {
				Matrix3 temp = GetAttachmentOverlayMatrix(i);
				Attachment* a = (*gGameApp)[aat.mAttachmentID];
				if (a && !a->vanished) {
					a->Update();
					a->SetMatrix(&temp);
				} else aat.mAttachmentID = 0;
			}
		}
	}

	void Attachment::Update() {
		for (int i = 0; i < listSize; ++i) {
			Attacher& attachEffect = Attachers[i];
			bool exist = true;
			switch (attachEffect.type) {
			case Attacher::Type::PARTICLESYSTEM:
			{
				ParticleSystem* p = (*gGameApp)[(ID<ParticleSystem>)attachEffect.ID];
				if (p) {
					p->Update();
					if (p->vanished)exist = false;
				} else  exist = false;
			}break;
			case Attacher::Type::TRAIL:
			{
				Trail* p = (*gGameApp)[(ID<Trail>)attachEffect.ID];
				if (p) {
					p->Update();
					if (p->vanished)exist = false;
				} else  exist = false;
			}break;
			case Attacher::Type::ANIM:
			{
				Anim* p = (*gGameApp)[(ID<Anim>)attachEffect.ID];
				if (p) {
					p->Update();
					if (p->vanished)exist = false;
				} else  exist = false;
			}break;
			case Attacher::Type::ATTACHMENT:
			{
				Attachment* p = (*gGameApp)[(ID<Attachment>)attachEffect.ID];
				if (p) {
					p->Update();
					if (p->vanished)exist = false;
				} else  exist = false;
			}break;
			}
			if (!exist) {
				int n = listSize - i - 1;
				if (n) {
					memcpy(Attachers + i + 1, Attachers + i, n * sizeof(Attacher));
					--i;
				}
				--listSize;
			}
		}
		if (listSize == 0)vanished = true;
	}

	void Attachment::SetMatrix(Matrix3* matrix) {
		for (int i = 0; i < listSize; ++i) {
			Attacher& attachEffect = Attachers[i];
			Matrix3 m = *matrix * attachEffect.mPosition;
			switch (attachEffect.type) {
			case Attacher::Type::PARTICLESYSTEM:
			{
				ParticleSystem* p = (*gGameApp)[(ID<ParticleSystem>)attachEffect.ID];
				if (p) {
					p->SetPosition(matrix->xDiff, matrix->yDiff);
				}
			}break;
			case Attacher::Type::TRAIL:
			{
				Trail* p = (*gGameApp)[(ID<Trail>)attachEffect.ID];
				if (p) {
					p->x = matrix->xDiff;
					p->y = matrix->yDiff;
				}
			}break;
			case Attacher::Type::ANIM:
			{
				Anim* p = (*gGameApp)[(ID<Anim>)attachEffect.ID];
				if (p) {
					p->mPosition = *matrix;
				}
			}break;
			case Attacher::Type::ATTACHMENT:
			{
				Attachment* p = (*gGameApp)[(ID<Attachment>)attachEffect.ID];
				if (p) {
					p->SetMatrix(matrix);
				}
			}break;
			}
		}
	}

	Matrix3 FramePartProp::GetMatrix() {
		return Matrix3(mScaleX * cos(mSkewX * Pi / 180.0f), -mScaleY * sin(mSkewY * Pi / 180.0f), mTransX, mScaleX * sin(mSkewX * Pi / 180.0f), mScaleY * cos(mSkewY * Pi / 180.0f), mTransY);
	}

	Matrix3 Anim::GetPartMatrix(int index) {
		if (frameBasePos == BASEPOS_NIL)return Matrix3();
		return GetCurrentFramePart(index, AnimFrameTime({ 0.0f,frameBasePos,frameBasePos + 1 })).GetMatrix();
	}

	Matrix3 Anim::GetAttachmentOverlayMatrix(int index) {
		return mPosition * GetCurrentFramePart(index).GetMatrix() * GetPartMatrix(index).GetInverse();
	}

	AttacherInfo Anim::ParseAttacherInfo(const FramePartProp& prop) {
		AttacherInfo ans;
		ans.mReanimName = u8"";
		ans.mTrackName = u8"";
		ans.mAnimRate = 12.0f;
		ans.mLoopType = Anim::LoopType::LOOP;
		if (prop.mFrame == -1.0f)return ans;
		const char* ptr1 = strstr(prop.mText, u8"__");
		if (!ptr1)return ans;
		const char* ptr2 = strstr(ptr1 + 2, u8"__");
		const char* ptr3 = strstr(ptr1 + 2, u8"[");
		if (ptr3 && ptr2 && ptr3 < ptr2)return ans;
		if (ptr2) {
			ans.mReanimName = std_string(ptr1 + 2, ptr2 - ptr1 - 2);
			if (ptr3) {
				ans.mReanimName = std_string(ptr2 + 2, ptr3 - ptr2 - 2);
			} else {
				ans.mReanimName = std_string(ptr2 + 2);
			}
		} else if (ptr3) {
			ans.mReanimName = std_string(ptr1 + 2, ptr3 - ptr1 - 2);
		} else {
			ans.mReanimName = std_string(ptr1 + 2);
		}
		while (ptr3) {
			const char* ptr4 = strstr(ptr3 + 1, u8"]");
			if (!ptr4)return ans;
			std_string text = std_string(ptr3 + 1, ptr4 - ptr3 - 1);
			if (sscanf_s(text.data(), u8"%f", &ans.mAnimRate) == 1);
			else if (text == u8"hold") {
				ans.mLoopType = Anim::LoopType::PLAY_ONCE_AND_HOLD;
			} else if (text == u8"once") {
				ans.mLoopType = Anim::LoopType::PLAY_ONCE;
			}
			const char* ptr3 = strstr(ptr4 + 1, u8"[");
		}
		return ans;
	}

	void Global::LoadAnim(Anim::Type _type, bool preLoading) {
		AnimDefinition& reanimatorDefinition = gReanimatorDefArray[(int)_type];
		if (reanimatorDefinition.mTracks)return;
		AnimParams reanimationParams = gReanimationParamArray[(int)_type];
		if (preLoading && gGameApp->mShutdown)return;
		LoadAnim(&std_string(reanimationParams.mReanimFileName), &reanimatorDefinition);
	}

	Attacher* Attachment::NewAttacher() {
		if (!this)return nullptr;
		if (listSize == 15) {
			Attachment* a = gGameApp->mAnimsLists->mAttachmentList->New();
			Attacher* aa = Attachers + listSize;
			aa->type = Attacher::Type::ATTACHMENT;
			aa->ID = GetID(*a);
			aa->vanished = false;
			aa->mPosition = Matrix3();
			++listSize;
			return a->NewAttacher();
		} else if (listSize >= 16) {
			Attachment* a = (*gGameApp)[(ID<Attachment>)Attachers[15].ID];
			if (a == nullptr)Cvp::error(u8"Attachment Get failed");
			return a->NewAttacher();
		} else {
			++listSize;
			return Attachers + listSize - 1;
		}
	}

	Attacher* Global::AttachParticle(ID<Attachment>& theAttachmentID, ParticleSystem* theParticle, float theOffsetX, float theOffsetY) {
		Attacher* ans;
		Attachment* attachment = (*gGameApp)[theAttachmentID];
		if (!attachment) {
			attachment = gGameApp->mAnimsLists->mAttachmentList->New();
			theAttachmentID = GetID(*attachment);
		}
		ans = attachment->NewAttacher();
		ans->type = Attacher::Type::PARTICLESYSTEM;
		ans->ID = GetID(*theParticle);
		ans->vanished = false;
		ans->mPosition = Matrix3();
		ans->mPosition.xDiff = theOffsetX;
		ans->mPosition.yDiff = theOffsetY;
		theParticle->isAttachment = true;
		if (attachment->listSize > 16) Cvp::error(u8"Attachment over flow");
		return ans;
	}

	Attacher* Global::AttachAnim(ID<Attachment>& theAttachmentID, Anim* theReanimation, float theOffsetX, float theOffsetY) {
		Attacher* ans;
		Attachment* attachment = (*gGameApp)[theAttachmentID];
		if (!attachment) {
			attachment = gGameApp->mAnimsLists->mAttachmentList->New();
			theAttachmentID = GetID(*attachment);
		}
		ans = attachment->NewAttacher();
		ans->type = Attacher::Type::ANIM;
		ans->ID = GetID(*theReanimation);
		ans->vanished = false;
		ans->mPosition = Matrix3();
		ans->mPosition.xDiff = theOffsetX;
		ans->mPosition.yDiff = theOffsetY;
		theReanimation->isAttachment = true;
		if (attachment->listSize > 16) Cvp::error(u8"Attachment over flow");
		return ans;
	}

	void Anim::AttacherSynchWalkSpeed(int index, Anim* theAttachReanim, AttacherInfo* theAttacherInfo) {
		PartProp reanimatorTrack = reAnim->mTracks[index];
		AnimFrameTime reanimatorFrameTime = GetFrameTime();
		int num = reanimatorFrameTime.mAnimFrameBeforeInt;
		while (num > initFrame && reanimatorTrack.mTransforms[num - 1].mText == reanimatorTrack.mTransforms[num].mText)--num;
		int num2 = (int)reanimatorFrameTime.mAnimFrameBeforeInt;
		while (num2 < initFrame + frameCount - 1 && reanimatorTrack.mTransforms[num2 + 1].mText == reanimatorTrack.mTransforms[num2].mText)++num2;
		int num3 = num2 - num;
		FramePartProp reanimatorTransform = reanimatorTrack.mTransforms[num];
		FramePartProp reanimatorTransform2 = reanimatorTrack.mTransforms[num2 - 1];
		if (-0.000001f < updateV && updateV < 0.000001f) {
			theAttachReanim->updateV = 0.0f;
			return;
		}
		float num4 = -(reanimatorTransform2.mTransX - reanimatorTransform.mTransX);
		float num5 = (float)num3 / updateV;
		if (-0.000001f < num5 && num5 < 0.000001f) {
			theAttachReanim->updateV = 0.0f;
			return;
		}
		int num6 = theAttachReanim->GetPartIndex(u8"_ground");
		PartProp reanimatorTrack2 = theAttachReanim->reAnim->mTracks[num6];
		FramePartProp reanimatorTransform3 = reanimatorTrack2.mTransforms[theAttachReanim->initFrame];
		FramePartProp reanimatorTransform4 = reanimatorTrack2.mTransforms[(theAttachReanim->initFrame + theAttachReanim->frameCount - 1)];
		float num7 = reanimatorTransform4.mTransX - reanimatorTransform3.mTransX;
		if (num7 < 0.000001f || num4 < 0.000001f) {
			theAttachReanim->updateV = 0.0f;
			return;
		}
		float num8 = num4 / num7;
		float num9 = theAttachReanim->GetCurrentFramePart(num6).mTransX - reanimatorTransform3.mTransX;
		float num10 = num7 * theAttachReanim->updateV;
		AnimAttachment reanimatorTrackInstance = mAttachment[index];
		Attachment* p = (*gGameApp)[mAttachment[index].mAttachmentID];
		if (p) {
			Attacher* attachEffect = p->GetFirstAttacher();
			if (attachEffect)attachEffect->mPosition.xDiff = num10 - num9;
		}
		theAttachReanim->updateV = num8 * (float)theAttachReanim->frameCount / num5;
	}

	Attacher* Attachment::GetFirstAttacher() {
		if (listSize == 0)return nullptr;
		return Attachers;
	}

	void Anim::UpdateAttacher(int index) {
		AnimAttachment& theAttachment = mAttachment[index];
		AttacherInfo attacherInfo = ParseAttacherInfo(GetCurrentFramePart(index));
		Anim::Type reanimationType = Anim::Type::NIL;
		if (attacherInfo.mReanimName.length()) {
			std_string text = format(u8"reanim\\%s.reanim", attacherInfo.mReanimName.data());
			for (int i = 0; i < gReanimationParamArraySize; ++i) {
				AnimParams reanimationParams = gReanimationParamArray[i];
				if (text == reanimationParams.mReanimFileName) {
					reanimationType = reanimationParams.mReanimationType;
					break;
				}
			}
		}
		Attachment* a = (*gGameApp)[theAttachment.mAttachmentID];
		if (reanimationType == Anim::Type::NIL) {
			if (a)a->Kill();
			return;
		}
		Anim* reanimation = a->GetFirstAnim();
		if (!reanimation || reanimation->type != reanimationType) {
			a->Kill();
			reanimation = gGameApp->mAnimsLists->mAnimList->New();
			reanimation->mAnimList = gGameApp->mAnimsLists->mAnimList;
			reanimation->layer = 0;
			Global::LoadAnim(reanimationType, false);
			reanimation->type = reanimationType;
			reanimation->Init(0.0f, 0.0f, gReanimatorDefArray + (int)reanimationType);
			reanimation->loopType = attacherInfo.mLoopType;
			reanimation->updateV = attacherInfo.mAnimRate;
			Global::AttachAnim(theAttachment.mAttachmentID, reanimation, 0.0f, 0.0f);
			reanimation->frameBasePos = BASEPOS_NIL;
		}
		if (attacherInfo.mTrackName.length()) {
			int num;
			int num2;
			reanimation->GetSegment(attacherInfo.mTrackName.data(), num, num2);
			if (reanimation->initFrame != num || reanimation->frameCount != num2) {
				reanimation->StartBlend(20);
				reanimation->SetSegment(attacherInfo.mTrackName.data());
			}
			if (attacherInfo.mAnimRate == 12.0f && attacherInfo.mTrackName == u8"anim_walk" && reanimation->GetPartIndex(u8"_ground") != -1) {
				AttacherSynchWalkSpeed(index, reanimation, &attacherInfo);
			} else {
				reanimation->updateV = attacherInfo.mAnimRate;
			}
			reanimation->loopType = attacherInfo.mLoopType;
		}
		Color theColor = mColor * theAttachment.mColor;
		theColor.mAlpha = limit(0, theColor.mAlpha, 255);
		a = (*gGameApp)[theAttachment.mAttachmentID];
		if (a)a->PropogateColor(theColor, haveColor1, mColor1, haveColor2, mColor2);
	}

	void Anim::PropogateColorToAttachments() {
		for (int i = 0; i < reAnim->mTrackCount; ++i) {
			Attachment* p = (*gGameApp)[mAttachment[i].mAttachmentID];
			if (p)p->PropogateColor(mColor, haveColor1, mColor1, haveColor2, mColor2);
		}
	}

	void Attachment::PropogateColor(Color theColor, bool theEnableAdditiveColor, Color theAdditiveColor, bool theEnableOverlayColor, Color theOverlayColor) {
		for (int i = 0; i < listSize; ++i) {
			Attacher& attachEffect = Attachers[i];
			if (!attachEffect.mDontPropogateColor) {
				switch (attachEffect.type) {
				case Attacher::Type::PARTICLESYSTEM:
				{
					ParticleSystem* p = (*gGameApp)[(ID<ParticleSystem>)attachEffect.ID];
					if (p) {
						p->SetColor(&theColor);
						p->SetShine(theEnableAdditiveColor);
					}
				}break;
				case Attacher::Type::ANIM:
				{
					Anim* p = (*gGameApp)[(ID<Anim>)attachEffect.ID];
					if (p) {
						p->mColor = theColor;
						p->mColor1 = theAdditiveColor;
						p->haveColor1 = theEnableAdditiveColor;
						p->mColor2 = theOverlayColor;
						p->haveColor2 = theEnableOverlayColor;
						p->PropogateColorToAttachments();
					}
				}break;
				case Attacher::Type::ATTACHMENT:
				{
					Attachment* p = (*gGameApp)[(ID<Attachment>)attachEffect.ID];
					if (p)p->PropogateColor(theColor, theEnableAdditiveColor, theAdditiveColor, theEnableOverlayColor, theOverlayColor);
				}break;
				}
			}
		}
	}

	bool PartProp::isAttacher() {
		return strncmp(name, u8"attacher__", 10) == 0;
	}

	void Zombie::WaterSplash(bool in) {
		float xdiff = 23.0f;
		float ytemp = 78.0f;
		if (state == State::SNORKEL_SWIM) {
			xdiff += -37.0f;
			ytemp += -8.0f;
		}
		int ydiff;
		if (h == 0.0f) {
			ydiff = (int)(ytemp * size);
		} else {
			ydiff = (int)ytemp;
		}
		Anim* reanimation = mApp->NewAnim(Anim::Type::SPLASH, layer + 1, (float)(mX + (int)(xdiff * size)), (float)(mY + ydiff));
		reanimation->mPosition.xStrech = reanimation->mPosition.yStrech = 0.8f;
		mApp->NewParticleSystem(ParticleSystem::Type::PLANTING_POOL, layer + 1, (float)mX + xdiff + 37.0f, (float)mY + ytemp + 42.0f);
		if (in) {
			mApp->NewSampleF(Sample::Type::ZOMBIE_ENTER_WATER);
		} else mApp->NewSampleF(Sample::Type::PLANT_IN_WATER);
	}

	void Zombie::UpdateEnterWater() {
		if (!BasicProp(type).canEnterWater)return;
		if (isFlying())return;
		if (type == Type::DOLPHIN_RIDER_ZOMBIE || type == Type::SNORKEL_ZOMBIE)return;
		if (movementState == MovementState::ENTER_WATER || movementState == MovementState::LEAVE_WATER)return;
		bool shouldInWater = isInWater();
		if (!inWater && shouldInWater) {
			if (mBoard->poolFreezeCountdown > 0) {
				freezeCountdown = mBoard->poolFreezeCountdown;
				Slowed(2000);
				return;
			}
			movementState = MovementState::ENTER_WATER;
			inWater = true;
			WaterSplash(true);
		} else if (inWater && !shouldInWater) {
			movementState = MovementState::LEAVE_WATER;
			this->AnimStartWalk(0);
			WaterSplash(false);
		}
	}

	void Zombie::UpdateHighGridEnterLeave() {
		if (movementState != MovementState::NIL)return;
		if (type == Type::BUNGEE_ZOMBIE)return;
		if (!isOnBoard())return;
		int col = mBoard->GetCol(mX + 75, mY);
		bool shouldInHigh = isInHighgrid();
		if (!inHighgrid && shouldInHigh) {
			movementState = MovementState::ENTER_HIGHLAND;
			inHighgrid = true;
			return;
		}
		if (inHighgrid && !shouldInHigh) {
			movementState = MovementState::LEAVE_HIGHLAND;
		}
	}

	void Zombie::UpdateUpLadder() {
		float xdiff = h;
		if (inHighgrid) {
			xdiff -= 30.0f;
		}
		int col = max(0, mBoard->GetCol(mX + 5 + (int)xdiff / 2, mY));
		if (!mBoard->GetGridBuilding(col, row, Building::Type::LADDER)) {
			movementState = MovementState::LEAVE_LADDER;
			return;
		}
		h += 0.8f;
		if (v < 0.5f)x -= 0.5f;
		float hMax = 90.0f;
		if (inHighgrid) {
			hMax += 30.0f;
		}
		if (h >= hMax) {
			movementState = MovementState::LEAVE_LADDER;
		}
	}

	void Zombie::UpdateWater() {
		if (movementState == MovementState::LEAVE_WATER) {
			h += 1.0f;
			if (type == Type::SNORKEL_ZOMBIE)h += 1.0f;
			if (h >= 0.0f) {
				h = 0.0f;
				movementState = MovementState::NIL;
				inWater = false;
				return;
			}
		} else if (movementState == MovementState::ENTER_WATER) {
			h -= 1.0f;
			float hMin = -40.0f;
			hMin *= size;
			if (h <= hMin) {
				h = hMin;
				movementState = MovementState::NIL;
				AnimStartWalk(0);
				return;
			}
		} else if (movementState == MovementState::DRAGGED_UNDER) {
			h -= 1.0f;
		}
	}

	void Zombie::UpdateHighGrid() {
		if (type == Type::POGO_ZOMBIE)return;
		if (movementState == MovementState::ENTER_HIGHLAND) {
			h += 1.0f;
			if (h >= 30.0f) {
				h = 30.0f;
				movementState = MovementState::NIL;
				return;
			}
		} else if (movementState == MovementState::LEAVE_HIGHLAND) {
			h -= 1.0f;
			if (h <= 0.0f) {
				h = 0.0f;
				movementState = MovementState::NIL;
				inHighgrid = false;
			}
		}
	}

	void Zombie::UpdateDownLadder() {
		h -= 1.0f;
		if (state == State::POLE_VAULTING_RUN)h -= 1.0f;
		float hMin = 0.0f;
		if (isInHighgrid())hMin = 30.0f;
		if (h <= hMin) {
			h = hMin;
			movementState = MovementState::NIL;
		}
	}


	void Zombie::UpdateLeave() {
		if (type == Type::ZOMBOSS)return;
		if (isFacingRight() && x > 850.0f)return Kill();
		int xMin;
		if (inrange(type,
			Type::GARGANTUAR,
			Type::GIGA_GARGANTUAR,
			Type::POLE_VAULTING_ZOMBIE
		))xMin = -150;
		else if (inrange(type,
			Type::CATAPULT_ZOMBIE,
			Type::FOOTBALL_ZOMBIE,
			Type::ZOMBONI
		))xMin = -175;
		else if (inrange(type,
			Type::BACKUP_DANCER,
			Type::DANCING_ZOMBIE,
			Type::SNORKEL_ZOMBIE
		))xMin = -130;
		else  xMin = -100;
		if (mX <= xMin && haveHead) {
			if (mApp->isIZ())Kill();
			else mBoard->Lose(this);
		}
		if (mX <= xMin + 70 && !haveHead)Hitted(1800, HitType::SIDE | HitType::NO_FLASH);
	}

	void Anim::IgnoreClip(const char* name, bool ignore) {
		AnimAttachment* a = GetPartAttachment(name);
		if (a)a->mIgnoreClipRect = ignore;
	}

	void Zombie::UpdateRise() {
		if (inWater)h = (float)getCurveValue(1, 0, 50, -40, -150, propCountdown) * size;
		else h = (float)getCurveValue(1, 0, 50, 0, -200, propCountdown);
		if (propCountdown <= 0) {
			state = State::NIL;
			if (isInHighgrid())h = 30.0f;
			if (inWater) {
				Anim* a = (*mApp)[mAnimId];
				if (!a)return;
				a->IgnoreClip(u8"Zombie_duckytube", true);
				a->IgnoreClip(u8"Zombie_whitewater", true);
				a->IgnoreClip(u8"Zombie_outerarm_hand", true);
				a->IgnoreClip(u8"Zombie_innerarm3", true);
			}
		}
	}

	bool SceneProp::ShouldUpsell() { return(mApp->level == GameApp::Level::Type::UPSELL || mApp->level == GameApp::Level::Type::INTRO) && !battle; }

	void Bullet::Update() {
		++existTime;
		if (mApp->gameState != GameApp::State::BATTLE && !mBoard->mSceneProp->ShouldUpsell())return;
		int layerInitTime = inrange(type,
			Type::PEA,
			Type::SNOW_PEA,
			Type::CABBAGE,
			Type::MELON,
			Type::SNOW_MELON,
			Type::KERNEL,
			Type::BUTTER,
			Type::BOMB,
			Type::ZOMBIE_PEA,
			Type::SPIKE
		) ? 0 : 20;
		if (existTime > layerInitTime)layer = 305000 + 10000 * row;
		if (clickBackoffCountdown > 0)--clickBackoffCountdown;
		rotateRad += rotateSpeed;
		UpdateMain();
		Attachment* a = (*mApp)[mAttachmentID];
		if (!a)return;
		a->Update();
		a->SetPosition(x, y + h);
	}

	void Trail::AddPoint(float x, float y) {
		int num = limit(2, mDefinition->mMaxPoints, 20);
		if (pointCount > 0) {
			Point<float>& pback = points[pointCount - 1];
			float num2 = pback.Distance();
			if (num2 < mDefinition->mMinPointDistance)return;
		}
		Point<float> trailPoint2 = points[pointCount];
		trailPoint2.mX = x;
		trailPoint2.mY = y;
		++pointCount;
	}

	void Anim::SetPosition(float x, float y) {
		mPosition.xDiff = x;
		mPosition.yDiff = y;
	}

	void Attachment::SetColor(Color& theColor) {
		for (int i = 0; i < listSize; ++i) {
			Attacher& attachEffect = Attachers[i];
			switch (attachEffect.type) {
			case Attacher::Type::PARTICLESYSTEM:
			{
				ParticleSystem* p = (*gGameApp)[(ID<ParticleSystem>)attachEffect.ID];
				if (p) {
					p->SetColor(&theColor);
				}
			}break;
			case Attacher::Type::ANIM:
			{
				Anim* p = (*gGameApp)[(ID<Anim>)attachEffect.ID];
				if (p) {
					p->mColor = theColor;
				}
			}break;
			case Attacher::Type::ATTACHMENT:
			{
				Attachment* p = (*gGameApp)[(ID<Attachment>)attachEffect.ID];
				if (p) {
					p->SetColor(theColor);
				}
			}break;
			}
		}
	}

	void Attachment::SetSize(float size) {
		for (int i = 0; i < listSize; ++i) {
			Attacher& attachEffect = Attachers[i];
			switch (attachEffect.type) {
			case Attacher::Type::PARTICLESYSTEM:
			{
				ParticleSystem* p = (*gGameApp)[(ID<ParticleSystem>)attachEffect.ID];
				if (p) {
					p->SetSize(size);
				}
			}break;
			case Attacher::Type::ANIM:
			{
				Anim* p = (*gGameApp)[(ID<Anim>)attachEffect.ID];
				if (p) {
					p->mPosition.xStrech = size;
					p->mPosition.yStrech = size;
				}
			}break;
			case Attacher::Type::ATTACHMENT:
			{
				Attachment* p = (*gGameApp)[(ID<Attachment>)attachEffect.ID];
				if (p) {
					p->SetSize(size);
				}
			}break;
			}
		}
	}

	void Attachment::SetPosition(float x, float y) {
		for (int i = 0; i < listSize; ++i) {
			Attacher& attachEffect = Attachers[i];
			switch (attachEffect.type) {
			case Attacher::Type::PARTICLESYSTEM:
			{
				ParticleSystem* p = (*gGameApp)[(ID<ParticleSystem>)attachEffect.ID];
				if (p) {
					p->SetPosition(x, y);
				}
			}break;
			case Attacher::Type::TRAIL:
			{
				Trail* p = (*gGameApp)[(ID<Trail>)attachEffect.ID];
				if (p) {
					p->AddPoint(x, y);
				}
			}break;
			case Attacher::Type::ANIM:
			{
				Anim* p = (*gGameApp)[(ID<Anim>)attachEffect.ID];
				if (p) {
					p->SetPosition(x, y);
				}
			}break;
			case Attacher::Type::ATTACHMENT:
			{
				Attachment* p = (*gGameApp)[(ID<Attachment>)attachEffect.ID];
				if (p) {
					p->SetPosition(x, y);
				}
			}break;
			}
		}
	}

	Rect Bullet::GetRect() {
		switch (type) {
		case Type::PEA:
		case Type::SNOW_PEA:
		case Type::ZOMBIE_PEA:
		case Type::BOMB:return Rect(mX + mW / 2 - 115, mY + mH / 2 - 115, 130, 130);
		case Type::MELON:
		case Type::SNOW_MELON:return Rect(mX + 20, mY, 60, mH);
		case Type::FIRE_PEA:return Rect(mX, mY, mW - 10, mH);
		case Type::SPIKE:return Rect(mX - 25, mY, mW + 25, mH);
		default:return Rect(mX, mY, mW, mH);
		}
	}

	Plant* Bullet::GetTargetPlant() {
		Rect projectileRect = GetRect();
		for (auto&& p : mBoard->mPlantList) {
			if (row == p.row && (type != Type::ZOMBIE_PEA || !inrange(p.type,
				Plant::Type::PUFF_SHROOM,
				Plant::Type::SUN_SHROOM,
				Plant::Type::POTATO_MINE,
				Plant::Type::SPIKEWEED,
				Plant::Type::SPIKEROCK,
				Plant::Type::LILY_PAD
			))) {
				int rectOverlap = projectileRect.IntersectWidth(p.GetDefRect());
				if (rectOverlap > 8) {
					if (type == Type::ZOMBIE_PEA) {
						return mBoard->GetGridPlant(p.col, p.row, PlantPriority::BITE);
					} else return mBoard->GetGridPlant(p.col, p.row, PlantPriority::CATAPULT);
				}
			}
		}
		return nullptr;
	}

	bool Bullet::TryTorched() {
		if (movementState != MovementState::DIRECT)return false;
		if (type != Type::PEA && type != Type::SNOW_PEA)return false;
		for (auto&& p : mBoard->mPlantList) if (p.type == Plant::Type::TORCHWOOD && p.row == row && !p.isFlying() && lastTorchCol != p.col) {
			Rect plantAttackRect;
			p.GetAtkRect(&plantAttackRect);
			int rectOverlap = plantAttackRect.IntersectWidth(GetRect() + Point<int>(40, 0));
			return rectOverlap > 10;
		}
		return false;
	}

	Zombie* Bullet::GetTargetZombie() {
		if (TryTorched())return nullptr;
		Rect projectileRect = GetRect();
		Zombie* ans = nullptr;
		int xMin = 0;
		for (auto&& p : mBoard->mZombieList) if ((p.state != Zombie::State::SNORKEL_SWIM || h > 45.0f) && (type != Type::STAR || existTime >= 25 || dx < 0.0f || p.type != Zombie::Type::DIGGER_ZOMBIE) && p.inRange(hitRange) && (p.row == row || p.type == Zombie::Type::ZOMBOSS) && projectileRect.IntersectWidth(p.GetDefRect()) >= 0 && (!ans || p.mX < xMin)) ans = &p, xMin = p.mX;
		return ans;
	}

	void Bullet::UpdatePelt() {
		if (type == Type::BOMB && h < -700.0f) {
			dh = 8.0f;
			x = mTargetX;
			row = mTargetRow;
			y = (float)mBoard->GetY(max(0, mBoard->GetCol((int)mTargetX, 0)), mTargetRow);
			shadowY = y + 67.0f;
			rotateRad = -Pi / 2;
		}
		dh += ddh;
		if (mApp->level == GameApp::Level::Type::GRAVITY)dh += ddh;
		x += dx;
		y += dy;
		h += dh;
		bool raise = dh < 0.0f;
		if (raise && (type == Type::ZOMBIE_BALL || type == Type::BOMB))return;
		if (existTime > 20) {
			if (raise)return;
			float activeh;
			if (type == Type::BUTTER) {
				activeh = -32.0f;
			} else if (type == Type::ZOMBIE_BALL) {
				activeh = 60.0f;
			} else if (type == Type::MELON || type == Type::SNOW_MELON) {
				activeh = -35.0f;
			} else if (type == Type::CABBAGE || type == Type::KERNEL) {
				activeh = -30.0f;
			} else if (type == Type::BOMB) {
				activeh = -60.0f;
			} else activeh = 0.0f;
			if (mBoard->rowSpawnType[row] == Board::SpawnType::Water)activeh += 40.0f;
			if (h <= activeh)return;
		}
		Plant* plant = nullptr;
		Zombie* zombie = nullptr;
		if (type == Type::ZOMBIE_BALL || type == Type::ZOMBIE_PEA)plant = GetTargetPlant();
		else zombie = GetTargetZombie();
		float groundH = 80.0f;
		if (type == Type::BOMB)groundH = -40.0f;
		bool hitground = h > groundH;
		if (!zombie && !plant && !hitground)return;
		if (plant) {
			Plant* leaf = mBoard->GetGridUmbrella(plant->col, plant->row);
			if (leaf) {
				if (leaf->state == Plant::State::UMBRELLA_UP) {
					mApp->NewSampleF(Sample::Type::SPLAT);
					mApp->NewParticleSystem(ParticleSystem::Type::UMBRELLA_REFLECT, 400001, x + 20.0f, y + 20.0f);
				} else if (leaf->state == Plant::State::UMBRELLA_RISE)return;
				else {
					mApp->NewSample(Sample::Type::PLANT_UMBRELLA_RISE);
					leaf->Suicide();
					return;
				}
			} else {
				plant->hp -= BasicProp(type).damage;
				if (plant->flashCountdown < 25)plant->flashCountdown = 25;
				mApp->NewSampleF(Sample::Type::SPLAT);
			}
			Kill();
			return;
		}
		if (type == Type::BOMB) {
			mBoard->Explode(row, (int)x + 80, (int)y + 40, 115, 1, true, hitRange);
			Hit();
			return;
		}
		Hit(zombie);
	}

	void Bullet::HitSound(Zombie* that) {
		bool basicSound = true;
		if (type == Type::KERNEL) {
			mApp->NewSampleF(Sample::Type::BULLET_KERNEL_HIT);
			return;
		} else if (type == Type::BUTTER) {
			mApp->NewSampleF(Sample::Type::BULLET_BUTTER_HIT);
			basicSound = false;
		} else if (type == Type::FIRE_PEA && isAoe(that)) {
			mApp->NewSampleF(Sample::Type::BULLET_FIREBALL_HIT);
			return;
		} else if (type == Type::MELON || type == Type::SNOW_MELON) {
			mApp->NewSampleF(Sample::Type::BULLET_MELON_HIT);
			basicSound = false;
		}
		if (that) {
			if (that->helmetType == Zombie::HelmType::BUCKET) {
				mApp->NewSampleF(Sample::Type::BULLET_HIT_IRON);
				return;
			} else if (inrange(that->helmetType,
				Zombie::HelmType::CONE,
				Zombie::HelmType::DIGGER,
				Zombie::HelmType::FOOTBALL
			)) {
				mApp->NewSampleF(Sample::Type::BULLET_HIT_CONE);
			}
		}
		if (basicSound) {
			mApp->NewSampleF(Sample::Type::SPLAT);
		}
	}

	bool Bullet::isAoe(Zombie* that) {
		return(type != Type::FIRE_PEA || !that || !(inrange(that->type,
			Zombie::Type::CATAPULT_ZOMBIE,
			Zombie::Type::ZOMBONI
		) || inrange(that->shieldType,
			Zombie::ShieldType::SCREEN_DOOR,
			Zombie::ShieldType::LADDER
		))) && inrange(type,
			Type::MELON,
			Type::SNOW_MELON,
			Type::FIRE_PEA
		);
	}

	void Zombie::Warmed() {
		if (freezeCountdown > 0)BreakIce();
		if (slowCountdown > 0)slowCountdown = 0, AnimInitSpeed();
	}

	void Bullet::HitAoe(Zombie* that) {
		Rect projectileRect = GetRect();
		if (type == Type::FIRE_PEA)projectileRect.mW = 100;
		if (bugfix_leftfireball && type == Type::FIRE_PEA && dx < 0)projectileRect.mX -= 70;
		int num = 0;
		for (auto p = mBoard->mZombieList.begin(); p != mBoard->mZombieList.end(); ++p) {
			if (&*p == that)continue;
			if (type == Type::FIRE_PEA && (inrange(p->type,
				Zombie::Type::CATAPULT_ZOMBIE,
				Zombie::Type::ZOMBONI
			) || inrange(p->shieldType,
				Zombie::ShieldType::SCREEN_DOOR,
				Zombie::ShieldType::LADDER
			)))continue;
			int rowDiff = p->row - row;
			if (p->type == Zombie::Type::ZOMBOSS)rowDiff = 0;
			if (type == Type::FIRE_PEA && rowDiff)continue;
			else if (rowDiff > 1 || rowDiff < -1)continue;
			if (!p->inRange(hitRange))continue;
			if (projectileRect.IntersectWidth(p->GetDefRect()) < 0)continue;
			++num;
		}
		int dmg = BasicProp(type).damage;
		if (!num) {
			if (that)return that->Hitted(dmg, GetHitType(that));
			else return;
		}
		int dmgMax;
		if (type == Type::FIRE_PEA)dmgMax = dmg;
		else dmgMax = dmg * 7;
		int dmgAoe = limit(1, dmg / 3, dmgMax / num);
		for (auto p = mBoard->mZombieList.begin(); p != mBoard->mZombieList.end(); ++p) {
			if (&*p == that)continue;
			if (type == Type::FIRE_PEA && (inrange(p->type,
				Zombie::Type::CATAPULT_ZOMBIE,
				Zombie::Type::ZOMBONI
			) || inrange(p->shieldType,
				Zombie::ShieldType::SCREEN_DOOR,
				Zombie::ShieldType::LADDER
			)))continue;
			int rowDiff = p->row - row;
			if (p->type == Zombie::Type::ZOMBOSS)rowDiff = 0;
			if (type == Type::FIRE_PEA && rowDiff)continue;
			else if (rowDiff > 1 || rowDiff < -1)continue;
			if (!p->inRange(hitRange))continue;
			if (projectileRect.IntersectWidth(p->GetDefRect()) < 0)continue;
			HitType damageFlags = GetHitType(&*p);
			if (&*p == that)p->Hitted(dmg, damageFlags);
			else p->Hitted(dmgAoe, damageFlags);
		}
	}

	HitType Bullet::GetHitType(Zombie* that) {
		HitType ans = HitType::NIL;
		if (isAoe(that))ans = ans | HitType::SPLASH;
		else if (inrange(movementState,
			MovementState::PELT,
			MovementState::LEFT,
			MovementState::INCLINED
		) && dx < 0.0f)ans = ans | HitType::SIDE;
		if (type == Type::SNOW_PEA || type == Type::SNOW_MELON)ans = ans | HitType::SLOW;
		return ans;
	}

	void Zombie::Buttered() {
		if (!haveHead || !isFreezeable())return;
		if (type == Type::ZOMBONI || type == Type::ZOMBOSS || isTangleTarget() || GetTeamRank() != -1 || isFlying())return;
		butterCountdown = 400;
		Zombie* zombie = mBoard->mZombieList[mPartners[0]];
		if (zombie)zombie->mPartners[0] = mPartners[0] = 0;
		if (type == Type::POGO_ZOMBIE)h = inHighgrid ? 30.0f : 0.0f;
		if (type == Type::BALLOON_ZOMBIE) {
			Anim* p = (*mApp)[(*mApp)[mAnimId]->GetPartAttachment(u8"hat")->mAttachmentID]->GetFirstAnim();
			if (p)p->updateV = 0.0f;
		}
		if (inrange(type,
			Type::PEASHOOTER,
			Type::WALL_NUT,
			Type::TALL_NUT,
			Type::JALAPENO,
			Type::GATLING_PEA,
			Type::SQUASH
		)) {
			Anim* p = (*mApp)[addHead];
			if (p)p->updateV = 0.0f;
		}
		AnimInitSpeed();
		StopUniqueSample();
	}

	void Bullet::Hit(Zombie* that) {
		HitSound(that);
		if (isAoe(that)) {
			if (type == Type::FIRE_PEA && that)that->Warmed();
			HitAoe(that);
		} else if (that)that->Hitted(BasicProp(type).damage, GetHitType(that));
		int aRenderOrder = layer + 1;
		float num = x - dx;
		float num2 = y + h - dy - dh;
		float num3 = x + 12.0f;
		float num4 = y + 12.0f;
		ParticleSystem::Type particleEffect = ParticleSystem::Type::NIL;
		if (type == Type::MELON) {
			mApp->NewParticleSystem(ParticleSystem::Type::MELONSPLASH, layer + 1, num + 30.0f, num2 + 30.0f);
		} else if (type == Type::SNOW_MELON) {
			mApp->NewParticleSystem(ParticleSystem::Type::WINTERMELON, layer + 1, num + 30.0f, num2 + 30.0f);
		} else if (type == Type::BOMB) {
			int aRenderOrder2 = 200002 + row * 10000;
			mApp->NewParticleSystem(ParticleSystem::Type::BLASTMARK, aRenderOrder2, x + 80.0f, y + 40.0f);
			mApp->NewParticleSystem(ParticleSystem::Type::POPCORNSPLASH, layer + 1, x + 80.0f, y + 40.0f);
			mApp->PlaySample(SOUND_DOOMSHROOM);
			mBoard->Shake(3, -4);
		} else if (type == Type::PEA) {
			num3 -= 15.0f;
			particleEffect = ParticleSystem::Type::PEA_SPLAT;
		} else if (type == Type::SNOW_PEA) {
			num3 -= 15.0f;
			particleEffect = ParticleSystem::Type::SNOWPEA_SPLAT;
		} else if (type == Type::FIRE_PEA) {
			if (isAoe(that)) {
				Anim* a = mApp->NewAnim(Anim::Type::JALAPENO_FIRE, aRenderOrder, x + 38.0f, y - 20.0f);
				a->updateRate = 0.25f;
				a->updateV = 24.0f;
				a->mPosition.xStrech = 0.7f;
				a->mPosition.yStrech = 0.4f;
			}
		} else if (type == Type::STAR) {
			particleEffect = ParticleSystem::Type::STAR_SPLAT;
		} else if (type == Type::PUFF) {
			num3 -= 20.0f;
			particleEffect = ParticleSystem::Type::PUFF_SPLAT;
		} else if (type == Type::CABBAGE) {
			num3 = num - 38.0f;
			num4 = num2 + 23.0f;
			particleEffect = ParticleSystem::Type::CABBAGE_SPLAT;
		} else if (type == Type::BUTTER) {
			num3 = num - 20.0f;
			num4 = num2 + 63.0f;
			particleEffect = ParticleSystem::Type::BUTTER_SPLAT;
			if (that)that->Buttered();
		}
		if (particleEffect != ParticleSystem::Type::NIL) {
			if (that) {
				float num5 = num3 + 52.0f - (float)that->mX;
				float num6 = num4 - (float)that->mY;
				if (that->state == Zombie::State::SNORKEL_SWIM || that->state == Zombie::State::DOLPHIN_SWIM)num6 += 60.0f;
				if (movementState == MovementState::LEFT)num5 -= 80.0f;
				else if (x > (float)(that->mX + 40) && movementState != MovementState::PELT)num5 -= 60.0f;
				num6 = limit(20.0f, num6, 100.0f);
				that->NewAttachedParticle((int)num5, (int)num6, particleEffect);
			} else {
				mApp->NewParticleSystem(particleEffect, aRenderOrder, num3, num4);
			}
		}
		Kill();
	}

	void Bullet::TryHitZombie() {
		if (movementState == MovementState::SHORT && existTime >= 75)return Kill();
		if (x > 800.0f || x + (float)mW < 0.0f)return Kill();
		Zombie* zombie;
		if (movementState == MovementState::TRACK) {
			zombie = mBoard->mZombieList[mTargetZombieID];
			if (zombie && zombie->inRange(hitRange)) {
				Rect zombieRect = zombie->GetDefRect();
				int rectOverlap = GetRect().IntersectWidth(zombieRect);
				if (rectOverlap >= 0 && y > (float)zombieRect.mY && y < (float)(zombieRect.mY + zombieRect.mH))Hit(zombie);
			}
			return;
		}
		if (type == Type::STAR && (y > 600.0f || y < 0.0f))return Kill();
		if ((type == Type::PEA || type == Type::STAR || (type == Type::FIRE_PEA && bugfix_rooffireball)) && shadowY - y > 90.0f)return;
		if (movementState == MovementState::FLOAT)return;
		if (type == Type::ZOMBIE_PEA) {
			Plant* plant = GetTargetPlant();
			if (plant) {
				plant->hp -= BasicProp(type).damage;
				plant->flashCountdown = max(plant->flashCountdown, 25);
				mApp->NewSample(Sample::Type::SPLAT);
				mApp->NewParticleSystem(ParticleSystem::Type::PEA_SPLAT, layer + 1, x - 3.0f, y + 17.0f);
				return Kill();
			}
			zombie = GetTargetBetrayed();
			if (zombie && !(zombie->inHighgrid && notHitHighgrid()))Hit(zombie);
			return;
		}
		zombie = GetTargetZombie();
		if (zombie && !(zombie->inHighgrid && notHitHighgrid()))Hit(zombie);
		return;
	}

	Zombie* Bullet::GetTargetBetrayed() {
		Rect projectileRect = GetRect();
		Zombie* ans = nullptr;
		int xMax = 0;
		for (auto&& p : mBoard->mZombieList) if (p.row == row && p.betray && projectileRect.IntersectWidth(p.GetDefRect()) >= 0 && (!ans || p.mX > xMax)) ans = &p, xMax = p.mX;
		return ans;
	}

	void Bullet::TryHitGround() {
		float relativeHeight = shadowY - y;
		if (inrange(type,
			Type::PEA,
			Type::SNOW_PEA,
			Type::FIRE_PEA,
			Type::SPIKE,
			Type::BOMB
		) && relativeHeight < 28.0f)return Hit();
		if (type == Type::PUFF && relativeHeight < 0.0f)return Hit();
		if (type == Type::STAR && relativeHeight < 23.0f)return Hit();
		if (!notHitHighgrid())return;
		int theColumn = max(0, mBoard->GetCol((int)x + 30, (int)y));
		if (mBoard->gridType[theColumn][row] == Board::GridType::HIGHLAND)return Hit();
	}

	float Zombie::PredictX(float time) {
		float num = v;
		if (slowCountdown > 0)num *= 0.4f;
		if (isFacingRight())num = -num;
		if (isStopped())num = 0.0f;
		Rect zombieRect = GetDefRect();
		return(float)(zombieRect.mX + zombieRect.mW / 2) - num * time;
	}

	void Bullet::UpdateNormal() {
		if (movementState == MovementState::LEFT) {
			x -= 3.33f;
		} else if (movementState == MovementState::TRACK) {
			Zombie* that = mBoard->mZombieList[mTargetZombieID];
			if (that && that->inRange(hitRange)) {
				Rect zombieRect = that->GetDefRect();
				Point<float> diff{ that->PredictX() - x - (float)(mW / 2), -y + (float)(zombieRect.mY + zombieRect.mH / 2 - mH / 2) };
				Point<float> direct = diff / diff.Distance();
				Point<float> dp{ dx, dy };
				dp = dp + direct * (0.001f * (float)existTime);
				dp = dp / dp.Distance();
				dp = dp * 2;
				dx = dp.mX;
				dy = dp.mY;
				rotateRad = -atan2(dy, dx);
			}
			y += dy;
			x += dx;
			shadowY += dy;
			row = max(0, mBoard->GetRow(max(40, (int)x), (int)y));
		} else if (movementState == MovementState::INCLINED) {
			y += dy;
			x += dx;
			shadowY += dy;
			if (dy != 0.0f)row = max(0, mBoard->GetRow(max(40, (int)x), (int)y));
		} else if (movementState == MovementState::RIGHT_UP) {
			if (existTime < 60) {
				y -= 0.5f;
			}
			x += 3.33f;
		} else if (movementState == MovementState::FLOAT) {
			if (dh < 0.0f) {
				dh += 0.002f;
				dh = min(dh, 0.0f);
				y += dh;
				rotateRad = 0.3f + -0.7f * dh * Pi * 0.25f;
			}
			x += 0.4f;
		} else if (movementState == MovementState::LEFT_UP) {
			if (existTime < 60)y -= 0.5f;
			x -= 3.33f;
		} else if (movementState == MovementState::SIDE_SHOOT) {
			x += 3.33f;
			y += dy;
			dy *= 0.97f;
			shadowY += dy;
		} else {
			x += 3.33f;
		}
		if (mApp->level == GameApp::Level::Type::GRAVITY) {
			if (movementState == MovementState::FLOAT)dh += 0.004f;
			else dh += 0.2f;
			y += dh;
		}
		TryHitZombie();
		TryHitGround();
	}

	void Bullet::UpdateMain() {
		if (noAnimShakeFrameCount > 0) {
			noAnimShakeTime = (noAnimShakeTime + 1) % (noAnimShakeFrameTime * noAnimShakeFrameCount);
			noAnimShakeFrameIndex = noAnimShakeTime / noAnimShakeFrameCount;
		}
		int rowPrev = row;
		float yBasePrev = mBoard->GetY(x, rowPrev);
		if (movementState == MovementState::PELT)UpdatePelt();
		else UpdateNormal();
		float yBaseDiff = mBoard->GetY(x, rowPrev) - yBasePrev;
		if (movementState == MovementState::FLOAT) {
			y += yBaseDiff;
		} else if (movementState == MovementState::PELT && !(type == Type::BOMB && bugfix_pao)) {
			y += yBaseDiff;
			h -= yBaseDiff;
		}
		shadowY += yBaseDiff;
		mX = (int)x;
		mY = (int)(y + h);
	}

	void Item::UpdateVanish() {
		if (mApp->level != GameApp::Level::Type::I_ZOMBIE_ENDLESS && mApp->level != GameApp::Level::Type::VASE_BREAKER_ENDLESS && type != Type::LETTER && isLevelAward())return;
		if (--vanishCountdown == 0)Kill();
	}

	void Item::UpdateCollected() {
		int xTarget = (int)x;
		int yTarget = (int)y;
		if (isSun()) {
			xTarget = 40;
			yTarget = 30;
		} else if (isMoney()) {
			xTarget = 39;
			yTarget = 558;
			if (mApp->GetDialog(Dialog::Type::STORE)) {
				xTarget = 662;
				yTarget = 546;
			} else if (mApp->DaveState != GameApp::DaveState::NIL || mApp->isGarden()) {
				xTarget = 442;
			}
		} else if (inrange(type,
			Type::PRESENT_MINIGAME,
			Type::PRESENT_PUZZLE,
			Type::PRESENT_SURVIVAL
		)) {
			xTarget = 35;
			yTarget = 487;
		} else if (type == Type::PRESENT_PLANT_AWARD || type == Type::PRESENT_PLANT) {
			++vanishCount;
			if (vanishCount >= 200)vanishCountdown = 15;
		} else if (!isLevelAward()) {
			if (type == Type::CARD)++vanishCount;
		} else {
			xTarget = 400 - mW / 2;
			yTarget = 200 - mH / 2;
			++vanishCount;
		}
		if (isLevelAward()) {
			size = getCurveValue(4, 0, 400, 1.01f, 2.0f, vanishCountdown);
			x = getCurveValue(3, 0, 350, collectedX, (float)xTarget, vanishCountdown);
			y = getCurveValue(3, 0, 350, collectedY, (float)yTarget, vanishCountdown);
			return;
		}
		float xDiff = (float)xTarget - x;
		float yDiff = (float)yTarget - y;
		x += xDiff / 21.0f;
		y += yDiff / 21.0f;
		targetDistance = Point<float>(xDiff, yDiff).Distance();
		if (inrange(type,
			Type::PRESENT_MINIGAME,
			Type::PRESENT_PUZZLE,
			Type::PRESENT_SURVIVAL
		)) {
			if (targetDistance < 15.0f) {
				if (!mBoard->AdviceShown[(int)Board::AdviceType::UNLOCKED_MODE]) {
					if (type == Type::PRESENT_MINIGAME) {
						mBoard->SetBoardText(u8"[UNLOCKED_MINIGAMES]", BoardText::Type::HINT_TALL_UNLOCKMESSAGE, Board::AdviceType::UNLOCKED_MODE);
						return;
					}
					if (type == Type::PRESENT_PUZZLE) {
						mBoard->SetBoardText(u8"[UNLOCKED_PUZZLE_MODE]", BoardText::Type::HINT_TALL_UNLOCKMESSAGE, Board::AdviceType::UNLOCKED_MODE);
						return;
					}
					if (type == Type::PRESENT_SURVIVAL) {
						mBoard->SetBoardText(u8"[UNLOCKED_SURVIVAL_MODE]", BoardText::Type::HINT_TALL_UNLOCKMESSAGE, Board::AdviceType::UNLOCKED_MODE);
						return;
					}
				} else if (mBoard->mBoardTextType != Board::AdviceType::UNLOCKED_MODE || mBoard->mBoardText->countdown == 0) {
					Kill();
				}
			}
			return;
		}
		if (targetDistance < (isMoney() ? 12.0f : 8.0f))Scored();
		size = limit(0.5f, targetDistance * 0.05f, 1.0f);
		if (type == Type::SUN_LARGE)size *= 2.0f;
		else if (type == Type::SUN_SMALL)size *= 0.5f;
	}

	void Item::Scored() {
		int value;
		if (isSun()) {
			value = BasicProp(type).sunValue;
			mBoard->sunValue += value;
			if (mBoard->sunValue > 9990)mBoard->sunValue = 9990;
		} else if (isMoney()) {
			value = BasicProp(type).coinValue;
			mApp->mUserData->money += value;
			if (mApp->mUserData->money > 99999)mApp->mUserData->money = 99999;
			if (mBoard)mBoard->collectedGoldcoinCount += value;
			if (type == Type::DIAMOND && mBoard)++mBoard->collectedDiamondCount;
		}
		Kill();
	}

	void Item::SplashConatins(Type theType, int num) {
		float dr = Pi / (float)(num + 1);
		float rad = 0.0f;
		for (int i = 0; i < num; ++i) {
			rad += dr;
			Item* coin = mBoard->NewItem((int)x + 20, (int)y, theType, MovementState::FROM_PRESENT);
			coin->dx = 5.0f * cos(rad);
			coin->dx = 5.0f * sin(rad);
		}
	}

	void Item::Collected() {
		if (vanished)return;
		collectedX = x;
		collectedY = y;
		collected = true;
		bool flag = false;
		if ((mApp->level == GameApp::Level::Type::I_ZOMBIE_ENDLESS || mApp->level == GameApp::Level::Type::VASE_BREAKER_ENDLESS) && isLevelAward())flag = true;
		if (type == Type::PRESENT_PLANT || type == Type::PRESENT_PLANT_AWARD) {
			if (mApp->mGardenProp->isFull(false)) {
				mBoard->SetBoardText(u8"[DIALOG_ZEN_GARDEN_FULL]", BoardText::Type::HINT_FAST, Board::AdviceType::NIL);
			} else {
				++mBoard->collectedFlowerpotCount;
				mBoard->SetBoardText(u8"[ADVICE_FOUND_PLANT]", BoardText::Type::HINT_FAST, Board::AdviceType::NIL);
				mApp->NewParticleSystem(ParticleSystem::Type::PRESENT_PICKUP, layer + 1, x + 30.0f, y + 30.0f);
				mApp->mGardenProp->NewPlant(&mGardenPlant);
			}
			vanishCount = 0;
			vanishCountdown = 0;
			if (flag) {
				Attachment* a = (*mApp)[mAttachment];
				if (a)a->RemoveAttacher(ParticleSystem::Type::AWARD_PICKUP_ARROW);
				mBoard->FadeOutLevel();
			}
			return;
		}
		if (type == Type::PRESENT_MINIGAME) {
			mApp->NewParticleSystem(ParticleSystem::Type::PRESENT_PICKUP, layer + 1, x + 30.0f, y + 30.0f);
			vanishCount = 0;
			vanishCountdown = 0;
			Attachment* a = (*mApp)[mAttachment];
			if (a)a->RemoveAttacher(ParticleSystem::Type::AWARD_PICKUP_ARROW);
			mApp->mUserData->minigamePresentCollected = 1;
			return;
		}
		if (type == Type::PRESENT_PUZZLE) {
			mApp->NewParticleSystem(ParticleSystem::Type::PRESENT_PICKUP, layer + 1, x + 30.0f, y + 30.0f);
			vanishCount = 0;
			vanishCountdown = 0;
			Attachment* a = (*mApp)[mAttachment];
			if (a)a->RemoveAttacher(ParticleSystem::Type::AWARD_PICKUP_ARROW);
			mApp->mUserData->puzzlePresentCollected = 1;
			return;
		}
		if (type == Type::PRESENT_SURVIVAL) {
			mApp->NewParticleSystem(ParticleSystem::Type::PRESENT_PICKUP, layer + 1, x + 30.0f, y + 30.0f);
			vanishCount = 0;
			vanishCountdown = 0;
			Attachment* a = (*mApp)[mAttachment];
			if (a)a->RemoveAttacher(ParticleSystem::Type::AWARD_PICKUP_ARROW);
			mApp->mUserData->survivalPresentCollected = true;
			return;
		}
		if (type == Type::CHOCOLATE || type == Type::CHOCOLATE_AWARD) {
			++mBoard->collectedChocolateCount;
			mApp->NewParticleSystem(ParticleSystem::Type::PRESENT_PICKUP, layer + 1, x + 30.0f, y + 30.0f);
			if (mApp->mUserData->shopItemBought[(int)Shop::ItemType::CHOCOLATE] < 1000) {
				mBoard->SetBoardText(u8"[ADVICE_FOUND_CHOCOLATE]", BoardText::Type::HINT_TALL_FAST, Board::AdviceType::NIL);
			} else ++mApp->mUserData->shopItemBought[(int)Shop::ItemType::CHOCOLATE];
			vanishCount = 0;
			vanishCountdown = 15;
			if (flag) {
				Attachment* a = (*mApp)[mAttachment];
				if (a)a->RemoveAttacher(ParticleSystem::Type::AWARD_PICKUP_ARROW);
				mBoard->FadeOutLevel();
			}
			return;
		}
		if (isLevelAward()) {
			if (flag) {
				if (type == Type::BAG_DIAMOND) {
					mApp->PlaySample(SOUND_DIAMOND);
					SplashConatins(Type::DIAMOND, 1);
					vanishCountdown = 15;
				} else if (type == Type::BAG_COIN) {
					mApp->NewSample(Sample::Type::ITEM_COIN_COLLECT);
					SplashConatins(Type::GOLD_COIN, 5);
					vanishCountdown = 15;
				}
			} else if (mApp->isVB()) {
				if (type == Type::TROPHY) {
					mApp->NewSample(Sample::Type::ITEM_COIN_COLLECT);
					SplashConatins(Type::GOLD_COIN, 5);
				} else if (type == Type::BAG_COIN_AWARD) {
					mApp->NewSample(Sample::Type::ITEM_COIN_COLLECT);
					SplashConatins(Type::GOLD_COIN, 2);
				}
			} else if (mApp->isAdventure() && mBoard->adventureLevelRank == 50) {
				SplashConatins(Type::DIAMOND, 3);
			} else if (mApp->isFirseTimeAdventure() && mBoard->adventureLevelRank == 4) {
				mApp->PlaySample(SOUND_SHOVEL);
			} else if (mApp->isAdventure() && inrange(mBoard->adventureLevelRank, 24, 34, 44)) {
				mApp->PlaySample(SOUND_TAP2);
			} else if (type == Type::TROPHY) {
				mApp->PlaySample(SOUND_DIAMOND);
				SplashConatins(Type::DIAMOND, 1);
			} else if (type == Type::BAG_COIN_AWARD) {
				mApp->NewSample(Sample::Type::ITEM_COIN_COLLECT);
				SplashConatins(Type::GOLD_COIN, 5);
			} else {
				mApp->PlaySample(SOUND_SEEDLIFT);
				mApp->PlaySample(SOUND_TAP2);
			}
			mApp->NewParticleSystem(ParticleSystem::Type::STARBURST, layer + 1, x + 30.0f, y + 30.0f);
			mBoard->FadeOutLevel();
			Attachment* a = (*mApp)[mAttachment];
			if (a) {
				a->RemoveAttacher(ParticleSystem::Type::SEED_PACKET);
				a->RemoveAttacher(ParticleSystem::Type::AWARD_PICKUP_ARROW);
				a->RemoveAttacher(ParticleSystem::Type::COIN_PICKUP_ARROW);
			}
			if (type == Type::LETTER) {
				mApp->NewParticleSystem(ParticleSystem::Type::PRESENT_PICKUP, layer + 1, x + 30.0f, y + 30.0f);
				vanishCountdown = 15;
			} else if (!flag && mApp->Is3DAccelerated()) {
				ParticleSystem* p = mApp->NewParticleSystem(ParticleSystem::Type::SEED_PACKET_PICKUP, layer - 1, x + (float)(mW / 2), y + (float)(mH / 2));
				if (p)Global::AttachParticle(mAttachment, p, (float)(mW / 2), (float)(mH / 2));
			}
			vanishCount = 0;
			return;
		}
		if (type == Type::CARD) {
			mBoard->mMouseProp->handCardType = cardType;
			mBoard->mMouseProp->handItemType = MouseProp::Type::ITEM_CARD;
			mBoard->mMouseProp->mItemID = GetID(*this);
			yTarget = (int)y;
			vanishCountdown = 0;
			return;
		}
		if (isMoney() && mBoard)mBoard->moneyShowCountdown = 1000;
		vanishCountdown = 0;
		if (isSun() && !mApp->isBelt()) {
			int collectingSunVal = mBoard->GetCollectingSunValue();
			for (int i = 0; i < mBoard->mSlot->SlotCount; ++i) {
				Card& card = mBoard->mSlot->mCards[i];
				int sundiff = mBoard->GetCardCost(card.trueType()) - mBoard->sunValue - collectingSunVal;
				if (sundiff > 0 && sundiff < BasicProp(card.trueType()).cost)card.Shine();
			}
			if (mApp->isFog())layer = 800002;
		}
		Attachment* a = (*mApp)[mAttachment];
		if (a)a->RemoveAttacher(ParticleSystem::Type::AWARD_PICKUP_ARROW);
		if (mApp->isFirseTimeAdventure() && mBoard && mBoard->adventureLevelRank == 11 && (type == Type::GOLD_COIN || type == Type::SILVER_COIN)) {
			mBoard->SetBoardText(u8"[ADVICE_CLICKED_ON_COIN]", BoardText::Type::HINT_FAST, Board::AdviceType::CLICKED_ON_COIN);
		}
	}

	int Board::GetPlantCount(Plant::Type type) {
		Plant* p = nullptr;
		int ans = 0;
		for (auto&& p : mPlantList)if (p.type == type)++ans;
		return ans;
	}

	int Board::GetCardCost(Card::Type type) {
		int ans = BasicProp(type).cost;
		if (BasicProp(type).typeGroup != Card::TypeGroup::PLANT)return ans;
		if (BasicProp(type).upgradeBase == Plant::Type::NIL)return ans;
		return ans + 50 * GetPlantCount(BasicProp(type).plantType);
	}

	void Item::UpdateFall() {
		if (movementState == MovementState::FROM_PRESENT) {
			x += dx;
			y += dy;
			dx *= 0.857f;
			dy *= 0.857f;
			if (existTime >= 80) {
				Collected();
			}
		} else if (y + dy < (float)yTarget) {
			y += dy;
			if (movementState == MovementState::FROM_PLANT)dy += 0.09f;
			else if (movementState == MovementState::DROPPED || movementState == MovementState::FROM_BOSS)dy += 0.15f;
			x += dx;
			if (x > (float)(800 - mW) && movementState != MovementState::FROM_BOSS) {
				x = (float)(800 - mW);
				dx = -rand(0.4f);
			} else if (x < 0.0f) {
				x = 0.0f;
				dx = rand(0.4f, 0.8f);
			}
		} else {
			if (needArrow && !haveArrow) {
				float xdiff = (float)(mW / 2);
				float ydiff = (float)(mH / 2) - 60.0f;
				if (type == Type::TROPHY) {
					xdiff += 2.0f;
				} else if (type == Type::BAG_COIN_AWARD || type == Type::BAG_DIAMOND) {
					xdiff += 2.0f;
					ydiff -= 2.0f;
				} else if (inrange(type,
					Type::PRESENT_PLANT_AWARD,
					Type::PRESENT_MINIGAME,
					Type::PRESENT_PUZZLE,
					Type::PRESENT_SURVIVAL
				)) {
					ydiff -= 20.0f;
				} else if (type == Type::SILVER_SUNFLOWER || type == Type::GOLD_SUNFLOWER) {
					xdiff -= 6.0f;
					ydiff -= 40.0f;
				} else if (isMoney()) {
					xdiff += 12.0f;
					ydiff += 21.0f;
				}
				ParticleSystem::Type theEffect;
				if (type == Type::NEW_CARD)theEffect = ParticleSystem::Type::SEED_PACKET;
				else if (isMoney())theEffect = ParticleSystem::Type::COIN_PICKUP_ARROW;
				else theEffect = ParticleSystem::Type::AWARD_PICKUP_ARROW;
				Global::AttachParticle(mAttachment, mApp->NewParticleSystem(theEffect, 0, x + xdiff, y + ydiff), xdiff, ydiff);
				haveArrow = true;
			}
			if (!onGround) {
				onGround = true;
				PlayGroundSample();
			}
			y = (float)yTarget;
			x = (float)(int)x;
			if ((!mApp->isLS() || mBoard && mBoard->mLevelProp->state == LevelProp::State::LAST_STAND_ONSLAUGHT) && !isLevelAward() && !(type == Type::PRESENT_MINIGAME || type == Type::PRESENT_PUZZLE || type == Type::PRESENT_SURVIVAL)) {
				++vanishCount;
				if (vanishCount >= GetDisappearTime())vanishCountdown = 15;
			}
		}
		if (movementState == MovementState::FROM_PLANT) {
			float sunSize = 1.0f;
			if (type == Type::SUN_LARGE)sunSize = 2.0f;
			else if (type == Type::SUN_SMALL)sunSize = 0.5f;
			if (size < sunSize) {
				size += 0.06f;
			} else size = sunSize;
		}
	}

	int Item::GetDisappearTime() {
		int ans = 750;
		if (or (
			type == Type::DIAMOND,
			type == Type::CHOCOLATE,
			haveArrow,
			type == Type::PRESENT_PLANT
			))ans = 1500;
		if ((mApp->isVB() || mApp->isSlotMachine()) && type == Type::CARD)ans = 1500;
		if (mApp->isGarden())ans = 6000;
		return ans;
	}

	void Item::PlayGroundSample() {
		if (type == Type::GOLD_COIN) {
			mApp->NewSampleF(Sample::Type::ITEM_COIN_FALL_GROUND);
		}
	}

	Color Item::GetColor() {
		if ((isSun() || isMoney()) && collected)return Color(255, 255, 255, limit(89, (int)(targetDistance * 8.925f), 255));
		else if (vanishCountdown > 0)return Color(255, 255, 255, limit(0, vanishCountdown * 17, 255));
		else return Color(255, 255, 255, 255);
	}

	void Item::Update() {
		++existTime;
		if (mApp->gameState != GameApp::State::BATTLE && mApp->gameState != GameApp::State::WIN && mBoard && !mBoard->mSceneProp->ShouldUpsell())return;
		if (vanishCountdown)UpdateVanish();
		else if (collected)UpdateCollected();
		else UpdateFall();
		Attachment* a = (*mApp)[mAttachment];
		if (!a)return;
		a->Update();
		if (type == Type::DIAMOND)a->SetPosition(x + 18.0f - 18.0f * size, y + 13.0f - 13.0f * size);
		else a->SetPosition(x, y);
		a->SetColor(GetColor());
		a->SetSize(size);
		if ((!onGround || collected) && (type == Type::SILVER_COIN || type == Type::GOLD_COIN))a->SetColor(Color(0, 0, 0, 0));
	}

	Rect Mower::GetAtkRect() {
		return Rect((int)x, (int)y, 50, 80);
	}

	void Mower::Start() {
		if (state == State::WORK)return;
		Anim* reanimation = (*mApp)[mAnimID];
		if (type == Type::POOL) {
			reanimation->updateV = 35.0f;
			mApp->NewSampleF(Sample::Type::MOWER_ACT_WATER);
		} else {
			reanimation->updateV = 70.0f;
			mApp->NewSampleF(Sample::Type::MOWER_ACT);
		}
		mBoard->rowMoweredWave[row] = mBoard->nowwaveNum;
		++mBoard->mTriggeredLawnMowers;
		state = State::WORK;
	}

	void Mower::Smash(Zombie* that) {
		if (state == State::IDLE) {
			Start();
			slowCountdown = 25;
		} else if (state == State::WORK) {
			slowCountdown = 50;
		}
		if (type == Type::POOL) {
			mApp->NewSampleF(Sample::Type::SHOOP);
			if (movementState == MovementState::POOL) {
				Anim* reanimation = (*mApp)[mAnimID];
				reanimation->SetSegment(u8"anim_suck", Anim::LoopType::PLAY_ONCE_AND_HOLD, 10, 35.0f);
			} else {
				Anim* reanimation = (*mApp)[mAnimID];
				reanimation->SetSegment(u8"anim_landsuck", Anim::LoopType::PLAY_ONCE_AND_HOLD, 10, 35.0f);
			}
			that->KillWithItem();
			return;
		}
		mApp->NewSampleF(Sample::Type::SPLAT);
		that->Mowered();
	}

	void Mower::Update() {
		if (state == State::SMASHED) {
			--vanishCountdown;
			if (vanishCountdown <= 0)return Kill();
		}
		if (state == State::PREPARE) {
			++prepareCountup;
			x = getCurveValue(4, 0, 100, -160.0f, -21.0f, prepareCountup);
			if (prepareCountup >= 100)state = State::IDLE;
			return;
		}
		if (mApp->gameState != GameApp::State::BATTLE && !mBoard->mSceneProp->ShouldUpsell())return;
		Rect lawnMowerAttackRect = GetAtkRect();
		for (auto p = mBoard->mZombieList.begin(); p != mBoard->mZombieList.end(); ++p) {
			if (p->type != Zombie::Type::ZOMBOSS && p->row == row && p->state != Zombie::State::MOWERED && !p->isTangleTarget()) {
				int theDamageRangeFlags = 127;
				if (p->inRange(HitRange::GROUND | HitRange::AIR | HitRange::SUBMERGE | HitRange::DOG | HitRange::OFF_GROUND | HitRange::DYING | HitRange::UNDERGROUND)) {
					int rectOverlap = lawnMowerAttackRect.IntersectWidth(p->GetDefRect());
					if (p->type == Zombie::Type::BALLOON_ZOMBIE)rectOverlap -= 20;
					if (rectOverlap > 0 && (state != State::IDLE || (p->type != Zombie::Type::BUNGEE_ZOMBIE && p->haveHead)))Smash(&*p);
				}
			}
		}
		if (state != State::WORK && state != State::SMASHED) {
			return;
		}
		float xdiff = 3.33f;
		if (type == Type::POOL)xdiff = 2.5f;
		if (slowCountdown > 0) {
			slowCountdown -= 1;
			xdiff = getCurveValue(11, 50, 0, xdiff, 1.0f, slowCountdown);
		}
		x += xdiff;
		y = mBoard->GetY(x + 40.0f, row) + 23.0f;
		if (type == Type::POOL) {
			UpdatePool();
		}
		if (type == Type::LAWN && mBoard->rowSpawnType[row] == Board::SpawnType::Water && x > 50.0f) {
			Anim* reanimation = mApp->NewAnim(Anim::Type::SPLASH, layer + 1, x, y + 25.0f);
			reanimation->mPosition.xStrech = 1.2f;
			reanimation->mPosition.yStrech = 0.8f;
			mApp->NewParticleSystem(ParticleSystem::Type::PLANTING_POOL, layer + 1, x + 50.0f, y + 67.0f);
			mApp->PlaySample(SOUND_ZOMBIE_ENTERING_WATER);
			mApp->mSampleManagers->StopSample(Sample::Type::MOWER_ACT);
			Kill();
		}
		if (x > 800.0f)Kill();
		Anim* reanimation = (*mApp)[mAnimID];
		if (reanimation)reanimation->Update();
	}

	void Mower::UpdatePool() {
		bool flag = false;
		if (x > 150.0f && x < 770.0f)flag = true;
		Anim* reanimation = (*mApp)[mAnimID];
		if (flag && movementState == MovementState::LAND) {
			Anim* reanimation2 = mApp->NewAnim(Anim::Type::SPLASH, layer + 1, x, y + 25.0f);
			reanimation2->mPosition.xStrech = 1.2f;
			reanimation2->mPosition.yStrech = 0.8f;
			mApp->NewParticleSystem(ParticleSystem::Type::PLANTING_POOL, layer + 1, x + 50.0f, y + 67.0f);
			mApp->NewSampleF(Sample::Type::ZOMBIE_ENTER_WATER);
			movementState = MovementState::DOWN;
		} else if (movementState == MovementState::DOWN) {
			h -= 2.0f;
			if (h <= -28.0f) {
				h = 0.0f;
				movementState = MovementState::POOL;
				reanimation->SetSegment(u8"anim_water", Anim::LoopType::LOOP, 0);
			}
		} else if (movementState == MovementState::POOL) {
			if (!flag) {
				h = -28.0f;
				movementState = MovementState::UP;
				Anim* reanimation2 = mApp->NewAnim(Anim::Type::SPLASH, layer + 1, x, y + 25.0f);
				reanimation2->mPosition.xStrech = 1.2f;
				reanimation2->mPosition.yStrech = 0.8f;
				mApp->NewParticleSystem(ParticleSystem::Type::PLANTING_POOL, layer + 1, x + 50.0f, y + 42.0f);
				mApp->NewSampleF(Sample::Type::PLANT_IN_WATER);
				reanimation->SetSegment(u8"anim_land", Anim::LoopType::LOOP, 0);
			}
		} else if (movementState == MovementState::UP) {
			h += 2.0f;
			if (h >= 0.0f) {
				h = 0.0f;
				movementState = MovementState::LAND;
			}
		}
		if (movementState == MovementState::POOL && reanimation->loopType == Anim::LoopType::PLAY_ONCE_AND_HOLD && reanimation->loopCount > 0) {
			reanimation->SetSegment(u8"anim_water", Anim::LoopType::LOOP, 10, 35.0f);
		}
	}

	void MouseProp::Update() {
		if (mApp->gameState != GameApp::State::BATTLE && mBoard->tutorial != Board::Tutorial::SHOVEL_PICKUP && mBoard->tutorial != Board::Tutorial::SHOVEL_DIG && mBoard->tutorial != Board::Tutorial::SHOVEL_KEEP_DIGGING) {
			visible = false;
			return;
		}
		if (!mApp->mWidgetManager->mMouseIn) {
			visible = false;
			return;
		}
		Anim* reanimation = (*mApp)[mAnimID];
		if (reanimation)reanimation->Update();
		visible = true;
		mX = mApp->mWidgetManager->mLastMouseX - 25;
		mY = mApp->mWidgetManager->mLastMouseY - 35;
	}

	Card::Type LevelProp::GetGridShadow(int col, int row) {
		if (row < 0 || row > 5 || col < 0 || col > 8)return Card::Type::NIL;
		if (mApp->level == GameApp::Level::Type::ART_WALL_NUT) {
			return gArtChallengeWallnut[col + 9 * row];
		}
		if (mApp->level == GameApp::Level::Type::ART_SUNFLOWER) {
			return gArtChallengeSunFlower[col + 9 * row];
		}
		if (mApp->level == GameApp::Level::Type::SEEING_STARS) {
			return gArtChallengeStarfruit[col + 9 * row];
		}
		return Card::Type::NIL;
	}

	CardReject LevelProp::GetCardReject(int col, int row, Card::Type type) {
		if (mApp->isBowling()) {
			if (col > 2) return CardReject::NOT_PASSED_LINE;
			return CardReject::NIL;
		}
		if (mApp->isIZ()) {
			int num = 6;
			if (inrange(mApp->level, GameApp::Level::Type::I_ZOMBIE_1, GameApp::Level::Type::I_ZOMBIE_2, GameApp::Level::Type::I_ZOMBIE_3, GameApp::Level::Type::I_ZOMBIE_4, GameApp::Level::Type::I_ZOMBIE_5)) num = 4;
			else if (inrange(mApp->level, GameApp::Level::Type::I_ZOMBIE_6, GameApp::Level::Type::I_ZOMBIE_7, GameApp::Level::Type::I_ZOMBIE_8, GameApp::Level::Type::I_ZOMBIE_ENDLESS)) num = 5;
			if (type == Card::Type::ZOMBIE_BUNGEE) {
				if (col < num) 	return CardReject::NIL;
				return CardReject::NOT_HERE;
			}
			if (BasicProp(type).typeGroup == Card::TypeGroup::ZOMBIE) {
				if (col >= num) return CardReject::NIL;
				return CardReject::NOT_HERE;
			}
			return CardReject::NIL;
		}
		if (mApp->isArt()) {
			Card::Type artChallengeSeed = GetGridShadow(col, row);
			if (artChallengeSeed != Card::Type::NIL && artChallengeSeed != type && type != Card::Type::LILY_PAD && type != Card::Type::PUMPKIN) return CardReject::NOT_ON_ART;
			if (mApp->level == GameApp::Level::Type::ART_WALL_NUT) {
				if (col == 4 && row == 1) return CardReject::NOT_HERE;
				if (col == 6 && row == 1) return CardReject::NOT_HERE;
				return CardReject::NIL;
			}
		}
		if (mApp->isBoss() && col >= 8) return CardReject::NOT_HERE;
		return CardReject::NIL;
	}

	bool Board::canPlantCobHelper(int col, int row) {
		GridPlantList list = GetGridPlantList(col, row);
		if (list.mMiddle)return false;
		if (!mApp->freePlant)return list.mMain && list.mMain->type == Plant::Type::KERNEL_PULT;
		return(list.mMain && list.mMain->type == Plant::Type::KERNEL_PULT) || GetCardReject(col, row, Card::Type::KERNEL_PULT) == CardReject::NIL;
	}

	bool Board::canPlantCob(int col, int row) {
		if (!canPlantCobHelper(col, row) || !canPlantCobHelper(col + 1, row))return false;
		bool flag = GetGridPlant(col, row, Plant::Type::FLOWER_POT);
		bool flag2 = GetGridPlant(col + 1, row, Plant::Type::FLOWER_POT);
		return flag == flag2;
	}

	bool Board::canPlant(Card::Type type) {
		for (int i = 0; i < 9; ++i)for (int j = 0; j < 6; ++j)if (GetCardReject(i, j, type) == CardReject::NIL)return true;
		return false;
	}

	CardReject Board::GetCardReject(int col, int row, Card::Type type) {
		if (col < 0 || col > 8 || row < 0 || row > 5)return CardReject::NOT_HERE;
		CardReject cardReject = mLevelProp->GetCardReject(col, row, type);
		if (cardReject != CardReject::NIL || BasicProp(type).typeGroup == Card::TypeGroup::ZOMBIE)return cardReject;
		GridPlantList list = GetGridPlantList(col, row);
		if (mApp->isGarden()) {
			if (list.mBottom || list.mMain || list.mTop || list.mMiddle)return CardReject::NOT_HERE;
			if (mApp->mGardenProp->type == GardenProp::YardType::AQUARIUM && !BasicProp(type).inWater)return CardReject::NOT_ON_WATER;
			return CardReject::NIL;
		}
		if (type == Card::Type::GRAVE_BUSTER) {
			if (list.mMain)return CardReject::NOT_HERE;
			if (GetGridBuilding(col, row, Building::Type::GRAVE))return CardReject::NIL;
			return CardReject::ONLY_ON_GRAVES;
		}
		if (type == Card::Type::COFFEE_BEAN) {
			if (list.mTop)return CardReject::NOT_HERE;
			if (!list.mMain || !list.mMain->slept || list.mMain->wakeupCountdown > 0 || list.mMain->bungeeProp == Plant::BungeeProp::GRABBED)return CardReject::NEEDS_SLEEPING;
			return CardReject::NIL;
		}
		if (GetGridBuilding(col, row, Building::Type::GRAVE))return CardReject::NOT_ON_GRAVE;
		if (GetGridBuilding(col, row, Building::Type::CRATER))return CardReject::NOT_ON_CRATER;
		if (GetGridBuilding(col, row, Building::Type::VASE))return CardReject::NOT_HERE;
		bool lilypad = list.mBottom && list.mBottom->type == Plant::Type::LILY_PAD && list.mBottom->bungeeProp != Plant::BungeeProp::GRABBED;
		bool flowerpot = list.mBottom && list.mBottom->type == Plant::Type::FLOWER_POT && list.mBottom->bungeeProp != Plant::BungeeProp::GRABBED;
		if (isIceCovered(col, row))return CardReject::NOT_HERE;
		if (gridType[col][row] == GridType::DIRT || gridType[col][row] == GridType::NIL)return CardReject::NOT_HERE;
		if (type == Card::Type::LILY_PAD || type == Card::Type::TANGLE_KELP || type == Card::Type::SEA_SHROOM) {
			if (gridType[col][row] != GridType::POOL)return CardReject::ONLY_IN_POOL;
			if (list.mMain || list.mBottom)return CardReject::NOT_HERE;
			return CardReject::NIL;
		}
		if ((type == Card::Type::SPIKEWEED || type == Card::Type::SPIKEROCK) && (gridType[col][row] == GridType::POOL || BasicProp(yard).onRoof || list.mBottom))return CardReject::NEEDS_GROUND;
		if (gridType[col][row] == GridType::POOL && !lilypad && type != Card::Type::CATTAIL && (!list.mMain || list.mMain->type != Plant::Type::CATTAIL || type != Card::Type::PUMPKIN))return CardReject::NOT_ON_WATER;
		if (type == Card::Type::FLOWER_POT) {
			if (list.mMain || list.mBottom || list.mMiddle)return CardReject::NOT_HERE;
			return CardReject::NIL;
		}
		if (BasicProp(yard).onRoof && !flowerpot)return CardReject::NEEDS_POT;
		if (type == Card::Type::PUMPKIN) {
			if (list.mMain && list.mMain->type == Plant::Type::COB_CANNON)return CardReject::NOT_HERE;
			if (!list.mMiddle)return CardReject::NIL;
			if (mApp->mUserData->shopItemBought[(int)Shop::ItemType::FIRSTAID] && list.mMiddle->hp < list.mMiddle->hpMax * 2 / 3 && Plant::Type::PUMPKIN == list.mMiddle->type && list.mMiddle->bungeeProp != Plant::BungeeProp::GRABBED)return CardReject::NIL;
			return CardReject::NOT_HERE;
		}
		if (lilypad && type == Card::Type::POTATO_MINE)return CardReject::ONLY_ON_GROUND;
		if (list.mBottom && type == Card::Type::CATTAIL) {
			if (list.mMain)return CardReject::NOT_HERE;
			if (list.mBottom->type == BasicProp(type).upgradeBase && list.mBottom->bungeeProp != Plant::BungeeProp::GRABBED)return CardReject::NIL;
			if (BasicProp(type).upgradeBase != Plant::Type::NIL)return CardReject::NEEDS_UPGRADE;
		}
		if (list.mBottom && list.mBottom->type == Plant::Type::IMITATER)return CardReject::NOT_HERE;
		if (!list.mMain) {
			if (!mApp->freePlant) {
				if (BasicProp(type).upgradeBase != Plant::Type::NIL)return CardReject::NEEDS_UPGRADE;
				return CardReject::NIL;
			}
			if (type == Card::Type::COB_CANNON && !canPlantCob(col, row))return CardReject::NEEDS_UPGRADE;
			if (type == Card::Type::CATTAIL && gridType[col][row] != GridType::POOL)return CardReject::NOT_HERE;
			return CardReject::NIL;
		}
		if (list.mMain->type == BasicProp(type).upgradeBase && list.mMain->bungeeProp != Plant::BungeeProp::GRABBED)return CardReject::NIL;
		if (BasicProp(type).upgradeBase != Plant::Type::NIL)return CardReject::NEEDS_UPGRADE;
		if ((type == Card::Type::WALL_NUT || type == Card::Type::TALL_NUT) && mApp->mUserData->shopItemBought[(int)Shop::ItemType::FIRSTAID] && list.mMain->hp < list.mMain->hpMax * 2 / 3 && Plant::Type::WALL_NUT == list.mMain->type && list.mMain->bungeeProp != Plant::BungeeProp::GRABBED)return CardReject::NIL;
		return CardReject::NOT_HERE;
	}

	void MouseAddProp::Update() {
		visible = false;
		if (mApp->gameState != GameApp::State::BATTLE)return;
		if (!mApp->mWidgetManager->mMouseIn)return;
		Card::Type theType = mBoard->GetHandPlantType();
		mouseCol = mBoard->GetCol(theType, mApp->mWidgetManager->mLastMouseX, mApp->mWidgetManager->mLastMouseY);
		mouseRow = mBoard->GetRow(theType, mApp->mWidgetManager->mLastMouseX, mApp->mWidgetManager->mLastMouseY);
		if (mouseCol < 0 || mouseCol > 8 || mouseRow < 0 || mouseRow > 5)return;
		if (theType != Card::Type::NIL && mBoard->GetCardReject(mouseCol, mouseRow, theType) == CardReject::NIL) {
			mX = mBoard->GetX(mouseCol, mouseRow);
			mY = mBoard->GetY(mouseCol, mouseRow);
			visible = true;
		}
	}

	int Board::GetCol(Card::Type type, int x, int y) {
		if (type == Card::Type::GRAVE_BUSTER || type == Card::Type::COFFEE_BEAN)y += 15;
		if (type == Card::Type::SPIKEWEED || type == Card::Type::SPIKEROCK)y -= 15;
		if (mApp->isGarden() && yard == Yard::Type::GREENHOUSE)y -= 25;
		return GetCol(x, y);
	}

	GridPlantList Board::GetGridPlantList(int col, int row) {
		GridPlantList ans{};
		ans.mBottom = nullptr;
		ans.mMiddle = nullptr;
		ans.mTop = nullptr;
		ans.mMain = nullptr;
		if (col < 0 || col > 8 || row < 0 || row > 5)return ans;
		if (mApp->isBowling() && tutorial != Tutorial::SHOVEL_PICKUP && tutorial != Tutorial::SHOVEL_DIG && tutorial != Tutorial::SHOVEL_KEEP_DIGGING)return ans;
		for (auto&& p : mPlantList) {
			Plant::Type theType = p.type == Plant::Type::IMITATER ? p.imitaterType : p.type;
			if (theType == Plant::Type::COB_CANNON) {
				if (p.col < col - 1 || p.col > col)continue;
				if (p.row != row)continue;
			} else if (p.col != col || p.row != row)continue;
			if (p.isFlying())continue;
			if (theType == Plant::Type::COFFEE_BEAN)ans.mTop = &p;
			else if (theType == Plant::Type::FLOWER_POT)ans.mBottom = &p;
			else if (theType == Plant::Type::LILY_PAD) {
				if (mApp->isGarden())ans.mMain = &p;
				else ans.mBottom = &p;
			} else if (theType == Plant::Type::PUMPKIN)ans.mMiddle = &p;
			else ans.mMain = &p;
		}
		return ans;
	}

	int Board::GetRow(Card::Type type, int x, int y) {
		if (type == Card::Type::GRAVE_BUSTER || type == Card::Type::COFFEE_BEAN)y += 15;
		if (type == Card::Type::SPIKEWEED || type == Card::Type::SPIKEROCK)y -= 15;
		if (mApp->isGarden() && yard == Yard::Type::GREENHOUSE)y -= 25;
		if (type != Card::Type::COFFEE_BEAN)return GetRow(x, y);
		GridPlantList list;
		int theRow = GetRow(x, y);
		if (mApp->isBowling() && tutorial != Tutorial::SHOVEL_PICKUP && tutorial != Tutorial::SHOVEL_DIG && tutorial != Tutorial::SHOVEL_KEEP_DIGGING)return theRow;
		int theCol = GetCol(x, y);
		if (theCol <= 8 && theRow <= 5) {
			list = GetGridPlantList(theCol, theRow);
			if (list.mMain && list.mMain->slept)return theRow;
		}
		theCol = GetCol(x, y + 30);
		theRow = GetRow(x, y + 30);
		if (theCol <= 8 && theRow <= 5) {
			list = GetGridPlantList(theCol, theRow);
			if (list.mMain && list.mMain->slept)return theRow;
		}
		theCol = GetCol(x, y - 50);
		theRow = GetRow(x, y - 50);
		if (theCol <= 8 && theRow <= 5) {
			list = GetGridPlantList(theCol, theRow);
			if (list.mMain && list.mMain->slept)return theRow;
		}
		return GetRow(x, y);
	}

	GardenPlant* GardenProp::GetCartPlant() {
		for (int i = 0; i < mApp->mUserData->gardenPlantCount; ++i)if (mApp->mUserData->mGardenPlant[i].gardenYard == YardType::CART)return mApp->mUserData->mGardenPlant + i;
		return nullptr;
	}

	Card::Type Board::GetHandPlantType() {
		if (mMouseProp->handItemType == MouseProp::Type::CART && mApp->mGardenProp->GetCartPlant())return BasicProp(mApp->mGardenProp->GetCartPlant()->type).cardType;
		if (!inrange(mMouseProp->handItemType,
			MouseProp::Type::SLOT_CARD,
			MouseProp::Type::ITEM_CARD,
			MouseProp::Type::GLOVE_PLANT,
			MouseProp::Type::DUPLICATOR_PLANT,
			MouseProp::Type::CART_PLANT
		))return Card::Type::NIL;
		return mMouseProp->trueCardType();
	}

	bool Card::canPick() {
		if (mBoard->pause || mApp->gameState != GameApp::State::BATTLE)return false;
		if (type == Type::NIL)return false;
		if (mApp->isSlotMachine())return false;
		if (mApp->freePlant)return true;
		if (!useable)return false;
		if (mBoard->GetCardCost(trueType()) > mBoard->sunValue + mBoard->GetCollectingSunValue())return false;
		return mBoard->canPlant(trueType());
	}

	void Board::SetTutorialArrow(int x, int y) {
		ParticleSystem* todParticleSystem = (*mApp)[adviceArrow];
		if (todParticleSystem)todParticleSystem->Kill();
		todParticleSystem = mApp->NewParticleSystem(ParticleSystem::Type::SEED_PACKET_PICK, 800000, (float)x, (float)y);
		adviceArrow = GetID(*todParticleSystem);
	}

	Rect Board::GetShovelRect() {
		Rect ans(0, 0, 70, 72);
		switch (mSlot->SlotCount) {
		case 7:ans.mX = 516; break;
		case 8:ans.mX = 532; break;
		case 9:ans.mX = 568; break;
		case 10:ans.mX = 609; break;
		default:ans.mX = 456; break;
		}
		if (mApp->level == GameApp::Level::Type::SLOT_MACHINE || mApp->level == GameApp::Level::Type::SQUIRREL)ans.mX = 600;
		return ans;
	}

	void Board::SetTutorial(Tutorial type) {
		switch (type) {
		case Tutorial::LEVEL1_PICK_PEASHOOTER:
		{
			if (mPlantList.mSize == 0) {
				SetTutorialArrow(mSlot->mX + mSlot->mCards[0].mX, mSlot->mY + mSlot->mCards[0].mY);
				SetBoardText(u8"[ADVICE_CLICK_SEED_PACKET]", BoardText::Type::TUTORIAL_LEVEL1_STAY, AdviceType::NIL);
			} else {
				SetBoardText(u8"[ADVICE_ENOUGH_SUN]", BoardText::Type::TUTORIAL_LEVEL1_STAY, AdviceType::NIL);
			}
		}break;
		case Tutorial::LEVEL1_PLANT_PEASHOOTER:
		{
			tutorialCountdown = -1;
			ParticleSystem* todParticleSystem = (*mApp)[adviceArrow];
			if (todParticleSystem)todParticleSystem->Kill();
			adviceArrow = 0;
			if (mPlantList.mSize == 0) {
				SetBoardText(u8"[ADVICE_CLICK_ON_GRASS]", BoardText::Type::TUTORIAL_LEVEL1_STAY, AdviceType::NIL);
			} else {
				KillBoardText(AdviceType::NIL);
			}
		}break;
		case Tutorial::LEVEL1_REFRESH_PEASHOOTER:
		{
			SetBoardText(u8"[ADVICE_PLANTED_PEASHOOTER]", BoardText::Type::TUTORIAL_LEVEL1_STAY, AdviceType::NIL);
			sunDropCount = 200;
		}break;
		case Tutorial::LEVEL1_COMPLETED:
		{
			SetBoardText(u8"[ADVICE_ZOMBIE_ONSLAUGHT]", BoardText::Type::TUTORIAL_LEVEL1, AdviceType::NIL);
			nextwaveSpawnCountdown = 100;
			nextwaveSpawnCountdownMax = 100;
		}break;
		case Tutorial::LEVEL2_PICK_SUNFLOWER:
		case Tutorial::MORESUN_PICK_SUNFLOWER:
		{
			SetTutorialArrow(mSlot->mX + mSlot->mCards[1].mX, mSlot->mY + mSlot->mCards[1].mY);
		}break;
		case Tutorial::LEVEL2_PLANT_SUNFLOWER:
		case Tutorial::LEVEL2_REFRESH_SUNFLOWER:
		case Tutorial::MORESUN_PLANT_SUNFLOWER:
		case Tutorial::MORESUN_REFRESH_SUNFLOWER:
		{
			ParticleSystem* todParticleSystem = (*mApp)[adviceArrow];
			if (todParticleSystem)todParticleSystem->Kill();
			adviceArrow = 0;
		}break;
		case Tutorial::LEVEL2_COMPLETED:
		{
			if (nowwaveNum == 0)nextwaveSpawnCountdown = 1000, nextwaveSpawnCountdownMax = 1000;
		}break;
		case Tutorial::SLOTMACHINE_PULL:
		{
			SetBoardText(u8"[ADVICE_SLOT_MACHINE_PULL]", BoardText::Type::SLOT_MACHINE, AdviceType::SLOT_MACHINE_PULL);
		}break;
		case Tutorial::SLOTMACHINE_COMPLETED:
		{
			KillBoardText(AdviceType::SLOT_MACHINE_PULL);
		}break;
		case Tutorial::SHOVEL_PICKUP:
		{
			SetBoardText(u8"[ADVICE_CLICK_SHOVEL]", BoardText::Type::HINT_STAY, AdviceType::NIL);
			Rect temp = GetShovelRect();
			SetTutorialArrow(temp.mX + temp.mW / 2 - 25, temp.mY + temp.mH - 65);
		}break;
		case Tutorial::SHOVEL_DIG:
		{
			SetBoardText(u8"[ADVICE_CLICK_PLANT]", BoardText::Type::HINT_STAY, AdviceType::NIL);
			ParticleSystem* todParticleSystem = (*mApp)[adviceArrow];
			if (todParticleSystem)todParticleSystem->Kill();
			adviceArrow = 0;
		}break;
		case Tutorial::SHOVEL_KEEP_DIGGING:
		{
			SetBoardText(u8"[ADVICE_KEEP_DIGGING]", BoardText::Type::HINT_STAY, AdviceType::NIL);
		}break;
		case Tutorial::SHOVEL_COMPLETED:
		{
			KillBoardText(AdviceType::NIL);
			mSceneProp->sceneTime = 1500;
			mSceneProp->daveTalkID = 2410;
		}break;
		default:
			tutorial = type;
		}
	}

	void Card::Flash() {
		if (!canPick())return;
		if (mApp->freePlant)return;
		if (mBoard->tutorial == Board::Tutorial::LEVEL1_REFRESH_PEASHOOTER)return mBoard->SetTutorial(Board::Tutorial::LEVEL1_PICK_PEASHOOTER);
		if (mBoard->tutorial == Board::Tutorial::LEVEL2_REFRESH_SUNFLOWER && type == Type::SUNFLOWER)return mBoard->SetTutorial(Board::Tutorial::LEVEL2_PICK_SUNFLOWER);
		if (mBoard->tutorial == Board::Tutorial::MORESUN_REFRESH_SUNFLOWER && type == Type::SUNFLOWER)return mBoard->SetTutorial(Board::Tutorial::MORESUN_PICK_SUNFLOWER);
	}

	void Card::SlotMachineNext() {
		auto rnd = RndSelecter(Type::SLOTMACHINE_DIAMOND);
		for (auto&& seedType : { Type::SLOTMACHINE_DIAMOND, Type::SLOTMACHINE_SUN, Type::WALL_NUT, Type::SNOW_PEA, Type::PEASHOOTER, Type::SUNFLOWER }) {
			int weight = 100;
			if (seedType == Type::PEASHOOTER)weight = 200 - 20 * limit(0, mBoard->GetPlantCount(Plant::Type::PEASHOOTER), 5);
			if (seedType == Type::SLOTMACHINE_DIAMOND)weight = 30;
			if (slotRank == 2 && seedType != Type::SLOTMACHINE_DIAMOND && (seedType == (this - 1)->slotMachineType || seedType == (this - 2)->slotMachineType))weight += weight >> 1;
			rnd.put(weight, seedType);
		}
		slotMachineType = rnd.get();
	}

	void Card::Update() {
		if (mApp->gameState != GameApp::State::BATTLE)return;
		if (type == Type::NIL)return;
		if (mBoard->timeBattle == 0)Flash();
		if (!useable && inCD && ++CDAcc > CDTarget) {
			CDAcc = 0;
			inCD = false;
			useable = true;
			Flash();
		}
		if (slotMachineCountdown > 0) {
			--slotMachineCountdown;
			slotMachinePosition += limit(0.02f, 0.02f + slotMachineCountdown * 0.0001f, 0.06f);
			if (slotMachinePosition >= 1.0f) {
				type = slotMachineType;
				if (slotMachineCountdown == 0) {
					slotMachinePosition = 0.0f;
					useable = true;
					return;
				}
				slotMachinePosition -= 1.0f;
				SlotMachineNext();
				return;
			} else if (slotMachineCountdown == 0) {
				slotMachineCountdown = 1;
			}
		}
	}

	void LevelProp::SetIZBuild() {
		BasicProp(mApp->level).build(this);
		return;
	}

	void Building::Update() {
		__asm {
			mov eax, this
			mov ecx, 0x44E5E0ul
			call ecx
		}
	}

	void Plant::UpdateAnim() {
		__asm {
			mov eax, this
			mov ecx, 0x464820ul
			call ecx
		}
	}

	void Plant::UpdateBowling() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x462CE0ul
			call eax
			pop edi
		}
	}

	void Plant::UpdateAttack() {
		__asm {
			mov eax, this
			mov ecx, 0x45F8A0ul
			call ecx
		}
	}

	void Plant::UpdateShine() {
		__asm {
			push this
			mov eax, 0x4635C0ul
			call eax
		}
	}

	void Zombie::DieTryEndGame() {
		__asm {
			push this
			mov eax, 0x52FE50ul
			call eax
		}
	}

	void Zombie::UpdateFallGround() {
		__asm {
			mov eax, this
			mov ecx, 0x5336B0ul
			call ecx
		}
	}

	void Zombie::Mowered() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x5327E0ul
			call eax
			pop edi
		}
	}












	void Zombie::UpdateAnim() {
		__asm {
			mov eax, this
			mov ecx, 0x52C310ul
			call ecx
		}
	}

	void Zombie::UpdateAnimate() {
		__asm {
			mov eax, this
			mov ecx, 0x52BCA0ul
			call ecx
		}
	}

	void Zombie::UpdateEnterChimney() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x534730ul
			call eax
			pop esi
		}
	}

	void Zombie::UpdateAQ() {
		__asm {
			mov eax, this
			mov ecx, 0x5291E0ul
			call ecx
		}
	}

	void Zombie::UpdatePole() {
		__asm {
			push  this
			mov eax, 0x525DC0ul
			call eax
		}
	}

	void Zombie::UpdateCatapult() {
		__asm {
			mov eax, this
			mov ecx, 0x5259D0ul
			call ecx
		}
	}

	void Zombie::UpdateDolphin() {
		__asm {
			mov eax, this
			mov ecx, 0x5261E0ul
			call ecx
		}
	}

	void Zombie::UpdateSnorkle() {
		__asm {
			mov eax, this
			mov ecx, 0x526720ul
			call ecx
		}
	}

	void Zombie::UpdateBalloon() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x525BE0ul
			call eax
			pop edi
		}
	}

	void Zombie::UpdateNewspaper() {
		__asm {
			push this
			mov eax, 0x525CE0ul
			call eax
		}
	}

	void Zombie::UpdateDigger() {
		__asm {
			mov eax, this
			mov ecx, 0x528310ul
			call ecx
		}
	}

	void Zombie::UpdateJack() {
		__asm {
			push this
			mov eax, 0x526AE0ul
			call eax
		}
	}

	void Zombie::UpdateGargantuar() {
		__asm {
			push this
			mov eax, 0x526D10ul
			call eax
		}
	}

	void Zombie::UpdateBobsled() {
		__asm {
			mov eax, this
			mov ecx, 0x528050ul
			call ecx
		}
	}

	void Zombie::UpdateZomboni() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x52A7B0ul
			call eax
			pop esi
		}
	}

	void Zombie::UpdateLadder() {
		__asm {
			mov ebx, this
			mov eax, 0x52A930ul
			call eax
		}
	}

	void Zombie::UpdateYeti() {
		__asm {
			mov eax, this
			mov ecx, 0x52A8E0ul
			call ecx
		}
	}

	void Zombie::UpdateMJ() {
		__asm {
			mov eax, this
			mov ecx, 0x528CA0ul
			call ecx
		}
	}

	void Zombie::UpdateDancer() {
		__asm {
			mov eax, this
			mov ecx, 0x528B80ul
			call ecx
		}
	}

	void Zombie::UpdateIMP() {
		__asm {
			mov eax, this
			mov ecx, 0x5272E0ul
			call ecx
		}
	}

	void Zombie::UpdatePeashooter() {
		__asm {
			mov eax, this
			mov ecx, 0x5273D0ul
			call ecx
		}
	}

	void Zombie::UpdateJalapeno() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x5275C0ul
			call eax
			pop edi
		}
	}

	void Zombie::UpdateGatling() {
		__asm {
			mov eax, this
			mov ecx, 0x527750ul
			call ecx
		}
	}

	void Zombie::UpdateSquash() {
		__asm {
			push this
			mov eax, 0x527AA0ul
			call eax
		}
	}

	void Zombie::UpdateZomboss() {
		__asm {
			mov eax, this
			mov ecx, 0x536080ul
			call ecx
		}
	}

	void Zombie::UpdateBungee() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x525180ul
			call eax
			pop edi
		}
	}

	void Zombie::UpdatePogo() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x525480ul
			call eax
			pop edi
		}
	}

	void Plant::UpdateSquash() {
		__asm {
			push this
			mov eax, 0x4609D0ul
			call eax
		}
	}

	void Plant::UpdateDoomshroom() {
		__asm {
			mov eax, this
			mov ecx, 0x460DD0ul
			call ecx
		}
	}

	void Plant::UpdateChomper() {
		__asm {
			mov eax, this
			mov ecx, 0x461320ul
			call ecx
		}
	}

	void Plant::UpdateBlover() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x460F00ul
			call eax
			pop edi
		}
	}

	void Plant::UpdateImitater() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x466CA0ul
			call eax
			pop edi
		}
	}

	void Plant::UpdateCoffeeBean() {
		__asm {
			mov ecx, this
			mov eax, 0x460F60ul
			call eax
		}
	}

	void Plant::UpdateUmbrellaleaf() {
		__asm {
			mov eax, this
			mov ecx, 0x460FA0ul
			call ecx
		}
	}

	void Plant::UpdateCobcannon() {
		__asm {
			mov eax, this
			mov ecx, 0x461020ul
			call ecx
		}
	}

	void Plant::UpdateCactus() {
		__asm {
			mov eax, this
			mov ecx, 0x4611F0ul
			call ecx
		}
	}

	void Plant::UpdateMagnetshroom() {
		__asm {
			push this
			mov eax, 0x461D90ul
			call eax
		}
	}

	void Plant::UpdateGoldmagnet() {
		__asm {
			mov eax, this
			mov ecx, 0x462680ul
			call ecx
		}
	}

	void Plant::UpdateSunshroom() {
		__asm {
			mov eax, this
			mov ecx, 0x45FB70ul
			call ecx
		}
	}

	void Plant::UpdateGravebuster() {
		__asm {
			push this
			mov eax, 0x45FC70ul
			call eax
		}
	}

	void Plant::UpdateTorchwood() {
		__asm {
			push this
			mov eax, 0x460610ul
			call eax
		}
	}

	void Plant::UpdatePotatomone() {
		__asm {
			mov eax, this
			mov ecx, 0x45FE20ul
			call ecx
		}
	}

	void Plant::UpdateSpike() {
		__asm {
			mov eax, this
			mov ecx, 0x460370ul
			call ecx
		}
	}

	void Plant::UpdateTanglekelp() {
		__asm {
			push this
			mov eax, 0x460060ul
			call eax
		}
	}

	void Plant::UpdateScardyshroom() {
		__asm {
			push this
			mov eax, 0x460420ul
			call eax
		}
	}

	void Plant::UpdateProducer() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x45F9A0ul
			call eax
			pop edi
		}
	}

	void Plant::UpdateIceshroom() {
		if (!slept && state != State::EXPLODE)state = State::EXPLODE, suicideCountdown = 100;
	}

	void Plant::UpdateLilypad() {
		if (state == State::LILYPAD_INVULNERABLE && propCountdown == 0)state = State::NIL;
	}

	void Plant::UpdateFlowerpot() {
		if (state == State::FLOWERPOT_INVULNERABLE && propCountdown == 0)state = State::NIL;
	}

	void LevelProp::UpdateLS() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x42C5C0ul
			call eax
			pop esi
		}
	}

	void LevelProp::UpdateSeedRain() {
		__asm {
			push this
			mov eax, 0x4234A0ul
			call eax
		}
	}

	void LevelProp::UpdatePortal() {
		__asm {
			mov eax, this
			mov ecx, 0x42C2C0ul
			call ecx
		}
	}

	void LevelProp::UpdateSquirrel() {
		__asm {
			push this
			mov eax, 0x423800ul
			call eax
		}
	}

	void LevelProp::UpdateSlotMachine() {
		__asm {
			push this
			mov eax, 0x423800ul
			call eax
		}
	}

	void LevelProp::UpdateIZ() {
		__asm {
			push this
			mov eax, 0x42B340ul
			call eax
		}
	}

	void LevelProp::UpdateHammer() {
		__asm {
			mov eax, this
			mov ecx, 0x42C9B0ul
			call ecx
		}
	}

	void LevelProp::UpdateZombieAQ() {
		__asm {
			push this
			mov eax, 0x4280A0ul
			call eax
		}
	}

	void LevelProp::UpdateWT() {
		__asm {
			mov eax, this
			mov ecx, 0x42D680ul
			call ecx
		}
	}

	void LevelProp::UpdateVB() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x4296F0ul
			call eax
			pop esi
		}
	}

	void LevelProp::UpdateBejeveled() {
		__asm {
			mov ecx, this
			mov eax, 0x4229F0ul
			call eax
		}
	}

	void LevelProp::UpdateBelt() {
		__asm {
			push this
			mov eax, 0x422CD0ul
			call eax
		}
	}

	void LevelProp::UpdateRain() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x42C340ul
			call eax
			pop edi
		}
	}

	void LevelProp::UpdateThunderEffect() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x423670ul
			call eax
			pop edi
		}
	}

































































	static bool __extendWnd = true;
	void WndAttach(bool a) {
		__extendWnd = a;
		ShowWindow(gGameApp->mHWnd, SW_HIDE);
		if (a) {
			*(DWORD*)0x43b41aul = 1660;
			*(DWORD*)0x43b916ul = 1660;
			*(DWORD*)0x43ba53ul = 1660;
			*(DWORD*)0x484e37ul = 1660;
			*(DWORD*)0x484f1aul = 1660;
			gGameApp->mWidth = 1280;
			gGameApp->mHeight = 720;
		} else {
			*(DWORD*)0x43b41aul = 1180;
			*(DWORD*)0x43b916ul = 1180;
			*(DWORD*)0x43ba53ul = 1180;
			*(DWORD*)0x484e37ul = 1180;
			*(DWORD*)0x484f1aul = 1180;
			gGameApp->mWidth = 800;
			gGameApp->mHeight = 600;
		}
		gGameApp->MakeWindow();
		ShowWindow(gGameApp->mHWnd, SW_SHOW);
	}
	void WndTrans() {
		__extendWnd = !__extendWnd;
		WndAttach(__extendWnd);
	}

	
	void __thiscall GameApp::v_DoMainLoop() {
#ifndef CVP
		HKL keyboard = LoadKeyboardLayoutA(u8"00000409", KLF_ACTIVATE);
		keyboard = ActivateKeyboardLayout(keyboard, 0);
		while (!mShutdown) {
			if (mExitToTop)mExitToTop = false;
			if (mLoadingPage)UpdateApp();
			else Ui::WidgetManager::Update();
			static bool finish = false;
			if (finish)continue;
			if (!mLoadingPage) {
				finish = true;
				for (auto&& str : {
					//u8"Init",
					//u8"LoaderBar",
					//u8"LoadingFonts",
					//u8"LoadingImages",
					//u8"LoadingSounds",
					u8"DelayLoad_Background1",
					u8"DelayLoad_BackgroundUnsodded",
					u8"DelayLoad_Background2",
					u8"DelayLoad_Background3",
					u8"DelayLoad_Background4",
					u8"DelayLoad_Background5",
					u8"DelayLoad_Background6",
					u8"DelayLoad_MushroomGarden",
					u8"DelayLoad_GreenHouseGarden",
					u8"DelayLoad_GreenHouseOverlay",
					u8"DelayLoad_Zombiquarium",
					u8"DelayLoad_TreeOfWisdom",
					u8"DelayLoad_AwardScreen",
					u8"DelayLoad_ChallengeScreen",
					u8"DelayLoad_Almanac",
					u8"DelayLoad_Store",
					u8"DelayLoad_ZombieNote",
					u8"DelayLoad_ZombieNote1",
					u8"DelayLoad_ZombieNote2",
					u8"DelayLoad_ZombieNote3",
					u8"DelayLoad_ZombieNote4",
					u8"DelayLoad_ZombieFinalNote",
					u8"DelayLoad_ZombieNoteHelp",
					u8"DelayLoad_Credits"
					})gGameApp->mResourceManager->LoadGroup(std_string(str));
				for (auto&& p : Cvp::__cvpinit_ereg_base())p();
				for (auto&& p : Cvp::__cvpinit_enum_base())p();
				for (auto&& p : Cvp::__cvpinit_base_base())p();
				for (auto&& p : Cvp::__cvpinit_cach_base())p();
				for (auto&& p : Cvp::__cvpinit_data_base())p();
				Cvp::__cvpinit_ereg_base().clear();
				Cvp::__cvpinit_enum_base().clear();
				Cvp::__cvpinit_base_base().clear();
				Cvp::__cvpinit_cach_base().clear();
				Cvp::__cvpinit_data_base().clear();
				RECT rt;
				GetWindowRect(gGameApp->mHWnd, &rt);
				prevproc = (WNDPROC)SetWindowLongA(gGameApp->mHWnd, GWL_WNDPROC, (LONG)FakeProc);
				WndAttach(__extendWnd);
				gGameApp->debugMode = Cvp::RegRead<bool>(u8"default_bool_debug");
				*(WORD*)0x54eba8ul = Cvp::RegRead<bool>(u8"default_bool_bkgdrun") ? 0x00ebu : 0x2e74u;
				*(QWORD*)0x44f81ful = Cvp::RegRead<bool>(u8"default_bool_noask") ? 0x247c839090909090ull : 0x247c83000009fce8ull;
				Cvp::RegRead<Cvp::KeyCode>(super_pause_key, u8"default_key_super_pause");

				Ui::WidgetManager::SetTab({
					{ u8"默认", Ui::WidgetManager::MakeTabPage({
						/*\■□○●◇◆
						 * //■■■■■□□□□□■■■■■□□□□□■■■■■□□□\\
						 * ■□ debug  □ 后台运行 □ 不再询问重开  关卡调试 /碰撞/□■
						 * ■/存档/  /读档/  刷新速度 /                             /■
						 * ■高级暂停  /高级暂停/         ■
						 * ■□ 上界之风修复  □ 天台火球修复  □ 火球溅射修复       ■
						\*/
						Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(0,0,5),[](bool a) {if (gGameApp)gGameApp->debugMode = a; } ,u8"debug",gGameApp->debugMode),
						Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(10,0,8), [](bool a) {*(WORD*)0x54eba8ul = a ? 0x00ebu : 0x2e74u; }, u8"后台运行", *(WORD*)0x54eba8ul == 0x00ebu),
						Ui::WidgetManager::MakeCheck(Ui::MakeRect_Check(22,0,12), [](bool a) {*(QWORD*)0x44f81ful = a ? 0x247c839090909090ull : 0x247c83000009fce8ull; }, u8"不再询问重开", *(QWORD*)0x44f81ful == 0x247c839090909090ull),
						Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(39,0,8),u8"关卡调试"),
						Ui::WidgetManager::MakeComboList(Ui::MakeRect_Combo(48,0,4), {u8"关闭",u8"刷新",u8"音乐",u8"内存",u8"碰撞"}, [](int val) {if (gGameApp->mBoard)gGameApp->mBoard->debugMode = val; },0),
						Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(0,1,4), []() {if (gGameApp && gGameApp->mBoard)gGameApp->mBoard->Save(); }, u8"存档"),
						Ui::WidgetManager::MakeButton(Ui::MakeRect_Button(8,1,4), []() {if (gGameApp && gGameApp->mBoard)gGameApp->LoadBoard(); }, u8"读档"),
						Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(16,1,8),u8"运行速度"),
						Ui::WidgetManager::MakeSlider_H(Ui::MakeRect_Slider_H(25,1,31),[](float val) {if (gGameApp)gGameApp->mUpdateMultiplier = pow(10.0, val); },20,-1.0f,1.0f,0.0f),
						Ui::WidgetManager::MakeLabel(Ui::MakeRect_Label(0,2,8),u8"高级暂停"),
						Ui::WidgetManager::MakeKeySelector(Ui::MakePos(10,2),super_pause_key)
					})}
					});
				Ui::WidgetManager::SetCmd({
					Ui::MakeCmd(u8"window", []()->bool {return gGameApp && gGameApp->mWidgetManager; })
					(
						Ui::MakeCmd(u8"MouseDown")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,1); })
						(
							Ui::MakeCmd(u8"left")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,1); }),
							Ui::MakeCmd(u8"right")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,-1); }),
							Ui::MakeCmd(u8"mid")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,3); })
						),
						Ui::MakeCmd(u8"MouseUp")																			([](int x,int y) {gGameApp->mWidgetManager->MouseUp(x,y,1); })
						(
							Ui::MakeCmd(u8"left")																			([](int x,int y) {gGameApp->mWidgetManager->MouseUp(x,y,1); }),
							Ui::MakeCmd(u8"right")																			([](int x,int y) {gGameApp->mWidgetManager->MouseUp(x,y,-1); }),
							Ui::MakeCmd(u8"mid")																			([](int x,int y) {gGameApp->mWidgetManager->MouseUp(x,y,3); })
						),
						Ui::MakeCmd(u8"MouseClick")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,1); gGameApp->mWidgetManager->MouseUp(x,y,1); })
						(
							Ui::MakeCmd(u8"left")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,1); gGameApp->mWidgetManager->MouseUp(x,y,1); }),
							Ui::MakeCmd(u8"right")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,-1); gGameApp->mWidgetManager->MouseUp(x,y,-1); }),
							Ui::MakeCmd(u8"mid")																			([](int x,int y) {gGameApp->mWidgetManager->MouseDown(x,y,3); gGameApp->mWidgetManager->MouseUp(x,y,3); })
						),
						Ui::MakeCmd(u8"MouseMove")																			([](int x,int y) {gGameApp->mWidgetManager->MouseMove(x,y); }),
						Ui::MakeCmd(u8"MouseWheel")																			([](int delta) {gGameApp->mWidgetManager->MouseWheel(delta); }),
						Ui::MakeCmd(u8"KeyDown")																			([](KeyCode key) {gGameApp->mWidgetManager->KeyDown(key); }),
						Ui::MakeCmd(u8"KeyUp")																				([](KeyCode key) {gGameApp->mWidgetManager->KeyUp(key); }),
						Ui::MakeCmd(u8"KeyPress")																			([](KeyCode key) {gGameApp->mWidgetManager->KeyDown(key); gGameApp->mWidgetManager->KeyUp(key); })
					),
					Ui::MakeCmd(u8"gameBase", []()->bool {return gGameApp; })
					(
						Ui::MakeCmd(u8"UpdateMultiplier")																	([](float rate) {gGameApp->mUpdateMultiplier = rate; })
					),
					Ui::MakeCmd(u8"board", []()->bool {return gGameApp && gGameApp->mBoard; })
					(
						Ui::MakeCmd(u8"SetSunNum")																			([](int num) {gGameApp->mBoard->sunValue = num; })
					),
					});

				KeyHook() += [](Cvp::KeyCode key) {
					switch (key.Val()) {
					case Cvp::KeyCode::MakeVal(KeyCode::F4):WndTrans(); return true;
					}
					if (key == super_pause_key) { super_pause = !super_pause; return true; }
					return KeyHook().Recur(key);
				};
				for (auto&& p : Cvp::__cvpinit_fnal_base())p();
				Cvp::__cvpinit_fnal_base().clear();
				for (auto&& p : Cvp::__cvpinit_ereg_base())p();
				for (auto&& p : Cvp::__cvpinit_enum_base())p();
				for (auto&& p : Cvp::__cvpinit_base_base())p();
				for (auto&& p : Cvp::__cvpinit_cach_base())p();
				for (auto&& p : Cvp::__cvpinit_data_base())p();
				Cvp::__cvpinit_ereg_base().clear();
				Cvp::__cvpinit_enum_base().clear();
				Cvp::__cvpinit_base_base().clear();
				Cvp::__cvpinit_cach_base().clear();
				Cvp::__cvpinit_data_base().clear();
				Cvp::__cvpinited() = true;
				MainLoopHook()();
			}
		}
		Cvp::RegWrite(super_pause_key, u8"default_key_super_pause");
		Cvp::RegWrite(gGameApp->debugMode, u8"default_bool_debug");
		Cvp::RegWrite(*(WORD*)0x54eba8ul != 0x2e74u, u8"default_bool_bkgdrun");
		Cvp::RegWrite(*(QWORD*)0x44f81ful != 0x247c83000009fce8ull, u8"default_bool_noask");
		if (keyboard)ActivateKeyboardLayout(keyboard, 0);
		for (auto&& p : Cvp::__cvpdestroy_base())p();
		Cvp::__cvpdestroy_base().clear();
#else
		while (!mShutdown) {
			if (mExitToTop)mExitToTop = false;
			UpdateApp();
		}
#endif
	}

	void __thiscall Board::v_MouseDown(int x, int y, int theClickCount) {
		++mUpdateCnt;
		mouseDisabled = !IfShowCursor();
		if (this->glintCountdown) return;
		MouseResult mouseResult = GetMouseResult(x, y);
		if (mLevelProp->MouseDown(x, y, theClickCount, mouseResult))return;
		if (btnMenu->isMouseOver() && !mouseDisabled && theClickCount > 0)mApp->PlaySample(SOUND_GRAVEBUTTON);
		else if (btnStartLS && btnStartLS->isMouseOver() && !mouseDisabled && theClickCount > 0) mApp->PlaySample(mApp->isGardenTree() ? SOUND_TAP : SOUND_GRAVEBUTTON);
		if (mApp->gameState == GameApp::State::SELECT_CARD && mApp->mSelectCardWnd)mApp->mSelectCardWnd->QuitLawnView();
		if (mApp->gameState == GameApp::State::LOSE)return mSceneProp->LoseClick();
		if (mApp->gameState == GameApp::State::SELECT_CARD) mSceneProp->MouseDown();
		if (mApp->debugMode && !mApp->isVB() && nextLevelCountdown > 0) {
			nextLevelCountdown = 2;
			for (int i = 0; i < 6; ++i)if (rowIceCountdown[i] > 2)rowIceCountdown[i] = 2;
		}
		if (mouseResult.type == MouseResult::Type::NIL && mMouseProp->handItemType == MouseProp::Type::AIM) {
			CannonShoot(x, y, theClickCount);
			return CursorInit();
		}
		if (mouseResult.type == MouseResult::Type::ITEM && theClickCount >= 0 && mouseResult.Get<Item>().mBoard) {
			mouseResult.Get<Item>().MouseDown();
			return CursorInit();
		}
		switch (mMouseProp->handItemType) {
		case MouseProp::Type::SHOVEL:
		case MouseProp::Type::POT:
		case MouseProp::Type::FERTILIZE:
		case MouseProp::Type::INSECTICIDE:
		case MouseProp::Type::PHONOGRAPH:
		case MouseProp::Type::CHOCOLATE:
		case MouseProp::Type::GLOVE:
		case MouseProp::Type::SELL:
		case MouseProp::Type::CART:
		case MouseProp::Type::TREE_FERTILIZE:
			UseTool(x, y, theClickCount, mMouseProp->handItemType);
			break;
		case MouseProp::Type::SLOT_CARD:
		case MouseProp::Type::ITEM_CARD:
		case MouseProp::Type::GLOVE_PLANT:
		case MouseProp::Type::DUPLICATOR_PLANT:
		case MouseProp::Type::CART_PLANT:
			UsePlant(x, y, theClickCount);
			break;
		}
		switch (mouseResult.type) {
		case MouseResult::Type::CARD:
			mouseResult.Get<Card>().MouseDown();
			break;
		case MouseResult::Type::NEXT_GARDEN:
			if (mApp->isGarden()) mApp->mGardenProp->Change();
			else if (mApp->level == GameApp::Level::Type::WISDOM_TREE)mLevelProp->WTChange();
			mApp->PlaySample(SOUND_TAP);
			break;
		case MouseResult::Type::SHOVEL:
		case MouseResult::Type::POT:
		case MouseResult::Type::FERTILIZER:
		case MouseResult::Type::INSECTICIDE:
		case MouseResult::Type::PHONOGRAPH:
		case MouseResult::Type::CHOCOLATE:
		case MouseResult::Type::GLOVE:
		case MouseResult::Type::SELL:
		case MouseResult::Type::CART:
		case MouseResult::Type::TREE_FOOD:
			PickTool(mouseResult.type);
			break;
		case MouseResult::Type::PLANT:
			mouseResult.Get<Plant>().MouseDown();
			break;
		}
		return CursorInit();
	}

	void Board::PickTool(MouseResult::Type tool) {
		__asm {
			mov ebx, this
			mov edx, tool
			mov eax, 0x411C10
			call eax
		}
	}

	void Plant::MouseDown() {
		if (state != State::CANNON_LOADED || mBoard->mMouseProp->handItemType != MouseProp::Type::NIL)return;
		mBoard->CursorClear();
		mBoard->mMouseProp->handCardType = Card::Type::NIL;
		mBoard->mMouseProp->handItemType = MouseProp::Type::AIM;
		mBoard->mMouseProp->handPlantSlotRank = -1;
		mBoard->mMouseProp->mItemID = 0;
		mBoard->mMouseProp->mPlantID = GetID(*this);
	}

	void LevelProp::WTChange() {
		__asm {
			mov ecx, this
			mov eax, 0x42D830
			call eax
		}
	}

	void GardenProp::Change() {
		__asm {
			push this
			mov eax, 0x520D30
			call eax
		}
	}

	bool Board::CardPickableCob() {
		for (auto&& p : mPlantList)	if (p.type == Plant::Type::KERNEL_PULT && canPlantCob(p.col, p.row))return true;
		return false;
	}

	bool Board::CardPickableCat() {
		for (auto&& p : mPlantList)	if (p.type == Plant::Type::LILY_PAD && !GetGridPlant(p.col, p.row, PlantPriority::MAIN))return true;
		return false;
	}

	bool Board::CardPickable(Card::Type type) {
		return and (
			type != Card::Type::GATLING_PEA || 0 != GetPlantCount(Plant::Type::REPEATER),
			type != Card::Type::WINTER_MELON || 0 != GetPlantCount(Plant::Type::MELON_PULT),
			type != Card::Type::TWIN_SUNFLOWER || 0 != GetPlantCount(Plant::Type::SUNFLOWER),
			type != Card::Type::SPIKEROCK || 0 != GetPlantCount(Plant::Type::SPIKEWEED),
			type != Card::Type::COB_CANNON || CardPickableCob(),
			type != Card::Type::GOLD_MAGNET || 0 != GetPlantCount(Plant::Type::MAGNET_SHROOM),
			type != Card::Type::GLOOM_SHROOM || 0 != GetPlantCount(Plant::Type::FUME_SHROOM),
			type != Card::Type::CATTAIL || CardPickableCat()
			);
	}

	void Card::MouseDown() {
		if (mBoard->pause || mApp->gameState != GameApp::State::BATTLE || type == Type::NIL) return;
		if (mApp->isSlotMachine()) {
			if (!mBoard->mBoardText->IsBeingDisplayed()) mBoard->SetBoardText("[ADVICE_SLOT_MACHINE_PULL]", BoardText::Type::HINT_TALL_FAST, Board::AdviceType::NIL);
			mBoard->mLevelProp->SlotMachineRollCount = min(2, mBoard->mLevelProp->SlotMachineRollCount);
			return;
		}
		Type mtype = trueType();
		if (!mApp->freePlant) {
			if (!useable) {
				mApp->PlaySample(SOUND_BUZZER);
				if (mApp->isFirseTimeAdventure() && mBoard->adventureLevelRank == 1 && mBoard->AdviceShown[0]) mBoard->SetBoardText("[ADVICE_SEED_REFRESH]", BoardText::Type::TUTORIAL_LEVEL1, Board::AdviceType::SEED_REFRESH);
				return;
			}
			if (mBoard->GetCardCost(mtype) > mBoard->sunValue + mBoard->GetCollectingSunValue() && !mApp->isBelt()) {
				mApp->PlaySample(SOUND_BUZZER);
				mBoard->sunValueShineCountdown = 70;
				if (mApp->isFirseTimeAdventure() && mBoard->adventureLevelRank == 1 && mBoard->AdviceShown[0]) mBoard->SetBoardText("[ADVICE_CANT_AFFORD_PLANT]", BoardText::Type::TUTORIAL_LEVEL1, Board::AdviceType::CANT_AFFORD_PLANT);
				return;
			}
			if (!mBoard->CardPickable(mtype)) {
				mApp->PlaySample(SOUND_BUZZER);
				switch (mtype) {
				case Type::GATLING_PEA:	mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_REPEATER]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_REPEATER); break;
				case Type::WINTER_MELON: mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_MELONPULT]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_MELONPULT); break;
				case Type::TWIN_SUNFLOWER: mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_SUNFLOWER]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_SUNFLOWER); break;
				case Type::SPIKEROCK: mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_SPIKEWEED]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_SPIKEWEED); break;
				case Type::COB_CANNON: mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_KERNELPULT]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_KERNELPULT); break;
				case Type::GOLD_MAGNET: mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_MAGNETSHROOM]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_MAGNETSHROOM); break;
				case Type::GLOOM_SHROOM: mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_FUMESHROOM]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_FUMESHROOM); break;
				case Type::CATTAIL: mBoard->SetBoardText("[ADVICE_PLANT_NEEDS_LILYPAD]", BoardText::Type::HINT_LONG, Board::AdviceType::PLANT_NEEDS_LILYPAD); break;
				}
				return;
			}
		}
		mBoard->KillBoardText(Board::AdviceType::CANT_AFFORD_PLANT);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_REPEATER);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_MELONPULT);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_SUNFLOWER);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_KERNELPULT);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_SPIKEWEED);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_MAGNETSHROOM);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_FUMESHROOM);
		mBoard->KillBoardText(Board::AdviceType::PLANT_NEEDS_LILYPAD);
		if (mApp->isBejeveled()) return mBoard->mLevelProp->BejeveledUseCard(*this);
		mBoard->mMouseProp->handCardType = type;
		mBoard->mMouseProp->handImitaterType = imitaterType;
		mBoard->mMouseProp->handItemType = MouseProp::Type::SLOT_CARD;
		mBoard->mMouseProp->handPlantSlotRank = slotRank;
		mApp->PlaySample(SOUND_SEEDLIFT);
		switch (mBoard->tutorial) {
		case Board::Tutorial::LEVEL1_PICK_PEASHOOTER:mBoard->SetTutorial(Board::Tutorial::LEVEL1_PLANT_PEASHOOTER); break;
		case Board::Tutorial::LEVEL2_PICK_SUNFLOWER:mBoard->SetTutorial((mtype == Type::SUNFLOWER) ? Board::Tutorial::LEVEL2_PLANT_SUNFLOWER : Board::Tutorial::LEVEL2_REFRESH_SUNFLOWER); break;
		case Board::Tutorial::MORESUN_PICK_SUNFLOWER:mBoard->SetTutorial((mtype == Type::SUNFLOWER) ? Board::Tutorial::MORESUN_PLANT_SUNFLOWER : Board::Tutorial::MORESUN_REFRESH_SUNFLOWER); break;
		case Board::Tutorial::HAMMER_PICK_SEED:
		case Board::Tutorial::HAMMER_BEFORE_PICK_SEED:mBoard->SetTutorial(Board::Tutorial::HAMMER_COMPLETED); break;
		}
		DeActive();
	}

	void LevelProp::BejeveledUseCard(Card& card) {
		switch (card.trueType()) {
		case Card::Type::REPEATER:
		{
			bejeveledRepeater = true;
			for (auto p = mBoard->mPlantList.begin(); p != mBoard->mPlantList.end(); ++p) if (p->type == Plant::Type::PEASHOOTER)mBoard->NewPlant(p->col, p->row, Plant::Type::REPEATER), p->Kill();
			card.DeActive();
		}break;
		case Card::Type::FUME_SHROOM:
		{
			bejeveledFumeShroom = true;
			for (auto p = mBoard->mPlantList.begin(); p != mBoard->mPlantList.end(); ++p) if (p->type == Plant::Type::PUFF_SHROOM)mBoard->NewPlant(p->col, p->row, Plant::Type::FUME_SHROOM), p->Kill();
			card.DeActive();
		}break;
		case Card::Type::TALL_NUT:
		{
			bejeveledTallNut = true;
			for (auto p = mBoard->mPlantList.begin(); p != mBoard->mPlantList.end(); ++p) if (p->type == Plant::Type::WALL_NUT)mBoard->NewPlant(p->col, p->row, Plant::Type::TALL_NUT), p->Kill();
			card.DeActive();
		}break;
		case Card::Type::BEGHOULED_RESET:
		{
			if (state == State::BEGHOULED_FALLING || state == State::BEGHOULED_MOVING) return;
			BejeveledReset();
		}break;
		case Card::Type::BEGHOULED_CRATER:
		{
			if (state == State::BEGHOULED_FALLING || state == State::BEGHOULED_MOVING) return;
			if (!BejeveledHaveCrater())return;
			mBoard->KillBoardText(Board::AdviceType::BEGHOULED_USE_CRATER_1);
			mBoard->KillBoardText(Board::AdviceType::BEGHOULED_USE_CRATER_2);
			for (int i = 0; i < 9; i++) for (int j = 0; j < 5; j++) if (bejeveledCrater[i][j]) { bejeveledCrater[i][j] = false; break; }
			BejeveledUpdateCraters();
			BejeveledStartFalling(State::BEGHOULED_FALLING);
		}break;
		}
		mBoard->sunValue -= mBoard->GetCardCost(card.trueType());
	}

	bool LevelProp::BejeveledHaveCrater() {
		for (int i = 0; i < 9; i++) for (int j = 0; j < 5; j++) if (bejeveledCrater[i][j]) return true;
		return false;
	}

	void LevelProp::BejeveledUpdateCraters() {
		if (mBoard->mSlot->SlotCount != 5)return;
		Card& card = mBoard->mSlot->mCards[4];
		if (BejeveledHaveCrater()) card.useable = true;
		else card.DeActive();
	}

	void LevelProp::BejeveledCancelMatchFlashing() {
		for (auto p = mBoard->mPlantList.begin(); p != mBoard->mPlantList.end(); ++p) p->shineCountdown = min(25, p->shineCountdown);
	}

	void LevelProp::BejeveledStartFalling(State _state) {
		mainCountdown = 100;
		state = _state;
		BejeveledCancelMatchFlashing();
		mBoard->KillBoardText(Board::AdviceType::BEGHOULED_NO_MOVES);
	}

	void LevelProp::BejeveledReset() {
		mBoard->KillBoardText();
		for (auto p = mBoard->mPlantList.begin(); p != mBoard->mPlantList.end(); ++p) p->Kill();
		BejeveledStartFalling(State::BEGHOULED_FALLING);
	}

	void Board::ThrowMouse() {
		if (mMouseProp->handItemType == MouseProp::Type::ITEM_CARD) {
			Item* i = mItemList[mMouseProp->mItemID];
			if (i)i->collected = false;
		} else if (mMouseProp->handItemType == MouseProp::Type::SLOT_CARD && mMouseProp->handPlantSlotRank != -1) mSlot->mCards[mMouseProp->handPlantSlotRank].useable = true;
		CursorClear();
	}

	void Slot::Remove(int rank) {
		for (int i = rank; i < SlotCount; ++i) {
			if (mCards[i].type == Card::Type::NIL) return;
			if (i == SlotCount - 1) {
				mCards[i].type = Card::Type::NIL;
				mCards[i].conveyMoveCountdown = 0;
			} else {
				mCards[i].type = mCards[i + 1].type;
				mCards[i].conveyMoveCountdown = mCards[i + 1].conveyMoveCountdown + 51;
			}
			mCards[i].CDAcc = 0;
			mCards[i].CDTarget = 0;
			mCards[i].inCD = false;
			mCards[i].useable = true;
		}
	}

	void Card::Used() {
		if (mApp->isBelt()) return mBoard->mSlot->Remove(slotRank);
		if (mApp->isSlotMachine()) {
			CDAcc = 0;
			CDTarget = 0;
			inCD = false;
			useable = true;
			return;
		}
		if (mApp->isLS() && mBoard->mLevelProp->state != LevelProp::State::LAST_STAND_ONSLAUGHT) {
			++CDAcc;
			useable = true;
			Shine();
			return;
		}
		++CDAcc;
		inCD = true;
		CDTarget = BasicProp(trueType()).CD;
	}

	void LevelProp::IZUseCard(int col, int row) {
		if (col == -1 || row == -1) {
			mBoard->ThrowMouse();
			mApp->NewSample(Sample::Type::DROP);
			return;
		}
		CardReject cardReject = GetCardReject(col, row, mBoard->mMouseProp->trueCardType());
		if (cardReject == CardReject::NIL) {
			if (!mApp->freePlant) {
				int currentPlantCost = mBoard->GetCardCost(mBoard->mMouseProp->trueCardType());
				if (currentPlantCost > mBoard->sunValue + mBoard->GetCollectingSunValue()) {
					mApp->PlaySample(SOUND_BUZZER);
					mBoard->sunValueShineCountdown = 70;
					return;
				}
				mBoard->sunValue -= currentPlantCost;
			}
			mBoard->KillBoardText(Board::AdviceType::I_ZOMBIE_LEFT_OF_LINE);
			mBoard->KillBoardText(Board::AdviceType::I_ZOMBIE_NOT_PASSED_LINE);
			NewZombie(col, row, BasicProp(mBoard->mMouseProp->trueCardType()).zombieType);
			if (mBoard->mMouseProp->handPlantSlotRank != -1) mBoard->mSlot->mCards[mBoard->mMouseProp->handPlantSlotRank].Used();
			mApp->NewSample(Sample::Type::PLANT_INIT);
			return mBoard->CursorClear();
		}
		mBoard->KillBoardText();
		if (mBoard->mMouseProp->trueCardType() == Card::Type::ZOMBIE_BUNGEE) mBoard->SetBoardText(u8"[ADVICE_I_ZOMBIE_LEFT_OF_LINE]", BoardText::Type::HINT_LONG, Board::AdviceType::I_ZOMBIE_LEFT_OF_LINE);
		else mBoard->SetBoardText(u8"[ADVICE_I_ZOMBIE_NOT_PASSED_LINE]", BoardText::Type::HINT_LONG, Board::AdviceType::I_ZOMBIE_NOT_PASSED_LINE);
	}

	void LevelProp::NewZombie(int col, int row, Zombie::Type _type) {
		Zombie* p = mBoard->NewZombie(row, _type, 0);
		if (_type == Zombie::Type::BUNGEE_ZOMBIE) {
			p->bungeeCol = col;
			p->row = row;
			p->layer = 303004 + 10000 * row;
			p->x = (float)mBoard->GetX(col, row);
			p->y = p->GetYBase();
			return;
		}
		p->x = (float)mBoard->GetX(col, row) - 30.0f;
		p->ResetSpeed();
		p->AnimInitSpeed();
	}

	void Board::UsePlant(int x, int y, int theClickCount) {
		Card::Type type = mMouseProp->trueCardType();
		Plant::Type ptype = BasicProp(type).plantType;
		if (theClickCount < 0) {
			ThrowMouse();
			mApp->NewSample(Sample::Type::DROP);
			return;
		}
		int col = GetCol(type, x, y);
		int row = GetRow(type, x, y);
		if (mApp->isIZ()) {
			mLevelProp->IZUseCard(col, row);
			return;
		}
		if (col < 0 || col >= 8 || row < 0 || row >= 5) {
			ThrowMouse();
			mApp->NewSample(Sample::Type::DROP);
			return;
		}
		CardReject cardReject = GetCardReject(col, row, type);
		switch (cardReject) {
		case CardReject::ONLY_ON_GRAVES:
			this->SetBoardText("[ADVICE_GRAVEBUSTERS_ON_GRAVES]", BoardText::Type::HINT_FAST, AdviceType::PLANT_GRAVEBUSTERS_ON_GRAVES);
			break;
		case CardReject::ONLY_IN_POOL:
			switch (type) {
			case Card::Type::LILY_PAD:SetBoardText("[ADVICE_LILYPAD_ON_WATER]", BoardText::Type::HINT_FAST, AdviceType::PLANT_LILYPAD_ON_WATER); break;
			case Card::Type::TANGLE_KELP:SetBoardText("[ADVICE_TANGLEKELP_ON_WATER]", BoardText::Type::HINT_FAST, AdviceType::PLANT_TANGLEKELP_ON_WATER); break;
			case Card::Type::SEA_SHROOM:SetBoardText("[ADVICE_SEASHROOM_ON_WATER]", BoardText::Type::HINT_FAST, AdviceType::PLANT_SEASHROOM_ON_WATER); break;
			}
			break;
		case CardReject::ONLY_ON_GROUND:
			SetBoardText("[ADVICE_POTATO_MINE_ON_LILY]", BoardText::Type::HINT_FAST, AdviceType::PLANT_POTATO_MINE_ON_LILY);
			break;
		case CardReject::NOT_PASSED_LINE:
			SetBoardText("[ADVICE_NOT_PASSED_LINE]", BoardText::Type::HINT_FAST, AdviceType::PLANT_NOT_PASSED_LINE);
			break;
		case CardReject::NEEDS_UPGRADE:
			switch (type) {
			case Card::Type::GATLING_PEA:SetBoardText("[ADVICE_ONLY_ON_REPEATERS]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_REPEATERS); break;
			case Card::Type::WINTER_MELON:SetBoardText("[ADVICE_ONLY_ON_MELONPULT]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_MELONPULT); break;
			case Card::Type::TWIN_SUNFLOWER:SetBoardText("[ADVICE_ONLY_ON_SUNFLOWER]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_SUNFLOWER); break;
			case Card::Type::SPIKEROCK:SetBoardText("[ADVICE_ONLY_ON_SPIKEWEED]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_SPIKEWEED); break;
			case Card::Type::COB_CANNON:SetBoardText("[ADVICE_ONLY_ON_KERNELPULT]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_KERNELPULT); break;
			case Card::Type::GOLD_MAGNET:SetBoardText("[ADVICE_ONLY_ON_MAGNETSHROOM]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_MAGNETSHROOM); break;
			case Card::Type::GLOOM_SHROOM:SetBoardText("[ADVICE_ONLY_ON_FUMESHROOM]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_FUMESHROOM); break;
			case Card::Type::CATTAIL:SetBoardText("[ADVICE_ONLY_ON_LILYPAD]", BoardText::Type::HINT_FAST, AdviceType::PLANT_ONLY_ON_LILYPAD); break;
			}
			break;
		case CardReject::NOT_ON_ART:
			SetBoardText("[ADVICE_WRONG_ART_TYPE]", BoardText::Type::HINT_FAST, AdviceType::PLANT_WRONG_ART_TYPE);
			break;
		case CardReject::NEEDS_POT:
			if (mApp->isFirseTimeAdventure() && adventureLevelRank == 41) SetBoardText("[ADVICE_PLANT_NEED_POT1]", BoardText::Type::HINT_FAST, AdviceType::PLANT_NEED_POT);
			else SetBoardText("[ADVICE_PLANT_NEED_POT2]", BoardText::Type::HINT_FAST, AdviceType::PLANT_NEED_POT);
			break;
		case CardReject::NOT_ON_GRAVE:
			this->SetBoardText("[ADVICE_PLANT_NOT_ON_GRAVE]", BoardText::Type::HINT_FAST, AdviceType::PLANT_NOT_ON_GRAVE);
		case CardReject::NOT_ON_CRATER:
			if (gridType[col][row] == GridType::POOL) SetBoardText("[ADVICE_CANT_PLANT_THERE]", BoardText::Type::HINT_FAST, AdviceType::CANT_PLANT_THERE);
			else SetBoardText("[ADVICE_PLANT_NOT_ON_CRATER]", BoardText::Type::HINT_FAST, AdviceType::PLANT_NOT_ON_CRATER);
			break;
		case CardReject::NOT_ON_WATER:
			if (mApp->isGarden() && mApp->mGardenProp->type == GardenProp::YardType::AQUARIUM) SetBoardText("[ZEN_ONLY_AQUATIC_PLANTS]", BoardText::Type::HINT_TALL_FAST, AdviceType::NIL);
			else if (type == Card::Type::POTATO_MINE) SetBoardText("[ADVICE_CANT_PLANT_THERE]", BoardText::Type::HINT_FAST, AdviceType::CANT_PLANT_THERE);
			else SetBoardText("[ADVICE_PLANT_NOT_ON_WATER]", BoardText::Type::HINT_FAST, AdviceType::PLANT_NOT_ON_WATER);
			break;
		case CardReject::NEEDS_GROUND:
			this->SetBoardText("[ADVICE_PLANTING_NEEDS_GROUND]", BoardText::Type::HINT_FAST, AdviceType::NEEDS_GROUND);
			break;
		case CardReject::NEEDS_SLEEPING:
			this->SetBoardText("[ADVICE_PLANTING_NEED_SLEEPING]", BoardText::Type::HINT_FAST, AdviceType::NEED_SLEEPING);
			break;
		}
		if (cardReject != CardReject::NIL) {
			if (mMouseProp->handItemType == MouseProp::Type::GLOVE_PLANT || mApp->isHammer()) {
				ThrowMouse();
				mApp->NewSample(Sample::Type::DROP);
			}
			return;
		}
		KillBoardText(AdviceType::NEED_SLEEPING);
		KillBoardText(AdviceType::CANT_PLANT_THERE);
		KillBoardText(AdviceType::NEEDS_GROUND);
		KillBoardText(AdviceType::PLANT_NOT_ON_WATER);
		KillBoardText(AdviceType::PLANT_NOT_ON_CRATER);
		KillBoardText(AdviceType::PLANT_NOT_ON_GRAVE);
		KillBoardText(AdviceType::PLANT_NEED_POT);
		KillBoardText(AdviceType::PLANT_WRONG_ART_TYPE);
		KillBoardText(AdviceType::PLANT_ONLY_ON_LILYPAD);
		KillBoardText(AdviceType::PLANT_ONLY_ON_MAGNETSHROOM);
		KillBoardText(AdviceType::PLANT_ONLY_ON_FUMESHROOM);
		KillBoardText(AdviceType::PLANT_ONLY_ON_KERNELPULT);
		KillBoardText(AdviceType::PLANT_ONLY_ON_SUNFLOWER);
		KillBoardText(AdviceType::PLANT_ONLY_ON_SPIKEWEED);
		KillBoardText(AdviceType::PLANT_ONLY_ON_MELONPULT);
		KillBoardText(AdviceType::PLANT_ONLY_ON_REPEATERS);
		KillBoardText(AdviceType::PLANT_NOT_PASSED_LINE);
		KillBoardText(AdviceType::PLANT_GRAVEBUSTERS_ON_GRAVES);
		KillBoardText(AdviceType::PLANT_LILYPAD_ON_WATER);
		KillBoardText(AdviceType::PLANT_TANGLEKELP_ON_WATER);
		KillBoardText(AdviceType::PLANT_SEASHROOM_ON_WATER);
		KillBoardText(AdviceType::PLANT_POTATO_MINE_ON_LILY);
		KillBoardText(AdviceType::SURVIVE_FLAGS);
		if (!mApp->freePlant && mMouseProp->handItemType == MouseProp::Type::SLOT_CARD && !mApp->isBelt()) {
			int currentPlantCost = GetCardCost(mMouseProp->trueCardType());
			if (currentPlantCost > sunValue + GetCollectingSunValue()) {
				mApp->PlaySample(SOUND_BUZZER);
				sunValueShineCountdown = 70;
				return;
			}
			sunValue -= currentPlantCost;
		}
		auto list = GetGridPlantList(col, row);
		bool awake = false;
		int mWakeUpCounter = 0;
		if (list.mMain && BasicProp(type).upgradeBase == list.mMain->type) {
			if (type == Card::Type::GLOOM_SHROOM) {
				if (!list.mMain->slept) awake = true;
				else mWakeUpCounter = list.mMain->wakeupCountdown;
			}
			list.mMain->Kill();
		}
		switch (type) {
		case Card::Type::WALL_NUT:
		case Card::Type::TALL_NUT:
			if (list.mMain && list.mMain->type == ptype)list.mMain->Kill();
			break;
		case Card::Type::PUMPKIN:
			if (list.mMiddle && list.mMiddle->type == Plant::Type::PUMPKIN)list.mMiddle->Kill();
			break;
		case Card::Type::COB_CANNON:
		{
			Plant* frontKern = GetGridPlant(col + 1, row, Plant::Type::KERNEL_PULT);
			if (frontKern)frontKern->Kill();
		}
		break;
		case Card::Type::CATTAIL:
			if (list.mBottom && list.mBottom->type == Plant::Type::LILY_PAD)list.mBottom->Kill();
			if (list.mMain && list.mMain->type == Plant::Type::LILY_PAD)list.mMain->Kill();
			break;
		}
		switch (mMouseProp->handItemType) {
		case MouseProp::Type::GLOVE_PLANT:
		{
			Plant* p = mPlantList[mMouseProp->mPlantID];
			if (p)mApp->mGardenProp->MovePlant(p, col, row);
		}
		break;
		case MouseProp::Type::CART_PLANT:
			mApp->mGardenProp->PutCartPlantint(x, y);
			break;
		case MouseProp::Type::ITEM_CARD:
		{
			NewPlant(col, row, ptype);
			Item* i = mItemList[mMouseProp->mItemID];
			if (i)i->Kill();
			mMouseProp->mItemID = 0;
		}
		break;
		case MouseProp::Type::SLOT_CARD:
		{
			Plant* p = NewPlant(col, row, ptype);
			if (awake) p->SetSleep(false);
			p->wakeupCountdown = mWakeUpCounter;
			if (mMouseProp->handPlantSlotRank != -1)mSlot->mCards[mMouseProp->handPlantSlotRank].Used();
		}
		break;
		}
		if (mApp->isColumn()) for (int trow = 0; trow < 6; ++trow) if (trow != row && GetCardReject(col, trow, type) == CardReject::NIL) {
			if (type == Card::Type::WALL_NUT || type == Card::Type::TALL_NUT) {
				Plant* p = GetGridPlant(col, trow, PlantPriority::MAIN);
				if (p && p->type == ptype) p->Kill();
			} else if (type == Card::Type::PUMPKIN) {
				Plant* p = GetGridPlant(col, trow, PlantPriority::MIDDLE);
				if (p && p->type == Plant::Type::PUMPKIN) p->Kill();
			}
			NewPlant(col, trow, ptype);
		}
		int sfCount = GetPlantCount(Plant::Type::SUNFLOWER);
		switch (tutorial) {
		case Tutorial::LEVEL1_PLANT_PEASHOOTER:
			SetTutorial((mPlantList.mSize >= 2) ? Tutorial::LEVEL1_COMPLETED : Tutorial::LEVEL1_REFRESH_PEASHOOTER);
			break;
		case Tutorial::LEVEL2_PLANT_SUNFLOWER:
			if (type == Card::Type::SUNFLOWER && sfCount == 2) SetBoardText("[ADVICE_MORE_SUNFLOWERS]", BoardText::Type::TUTORIAL_LEVEL2, AdviceType::NIL);
			if (sfCount >= 3) {
				SetTutorial(Tutorial::LEVEL2_COMPLETED);
			} else if (!mSlot->mCards[1].canPick()) {
				SetTutorial(Tutorial::LEVEL2_REFRESH_SUNFLOWER);
			} else {
				SetTutorial(Tutorial::LEVEL2_PICK_SUNFLOWER);
			}
			break;
		case Tutorial::MORESUN_PLANT_SUNFLOWER:
			if (sfCount >= 3) {
				SetTutorial(Tutorial::MORESUN_COMPLETED);
				SetBoardText("[ADVICE_PLANT_SUNFLOWER5]", BoardText::Type::TUTORIAL_LATER, AdviceType::PLANT_SUNFLOWER5);
				tutorialCountdown = -1;
			} else if (!mSlot->mCards[1].canPick()) {
				SetTutorial(Tutorial::MORESUN_REFRESH_SUNFLOWER);
			} else {
				SetTutorial(Tutorial::MORESUN_PICK_SUNFLOWER);
			}
			break;
		}
		if (mApp->isBowling()) mApp->PlaySample(SOUND_BOWLING);
		CursorClear();
	}

	void GardenProp::MovePlant(Plant* p, int col, int row) {
		__asm {
			push row
			push col
			push p
			push this
			mov eax, 0x51F700
			call eax
		}
	}

	void GardenProp::PutCartPlantint(int col, int row) {
		__asm {
			push row
			push col
			push this
			mov eax, 0x5210F0
			call eax
		}
	}


	void Board::UseTool(int x, int y, int theClickCount, MouseProp::Type tool) {
		__asm {
			push ebx
			push tool
			push theClickCount
			mov ecx, y
			mov edx, x
			mov eax, this
			mov ebx, 0x411060ul
			call ebx
			pop ebx
		}

	}

	void Item::PlayCollectedSample() {
		switch (type) {
		case Type::CARD:return mApp->PlaySample(SOUND_SEEDLIFT);
		case Type::SILVER_COIN:
		case Type::GOLD_COIN:return mApp->NewSample(Sample::Type::ITEM_COIN_COLLECT);
		case Type::DIAMOND:return mApp->PlaySample(SOUND_DIAMOND);
		case Type::SUN:
		case Type::SUN_SMALL:
		case Type::SUN_LARGE:return mApp->NewSample(Sample::Type::ITEM_SUN_COLLECT);
		case Type::PRESENT_PLANT:
		case Type::PRESENT_PLANT_AWARD:
		case Type::CHOCOLATE:
		case Type::CHOCOLATE_AWARD:
		case Type::PRESENT_MINIGAME:
		case Type::PRESENT_PUZZLE:
		case Type::PRESENT_SURVIVAL:return mApp->NewSample(Sample::Type::ITEM_PRESENT_COLLECT);
		}
	}

	void Item::MouseDown() {
		if (!mBoard || mBoard->pause || mApp->gameState != GameApp::State::BATTLE || vanished || collected)return;
		PlayCollectedSample();
		Collected();
		if (mApp->isFirseTimeAdventure() && mBoard->adventureLevelRank == 1) mBoard->SetBoardText("[ADVICE_CLICKED_ON_SUN]", BoardText::Type::TUTORIAL_LEVEL1_STAY, Board::AdviceType::CLICKED_ON_SUN);
	}

	void Board::CursorInit() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x40E520ul
			call eax
			pop edi
		}
	}

	void Board::CursorClear() {
		__asm {
			push edi
			mov edi, this
			mov eax, 0x412330ul
			call eax
			pop edi
		}
	}

	void Board::CannonShoot(int x, int y, int theClickCount) {
		if (theClickCount < 0 || y < 80 || (paoSafeCountdown > 0 && (Point<int>(x, y) - paoSafePoint).Distance() < 50) || mMouseProp->handItemType == MouseProp::Type::DUPLICATOR_PLANT)return CursorClear();
		Plant* plant = mPlantList[mMouseProp->mPlantID];
		if (plant) plant->CanonShoot(x, y);
		return CursorClear();
	}

	void SceneProp::MouseDown() {
		__asm {
			push this
			mov eax, 0x43CE00ul
			call eax
		}

	}

	bool LevelProp::MouseDown(int x, int y, int theClickCount, MouseResult mouseResult) {
		MouseResult* p = &mouseResult;
		__asm {
			push theClickCount
			push y
			push x
			push this
			mov eax, p
			mov ecx, 0x421F10ul
			call ecx
		}
	}

	MouseResult Card::GetMouseResult(int x, int y) {
		if (type == Type::NIL || slotMachineCountdown > 0 || !mRect.Contains(x, y))return MouseResult();
		return MouseResult(this);
	}

	MouseResult Slot::GetMouseResult(int x, int y) {
		MouseResult ans;
		if (x - mX > mW - 5) return ans;
		for (int i = 0; i < SlotCount; ++i) if (ans = mCards[i].GetMouseResult(x, y))return ans;
		return ans;
	}

	bool GardenProp::isSnainBoosting() {
		return timeGetTime() - mApp->mUserData->snailAteChocolateTime < 3600;
	}

	Building* GardenProp::GetSnail() {
		for (auto&& p : mBoard->mBuildingList)if (p.type == Building::Type::SNAIL)return &p;
		return nullptr;
	}

	MouseResult Item::GetMouseResult(int x, int y) {
		if (vanished || collected || (type == Type::CARD && mBoard && mBoard->mMouseProp->handItemType != MouseProp::Type::NIL && mApp->isHammer()))return MouseResult();
		int ydiff = inrange(type, Type::PRESENT_PLANT, Type::PRESENT_PLANT_AWARD, Type::PRESENT_MINIGAME, Type::PRESENT_PUZZLE, Type::PRESENT_SURVIVAL) ? 20 : 0;
		int extent = 0;
		int yextent = 0;
		if (mApp->isHammer()) {
			yextent = 30;
			extent = 15;
		}
		if (this->isMoney() || type == Type::SUN) {
			extent = 15;
		}
		if (Rect((int)this->x - extent, (int)this->y - ydiff - extent, mW + 2 * extent, mH + 2 * extent + yextent).Contains(x, y))return MouseResult(this);
		return MouseResult();
	}

	MouseResult LevelProp::GetWTMouseResult(int x, int y) {
		int tree = mApp->mUserData->levelRecord[mApp->levelRank];
		bool in = false;
		if (tree >= 7) {
			if (tree >= 12) in = Rect(280, 155, 225, 295).Contains(x, y);
			else in = Rect(290, 215, 205, 235).Contains(x, y);
		} else {
			if (tree >= 2) in = Rect(290, 255, 205, 195).Contains(x, y);
			else  in = Rect(310, 275, 185, 175).Contains(x, y);
		}
		return in ? MouseResult(MouseResult::Type::WISDOMTREE) : MouseResult();
	}

	bool Board::ToolExist(MouseResult::Type tool) {
		if (mApp->level == GameApp::Level::Type::WISDOM_TREE)return tool == MouseResult::Type::TREE_FOOD || tool == MouseResult::Type::NEXT_GARDEN;
		if (mApp->level != GameApp::Level::Type::GARDEN)return false;
		switch (tool) {
		case Pvz::MouseResult::Type::POT:return true;
		case Pvz::MouseResult::Type::FERTILIZER:return mApp->mUserData->shopItemBought[(int)Shop::ItemType::FERTILIZER];
		case Pvz::MouseResult::Type::INSECTICIDE:return mApp->mUserData->shopItemBought[(int)Shop::ItemType::INSECTICIDE];
		case Pvz::MouseResult::Type::PHONOGRAPH:return mApp->mUserData->shopItemBought[(int)Shop::ItemType::PHONOGRAPH];
		case Pvz::MouseResult::Type::CHOCOLATE:return mApp->mUserData->shopItemBought[(int)Shop::ItemType::CHOCOLATE];
		case Pvz::MouseResult::Type::GLOVE:return mApp->mUserData->shopItemBought[(int)Shop::ItemType::GLOVE];
		case Pvz::MouseResult::Type::SELL:return mApp->isFinishedAdventure();
		case Pvz::MouseResult::Type::CART:return mApp->mUserData->shopItemBought[(int)Shop::ItemType::CART];
		case Pvz::MouseResult::Type::NEXT_GARDEN:return mApp->mUserData->shopItemBought[(int)Shop::ItemType::MUSHROOMGARDEN] || mApp->mUserData->shopItemBought[(int)Shop::ItemType::AQUARIUM] || mApp->mUserData->shopItemBought[(int)Shop::ItemType::WT];
		default:return false;
		}
	}

	GardenPlant::Need GardenPlant::getNeed() {
		if (state != State::SPROUT && inrange(type,
			Plant::Type::PUFF_SHROOM,
			Plant::Type::SEA_SHROOM,
			Plant::Type::SUN_SHROOM,
			Plant::Type::FUME_SHROOM,
			Plant::Type::HYPNO_SHROOM,
			Plant::Type::DOOM_SHROOM,
			Plant::Type::ICE_SHROOM,
			Plant::Type::MAGNET_SHROOM,
			Plant::Type::SCAREDY_SHROOM,
			Plant::Type::GLOOM_SHROOM
		) && gardenYard != GardenProp::YardType::MUSHROOM) return Need::NIL;
		if (gardenYard == GardenProp::YardType::CART) return Need::NIL;
		DWORD time = timeGetTime();
		if (time - lastFertilizedTime < 3600 || time - lastShinedTime < 86400)return Need::NIL;
		if (BasicProp(type).inWater && state != GardenPlant::State::SPROUT) {
			if (state != GardenPlant::State::FULL) return gGameApp->mGardenProp->type == GardenProp::YardType::AQUARIUM ? Need::FERTILIZER : Need::NIL;
			return time - lastWateredTime > 3600 ? need : Need::NIL;
		} else {
			if (time - lastWateredTime < 16) return Need::NIL;
			if (mTimesFed < mFeedingsPerGrow) return Need::WATER;
			if (state != GardenPlant::State::FULL) return Need::FERTILIZER;
			if (time - lastWateredTime < 3600) return Need::NIL;
			if (need != Need::NIL) return need;
			return Need::WATER;
		}
	}

	bool GardenProp::canWater(Plant* p) {
		if (p->gardenRank == -1)return false;
		return mApp->mUserData->mGardenPlant[p->gardenRank].getNeed() == GardenPlant::Need::WATER;
	}

	bool GardenProp::canChocolate(Plant* p) {
		if (p->gardenRank == -1)return false;
		GardenPlant& pg = mApp->mUserData->mGardenPlant[p->gardenRank];
		DWORD time = timeGetTime();
		return time - pg.lastShinedTime < 86500 && time - pg.lastChocolatedTime>1800;
	}

	MouseResult Board::GetMouseResultSpecialPlant(int x, int y) {
		for (auto&& p : mPlantList) {
			if (p.type == Plant::Type::PUMPKIN) {
				int num = GetGridPlant(p.col, p.row, PlantPriority::MAIN) ? 25 : 0;
				int num2 = (Point<int>(x, y) - Point<int>(p.mX + 40, p.mY + 40)).Distance();
				if (num2 >= num && num2 <= 50 && y > p.mY + 25)return MouseResult(&p);
			}
			if (p.type == Plant::Type::COFFEE_BEAN) {
				if ((Point<int>(x, y) - Point<int>(p.mX + 40, p.mY + 40)).Distance() < 15)return MouseResult(&p);
			}
		}
		return MouseResult();
	}

	MouseResult Board::GetMouseResultPlant(int x, int y) {
		if (mMouseProp->handItemType == MouseProp::Type::AIM || mMouseProp->handItemType == MouseProp::Type::HAMMER)return MouseResult();
		MouseResult ans;
		if (ans = GetMouseResultSpecialPlant(x, y))return ans;
		int col = GetCol(x, y);
		int row = GetRow(x, y);
		Plant* p;
		if (mApp->isGarden()) {
			p = GetGridPlant(col, row, PlantPriority::TOOL);
			if (mMouseProp->handItemType == MouseProp::Type::POT && !(p && mApp->mGardenProp->canWater(p))) {
				Plant* p2 = GetGridPlant(GetCol(x - 30, y - 20), GetRow(x - 30, y - 20), PlantPriority::TOOL);
				if (p2 && mApp->mGardenProp->canWater(p2))p = p2;
			}
		} else {
			p = GetGridPlant(col, row, PlantPriority::DIG);
			if (p && (p->type == Plant::Type::LILY_PAD || p->type == Plant::Type::FLOWER_POT) && GetGridPlant(col, row, PlantPriority::MIDDLE)) p = nullptr;
		}
		if (!p || (mMouseProp->handItemType == MouseProp::Type::CHOCOLATE && mApp->mGardenProp->canChocolate(p)))return MouseResult();
		return MouseResult(p);
	}

	Rect Board::GetToolRect(MouseResult::Type tool) {
		Rect ans = GetShovelRect();
		if (tool == MouseResult::Type::NEXT_GARDEN) {
			ans.mX = 564;
			return ans;
		}
		if (!mApp->isGarden()) {
			if (tool == MouseResult::Type::TREE_FOOD)ans.mX = 30;
			return ans;
		}
		ans.mX = 30;
		for (int i = 6; i <= 15; ++i) if ((MouseResult::Type)i != MouseResult::Type::TREE_FOOD && !ToolExist((MouseResult::Type)i)) ans.mX = 0;
		for (int i = 6; i < (int)tool; ++i)	if (ToolExist((MouseResult::Type)i)) ans.mX += 70;
		return ans;
	}

	Rect Slot::GetPullRect() {
		return Rect(mX + 473, mY, 55, 80);
	}

	MouseResult Board::GetMouseResult(int x, int y) {
		MouseResult ans;
		if (exitLevelCountdown >= 0) return ans;
		if (mApp->isVB() && mApp->DaveState != GameApp::DaveState::NIL) return ans;
		if (btnMenu->isMouseOver() && !mouseDisabled) return MouseResult(MouseResult::Type::MENU_BUTTON);
		if (btnStartLS && btnStartLS->isMouseOver() && !mouseDisabled) return MouseResult(MouseResult::Type::STORE_BUTTON);
		if ((ans = mSlot->GetMouseResult(x, y)) && inrange(mMouseProp->handItemType, MouseProp::Type::NIL, MouseProp::Type::AIM, MouseProp::Type::HAMMER))return ans;
		if (showShovel && GetShovelRect().Contains(x, y) && !mouseDisabled)return MouseResult(MouseResult::Type::SHOVEL);
		if (mMouseProp->handItemType == MouseProp::Type::NIL || mMouseProp->handItemType == MouseProp::Type::HAMMER) {
			for (auto&& p : mItemList) if (ans = p.GetMouseResult(x, y))return ans;
		}
		Building* snail = nullptr;
		if (mApp->isGarden() && (snail = mApp->mGardenProp->GetSnail()) && Rect((int)snail->x - 6, (int)snail->y - 10, 84, 90).Contains(x, y) && ((mMouseProp->handItemType == MouseProp::Type::CHOCOLATE && mApp->mGardenProp->isSnainBoosting()) || (mMouseProp->handItemType == MouseProp::Type::NIL && snail->state == Building::State::SNAIL_SLEEPING)))return MouseResult(MouseResult::Type::SNAIL, snail);
		if (mApp->level == GameApp::Level::Type::WISDOM_TREE && mMouseProp->handItemType == MouseProp::Type::TREE_FERTILIZE && (ans = mLevelProp->GetWTMouseResult(x, y)))return ans;
		if (mApp->isGardenTree() && !mouseDisabled) for (int i = 6; i < 16; ++i) if (ToolExist((MouseResult::Type)i) && GetToolRect((MouseResult::Type)i).Contains(x, y))return MouseResult((MouseResult::Type)i);
		if (ans = GetMouseResultPlant(x, y))return ans;
		if (mApp->isVB() && mMouseProp->handItemType == MouseProp::Type::NIL && mLevelProp->state != LevelProp::State::SCARY_POTTER_MALLETING && mApp->gameState == GameApp::State::BATTLE && !mApp->GetDialog(Dialog::Type::GAME_OVER) && !mApp->GetDialog(Dialog::Type::CONTINUE)) {
			Building* vase = GetGridBuilding(GetCol(x, y), GetRow(x, y), Building::Type::VASE);
			if (vase)return MouseResult(MouseResult::Type::VASE, vase);
		}
		if (mApp->isSlotMachine() && mMouseProp->handItemType != MouseProp::Type::SHOVEL && mSlot->GetPullRect().Contains(x, y) && mLevelProp->state == LevelProp::State::NIL && !isLevelEnding())return MouseResult(MouseResult::Type::SLOTMACHINE);
		return MouseResult();
	}

	void SceneProp::LoseClick() {
		if (sceneTime > LostTimeEnd || mApp->debugMode)mApp->EndLevel();
	}

	void GameApp::EndLevel() {
		KillBoard();
		if (isAdventure())NewGame();
	}

	void Board::PreKill() {
		__asm {
			push esi
			mov esi, this
			mov eax, 0x408A70ul
			call eax
			pop esi
		}
	}

	void GameApp::KillBoard() {
		if (mSelectCardWnd) {
			mWidgetManager->RemoveWidget(mSelectCardWnd);
			SafeDeleteWidget(mSelectCardWnd);
			mSelectCardWnd = nullptr;
		}
		if (mBoard) {
			mBoard->PreKill();
			mWidgetManager->RemoveWidget(mBoard);
			SafeDeleteWidget(mBoard);
			mBoard = nullptr;
		}
	}

	void GameApp::NewGame() {
		__asm {
			mov eax, this
			mov ecx, 0x44F890ul
			call ecx
		}
	}

	void SelectCardWnd::QuitLawnView() {
		if (state == State::LAWNVIEW && viewlawnTime > 100 && viewlawnTime < 251)viewlawnTime = 251;
	}

	bool __thiscall GameApp::v_Process(bool allowSleep) {
		if (mLoadingFailed)Shutdown();
		bool isVSynched = (!mPlayingDemoBuffer) && (mVSyncUpdates) && (!mLastDrawWasEmpty) && (!mVSyncBroken) && ((!mIsPhysWindowed) || (mIsPhysWindowed && mWaitForVSync && !mSoftVSyncWait));
		double aFrameFTime;
		double anUpdatesPerUpdateF;
		if (mVSyncUpdates) {
			aFrameFTime = (1000.0f / mSyncRefreshRate) / mUpdateMultiplier;
			anUpdatesPerUpdateF = 1000.0f / (mFrameTime * mSyncRefreshRate);
		} else {
			aFrameFTime = mFrameTime / mUpdateMultiplier;
			anUpdatesPerUpdateF = 1;
		}
		if (mPlayingDemoBuffer) {
			if (mUpdateCount < mFastForwardToUpdateNum || mFastForwardToMarker) {
				if (!mDemoMute && !mFastForwardStep) {
					mDemoMute = true;
					Mute(true);
				}
				gTick = (DWORD)GetTickCount64();
				while (mUpdateCount < mFastForwardToUpdateNum || mFastForwardToMarker) {
					ClearUpdateBacklog();
					int aLastUpdateCount = mUpdateCount;
					bool hadRealUpdate = DoUpdateFrames();
					if (hadRealUpdate) {
						mPendingUpdatesAcc += anUpdatesPerUpdateF;
						mPendingUpdatesAcc -= 1;
						ProcessSafeDeleteList();
						while (mPendingUpdatesAcc >= 1) {
							ProcessDemo();
							bool hasRealUpdate = DoUpdateFrames();
							if (!hasRealUpdate)break;
							ProcessSafeDeleteList();
							mPendingUpdatesAcc -= 1;
						}
						DoUpdateFramesF((float)anUpdatesPerUpdateF);
						ProcessSafeDeleteList();
					}
					if (aLastUpdateCount == mUpdateCount)return true;
					DWORD aNewTick = (DWORD)GetTickCount64();
					if (aNewTick - gTick >= 1000 || mFastForwardStep) {
						mFastForwardStep = false;
						gTick = (DWORD)GetTickCount64();
						DrawDirtyStuff();
						return true;
					}
				}
			}
			if (mDemoMute) {
				mDemoMute = false;
				mSoundManager->StopAllSounds();
				Unmute(true);
			}
		}
		if ((!mPaused) && (mUpdateMultiplier > 0)) {
			ulong aStartTime = ::timeGetTime();
			ulong aCurTime = aStartTime;
			int aCumSleepTime = 0;
			if (!isVSynched)UpdateFTimeAcc();
			bool didUpdate = false;
			if (mUpdateAppState == UPDATESTATE_PROCESS_1) {
				if ((++mNonDrawCount < (int)(10 * mUpdateMultiplier)) || (!mLoaded)) {
					bool doUpdate = false;
					if (isVSynched)doUpdate = (!mHasPendingDraw) || (mUpdateFTimeAcc >= (int)(aFrameFTime * 3 / 4));
					else if (mUpdateFTimeAcc >= aFrameFTime)doUpdate = true;
					if (doUpdate) {
						if ((!mPlayingDemoBuffer) && (mUpdateMultiplier == 1)) {
							mVSyncBrokenTestUpdates++;
							if (mVSyncBrokenTestUpdates >= (DWORD)((1000 + mFrameTime - 1) / mFrameTime)) {
								if (aStartTime - mVSyncBrokenTestStartTick <= 800) {
									mVSyncBrokenCount++;
									if (mVSyncBrokenCount >= 3)mVSyncBroken = true;
								} else mVSyncBrokenCount = 0;
								mVSyncBrokenTestStartTick = aStartTime;
								mVSyncBrokenTestUpdates = 0;
							}
						}
						bool hadRealUpdate = DoUpdateFrames();
						if (hadRealUpdate)mUpdateAppState = UPDATESTATE_PROCESS_2;
						mHasPendingDraw = true;
						didUpdate = true;
					}
				}
			} else if (mUpdateAppState == UPDATESTATE_PROCESS_2) {
				mUpdateAppState = UPDATESTATE_PROCESS_DONE;
				mPendingUpdatesAcc += anUpdatesPerUpdateF;
				mPendingUpdatesAcc -= 1;
				ProcessSafeDeleteList();
				while (mPendingUpdatesAcc >= 1) {
					ProcessDemo();
					++mNonDrawCount;
					bool hasRealUpdate = DoUpdateFrames();
					if (!hasRealUpdate)break;
					ProcessSafeDeleteList();
					mPendingUpdatesAcc -= 1;
				}
				DoUpdateFramesF((float)anUpdatesPerUpdateF);
				ProcessSafeDeleteList();
				if (isVSynched)mUpdateFTimeAcc = max(mUpdateFTimeAcc - aFrameFTime - 1 / 5, 0);
				else mUpdateFTimeAcc -= aFrameFTime;
				if (mRelaxUpdateBacklogCount > 0)mUpdateFTimeAcc = 0;
				didUpdate = true;
			}
			if (!didUpdate) {
				mUpdateAppState = UPDATESTATE_PROCESS_DONE;
				mNonDrawCount = 0;
				if (mHasPendingDraw)DrawDirtyStuff();
				else {
					int aTimeToNextFrame = (int)(aFrameFTime - mUpdateFTimeAcc);
					if (aTimeToNextFrame > 0) {
						if (!allowSleep)return false;
						++mSleepCount;
						::Sleep(aTimeToNextFrame);
						aCumSleepTime += aTimeToNextFrame;
					}
				}
			}
			if (mYieldMainThread) {
				ULONG anEndTime = ::timeGetTime();
				int anElapsedTime = (anEndTime - aStartTime) - aCumSleepTime;
				int aLoadingYieldSleepTime = min(250, (anElapsedTime * 2) - aCumSleepTime);
				if (aLoadingYieldSleepTime >= 0) {
					if (!allowSleep)return false;
					::Sleep(aLoadingYieldSleepTime);
				}
			}
		}
		ProcessSafeDeleteList();
		return true;
	}

	bool __thiscall GameApp::v_UpdateAppStep(bool* updated) {
		if (updated)*updated = false;
		if (mExitToTop)return false;
		if (mUpdateAppState == UPDATESTATE_PROCESS_DONE)mUpdateAppState = UPDATESTATE_MESSAGES;
		mUpdateAppDepth++;
		if (mUpdateAppState == UPDATESTATE_MESSAGES) {
			MSG msg;
			while ((::PeekMessageA(&msg, mHWnd, 0, 0, PM_REMOVE)) && (!mShutdown)) {
				::TranslateMessage(&msg);
				::DispatchMessageA(&msg);
			}
			ProcessDemo();
			if (!ProcessDeferredMessages(true)) {
				mUpdateAppState = UPDATESTATE_PROCESS_1;
			}
		} else {
			if (mStepMode) {
				if (mStepMode == 2) {
					::Sleep(mFrameTime);
					mUpdateAppState = UPDATESTATE_PROCESS_DONE;
				} else {
					mStepMode = 2;
					DoUpdateFrames();
					DoUpdateFramesF(1.0f);
					DrawDirtyStuff();
				}
			} else {
				int anOldUpdateCnt = mUpdateCount;
				Process(true);
				if (updated)*updated = mUpdateCount != anOldUpdateCnt;
			}
		}
		--mUpdateAppDepth;
		return true;
	}

	bool __thiscall GameApp::v_UpdateApp() {
		if (mClose)Shutdown();
		bool updated;
		while (true) {
			if (!UpdateAppStep(&updated))return false;
			if (updated)return true;
		}
	}

	bool __thiscall GameApp::v_DoUpdateFrames() {
		//if(gScreenSaverActive())return false;
		if (mPlayingDemoBuffer) {
			if ((mLoadingThreadCompleted) && (!mLoaded) && (mDemoLoadingComplete)) {
				mLoaded = true;
				::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
				mYieldMainThread = false;
				LoadingThreadCompleted();
			}
			if ((mLoaded == mDemoLoadingComplete) && (mUpdateCount != mLastDemoUpdateCnt)) {
				UpdateFrames();
				return true;
			}
			return false;
		} else {
			if ((mLoadingThreadCompleted) && (!mLoaded)) {
				::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
				mLoaded = true;
				mYieldMainThread = false;
				LoadingThreadCompleted();
				if (mRecordingDemoBuffer) {
					WriteDemoTimingBlock();
					mDemoBuffer.WriteNumBits(0, 1);
					mDemoBuffer.WriteNumBits(DEMO_LOADING_COMPLETE, 5);
				}
			}
			UpdateFrames();
			return true;
		}
	}

	void __thiscall GameApp::v_UpdateFrames() {
		if ((!mActive) || mMinimized)if (mBoard)mBoard->mStartDrawTime = mBoard->mIntervalDrawTime = (DWORD)GetTickCount64(), mBoard->continuedTime = mBoard->mIntervalDrawCountStart = 1;
		int updateTimes = 1;
		if (gSpeedQuarter) {
			int temp = gSpeedCounter + 1;
			if (temp >= 4)gSpeedCounter = 0;
			else updateTimes = 0;
		} else if (gSpeedTwenty)updateTimes = 20;
		for (; updateTimes; --updateTimes) {
#ifndef CVP
			GlobalClockRefresh();
#endif
			++mUpdateClock;
			if (mBoard)mBoard->CleanEntityNodes();
			(((SexyApp*)this)->*SexyApp::vfUpdateFrames)();
			if (mBgm)mBgm->mApp = this , mBgm->Update();
			if (mLoadingThreadCompleted && mAnimsLists)mAnimsLists->CleanNodes();
			TryExitLevel();
		}
	}

	void __thiscall WidgetManager::v_UpdateAll(ModalFlags* theFlags) {
		AutoModalFlags anAutoModalFlags(theFlags, mWidgetFlagsMod);
		if (theFlags->GetFlags() & WIDGETFLAGS_MARK_DIRTY)MarkDirty();
		WidgetManager* aWidgetManager = mWidgetManager;
		if (aWidgetManager == nullptr)return;
		if (theFlags->GetFlags() & WIDGETFLAGS_UPDATE) {
			if (mLastWMUpdateCount != mWidgetManager->mUpdateCnt) {
				mLastWMUpdateCount = mWidgetManager->mUpdateCnt;
				Update();
			}
		}
		std_list<Dialog*>::iterator anItr = mApp->mDialogList.begin();
		while (anItr != mApp->mDialogList.end()) {
			mUpdateIteratorModified = false;
			Dialog* aWidget = *anItr;
			if (aWidget == aWidgetManager->mBaseModalWidget)theFlags->mIsOver = true;
			aWidget->UpdateAll(theFlags);
			if (!mUpdateIteratorModified)++anItr;
		}
		if (((GameApp*)mApp)->mBoard)((GameApp*)mApp)->mBoard->UpdateAll(theFlags);
		if (((GameApp*)mApp)->mLoadingPage)((GameApp*)mApp)->mLoadingPage->UpdateAll(theFlags);
		if (((GameApp*)mApp)->mMainMenu)((GameApp*)mApp)->mMainMenu->UpdateAll(theFlags);
		if (((GameApp*)mApp)->mSelectCardWnd)((GameApp*)mApp)->mSelectCardWnd->UpdateAll(theFlags);
		if (((GameApp*)mApp)->mNotePage)((GameApp*)mApp)->mNotePage->UpdateAll(theFlags);
		if (((GameApp*)mApp)->mMV)((GameApp*)mApp)->mMV->UpdateAll(theFlags);
		if (((GameApp*)mApp)->mSelectLevelPage)((GameApp*)mApp)->mSelectLevelPage->UpdateAll(theFlags);
		mUpdateIteratorModified = true;
	}

	void __thiscall Board::v_Update() {
		if (super_pause) {
			++mUpdateCnt;
			MarkDirty();
			UpdateCursor();
			mMouseAddProp->Update();
			mMouseProp->Update();
			return;
		}
		++mUpdateCnt;
		MarkDirty();
		mSceneProp->Update();
		UpdateCursor();
		if (mApp->isGarden())mApp->mGardenProp->UpdateMain();
		if (mApp->isVB() && (nextLevelCountdown > 0) && mApp->DaveState != GameApp::DaveState::NIL)mApp->UpdateDave();
		if (pause) {
			mLevelProp->UpdateEffect();
			mMouseAddProp->visible = false;
			mMouseProp->visible = false;
		} else {
			bool temp = mouseDisabled || !IfShowCursor();
			if (!btnMenu->invisible)btnMenu->disabled = temp;
			btnMenu->Update();
			if (btnStartLS)btnStartLS->disabled = temp, btnStartLS->Update();
			mApp->mAnimsLists->Update();
			mBoardText->Update();
			UpdateAdvice();
			if (paoSafeCountdown > 0)--paoSafeCountdown;
			if (sunValueShineCountdown > 0)--sunValueShineCountdown;
			if (shakeCountdown > 0) {
				if (--shakeCountdown) {
					if (rand(2, RandBattle))shakeOffset.mX = -shakeOffset.mX;
					mX = getCurveValue(9, shakeCountdown, 12, 0, 0, shakeOffset.mX);
					mY = getCurveValue(9, shakeCountdown, 12, 0, 0, shakeOffset.mY);
				} else mX = 0, mY = 0;
			}
			if (moneyShowCountdown > 0) {
				if (mApp->GetDialog(Dialog::Type::PURCHASE_PACKET_SLOT));
				else --moneyShowCountdown;
			}
			TidyDialogList();
			if (glintCountdown > 0)return;
			++timeBoard;
			if (yard == Yard::Type::POOL || yard == Yard::Type::FOG) {
				if ((poolFreezeCountdown == 0) && (mApp->gameState != GameApp::State::LOSE) && (!mSceneProp->InheritBoard())) {
					++mApp->poolEffectMImg->mPoolCounter;
				}
			}
			if (yard == Yard::Type::POOL && !particleSystem && continuedTime > 0) {
				particleSystem = GetID(*(mApp->NewParticleSystem(ParticleSystem::Type::POOL_SPARKLY, 220000, 450, 295)));
			}
			UpdateBuildings();
			UpdateRowFire();
			UpdateMain();
			UpdateFog();
			mLevelProp->UpdateEffect();
			UpdateLevelEndProcess();
			mousePoint = { mApp->mWidgetManager->mLastMouseX,mApp->mWidgetManager->mLastMouseY };
		}
	}

	void __thiscall Board::v_UpdateAll(ModalFlags* theFlags) {
		AutoModalFlags anAutoModalFlags(theFlags, mWidgetFlagsMod);
		if (theFlags->GetFlags() & WIDGETFLAGS_MARK_DIRTY)MarkDirty();
		WidgetManager* aWidgetManager = mWidgetManager;
		if (aWidgetManager == nullptr)return;
		if (theFlags->GetFlags() & WIDGETFLAGS_UPDATE) {
			if (mLastWMUpdateCount != mWidgetManager->mUpdateCnt) {
				mLastWMUpdateCount = mWidgetManager->mUpdateCnt;
				Update();
			}
		}
		mUpdateIterator = mWidgets.begin();
		while (mUpdateIterator != mWidgets.end()) {
			mUpdateIteratorModified = false;
			Widget* aWidget = *mUpdateIterator;
			if (aWidget == aWidgetManager->mBaseModalWidget)theFlags->mIsOver = true;
			aWidget->UpdateAll(theFlags);
			if (!mUpdateIteratorModified)++mUpdateIterator;
		}
		mUpdateIteratorModified = true;
	}

	bool __thiscall GameApp::v_DrawDirtyStuff() {
		MTAutoDisallowRand aDisallowRand;
		if (gIsFailing) {
			Redraw(nullptr);
			mHasPendingDraw = false;
			mLastDrawWasEmpty = true;
			return false;
		}
		/*
					if(mShowFPS){
						switch(mShowFPSMode){
						case FPS_ShowFPS: CalculateFPS(); break;
						case FPS_ShowCoords:
							if(mWidgetManager)FPSDrawCoords(mWidgetManager->mLastMouseX,mWidgetManager->mLastMouseY);
							break;
						}
						if(mPlayingDemoBuffer)CalculateDemoTimeLeft();
					}
		 */
		DWORD aStartTime = ::timeGetTime();
		if (aStartTime - gPeriodicTick > 1000)gPeriodicTick = aStartTime;
		if (gScreenSaverActive) {
			mHasPendingDraw = false;
			mLastDrawWasEmpty = true;
			return false;
		}
		mIsDrawing = true;
		bool drewScreen = mWidgetManager->DrawScreen();
#ifndef CVP
		if (!gGameApp->mLoadingPage) Ui::WidgetManager::Draw();
#endif
		mIsDrawing = false;
		if ((drewScreen || (aStartTime - mLastDrawTick >= 1000) || (mCustomCursorDirty)) && ((int)(aStartTime - mNextDrawTick) >= 0)) {
			mLastDrawWasEmpty = false;
			mDrawCount++;
			DWORD aMidTime = ::timeGetTime();
			mFPSCount++;
			mFPSTime += aMidTime - aStartTime;
			mDrawTime += aMidTime - aStartTime;
			/*
							if(mShowFPS){
								Graphics g(mDDInterface->GetScreenImage());
								g.DrawImage(gFPSImage,mWidth - gFPSImage->GetWidth()- 10,mHeight - gFPSImage->GetHeight()- 10);
								if(mPlayingDemoBuffer)g.DrawImage(gDemoTimeLeftImage,mWidth - gDemoTimeLeftImage->GetWidth()- 10,mHeight - gFPSImage->GetHeight()- gDemoTimeLeftImage->GetHeight()- 15);
							}
			 */
			if (mWaitForVSync && mIsPhysWindowed && mSoftVSyncWait) {
				DWORD aTick = ::timeGetTime();
				if (aTick - mLastDrawTick < (DWORD)mDDInterface->mMillisecondsPerFrame)::Sleep(mDDInterface->mMillisecondsPerFrame - (aTick - mLastDrawTick));
			}
			DWORD aPreScreenBltTime = ::timeGetTime();
			mLastDrawTick = aPreScreenBltTime;
			Redraw(nullptr);
			UpdateFTimeAcc();
			DWORD aEndTime = ::timeGetTime();
			mScreenBltTime = aEndTime - aPreScreenBltTime;
			if ((mLoadingThreadStarted) && (!mLoadingThreadCompleted)) {
				int aTotalTime = aEndTime - aStartTime;
				mNextDrawTick += 35 + max(aTotalTime, 15);
				if ((int)(aEndTime - mNextDrawTick) >= 0)mNextDrawTick = aEndTime;
			} else mNextDrawTick = aEndTime;
			mHasPendingDraw = false;
			mCustomCursorDirty = false;
			return true;
		} else {
			mHasPendingDraw = false;
			mLastDrawWasEmpty = true;
			return false;
		}
	}

	void GameApp::v_EnforceCursor() {
		bool wantSysCursor = true;
		if (mDDInterface == nullptr)return;
		if ((mSEHOccured) || (!mMouseIn)) {
			::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_ARROW));
			if (mDDInterface->SetCursorImage(nullptr))mCustomCursorDirty = true;
		} else {
			if ((mCursorImages[mCursorNum] == nullptr) || ((!mPlayingDemoBuffer) && (!mCustomCursorsEnabled) && (mCursorNum != CURSOR_CUSTOM))) {
				if (mOverrideCursor)::SetCursor(mOverrideCursor);
				else {
					switch (mCursorNum) {
					case CURSOR_POINTER: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_ARROW)); break;
					case CURSOR_HAND: ::SetCursor(mHandCursor); break;
					case CURSOR_TEXT: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_IBEAM)); break;
					case CURSOR_DRAGGING: ::SetCursor(mDraggingCursor); break;
					case CURSOR_CIRCLE_SLASH: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_NO)); break;
					case CURSOR_SIZEALL: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_SIZEALL)); break;
					case CURSOR_SIZENESW: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_SIZENESW)); break;
					case CURSOR_SIZENS: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_SIZENS)); break;
					case CURSOR_SIZENWSE: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_SIZENWSE)); break;
					case CURSOR_SIZEWE: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_SIZEWE)); break;
					case CURSOR_WAIT: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_WAIT)); break;
					case CURSOR_CUSTOM: ::SetCursor(nullptr); break;
					case CURSOR_NONE: ::SetCursor(nullptr); break;
					default: ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_ARROW)); break;
					}
				}
				if (mDDInterface->SetCursorImage(nullptr))mCustomCursorDirty = true;
			} else {
				if (mDDInterface->SetCursorImage(mCursorImages[mCursorNum]))mCustomCursorDirty = true;
				if (!mPlayingDemoBuffer)::SetCursor(nullptr);
				else {
					POINT aULCorner = { 0,0 };
					::ClientToScreen(mHWnd, &aULCorner);
					POINT aBRCorner = { mWidth,mHeight };
					::ClientToScreen(mHWnd, &aBRCorner);
					POINT aPoint;
					::GetCursorPos(&aPoint);
					if ((aPoint.x >= aULCorner.x) && (aPoint.y >= aULCorner.y) && (aPoint.x < aBRCorner.x) && (aPoint.y < aBRCorner.y))::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_NO));
					else ::SetCursor(::LoadCursorA(nullptr, (LPCSTR)IDC_ARROW));
				}
				wantSysCursor = false;
			}
		}
		if (wantSysCursor != mSysCursor) {
			mSysCursor = wantSysCursor;
		}
	}

	void DDImage::DeleteAllNonSurfaceData() {
		delete[] mBits;
		mBits = nullptr;
		delete[] mNativeAlphaData;
		mNativeAlphaData = nullptr;
		delete[] mRLAdditiveData;
		mRLAdditiveData = nullptr;
		delete[] mRLAlphaData;
		mRLAlphaData = nullptr;
		delete[] mColorTable;
		mColorTable = nullptr;
		delete[] mColorIndices;
		mColorIndices = nullptr;
	}







	void reVirtual() {
		GameApp::vfDoMainLoop = &GameApp::v_DoMainLoop;
		GameApp::vfUpdateApp = &GameApp::v_UpdateApp;
		GameApp::vfDoUpdateFrames = &GameApp::v_DoUpdateFrames;
		GameApp::vfUpdateFrames = &GameApp::v_UpdateFrames;
		GameApp::vfDrawDirtyStuff = &GameApp::v_DrawDirtyStuff;
		GameApp::vfEnforceCursor = &GameApp::v_EnforceCursor;
		GameApp::vfUpdateAppStep = &GameApp::v_UpdateAppStep;
		GameApp::vfProcess = &GameApp::v_Process;
		WidgetManager::vfUpdateAll = &WidgetManager::v_UpdateAll;
		Board::vfUpdateAll = &Board::v_UpdateAll;
		Board::vfUpdate = &Board::v_Update;
		Board::vfMouseDown = &Board::v_MouseDown;
		/*

			void SexyAppBase::Redraw(Rect* theClipRect){
				if((mIsDrawing)||(mShutdown))return;
				if(gScreenSaverActive)return;
				if(!mDDInterface->Redraw(theClipRect)){
					gD3DInterfacePreDrawError = false;
					if(!gIsFailing){
						gIsFailing = true;
					}
					WINDOWPLACEMENT aWindowPlacement;
					ZeroMemory(&aWindowPlacement,sizeof(aWindowPlacement));
					aWindowPlacement.length = sizeof(aWindowPlacement);
					::GetWindowPlacement(mHWnd,&aWindowPlacement);
					DWORD aTick = ::(DWORD)GetTickCount64();
					if((mActive ||(aTick - gRetryTick > 1000 && mIsPhysWindowed))&&(aWindowPlacement.showCmd != SW_SHOWMINIMIZED)&&(!mMinimized)){
						gRetryTick = aTick;
						mWidgetManager->mImage = nullptr;
						int aResult = InitDDInterface();
						if((mIsWindowed)&&(aResult == DDInterface::RESULT_INVALID_COLORDEPTH)){
							if(!mActive)return;
							SwitchScreenMode(false);
							mForceFullscreen = true;
							return;
						} else if(aResult == DDInterface::RESULT_3D_FAIL){
							Set3DAcclerated(false);
							return;
						} else if(aResult != DDInterface::RESULT_OK){
							return;
						}
						ReInitImages();
						mWidgetManager->mImage = mDDInterface->GetScreenImage();
						mWidgetManager->MarkAllDirty();
						mLastTime = ::timeGetTime();
					}
				} else {
					if(gIsFailing){
						gIsFailing = false;
						gRetryTick = 0;
					}
				}
				mFPSFlipCount++;
			}

				void WidgetContainer::MarkDirty(){
					if(mParent)mParent->MarkDirty(this);
					else mDirty = true;
				}

				Rect WidgetContainer::GetRect(){
					return Rect(mX,mY,mWidth,mHeight);
				}

				bool WidgetContainer::Intersects(WidgetContainer* theWidget){
					return GetRect().Intersects(theWidget->GetRect());
				}

			void WidgetContainer::MarkDirtyFull(){
				if(mParent)mParent->MarkDirtyFull(this);
				else mDirty = true;
			}

			void WidgetContainer::MarkDirtyFull(WidgetContainer* theWidget){
				MarkDirtyFull();
				theWidget->mDirty = true;
				if(mParent)return;
				std_list<Widget*>::iterator aFoundWidgetItr = std::find(mWidgets.begin(),mWidgets.end(),theWidget);
				if(aFoundWidgetItr == mWidgets.end())return;
				std_list<Widget*>::iterator anItr = aFoundWidgetItr;
				if(anItr != mWidgets.begin()){
					--anItr;
					for(;){
						Widget* aWidget = *anItr;
						if(aWidget->mVisible){
							if((!aWidget->mHasTransparencies)&&(!aWidget->mHasAlpha)){
								Rect aRect = Rect(theWidget->mX,theWidget->mY,theWidget->mWidth,theWidget->mHeight).Intersection(Rect(0,0,mWidth,mHeight));
								if((aWidget->Contains(aRect.mX,aRect.mY)&&(aWidget->Contains(aRect.mX + aRect.mW - 1,aRect.mY + aRect.mH - 1)))){
									aWidget->MarkDirty();
									break;
								}
							}
							if(aWidget->Intersects(theWidget))MarkDirty(aWidget);
						}
						if(anItr == mWidgets.begin())break;
						--anItr;
					}
				}
				anItr = aFoundWidgetItr;
				while(anItr != mWidgets.end()){
					Widget* aWidget = *anItr;
					if((aWidget->mVisible)&&(aWidget->Intersects(theWidget)))MarkDirty(aWidget);
					++anItr;
				}
			}

			void WidgetContainer::UpdateAll(ModalFlags* theFlags){
				AutoModalFlags anAutoModalFlags(theFlags,mWidgetFlagsMod);
				if(theFlags->GetFlags()& WIDGETFLAGS_MARK_DIRTY)MarkDirty();
				WidgetManager* aWidgetManager = mWidgetManager;
				if(aWidgetManager == nullptr)return;
				if(theFlags->GetFlags()& WIDGETFLAGS_UPDATE){
					if(mLastWMUpdateCount != mWidgetManager->mUpdateCnt){
						mLastWMUpdateCount = mWidgetManager->mUpdateCnt;
						Update();
					}
				}
				mUpdateIterator = mWidgets.begin();
				while(mUpdateIterator != mWidgets.end()){
					mUpdateIteratorModified = false;
					Widget* aWidget = *mUpdateIterator;
					if(aWidget == aWidgetManager->mBaseModalWidget)theFlags->mIsOver = true;
					aWidget->UpdateAll(theFlags);
					if(!mUpdateIteratorModified)++mUpdateIterator;
				}
				mUpdateIteratorModified = true;
			}

			void SexyAppBase::WriteToRegistry(){
				RegistryWriteInteger(u8"MusicVolume",(int)(mMusicVolume * 100));
				RegistryWriteInteger(u8"SfxVolume",(int)(mSfxVolume * 100));
				RegistryWriteInteger(u8"Muted",(mMuteCount - mAutoMuteCount > 0)? 1 : 0);
				RegistryWriteInteger(u8"ScreenMode",mIsWindowed ? 0 : 1);
				RegistryWriteInteger(u8"PreferredX",mPreferredX);
				RegistryWriteInteger(u8"PreferredY",mPreferredY);
				RegistryWriteInteger(u8"CustomCursors",mCustomCursorsEnabled ? 1 : 0);
				RegistryWriteInteger(u8"InProgress",0);
				RegistryWriteBoolean(u8"WaitForVSync",mWaitForVSync);
			}

			void SexyAppBase::Shutdown(){
				if((mPrimaryThreadId != 0)&&(::GetCurrentThreadId()!= mPrimaryThreadId))mLoadingFailed = true;
				else if(!mShutdown){
					mExitToTop = true;
					mShutdown = true;
					ShutdownHook();
					if(mPlayingDemoBuffer){
						SetMusicVolume(mDemoMusicVolume);
						SetSfxVolume(mDemoSfxVolume);
					}
					while(mCursorThreadRunning)::Sleep(10);
					if(mMusicInterface)mMusicInterface->StopAllMusic();
					if((!mIsPhysWindowed)&&(mDDInterfaceptr)&&(mDDInterface->mDDptr))mDDInterface->mDD->RestoreDisplayMode();
					if(mHWndptr)::ShowWindow(mHWnd,SW_HIDE);
					RestoreScreenResolution();
					if(mReadFromRegistry)WriteToRegistry();
					Pvz::CloseJPEG2000();
				}
			}

			void SexyAppBase::Mute(bool autoMute){
				mMuteCount++;
				if(autoMute)mAutoMuteCount++;
				SetMusicVolume(mMusicVolume);
				SetSfxVolume(mSfxVolume);
			}

			void SexyAppBase::Unmute(bool autoMute){
				if(mMuteCount > 0){
					--mMuteCount;
					if(autoMute)--mAutoMuteCount;
				}
				SetMusicVolume(mMusicVolume);
				SetSfxVolume(mSfxVolume);
			}

			void SexyAppBase::SwitchScreenMode(){
				SwitchScreenMode(mIsWindowed,Is3DAccelerated(),true);
			}

			void WidgetContainer::MarkAllDirty(){
				MarkDirty();
				std_list<Widget*>::iterator anItr = mWidgets.begin();
				while(anItr != mWidgets.end()){(*anItr)->mDirty = true;
					(*anItr)->MarkAllDirty();
					++anItr;
				}
			}

			void WidgetContainer::DrawAll(ModalFlags* theFlags,Graphics* g){
				if(mPriority > mWidgetManager->mMinDeferredOverlayPriority)mWidgetManager->FlushDeferredOverlayWidgets(mPriority);
				AutoModalFlags anAutoModalFlags(theFlags,mWidgetFlagsMod);
				if((mClip)&&(theFlags->GetFlags()& WIDGETFLAGS_CLIP))g->ClipRect(0,0,mWidth,mHeight);
				if(mWidgets.size()== 0){
					if(theFlags->GetFlags()& WIDGETFLAGS_DRAW)Draw(g);
					return;
				}
				if(theFlags->GetFlags()& WIDGETFLAGS_DRAW){
					mState temp;
					memcpyd((LPVOID)((DWORD)this + 4),&temp,sizeof(mState));
					Draw(g);
					memcpyd(&temp,(LPVOID)((DWORD)this + 4),sizeof(mState));
				}
				std_list<Widget*>::iterator anItr = mWidgets.begin();
				while(anItr != mWidgets.end()){
					Widget* aWidget = *anItr;
					if(aWidget->mVisible){
						if(aWidget == mWidgetManager->mBaseModalWidget)theFlags->mIsOver = true;
						Graphics aClipG(*g);
						aClipG.Translate(aWidget->mX,aWidget->mY);
						aWidget->DrawAll(theFlags,&aClipG);
						aWidget->mDirty = false;
					}
					++anItr;
				}
			}

			Rect Widget::GetInsetRect(){
				return Rect(mX + mMouseInsets.mLeft,mY + mMouseInsets.mTop,mWidth - mMouseInsets.mLeft - mMouseInsets.mRight,mHeight - mMouseInsets.mTop - mMouseInsets.mBottom);
			}

			Point WidgetContainer::GetAbsPos(){
				if(mParent == nullptr)return Point(mX,mY);
				else return Point(mX,mY)+ mParent->GetAbsPos();
			}

			void Widget::LostFocus(){
				mHasFocus = false;
			}

			void WidgetContainer::RemovedFromManager(WidgetManager* theWidgetManager){
				for(std_list<Widget*>::iterator anItr = mWidgets.begin(); anItr != mWidgets.end(); ++anItr){
					Widget* aWidget = *anItr;
					theWidgetManager->DisableWidget(aWidget);
					aWidget->RemovedFromManager(theWidgetManager);
					aWidget->mWidgetManager = nullptr;
				}
				if(theWidgetManager->mPopupCommandWidget == this)theWidgetManager->mPopupCommandWidget = nullptr;
			}

			void WidgetContainer::RemoveWidget(Widget* theWidget){
				std_list<Widget*>::iterator anItr = std::find(mWidgets.begin(),mWidgets.end(),theWidget);
				if(anItr != mWidgets.end()){
					theWidget->WidgetRemovedHelper();
					theWidget->mParent = nullptr;
					bool erasedCur =(anItr == mUpdateIterator);
					mWidgets.erase(anItr);
					++anItr;
					if(erasedCur){
						mUpdateIterator = anItr;
						mUpdateIteratorModified = true;
					}
				}
			}

			bool Widget::WantsFocus(){
				return mWantsFocus;
			}

			void Widget::GotFocus(){
				mHasFocus = true;
			}

			void WidgetContainer::SysColorChangedAll(){
				SysColorChanged();
				static int aDepthCount = 0;
				if(mWidgets.size()> 0)aDepthCount++;
				std_list<Widget*>::iterator anItr = mWidgets.begin();
				while(anItr != mWidgets.end()){
					Widget* aWidget = *anItr;
					aWidget->SysColorChangedAll();
					++anItr;
				}
			}

	void WidgetContainer::MarkDirty(WidgetContainer* theWidget) {
		if (theWidget->mDirty)return;
		MarkDirty();
		theWidget->mDirty = true;
		if (mParent)return;
		if (theWidget->mHasAlpha)MarkDirtyFull(theWidget);
		else {
			bool found = false;
			std_list<Widget*>::iterator anItr = mWidgets.begin();
			while (anItr != mWidgets.end()) {
				Widget* aWidget = *anItr;
				if (aWidget == theWidget)found = true;
				else if (found) {
					if ((aWidget->mVisible) && (aWidget->Intersects(theWidget)))MarkDirty(aWidget);
				}
				++anItr;
			}
		}
	}

	bool Widget::Contains(int theX, int theY) {
		return((theX >= mX) && (theX < mX + mWidth) && (theY >= mY) && (theY < mY + mHeight));
	}

	bool Widget::IsPointVisible(int x, int y) {
		return true;
	}

	void Widget::ShowFinger(bool on) {
		if (mWidgetManager == nullptr)return;
		if (on)mWidgetManager->mApp->SetCursor(CURSOR_HAND);
		else mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
	}

	void SexyAppBase::SetSfxVolume(double theVolume) {
		mSfxVolume = theVolume;
		if (mSoundManager)mSoundManager->SetVolume((mMuteCount > 0) ? 0 : mSfxVolume);
	}

	void SexyAppBase::SetMusicVolume(double theVolume) {
		mMusicVolume = theVolume;
		if (mMusicInterface)mMusicInterface->SetVolume((mMuteCount > 0) ? 0 : mMusicVolume);
	}

	void SexyAppBase::SwitchScreenMode(bool wantWindowed, bool is3d, bool force) {
		if (mForceFullscreen)wantWindowed = false;
		if (mIsWindowed == wantWindowed && !force) {
			Set3DAcclerated(is3d);
			return;
		}
		Set3DAcclerated(is3d, false);
		mIsWindowed = wantWindowed;
		MakeWindow();
		if (!mIsOpeningURL) {
			::ShowWindow(mHWnd, SW_NORMAL);
			::SetForegroundWindow(mHWnd);
		} else {
			::ShowWindow(mHWnd, SW_SHOWNOACTIVATE);
		}
		if (mSoundManager) {
			mSoundManager->SetCooperativeWindow(mHWnd, mIsWindowed);
		}
		mLastTime = ::timeGetTime();
	}

	void SexyAppBase::SwitchScreenMode(bool wantWindowed) {
		SwitchScreenMode(wantWindowed, Is3DAccelerated());
	}

	void SexyAppBase::URLOpenSucceeded(const std_string& theURL) {
		mIsOpeningURL = false;
		if (mShutdownOnURLOpen)Shutdown();
	}

	bool SexyAppBase::DebugKeyDown(int theKey) {
		__asm {
			push theKey
			mov ecx, this
			mov eax, 0x54FAB0ul
			call eax
		}
	}

	void SexyAppBase::URLOpenFailed(const std_string& theURL) {
		mIsOpeningURL = false;
	}

	void WidgetManager::DisableWidget(Widget* theWidget) {
		if (mOverWidget == theWidget) {
			Widget* aOverWidget = mOverWidget;
			mOverWidget = nullptr;
			MouseLeave(aOverWidget);
		}
		if (mLastDownWidget == theWidget) {
			Widget* aLastDownWidget = mLastDownWidget;
			mLastDownWidget = nullptr;
			DoMouseUps(aLastDownWidget, mDownButtons);
			mDownButtons = 0;
		}
		if (mFocusWidget == theWidget) {
			Widget* aFocusWidget = mFocusWidget;
			mFocusWidget = nullptr;
			aFocusWidget->LostFocus();
		}
		if (mBaseModalWidget == theWidget)mBaseModalWidget = nullptr;
	}

	void WidgetManager::SetFocus(Widget* aWidget) {
		if (aWidget == mFocusWidget)return;
		if (mFocusWidget)mFocusWidget->LostFocus();
		if ((aWidget) && (aWidget->mWidgetManager == this)) {
			mFocusWidget = aWidget;
			if ((mHasFocus) && (mFocusWidget))mFocusWidget->GotFocus();
		} else mFocusWidget = nullptr;
	}

	void SoundManager::SetVolume(double theVolume) { return; }

	void MusicInterface::SetVolume(double theVolume) { return; }

	void BassMusicInterface::SetVolume(double theVolume) {
		int aVolume = (int)(theVolume * mMaxMusicVolume);
		if (gBass->mVersion2) {
			gBass->BASS_SetConfig(/*BASS_CONFIG_GVOL_MUSIC*6, (int)(theVolume * 100));
			gBass->BASS_SetConfig(/*BASS_CONFIG_GVOL_STREAM*5, (int)(theVolume * 100));
		} else gBass->BASS_SetGlobalVolumes(aVolume, aVolume, aVolume);
	}


	*/
	}

	MTRand RandBattle = MTRand();
	MTRand RandSample = MTRand();
	MTRand RandAnim = MTRand();
}