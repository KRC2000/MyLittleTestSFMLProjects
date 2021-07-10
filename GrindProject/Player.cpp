#include "Player.h"

Player::Player(b2World& world, const Time& globalTime) :gTime(&globalTime)
{
	rect.setOrigin(32 / 2, 32 / 2);

	float scale = 32;
	shape.m_radius = 16 / scale;

	bdef.type = b2_dynamicBody;
	bdef.userData.pointer = (uintptr_t)&name;
	bdef.position.Set(32 / scale, 32 / scale);

	body = world.CreateBody(&bdef);
	body->IsBullet();
	body->CreateFixture(&shape, 2);

	body->GetFixtureList()->SetFriction(1);
	body->SetFixedRotation(true);
}

void Player::jump()
{
	body->ApplyLinearImpulseToCenter({ 0, -10.f }, true);
	jumpStartTimestamp = *gTime;
}
