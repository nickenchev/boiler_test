#include <iostream>
#include "blankpart.h"
#include "video/systems/rendersystem.h"
#include "core/components/positioncomponent.h"
#include "core/components/spritecomponent.h"
#include "gravitysystem.h"
#include "velocitycomponent.h"

BlankPart::BlankPart() : logger("Playground Part")
{
	spriteSheet = Boiler::getInstance().getSpriteLoader().loadSheet("data/terrain.json");
	EntityComponentSystem &ecs = Boiler::getInstance().getEcs();

	// add the rendering system
	ecs.getComponentSystems().registerSystem<RenderSystem>()
		.expects<PositionComponent>(ecs.getComponentMapper())
		.expects<SpriteComponent>(ecs.getComponentMapper());

	ecs.getComponentSystems().registerSystem<GravitySystem>()
		.expects<PositionComponent>(ecs.getComponentMapper())
		.expects<VelocityComponent>(ecs.getComponentMapper());

	const int maxTileSize = 100;
	for (int i = 0; i < 100; ++i)
	{
		int x = rand() % Boiler::getInstance().getRenderer().getScreenSize().getWidth();
		int y = rand() % Boiler::getInstance().getRenderer().getScreenSize().getHeight();
		int size = rand() % (maxTileSize + 1 - 30) + 30;

		Entity enemy = ecs.newEntity();
		auto pos = ecs.addComponent<PositionComponent>(enemy, Rect(x, y, size, size));
		pos->absolute = true;
		auto sprite = ecs.addComponent<SpriteComponent>(enemy, pos->frame);
		sprite->spriteFrame = spriteSheet->getFrame("forest.png");
		ecs.addComponent<VelocityComponent>(enemy);
	}
}

void BlankPart::onStart()
{
    Boiler::getInstance().getRenderer().setClearColor(Color3(0.2f, 0.2f, 0.4f));
    Boiler::getInstance().addKeyInputListener([this](const KeyInputEvent &event)
	{
		EntityComponentSystem &ecs = Boiler::getInstance().getEcs();
		// VelocityComponent &velocity = ecs.getComponentStore().retrieve<VelocityComponent>(this->player);

		if (event.state == ButtonState::UP)
		{
			if (event.keyCode == SDLK_ESCAPE)
			{
				Boiler::getInstance().quit();
			}
		// 	else if (event.keyCode == SDLK_a)
		// 	{
		// 		velocity.velocity.x = 0;
		// 	}
		// 	else if (event.keyCode == SDLK_d)
		// 	{
		// 		velocity.velocity.x = 0;
		// 	}
		// }
		// else if (event.state == ButtonState::DOWN)
		// {
		// 	if (event.keyCode == SDLK_a)
		// 	{
		// 		velocity.velocity.x = -3.0f;
		// 	}
		// 	else if (event.keyCode == SDLK_d)
		// 	{
		// 		velocity.velocity.x = 3.0f;
		// 	}
		}
	});
}
