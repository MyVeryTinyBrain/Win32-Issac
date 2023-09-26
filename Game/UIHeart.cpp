#include "stdafx.h"
#include "UIHeart.h"
#include "Player.h"
#include "MyExecutionOrder.h"

void UIHeart::Awake()
{
	m_redFull = SpriteManager::Find(TEXT("ui_hearts/red_full"));
	m_redHalf = SpriteManager::Find(TEXT("ui_hearts/red_half"));
	m_redEmpty = SpriteManager::Find(TEXT("ui_hearts/red_empty"));
	m_blueFull = SpriteManager::Find(TEXT("ui_hearts/blue_full"));
	m_blueHalf = SpriteManager::Find(TEXT("ui_hearts/blue_half"));

	m_lastRedMax = 0;
	m_lastRed = 0;
	m_lastBlue = 0;

	SetExecutionOrder(EX_ORDER_UI);
}

void UIHeart::Start()
{
}

void UIHeart::Update()
{
	Player* player = Player::instance();
	if (!player)
		return;

	bool hpChanged = false;
	if (m_lastRedMax != player->maxHP() || m_lastRed != player->HP() || m_lastBlue != player->subHP())
	{
		hpChanged = true;
		m_lastRedMax = player->maxHP();
		m_lastRed = player->HP();
		m_lastBlue = player->subHP();
		PlaceHearts();
	}

	Camera2D* mainCamera = Camera2D::mainCamera();
	if (!mainCamera)
		return;
	float posX = mainCamera->transform()->position().x - mainCamera->horizontal() * 0.5f + 3;
	float posY = mainCamera->transform()->position().y + mainCamera->vertical() * 0.5f - 3;
	transform()->setPosition({ posX,posY });
}

void UIHeart::LateUpdate()
{
}

void UIHeart::OnEnable()
{
}

void UIHeart::OnDisable()
{
}

void UIHeart::OnDestroy()
{
}

void UIHeart::PlaceHearts()
{
	size_t redMax = (int)m_lastRedMax;
	size_t redFull = (int)m_lastRed;
	size_t redHalf = (m_lastRed - (int)m_lastRed > 0 ? 1 : 0);
	size_t redEmpty = (int)m_lastRedMax - redFull - redHalf;
	size_t blueFull = (int)m_lastBlue;
	size_t blueHalf = (m_lastBlue - (int)m_lastBlue > 0 ? 1 : 0);
	size_t hearts = redMax + blueFull + blueHalf;

	for (size_t i = m_icons.size(); i < hearts; ++i)
	{
		GameObject* heartIconObj = new GameObject(this->transform());
		float localX = i * m_redEmpty->width() + m_redEmpty->width() * 0.5f;
		float localY = -m_redEmpty->height() * 0.5f;
		heartIconObj->transform()->setLocalPosition({ localX , localY });
		SpriteRenderer* renderer = heartIconObj->AddComponent<SpriteRenderer>();
		renderer->setRenderTag(RD_TAG_UI);
		m_icons.push_back(renderer);
	}

	size_t idx = 0;
	for (size_t i = 0; i < redFull; ++i)
		m_icons[idx++]->setSprite(m_redFull);
	for (size_t i = 0; i < redHalf; ++i)
		m_icons[idx++]->setSprite(m_redHalf);
	for (size_t i = 0; i < redEmpty; ++i)
		m_icons[idx++]->setSprite(m_redEmpty);
	for (size_t i = 0; i < blueFull; ++i)
		m_icons[idx++]->setSprite(m_blueFull);
	for (size_t i = 0; i < blueHalf; ++i)
		m_icons[idx++]->setSprite(m_blueHalf);
	for (size_t i = idx; i < m_icons.size(); ++i)
		m_icons[i]->setSprite(nullptr);
}
