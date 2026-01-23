#pragma once
#include <type_traits>
#include <memory>
#include "LifetimeInterface.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/ComponentTypes.h"


class Actor : public ILifetimeInterface, public std::enable_shared_from_this<Actor> // Can create shared ptr from yourself
{
public:

	Actor();
	virtual ~Actor();
#pragma region ILifetimeInterface
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	virtual void Tick(const float DeltaSeconds) override;
#pragma endregion
	virtual void Render(exEngineInterface* EngineInterface);

private:
	// Stores all the components
	ComponentList mComponents;


#pragma region TemplateRegion
public:

	template<std::derived_from<Component> ComponentType>
	std::tuple<std::shared_ptr<ComponentType>, bool, String> AddComponentOfType() 
	{
		ComponentType* ComponentPtr = new ComponentType(weak_from_this());
		std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>(*ComponentPtr);
		delete ComponentPtr;

		if (NewComponent->CanAddComponent())
		{
			NewComponent->BeginPlay();
			mComponents.emplace_back(NewComponent);
			return { NewComponent, true, "Component was created successfuly" };
		}
		return { nullptr, false, "Failed to add component" };
	}




#pragma endregion
};

