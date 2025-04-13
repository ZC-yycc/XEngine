#pragma once
#include "XActor.h"
class Plane : public XActor
{
public:
	Plane( const std::wstring &name);
	virtual ~Plane();

	void withholdBlood(const float& val);
protected:
	float		fSpeed_;
	float		fHP_;
	float		fDamage_;
};

