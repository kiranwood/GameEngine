#pragma once
#include "Game/Public/Utils.h"

class RenderComponent;
class exEngineInterface;
#define RENDER_ENGINE RenderEngine::GetInstance()


class RenderEngine
{

public:
	~RenderEngine();

	static RenderEngine& GetInstance()
	{
		if (!sRenderEngine)
		{
			sRenderEngine.reset(new RenderEngine());
		}
		return *sRenderEngine;
	}

	void AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd);
	void ClearInvalidRenderComponents();

	void RenderUpdate(exEngineInterface* mEngine);

private:

	RenderEngine();

	RenderEngine(const RenderEngine& OtherEngine) = delete;
	RenderEngine& operator=(const RenderEngine& OtherEngine) = delete;

	static std::unique_ptr<RenderEngine> sRenderEngine;

	std::list<std::weak_ptr<RenderComponent>> mRenderComponents;
};