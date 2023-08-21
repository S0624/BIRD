#pragma once
#include <DxLib.h>
#include<tchar.h>
#include "Util/game.h"
#include "Util/Pad.h"
#include "Util/SoundManager.h"

namespace Color
{
	const int kBlack = 0x000000;		// •
	const int kBrown = 0xA52A2A;		// ’ƒ
	const int kRed = 0xff0000;			// Ô
	const int kPeach = 0xff00ff;		// “
	const int kGreen = 0x00ff00;		// —Î
	const int kBlue = 0x0000ff;			// Â
	const int kLightBlue = 0x00ffff;	// …
	const int kYellow = 0xffff00;		// ‰©
	const int kYellowGreen = 0x9ACD32;	// ‰©—Î
	const int kWhite = 0xffffff;		// ”’
}

namespace font
{
	//ƒtƒHƒ“ƒg‚Ì“Ç‚İ‚İ
	void MyFontPath(const TCHAR* path);
};