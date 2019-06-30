#pragma once
#ifndef _CANIMATIONBEHAVIOR_H_
#define _CANIMATIONBEHAVIOR_H_

#include <afxwin.h>
#include <vector>
#include "BasicTools/BasicTools.h"

using namespace std;

struct Animation{
	CString number;           //动画编号
	int intervalTime;         //动画播放的间隔时间
	vector<BmpPic*> pictures;//动画的所有贴图（按顺序放）
	BOOL replay = FALSE;     //是否循环播放
	BOOL play = FALSE;        //是否播放
	double playtime = 0;      //当前播放时间
	int pictureNow = 0;       //播放动画过程中，当前的贴图
};

class AnimationBehavior {
	
private:

	vector<Animation*> animations;
	Animation* animationNow;
	
	
public:
	AnimationBehavior();

	//初始化
	AnimationBehavior(vector<Animation*>animations);

	//添加动画
	void addAnimation(Animation* animation);

	//添加动画
	void addAnimation(CString number, int intervalTime,vector<BmpPic*> pictures,BOOL replay);

	//更新接口
	void updateAnimation();
	
	//将一个动画设为不播放，重置时间
	void resetAnimation(CString animationNo);

	//重设所有动画
	void resetAllAnimation();

	//启动一个动画
	void enableAnimation(CString animationNo);

	//不使用动画
	void disableAnimation();

	//获取当前动画的当前帧，若无则返回NULL
	BmpPic* getCBitmap();

	//使用此类时需要重写这个类，为贴图函数提供当前贴图
	virtual PicPos* getPicAndPos() = 0 ;

	//获取当前播放动画，若无则返回NULL
	Animation* getAnimationNow();

	//获取某一动画
	Animation* getAnimation(CString number);

};

#endif