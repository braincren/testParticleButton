#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    auto closeItem = CCMenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           this,
                                             menu_selector(HelloWorld::menuCloseCallback));
    
	closeItem->setPosition(CCPoint(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    CCMenu *menu = CCMenu::create(closeItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1);

    ////////////////////
    
    CCSprite* pSprite = CCSprite::create("IMG1.jpg");
    pSprite->setPosition(ccp(-20 + origin.x, origin.y));
	pSprite->setAnchorPoint(ccp(0, 0));
    this->addChild(pSprite, 0);
    
    CCParticleSystem* m_emitter1 = CCParticleSystemQuad::create("snow.plist");
    m_emitter1->retain();
    CCParticleBatchNode *batch = CCParticleBatchNode::createWithTexture(m_emitter1->getTexture());
    batch->addChild(m_emitter1);
	m_emitter1->setPosition(ccp(240, 700));
    addChild(batch, 10);
	m_emitter1->release();
    
    /////////////////////
    
	CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 255));
	addChild(layer, -10);

	//按钮
	CCSprite* btnSprite = CCSprite::create("btn.png");
	btnSprite->setPosition(CCPoint(200, 250));
	btnSprite->setAnchorPoint(CCPoint(0, 0));
	this->addChild(btnSprite, 1);
	
	CCSprite* starSprite = CCSprite::create("star1.png");
	starSprite->setScale(0.4f);
	this->addChild(starSprite, 10);

	CCParticleSystem* _emitter = particleInit();
	starSprite->setPosition(CCPoint(btnSprite->getPosition().x + btnSprite->getContentSize().height / 2 - 4, btnSprite->getPosition().y));
	

	_emitter->setPosition(CCPoint(btnSprite->getPosition().x + btnSprite->getContentSize().height / 2 - 6, btnSprite->getPosition().y + 3));

	float X = btnSprite->getContentSize().height / 2;
	CCRepeatForever *path = MyPathFun(X+10, btnSprite->getContentSize().height, btnSprite->getContentSize().width - X * 2 /*+ starSprite->getContentSize().width*/);

	starSprite->runAction(path);
	_emitter->runAction((CCRepeatForever *)path->copy());

	//按钮1
	CCSprite *btnSprite1 = CCSprite::create("btn1.png");
	btnSprite1->setPosition(CCPoint(600, 250));
	btnSprite1->setAnchorPoint(CCPoint(0, 0));
	this->addChild(btnSprite1, 10);

	auto path1 = MyPathFun(75, btnSprite1->getContentSize().height, 80);
	auto _emitter1 = particleInit();
	auto starSprite1 = CCSprite::create("star1.png");
	starSprite1->setScale(0.4f);
	this->addChild(starSprite1, 10);

	starSprite1->setPosition(CCPoint(btnSprite1->getPosition().x + btnSprite1->getContentSize().height / 2 - 4, btnSprite1->getPosition().y));
	_emitter1->setPosition(CCPoint(btnSprite1->getPosition().x + btnSprite1->getContentSize().height / 2 - 5, btnSprite1->getPosition().y + 3));

	starSprite1->runAction(path1);
	_emitter1->runAction((CCRepeatForever *)path1->copy());


	//按钮2（矩形）
	auto btnSprite2 = CCSprite::create("btn0.png");
	btnSprite2->setPosition(CCPoint(350, 150));
	btnSprite2->setAnchorPoint(CCPoint(0, 0));
	this->addChild(btnSprite2, 10);

	auto path2 = MyPathFun(0, btnSprite2->getContentSize().height, btnSprite2->getContentSize().width );
	auto _emitter2 = particleInit();
	auto starSprite2 = CCSprite::create("star1.png");
	starSprite2->setScale(0.4f);
	this->addChild(starSprite2, 10);

	starSprite2->setPosition(CCPoint(btnSprite2->getPosition().x  - 2, btnSprite2->getPosition().y));
	_emitter2->setPosition(CCPoint(btnSprite2->getPosition().x  - 2, btnSprite2->getPosition().y + 3));

	starSprite2->runAction(path2);
	_emitter2->runAction((CCRepeatForever *)path2->copy());

	return true;
}

CCParticleSystem* HelloWorld::particleInit(){
	auto _emitter = new CCParticleSystemQuad();
	_emitter->initWithTotalParticles(50);
	addChild(_emitter, 10);
//brainc	_emitter->setTexture(CCDirector::sharedDirector()->getTextureCache()->addImage("point.png"));
    _emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("point.png"));
    
	_emitter->setAnchorPoint(CCPoint(0, 0));
	// duration
	//brainc _emitter->setDuration(CCParticleSystem::DURATION_INFINITY);
    _emitter->setDuration(kCCParticleDurationInfinity);

	// radius mode
	//bainc _emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);
    _emitter->setEmitterMode(kCCParticleModeRadius);
    
	// radius mode: start and end radius in pixels
	_emitter->setStartRadius(4);
	_emitter->setStartRadiusVar(1);
//brainc	_emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
    _emitter->setEndRadius(kCCParticleStartRadiusEqualToEndRadius);
    
	_emitter->setEndRadiusVar(0);

	// radius mode: degrees per second
	_emitter->setRotatePerSecond(100);
	_emitter->setRotatePerSecondVar(0);

	// angle
	_emitter->setAngle(90);
	_emitter->setAngleVar(0);

	// emitter position
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	_emitter->setPosVar(CCPointZero);

	// life of particles
	_emitter->setLife(0.5);
	_emitter->setLifeVar(0);

	// spin of particles
	_emitter->setStartSpin(0);
	_emitter->setStartSpinVar(0);
	_emitter->setEndSpin(0);
	_emitter->setEndSpinVar(0);

	// color of particles
     ccColor4F startColor = {0.0f, 0.8f, 0.9f, 1.0f};
	_emitter->setStartColor(startColor);

	ccColor4F startColorVar= {0, 0, 0, 1.0f};
	_emitter->setStartColorVar(startColorVar);

	ccColor4F endColor= {1.0f, 1.0f, 1.0f, 0.1f};
	_emitter->setEndColor(endColor);

	ccColor4F endColorVar= {0, 0, 0, 0.1f};
	_emitter->setEndColorVar(endColorVar);
//brainc
//	Color4F setStartColor(Color4F(Color4B(50, 50, 50, 50)));
//	Color4F setEndColor(Color4F(Color4B(0, 0, 0, 0)));
 //   Color4F setStartColor(Color4F(Color4B(50, 50, 50, 50)));
  //  Color4F setEndColor(Color4F(Color4B(0, 0, 0, 0)));
	
    // size, in pixels
	_emitter->setStartSize(20);
	_emitter->setStartSizeVar(1);
	_emitter->setEndSize(0);

	// emits per second
	_emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

	// additive
	_emitter->setBlendAdditive(false);

	return _emitter;
}

CCRepeatForever* HelloWorld::MyPathFun(float controlX, float controlY, float w)
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = CCPoint(-controlX, 0);
	bezier1.controlPoint_2 = CCPoint(-controlX, controlY);
	bezier1.endPosition = CCPoint(0, controlY);
	auto bezierBy1 = CCBezierBy::create(0.8f, bezier1);

	auto move1 = CCMoveBy::create(0.8f, CCPoint(w, 0));

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = CCPoint(controlX, 0);
	bezier2.controlPoint_2 = CCPoint(controlX, -controlY);
	bezier2.endPosition = CCPoint(0, -controlY);
	auto bezierBy2 = CCBezierBy::create(0.8f, bezier2);
	auto move2 = CCMoveBy::create(0.8f, CCPoint(-w, 0));
	auto path = CCRepeatForever::create(CCSequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
