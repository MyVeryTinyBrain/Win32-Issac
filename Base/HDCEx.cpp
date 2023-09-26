#include "BaseStdafx.h"
#include "HDCEx.h"

HDCEx::HDCEx(HDC hdc)
{
	BITMAP bitmapInfo;
	memset(&bitmapInfo, 0, sizeof(BITMAP));

	HGDIOBJ _hBitmap = GetCurrentObject(hdc, OBJ_BITMAP);
	GetObject(_hBitmap, sizeof(BITMAP), &bitmapInfo);

	m_hDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, bitmapInfo.bmWidth, bitmapInfo.bmHeight);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
	DeleteObject(oldBitmap);

	m_w = bitmapInfo.bmWidth;
	m_h = bitmapInfo.bmHeight;

	Init();
}

HDCEx::HDCEx()
{
	const HDC& hdc = *BaseGlobal::pHDCEx;

	BITMAP bitmapInfo;
	memset(&bitmapInfo, 0, sizeof(BITMAP));

	HGDIOBJ _hBitmap = GetCurrentObject(hdc, OBJ_BITMAP);
	GetObject(_hBitmap, sizeof(BITMAP), &bitmapInfo);

	m_hDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, bitmapInfo.bmWidth, bitmapInfo.bmHeight);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
	DeleteObject(oldBitmap);

	m_w = bitmapInfo.bmWidth;
	m_h = bitmapInfo.bmHeight;

	Init();
}

HDCEx::HDCEx(int cx, int cy)
{
	const HDC& hdc = *BaseGlobal::pHDCEx;

	m_hDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, cx, cy);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
	DeleteObject(oldBitmap);

	m_w = cx;
	m_h = cy;

	Init();
}

HDCEx::HDCEx(const TCHAR* bmpPath)
{
	const HDC& hdc = *BaseGlobal::pHDCEx;

	m_hDC = CreateCompatibleDC(hdc);
	m_hBitmap = (HBITMAP)LoadImage(
		NULL,
		bmpPath,
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
	DeleteObject(oldBitmap);

	BITMAP _bitmapInfo = bitmapInfo();
	m_w = _bitmapInfo.bmWidth;
	m_h = _bitmapInfo.bmHeight;

	Init();
}

HDCEx::~HDCEx()
{
	if (m_hDC)
	{
		DeleteObject(m_hBitmap);
		DeleteDC(m_hDC);
	}
	DeleteMirorreds();
}

HDCEx::HDCEx(HDCEx&& rhs) noexcept
{
	m_hDC = rhs.m_hDC;
	m_HMirrored = rhs.m_HMirrored;
	m_VMirrored = rhs.m_VMirrored;
	m_HVMirrored = rhs.m_HVMirrored;
	m_hBitmap = rhs.m_hBitmap;
	m_w = rhs.m_w;
	m_h = rhs.m_h;
	m_useBltToCenter = rhs.m_useBltToCenter;
	m_useRotate = rhs.m_useRotate;
	m_rot = rhs.m_rot;
	m_cos = rhs.m_cos;
	m_sin = rhs.m_sin;
	rhs.m_hDC = NULL;
	rhs.m_HMirrored = NULL;
	rhs.m_VMirrored = NULL;
	rhs.m_HVMirrored = NULL;
}

void HDCEx::Fill(COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldHBrush = (HBRUSH)SelectObject(m_hDC, hBrush);
	PatBlt(m_hDC, 0, 0, m_w, m_h, PATCOPY);
	SelectObject(m_hDC, oldHBrush);
	DeleteObject(hBrush);
}

void HDCEx::BitBlt(HDC dest, int destX, int destY)
{
	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, m_w, m_h);
	::BitBlt(
		dest,
		destX, destY,
		m_w, m_h,
		m_hDC,
		0, 0,
		SRCCOPY
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);
}

void HDCEx::BitBlt(HDC dest, int destX, int destY, int srcX, int srcY)
{
	HDC srcHDC = m_hDC;
	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, m_w - srcX, m_w - srcX);
	::BitBlt(
		dest,
		destX, destY,
		m_w - srcX, m_h - srcY,
		m_hDC,
		srcX, srcY,
		SRCCOPY
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);
}

void HDCEx::TrsBlt(HDC dest, int destX, int destY, COLORREF rmvCol)
{
	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, m_w, m_h);
	::GdiTransparentBlt(
		dest,
		destX, destY,
		m_w, m_h,
		m_hDC,
		0, 0,
		m_w, m_h,
		rmvCol
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);
}

void HDCEx::TrsBlt(HDC dest, int destX, int destY, int srcX, int srcY, COLORREF rmvCol)
{
	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, m_w, m_h);
	::GdiTransparentBlt(
		dest,
		destX, destY,
		m_w, m_h,
		m_hDC,
		srcX, srcY,
		m_w - srcX, m_h - srcY,
		rmvCol
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);
}

void HDCEx::TrsBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol)
{
	HDC srcHDC = m_hDC;
	MakeMirroreds();
	if (cx < 0 && cy < 0)
	{
		srcHDC = m_HVMirrored;
		cx *= -1;
		cy *= -1;
	}
	else if (cx < 0)
	{
		srcHDC = m_HMirrored;
		cx *= -1;
	}
	else if (cy < 0)
	{
		srcHDC = m_VMirrored;
		cy *= -1;
	}
	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, cx, cy);
	::GdiTransparentBlt(
		dest,
		destX, destY,
		cx, cy,
		srcHDC,
		srcX, srcY,
		m_w - srcX, m_h - srcY,
		rmvCol
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);
}

void HDCEx::StrBlt(HDC dest, int destX, int destY, int cx, int cy)
{
	int _srcX = 0;
	int _srcY = 0;
	int _srcW = m_w - _srcX;
	int _srcH = m_h - _srcY;
	if (cx < 0)
	{
		_srcX = m_w;
		_srcW *= -1;
		cx *= -1;
	}
	if (cy < 0)
	{
		_srcY = m_h;
		_srcH *= -1;
		cy *= -1;
	}
	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, cx, cy);
	::StretchBlt(
		dest,
		destX, destY,
		cx, cy,
		m_hDC,
		_srcX, _srcY,
		_srcW, _srcH,
		SRCCOPY
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);
}

void HDCEx::StrBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy)
{
	int _srcX = srcX;
	int _srcY = srcY;
	int _srcW = m_w - _srcX;
	int _srcH = m_h - _srcY;
	if (cx < 0)
	{
		_srcX = m_w;
		_srcW *= -1;
		cx *= -1;
	}
	if (cy < 0)
	{
		_srcY = m_h;
		_srcH *= -1;
		cy *= -1;
	}
	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, cx, cy);
	::StretchBlt(
		dest,
		destX, destY,
		cx, cy,
		m_hDC,
		_srcX, _srcY,
		_srcW, _srcH,
		SRCCOPY
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);
}

void HDCEx::FillBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF fillCol)
{
	HDC srcHDC = m_hDC;
	MakeMirroreds();
	if (cx < 0 && cy < 0)
	{
		srcHDC = m_HVMirrored;
		cx *= -1;
		cy *= -1;
	}
	else if (cx < 0)
	{
		srcHDC = m_HMirrored;
		cx *= -1;
	}
	else if (cy < 0)
	{
		srcHDC = m_VMirrored;
		cy *= -1;
	}

	HDC newHDC = CreateCompatibleDC(m_hDC);
	HBITMAP newHBitmap = CreateCompatibleBitmap(m_hDC, m_w, m_h);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(newHDC, newHBitmap);
	DeleteObject(oldBitmap);
	::BitBlt(newHDC, 0, 0, m_w, m_h, srcHDC, 0, 0, SRCCOPY);
	const LONG& widthBytes = bitmapInfo().bmWidthBytes;
	BYTE* bytes = new BYTE[widthBytes * m_h]{};
	LONG byteCount = GetBitmapBits(newHBitmap, widthBytes * m_h, bytes);
	RGBQUAD* pRgb = (RGBQUAD*)bytes;
	for (size_t i = 0; i < (size_t)(byteCount / sizeof(RGBQUAD)); ++i)
	{
		pRgb[i].rgbRed = (BYTE)((((float)pRgb[i].rgbRed / 255.0f) * ((float)GetRValue(fillCol) / 255.0f)) * 255.0f);
		if (pRgb[i].rgbRed == 255) pRgb[i].rgbRed = 254;
		pRgb[i].rgbGreen = (BYTE)((((float)pRgb[i].rgbGreen / 255.0f) * ((float)GetGValue(fillCol) / 255.0f)) * 255.0f);
		if (pRgb[i].rgbGreen == 255) pRgb[i].rgbGreen = 254;
		pRgb[i].rgbBlue = (BYTE)((((float)pRgb[i].rgbBlue / 255.0f) * ((float)GetBValue(fillCol) / 255.0f)) * 255.0f);
		if (pRgb[i].rgbBlue == 255) pRgb[i].rgbBlue = 254;
	}
	SetBitmapBits(newHBitmap, widthBytes * m_h, bytes);
	srcHDC = newHDC;

	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, cx, cy);
	::StretchBlt(
		dest,
		destX, destY,
		cx, cy,
		srcHDC,
		srcX, srcY,
		m_w - srcX, m_h - srcY,
		SRCCOPY
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);

	DeleteObject(newHBitmap);
	DeleteDC(newHDC);
	BASE_SAFE_DELETE_ARR(bytes);
}

void HDCEx::FillBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, COLORREF fillCol)
{
	HDC srcHDC = m_hDC;
	MakeMirroreds();
	if (cx < 0 && cy < 0)
	{
		srcHDC = m_HVMirrored;
		cx *= -1;
		cy *= -1;
	}
	else if (cx < 0)
	{
		srcHDC = m_HMirrored;
		cx *= -1;
	}
	else if (cy < 0)
	{
		srcHDC = m_VMirrored;
		cy *= -1;
	}

	HDC newHDC = CreateCompatibleDC(m_hDC);
	HBITMAP newHBitmap = CreateCompatibleBitmap(m_hDC, m_w, m_h);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(newHDC, newHBitmap);
	DeleteObject(oldBitmap);
	::BitBlt(newHDC, 0, 0, m_w, m_h, srcHDC, 0, 0, SRCCOPY);
	const LONG& widthBytes = bitmapInfo().bmWidthBytes;
	BYTE* bytes = new BYTE[widthBytes * m_h]{};
	LONG byteCount = GetBitmapBits(newHBitmap, widthBytes * m_h, bytes);
	RGBQUAD* pRgb = (RGBQUAD*)bytes;
	for (size_t i = 0; i < (size_t)(byteCount / sizeof(RGBQUAD)); ++i)
	{
		if (rmvCol == RGB(pRgb[i].rgbRed, pRgb[i].rgbGreen, pRgb[i].rgbBlue)) continue;
		pRgb[i].rgbRed = (BYTE)((((float)pRgb[i].rgbRed / 255.0f) * ((float)GetRValue(fillCol) / 255.0f)) * 255.0f);
		if (pRgb[i].rgbRed == 255) pRgb[i].rgbRed = 254;
		pRgb[i].rgbGreen = (BYTE)((((float)pRgb[i].rgbGreen / 255.0f) * ((float)GetGValue(fillCol) / 255.0f)) * 255.0f);
		if (pRgb[i].rgbGreen == 255) pRgb[i].rgbGreen = 254;
		pRgb[i].rgbBlue = (BYTE)((((float)pRgb[i].rgbBlue / 255.0f) * ((float)GetBValue(fillCol) / 255.0f)) * 255.0f);
		if (pRgb[i].rgbBlue == 255) pRgb[i].rgbBlue = 254;
	}
	SetBitmapBits(newHBitmap, widthBytes * m_h, bytes);
	srcHDC = newHDC;

	int prevGraphicMode;
	XFORM prevXForm;
	SetMatrix(dest, (float)destX, (float)destY, &prevGraphicMode, &prevXForm);
	BltPosToCenter(&destX, &destY, cx, cy);
	::GdiTransparentBlt(
		dest,
		destX, destY,
		cx, cy,
		srcHDC,
		srcX, srcY,
		m_w - srcX, m_h - srcY,
		rmvCol
	);
	ResetMatrix(dest, &prevGraphicMode, &prevXForm);

	DeleteObject(newHBitmap);
	DeleteDC(newHDC);
	BASE_SAFE_DELETE_ARR(bytes);
}

void HDCEx::AlpBlt1(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, float alpha)
{
	int absCX = abs(cx);
	int absCY = abs(cy);
	int sqrLen = (int)sqrt(absCX * absCX + absCY * absCX);
	HDCEx memDC(sqrLen, sqrLen);
	::BitBlt(
		memDC,
		0, 0,
		sqrLen, sqrLen,
		dest,
		destX - sqrLen / 2, destY - sqrLen / 2,
		SRCCOPY
	);

	StrBlt(memDC, sqrLen / 2, sqrLen / 2, srcX, srcY, cx, cy);

	BltPosToCenter(&destX, &destY, sqrLen, sqrLen);
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (BYTE)(alpha * 255);
	bf.AlphaFormat = 0;
	GdiAlphaBlend(
		dest,
		destX, destY,
		sqrLen, sqrLen,
		memDC,
		0, 0,
		sqrLen, sqrLen,
		bf);
}

void HDCEx::AlpBlt2(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, float alpha)
{
	int absCX = abs(cx);
	int absCY = abs(cy);
	int sqrLen = (int)sqrt(absCX * absCX + absCY * absCX);
	HDCEx memDC(sqrLen, sqrLen);
	::BitBlt(
		memDC,
		0, 0,
		sqrLen, sqrLen,
		dest,
		destX - sqrLen / 2, destY - sqrLen / 2,
		SRCCOPY
	);

	TrsBlt(memDC, sqrLen / 2, sqrLen / 2, srcX, srcY, cx, cy, rmvCol);

	BltPosToCenter(&destX, &destY, sqrLen, sqrLen);
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (BYTE)(alpha * 255);
	bf.AlphaFormat = 0;
	GdiAlphaBlend(
		dest, 
		destX, destY, 
		sqrLen, sqrLen,
		memDC, 
		0, 0, 
		sqrLen, sqrLen,
		bf);
}

void HDCEx::AlpBlt3(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, float alpha, COLORREF fillCol)
{
	int absCX = abs(cx);
	int absCY = abs(cy);
	int sqrLen = (int)sqrt(absCX * absCX + absCY * absCX);
	HDCEx memDC(sqrLen, sqrLen);
	::BitBlt(
		memDC,
		0, 0,
		sqrLen, sqrLen,
		dest,
		destX - sqrLen / 2, destY - sqrLen / 2,
		SRCCOPY
	);

	FillBlt(memDC, sqrLen / 2, sqrLen / 2, srcX, srcY, cx, cy, fillCol);

	BltPosToCenter(&destX, &destY, sqrLen, sqrLen);
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (BYTE)(alpha * 255);
	bf.AlphaFormat = 0;
	GdiAlphaBlend(
		dest,
		destX, destY,
		sqrLen, sqrLen,
		memDC,
		0, 0,
		sqrLen, sqrLen,
		bf);
}

void HDCEx::AlpBlt4(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, float alpha, COLORREF fillCol)
{
	int absCX = abs(cx);
	int absCY = abs(cy);
	int sqrLen = (int)sqrt(absCX * absCX + absCY * absCX);
	HDCEx memDC(sqrLen, sqrLen);
	::BitBlt(
		memDC,
		0, 0,
		sqrLen, sqrLen,
		dest,
		destX - sqrLen / 2, destY - sqrLen / 2,
		SRCCOPY
	);

	FillBlt(memDC, sqrLen / 2, sqrLen / 2, srcX, srcY, cx, cy, rmvCol, fillCol);

	BltPosToCenter(&destX, &destY, sqrLen, sqrLen);
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (BYTE)(alpha * 255);
	bf.AlphaFormat = 0;
	GdiAlphaBlend(
		dest,
		destX, destY,
		sqrLen, sqrLen,
		memDC,
		0, 0,
		sqrLen, sqrLen,
		bf);
}

void HDCEx::setUseBltToCenter(bool value)
{
	m_useBltToCenter = value;
}

void HDCEx::setUseRotate(bool value)
{
	m_useRotate = value;
}

void HDCEx::setRotateAngle(float radian)
{
	m_rot = radian;
	m_cos = cosf(m_rot);
	m_sin = sinf(m_rot);
}

void HDCEx::BltPosToCenter(int* x, int* y, int cx, int cy) const
{
	if (m_useBltToCenter)
	{
		*x -= cx / 2;
		*y -= cy / 2;
	}
}

XFORM HDCEx::GetIdentityMatrix(HDC hdc)
{
	XFORM xForm;
	xForm.eM11 = 1;
	xForm.eM12 = 0;
	xForm.eM21 = 0;
	xForm.eM22 = 0;
	xForm.eDx = 0;
	xForm.eDy = 0;
	return xForm;
}

void HDCEx::SetMatrix(HDC hdc, float x, float y, int* prevGraphicMode, XFORM* prevXForm)
{
	if (!m_useRotate) return;

	XFORM xForm;
	xForm.eM11 = m_cos;
	xForm.eM12 = m_sin;
	xForm.eM21 = -m_sin;
	xForm.eM22 = m_cos;
	xForm.eDx = x - m_cos * x + m_sin * y;
	xForm.eDy = y - m_cos * y - m_sin * x;

	if (prevXForm) GetWorldTransform(hdc, prevXForm);
	if (prevGraphicMode) *prevGraphicMode = SetGraphicsMode(hdc, GM_ADVANCED);
	else SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xForm);
}

void HDCEx::ResetMatrix(HDC hdc, const int* prevGraphicMode, const XFORM* prefXForm)
{
	SetWorldTransform(hdc, prefXForm);
	SetGraphicsMode(hdc, *prevGraphicMode);
}

void HDCEx::DeleteMirorreds()
{
	if (m_HMirrored)
	{
		DeleteObject(m_HMBitmap);
		DeleteDC(m_HMirrored);
	}
	if (m_VMirrored)
	{
		DeleteObject(m_VMBitmap);
		DeleteDC(m_VMirrored);
	}
	if (m_HVMirrored)
	{
		DeleteObject(m_HVMBitmap);
		DeleteDC(m_HVMirrored);
	}
	m_HMirrored = NULL;
	m_VMirrored = NULL;
	m_HVMirrored = NULL;
	m_HMBitmap = NULL;
	m_VMBitmap = NULL;
	m_HVMBitmap = NULL;
}

void HDCEx::Init()
{
	m_useBltToCenter = false;
	m_useRotate = false;
	m_rot = 0;
	m_cos = 1;
	m_sin = 0;
	m_HMirrored = NULL;
	m_VMirrored = NULL;
	m_HVMirrored = NULL;
	m_HMBitmap = NULL;
	m_VMBitmap = NULL;
	m_HVMBitmap = NULL;
}

void HDCEx::MakeMirroreds()
{
	if (!m_HMirrored)
	{
		m_HMirrored = CreateCompatibleDC(m_hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(m_hDC, m_w, m_h);
		DeleteObject(SelectObject(m_HMirrored, hBitmap));
		::StretchBlt(
			m_HMirrored,
			0, 0,
			m_w, m_h,
			m_hDC,
			m_w - 1, 0,
			-m_w, m_h,
			SRCCOPY
		);
		m_HMBitmap = hBitmap;
	}
	if (!m_VMirrored)
	{
		m_VMirrored = CreateCompatibleDC(m_hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(m_hDC, m_w, m_h);
		DeleteObject(SelectObject(m_VMirrored, hBitmap));
		::StretchBlt(
			m_VMirrored,
			0, 0,
			m_w, m_h,
			m_hDC,
			0, m_h - 1,
			m_w, -m_h,
			SRCCOPY
		);
		m_VMBitmap = hBitmap;
	}
	if (!m_HVMirrored)
	{
		m_HVMirrored = CreateCompatibleDC(m_hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(m_hDC, m_w, m_h);
		DeleteObject(SelectObject(m_HVMirrored, hBitmap));
		::StretchBlt(
			m_HVMirrored,
			0, 0,
			m_w, m_h,
			m_hDC,
			m_w - 1, m_h - 1,
			-m_w, -m_h,
			SRCCOPY
		);
		m_HVMBitmap = hBitmap;
	}
}
