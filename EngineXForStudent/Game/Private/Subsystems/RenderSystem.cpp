#include "Game/Public/Subsystems/RenderSystem.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Components/RenderComponent.h"

std::unique_ptr<RenderEngine> RenderEngine::sRenderEngine = nullptr;


RenderEngine::~RenderEngine()
{
	ClearInvalidRenderComponents();
}

void RenderEngine::AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd)
{
	mRenderComponents.emplace_back(componentToAdd);
}

void RenderEngine::ClearInvalidRenderComponents()
{
	if (mRenderComponents.empty())
	{
		return;
	}

	mRenderComponents.remove_if(
		[](const std::weak_ptr<RenderComponent>& component)
		{
			return component.expired();
		});
}

void RenderEngine::RenderUpdate(exEngineInterface* mEngine)
{
	ClearInvalidRenderComponents();

	for (size_t index1 = 0; index1 < mRenderComponents.size(); index1++)
	{
		std::list<std::weak_ptr<RenderComponent>>::iterator renderComponent = mRenderComponents.begin();
		std::advance(renderComponent, index1);

		std::shared_ptr<RenderComponent> ComponentToRender = renderComponent->lock();

		ComponentToRender->Render(mEngine);
	}
}

RenderEngine::RenderEngine()
{

}