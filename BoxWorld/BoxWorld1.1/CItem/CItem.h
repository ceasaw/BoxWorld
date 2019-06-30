#pragma once
#ifndef _CITEM_H_
#define _CITEM_H_

enum { metal = 1, wood, water, fire, earth };

class CItem {
protected:
	int bloodValue;   //血瓶回复的血量
	int attr;     //子弹属性
public:
	CItem();
	virtual void useItem()
	{

	}
};

#endif 