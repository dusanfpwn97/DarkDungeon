//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"

class FLaunchPadSystem {
public:
    static void Register();
    static void Unregister();

    static void Launch();
};
