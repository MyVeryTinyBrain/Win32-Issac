#include "BaseStdafx.h"
#include "Camera2D.h"
#include "Transform.h"
#include "HDCEx.h"
#include "ExecutionOrder.h"

Camera2D* Camera2D::g_mainCamera;
std::vector<Camera2D*> Camera2D::g_cameras;

void Camera2D::Awake()
{
	m_HDCEx = nullptr;
	m_horizontal = (float)(*BaseGlobal::pCX);
	m_vertical = (float)(*BaseGlobal::pCY);
	m_halfWidth = m_horizontal * 0.5f;
	m_halfHeight = m_vertical * 0.5f;
	m_worldToCameraMatrix = {};


	if (!g_mainCamera)
		g_mainCamera = this;

	SetHDCEx();

	g_cameras.push_back(this);
	SetExecutionOrder(EX_ORDER_CAMERA2D);
}

void Camera2D::Start()
{
}

void Camera2D::Update()
{
}

void Camera2D::LateUpdate()
{
	// ī�޶� ũ�Ⱑ ����Ǵ� ��� ī�޶��� HDCEx�� ũ�� ���� �����Ѵ�.
	SetHDCEx();

	MakeWorldToCameraMatrix();
	MakeCameraToWorldMatrix();
	MakeCameraToScrenMatrix();
	MakeScreenToCameraMatrix();
}

void Camera2D::OnEnable()
{
	
}

void Camera2D::OnDisable()
{
}

void Camera2D::OnDestroy()
{
	if (g_mainCamera == this)
		g_mainCamera = nullptr;

	BASE_SAFE_DELETE(m_HDCEx);
	auto it = std::find(g_cameras.begin(), g_cameras.end(), this);
	g_cameras.erase(it);
}

const Matrix3x3& Camera2D::worldToCameraMatrix() const
{
	return m_worldToCameraMatrix;
}

const float& Camera2D::horizontal() const
{
	return m_horizontal;
}

void Camera2D::setHorizontal(const float& Horizontal)
{
	m_horizontal = Horizontal;
	m_halfWidth = Horizontal * 0.5f;
}

const float& Camera2D::vertical() const
{
	return m_vertical;
}

void Camera2D::setVertical(const float& Vertical)
{
	m_vertical = Vertical;
	m_halfHeight = Vertical * 0.5f;
}

const float& Camera2D::halfWidth() const
{
	return m_halfWidth;
}

const float& Camera2D::halfHeight() const
{
	return m_halfHeight;
}

const Matrix3x3& Camera2D::cameraToWorldMatrix() const
{
	return m_cameraToWorldMatrix;
}

const Matrix3x3& Camera2D::cameraToScreenMatrix() const
{
	return m_cameraToScreenMatrix;
}

const Matrix3x3& Camera2D::screenToCameraMatrix() const
{
	return m_screenToCameraMatrix;
}

HDCEx* Camera2D::hDCEx() const
{
	return m_HDCEx;
}

Camera2D* Camera2D::mainCamera()
{
	return g_mainCamera;
}

std::vector<Camera2D*>* Camera2D::getCameras()
{
	return &g_cameras;
}

void Camera2D::SetHDCEx()
{
	float newHor = m_horizontal * transform()->size().x;
	float newVer = m_vertical * transform()->size().y;
	if (m_HDCEx)
	{
		int prevHor = m_HDCEx->bitmapInfo().bmWidth;
		int prevVer = m_HDCEx->bitmapInfo().bmHeight;
		if ((int)newHor == prevHor && (int)newVer == prevVer)
			return;
	}
	BASE_SAFE_DELETE(m_HDCEx);
	m_HDCEx = new HDCEx((int)newHor, (int)newVer);
}

void Camera2D::MakeWorldToCameraMatrix()
{
	// ī�޶� ����� �����Ѵ�.
	// ===========================================================================================
	Vector2 position = transform()->position();
	float angle = transform()->angle();
	Vector2 size = transform()->size();

	// TRS
	// ī�޶� �������� ��ȯ�ϴ� ����Դϴ�.
	// t(translate): ī�޶��� ��ġ��ŭ ���� ����Դϴ�.
	// r(rotate): ī�޶��� ������ŭ ���� ����Դϴ�.
	// s(scale): ī�޶��� ũ�⸸ŭ ���̴� ����Դϴ�.
	// ===========================================================================================
	Matrix3x3 t = Matrix3x3::Translate(-position.x, -position.y);
	Matrix3x3 r = Matrix3x3::Rotate(-angle);
	Matrix3x3 s = Matrix3x3::Scale(1.0f / size.x, 1.0f / size.y);
	// ===========================================================================================

	// To window space
	Matrix3x3 w =
	{
		1,		0,		m_halfWidth * transform()->size().x,
		0,		-1,		m_halfHeight * transform()->size().y,
		0,		0,		1
	};

	// �켱 ���� ũ��� �׸� ���Ŀ� �׸� �׸� ��ü�� �ø��ų� ���� ���̹Ƿ� ������ ����� ������ �ʴ´�.
	//m_worldToCameraMatrix = w * s * r * t;
	m_worldToCameraMatrix = w * r * t;
	// ===========================================================================================
}

void Camera2D::MakeCameraToWorldMatrix()
{
	Vector2 position = transform()->position();
	float angle = transform()->angle();
	Vector2 size = transform()->size();

	Matrix3x3 t = Matrix3x3::Translate(+position.x, +position.y);
	Matrix3x3 r = Matrix3x3::Rotate(+angle);
	Matrix3x3 s = Matrix3x3::Scale(size.x, size.y);
	Matrix3x3 w =
	{
		1,		0,		-m_halfWidth * transform()->size().x,
		0,		-1,		+m_halfHeight * transform()->size().y,
		0,		0,		1
	};

	m_cameraToWorldMatrix = t * r * w;
}

void Camera2D::MakeScreenToCameraMatrix()
{
	m_screenToCameraMatrix = Matrix3x3::Scale(
		(m_horizontal * transform()->size().x) / (float)(*BaseGlobal::pCX),
		(m_vertical * transform()->size().y) / (float)(*BaseGlobal::pCY)
	);
}

void Camera2D::MakeCameraToScrenMatrix()
{
	m_cameraToScreenMatrix = Matrix3x3::Scale(
		(float)(*BaseGlobal::pCX) / (m_horizontal * transform()->size().x),
		(float)(*BaseGlobal::pCY) / (m_vertical * transform()->size().y)
	);
}
