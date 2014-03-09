#include "OptionLayer.h"

using namespace cocos2d;

OptionLayer::OptionLayer()
{}

OptionLayer::~OptionLayer()
{}

bool OptionLayer::init()
{
    bool ret = false;

    do {
        CC_BREAK_IF(!Layer::init());

        _joystick = Sprite::create("joystick.png");
        _joystick_bg = Sprite::create("joystick_bg.png");
        this->addChild(_joystick_bg);
        this->addChild(_joystick);

        _inactivityJoystick();

        setTouchEnabled(true);

		EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::TouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(OptionLayer::TouchesMoved, this);		
		listener->onTouchesEnded = CC_CALLBACK_2(OptionLayer::TouchesEnded, this);

		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        ret = true;
    } while(0);

    return ret;
}

//void OptionLayer::ccTouchesBegan(Set *ts, Event *e)	
void OptionLayer::TouchesBegan(const std::vector<Touch*>& ts, Event* event)
{
    Size winSize = Director::getInstance()->getWinSize();
	/*
    SetIterator iter = ts->begin();

    while (iter != ts->end()) {
        Touch *t = (Touch*)(*iter);
		*/
	int iter = 0;
	
    while (iter < ts.size()) {
        Touch *t = (Touch*)ts[iter];		
        Point p = t->getLocation();
        // left�������ز��������С����Ļ��ȵ�һ�룬˵�����ط���������
        if (p.x <= winSize.width / 2) {
            _activityJoystick(p);
        } else {
            // right������������������������������ź�
            _delegator->onAttack();
        }

        iter++;
    }
}

//void OptionLayer::ccTouchesMoved(Set *ts, Event *e)
void OptionLayer::TouchesMoved(const std::vector<Touch*>& ts, Event* event)
{
    Size winSize = Director::getInstance()->getWinSize();
	/*
    SetIterator iter = ts->begin();
    Touch *t = (Touch*)(*iter);
	*/
	Touch *t = (Touch*)ts[0];
    Point start = t->getStartLocation();

    // ����ô��ص���������������ģ�����������������
    if (start.x > winSize.width / 2) {
        return;
    }

    Point p = t->getLocation();
    // ��ȡλ�Ƶ�����ʼ���ƫ������ֱ�߾��룩
    float distance = start.getDistance(p);
    // ��ȡ��ʼ�㵽λ�Ƶ����������λΪ1�����꣩
    Point direction = (p - start).normalize();

    _updateJoystick(direction, distance);
    _delegator->onWalk(direction, distance);
}

//void OptionLayer::ccTouchesEnded(Set *ts, Event *e)
void OptionLayer::TouchesEnded(const std::vector<Touch*>& ts, Event* event)
{
    if (_joystick_bg->isVisible()) {
        _inactivityJoystick();
        _delegator->onStop();
    }
}

void OptionLayer::_activityJoystick(Point position)
{
    _joystick->setPosition(position);
    _joystick_bg->setPosition(position);
    _joystick->setVisible(true);
    _joystick_bg->setVisible(true);
}

void OptionLayer::_inactivityJoystick()
{
    _joystick->setPosition(_joystick_bg->getPosition());
    _joystick->setVisible(false);
    _joystick_bg->setVisible(false);
}

void OptionLayer::_updateJoystick(Point direction, float distance)
{
    // �ԡ�ҡ�˻�������Բ��Ϊ�������ο�����ҡ�ˡ�����Ӧ�ı���
    Point start = _joystick_bg->getPosition();

    if (distance < 32) {
        // ����ƶ�δ������ҡ�˻���������ҡ�ˡ��ڡ���������ƫ��
        _joystick->setPosition(start + (direction * distance));
    } else if (distance > 96) {
        // ����ƶ�������ҡ�˻���������ҡ�ˡ�Բ��ʼ���ڡ���������Ե��ƫ��
        _joystick->setPosition(start + (direction * 64));
    } else {
        // ����ƶ�������ҡ�˻���������ҡ�ˡ���Եʼ���ڡ���������Ե��ƫ��
        _joystick->setPosition(start + (direction * 32));
    }
}
