#include "Mutation.h"


QString Mutation::operator()(QString message)
{
    isOpened_ = !isOpened_;
	message = f_(message, isOpened_);
	if (!isOpened_)
		wasUsed_ = true;
	return message;
}

bool Mutation::open()
{
	return isOpened_;
}

