#ifndef GRAVITYSYSTEM_H
#define GRAVITYSYSTEM_H

#include "core/system.h"
#include "core/components/positioncomponent.h"
#include "velocitycomponent.h"
#include "core/boiler.h"

class GravitySystem : public System
{
public:
	GravitySystem() { }

	void update(ComponentStore &store, const double delta) const override
	{
		Size screenSize = Boiler::getInstance().getRenderer().getScreenSize();

		for (auto &entity : getEntities())
		{
			PositionComponent &pos = store.retrieve<PositionComponent>(entity);
			VelocityComponent &vel = store.retrieve<VelocityComponent>(entity);

			vel.velocity.y += delta * 30.0;
			if (pos.frame.position.y + vel.velocity.y >= screenSize.getHeight() - pos.frame.size.getHeight())
			{
				vel.velocity.y = -(vel.velocity.y * 0.6f);
			}
			else
			{
				pos.frame.position.y += vel.velocity.y;
			}
		}
	}
};

#endif /* GRAVITYSYSTEM_H */
