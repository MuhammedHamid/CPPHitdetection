#pragma once


#include "FightInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UFightInterface : public UInterface
{
    GENERATED_BODY()
    
};

class IFightInterface
{    
    GENERATED_BODY()

public:
    /** Add interface function declarations here */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= attacks)
    void CheckPunch( bool is_leftHand);

    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= attacks)
    void CheckKick( bool is_leftLeg);
};