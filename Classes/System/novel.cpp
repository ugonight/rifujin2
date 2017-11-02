#pragma  execution_character_set("utf-8")

#include "novel.h"
#include "define.h"

#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

Novel::~Novel() {
	for (int i = 0; i < MAX_BRANCH; i++) {
		//if (mFuncTask[i].size() > 1) {
			for (auto tsk : mFuncTask[i]) {
				if (tsk.func/*->getReferenceCount() > 0*/) 
					CC_SAFE_RELEASE_NULL(tsk.func);
			}
		//}
	}
}

bool Novel::init() {

	if (Layer::init() == false)
		return false;

	this->scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mCount = 0;
	mEndFlag = 0;
	mTouchTime = 0; mHideMsg = 0; mFast = 0;
	mBranch = 0; //最初はメイン
	for (int i = 0; i < 4; i++)mImageNum[i] = 0;
	mSwitch = false;
	mLogOnly = false;

	for (int i = 0; i < MAX_BRANCH; i++) {
		mNovelNum[i] = 0;
		mNovelSetNum[i] = 1;
		mSentense[i].push_back("");
		mTaskNum[i] = mColorNum[i] = mFuncNum[i] = mSwitchNum[i] = mJumpNum[i] = 0;
	}
	

	//背景
	auto bg = Sprite::create();
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "bg0");

	//キャラクター・センター
	auto charaC = Sprite::create();
	charaC->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(charaC, 1, "charaC0");

	//キャラクター・レフト
	auto charaL = Sprite::create();
	charaL->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(charaL, 1, "charaL0");

	//キャラクター・ライト
	auto charaR = Sprite::create();
	charaR->setPosition(Vec2(visibleSize.width * 3 / 4 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(charaR, 1, "charaR0");

	//メッセージボックス
	auto msg = Sprite::create("msg.png");
	msg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	msg->setOpacity(0.0f);
	auto seq = Sequence::create(
		FadeIn::create(0.5f),
		CallFunc::create(CC_CALLBACK_0(Novel::func,this)),
		NULL);
	msg->runAction(seq);
	this->addChild(msg, 2,"msgBox");

	//文字
	auto label = Label::createWithTTF("", FONT_NAME, 24);
	label->setPosition(Vec2(origin.x + 50,
				origin.y + visibleSize.height - 340));
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setColor(Color3B::BLUE);
	label->enableOutline(Color4B::WHITE, 2);
	label->setDimensions(750, 130);
	this->addChild(label, 3, "label");

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Novel::touchEvent, this);
	listener->onTouchEnded = [this](Touch *touch, Event *event) { mTouchTime = 0; };
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//バックログ
	auto path = FileUtils::getInstance()->getWritablePath();
	auto file = path + "speak.plist";

	if (FileUtils::getInstance()->isFileExist(file)) {
		mLog = FileUtils::getInstance()->getValueVectorFromFile(file);
	}

	auto log = Sprite::create("log.png");
	log->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	log->setPosition(Vec2(visibleSize.width -15 + origin.x, -15 + origin.y + visibleSize.height));
	addChild(log, 5, "log");

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Novel::logEvent, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, log);

	//早送り
	auto fast = Sprite::create("ff.png");
	fast->setPosition(Vec2(60 + origin.x, visibleSize.height / 2 - 50));
	addChild(fast, 3, "fast");
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
			mFast = true;
			return true;
		}
		return false;
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event) { mFast = false; };
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, fast);


	return true;
}

void Novel::func() { 
	mNovelNum[0] = 1;
	auto label = (Label*)this->getChildByName("label");
	label->setString(mSentense[0][mNovelNum[0]]);
	setDelayAnime();
}

bool Novel::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto label = (Label*)this->getChildByName("label");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (mLogOnly == true)
		return false;


	//会話を進める
	if (/*touch->getLocation().y < visibleSize.height / 2 && */
		!mHideMsg && 
		!mSwitch &&
		mNovelNum[mBranch] > 0 /* フェードイン前に押されるのを防ぐ */) {
		readTalk();
		mTouchTime = 1;
	}
	else {
		getChildByName("msgBox")->setVisible(true);
		getChildByName("label")->setVisible(true);
		getChildByName("fast")->setVisible(true);
		mHideMsg = false;
	}

	return true;
}

void Novel::readTalk() {
	auto label = (Label*)this->getChildByName("label");
	if (endCheck()) {	//文がすべて表示されていたら
						//バックログに記録
		if (this->getOpacity() == 255) mLog.push_back(Value(mSentense[mBranch][mNovelNum[mBranch]]));
		if (mSentense[mBranch].size() - 1 > mNovelNum[mBranch]) {	//文リストの最後でなければ
																	//次の分をセット
			mNovelNum[mBranch]++;
			label->setString(mSentense[mBranch][mNovelNum[mBranch]]);
			setDelayAnime();
		}
		else if (mSentense[mBranch].size() - 1 == mNovelNum[mBranch] && this->getOpacity() == 255) {	//文リストの最後なら
			mNovelNum[mBranch]++;
			this->runAction(Sequence::create(FadeOut::create(0.5f), CallFunc::create(CC_CALLBACK_0(Novel::end, this)),/* RemoveSelf::create(true),*/ NULL));
			//スプライト全部をフェードアウトする
			Sprite* spr;
			for (auto child : this->getChildren()) {
				spr = (Sprite*)child;
				spr->runAction(FadeOut::create(0.5f));
			}

			//ログを保存
			mLog.push_back(Value(""));
			auto path = FileUtils::getInstance()->getWritablePath();
			auto file = path + "speak.plist";
			FileUtils::getInstance()->writeValueVectorToFile(mLog, file);

		}
	}
	else {
		for (int i = 0; i < label->getStringLength() + label->getStringNumLines(); i++) {
			auto AChar = label->getLetter(i);
			if (nullptr != AChar) {
				AChar->setOpacity(255);
				AChar->stopAllActions();
			}
		}
	}


}

void Novel::end(){	
	mEndFlag = 1;
}

void Novel::update(float delta) {
	if (mTouchTime > 0) mTouchTime++;
	if (mTouchTime > 60) {
		getChildByName("msgBox")->setVisible(false);
		getChildByName("label")->setVisible(false);
		getChildByName("fast")->setVisible(false);
		mHideMsg = true;
	}
	if (mFast) {
		if (/*touch->getLocation().y < visibleSize.height / 2 && */
			!mHideMsg &&
			!mSwitch &&
			mSentense[mBranch].size() - 1 > mNovelNum[mBranch] &&
			mNovelNum[mBranch] > 0 /* フェードイン前に押されるのを防ぐ */) {
			readTalk();
		}
	}

	updateImg();
	updateColor();
	updateFunc();
	updateSwitch();
	updateJump();
}

int Novel::addSentence(int branch,std::string s) {
	mSentense[branch].push_back(s);
	mNovelSetNum[branch]++;
	return mNovelSetNum[branch] - 1;
}

void Novel::updateImg() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int num = mTaskNum[mBranch];
	std::stringstream name;
	while (mTask[mBranch][num].num == mNovelNum[mBranch]) {
		name.clear(); name.str("");

		if (mTask[mBranch][num].imgPos == IMG_BG) {
			name << "bg" << mImageNum[0];
			auto old = this->getChildByName(name.str());
			old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));

			mImageNum[0]++;

			name.clear(); name.str("");
			name << "bg" << mImageNum[0];

			if (mTask[mBranch][num].imgName != "") {
				auto newOne = Sprite::create(mTask[mBranch][num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.5f));
				this->addChild(newOne, 0, name.str());
			}
			else {
				auto bg = Sprite::create();
				bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(bg, 0, name.str());
			}
		}
		else if (mTask[mBranch][num].imgPos == IMG_CENTER) {
			name << "charaC" << mImageNum[1];
			auto old = this->getChildByName(name.str());
			old->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(true), NULL));

			mImageNum[1]++;

			name.clear(); name.str("");
			name << "charaC" << mImageNum[1];

			if (mTask[mBranch][num].imgName != "") {
				auto newOne = Sprite::create(mTask[mBranch][num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.3f));
				this->addChild(newOne, 1, name.str());
			}
			else {
				auto charaC = Sprite::create();
				charaC->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(charaC, 1, name.str());
			}
		}
		else if (mTask[mBranch][num].imgPos == IMG_LEFT) {
			name << "charaL" << mImageNum[2];
			auto old = this->getChildByName(name.str());
			old->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(true), NULL));

			mImageNum[2]++;

			name.clear(); name.str("");
			name << "charaL" << mImageNum[2];

			if (mTask[mBranch][num].imgName != "") {
				auto newOne = Sprite::create(mTask[mBranch][num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.3f));
				this->addChild(newOne, 1, name.str());
			}
			else {
				auto charaL = Sprite::create();
				charaL->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(charaL, 1, name.str());
			}
		}
		else if (mTask[mBranch][num].imgPos == IMG_RIGHT) {
			name << "charaR" << mImageNum[3];
			auto old = this->getChildByName(name.str());
			old->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(true), NULL));

			mImageNum[3]++;

			name.clear(); name.str("");
			name << "charaR" << mImageNum[3];

			if (mTask[mBranch][num].imgName != "") {
				auto newOne = Sprite::create(mTask[mBranch][num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.3f));
				this->addChild(newOne, 1, name.str());
			}
			else {
				auto charaR = Sprite::create();
				charaR->setPosition(Vec2(visibleSize.width * 3 / 4 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(charaR, 1, name.str());
			}
		}
		mTask[mBranch].erase(mTask[mBranch].begin());
	}
}

bool Novel::getEndFlag(){return mEndFlag;}

void Novel::setBg(int branch, std::string s) {
	Task tsk = { mNovelSetNum[branch],IMG_BG,s };
	mTask[branch].push_back(tsk);
}

void Novel::setCharaC(int branch, std::string s) {
	Task tsk = { mNovelSetNum[branch],IMG_CENTER,s };
	mTask[branch].push_back(tsk);
}

void Novel::setCharaL(int branch, std::string s) {
	Task tsk = { mNovelSetNum[branch],IMG_LEFT,s };
	mTask[branch].push_back(tsk);
}

void Novel::setCharaR(int branch, std::string s) {
	Task tsk = { mNovelSetNum[branch],IMG_RIGHT,s };
	mTask[branch].push_back(tsk);
}

void Novel::setEndTask(int branch) {
	if (branch > 0) {
		Task tsk = { -1,IMG_NONE,"" };
		mTask[branch].push_back(tsk);

		CTask ctsk = { -1, Color3B::BLACK };
		mColorTask[branch].push_back(ctsk);

		auto fnc = CallFunc::create([] {});
		fnc->retain();
		FTask ftsk = { -1, fnc };
		mFuncTask[branch].push_back(ftsk);

		STask stsk = { -1 };
		mSwitchTask[branch].push_back(stsk);

		JTask jtsk = { -1 };
		mJumpTask[branch].push_back(jtsk);
	}
	else {	//-の場合はまとめて入れる
		for (int i = 0; i < MAX_BRANCH; i++) {
			Task tsk = { -1,IMG_NONE,"" };
			mTask[i].push_back(tsk);

			CTask ctsk = { -1, Color3B::BLACK };
			mColorTask[i].push_back(ctsk);

			auto fnc = CallFunc::create([] {});
			fnc->retain();
			FTask ftsk = { -1, fnc };
			mFuncTask[i].push_back(ftsk);

			STask stsk = { -1 };
			mSwitchTask[i].push_back(stsk);

			JTask jtsk = { -1 };
			mJumpTask[i].push_back(jtsk);
		}
	}

	updateImg();
	updateColor();
	//updateFunc();
}

void Novel::updateColor() {
	if (mColorTask[mBranch][mColorNum[mBranch]].num == mNovelNum[mBranch]) {
		//for (int i = 0; i < 3; i++)mLabel[i]->setColor(mColorTask[0].color);
		auto label = (Label*)this->getChildByName("label");
		label->setTextColor((Color4B)mColorTask[mBranch][mColorNum[mBranch]].color);
		//mColorTask[mBranch].erase(mColorTask[mBranch].begin());
		mColorNum[mBranch]++;
	}
}

void Novel::updateFunc() {
	if (mFuncTask[mBranch][mFuncNum[mBranch]].num == mNovelNum[mBranch]) {
		this->runAction(mFuncTask[mBranch][mFuncNum[mBranch]].func);
		//mFuncTask[mBranch].erase(mFuncTask[mBranch].begin());
		mFuncNum[mBranch]++;
	}
}

void Novel::updateSwitch() {
	if (mSwitchTask[mBranch][mSwitchNum[mBranch]].num == mNovelNum[mBranch]) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mSwitch = true;

		if (mSwitchTask[mBranch][mSwitchNum[mBranch]].branchStr[0] == "") {	//ルート変更のみ
			mCurrentSTask = mSwitchTask[mBranch][mSwitchNum[mBranch]];
			int branchTo = mSwitchTask[mBranch][mSwitchNum[mBranch]].branchTo[0];
			auto fake = Layer::create();
			fake->setPosition(visibleSize / 2);
			fake->setSwallowsTouches(true);
			this->addChild(fake, 10, "fakeLayer");

			auto listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				return true;
			};
			listener->onTouchEnded = [this, branchTo](Touch* touch, Event* event) {
				mBranch = mCurrentSTask.branchTo[branchTo];
				auto label = (Label*)this->getChildByName("label");
				mNovelNum[mBranch]++;
				label->setString(mSentense[mBranch][mNovelNum[mBranch]]);
				setDelayAnime();
				this->removeChildByName("fakeLayer");
				mSwitch = false;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, fake);
		}
		else {
			int bNum; //選択肢の数
			for (bNum = 0; mSwitchTask[mBranch][mSwitchNum[mBranch]].branchTo[bNum] != -1; bNum++);

			std::stringstream name;
			for (int i = 0; i < bNum; i++) {
				auto box = Sprite::create("ele_mini1.png");
				box->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (300 / (bNum + 1) * (i + 1)));
				box->setOpacity(0.00f);
				box->runAction(FadeIn::create(0.5));
				name.clear(); name.str("");
				name << "branch" << i;
				addChild(box, 3, name.str());
				auto text = Label::createWithTTF(mSwitchTask[mBranch][mSwitchNum[mBranch]].branchStr[i], FONT_NAME, 24);
				text->setPosition(box->getPosition());
				text->setTextColor(Color4B::BLACK);
				text->enableOutline(Color4B::WHITE, 2);
				text->setOpacity(0.00f);
				text->runAction(FadeIn::create(0.5));
				name.clear(); name.str("");
				name << "text" << i;
				addChild(text, 4, name.str());
				mCurrentSTask = mSwitchTask[mBranch][mSwitchNum[mBranch]];
				auto listener = EventListenerTouchOneByOne::create();
				listener->setSwallowTouches(true);
				listener->onTouchBegan = [this, i, bNum](Touch* touch, Event* event) {
					if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
						//log("switch : %d", i);
						mSwitch = false;  
						mBranch = mCurrentSTask.branchTo[i];
						std::stringstream name;
						for (int j = 0; j < bNum; j++) {
							name << "branch" << j;
							getChildByName(name.str())->runAction(Sequence::createWithTwoActions(FadeOut::create(0.3f), RemoveSelf::create()));
							name.clear(); name.str("");
							name << "text" << j;
							getChildByName(name.str())->runAction(Sequence::createWithTwoActions(FadeOut::create(0.3f), RemoveSelf::create()));
							name.clear(); name.str("");
						}
						auto label = (Label*)this->getChildByName("label");
						mNovelNum[mBranch]++;
						label->setString(mSentense[mBranch][mNovelNum[mBranch]]);
						setDelayAnime();
						AudioEngine::play2d("SE/choice.ogg");

						return true;
					}
					return false;
				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, box);
			}
		}

		//mSwitchTask[mBranch].erase(mSwitchTask[mBranch].begin());
		mSwitchNum[mBranch]++;
	}	
}

void Novel::updateJump() {
	if (mJumpTask[mBranch][mJumpNum[mBranch]].num == mNovelNum[mBranch]) {
		int branch = mJumpTask[mBranch][mJumpNum[mBranch]].branch;
		mNovelNum[branch] = mJumpTask[mBranch][mJumpNum[mBranch]].novelNum;
		mBranch =  branch;
		
		//タスクの位置も戻す
		int i = 0;
		for (auto tsk : mTask[mBranch]) {
			if (tsk.num >= mNovelNum[mBranch]) {
				mTaskNum[mBranch] = i;
				break;
			}
			i++;
		}
		i = 0;
		for (auto tsk : mColorTask[mBranch]) {
			if (tsk.num >= mNovelNum[mBranch]) {
				mColorNum[mBranch] = i;
				break;
			}
			i++;
		}
		i = 0;
		for (auto tsk : mFuncTask[mBranch]) {
			if (tsk.num >= mNovelNum[mBranch]) {
				mFuncNum[mBranch] = i;
				break;
			}
			i++;
		}
		i = 0;
		for (auto tsk : mSwitchTask[mBranch]) {
			if (tsk.num >= mNovelNum[mBranch]) {
				mSwitchNum[mBranch] = i;
				break;
			}
			i++;
		}
		i = 0;
		for (auto tsk : mJumpTask[mBranch]) {
			if (tsk.num >= mNovelNum[mBranch]) {
				mJumpNum[mBranch] = i;
				break;
			}
			i++;
		}

		//メインルート以外は全部初期化
		for (i = 1; i < MAX_BRANCH; i++) {
			mNovelNum[i] = mTaskNum[i] = mColorNum[i] = mFuncNum[i] = mSwitchNum[i] = mJumpNum[i] = 0;
		}

		//mJumpNum[mBranch]++;
	}
}

void Novel::setFontColor(int branch,cocos2d::Color3B c) {
	CTask tsk = {mNovelSetNum[branch], c};
	mColorTask[branch].push_back(tsk);
}

void Novel::addEvent(int branch,cocos2d::CallFunc* func) {
	func->retain();
	FTask tsk = {mNovelSetNum[branch], func};
	mFuncTask[branch].push_back(tsk);
}

void Novel::addSwitchEvent(int branch, int br1, std::string st1, int br2, std::string st2, int br3, std::string st3, int br4, std::string st4) {
	STask tsk;
	tsk.num = mNovelSetNum[branch];
	tsk.branchTo[0] = br1;
	tsk.branchStr[0] = st1;
	tsk.branchTo[1] = br2;
	tsk.branchStr[1] = st2;
	tsk.branchTo[2] = br3;
	tsk.branchStr[2] = st3;
	tsk.branchTo[3] = br4;
	tsk.branchStr[3] = st4;
	mSwitchTask[branch].push_back(tsk);
}

void Novel::setJump(int branch, int branchTo, int novelNum) {
	JTask tsk = { mNovelSetNum[branch], branchTo,novelNum };
	mJumpTask[branch].push_back(tsk);
	mSentense[branch].push_back("");	//終了しないように
}

bool Novel::endCheck() {
	auto label = (Label*)getChildByName("label");
	for (int i = 0; i < label->getStringLength() + label->getStringNumLines(); i++) {
		auto AChar = label->getLetter(i);
		if (nullptr != AChar) {
			if (AChar->getOpacity() < 255) {
				return false;
			}
		}
	}
	return true;
}

void Novel::setDelayAnime() {
	auto label1 = (Label*)getChildByName("label");
	for (int i = 0; i < label1->getStringLength() + label1->getStringNumLines(); i++) {
		auto AChar = label1->getLetter(i);
		mCharNum = 0;
		if (nullptr != AChar) {
			mCharNum++;
			AChar->setOpacity(0.0f);
			AChar->runAction(
				Sequence::create(
					DelayTime::create(0.05f*i),
					FadeIn::create(0.05f),
					CallFunc::create([this]() {	if (mCharNum % 4 == 0) AudioEngine::play2d("SE/po.ogg"); }),	//全角の最初で鳴らす
					NULL
				));
		}
	}
}

bool Novel::logEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	if (targetBox.containsPoint(touchPoint))
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto layer = Layer::create();
		this->addChild(layer, 5, "layer_l");

		//背景
		Rect rect = Rect(0, 0, visibleSize.width, visibleSize.height);
		Sprite* square = Sprite::create();
		square->setTextureRect(rect);
		square->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		square->setColor(Color3B(0, 0, 0));
		square->setOpacity(128);
		layer->addChild(square, 0, "back_l");
		//auto listener = EventListenerTouchOneByOne::create();
		//listener->setSwallowTouches(true);
		//listener->onTouchBegan = [this](Touch* touch, Event* event) {
		//	mLogScrollX = touch->getLocation().x;
		//	mLogScrollY = touch->getLocation().y;
		//	return true;
		//};
		//listener->onTouchMoved = [this](Touch* touch, Event* event) {
		//	auto label = (Label*)this->getChildByName("layer_l")->getChildByName("label");
		//	auto height = Director::getInstance()->getVisibleSize().height;
		//	label->setPosition(label->getPositionX() + touch->getLocation().x - mLogScrollX, label->getPositionY() + touch->getLocation().y - mLogScrollY);
		//	if (label->getPositionY() > label->getDimensions().height + height) {
		//		label->setPositionY(label->getDimensions().height + height);
		//	}
		//	else if (label->getPositionY() < 0) {
		//		label->setPositionY(0.0f);
		//	}
		//	mLogScrollY = touch->getLocation().y;
		//	if (label->getPositionX() < -label->getDimensions().width) {
		//		label->setPositionX(-label->getDimensions().width);
		//	}
		//	else if (label->getPositionX() > 20) {
		//		label->setPositionX(20.0f);
		//	}
		//	mLogScrollX = touch->getLocation().x;
		//};
		//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, square);


		//文字
		std::stringstream str;
		int lineNum = 0, returnNum = 0;
		for (auto s : mLog) { lineNum++; }
		if (lineNum > 100) {	//100行越えなら最新の100行を表示
			for (int i = 0; i < 100; i++) {
				auto s = mLog[lineNum - 100 + i];
				str << s.asString() << "\n";
			}
		}
		else {
			for (auto s : mLog) {
				str << s.asString() << "\n";
			}
		}

		auto label = Label::createWithTTF(str.str(), FONT_NAME, 24);
		label->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - 20));
		label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		label->setColor(Color3B::WHITE);
		label->setDimensions(visibleSize.width - 20/* * 3*/, visibleSize.height * 8 /*label->getLineHeight() * (label->getStringNumLines() + 1)*/);
		//label->setPositionY(label->getDimensions().height);
		label->setPositionY(visibleSize.height * 7.5);
		//layer->addChild(label, 3, "label");
		auto labelLayer = Layer::create();
		labelLayer->setContentSize(Size(visibleSize.width, visibleSize.height * 5));
		labelLayer->addChild(label, 1, "label");

		//閉じる
		auto close = Sprite::create("log_.png");
		close->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
		close->setOpacity(150.0f);
		close->setPosition(Vec2(visibleSize.width - 15 + origin.x, -15 + origin.y + visibleSize.height));
		layer->addChild(close, 5, "close");
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch* touch, Event* event) { return true; };
		listener->onTouchEnded = [this](Touch* touch, Event* event) {
			auto target = (Sprite*)event->getCurrentTarget();
			Rect targetBox = target->getBoundingBox();
			Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
			if (targetBox.containsPoint(touchPoint))
			{
				this->removeChildByName("layer_l");
			}
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, close);

		auto _scrollView = cocos2d::ui::ScrollView::create();
		_scrollView->setPosition(Vec2::ZERO);
		_scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
		_scrollView->setTouchEnabled(true);
		_scrollView->setBounceEnabled(true);
		layer->addChild(_scrollView, 3, "scroll");
		//スクロールする中身を追加（LayerやSpriteなど）
		_scrollView->addChild(labelLayer, 2, "label");
		//中身のサイズを指定
		_scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height * 8));
		//実際に表示される領域（これ以外は隠れる)
		_scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));
		//_scrollView->setInnerContainerPosition(Vec2(visibleSize.width, visibleSize.height * 5));

		return true;
	}
	return false;
}

void Novel::setLogOnly() { 
	for (auto child : this->getChildren()) {
		if (child->getName() != "log") {
			child->setVisible(false);
		}
	}

	mLogOnly = true;
}