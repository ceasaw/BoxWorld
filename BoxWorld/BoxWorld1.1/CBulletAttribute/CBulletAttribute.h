#pragma once
#ifndef _CBULLETATTRIBUTE_H_
#define _CBULLETATTRIBUTE_H_

#include "CItem\CItem.h"

class CBulletAttribute : public CItem {
public:
	CBulletAttribute();
	CBulletAttribute(int gattr);
	int getBulletAttribute();  //��ȡ�ӵ�����
	void useItem();  //�����ӵ����ԣ�����Ϊattr
};

#endif 