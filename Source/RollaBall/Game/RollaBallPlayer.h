// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollaBallPlayer.generated.h"

// Forward declaration to reduce compile time: https://forums.unrealengine.com/t/including-classes-in-header-vs-forward-declaration-in-header-and-include-in-cpp/137524/2\
// https://stackoverflow.com/questions/3632818/forward-declaration-vs-include
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ROLLABALL_API ARollaBallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollaBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce{500.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpImpulse{500.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxJumpCount{1};

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveRight(const float Value);
	void MoveForward(const float Value);
	void Jump();

	// Must be UFUNCTION to be dynamically linked to OnComponentHit
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	int32 JumpCount{0};
};
