#pragma once
#ifndef _CITEM_H_
#define _CITEM_H_

enum { metal = 1, wood, water, fire, earth };

class CItem {
protected:
	int bloodValue;   //Ѫƿ�ظ���Ѫ��
	int attr;     //�ӵ�����
public:
	CItem();
	virtual void useItem()
	{

	}
};

#endif 