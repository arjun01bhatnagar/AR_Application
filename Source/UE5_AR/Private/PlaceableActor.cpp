// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableActor.h"
#include "ARPin.h"
#include "ARBlueprintLibrary.h"
#include "CustomARPawn.h"


// Sets default values
APlaceableActor::APlaceableActor()//:SpawnedEnemy(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);


	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);


	

	t=0.5f;

}

// Called when the game starts or when spawned
void APlaceableActor::BeginPlay()
{
	Super::BeginPlay();



	//PlacableLoc=SetActorLocation();
	
	
}

// Called every frame
void APlaceableActor::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
//
	t += DeltaTime;
	scale = 2.0f / (3.0f - cos(2.0f * t));
	scale *= 50;
	x = scale * cos(t);
	y = scale * sin(15.f * t) / 2.0f;

	

	SetActorLocation(FVector(PlacableLoc.X , PlacableLoc.Y + x, PlacableLoc.Z +y));
	
	// Making sure the actor remains on the ARPin that has been found.
	if(PinComponent)
	{
	  auto TrackingState = PinComponent->GetTrackingState();
	//
	switch (TrackingState)
	{
	case EARTrackingState::Tracking:
		SceneComponent->SetVisibility(true);
		//SetActorTransform(PinComponent->GetLocalToWorldTransform());

		// Scale down default cube mesh - Change this for your applications.
		SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
		break;

	case EARTrackingState::NotTracking:
		PinComponent = nullptr;

		break;

	}
}
	

}


void APlaceableActor::LocationForActor()
{


	PlacableLoc=GetActorLocation();

}


