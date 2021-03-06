//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetworkEntity.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkEntity.h"
#include <Network/CBitStream.h>
#include <CLogFile.h>
#include "CPlayerEntity.h"
#include "CVehicleEntity.h"
#include <CCore.h>
extern CCore * g_pCore;

CNetworkEntity::CNetworkEntity()
	: m_vecPosition(CVector3()),
	m_vecRotation(CVector3()),
	m_vecMoveSpeed(CVector3()),
	m_vecTurnSpeed(CVector3()),
	m_entityId(INVALID_ENTITY),
	m_eType(UNKNOWN_ENTITY)
{

}

CNetworkEntity::~CNetworkEntity()
{

}

void CNetworkEntity::GetPosition(CVector3& vecPos)
{
	vecPos = m_vecPosition;
}

void CNetworkEntity::SetPosition(const CVector3& vecPos)
{
	CLogFile::Printf(__FUNCTION__);
	m_vecPosition = vecPos;
}


void CNetworkEntity::GetRotation(CVector3& vecRot)
{
	vecRot = m_vecRotation;
}

void CNetworkEntity::SetRotation(const CVector3& vecRot)
{
	m_vecRotation = vecRot;
}

void CNetworkEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	vecMoveSpeed = m_vecMoveSpeed;
}

void CNetworkEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	m_vecMoveSpeed = vecMoveSpeed;
}

void CNetworkEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	vecTurnSpeed = m_vecTurnSpeed;
}

void CNetworkEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	m_vecTurnSpeed = vecTurnSpeed;
}

bool CNetworkEntity::IsMoving()
{
	if(!(m_vecMoveSpeed.fX == 0 && m_vecMoveSpeed.fY == 0 && (m_vecMoveSpeed.fZ >= -0.000020 && m_vecMoveSpeed.fZ <= 0.000020)))
		return true;

	return false;
}

void CNetworkEntity::StopMoving()
{
	m_vecMoveSpeed = CVector3();
}

void CNetworkEntity::Pulse(CPlayerEntity * pPlayer)
{
	// Check if our player ptr
	if(pPlayer)
	{
		// Get the latest position
		pPlayer->GetPosition(m_vecPosition);

		// Get the latest move speed
		pPlayer->GetMoveSpeed(m_vecMoveSpeed);

		// Get the latest turn speed
		pPlayer->GetTurnSpeed(m_vecTurnSpeed);

		// Get the latest crouch state
		m_pPlayerHandle.bDuckState = pPlayer->GetPlayerPed()->IsDucking();
	}
}

void CNetworkEntity::Pulse(CVehicleEntity * pVehicle)
{
	// Check if our player ptr
	if(pVehicle)
	{
		// Get the latest position
		pVehicle->GetPosition(m_vecPosition);
	}
}

void CNetworkEntity::Serialize(ePackageType pType)
{
	// Create Sync package here and send it to the server
	CBitStream * pBitStream = new CBitStream;

	// Backup old sync
	memcpy(&m_pEntityLastSync, &m_pEntitySync, sizeof(CNetworkEntitySync));

	// Create package
	m_pEntitySync = *(new CNetworkEntitySync);

	switch(m_eType)
	{
	case PLAYER_ENTITY:
		{
			// If we already set data for our next sync packet, copy the data
			sNetwork_Sync_Entity_Player * pSyncPacket = &(m_pEntitySync.pPlayerPacket);

			// Apply entity type to package
			m_pEntityLastSync.pEntityType = PLAYER_ENTITY;

			// Apply current 3D Position to the sync package
			pSyncPacket->vecPosition = m_vecPosition;
			
			// Merge EntitySync packet with our packet
			memcpy(&m_pEntitySync.pPlayerPacket, pSyncPacket, sizeof(sNetwork_Sync_Entity_Player));

			// Stop current case
			break;

		}
	case VEHICLE_ENTITY:
		{
			// If we already set data for our next sync packet, copy the data
			sNetwork_Sync_Entity_Vehicle * pSyncPacket = &(m_pEntitySync.pVehiclePacket);

			// Apply entity type to package
			m_pEntityLastSync.pEntityType = VEHICLE_ENTITY;

			// Apply current 3D Position to the sync package
			pSyncPacket->vecPosition = m_vecPosition;

			// Merge EntitySync packet with our packet
			memcpy(&m_pEntitySync.pVehiclePacket, pSyncPacket, sizeof(sNetwork_Sync_Entity_Vehicle));

			// Stop current case
			break;
		}
	default:
		{
			CLogFile::Print("Failed to get entity type from current entitiy. Sync canceled..");
			break;
		}
	}

	// Write our Entity-Sync to the bitstream
	pBitStream->Write((char *) &m_pEntitySync, sizeof(CNetworkEntitySync));

	// Send package to network
	g_pCore->GetNetworkManager()->Call(CString("0x69766D50_F%d", eRPCIdentifier::RPC_SYNC_PACKAGE).Get(), pBitStream, ePacketPriority::PRIORITY_HIGH, ePacketReliability::RELIABILITY_RELIABLE, ePacketChannels::PACKET_CHANNEL_DEFAULT, false);
}

void CNetworkEntity::Deserialize(ePackageType pType)
{
	// Get Sync package here and recieve it to the server
	CBitStream * pBitStream = new CBitStream();
	pBitStream->Write0();
}