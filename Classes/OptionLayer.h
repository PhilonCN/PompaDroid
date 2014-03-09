#ifndef Philon_cocos2dx_PompaDroid_OPTIONLAYER_H_
#define Philon_cocos2dx_PompaDroid_OPTIONLAYER_H_
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class OptionDelegate
{
public:
    // �ƶ���directionΪ������distance��������ֱ�߾���
    virtual void onWalk(cocos2d::Point direction, float distance) = 0;
    // ����
    virtual void onAttack() = 0;
    // ֹͣ�ƶ�
    virtual void onStop() = 0;
};

class OptionLayer : public cocos2d::Layer
{
public:
    OptionLayer();
    ~OptionLayer();

    virtual bool init();
    CREATE_FUNC(OptionLayer);

    // ���ص������¼���������
	/*
    void ccTouchesBegan(cocos2d::Set *ts, cocos2d::Event *e);
    void ccTouchesMoved(cocos2d::Set *ts, cocos2d::Event *e);
    void ccTouchesEnded(cocos2d::Set *ts, cocos2d::Event *e);
	*/
	void TouchesBegan(const std::vector<Touch*>&, Event*);
	void TouchesMoved(const std::vector<Touch*>&, Event*);
	void TouchesEnded(const std::vector<Touch*>&, Event*);

    // ί����
    CC_SYNTHESIZE(OptionDelegate*, _delegator, Delegator);

private:
    // ҡ�ˣ���Ϊ��ҡ�ˡ�����ҡ�˻�������������
    cocos2d::Sprite *_joystick;
    cocos2d::Sprite *_joystick_bg;
    // ���ҡ�˾��顱��������������
    void _activityJoystick(cocos2d::Point position);
    // ���ء�ҡ�˾��顱��������ҡ�ˡ����ڡ�ҡ�˻���������
    void _inactivityJoystick();
    // ˢ�¡�ҡ�ˡ�����ڡ�ҡ�˻�������λ�ã����ݴ������ƣ�
    void _updateJoystick(cocos2d::Point direction, float distance);
};

#endif // End of Philon_cocos2dx_PompaDroid_GAMELAYER_H_
