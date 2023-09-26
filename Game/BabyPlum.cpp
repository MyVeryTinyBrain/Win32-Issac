#include "stdafx.h"
#include "BabyPlum.h"
#include "BabyPlumAnimator.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "MyGameObjectLayer.h"
#include "Player.h"
#include "Define.h"
#include "Projectile.h"
#include "Room.h"
#include "Pool.h"
#include "Brimston.h"
#include "SoundMgr.h"

void BabyPlum::setSize(Size* pSize)
{
    *pSize = Character::Size::Large;
}

void BabyPlum::setInitHP(float* pHP)
{
    *pHP = 100;
}

void BabyPlum::setCollider(Collider2D** pCollider, Collider2D** pHitTrigger)
{
    m_objParent = new GameObject(this->transform());
    m_objParent->transform()->setLocalPosition({});

    m_hitObj = new GameObject(m_objParent->transform());
    m_hitObj->transform()->setLocalPosition({});
    m_hitObj->setLayer(GO_LAYER_ENEMY);
    m_hit = m_hitObj->AddComponent<CircleCollider2D>();
    m_hit->setIsTrigger(true);
    m_hit->circle()->setRadius(21);
    m_hitObj->AddComponent<Collider2DRenderer>();

    *pHitTrigger = m_hit;
}

void BabyPlum::setRenderers(std::vector<SpriteRenderer*>* pRenderers)
{
    m_rendererObj = new GameObject(m_objParent->transform());
    m_rendererObj->transform()->setLocalPosition({});
    m_renderer = m_rendererObj->AddComponent<SpriteRenderer>();
    m_renderer->setRenderTag(RD_TAG_FLYING_OBJ);
    m_renderer->setRenderOrder(RD_ORDER_FLYING_OBJ_FLY);
    m_renderer->setFixedSize(false);
    m_renderer->setOriginSizeWhenDefixedSize(true);

    m_animator = m_rendererObj->AddComponent<BabyPlumAnimator>();
    m_animator->OnAwakeAnimated += Function<void>(this, &BabyPlum::OnAwakeAnimated);
    m_animator->OnReflectReadyAnimated += Function<void>(this, &BabyPlum::OnRelfectReadyAnimated);
    m_animator->OnStamped += Function<void>(this, &BabyPlum::OnStamped);
    m_animator->OnStampAnimated += Function<void>(this, &BabyPlum::OnStampAnimated);
    m_animator->OnSpinAnimated += Function<void>(this, &BabyPlum::OnSpinAnimated);
    m_animator->OnStamped2 += Function<void>(this, &BabyPlum::OnStamped2);
    m_animator->OnDefeatAnimated += Function<void>(this, &BabyPlum::OnDefeatAnimated);

    pRenderers->push_back(m_renderer);
}

void BabyPlum::LateAwake()
{
    m_speed = 35;
    m_hit->setEnable(false);
    m_body->setFriction(1.0f);
    m_body->setMass(0);

    m_targetPos = {};
    m_targetCaptureCounter = 0;
    m_targetCaptureDelay = 0.5f;

    m_shadowObj = new GameObject(this->transform());
    SpriteRenderer* shadowRenderer = m_shadowObj->AddComponent<SpriteRenderer>();
    shadowRenderer->setSprite(SpriteManager::Find(TEXT("shadow")));
    shadowRenderer->setRenderTag(RD_TAG_SHADOW);
    shadowRenderer->setFixedSize(false);
    shadowRenderer->setOriginSizeWhenDefixedSize(false);
    shadowRenderer->setAlphaMode(true);
    shadowRenderer->setAlpha(SHADOW_ALPHA);
    m_shadowObj->transform()->setSize({ 40,15 });
    m_shadowObj->transform()->setLocalPosition({ 0, -FLYING_HEIGHT - 10 });

    m_attackDelay = 2.0f;
    m_attackCounter = m_attackDelay;
    m_spinCount = 0;
    m_stampCount = 0;
    m_reflectCount = 0;
    m_stamp2Count = 0;

    m_lastStampShootAngle = 0;
    m_spinDir = {};
    m_spinShootCounter = 0;
    m_lastSpinShootAngle = 0;
    m_reflectShootCounter = 0;
    m_reflectCounter = 0;
}

void BabyPlum::OnCollision(Collider2D* collider)
{
}

void BabyPlum::OnTrigger(Collider2D* collider)
{
}

void BabyPlum::OnDamaged()
{
}

void BabyPlum::OnDead()
{
    GameObject* poolObj = new GameObject(center() + Vector2(0, -25));
    Pool* pool = poolObj->AddComponent<Pool>();
    pool->InitGenerate(Pool::Type::Blood, Pool::Size::Regular);

    m_shadowObj->setEnable(false);
    m_animator->SetReflectState(false);
    m_animator->PlayDefeat();

    CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::BGM);
    CSoundMgr::Get_Instance()->PlayBGM(L"m_catacombs.ogg");
}

void BabyPlum::Start()
{
    Monster::Start();

    CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::BGM);
    CSoundMgr::Get_Instance()->PlayBGM(L"m_chest room chapter 6.ogg");
}

Vector2 BabyPlum::center() const
{
    return m_objParent->transform()->position();
}

void BabyPlum::Update()
{
    Monster::Update();

    if (isDead())
        return;

    if (m_animator->isPlayingSpin())
    {
        m_body->AddImpulseToSpeed(m_spinDir, 200);
        m_spinShootCounter -= Global::deltaTime;
        if (m_spinShootCounter <= 0)
        {
            m_spinShootCounter = 0.05f;
            CreateBullet(90, 150, 0, m_lastSpinShootAngle, center() + Vector2(0, -15));
            m_lastSpinShootAngle += 20 * DEG2RAD;
        }
    }
    if (m_animator->isReflecting())
    {
        Vector2 vel = m_body->velocity();
        if (center().y > m_room->floorTop())
            vel.y = -fabsf(vel.y);
        else if (center().y < m_room->floorBottom())
            vel.y = fabsf(vel.y);
        if (center().x > m_room->floorRight())
            vel.x = -fabsf(vel.x);
        else if (center().x < m_room->floorLeft())
            vel.x = fabsf(vel.x);
        m_body->setVelocity(vel);

        Vector2 moveDir = vel.normalized();
        m_body->AddImpulseToSpeed(moveDir, 225);
        m_animator->SetDirection(m_animator->VectorToDirection(m_body->velocity()));

        m_reflectShootCounter -= Global::deltaTime;
        if (m_reflectShootCounter <= 0)
        {
            m_reflectShootCounter = 0.09f;
            float invMoveDirAngle = Vector2::Radian(Vector2::right(), -1 * moveDir);
            int randAreaAngle = 145;
            float addingAngle = (float)(rand() % randAreaAngle - randAreaAngle / 2) * DEG2RAD;
            CreateBullet(100, 175, 0, invMoveDirAngle + addingAngle, center());
        }

        m_reflectCounter -= Global::deltaTime;
        if (m_reflectCounter <= 0)
        {
            m_body->setVelocity(m_room->center() - center());
            m_animator->SetReflectState(false);
            m_animator->PlayIdle();
        }
    }

    if (m_animator->isPlayingAwake() || m_animator->isPlayingAttack())
        return;

    m_targetCaptureCounter -= Global::deltaTime;
    if (m_targetCaptureCounter <= 0)
    {
        m_targetCaptureCounter = m_targetCaptureDelay;
        m_targetPos = Player::instance()->headPosition();
    }
    Vector2 relVec = m_targetPos - center();
    Vector2 dir = relVec.normalized();
    m_body->AddImpulseToSpeed(dir, m_speed);

    m_attackCounter -= Global::deltaTime;
    if (m_attackCounter <= 0)
    {
        m_attackCounter = m_attackDelay;
        size_t attackCase = rand() % 4;
        switch (attackCase)
        {
            case 0:
                m_spinCount = 1;
                break;
            case 1:
                m_stampCount = 4;
                break;
            case 2:
                m_reflectCount = 1;
                break;
            case 3:
                m_stamp2Count = 1;
                break;
        }
    }
    if (m_spinCount > 0)
    {
        --m_spinCount;
        m_body->setVelocity({});
        m_spinDir = (m_room->center() - center()).normalized();
        m_lastSpinShootAngle = Vector2::Radian(Vector2::right(), m_spinDir) + 90 * DEG2RAD;
        m_spinShootCounter = 0;
        m_animator->PlaySpin();
    }
    else if (m_stampCount > 0)
    {
        --m_stampCount;
        m_body->setVelocity({});
        m_animator->PlayStamp();
    }
    else if (m_reflectCount > 0)
    {
        --m_reflectCount;
        float angle = (((rand() % 3 + 1) * 90) - 45) * DEG2RAD;
        m_body->setVelocity(Vector2::Direction(angle) * 50);
        m_reflectShootCounter = 0;
        m_reflectCounter = 4.5f;
        m_animator->PlayReflectReady();
    }
    else if (m_stamp2Count > 0)
    {
        --m_stamp2Count;
        m_body->setVelocity({});
        m_animator->PlayStamp2();
    }
}

void BabyPlum::OnAwakeAnimated()
{
    m_hit->setEnable(true);
}

void BabyPlum::OnRelfectReadyAnimated()
{
    m_animator->SetDirection(BabyPlumAnimator::Direction::RIGHTUP);
    m_animator->SetReflectState(true);
}

void BabyPlum::OnStamped()
{
    int cnt = 10;
    for (int i = 0; i < cnt; ++i)
    {
        float percent = (float)i / (float)cnt;
        CreateBullet(90, 250, 1, percent * TAU + m_lastStampShootAngle, center() + Vector2(0, -15));
    }
    m_lastStampShootAngle += 15 * DEG2RAD;

    GameObject* poolObj = new GameObject(center() + Vector2(0, -25));
    Pool* pool = poolObj->AddComponent<Pool>();
    pool->InitGenerate(Pool::Type::Blood, Pool::Size::Regular);

    CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::MONSTER);
    CSoundMgr::Get_Instance()->PlaySound(L"blobby wiggle 3.wav", CSoundMgr::CHANNELID::MONSTER);
}

void BabyPlum::OnStampAnimated()
{
}

void BabyPlum::OnSpinAnimated()
{
}

void BabyPlum::OnStamped2()
{
    Brimston* brimston[2];
    brimston[0] = CreateBrimston();
    brimston[1] = CreateBrimston();

    brimston[0]->gameObject()->setEnable(true);
    brimston[0]->transform()->setPosition(transform()->position() - Vector2(0, 10));
    brimston[0]->SetDirection(90 * DEG2RAD);
    brimston[0]->SetTargetDirection(180 * DEG2RAD);
    brimston[0]->setCounter(2.0f);

    brimston[1]->gameObject()->setEnable(true);
    brimston[1]->transform()->setPosition(transform()->position() - Vector2(0, 10));
    brimston[1]->SetDirection(270 * DEG2RAD);
    brimston[1]->SetTargetDirection(360 * DEG2RAD);
    brimston[1]->setCounter(2.0f);

    GameObject* poolObj = new GameObject(center() + Vector2(0, -25));
    Pool* pool = poolObj->AddComponent<Pool>();
    pool->InitGenerate(Pool::Type::Blood, Pool::Size::Regular);

    CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::MONSTER);
    CSoundMgr::Get_Instance()->PlaySound(L"blobby wiggle 3.wav", CSoundMgr::CHANNELID::MONSTER);
}

void BabyPlum::OnDefeatAnimated()
{
    this->gameObject()->Destroy();
}

Projectile* BabyPlum::CreateBullet(const float& speed, const float& range, const int& damage, const float& radian, const Vector2& position)
{
    Vector2 dir = Vector2::Direction(radian);

    GameObject* projectilObj = new GameObject(position);
    Projectile* projectile = projectilObj->AddComponent<Projectile>();
    projectile->InitSetType(Projectile::Type::Blood);
    projectile->InitSetDamage(damage == 0 ? (rand() % 3 + 1) : damage);
    projectile->InitSetRange(range);
    projectile->InitSetSpeed(speed);
    projectile->InitSetDirection(dir);
    projectile->InitSetTargetLayer(GO_LAYER_PLAYER);
    return projectile;
}

Brimston* BabyPlum::CreateBrimston()
{
    GameObject* obj = new GameObject(this->transform());
    Brimston* brimston = obj->AddComponent<Brimston>();
    brimston->setWidth(20);
    brimston->setTargetLayer(GO_LAYER_PLAYER);
    return brimston;
}
