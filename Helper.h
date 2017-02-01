#pragma once
#include <random>
#include <qstring.h>

class Helper
{
public:
	Helper();
	~Helper();
    static QString color();
private: // TODO: staticify
	static std::default_random_engine rng;
	static std::uniform_int_distribution<> rng_; 
};

