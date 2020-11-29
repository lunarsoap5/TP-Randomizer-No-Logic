#include "array.h"
#include "memory.h"

#include <cstring>

namespace mod::array
{
	s32 indexOf(u16 needle, u16* haystack, size_t count)
	{
		for (u32 i = 0; i < count; i++)
		{
			if (haystack[i] == needle)
			{
				return static_cast<s32>(i);
			}
		}
		return -1;
	}

	u8 shuffleDungeonArray[0x9] =
	{
		0x1,
		0x2,
		0x3,
		0x4,
		0x5,
		0x6,
		0x7,
		0x8,
		0x9
	};
}