#include "XActor.h"
#include "XEngine.h"

XActor::XActor(const std::wstring& name)
	:XObject(name)
{
	obj_type_ = XEngineObjectType::XACTOR;
}

XActor::~XActor()
{

}

