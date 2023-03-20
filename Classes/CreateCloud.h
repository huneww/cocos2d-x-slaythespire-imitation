#pragma once
#include "cocos2d.h"

class CreateCloud : public cocos2d::Scene
{
public:
	void Createcloud();

	CREATE_FUNC(CreateCloud);

private:

	void CloudAnimation_1(float dt);
	void CloudAnimation_2(float dt);
	void RemoveCloud();
};