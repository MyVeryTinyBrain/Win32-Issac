#include "stdafx.h"
#include "Player.h"
#include "PlayerHeadAnimator.h"
#include "PlayerBodyAnimator.h"
#include "MyRenderOrder.h"
#include "MyRenderTag.h"
#include "MyGameObjectLayer.h"
#include "Projectile.h"
#include "Bomb.h"
#include "Define.h"
#include "Placer.h"
#include "Brimston.h"
#include "SoundMgr.h"

void Player::setSize(Size* pSize)
{
	*pSize = Size::Regular;
}

void Player::setInitHP(float* pHP)
{
	*pHP = 3;
}

void Player::setCollider(Collider2D** pCollider, Collider2D** pHitTrigger)
{
	GameObject* colliderObj = new GameObject(this->transform());
	colliderObj->transform()->setLocalPosition({ 0,0 });
	colliderObj->setLayer(GO_LAYER_PLAYER);
	CircleCollider2D* circleCollider = colliderObj->AddComponent<CircleCollider2D>();
	circleCollider->circle()->setRadius(7);
	colliderObj->AddComponent<Collider2DRenderer>();
	*pCollider = circleCollider;

	GameObject* triggerObj = new GameObject(this->transform());
	triggerObj->transform()->setLocalPosition({ 0,8 });
	triggerObj->setLayer(GO_LAYER_PLAYER);
	RectCollider2D* rectTrigger = triggerObj->AddComponent<RectCollider2D>();
	rectTrigger->setIsTrigger(true);
	rectTrigger->rect()->setWidth(7);
	rectTrigger->rect()->setHeight(14);
	triggerObj->AddComponent<Collider2DRenderer>();
	*pHitTrigger = rectTrigger;
}

void Player::setRenderers(std::vector<SpriteRenderer*>* pRenderers)
{
	m_spriteParent = new GameObject(this->transform());
	m_spriteParent->transform()->setLocalPosition({});

	m_playerHeadObj = new GameObject(m_spriteParent->transform());
	m_playerHeadObj->transform()->setLocalPosition({ 0,14 });
	SpriteRenderer* headRenderer = m_playerHeadObj->AddComponent<SpriteRenderer>();
	headRenderer->setRenderTag(RD_TAG_OBJ);
	headRenderer->setRenderOrder(RD_ORDER_OBJ_HEAD);
	headRenderer->setFixedSize(false);
	m_headAnimator = m_playerHeadObj->AddComponent<PlayerHeadAnimator>();

	m_playerBodyObj = new GameObject(m_spriteParent->transform());
	m_playerBodyObj->transform()->setLocalPosition({});
	SpriteRenderer* bodyRenderer = m_playerBodyObj->AddComponent<SpriteRenderer>();
	bodyRenderer->setRenderTag(RD_TAG_OBJ);
	bodyRenderer->setRenderOrder(RD_ORDER_OBJ_BODY);
	bodyRenderer->setFixedSize(false);
	m_bodyAnimator = m_playerBodyObj->AddComponent<PlayerBodyAnimator>();

	pRenderers->push_back(headRenderer);
	pRenderers->push_back(bodyRenderer);
}

void Player::LateAwake()
{
	m_subHP = 3;

	g_instnace = this;

	m_speed = 150;
	m_invisibleTime = 0;

	GameObject* shadowObj = new GameObject(m_spriteParent->transform());
	shadowObj->transform()->setLocalPosition({ 0,-5 });
	SpriteRenderer* shadowRenderer = shadowObj->AddComponent<SpriteRenderer>();
	shadowRenderer->setSprite(SpriteManager::Find(TEXT("shadow")));
	shadowRenderer->setRenderTag(RD_TAG_SHADOW);
	shadowRenderer->setFixedSize(false);
	shadowRenderer->setOriginSizeWhenDefixedSize(false);
	shadowRenderer->setAlphaMode(true);
	shadowRenderer->setAlpha(SHADOW_ALPHA);
	shadowObj->transform()->setSize({ 20,10 });

	m_projShootCounter = 0;
	m_projDelay = 0.2f;
	m_damage = 1.0f;
	m_range = 150.0f;
	m_projSpeed = 200.0f;

	m_bomb = 3;
	m_coin = 5;
	m_key = 5;

	m_gotItemObj = new GameObject(this->transform());
	m_gotItemObj->transform()->setLocalPosition({ 0,30 });
	m_gotItemRenderer = m_gotItemObj->AddComponent<SpriteRenderer>();
	m_gotItemRenderer->setRenderTag(RD_TAG_EFFECT);
}

void Player::OnCollision(Collider2D* collider)
{
}

void Player::OnTrigger(Collider2D* collider)
{
	if (m_invisibleTime <= 0 && collider->gameObject()->layer() == GO_LAYER_ENEMY)
	{
		GameObject* obj = collider->body2D()->gameObject();
		Character* character = obj->GetComponent<Character>();
		if (character)
		{
			TakeDamage(1);
			Vector2 relVec = transform()->position() - character->transform()->position();
			Vector2 dir = relVec.normalized();
			m_body->AddImpulse(dir * 200);
		}
	}
}

void Player::OnDamaged()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::PLAYER);
	CSoundMgr::Get_Instance()->PlaySound(L"hurt grunt 2.wav", CSoundMgr::CHANNELID::PLAYER);
}

void Player::OnDead()
{
	Placer::g_shouldReset = true;
}

bool Player::ApplyDamage(float* pDamage)
{
	if (m_invisibleTime <= 0)
	{
		if (m_subHP > 0)
		{
			*pDamage = 0;
			m_subHP -= 1;
		}
		else
		{
			*pDamage = 1;
		}
		m_invisibleTime = 1.0f;
		return true;
	}
	else
	{
		return false;
	}
}

Vector2 Player::center() const
{
	return transform()->position() + Vector2(0, 10);
}

void Player::Update()
{
	Character::Update();

	Vector2 moveDir = {};
	if (Input::GetKey(Key::W))
		moveDir.y += 1;
	if (Input::GetKey(Key::S))
		moveDir.y -= 1;
	if (Input::GetKey(Key::A))
		moveDir.x -= 1;
	if (Input::GetKey(Key::D))
		moveDir.x += 1;
	moveDir.Normalize();
	m_body->AddImpulseToSpeed(moveDir, m_speed);
	m_bodyAnimator->SetState(PlayerBodyAnimator::BodyState::IDLE);
	if (moveDir.sqrMagnitude() > 0)
	{
		if (moveDir.y < 0)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::FORWARD);
			m_headAnimator->SetIdle(PlayerHeadAnimator::HeadDirection::FORWARD);
		}
		else if (moveDir.y > 0)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::BACKWARD);
			m_headAnimator->SetIdle(PlayerHeadAnimator::HeadDirection::BACKWARD);
		}
		else if (moveDir.x < 0)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::LEFT);
			m_headAnimator->SetIdle(PlayerHeadAnimator::HeadDirection::LEFT);
		}
		else if (moveDir.x > 0)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::RIGHT);
			m_headAnimator->SetIdle(PlayerHeadAnimator::HeadDirection::RIGHT);
		}
		m_bodyAnimator->SetState(PlayerBodyAnimator::BodyState::WALK);
	}

	if (m_projShootCounter > 0)
	{
		m_projShootCounter -= Global::deltaTime;
	}
	Vector2 shootDir = {};
	if (Input::GetKey(Key::Left) || Input::GetKey(Key::Right))
	{
		shootDir.x = Input::GetKey(Key::Left) ? -1.0f : +1.0f;
	}
	else if (Input::GetKey(Key::Down) || Input::GetKey(Key::Up))
	{
		shootDir.y = Input::GetKey(Key::Down) ? -1.0f : +1.0f;
	}
	shootDir.Normalize();
	if (!m_isBrimston)
	{
		if (m_projShootCounter <= 0 && shootDir.sqrMagnitude() > 0)
		{
			m_projShootCounter = m_projDelay;

			Vector2 projDir = shootDir;
			if (shootDir.y != 0)
			{
				if (moveDir.x < 0) projDir.x -= 0.2f;
				else if (moveDir.x > 0) projDir.x += 0.2f;
			}
			else if (shootDir.x != 0)
			{
				if (moveDir.y < 0) projDir.y -= 0.2f;
				else if (moveDir.y > 0) projDir.y += 0.2f;
			}
			projDir.Normalize();

			GameObject* projectilObj = new GameObject(m_playerHeadObj->transform()->position());
			Projectile* projectile = projectilObj->AddComponent<Projectile>();
			projectile->InitSetType(Projectile::Type::Normal);
			projectile->InitSetDamage((int)m_damage);
			projectile->InitSetRange(m_range);
			projectile->InitSetSpeed(m_projSpeed);
			projectile->InitSetDirection(projDir);
			projectile->InitSetTargetLayer(GO_LAYER_ENEMY);

			if (shootDir.y < 0)
			{
				m_headAnimator->SetClose(PlayerHeadAnimator::HeadDirection::FORWARD);
			}
			else if (shootDir.y > 0)
			{
				m_headAnimator->SetClose(PlayerHeadAnimator::HeadDirection::BACKWARD);
			}
			else if (shootDir.x < 0)
			{
				m_headAnimator->SetClose(PlayerHeadAnimator::HeadDirection::LEFT);
			}
			else if (shootDir.x > 0)
			{
				m_headAnimator->SetClose(PlayerHeadAnimator::HeadDirection::RIGHT);
			}
		}
	}
	else
	{
		if (shootDir.sqrMagnitude() > 0)
		{
			if (shootDir.y < 0)
			{
				m_headAnimator->setDirection(PlayerHeadAnimator::HeadDirection::FORWARD);
			}
			else if (shootDir.y > 0)
			{
				m_headAnimator->setDirection(PlayerHeadAnimator::HeadDirection::BACKWARD);
			}
			else if (shootDir.x < 0)
			{
				m_headAnimator->setDirection(PlayerHeadAnimator::HeadDirection::LEFT);
			}
			else if (shootDir.x > 0)
			{
				m_headAnimator->setDirection(PlayerHeadAnimator::HeadDirection::RIGHT);
			}
			m_headAnimator->Charge();
			m_headAnimator->SetChargeSpeed(1.0f / (m_projDelay / 0.2f));
		}
		if (Input::GetKeyUp(Key::Left) || Input::GetKeyUp(Key::Up) || Input::GetKeyUp(Key::Right) || Input::GetKeyUp(Key::Down))
		{
			bool keyState = Input::GetKey(Key::Left) || Input::GetKey(Key::Up) || Input::GetKey(Key::Right) || Input::GetKey(Key::Down);
			if (keyState == false)
			{
				if (m_headAnimator->StopChargeOrFire())
				{
					m_headAnimator->SetFireSpeed(1.0f);

					float brimstonAngle = 0;
					switch (m_headAnimator->direction())
					{
						case PlayerHeadAnimator::HeadDirection::RIGHT:
							brimstonAngle = 0;
							break;
						case PlayerHeadAnimator::HeadDirection::BACKWARD:
							brimstonAngle = 90 * DEG2RAD;
							break;
						case PlayerHeadAnimator::HeadDirection::LEFT:
							brimstonAngle = 180 * DEG2RAD;
							break;
						case PlayerHeadAnimator::HeadDirection::FORWARD:
							brimstonAngle = 270 * DEG2RAD;
							break;
					}
					Brimston* brimston = CompGenerate<Brimston>(headPosition(), this->transform());
					brimston->setTargetLayer(GO_LAYER_ENEMY);
					brimston->setDisableWhenCounterOver(true);
					brimston->setCounter(1);
					brimston->SetDirection(brimstonAngle);
					brimston->SetTargetDirection(brimstonAngle);
					brimston->setDamage(0.5f * m_damage);
					brimston->setWidth(10 * m_damage);
				}
			}
		}
	}

	if (Input::GetKeyDown(Key::E) && m_bomb > 0)
	{
		GameObject* bombObj = new GameObject(this->transform()->position());
		bombObj->AddComponent<Bomb>();
		--m_bomb;
	}

	const float clickDelay = 0.1f;
	if (m_invisibleTime > 0)
	{
		m_invisibleTime -= Global::deltaTime;
		//bool show = (int)(m_invisibleTime * (1.0f / clickDelay)) % 2 == 0;
		bool show = fmodf(m_invisibleTime / clickDelay, 2) / 2 > 0.5f;
		m_playerHeadObj->setEnable(show);
		m_playerBodyObj->setEnable(show);
		if (m_invisibleTime <= 0)
		{
			m_invisibleTime = 0;
			m_playerHeadObj->setEnable(true);
			m_playerBodyObj->setEnable(true);
		}
	}
}

void Player::LateUpdate()
{
	Character::LateUpdate();

	if (m_gotItemRenderer->sprite() != nullptr && m_bodyAnimator->isPlayingGotItem() == false)
	{
		m_gotItemRenderer->setSprite(nullptr);
	}
}

const Vector2& Player::headPosition() const
{
	return m_playerHeadObj->transform()->position();
}

const float& Player::subHP() const
{
	return m_subHP;
}

void Player::SetSubHP(const float& SubHP)
{
	m_subHP = SubHP;
}

const size_t& Player::bomb() const
{
	return m_bomb;
}

void Player::setBomb(const size_t& Bomb)
{
	m_bomb = Bomb;
}

const size_t& Player::coin() const
{
	return m_coin;
}

void Player::setCoin(const size_t& Coin)
{
	m_coin = Coin;
}

const size_t& Player::key() const
{
	return m_key;
}

void Player::setKey(const size_t& Key)
{
	if (Key < m_key)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::KEY);
		CSoundMgr::Get_Instance()->PlaySound(L"unlock.wav", CSoundMgr::CHANNELID::KEY);
	}
	m_key = Key;
}

const float& Player::shootDelay() const
{
	return m_projDelay;
}

void Player::setShootDelay(const float& value)
{
	m_projDelay = value;
}

const float& Player::damage() const
{
	return m_damage;
}

void Player::setDamage(const float& value)
{
	m_damage = value;
}

const float& Player::range() const
{
	return m_range;
}

void Player::setRange(const float& value)
{
	m_range = value;
}

const float& Player::projectileSpeed() const
{
	return m_projSpeed;
}

void Player::setProjectileSpeed(const float& value)
{
	m_projSpeed = value;
}

void Player::GotItem(Sprite* itemSprite)
{
	m_headAnimator->PlayGotItem();
	m_bodyAnimator->PlayGotItem();
	m_gotItemRenderer->setSprite(itemSprite);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::GOTITEM);
	CSoundMgr::Get_Instance()->PlaySound(L"choir.wav", CSoundMgr::CHANNELID::GOTITEM);
}

void Player::setToBrimston(const bool& value)
{
	if (m_isBrimston == value)
		return;
	m_isBrimston = value;
	m_headAnimator->setIsBrimston(true);
	m_bodyAnimator->setIsBrimston(true);
}

Player* Player::instance()
{
	return g_instnace;
}

Player* Player::g_instnace = nullptr;