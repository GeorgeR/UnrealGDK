// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// Note that this file has been generated automatically
#pragma once

#include <improbable/worker.h>
#include <improbable/view.h>
#include <unreal/generated/UnrealGameStateBase.h>
#include <unreal/core_types.h>
#include "SpatialHandlePropertyMap.h"
#include "SpatialTypeBinding.h"
#include "SpatialTypeBinding_GameStateBase.generated.h"

UCLASS()
class USpatialTypeBinding_GameStateBase : public USpatialTypeBinding
{
	GENERATED_BODY()

public:
	static const FRepHandlePropertyMap& GetHandlePropertyMap();

	void Init(USpatialUpdateInterop* InUpdateInterop, USpatialPackageMapClient* InPackageMap) override;
	void BindToView() override;
	void UnbindFromView() override;
	worker::ComponentId GetReplicatedGroupComponentId(EReplicatedPropertyGroup Group) const override;

	worker::Entity CreateActorEntity(const FString& ClientWorkerId, const FVector& Position, const FString& Metadata, const FPropertyChangeState& InitialChanges, USpatialActorChannel* Channel) const override;
	void SendComponentUpdates(const FPropertyChangeState& Changes, USpatialActorChannel* Channel, const worker::EntityId& EntityId) const override;
	void SendRPCCommand(AActor* TargetActor, const UFunction* const Function, FFrame* const DuplicateFrame) override;

	void ApplyQueuedStateToChannel(USpatialActorChannel* ActorChannel) override;

private:
	worker::Dispatcher::CallbackKey SingleClientAddCallback;
	worker::Dispatcher::CallbackKey SingleClientUpdateCallback;
	worker::Dispatcher::CallbackKey MultiClientAddCallback;
	worker::Dispatcher::CallbackKey MultiClientUpdateCallback;

	// Pending updates.
	TMap<worker::EntityId, improbable::unreal::UnrealGameStateBaseSingleClientReplicatedData::Data> PendingSingleClientData;
	TMap<worker::EntityId, improbable::unreal::UnrealGameStateBaseMultiClientReplicatedData::Data> PendingMultiClientData;

	// RPC sender and receiver callbacks.
	using FRPCSender = void (USpatialTypeBinding_GameStateBase::*)(worker::Connection* const, struct FFrame* const, AActor*);
	TMap<FName, FRPCSender> RPCToSenderMap;
	TArray<worker::Dispatcher::CallbackKey> RPCReceiverCallbacks;

	// Component update helper functions.
	void BuildSpatialComponentUpdate(
		const FPropertyChangeState& Changes,
		USpatialActorChannel* Channel,
		improbable::unreal::UnrealGameStateBaseSingleClientReplicatedData::Update& SingleClientUpdate,
		bool& bSingleClientUpdateChanged,
		improbable::unreal::UnrealGameStateBaseMultiClientReplicatedData::Update& MultiClientUpdate,
		bool& bMultiClientUpdateChanged) const;
	void ApplyUpdateToSpatial_SingleClient(
		const uint8* RESTRICT Data,
		int32 Handle,
		UProperty* Property,
		USpatialActorChannel* Channel,
		improbable::unreal::UnrealGameStateBaseSingleClientReplicatedData::Update& OutUpdate) const;
	void ApplyUpdateToSpatial_MultiClient(
		const uint8* RESTRICT Data,
		int32 Handle,
		UProperty* Property,
		USpatialActorChannel* Channel,
		improbable::unreal::UnrealGameStateBaseMultiClientReplicatedData::Update& OutUpdate) const;
	void ReceiveUpdateFromSpatial_SingleClient(
		USpatialActorChannel* ActorChannel,
		const improbable::unreal::UnrealGameStateBaseSingleClientReplicatedData::Update& Update) const;
	void ReceiveUpdateFromSpatial_MultiClient(
		USpatialActorChannel* ActorChannel,
		const improbable::unreal::UnrealGameStateBaseMultiClientReplicatedData::Update& Update) const;

	// RPC sender functions.

	// RPC sender response functions.

	// RPC receiver functions.
};
