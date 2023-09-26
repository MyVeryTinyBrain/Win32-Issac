#include "stdafx.h"
#include "Brimston.h"
#include "BrimstonCorner.h"
#include "BrimstonBeam.h"
#include "BrimstonHit.h"
#include "MyGameObjectLayer.h"
#include "SoundMgr.h"

void Brimston::Awake()
{
    m_vertexCount = 4;
    m_width = 10;

    m_dir = { 1,0 };
    m_dirAngle = 0;
    m_targetDirAngle = 0;

    m_beg = {};
    m_mid = {};
    m_end = {};

    m_targetEnd = {};
    m_targetMid = {};
    m_lastHitCollider = nullptr;
    m_lastHitPoint = {};

    m_lineRendererObj = new GameObject(this->transform());
    m_lineRendererObj->transform()->setLocalPosition({});
    m_lineRenderer = gameObject()->AddComponent<LineRenderer>();
    m_lineRenderer->setRenderTag(RD_TAG_DEBUG);

    m_targetLayer = GO_LAYER_ENEMY;
    m_damage = 0.5f;

    m_stopCounter = false;
    setCounter(1.5f);
    m_disableWhenCounterOver = true;

    m_lerpPower = 5;
}

void Brimston::Start()
{
    CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::BRIMSTON);
    CSoundMgr::Get_Instance()->PlaySound(L"blood laser short 2.wav", CSoundMgr::CHANNELID::BRIMSTON);
}

void Brimston::Update()
{
    if (!m_stopCounter)
    {
        m_counter -= Global::deltaTime;
        if (m_counter <= 0)
        {
            m_counter = 0;
            if (m_disableWhenCounterOver)
            {
                for (auto& e : m_beams)
                    e->gameObject()->setEnable(false);
                for (auto& e : m_corners)
                    e->gameObject()->setEnable(false);
                if (m_hitEffect)
                    m_hitEffect->gameObject()->setEnable(false);
                gameObject()->setEnable(false);

            }
            else
            {
                gameObject()->Destroy();
            }
            return;
        }
    }

    m_beg = transform()->position();

    m_dirAngle = LerpAngle(m_dirAngle, m_targetDirAngle, m_lerpPower * Global::deltaTime);
    m_dir = Vector2::Direction(m_dirAngle);
    SetTargetMidAndTargetEnd();

    //m_mid = Vector2::Lerp(m_mid, m_targetMid, 10.0f * Global::deltaTime);
    //m_end = Vector2::Lerp(m_end, m_targetEnd, 5.0f * Global::deltaTime);

    m_mid = m_targetMid;
    m_end = Vector2::Lerp(m_end, m_targetEnd, m_lerpPower * Global::deltaTime);

    //m_mid = Vector2::Lerp(m_mid, m_targetMid, 5.0f * Global::deltaTime);
    //m_end = m_targetEnd;

    //ShowBezierCurve(m_vertexCount);

    float bezierLength = BezierCurveLength();
    if (m_vertexCount < 2)
        m_vertexCount = 2;
    size_t i;
    for (i = 0; i < m_vertexCount; ++i)
    {
        float per = (float)i / (float)(m_vertexCount - 1);
        PlaceCorner(i, per);
        if (i > 0) PlaceBeam(i - 1, i);
        PlaceHit();
    }
    for (size_t j = i; j < m_corners.size(); ++j)
        m_corners[j]->gameObject()->setEnable(false);
    for (size_t j = i; j < m_beams.size() - 1; ++j)
        m_beams[j]->gameObject()->setEnable(false);
}

void Brimston::LateUpdate()
{
}

void Brimston::OnEnable()
{
}

void Brimston::OnDisable()
{
}

void Brimston::OnDestroy()
{
    for (auto& e : m_beams)
        e->gameObject()->Destroy();
    m_beams.clear();
    for (auto& e : m_corners)
        e->gameObject()->Destroy();
    m_corners.clear();
    if (m_hitEffect)
    {
        m_hitEffect->gameObject()->Destroy();
        m_hitEffect = nullptr;
    }
}

Vector2 Brimston::BezierCurve(const float& t)
{
    Vector2 u1 = Vector2::Lerp(m_beg, m_mid, t);
    Vector2 u2 = Vector2::Lerp(m_mid, m_end, t);
    Vector2 v1 = Vector2::Lerp(u1, u2, t);
    return v1;
}

float Brimston::BezierCurveLength()
{
    return BezierCurveLength(1);
}

float Brimston::BezierCurveLength(const float& t)
{
    float length = 0;
    const size_t slice = 100;
    Vector2 prev = m_beg;
    for (size_t i = 1; i <= slice; ++i)
    {
        float per = t * (float)i / (float)slice;
        Vector2 cur = BezierCurve(per);
        length += (cur - prev).magnitude();
        prev = cur;
    }
    return length;
}

Vector2 Brimston::BezierCurveDirection(const float& t)
{
    float& a = m_beg.x;
    float& b = m_mid.x;
    float& c = m_end.x;
    float& u = m_beg.y;
    float& v = m_mid.y;
    float& w = m_end.y;
    float j = 2 * (b - a) + 2 * t * (a - 2 * b + c);
    float k = 2 * (v - u) + 2 * t * (u - 2 * v + w);
    return Vector2(j, k).normalized();
}

void Brimston::SetTargetMidAndTargetEnd()
{
    bool layers[GO_LAYER_MAX] = {};
    layers[GO_LAYER_PROJ_WALL] = true;
    layers[GO_LAYER_OBJECT] = true;
    RaycastResult result = {};
    if (Physics2D::Raycast(m_beg, m_dir, 1500, layers, &result))
    {
        m_targetEnd = result.ContactPoint;
        m_targetMid = (m_beg + m_targetEnd) * 0.5f;
        if (result.Collider != m_lastHitCollider)
        {
            if (m_lastHitCollider != NULL &&
                result.Collider->gameObject()->layer() == m_lastHitCollider->gameObject()->layer())
                return;

            m_lastHitCollider = result.Collider;
            m_end = m_targetEnd;
        }
    }
    else
    {
        m_targetEnd = m_beg + m_dir * 1500;
        m_targetMid = (m_beg + m_targetEnd) * 0.5f;
    }
}

float Brimston::Lerp(const float& a, const float& b, const float& t)
{
    return a + (b - a) * t;
}

float Brimston::LerpAngle(float a, float b, const float& t)
{
    float result;
    float diff = b - a;
    if (diff < -PI)
    {
        b += TAU;
        result = Lerp(a, b, t);
        if (result >= TAU)
        {
            result -= TAU;
        }
    }
    else if (diff > PI)
    {
        b -= TAU;
        result = Lerp(a, b, t);
        if (result < 0.f)
        {
            result += TAU;
        }
    }
    else
    {
        result = Lerp(a, b, t);
    }
    return result;
}

BrimstonCorner* Brimston::CreateCorner()
{
    GameObject* obj = new GameObject(this->transform());
    return obj->AddComponent<BrimstonCorner>();
}

BrimstonBeam* Brimston::CreateBeam()
{
    GameObject* obj = new GameObject(this->transform());
    return obj->AddComponent<BrimstonBeam>();
}

void Brimston::ShowBezierCurve(const size_t& vertexCount)
{
    m_lineRenderer->ClearWorldVertex();
    int vmax = (int)vertexCount;
    for (int i = 0; i <= vmax; ++i)
    {
        float t = (float)i / (float)vmax;
        m_lineRenderer->addWorldVertex(BezierCurve(t));
    }
}

void Brimston::PlaceCorner(const int& index, const float& t)
{
    //if (m_corners.size() <= index)
    //    m_corners.push_back(CreateCorner());
    //if (index == 0 || index == m_vertexCount - 1)
    //    m_corners[index]->gameObject()->setEnable(true);
    //else 
    //    m_corners[index]->gameObject()->setEnable(false);
    //m_corners[index]->transform()->setPosition(BezierCurve(t));
    //m_corners[index]->SetRadius(m_width);
    //m_corners[index]->SetOrder(index);

    if (m_corners.size() <= (size_t)index)
        m_corners.push_back(CreateCorner());
    m_corners[index]->gameObject()->setEnable(true);
    float percent = m_counter / m_counterMax;
    if (index == 0)
    {
        m_corners[index]->SetRadius(m_width * percent);
        m_corners[index]->SetOrder(index + 100);
    }
    else if (index == m_vertexCount - 1)
    {
        m_corners[index]->gameObject()->setEnable(false);
    }
    else
    {
        m_corners[index]->SetRadius(m_width * 0.8f * percent);
        m_corners[index]->SetOrder(index);
    }
    m_corners[index]->transform()->setPosition(BezierCurve(t));
}

void Brimston::PlaceBeam(const int& indexA, const int& indexB)
{
    if (m_beams.size() <= (size_t)indexA)
        m_beams.push_back(CreateBeam());
    float percent = m_counter / m_counterMax;
    Vector2 a = m_corners[indexA]->transform()->position();
    Vector2 b = m_corners[indexB]->transform()->position();
    if (indexA == 0) a += (b - a).normalized() * m_width * 0.5f * percent;
    if (indexA == m_vertexCount - 2) b += (a - b).normalized() * m_width * 0.5f * percent;
    m_beams[indexA]->SetTwoPoints(a, b);
    m_beams[indexA]->SetWidth(m_width * percent);
    m_beams[indexA]->SetOrder(indexA);
    m_beams[indexA]->setTargetLayer(m_targetLayer);
    m_beams[indexA]->setDamage(m_damage);
    m_beams[indexA]->gameObject()->setEnable(true);
}

void Brimston::PlaceHit()
{
    if (m_hitEffect == nullptr)
    {
        GameObject* hitObj = new GameObject();
        m_hitEffect = hitObj->AddComponent<BrimstonHit>();
    }
    Vector2 dir = BezierCurveDirection(1);
    m_hitEffect->transform()->setPosition(BezierCurve(1) - dir * 5);
    m_hitEffect->transform()->setAngle(Vector2::Radian(Vector2::right(), dir) - 90 * DEG2RAD);
    float percent = m_counter / m_counterMax;
    m_hitEffect->SetRadius(m_width * percent);
    m_hitEffect->gameObject()->setEnable(true);
}

void Brimston::SetDirection(const float& Angle)
{
    m_beg = transform()->position();
    m_dir = Vector2::Direction(Angle);
    m_dirAngle = Angle;
    m_targetDirAngle = Angle;
    SetTargetMidAndTargetEnd();
    m_mid = m_targetMid;
    m_end = m_targetEnd;
}

void Brimston::SetDirection(const Vector2& Direction)
{
    m_beg = transform()->position();
    m_dir = Direction;
    m_dirAngle = Vector2::Radian(Vector2::right(), Direction);
    m_targetDirAngle = m_dirAngle;
    SetTargetMidAndTargetEnd();
    m_mid = m_targetMid;
    m_end = m_targetEnd;
}

void Brimston::SetTargetDirection(const float& TargetAngle)
{
    m_targetDirAngle = TargetAngle;
}

void Brimston::SetTargetDirection(const Vector2& TargetDirection)
{
    m_targetDirAngle = Vector2::Radian(Vector2::right(), TargetDirection);
}

const unsigned char& Brimston::targetLayer() const
{
    return m_targetLayer;
}

void Brimston::setTargetLayer(const unsigned char& TargetLayer)
{
    m_targetLayer = TargetLayer;
}

void Brimston::setDamage(const float& damage)
{
    m_damage = damage;
}

void Brimston::setCounter(const float& time)
{
    m_counterMax = m_counter = time;
}

void Brimston::setUseCounter(const bool& enable)
{
    m_stopCounter = !enable;
}

void Brimston::setDisableWhenCounterOver(const bool& enable)
{
    m_disableWhenCounterOver = enable;
}

void Brimston::setWidth(const float& width)
{
    m_width = width;
}

void Brimston::setLerpPower(const float& power)
{
    m_lerpPower = power;
}

void Brimston::setVertexCount(const size_t& count)
{
    m_vertexCount = count;
}
