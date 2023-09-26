#pragma once
#ifndef __Physics2D_h__
#define __Physics2D_h__

#include "GameObjectLayer.h"

class Body2D;
class Shape2D;
class Collider2D;

struct SATResult
{
	Vector2 CollidedVertex;
	Vector2 PenetrationDirection;
	float Penetration;
};

struct RaycastResult
{
	Collider2D* Collider;
	Vector2 ContactPoint;
	Vector2 Normal;
};

class Physics2D
{
	//using pVectorBody2D = std::vector<Body2D*>*;
	//using arrVectorCollider2D = std::vector<Collider2D*>[GO_LAYER_MAX];
	//static pVectorBody2D g_bodyTargets;
	//static arrVectorCollider2D* g_colliderTargets;

	using vecPBody2D_t = std::vector<Body2D*>;
	using arrVecPCollider2D_t = std::vector<Collider2D*>[GO_LAYER_MAX];
	using pVecPBody2D_t = vecPBody2D_t*;
	using pArrVecPCollider2D_t = arrVecPCollider2D_t*;
	static pVecPBody2D_t g_bodyTargets;
	static pArrVecPCollider2D_t g_colliderTargets;

	static bool g_collisionLayer[GO_LAYER_MAX][GO_LAYER_MAX];
private:
	static Vector2 ClosetVertexToPoint(Shape2D* shape, Vector2 point);
	static void ProjectShapeOntoAxis(Vector2 axis, Shape2D* object, float* out_minLength, float* out_maxLength, Vector2* out_colVertex);
	static bool SAT(Shape2D* object1, Shape2D* object2, SATResult* out_SATData);
	static void PenetrationResolution(Body2D* body1, Body2D* body2, SATResult* satResult);
	static void CollisionResolution(Body2D* body1, Collider2D* col1, Body2D* body2, Collider2D* col2, SATResult* satResult);
public:
	static void SetAllOffCollisionLayer();
	static void SetCollisionLayer(const unsigned char& layer1, const unsigned char& layer2, const bool& collision);
	static void Reset();
	static void SetProcessDatas(std::vector<Body2D*>* pBodyTargets, std::vector<Collider2D*>(*pColliderTargets)[GO_LAYER_MAX]);
	static void Process();
	static void ClearProcessDatas();
	static bool Raycast(const Vector2& pt, const Vector2& dir, const float& len, bool layers[GO_LAYER_MAX], RaycastResult* out_result);
};

#endif
