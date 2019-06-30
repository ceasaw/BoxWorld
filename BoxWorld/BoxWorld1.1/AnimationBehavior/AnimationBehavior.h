#pragma once
#ifndef _CANIMATIONBEHAVIOR_H_
#define _CANIMATIONBEHAVIOR_H_

#include <afxwin.h>
#include <vector>
#include "BasicTools/BasicTools.h"

using namespace std;

struct Animation{
	CString number;           //�������
	int intervalTime;         //�������ŵļ��ʱ��
	vector<BmpPic*> pictures;//������������ͼ����˳��ţ�
	BOOL replay = FALSE;     //�Ƿ�ѭ������
	BOOL play = FALSE;        //�Ƿ񲥷�
	double playtime = 0;      //��ǰ����ʱ��
	int pictureNow = 0;       //���Ŷ��������У���ǰ����ͼ
};

class AnimationBehavior {
	
private:

	vector<Animation*> animations;
	Animation* animationNow;
	
	
public:
	AnimationBehavior();

	//��ʼ��
	AnimationBehavior(vector<Animation*>animations);

	//��Ӷ���
	void addAnimation(Animation* animation);

	//��Ӷ���
	void addAnimation(CString number, int intervalTime,vector<BmpPic*> pictures,BOOL replay);

	//���½ӿ�
	void updateAnimation();
	
	//��һ��������Ϊ�����ţ�����ʱ��
	void resetAnimation(CString animationNo);

	//�������ж���
	void resetAllAnimation();

	//����һ������
	void enableAnimation(CString animationNo);

	//��ʹ�ö���
	void disableAnimation();

	//��ȡ��ǰ�����ĵ�ǰ֡�������򷵻�NULL
	BmpPic* getCBitmap();

	//ʹ�ô���ʱ��Ҫ��д����࣬Ϊ��ͼ�����ṩ��ǰ��ͼ
	virtual PicPos* getPicAndPos() = 0 ;

	//��ȡ��ǰ���Ŷ����������򷵻�NULL
	Animation* getAnimationNow();

	//��ȡĳһ����
	Animation* getAnimation(CString number);

};

#endif