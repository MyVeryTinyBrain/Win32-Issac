#include "stdafx.h"
#include "UICollectibles.h"
#include "MyExecutionOrder.h"
#include "Player.h"

void UICollectibles::Awake()
{
	SetExecutionOrder(EX_ORDER_UI);

	m_coin = SpriteManager::Find(TEXT("pickup_002_coin/01"));
	m_bomb = SpriteManager::Find(TEXT("pickup_016_bomb/default"));
	m_key = SpriteManager::Find(TEXT("pickup_003_charged_key"));

	GameObject* coinRendObj = new GameObject(this->transform());
	coinRendObj->transform()->setLocalPosition({ 0, 0 });
	coinRendObj->transform()->setLocalSize({ 0.8f, 0.8f });
	m_coinSpriteRenderer = coinRendObj->AddComponent<SpriteRenderer>();
	m_coinSpriteRenderer->setSprite(m_coin);
	m_coinSpriteRenderer->setRenderTag(RD_TAG_UI);
	m_coinSpriteRenderer->setFixedSize(false);

	GameObject* bombRendObj = new GameObject(this->transform());
	bombRendObj->transform()->setLocalPosition({-1, -15});
	bombRendObj->transform()->setLocalSize({ 0.8f, 0.8f });
	m_bombSpriteRenderer = bombRendObj->AddComponent<SpriteRenderer>();
	m_bombSpriteRenderer->setSprite(m_bomb);
	m_bombSpriteRenderer->setRenderTag(RD_TAG_UI);
	m_bombSpriteRenderer->setFixedSize(false);

	GameObject* keyRendObj = new GameObject(this->transform());
	keyRendObj->transform()->setLocalPosition({0, -30});
	keyRendObj->transform()->setLocalSize({ 0.8f, 0.6f });
	m_keySpriteRenderer = keyRendObj->AddComponent<SpriteRenderer>();
	m_keySpriteRenderer->setSprite(m_key);
	m_keySpriteRenderer->setRenderTag(RD_TAG_UI);
	m_keySpriteRenderer->setFixedSize(false);

	GameObject* coinCountObj = new GameObject(this->transform());
	coinCountObj->transform()->setLocalPosition({ 10, 0 });
	coinCountObj->transform()->setLocalSize({ 1, 1 });
	m_coinCountRenderer = coinCountObj->AddComponent<TextRenderer>();
	m_coinCountRenderer->setColor(RGB(255, 255, 255));
	m_coinCountRenderer->setFontName(TEXT("Upheaval"));
	m_coinCountRenderer->setText(TEXT("0"));
	m_coinCountRenderer->setFontSize(15);
	m_coinCountRenderer->setFontWidth(1000);

	GameObject* bombCountObj = new GameObject(this->transform());
	bombCountObj->transform()->setLocalPosition({ 10, -15 });
	m_bombCountRenderer = bombCountObj->AddComponent<TextRenderer>();
	m_bombCountRenderer->setColor(RGB(255, 255, 255));
	m_bombCountRenderer->setFontName(TEXT("Upheaval"));
	m_bombCountRenderer->setText(TEXT("0"));
	m_bombCountRenderer->setFontSize(15);
	m_bombCountRenderer->setFontWidth(1000);

	GameObject* keyCountObj = new GameObject(this->transform());
	keyCountObj->transform()->setLocalPosition({ 10, -30 });
	m_keyCountRenderer = keyCountObj->AddComponent<TextRenderer>();
	m_keyCountRenderer->setColor(RGB(255, 255, 255));
	m_keyCountRenderer->setFontName(TEXT("Upheaval"));
	m_keyCountRenderer->setText(TEXT("0"));
	m_keyCountRenderer->setFontSize(15);
	m_keyCountRenderer->setFontWidth(1000);

	m_prevCoin = 0;
	m_prevBomb = 0;
	m_prevKey = 0;
}

void UICollectibles::Start()
{
}

void UICollectibles::Update()
{
	Camera2D* mainCamera = Camera2D::mainCamera();
	if (!mainCamera)
		return;

	float posX = mainCamera->transform()->position().x - mainCamera->horizontal() * 0.5f + 10;
	float posY = mainCamera->transform()->position().y + mainCamera->vertical() * 0.5f - 23;
	transform()->setPosition({ posX,posY });

	Player* player = Player::instance();
	if (!player)
		return;

	if (m_prevCoin != player->coin())
	{
		m_prevCoin = player->coin();
		TCHAR str[128]{};
		_stprintf_s(str, 128, TEXT("%u"), m_prevCoin);
		m_coinCountRenderer->setText(str);
	}
	if (m_prevBomb != player->bomb())
	{
		m_prevBomb = player->bomb();
		TCHAR str[128]{};
		_stprintf_s(str, 128, TEXT("%u"), m_prevBomb);
		m_bombCountRenderer->setText(str);
	}
	if (m_prevKey != player->key())
	{
		m_prevKey = player->key();
		TCHAR str[128]{};
		_stprintf_s(str, 128, TEXT("%u"), m_prevKey);
		m_keyCountRenderer->setText(str);
	}
}

void UICollectibles::LateUpdate()
{
}

void UICollectibles::OnEnable()
{
}

void UICollectibles::OnDisable()
{
}

void UICollectibles::OnDestroy()
{
}
