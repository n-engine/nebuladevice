/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __MENUPARTSPARTS_H__
#define __MENUPARTSPARTS_H__

#include <string>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// メニューコントロールの種類

enum MenuCtrlType {
	MenuCtrlTypeLabel,
	MenuCtrlTypeLabelFloat,
	MenuCtrlTypeLabelInteger,
	MenuCtrlTypeLabelBool,
	MenuCtrlTypeSpinFloat,
	MenuCtrlTypeSpinInteger,
	MenuCtrlTypeSpinBool,
	MenuCtrlTypeItemList,
};

///////////////////////////////////////////////////////////////////////////////
// コールバッククラス

class MenuCtrlBase;
class MenuCtrlCallback {
public:
	virtual ~MenuCtrlCallback() {}
	virtual void onMenuCtrlChange(MenuCtrlBase *ctrl) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// メニューコントロールのベースクラス

class MenuCtrlBase {
protected:
	string label;
	MenuCtrlType type;
	bool changable;
	MenuCtrlCallback *callback;
	float color[3];

public:

	MenuCtrlBase(const char *l,MenuCtrlType t,bool chg,MenuCtrlCallback *cb = NULL)
		: label(l),type(t),changable(chg),callback(cb)
	{
		setColor(0.0f,1.0f,0.0f);
	}
	
	virtual ~MenuCtrlBase() {}

	const char *getLabel() {return label.c_str();}

	MenuCtrlType getType() {return type;}

	float getColorR() {return color[0];}
	float getColorG() {return color[1];}
	float getColorB() {return color[2];}
	void setColor(float r,float g,float b) {color[0]=r;color[1]=g;color[2]=b;}

	bool isChangable() {return changable;}
	
	virtual void increaseValue() = 0;
	virtual void decreaseValue() = 0;
};

///////////////////////////////////////////////////////////////////////////////
// メニューコントロールの型

class MenuCtrlFloat : public MenuCtrlBase {
public:
	float cur;
	float rangeMin,rangeMax;
	float diff;

	MenuCtrlFloat(const char *l,MenuCtrlType t,bool chg,float c,float rmin,float rmax,float d,MenuCtrlCallback *cb = NULL)
		: MenuCtrlBase(l,t,chg,cb),cur(c),rangeMin(rmin),rangeMax(rmax),diff(d)
	{
	}
	
	virtual ~MenuCtrlFloat() {}

	virtual void increaseValue()
	{
		if(cur < rangeMax) {
			cur += diff;
			if(cur > rangeMax) {
				cur = rangeMax;
			}
			if(callback) callback->onMenuCtrlChange(this);
		}
	}
	
	virtual void decreaseValue()
	{
		if(cur > rangeMin) {
			cur -= diff;
			if(cur < rangeMin) {
				cur = rangeMin;
			}
			if(callback) callback->onMenuCtrlChange(this);
		}
	}
	
	virtual float getValue() {return cur;}
	virtual void  setValue(float v)
	{
		if(v >= rangeMin && v <= rangeMax) {
			cur = v;
		}
	}
};

class MenuCtrlInteger : public MenuCtrlBase {
public:
	long cur;
	long rangeMin,rangeMax;
	long diff;

	MenuCtrlInteger(const char *l,MenuCtrlType t,bool chg,int c,int rmin,int rmax,int d,MenuCtrlCallback *cb = NULL)
		: MenuCtrlBase(l,t,chg,cb),cur(c),rangeMin(rmin),rangeMax(rmax),diff(d)
	{
	}

	virtual ~MenuCtrlInteger() {}

	virtual void increaseValue()
	{
		cur += diff;
		if(cur > rangeMax) {
			cur = rangeMin;
		}
		if(callback) callback->onMenuCtrlChange(this);
	}
	
	virtual void decreaseValue()
	{
		cur -= diff;
		if(cur < rangeMin) {
			cur = rangeMax;
		}
		if(callback) callback->onMenuCtrlChange(this);
	}
	
	virtual int getValue() {return cur;}
	virtual void  setValue(int v)
	{
		if(v >= rangeMin && v <= rangeMax) {
			cur = v;
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
// メニューコントロール

class MenuCtrlLabel : public MenuCtrlInteger
{
public:
	MenuCtrlLabel(const char *l)
		: MenuCtrlInteger(l,MenuCtrlTypeLabel,false,0,0,0,0)
	{
	}
	
	void increaseValue() {}
	void decreaseValue() {}
};

class MenuCtrlLabelFloat : public MenuCtrlFloat
{
public:
	MenuCtrlLabelFloat(const char *l,float c)
		: MenuCtrlFloat(l,MenuCtrlTypeLabelFloat,false,c,0.0f,0.0f,0.0f)
	{
	}

	void increaseValue() {}
	void decreaseValue() {}
};

class MenuCtrlLabelInteger : public MenuCtrlInteger
{
public:
	MenuCtrlLabelInteger(const char *l,int c)
		: MenuCtrlInteger(l,MenuCtrlTypeLabelInteger,false,c,0,0,0)
	{
	}

	void increaseValue() {}
	void decreaseValue() {}
};

class MenuCtrlLabelBool : public MenuCtrlInteger
{
public:
	MenuCtrlLabelBool(const char *l,bool c)
		: MenuCtrlInteger(l,MenuCtrlTypeLabelBool,false,c,0,0,0)
	{
	}

	void increaseValue() {}
	void decreaseValue() {}
};

class MenuCtrlSpinFloat : public MenuCtrlFloat
{
public:
	MenuCtrlSpinFloat(const char *l,float c,float rmin,float rmax,float d,MenuCtrlCallback *cb = NULL)
		: MenuCtrlFloat(l,MenuCtrlTypeSpinFloat,true,c,rmin,rmax,d,cb)
	{
	}
};

class MenuCtrlSpinInteger : public MenuCtrlInteger
{
public:
	MenuCtrlSpinInteger(const char *l,int c,int rmin,int rmax,int d,MenuCtrlCallback *cb = NULL)
		: MenuCtrlInteger(l,MenuCtrlTypeSpinInteger,true,c,rmin,rmax,d,cb)
	{
	}
};

class MenuCtrlSpinBool : public MenuCtrlInteger
{
public:
	MenuCtrlSpinBool(const char *l,bool c,MenuCtrlCallback *cb = NULL)
		: MenuCtrlInteger(l,MenuCtrlTypeSpinBool,true,c,0,1,1,cb)
	{
	}
};

class MenuCtrlItemList : public MenuCtrlInteger
{
private:
	vector<string> itemList;

public:
	MenuCtrlItemList(const char *l,int c,int rmin,int rmax,int d,MenuCtrlCallback *cb = NULL)
		: MenuCtrlInteger(l,MenuCtrlTypeItemList,true,c,rmin,rmax,d,cb)
	{
		string tmp;
		itemList.assign(rmax+1-rmin,tmp);
	}

	void addItem(int idx,const char *itemName)
	{
		itemList[idx-rangeMin] = itemName;
	}

	const char *getItem()
	{
		return itemList[getValue()-rangeMin].c_str();
	}
};

#endif // __MENUPARTSPARTS_H__
