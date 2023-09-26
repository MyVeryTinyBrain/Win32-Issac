#include "stdafx.h"
#include "UIHealthBar.h"
#include "MyRenderOrder.h"
#include "Character.h"
#include "MyExecutionOrder.h"

void UIHealthBar::Awake()
{
	m_hpObj = new GameObject(this->transform());
	m_hpObj->transform()->setLocalPosition({});
	m_hp = m_hpObj->AddComponent<SpriteRenderer>();
	m_hp->setRenderTag(RD_TAG_UI);
	m_hp->setRenderOrder(RD_ORDER_UI_HP);
	m_hp->setFixedSize(false);
	m_hp->setOriginSizeWhenDefixedSize(true);
	m_hp->setSprite(SpriteManager::Find(TEXT("ui_bosshealthbar/hp")));
	m_hpWidth = m_hp->sprite()->width();

	GameObject* barObj = new GameObject(this->transform());
	barObj->transform()->setLocalPosition({});
	m_bar = barObj->AddComponent<SpriteRenderer>();
	m_bar->setRenderTag(RD_TAG_UI);
	m_bar->setRenderOrder(RD_ORDER_UI_BAR);
	m_bar->setSprite(SpriteManager::Find(TEXT("ui_bosshealthbar/bar")));

	GameObject* skullObj = new GameObject(this->transform());
	m_skull = skullObj->AddComponent<SpriteRenderer>();
	m_skull->setRenderTag(RD_TAG_UI);
	m_skull->setRenderOrder(RD_ORDER_UI_SKULL);
	m_skull->setSprite(SpriteManager::Find(TEXT("ui_bosshealthbar/skull")));
	skullObj->transform()->setLocalPosition({-m_bar->sprite()->width() * 0.5f, 0});

	SetExecutionOrder(EX_ORDER_UI);

	if (g_healthBar == nullptr)
		g_healthBar = this;

	m_skull->setEnable(false);
	m_hp->setEnable(false);
	m_bar->setEnable(false);
	m_hideCounter = 0;
}

void UIHealthBar::Start()
{
}

void UIHealthBar::Update()
{
	Camera2D* mainCamera = Camera2D::mainCamera();
	if (mainCamera)
	{
		Vector2 center =
			mainCamera->transform()->position() +
			Vector2(0, -mainCamera->halfHeight()) +
			Vector2(0, m_bar->sprite()->height());
		transform()->setPosition(center);
	}
	else return;

	float percent = 0;
	if (m_target)
		percent = m_target->HP() / m_target->maxHP();
	m_hpObj->transform()->setLocalSize({ percent,1 });
	m_hpObj->transform()->setLocalPosition({ m_hpWidth * percent * 0.5f - m_hpWidth * 0.5f,0 });

	if (m_target == nullptr)
		m_hideCounter -= Global::deltaTime;
	if (m_hideCounter <= 0)
	{
		m_skull->setEnable(false);
		m_hp->setEnable(false);
		m_bar->setEnable(false);
	}
}

void UIHealthBar::LateUpdate()
{
}

void UIHealthBar::OnEnable()
{
}

void UIHealthBar::OnDisable()
{
}

void UIHealthBar::OnDestroy()
{
	if (g_healthBar == this)
		g_healthBar = nullptr;
}

void UIHealthBar::AddTarget(Character* character)
{
	if (m_target == character)
		return;
	if (character != nullptr && character->HP() == 0)
		return;

	ClearTargets();

	m_target = character;
	character->OnDeadCallback += Function<void, Character*>(this, &UIHealthBar::OnTargetDead);

	m_skull->setEnable(true);
	m_hp->setEnable(true);
	m_bar->setEnable(true);
	m_hideCounter = 1.0f;
}

void UIHealthBar::ClearTargets()
{
	if (m_target == nullptr)
		return;

	m_target->OnDeadCallback -= Function<void, Character*>(this, &UIHealthBar::OnTargetDead);
	m_target = nullptr;
}

void UIHealthBar::OnTargetDead(Character* character)
{
	ClearTargets();
}

UIHealthBar* UIHealthBar::g_healthBar = nullptr;

UIHealthBar* UIHealthBar::instance()
{
	return g_healthBar;
}
