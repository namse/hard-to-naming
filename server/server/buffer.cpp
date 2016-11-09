#include "stdafx.h"
#include "buffer.h"

bool Buffer::Shift()
{
	if (Begin() == buffer_) {
		return false;
	}
	memcpy(buffer_, Begin(), ReadableLength());
	return true;
}
