#pragma once
#include "StaticObj.h"

class CSnowMan :
	public CStaticObj
{
private:
	CSnowMan();
	~CSnowMan();

public:
	virtual bool Init();

};