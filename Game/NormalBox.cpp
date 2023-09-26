#include "stdafx.h"
#include "NormalBox.h"
#include "Player.h"

#include "ItemBlueHeart.h"
#include "ItemBomb.h"
#include "ItemCoin.h"
#include "ItemKey.h"
#include "ItemRedHeart.h"

void NormalBox::SetCanGetItem(bool* pCanGetItem)
{
    *pCanGetItem = false;
}

void NormalBox::SetSprites(Sprite** pDefault, Sprite** pChanged)
{
    *pDefault = SpriteManager::Find(TEXT("pickup_005_chests/normal_closed"));
    *pChanged = SpriteManager::Find(TEXT("pickup_005_chests/normal_open"));
}

void NormalBox::SetCollider(Collider2D** pCollider)
{
    RectCollider2D* collider = gameObject()->AddComponent<RectCollider2D>();
    collider->rect()->setWidth(10);
    collider->rect()->setHeight(10);
    gameObject()->AddComponent<Collider2DRenderer>();
    *pCollider = collider;
}

void NormalBox::SetBody2DProperty(Body2D* body)
{
}

void NormalBox::LateAwake()
{
}

void NormalBox::Update()
{
}

void NormalBox::OnPlayerCollision(Player* player)
{
    if (isShowingItem())
        return;

    if (player->key() > 0)
    {
        player->setKey(player->key() - 1);
        ToShowItem();
    }
}

void NormalBox::GiveAbilityToPlayer(Player* player)
{
    size_t r = rand() % 5;
    switch (r)
    {
        case 0:
            CompGenerate<ItemBlueHeart>(this->transform()->position() + Vector2(0, 10), this->transform()->parent());
            break;
        case 1:
            CompGenerate<ItemBomb>(this->transform()->position() + Vector2(0, 10), this->transform()->parent());
            break;
        case 2:
            CompGenerate<ItemCoin>(this->transform()->position() + Vector2(0, 10), this->transform()->parent());
            CompGenerate<ItemCoin>(this->transform()->position() + Vector2(0, -10), this->transform()->parent());
            CompGenerate<ItemCoin>(this->transform()->position() + Vector2(10, 0), this->transform()->parent());
            CompGenerate<ItemCoin>(this->transform()->position() + Vector2(-10, 0), this->transform()->parent());
            break;
        case 3:
            CompGenerate<ItemKey>(this->transform()->position() + Vector2(0, 10), this->transform()->parent());
            CompGenerate<ItemKey>(this->transform()->position() + Vector2(0, -10), this->transform()->parent());
            break;
        case 4:
            CompGenerate<ItemRedHeart>(this->transform()->position() + Vector2(0, 10), this->transform()->parent());
            break;
    }
}
