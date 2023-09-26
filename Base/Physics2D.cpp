#include "BaseStdafx.h"
#include "Physics2D.h"
#include "Body2D.h"
#include "Collider2D.h"
#include "GameObject.h"
#include "Transform.h"
#include "Shape2D.h"
#include "Delegate.h"
#include "Circle2D.h"
#include "Line2D.h"

Physics2D::pVecPBody2D_t Physics2D::g_bodyTargets = nullptr;
Physics2D::pArrVecPCollider2D_t Physics2D::g_colliderTargets = nullptr;
bool Physics2D::g_collisionLayer[GO_LAYER_MAX][GO_LAYER_MAX] = {};

void Physics2D::SetAllOffCollisionLayer()
{
	for (auto& layer : g_collisionLayer)
		for (auto& e : layer)
			e = false;
}

void Physics2D::SetCollisionLayer(const unsigned char& layer1, const unsigned char& layer2, const bool& collision)
{
	g_collisionLayer[layer1][layer2] = collision;
	g_collisionLayer[layer2][layer1] = collision;
}

void Physics2D::Reset()
{
	for (auto& layer : g_collisionLayer)
		for (auto& e : layer)
			e = true;
	g_bodyTargets = nullptr;
	g_colliderTargets = nullptr;
}

void Physics2D::SetProcessDatas(std::vector<Body2D*>* pBodyTargets, std::vector<Collider2D*>(*pColliderTargets)[GO_LAYER_MAX])
{
	g_bodyTargets = pBodyTargets;
	g_colliderTargets = pColliderTargets;
}

void Physics2D::Process()
{
	for (auto& body : *g_bodyTargets)
	{
		body->ApplyVelocity();
	}
	for (auto& body1 : *g_bodyTargets)
	{
		if (body1->justCollider()) continue;
		for (size_t i = 0; i < body1->colliderCount(); ++i)
		{
			Collider2D* body1Collider = body1->collider2D(i);
			if (body1Collider->gameObject()->active() == false || body1Collider->enable() == false) continue;
			const unsigned char& layer1 = body1Collider->gameObject()->layer();
			for (size_t colLayer = 0; colLayer < GO_LAYER_MAX; ++colLayer)
			{
				if (g_collisionLayer[layer1][colLayer] == false) continue;
				std::vector<Collider2D*>& colliderVec = (*g_colliderTargets)[colLayer];
				for (auto& body2Collider : colliderVec)
				{
					if (body2Collider->gameObject()->active() == false || body2Collider->enable() == false) continue;
					Body2D* body2 = body2Collider->body2D();
					if (body1 == body2) continue;
					SATResult satData = {};
					if (SAT(body1Collider->shape2D(), body2Collider->shape2D(), &satData))
					{
						if (satData.Penetration <= 0) continue;
						if (body1Collider->isTrigger() || body2Collider->isTrigger())
						{
							body1Collider->OnTriggerCallback(body2Collider);
							body2Collider->OnTriggerCallback(body1Collider);
						}
						else
						{
							PenetrationResolution(body1, body2, &satData);
							CollisionResolution(body1, body1Collider, body2, body2Collider, &satData);
							body1Collider->OnCollisionCallback(body2Collider);
							body2Collider->OnCollisionCallback(body1Collider);
						}
					}
				}
			}
		}
	}
}

void Physics2D::ClearProcessDatas()
{
	g_bodyTargets->clear();
	for (size_t colLayer = 0; colLayer < GO_LAYER_MAX; ++colLayer)
		(*g_colliderTargets)[colLayer].clear();
}

bool Physics2D::Raycast(const Vector2& pt, const Vector2& dir, const float& len, bool layers[GO_LAYER_MAX], RaycastResult* out_result)
{
	*out_result = {};
	float shortDistance = FLT_MAX;
	Line2D line(dir, len);
	line.setWorldPosition(dir * len * 0.5f + pt);

	auto intersectPoint = [&](const Vector2& ap1, const Vector2& ap2, const Vector2& bp1, const Vector2& bp2, Vector2* out_pt) -> bool
	{
		float t;
		float s;
		float under = (bp2.y - bp1.y) * (ap2.x - ap1.x) - (bp2.x - bp1.x) * (ap2.y - ap1.y);
		if (under == 0) return false;

		float _t = (bp2.x - bp1.x) * (ap1.y - bp1.y) - (bp2.y - bp1.y) * (ap1.x - bp1.x);
		float _s = (ap2.x - ap1.x) * (ap1.y - bp1.y) - (ap2.y - ap1.y) * (ap1.x - bp1.x);

		t = _t / under;
		s = _s / under;

		if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
		if (_t == 0 && _s == 0) return false;

		out_pt->x = ap1.x + t * (float)(ap2.x - ap1.x);
		out_pt->y = ap1.y + t * (float)(ap2.y - ap1.y);

		return true;
	};
	auto contactPoint = [&](Shape2D* pShape, const Vector2& collidedVertex) -> Vector2
	{
		if (pShape->vertexCount() == 0)
			return collidedVertex;
		Vector2 shortPt = {};
		float shortDist = FLT_MAX;
		const Vector2& ap1 = pt;
		const Vector2& ap2 = line.vertex(1);
		for (size_t i = 0; i < pShape->vertexCount(); ++i)
		{
			size_t next = i + 1;
			if (next == pShape->vertexCount()) next = 0;
			const Vector2& bp1 = pShape->vertex(i);
			const Vector2& bp2 = pShape->vertex(next);
			Vector2 intersect;
			if (intersectPoint(ap1, ap2, bp1, bp2, &intersect))
			{
				float dist = (pt - intersect).magnitude();
				if (dist < shortDist)
				{
					shortDist = dist;
					shortPt = intersect;
				}
			}
		}
		return shortPt;
	};

	for (size_t colLayer = 0; colLayer < GO_LAYER_MAX; ++colLayer)
	{
		if (layers[colLayer] == false) continue;
		std::vector<Collider2D*>& colliderVec = (*g_colliderTargets)[colLayer];
		for (auto& col : colliderVec)
		{
			if (col->gameObject()->active() == false || col->enable() == false) continue;
			SATResult satData = {};
			if (SAT(&line, col->shape2D(), &satData))
			{
				Vector2 contact = contactPoint(col->shape2D(), satData.CollidedVertex);
				Vector2 relVec = pt - contact;
				float dist = relVec.magnitude();
				if (dist < shortDistance)
				{
					shortDistance = dist;
					out_result->Collider = col;
					out_result->ContactPoint = contact;
					out_result->Normal = relVec.normalized();
				}
			}
		}
	}
	if (shortDistance == FLT_MAX)
		return false;
	else
		return true;
}

Vector2 Physics2D::ClosetVertexToPoint(Shape2D* shape, Vector2 point)
{
	float minSqrDist = FLT_MAX;
	Vector2 closetVertex;
	for (size_t i = 0; i < shape->vertexCount(); ++i)
	{
		float dist = (point - shape->vertex(i)).sqrMagnitude();
		if (dist < minSqrDist)
		{
			minSqrDist = dist;
			closetVertex = shape->vertex(i);
		}
	}
	return closetVertex;
}

void Physics2D::ProjectShapeOntoAxis(Vector2 axis, Shape2D* object, float* out_minLength, float* out_maxLength, Vector2* out_colVertex)
{
	size_t vertexCount = object->vertexCount() == 0 ? 2 : object->vertexCount();
	auto vertex = [&](size_t index) -> Vector2
	{
		if (object->vertexCount() == 0)
		{
			Circle2D* circle = static_cast<Circle2D*>(object);
			if (index == 0) return object->worldPosition() + axis.normalized() * circle->scaledRadius() * (-1);
			if (index == 1) return object->worldPosition() + axis.normalized() * circle->scaledRadius() * (+1);
			bool wtf_error = false;
			assert(wtf_error);
		}
		else return object->vertex(index);
		return {};
	};
	float minLength = Vector2::Dot(axis, vertex(0));
	float maxLength = minLength;
	if (out_colVertex) *out_colVertex = vertex(0);
	for (size_t i = 0; i < vertexCount; ++i)
	{
		float p = Vector2::Dot(axis, vertex(i)); // 한 점을 축에 사영한 길이
		if (p < minLength)
		{
			minLength = p;
			if (out_colVertex) *out_colVertex = vertex(i);
		}
		if (p > maxLength)
		{
			maxLength = p;
		}
	}
	if (out_minLength) *out_minLength = minLength;
	if (out_maxLength) *out_maxLength = maxLength;
}

bool Physics2D::SAT(Shape2D* object1, Shape2D* object2, SATResult* out_SATData)
{
	// Find axes ===================================================================================
	std::vector<Vector2> axis;
	auto addNormals = [&](Shape2D* obj) -> void
	{
		size_t vertexCount = obj->vertexCount();
		if (obj->vertexCount() == 0) return;
		if (obj->vertexCount() % 2 == 0) vertexCount /= 2;
		for (size_t i = 0; i < vertexCount; ++i)
		{
			size_t next = i + 1;
			if (next == obj->vertexCount()) next = 0;
			Vector2 dir = (obj->vertex(next) - obj->vertex(i)).normalized();
			axis.push_back(dir.normal());
		}
	};
	auto findAxis = [&](Shape2D* obj1, Shape2D* obj2) -> void
	{
		if (obj1->vertexCount() == 0)
		{
			Vector2 oneAxis = (ClosetVertexToPoint(obj2, obj1->worldPosition()) - obj1->worldPosition()).normalized();
			if (oneAxis.sqrMagnitude() == 0) oneAxis = Vector2(1, 0);
			axis.push_back(oneAxis);
		}
		else addNormals(obj1);
	};
	if (object1->vertexCount() == 0 && object2->vertexCount() == 0)
	{
		Vector2 oneAxis = (object2->worldPosition() - object1->worldPosition()).normalized();
		if (oneAxis.sqrMagnitude() == 0) oneAxis = Vector2(1, 0);
		axis.push_back(oneAxis);
	}
	else
	{
		findAxis(object1, object2);
		findAxis(object2, object1);
	}
	// Find axes ===================================================================================

	// SAT =========================================================================================
	float	shortOverlap = FLT_MAX;
	Vector2 shortOverlapAxis;
	Shape2D* colObj = nullptr;
	float	proj1min, proj1max, proj2min, proj2max, overlap;
	for (size_t i = 0; i < axis.size(); ++i)
	{
		ProjectShapeOntoAxis(axis[i], object1, &proj1min, &proj1max, nullptr);
		ProjectShapeOntoAxis(axis[i], object2, &proj2min, &proj2max, nullptr);
		overlap = min(proj1max, proj2max) - max(proj1min, proj2min);
		if (overlap < 0) return false;
		if ((proj1max > proj2max && proj1min < proj2min) || (proj1max < proj2max && proj1min > proj2min))
		{
			float mins = fabsf(proj1min - proj2min);
			float maxs = fabsf(proj1max - proj2max);
			if (mins < maxs)
			{
				overlap += mins;
			}
			else
			{
				overlap += maxs;
				axis[i] *= -1;
			}
		}
		if (overlap < shortOverlap)
		{
			shortOverlap = overlap;
			shortOverlapAxis = axis[i];
			if (i < object1->vertexCount())
			{
				colObj = object2;
				if (proj1max > proj2max)
					shortOverlapAxis = axis[i] * -1;
			}
			else
			{
				colObj = object1;
				if (proj1max < proj2max)
					shortOverlapAxis = axis[i] * -1;
			}
		}
	}
	// SAT =========================================================================================

	if (out_SATData)
	{
		ProjectShapeOntoAxis(shortOverlapAxis, colObj, nullptr, nullptr, &out_SATData->CollidedVertex);
		if (colObj == object2)
			shortOverlapAxis *= -1;
		out_SATData->PenetrationDirection = shortOverlapAxis;
		out_SATData->Penetration = shortOverlap;
	}

	return true;
}

void Physics2D::PenetrationResolution(Body2D* body1, Body2D* body2, SATResult* sat)
{
	const float& bodyInvMass = body1->invMass();
	const float& otherInvMass = body2->invMass();
	float invMassSum = bodyInvMass + otherInvMass;
	if (invMassSum == 0) return;
	Vector2 penetrationResolution = sat->PenetrationDirection * (sat->Penetration / invMassSum);
	Vector2 bodyPosition = body1->transform()->position() + penetrationResolution * bodyInvMass;
	Vector2 otherPosition = body2->transform()->position() - penetrationResolution * otherInvMass;
	body1->transform()->setPosition(bodyPosition);
	body1->UpdateColliderVertices();
	body2->transform()->setPosition(otherPosition);
	body2->UpdateColliderVertices();
}

void Physics2D::CollisionResolution(Body2D* body, Collider2D* col1, Body2D* other, Collider2D* col2, SATResult* sat)
{
	Vector2 normal = sat->PenetrationDirection;
	Vector2 relVel = body->velocity() - other->velocity();
	float sepVel = Vector2::Dot(relVel, normal);
	float new_sepVel = -sepVel * min(body->elasticity(), other->elasticity());

	float vsep_diff = new_sepVel - sepVel;

	float impulse;
	if (body->invMass() == 0 && other->invMass() == 0)
		impulse = 0;
	else
		impulse = vsep_diff / (body->invMass() + other->invMass());
	Vector2 impulseVec = normal * impulse;

	body->setVelocity(body->velocity() + impulseVec * body->invMass());
	other->setVelocity(other->velocity() + impulseVec * other->invMass() * (-1));
}