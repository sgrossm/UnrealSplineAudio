
#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "GameFramework/Actor.h"
#include "SplineAudio.generated.h"

// Forward Declaration
class USplineComponent;

UCLASS(Blueprintable)
class UNREALSPLINEAUDIO_API ASplineAudio : public AAmbientSound
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineAudio();

	// Minimum distance for sound to be played
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline Audio")
	float TickRange { 1000.0f };

	// How often to check for Player in range of Spline
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline Audio")
	float CustomRegularTickInterval { 0.2f };

	// Slow down tick interval when outside range (should be larger than regular tick interval)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline Audio")
	float CustomSlowTickInterval { 0.5f };

	// Debugging will draw sphere for the audio component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Audio")
	bool DebugOn { true };

	// Debug Sphere color when player is moving
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline Audio")
	FColor DebugColorMoving { FColor::Blue };

	// Debug Sphere color when player is static
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline Audio")
	FColor DebugColorStatic { FColor::White };

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	/*
		Component variables
	*/
	// Spline Component
	USplineComponent* SplineComponent;

	// Audio Component
	UAudioComponent* AudioComponent;


	/*
		Functions
	*/
	// Check if player is in MinDistance range of Moving Audio Component 
	bool IsPlayerInRange(const FVector& PlayerLocation, const UAudioComponent* MovingAudioComponent) const;

	// Moves Audio Component along spline as player moves
	void UpdateAudioPosition(const FVector& PlayerLocation);

	// Get Current(first) player location
	FVector GetPlayerCurrentLocation() const;

	// Returns true if the player is moving, false otherwise
	bool IsPlayerMoving(const FVector& PlayerLocation);

	// Draw Debug sphere if DebugOn=true
	void DrawDebug(const FVector SphereLocation, const FString DebugMessage, const FColor DebugColor) const;


	/* 
		Variables
	*/
	// These variables handle calculating whether the player is moving
	FVector CurrentPlayerLocation;
	FVector PrevPlayerLocation;
};
