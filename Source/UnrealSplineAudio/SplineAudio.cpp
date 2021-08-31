
#include "SplineAudio.h"
#include "Components/SplineComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASplineAudio::ASplineAudio()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Create Spline Component and set it to be the root component
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	// Create Audio Component and attach to the root
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASplineAudio::BeginPlay()
{
	Super::BeginPlay();
	
	// Set custom tick interval
	PrimaryActorTick.TickInterval = CustomRegularTickInterval;

	
	// Make sure sound cue is attached
	if (!AudioComponent->Sound)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a Sound Cue attached"), *GetName());
	}

	// Make sure attenuation is attached
	if (!AudioComponent->AttenuationSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have Attenuation attached"), *GetName());
	}
}

// Called every frame
void ASplineAudio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Cache player location
	FVector PlayerCurrentLocation = GetPlayerCurrentLocation();

	// Check if the player is moving (do we need to move Audio Component?)
	if (IsPlayerMoving(PlayerCurrentLocation))
	{
		// Update Audio Component relative to player
		UpdateAudioPosition(PlayerCurrentLocation);


// Only run debugging while working in Editor
#if WITH_EDITOR
		
		// player is moving, draw debug sphere in moving color
		if (DebugOn)
		{
			DrawDebug(AudioComponent->GetComponentLocation(), "", DebugColorMoving);
		}
	}

	 
	else
	{
		// if the player isn't moving, draw the debug sphere in static color
		if (DebugOn)
		{			
			DrawDebug(AudioComponent->GetComponentLocation(), "", DebugColorStatic);
		}
	}
#endif

	// Check if the player is in range of Audio Component 
	if (IsPlayerInRange(PlayerCurrentLocation, AudioComponent))
	{
		// Set normal tick interval 
		PrimaryActorTick.TickInterval = CustomRegularTickInterval;
	}

	else
	{
		// Slow down the tick if player is not in range
		PrimaryActorTick.TickInterval = CustomSlowTickInterval;
	}

}

// Check if player is in MinDistance range of Audio Component 
bool ASplineAudio::IsPlayerInRange(const FVector& PlayerLocation, const UAudioComponent* MovingAudioComponent) const
{
	// Get Audio Component location
	FVector MovingAudioComponentLocation = MovingAudioComponent->GetComponentLocation();

	// Get the distance between Player and Audio Component
	float DistanceToPlayer = FVector::Dist(PlayerLocation, MovingAudioComponentLocation);

	// Returns true if distance between Player and Audio component is within MinDistance range
	return DistanceToPlayer < TickRange;
}

// Moves Audio Component along spline as player moves
void ASplineAudio::UpdateAudioPosition(const FVector& PlayerLocation)
{
	// Get location of point on spline that is closest to the Player
	FVector ClosestPointOnSpline = SplineComponent->FindLocationClosestToWorldLocation(PlayerLocation, ESplineCoordinateSpace::World);

	// Move Audio Component to closest point
	AudioComponent->SetWorldLocation(ClosestPointOnSpline);
}

// Gets first Player location
FVector ASplineAudio::GetPlayerCurrentLocation() const
{
	// Gets current player using index 0 to indicate first player
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	return PlayerPawn->GetActorLocation();
}

// Determine if the player is moving
bool ASplineAudio::IsPlayerMoving(const FVector& PlayerLocation)
{
	// Set player current location
	CurrentPlayerLocation = PlayerLocation;

	if (PrevPlayerLocation == CurrentPlayerLocation)
	{
		// Update Player's previous location
		PrevPlayerLocation = CurrentPlayerLocation;
		// If current == prev, we are not moving
		return false;
	}

	else
	{
		// Update Player's previous location
		PrevPlayerLocation = CurrentPlayerLocation;
		// if current != prev, we are moving
		return true;
	}
	
}

// Draws sphere if DebugOn=true
void ASplineAudio::DrawDebug(const FVector SphereLocation, const FString DebugMessage, const FColor DebugColor) const
{
	// Draw sphere at Audio Component location 
	DrawDebugSphere(GetWorld(), SphereLocation, 100, 12, DebugColor, false, PrimaryActorTick.TickInterval + 0.01f);

	// Draw sphere for tick range
	DrawDebugSphere(GetWorld(), SphereLocation, TickRange, 24, DebugColor, false, PrimaryActorTick.TickInterval + 0.01f);

}