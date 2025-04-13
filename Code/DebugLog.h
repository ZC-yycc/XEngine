#pragma once
#ifndef DEBUGLOG_H
#define DEBUGLOG_H
#include <iostream>

#if PR_DEBUG
#define XENGINE_LOG(x) std::cout<< x <<std::endl
#else
#define XENGINE_LOG(x)
#endif

#endif 
