//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetworkEntity.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CNetworkEntity_h
#define CNetworkEntity_h

#include <Common.h>
#include <Math/CMaths.h>

class CPlayerEntity;
class CVehicleEntity;
enum eEntityType
{
	PLAYER_ENTITY,
	VEHICLE_ENTITY,
	OBJECT_ENTITY,
	PICKUP_ENTITY,
	LABEL_ENTITY,
	FIRE_ENTITY,
	CHECKPOINT_ENTITY,
	BLIP_ENTITY,
	ACTOR_ENTITY,
	UNKNOWN_ENTITY, // MAX_ENTITY
	INVALID_ENTITY,
};

class CNetworkEntityType {
public:
	static CString		ConverEntityTypeStringToEntityId(eEntityType eEntityType)
	{
		switch(eEntityType)
		{
		case PLAYER_ENTITY:
			{
				return CString("PLAYER_ENTITY");
			}
		case VEHICLE_ENTITY:
			{
				return CString("VEHICLE_ENTITY");
			}
		case OBJECT_ENTITY:
			{
				return CString("OBJECT_ENTITY");
			}
		case PICKUP_ENTITY:
			{
				return CString("PICKUP_ENTITY");
			}
		case LABEL_ENTITY:
			{
				return CString("LABEL_ENTITY");
			}
		case FIRE_ENTITY:
			{
				return CString("FIRE_ENTITY");
			}
		case CHECKPOINT_ENTITY:
			{
				return CString("CHECKPOINT_ENTITY");
			}
		case BLIP_ENTITY:
			{
				return CString("BLIP_ENTITY");
			}
		case ACTOR_ENTITY:
			{
				return CString("ACTOR_ENTITY");
			}
		case UNKNOWN_ENTITY:
			{
				return CString("UNKNOWN_ENTITY");
			}
		case INVALID_ENTITY:
			{
				return CString("INVALID_ENTITY");
			}
		default:
			{
				return CString("Wrong entity type..");
			}
		}

		return CString("Some shit happened. Please restart the client");
	}

	static BYTE			ConvertEntityTypeToEntityTypeString(CString strEntityType)
	{
		if(strEntityType.Find("PLAYER_ENTITY") != std::string::npos)
			return 0;
		if(strEntityType.Find("VEHICLE_ENTITY") != std::string::npos)
			return 1;
		if(strEntityType.Find("OBJECT_ENTITY") != std::string::npos)
			return 2;
		if(strEntityType.Find("PICKUP_ENTITY") != std::string::npos)
			return 3;
		if(strEntityType.Find("LABEL_ENTITY") != std::string::npos)
			return 4;
		if(strEntityType.Find("FIRE_ENTITY") != std::string::npos)
			return 5;
		if(strEntityType.Find("CHECKPOINT_ENTITY") != std::string::npos)
			return 6;
		if(strEntityType.Find("BLIP_ENTITY") != std::string::npos)
			return 7;
		if(strEntityType.Find("ACTOR_ENTITY") != std::string::npos)
			return 8;
		if(strEntityType.Find("UNKNOWN_ENTITY") != std::string::npos)
			return 9;
		if(strEntityType.Find("INVALID_ENTITY") != std::string::npos)
			return 10;

		// Return invalid
		return 10;
	}
};

class CNetworkEntitySubPlayer {
private:

public:
	bool						bDuckState;
	// Add player members to sync(like weapon sync, key sync etc.)
};


class CNetworkEntitySubVehicle {
private:

public:
	// Add vehicle members to sync(like indicators, variation etc.)
};

class CNetworkEntitySync {
public:
	eEntityType							pEntityType;
	sNetwork_Sync_Entity_Player			pPlayerPacket;
	sNetwork_Sync_Entity_Vehicle		pVehiclePacket;
};

class CNetworkEntity {
private:
	eEntityType						m_eType;
	EntityId						m_entityId;
	CVector3						m_vecPosition;
	CVector3						m_vecRotation;
	CVector3						m_vecMoveSpeed;
	CVector3						m_vecTurnSpeed;

	CNetworkEntitySync				m_pEntitySync;
	CNetworkEntitySync				m_pEntityLastSync;

	CNetworkEntitySubPlayer			m_pPlayerHandle;
	CNetworkEntitySubVehicle		m_pVehicleHandle;

public:
	CNetworkEntity();
	CNetworkEntity(eEntityType eType);
	CNetworkEntity(eEntityType eType, EntityId entityId);
	~CNetworkEntity();

	virtual bool		Create() = 0;
	virtual bool		Destroy() = 0;

	virtual void		Pulse(CPlayerEntity * pPlayer);
	virtual void		Pulse(CVehicleEntity * pVehicle);

	virtual void		GetPosition(CVector3& vecPos);
	virtual void		SetPosition(const CVector3& vecPos);

	virtual void		GetRotation(CVector3& vecRot);
	virtual void		SetRotation(const CVector3& vecRot);

	virtual void		GetMoveSpeed(CVector3& vecMoveSpeed);
	virtual void		SetMoveSpeed(const CVector3& vecMoveSpeed);

	virtual void		GetTurnSpeed(CVector3& vecTurnSpeed);
	virtual void		SetTurnSpeed(const CVector3& vecTurnSpeed);

	virtual EntityId	GetId() { return m_entityId; }
	virtual void		SetId(EntityId entityId) { m_entityId = entityId; }

	bool				IsOnScreen();

	virtual	bool		IsMoving();
	virtual void		StopMoving();

	virtual void		Serialize(ePackageType pType);
	virtual void		Deserialize(ePackageType pType);

	virtual void		AddToWorld() { /* Nothing can be done here */ };
	virtual void		RemoveFromWorld(bool bStopMoving = true) { /* Nothing can be done here */ };

	//virtual void		SetInterior(DWORD dwInterior) { m_dwInterior = dwInterior; }
	//virtual DWORD		GetInterior() { return m_dwInterior; }

	eEntityType			GetType() { return m_eType; }
	void				SetType(eEntityType eType) { m_eType = eType; }

	CNetworkEntitySync	GetLatestSyncPackage() { return m_pEntitySync; }
	CNetworkEntitySync	GetOldestSyncPackage() { return m_pEntityLastSync; }

	CNetworkEntitySubPlayer	GetPlayerHandle() { return m_pPlayerHandle; }
	CNetworkEntitySubVehicle GetVehicleHandle() { return m_pVehicleHandle; }
};

#endif // CNetworkEntity_h