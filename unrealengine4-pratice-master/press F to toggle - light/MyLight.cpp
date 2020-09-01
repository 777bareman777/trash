// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectBlueprint/MyLight.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AMyLight::AMyLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    LampFixture=CreateDefaultSubobject<class UStaticMeshComponent>(TEXT("LAMPFIXTURE"));
    SpotLight=CreateDefaultSubobject<class USpotLightComponent>(TEXT("SPOTLIGHT"));
    Trigger=CreateDefaultSubobject<class UBoxComponent>(TEXT("TRIGGER"));
    HelpfulText=CreateDefaultSubobject<class UTextRenderComponent>(TEXT("HELPFULTEXT"));
    InputComponent=CreateDefaultSubobject<class UInputComponent>(TEXT("INPUTCOMPONENT"));
    
    RootComponent=LampFixture;
    SpotLight->SetupAttachment(LampFixture);
    Trigger->SetupAttachment(LampFixture);
    HelpfulText->SetupAttachment(LampFixture);
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LAMP(TEXT("/Game/StarterContent/Props/SM_Lamp_Wall.SM_Lamp_Wall"));
    if(SM_LAMP.Succeeded())
    {
        LampFixture->SetStaticMesh(SM_LAMP.Object);
    }
    
    
    Trigger->SetRelativeRotation(FRotator(90.0f,0.0f,0.0f));
    Trigger->SetRelativeScale3D(FVector(3.5f, 2.5f, 1.0f));
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyLight::OnTriggerBeginOverlap);
    Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyLight::OnTriggerEndOverlap);
    
    HelpfulText->SetRelativeLocation(FVector(0.0f,0.0f,-20.0f));
    HelpfulText->SetWorldSize(18.0f);
    HelpfulText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    
    SpotLight->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,16.0f), FRotator(90.0f,0.0f,0.0f));
    SpotLight->SetOuterConeAngle(60.0f);
    
    
    LightColor=FLinearColor(1.0f,1.0f,1.0f,1.0f);
    VisibilitySettings=false;
    SpotLight->SetLightColor(LightColor, true);
    SpotLight->SetVisibility(VisibilitySettings, false);
    HelpfulText->SetVisibility(VisibilitySettings, false);
    HelpfulText->SetText(FText::FromString(FString(TEXT("Press F to toggle"))));
    
    BindInput();
}

// Called when the game starts or when spawned
void AMyLight::BeginPlay()
{
	Super::BeginPlay();
    
}

void AMyLight::OnConstruction(const FTransform & Transform)
{
    SpotLight->SetLightColor(LightColor, true);
    SpotLight->SetVisibility(VisibilitySettings,false);
    HelpfulText->SetVisibility(VisibilitySettings,false);
}

void AMyLight::SetMesh(class UStaticMeshComponent* NewMesh)
{
    if(nullptr != NewMesh)
        return;
    
    LampFixture=NewMesh;
}

void AMyLight::SetSpotLight(class USpotLightComponent* NewSpotLight)
{
    if(nullptr != NewSpotLight)
        return;
    
    SpotLight=NewSpotLight;
}

void AMyLight::SetTrigger(class UBoxComponent* NewTrigger)
{
    if(nullptr != NewTrigger)
        return;
    
    Trigger=NewTrigger;
}

void AMyLight::SetHelpfulText(class UTextRenderComponent* NewHelpfulText)
{
    if(nullptr != NewHelpfulText)
        return;
    
    HelpfulText=NewHelpfulText;
}

void AMyLight::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    auto PlayerController=UGameplayStatics::GetPlayerController(GetWorld(),0);
    EnableInput(PlayerController);
    HelpfulText->ToggleVisibility(false);
    
    UE_LOG(LogTemp, Log, TEXT(" begin overlap acotr : %s"), *PlayerController->GetName());
}

void AMyLight::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    auto PlayerController=UGameplayStatics::GetPlayerController(GetWorld(),0);
    DisableInput(PlayerController);
    HelpfulText->ToggleVisibility(false);
    UE_LOG(LogTemp, Log, TEXT(" end overlap acotr : %s"), *PlayerController->GetName());
}

void AMyLight::BindInput()
{
    InputComponent->BindAction(TEXT("PressF"),EInputEvent::IE_Pressed,this, &AMyLight::OnPressedF);
}

void AMyLight::OnPressedF()
{
    UE_LOG(LogTemp, Log, TEXT("Press F"));
    SpotLight->ToggleVisibility(false);
}
