#pragma once

#include "UMG.h"
#include "Blueprint/UserWidget.h"

#include "ViewWidget3D.generated.h"

USTRUCT()
struct FViewWidget3DBounds
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FVector TopLeft;

	UPROPERTY()
	FVector TopRight;

	UPROPERTY()
	FVector BottomRight;

	UPROPERTY()
	FVector BottomLeft;
};

UCLASS()
class VIEWACTIVATOR_API UViewWidget3D
	: public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UViewWidget* Widget2D;

private:
	UPROPERTY()
	int32 Divisions;

	UPROPERTY()
	TArray<FVector> SpherePoints;

	void ConstructSphere();
	bool RaycastSphere(FHitResult& OutHitResult, FVector InStart, FVector InEnd, FSphere& InSphere);

protected:
	virtual void NativeConstruct() override;
};