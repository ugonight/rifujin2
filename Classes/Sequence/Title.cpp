#include "Title.h"
#include "Prologue.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

Scene* Title::createScene()
{
    auto scene = Scene::create();
    auto layer = Title::create();
    scene->addChild(layer);
    return scene;
}

bool Title::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Title::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto sprite = Sprite::create("title/title.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (Rect(270,150,290,80).containsPoint(touch->getLocationInView())) {
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Prologue::createScene(), Color3B::WHITE));
		}
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
	//BGM
	AudioEngine::preload("BGM/days.ogg");

	//SE
	AudioEngine::preload("SE/po.ogg");

    return true;
}


void Title::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
