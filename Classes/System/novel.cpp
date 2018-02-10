#pragma  execution_character_set("utf-8")

#include "novel.h"
#include "define.h"

#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

Novel::~Novel() {
	for (int i = 0; i < MAX_BRANCH; i++) {
		if (mTask[i].size() > 1) {
			for (auto tsk : mTask[i]) {
				//if (tsk.func/*->getReferenceCount() > 0*/) 
				//	CC_SAFE_RELEASE_NULL(tsk.func);
				//delete tsk.get();
			}
		}
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
	for (int i = 0; i < 4; i++) mImageNum[i] = 0;
	mSwitch = false;
	mLogOnly = false;

	for (int i = 0; i < MAX_BRANCH; i++) {
		mNovelNum[i] = 0;
		mNovelSetNum[i] = 1;
		mSentense[i].push_back("");
		mName[i].push_back("");
		mTaskNum[i] = 0;
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
		CallFunc::create(CC_CALLBACK_0(Novel::func, this)),
		NULL);
	msg->runAction(seq);
	this->addChild(msg, 2, "msgBox");

	//文字
	auto label = Label::createWithTTF("", FONT_NAME, 24);
	label->setPosition(Vec2(origin.x + 50,
		origin.y + visibleSize.height - 340));
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setColor(Color3B::BLUE);
	label->enableOutline(Color4B::WHITE, 2);
	label->setDimensions(750, 130);
	this->addChild(label, 3, "label");
	//名前
	label = Label::createWithTTF("", FONT_NAME, 20);
	label->setPosition(Vec2(origin.x + 130,
		origin.y + visibleSize.height - 320));
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setColor(Color3B::WHITE);
	label->enableOutline(Color4B::BLACK, 1);
	this->addChild(label, 3, "name");

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
	log->setPosition(Vec2(visibleSize.width - 15 + origin.x, -15 + origin.y + visibleSize.height));
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
	label = (Label*)this->getChildByName("name");
	label->setString(mName[0][mNovelNum[0]]);
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
		mSentense[mBranch].size() > mNovelNum[mBranch] &&
		mNovelNum[mBranch] > 0 /* フェードイン前に押されるのを防ぐ */) {
		readTalk();
		mTouchTime = 1;
	}
	else {
		getChildByName("msgBox")->setVisible(true);
		getChildByName("label")->setVisible(true);
		getChildByName("name")->setVisible(true);
		getChildByName("fast")->setVisible(true);
		mHideMsg = false;
	}

	return true;
}

void Novel::readTalk() {
	auto label = (Label*)this->getChildByName("label");
	auto name = (Label*)this->getChildByName("name");
	if (endCheck()) {	//文がすべて表示されていたら
						//バックログに記録
		if (this->getOpacity() == 255) {
			std::string log = "";
			if (mName[mBranch][mNovelNum[mBranch]] != "")log += mName[mBranch][mNovelNum[mBranch]] + " : ";
			log += mSentense[mBranch][mNovelNum[mBranch]];
			mLog.push_back(Value(log));
		}
		if (mSentense[mBranch].size() - 1 > mNovelNum[mBranch]) {	//文リストの最後でなければ
																	//次の分をセット
			mNovelNum[mBranch]++;
			label->setString(mSentense[mBranch][mNovelNum[mBranch]]);
			name->setString(mName[mBranch][mNovelNum[mBranch]]);
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

void Novel::end() {
	mEndFlag = 1;
}

void Novel::update(float delta) {
	if (mTouchTime > 0) mTouchTime++;
	if (mTouchTime > 60) {
		getChildByName("msgBox")->setVisible(false);
		getChildByName("label")->setVisible(false);
		getChildByName("name")->setVisible(false);
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

	int num = mTaskNum[mBranch];
	while (mTask[mBranch][num].get()->num == mNovelNum[mBranch]) {
		mTask[mBranch][num].get()->update(this);
		num = ++mTaskNum[mBranch];
	}
}

int Novel::addSentence(int branch, std::string name, std::string s) {
	mSentense[branch].push_back(s);
	mName[branch].push_back(name);
	mNovelSetNum[branch]++;
	return mNovelSetNum[branch] - 1;
}

void Novel::ITask::update(Novel* parent) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int num = parent->mTaskNum[parent->mBranch];
	std::stringstream name;
	name.clear(); name.str("");
	auto *tsk = (ITask*)parent->mTask[parent->mBranch][num].get();

	if (tsk->imgPos == IMG_BG) {
		name << "bg" << parent->mImageNum[0];
		auto old = parent->getChildByName(name.str());
		old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));

		parent->mImageNum[0]++;

		name.clear(); name.str("");
		name << "bg" << parent->mImageNum[0];

		if (tsk->imgName != "") {
			auto newOne = Sprite::create(tsk->imgName);
			newOne->setPosition(old->getPosition());
			newOne->setOpacity(0.0f);

			newOne->runAction(FadeIn::create(0.5f));
			parent->addChild(newOne, 0, name.str());
		}
		else {
			auto bg = Sprite::create();
			bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
			parent->addChild(bg, 0, name.str());
		}
	}
	else if (tsk->imgPos == IMG_CENTER) {
		name << "charaC" << parent->mImageNum[1];
		auto old = parent->getChildByName(name.str());
		old->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(true), NULL));

		parent->mImageNum[1]++;

		name.clear(); name.str("");
		name << "charaC" << parent->mImageNum[1];

		if (tsk->imgName != "") {
			auto newOne = Sprite::create(tsk->imgName);
			newOne->setPosition(old->getPosition());
			newOne->setOpacity(0.0f);

			newOne->runAction(FadeIn::create(0.3f));
			parent->addChild(newOne, 1, name.str());
		}
		else {
			auto charaC = Sprite::create();
			charaC->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
			parent->addChild(charaC, 1, name.str());
		}
	}
	else if (tsk->imgPos == IMG_LEFT) {
		name << "charaL" << parent->mImageNum[2];
		auto old = parent->getChildByName(name.str());
		old->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(true), NULL));

		parent->mImageNum[2]++;

		name.clear(); name.str("");
		name << "charaL" << parent->mImageNum[2];

		if (tsk->imgName != "") {
			auto newOne = Sprite::create(tsk->imgName);
			newOne->setPosition(old->getPosition());
			newOne->setOpacity(0.0f);

			newOne->runAction(FadeIn::create(0.3f));
			parent->addChild(newOne, 1, name.str());
		}
		else {
			auto charaL = Sprite::create();
			charaL->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
			parent->addChild(charaL, 1, name.str());
		}
	}
	else if (tsk->imgPos == IMG_RIGHT) {
		name << "charaR" << parent->mImageNum[3];
		auto old = parent->getChildByName(name.str());
		old->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(true), NULL));

		parent->mImageNum[3]++;

		name.clear(); name.str("");
		name << "charaR" << parent->mImageNum[3];

		if (tsk->imgName != "") {
			auto newOne = Sprite::create(tsk->imgName);
			newOne->setPosition(old->getPosition());
			newOne->setOpacity(0.0f);

			newOne->runAction(FadeIn::create(0.3f));
			parent->addChild(newOne, 1, name.str());
		}
		else {
			auto charaR = Sprite::create();
			charaR->setPosition(Vec2(visibleSize.width * 3 / 4 + origin.x, visibleSize.height / 2 + origin.y));
			parent->addChild(charaR, 1, name.str());
		}
	}

}

bool Novel::getEndFlag() { return mEndFlag; }

void Novel::setBg(int branch, std::string s) {
	ITask* tsk = new ITask();
	tsk->num = mNovelSetNum[branch];
	tsk->imgPos = IMG_BG;
	tsk->imgName = s;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
}

void Novel::setCharaC(int branch, std::string s) {
	ITask* tsk = new ITask();
	tsk->num = mNovelSetNum[branch];
	tsk->imgPos = IMG_CENTER;
	tsk->imgName = s;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
}

void Novel::setCharaL(int branch, std::string s) {
	ITask* tsk = new ITask();
	tsk->num = mNovelSetNum[branch];
	tsk->imgPos = IMG_LEFT;
	tsk->imgName = s;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
}

void Novel::setCharaR(int branch, std::string s) {
	ITask* tsk = new ITask();
	tsk->num = mNovelSetNum[branch];
	tsk->imgPos = IMG_RIGHT;
	tsk->imgName = s;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
}

void Novel::setEndTask(int branch) {
	if (branch > 0) {
		auto tsk = new Task();
		tsk->num = -1;
		mTask[branch].push_back((std::shared_ptr<Task>)tsk);

	}
	else {	//-の場合はまとめて入れる
		for (int i = 0; i < MAX_BRANCH; i++) {
			auto tsk = new Task();//{ -1,IMG_NONE,"" };
			tsk->num = -1;
			mTask[i].push_back((std::shared_ptr<Task>)tsk);
		}
	}

	std::stringstream name;
	while (mTask[mBranch][mTaskNum[mBranch]].get()->num == mNovelNum[mBranch]) {
		mTask[mBranch][mTaskNum[mBranch]].get()->update(this);
		mTaskNum[mBranch]++;
	}
}

void Novel::CTask::update(Novel* parent) {
	auto label = (Label*)parent->getChildByName("label");
	auto name = (Label*)parent->getChildByName("name");
	auto tsk = (CTask*)parent->mTask[parent->mBranch][parent->mTaskNum[parent->mBranch]].get();
	label->setTextColor((Color4B)tsk->color);
	name->enableOutline((Color4B)tsk->color, 1);
}

void Novel::FTask::update(Novel* parent) {
	parent->runAction(((FTask*)parent->mTask[parent->mBranch][parent->mTaskNum[parent->mBranch]].get())->func);
}
Novel::FTask::~FTask() {
	CC_SAFE_RELEASE_NULL(func);
}

void Novel::STask::update(Novel* parent) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	parent->mSwitch = true;

	auto tsk = (STask*)parent->mTask[parent->mBranch][parent->mTaskNum[parent->mBranch]].get();
	if (tsk->branchStr[0] == "") {	//ルート変更のみ
		parent->mCurrentSTask = new STask();
		parent->mCurrentSTask->num = tsk->num;
		parent->mCurrentSTask->branchTo[0] = tsk->branchTo[0];
		parent->mCurrentSTask->branchStr[0] = tsk->branchStr[0];
		int branchTo = tsk->branchTo[0];
		auto fake = Layer::create();
		fake->setPosition(visibleSize / 2);
		fake->setSwallowsTouches(true);
		parent->addChild(fake, 10, "fakeLayer");

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			return true;
		};
		listener->onTouchEnded = [this, branchTo, parent](Touch* touch, Event* event) {
			parent->mBranch = parent->mCurrentSTask->branchTo[branchTo];
			auto label = (Label*)parent->getChildByName("label");
			auto name = (Label*)parent->getChildByName("name");
			parent->mNovelNum[parent->mBranch]++;
			label->setString(parent->mSentense[parent->mBranch][parent->mNovelNum[parent->mBranch]]);
			name->setString(parent->mName[parent->mBranch][parent->mNovelNum[parent->mBranch]]);
			parent->setDelayAnime();
			parent->removeChildByName("fakeLayer");
			parent->mSwitch = false;
		};
		parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, fake);
	}
	else {
		int bNum; //選択肢の数
		for (bNum = 0; tsk->branchTo[bNum] != -1; bNum++);

		std::stringstream name;
		for (int i = 0; i < bNum; i++) {
			auto box = Sprite::create("ele_mini1.png");
			box->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - (300 / (bNum + 1) * (i + 1)));
			box->setOpacity(0.00f);
			box->runAction(FadeIn::create(0.5));
			name.clear(); name.str("");
			name << "branch" << i;
			parent->addChild(box, 3, name.str());
			auto text = Label::createWithTTF(tsk->branchStr[i], FONT_NAME, 24);
			text->setPosition(box->getPosition());
			text->setTextColor(Color4B::BLACK);
			text->enableOutline(Color4B::WHITE, 2);
			text->setOpacity(0.00f);
			text->runAction(FadeIn::create(0.5));
			name.clear(); name.str("");
			name << "text" << i;
			parent->addChild(text, 4, name.str());
			parent->mCurrentSTask = new STask();
			parent->mCurrentSTask->num = tsk->num;
			for (int i_ = 0; i_ < bNum; i_++) {
				parent->mCurrentSTask->branchTo[i_] = tsk->branchTo[i_];
				parent->mCurrentSTask->branchStr[i_] = tsk->branchStr[i_];
			}
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this, i, bNum, parent](Touch* touch, Event* event) {
				if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
					//log("switch : %d", i);
					parent->mSwitch = false;
					parent->mBranch = parent->mCurrentSTask->branchTo[i];
					std::stringstream name;
					for (int j = 0; j < bNum; j++) {
						name << "branch" << j;
						parent->getChildByName(name.str())->runAction(Sequence::createWithTwoActions(FadeOut::create(0.3f), RemoveSelf::create()));
						name.clear(); name.str("");
						name << "text" << j;
						parent->getChildByName(name.str())->runAction(Sequence::createWithTwoActions(FadeOut::create(0.3f), RemoveSelf::create()));
						name.clear(); name.str("");
					}
					auto label = (Label*)parent->getChildByName("label");
					auto nlabel = (Label*)parent->getChildByName("name");
					parent->mNovelNum[parent->mBranch]++;
					label->setString(parent->mSentense[parent->mBranch][parent->mNovelNum[parent->mBranch]]);
					nlabel->setString(parent->mName[parent->mBranch][parent->mNovelNum[parent->mBranch]]);
					parent->setDelayAnime();
					AudioEngine::play2d("SE/choice.ogg");

					return true;
				}
				return false;
			};
			parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, box);
		}
	}
}

void Novel::JTask::update(Novel* parent) {
	auto tsk = (JTask*)parent->mTask[parent->mBranch][parent->mTaskNum[parent->mBranch]].get();

	int branch = tsk->branch;
	parent->mNovelNum[branch] = tsk->novelNum;
	parent->mBranch = branch;

	//タスクの位置も戻す
	int i = 0;
	for (auto tsk : parent->mTask[parent->mBranch]) {
		if (tsk->num >= parent->mNovelNum[parent->mBranch]) {
			parent->mTaskNum[parent->mBranch] = i - 1;	// updateでnum=0になるため-1
			break;
		}
		i++;
	}

	//メインルート以外は全部初期化
	for (i = 1; i < MAX_BRANCH; i++) {
		parent->mNovelNum[i] = parent->mTaskNum[i] = 0;
	}

}

void Novel::setFontColor(int branch, cocos2d::Color3B c) {
	auto tsk = new CTask(); 
	tsk->num = mNovelSetNum[branch];
	tsk->color = c;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
}

void Novel::addEvent(int branch, cocos2d::CallFunc* func) {
	func->retain();
	auto tsk = new FTask();
	tsk->num = mNovelSetNum[branch];
	tsk->func = func;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
}

void Novel::addSwitchEvent(int branch, int br1, std::string st1, int br2, std::string st2, int br3, std::string st3, int br4, std::string st4) {
	auto tsk = new STask();
	tsk->num = mNovelSetNum[branch];
	tsk->branchTo[0] = br1;
	tsk->branchStr[0] = st1;
	tsk->branchTo[1] = br2;
	tsk->branchStr[1] = st2;
	tsk->branchTo[2] = br3;
	tsk->branchStr[2] = st3;
	tsk->branchTo[3] = br4;
	tsk->branchStr[3] = st4;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
}

void Novel::setJump(int branch, int branchTo, int novelNum) {
	auto tsk = new JTask();
	tsk->num = mNovelSetNum[branch];
	tsk->branch = branchTo;
	tsk->novelNum = novelNum;
	mTask[branch].push_back((std::shared_ptr<Task>)tsk);
	mSentense[branch].push_back("");	//終了しないように
	mName[branch].push_back("");	//終了しないように
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