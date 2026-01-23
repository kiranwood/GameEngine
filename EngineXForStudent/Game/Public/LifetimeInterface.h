#pragma once

// Interface class has no function implemented

class ILifetimeInterface
{
public:

	virtual void BeginPlay() = 0;
	virtual void EndPlay() = 0;
	virtual void Tick(const float DeltaTime) = 0; // Dont want to change delta time
};
