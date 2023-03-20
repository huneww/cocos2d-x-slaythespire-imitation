#include "Relics.h"

USING_NS_CC;

void Relics::Create_Have_Relics()
{
	int character = user->getIntegerForKey("Charcter_choes");

	if (character == 0 && Relics_sprite[0] == nullptr)
	{
		Relics_sprite[0] = Sprite::create("slaythespire/relics/burningBlood.png");
		Relics_sprite[0]->setScale(0.75f);
		Relics_sprite[0]->setPosition(Vec2(35, 650));
		this->addChild(Relics_sprite[0]);
	}

	relics;
}
