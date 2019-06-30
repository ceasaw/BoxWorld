#pragma once
#ifndef _CBULLETATTRIBUTE_H_
#define _CBULLETATTRIBUTE_H_

#include "CItem\CItem.h"

class CBulletAttribute : public CItem {
public:
	CBulletAttribute();
	CBulletAttribute(int gattr);
	int getBulletAttribute();  //获取子弹属性
	void useItem();  //更改子弹属性，更改为attr
};

#endif 