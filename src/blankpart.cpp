#include <iostream>
#include "blankpart.h"
#include "video/systems/rendersystem.h"
 "core/components/positioncomponent.h"
#include "core/components/spritecomponent.h"
#include "core/spriteloader.h"
#include "gravitysystem.h"
#include "velocitycomponent.h"

BlankPart::BlankPart() : logger("Playground Part")
{
	spriteSheet = Boiler::getInstance().getSpriteLoader().loadJsonArray("data/triptych.json");
	EntityComponentSystem &ecs = Boiler::getInstance().getEcs();

	// add the rendering system
	ecs.getComponentSystems().registerSystem<RenderSystem>()
		.expects<PositionComponent>()
		.expects<SpriteComponent>();

	ecs.getComponentSystems().registerSystem<GravitySystem>()
		.expects<PositionComponent>()
		.expects<VelocityComponent>();
}

void BlankPart::onStart()
{
    Boiler::getInstance().getRenderer().setClearColor(Color3(0.2f, 0.2f, 0.4f));
    auto keyListener = [this](const KeyInputEvent &event)
	{
		const int maxTileSize = 100;
		EntityComponentSystem &ecs = Boiler::getInstance().getEcs();

		if (event.state == ButtonState::UP)
		{
			if (event.keyCode == SDLK_ESCAPE)
			{
				Boiler::getInstance().quit();
			}
		}
		if (event.state == ButtonState::DOWN)
		{
			if (event.keyCode == SDLK_SPACE)
			{
				int x = rand() % Boiler::getInstance().getRenderer().getScreenSize().getWidth();
				int y = 0;
				int size = rand() % (maxTileSize + 1 - 30) + 30;

				Entity enemy = ecs.newEntity();
				auto pos = ecs.createComponent<PositionComponent>(enemy, Rect(x, y, size, size));
				pos->absolute = true;
				auto sprite = ecs.createComponent<SpriteComponent>(enemy, pos->frame);
				sprite->spriteFrame = spriteSheet->getFrame("diskette.png");
				auto velocity = ecs.createComponent<VelocityComponent>(enemy);
				velocity->velocity.x = 50;
			}
		}
	};
	Boiler::getInstance().addKeyInputListener(keyListener);
	
    Boiler::getInstance().getRenderer().setClearColor(Color3(0.2f, 0.2f, 0.4f));
}
