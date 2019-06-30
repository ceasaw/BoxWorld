#include "AnimationBehavior/AnimationBehavior.h"

AnimationBehavior::AnimationBehavior()
{

}

AnimationBehavior::AnimationBehavior(vector<Animation*>animations) {
	this->animations = animations;
	animationNow = NULL;
}

void AnimationBehavior::addAnimation(Animation* animation) {
	this->animations.push_back(animation);
}

void AnimationBehavior::addAnimation(CString number, int intervalTime, vector<BmpPic*> pictures, BOOL replay)
{
	Animation* a=new Animation;
	a->number = number;
	a->intervalTime = intervalTime;
	a->pictures = pictures;
	a->replay = replay;
	this->animations.push_back(a);
}

void AnimationBehavior::updateAnimation() {
	if (this->getAnimationNow() == NULL) {
		return;
	}
	else {
		double systemTime = GetTickCount();
		Animation* a = this->animationNow;
		if (a->play) {
			if (a->playtime == 0) {
				a->playtime = systemTime;
				a->pictureNow = 0;
			}
			else if (systemTime - a->playtime > a->intervalTime) {
				a->playtime = systemTime;

				a->pictureNow = (a->pictureNow + 1) % a->pictures.size();
				if ((!a->replay) && a->pictureNow == 0) {
					resetAnimation(a->number);
				}
				
			}
		}
	}

}

void AnimationBehavior::resetAnimation(CString animationNo) {
	vector<Animation*>::iterator iter = animations.begin();
	while (iter != animations.end()) {
		Animation* a = *iter;
		if (a->number.Compare(animationNo) == 0) {
			a->playtime = 0;
			a->play = FALSE;
			break;
		}
		iter++;
	}
}

void AnimationBehavior::resetAllAnimation() {
	vector<Animation*>::iterator iter = animations.begin();
	while (iter != animations.end()) {
		Animation* a = *iter;
		a->playtime = 0;
		a->play = FALSE;

		iter++;
	}
}

void AnimationBehavior::enableAnimation(CString animationNo) {

	vector<Animation*>::iterator iter = animations.begin();
	while (iter != animations.end()) {
		Animation* a = *iter;
		if (a->number.Compare(animationNo)==0) {
			animationNow = a;
			a->play = TRUE;
			break;
		}
		iter++;
	}
}

void AnimationBehavior::disableAnimation() {
	this->resetAllAnimation();
}


BmpPic* AnimationBehavior::getCBitmap() {
	if (this->getAnimationNow() != NULL) {
		return animationNow->pictures[animationNow->pictureNow];
	}
	return NULL;
}

Animation* AnimationBehavior::getAnimationNow() {
	if (animationNow != NULL && animationNow->play) {
		return animationNow;
	}
	else {
		return NULL;
	}
}

Animation * AnimationBehavior::getAnimation(CString animationNo)
{
	vector<Animation*>::iterator iter = animations.begin();
	while (iter != animations.end()) {
		Animation* a = *iter;
		if (a->number.Compare(animationNo) == 0) {
			return a;
		}
		iter++;
	}
	return nullptr;
}
