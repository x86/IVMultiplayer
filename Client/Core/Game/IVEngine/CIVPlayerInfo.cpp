//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
//
// File: CIVPlayerInfo.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPlayerInfo.h"
#include <CCore.h>
extern CCore * g_pCore;

CIVPlayerInfo::CIVPlayerInfo( )
{
	// Mark as not created by us
	m_bCreatedByUs = false;

	// Set the player info
	SetPlayerInfo( NULL );
}

CIVPlayerInfo::CIVPlayerInfo( BYTE bytePlayerNumber )
{
	IVPlayerInfo * pPlayerInfo = (IVPlayerInfo *)CGameFunction::Alloc(sizeof(IVPlayerInfo));

	if( !pPlayerInfo )
		CLogFile::Print( "ERROR: CIVPlayerInfo::CIVPlayerInfo - Alloc fail!" );

	DWORD dwFunc = (g_pCore->GetBase() + 0x87AB70);
	_asm
	{
		mov ecx, pPlayerInfo
		call dwFunc
	}

	pPlayerInfo->m_bytePlayerNumber = bytePlayerNumber;
	*(DWORD *)(pPlayerInfo + 0x15C) = 0;
	*(DWORD *)(pPlayerInfo + 0x15D) = 0;
	*(DWORD *)(pPlayerInfo + 0x15B) = 0;
	*(DWORD *)(pPlayerInfo + 0x137) = 2;

	m_bCreatedByUs = true;
	m_pPlayerInfo = pPlayerInfo;
}

CIVPlayerInfo::CIVPlayerInfo( IVPlayerInfo * pPlayerInfo )
{
	// Mark as not created by us
	m_bCreatedByUs = false;

	// Set the player info
	SetPlayerInfo( pPlayerInfo );
}

CIVPlayerInfo::~CIVPlayerInfo( )
{
	// Set the player info
	SetPlayerInfo( NULL );
}

void CIVPlayerInfo::SetPlayerInfo( IVPlayerInfo * pPlayerInfo )
{
	// Was this created by us?
	if( m_bCreatedByUs )
	{
		IVPlayerInfo * pPlayerInfo = m_pPlayerInfo;
		DWORD dwFunc = (g_pCore->GetBase() + 0x878AF0);
		_asm
		{
			mov ecx, pPlayerInfo
			call dwFunc
		}

		CGameFunction::Free( pPlayerInfo );
	}

	// Copy the player info
	m_pPlayerInfo = pPlayerInfo;
}

IVPlayerInfo * CIVPlayerInfo::GetPlayerInfo( )
{
	return m_pPlayerInfo;
}

void CIVPlayerInfo::SetPlayerNumber( BYTE bytePlayerNumber )
{
	if( m_pPlayerInfo )
		m_pPlayerInfo->m_bytePlayerNumber = bytePlayerNumber;
}

BYTE CIVPlayerInfo::GetPlayerNumber( )
{
	if( m_pPlayerInfo )
		return m_pPlayerInfo->m_bytePlayerNumber;

	return INVALID_PLAYER_PED;
}

void CIVPlayerInfo::SetPlayerPed( IVPlayerPed * pPlayerPed )
{
	if( m_pPlayerInfo )
		m_pPlayerInfo->m_pPlayerPed = pPlayerPed;
}

IVPlayerPed * CIVPlayerInfo::GetPlayerPed( )
{
	if( m_pPlayerInfo )
		return m_pPlayerInfo->m_pPlayerPed;

	return NULL;
}

void CIVPlayerInfo::SetName( char * szName )
{
	if( m_pPlayerInfo )
		strncpy( m_pPlayerInfo->m_szName, szName, 20 );
}

char * CIVPlayerInfo::GetName( )
{
	if( m_pPlayerInfo )
		return m_pPlayerInfo->m_szName;

	return 0;
}

void CIVPlayerInfo::SetColour( DWORD dwColour )
{
	if( m_pPlayerInfo )
		m_pPlayerInfo->m_dwColour = dwColour;
}

DWORD CIVPlayerInfo::GetColour( )
{
	if( m_pPlayerInfo )
		return m_pPlayerInfo->m_dwColour;

	return 0;
}

void CIVPlayerInfo::SetScore( int iScore )
{
	if( m_pPlayerInfo )
	{

	}
}

int CIVPlayerInfo::GetScore( )
{

	return 0;
}