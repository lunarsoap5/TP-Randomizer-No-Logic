#include "defines.h"
#include "tools.h"
#include "global.h"

#include <tp/evt_control.h>
#include <tp/d_com_inf_game.h>
#include <tp/JFWSystem.h>
#include <cstring>
#include <cstdio>

namespace mod::tools
{
	u64 randomSeed = 0x9e3779b97f4a7c15;

	u32 getRandom(u32 max)
	{
		u64 z = (randomSeed += 0x9e3779b97f4a7c15);
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;

		return (z % max);
	}

	void triggerRandomGenerator()
	{
		// This function runs when the user starts a new file (intro cs is running)
		// We do it the dirty way and store the seed behind Epona's name (hehe xd)
		// With 1.0 this will change anyway so I really don't care and it improves QoL for players!

		*global::seedInSaveFile =  tools::randomSeed;
		global::chestRandoPtr->generate();
	}

	void triggerSaveLoad(char* stage, u8 room, u8 spawn, u8 state, u8 event)
	{
		strcpy(gameInfo.nextStageVars.nextStage, stage);
		gameInfo.nextStageVars.nextRoom = room;
		gameInfo.nextStageVars.nextSpawnPoint = spawn;
		gameInfo.nextStageVars.nextState = state;

		gameInfo.eventSystem.nextEventID = event;
		gameInfo.respawnValues.respawnAnimation = 0;
		gameInfo.nextStageVars.isVoidorWarp = 0;
		gameInfo.respawnValues.respawnCutscene = 0;
		gameInfo.eventSystem.immediateControl = 0xFFFF;
		gameInfo.nextStageVars.fadeType = 0x13;

		gameInfo.nextStageVars.triggerLoad = true;
	}

	void setCutscene(bool skippable, bool fade, tp::evt_control::csFunc onSkip)
	{
		gameInfo.eventSystem.fadeOnSkip = fade;
		if(skippable)
		{
			gameInfo.eventSystem.onSkip = onSkip;
		}
		else
		{
			gameInfo.eventSystem.onSkip = nullptr;
		}
	}

	float fCompare(const float f1, const float f2)
	{
		if(f1 > f2)
		{
			return (f1 - f2);
		}
		else
		{
			return (f2 - f1);
		}
	}
	
	u16 fletcher16(u8* data, s32 count)
	{
		u16 sum1 = 0;
		u16 sum2 = 0;

		for(s32 index = 0; index < count; ++index )
		{
			sum1 = (sum1 + data[index]) % 0xFF;
			sum2 = (sum2 + sum1) % 0xFF;
		}

		return (sum2 << 8) | sum1;
	}

	void setItemFlag(ItemFlags flag)
	{
		u32 flagsPerVar = sizeof(u32) * 8;
		u32 tempFlagVar = static_cast<u32>(flag);

		u32* tempItemFlagsArray = gameInfo.scratchPad.itemFlags;
		tempItemFlagsArray[tempFlagVar / flagsPerVar] |= 1 << (tempFlagVar % flagsPerVar);
	}

	void clearItemFlag(ItemFlags flag)
	{
		u32 flagsPerVar = sizeof(u32) * 8;
		u32 tempFlagVar = static_cast<u32>(flag);

		u32* tempItemFlagsArray = gameInfo.scratchPad.itemFlags;
		tempItemFlagsArray[tempFlagVar / flagsPerVar] &= ~(1 << (tempFlagVar % flagsPerVar));
	}

	bool checkItemFlag(ItemFlags flag)
	{
		u32 flagsPerVar = sizeof(u32) * 8;
		u32 tempFlagVar = static_cast<u32>(flag);

		u32* tempItemFlagsArray = gameInfo.scratchPad.itemFlags;
		return tempItemFlagsArray[tempFlagVar / flagsPerVar] & (1 << (tempFlagVar % flagsPerVar));
	}

	void fillArrayIncrement(u8* array, u32 numItems, u8 incrementAmount)
	{
		u8 val = 0;
		for (u32 i = 0; i < numItems; i++)
		{
			array[i] = val;
			val += incrementAmount;
		}
	}

	void shuffleByteArray(u8* array, u32 numItems) // Fisher�Yates shuffle
	{
		for (s32 i = numItems - 1; i > 0; i--)
		{
			// Get a random index
			u32 tempIndex = getRandom(numItems) % (i + 1);

			// Swap array[i] with array[tempIndex]
			u8 tempByte = array[i];
			array[i] = array[tempIndex];
			array[tempIndex] = tempByte;
		}
	}
}