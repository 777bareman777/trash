// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "MyLight.generated.h"

UCLASS()
class PROJECTBLUEPRINT_API AMyLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
public:
    // 에디터 작업시 변경된 정보들 즉각 반영
    virtual void OnConstruction(const FTransform & Transform) override;
    
    
// 라이트에 필요한 컴포넌트
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySetting, Meta=(AllowPrivateAccess=true))
    class UStaticMeshComponent* LampFixture;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySetting, Meta=(AllowPrivateAccess=true))
    class USpotLightComponent* SpotLight;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySetting, Meta=(AllowPrivateAccess=true))
    class UBoxComponent* Trigger;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MySetting, Meta=(AllowPrivateAccess=true))
    class UTextRenderComponent* HelpfulText;
    
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=MySetting, Meta=(AllowPrivateAccess=true))
    FLinearColor LightColor;
    
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=MySetting, Meta=(AllowPrivateAccess=true))
    bool VisibilitySettings;

// 라이트에 필요한 컴포넌트 getter/setter
public:
    UFUNCTION(BlueprintPure, Category=MySetting)
    class UStaticMeshComponent* GetMesh() const { return LampFixture; }
    
    UFUNCTION(BlueprintCallable, Category=MySetting)
    void SetMesh(class UStaticMeshComponent* NewMesh);
    
    UFUNCTION(BlueprintPure, Category=MySetting)
    class USpotLightComponent* GetSpotLight() const { return SpotLight; }
    
    UFUNCTION(BlueprintCallable, Category=MySetting)
    void SetSpotLight(class USpotLightComponent* NewSpotLight);
    
    UFUNCTION(BlueprintPure, Category=MySetting)
    class UBoxComponent* GetTrigger() const { return Trigger; }
    
    UFUNCTION(BlueprintCallable, Category=MySetting)
    void SetTrigger(class UBoxComponent* NewTrigger);
    
    UFUNCTION(BlueprintPure, Category=MySetting)
    class UTextRenderComponent* GetHelpfulText() const { return HelpfulText; }
    
    UFUNCTION(BlueprintCallable, Category=MySetting)
    void SetHelpfulText(class UTextRenderComponent* NewHelpfulText);
    
// 오버랩시에 발동할 함수들
private:
    UFUNCTION()
    void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    
    UFUNCTION()
    void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
// 오버랩시에 F키 입력시 라이트를 킬 수 있도록 함수 구현
private:
    void BindInput();
    void OnPressedF();
};
