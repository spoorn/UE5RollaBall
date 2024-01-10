// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Set the RootComponent to be our Mesh
	RootComponent = Mesh;
	// Attach the SpringArm to the Mesh, Spring will now follow the Mesh Transform
	SpringArm->SetupAttachment(Mesh);
	// Attach the Camera to the SpringArm, Camera will follow the SpringArm Transform
	Camera->SetupAttachment(SpringArm);
	
	// Set physics to true
	Mesh->SetSimulatePhysics(true);
	// https://forums.unrealengine.com/t/simulation-generate-hit-events-boolean-in-c/297944
	Mesh->BodyInstance.SetInstanceNotifyRBCollision(true);

	// Grounded
	Mesh->OnComponentHit.AddDynamic(this, &ARollaBallPlayer::OnHit);

	// Don't rotate spring arm
	SpringArm->SetRelativeRotation(FRotator(-40.0, 0.0, 0.0));
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->TargetArmLength = 1000.0f;
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Account for mass in MoveForce and JumpImpulse
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Custom input axis bindings
	InputComponent->BindAxis("MoveForward", this, &ARollaBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollaBallPlayer::MoveRight);
	// Custom action bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollaBallPlayer::Jump);
}

void ARollaBallPlayer::MoveRight(const float Value)
{
	// Get the right vector of the camera as it doesn't rotate and move the player in this direction based on input and MoveForce
	// this is because UE is (x-forward, y-right, z-up) which is pretty counter intuitive, and left hand rule -> right vector would be  (0, 1, 0)
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollaBallPlayer::MoveForward(const float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollaBallPlayer::Jump()
{
	if (JumpCount >= MaxJumpCount)
	{
			return;
	}
	// Apply an impulse to the Mesh in the Z-Axis (up)
	// Impulse is for instantaneous momentum or change in momentum, force is for continuous acceleration
	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
	JumpCount++;
}

void ARollaBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Z Normal: %f"), Hit.Normal.Z));
	// UE_LOG(LogTemp, Display, TEXT("Z Normal: %f"), Hit.Normal.Z);
	// We hit something on the bottom
	if (Hit.Normal.Z > 0)
	{
		JumpCount = 0;
	}
}

