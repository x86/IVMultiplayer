//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVPlayerPed.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPlayerPed_h
#define CIVPlayerPed_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVPed.h"

class IVPlayerPed : public IVPed {
public:
};

class CIVPlayerPed : public CIVPed {
public:
	CIVPlayerPed();
	CIVPlayerPed(IVPlayerPed * pPlayerPed);
	~CIVPlayerPed();

	void					SetPlayerPed(IVPlayerPed * pPlayerPed);
	IVPlayerPed				* GetPlayerPed();
};

#endif // CIVPlayerPed_h