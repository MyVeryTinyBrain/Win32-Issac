#pragma once
#ifndef __HDCEx_h__
#define __HDCEx_h__

class HDCEx
{
	HDC m_hDC;
	HBITMAP m_hBitmap;
	LONG m_w;
	LONG m_h;
	bool m_useBltToCenter;
	bool m_useRotate;
	float m_rot;
	float m_cos;
	float m_sin;

	HDC m_HMirrored;
	HBITMAP m_HMBitmap;
	HDC m_VMirrored;
	HBITMAP m_VMBitmap;
	HDC m_HVMirrored;
	HBITMAP m_HVMBitmap;

public:

	// HDC를 받아 이에 호환되는 크기가 같은 새로운 HDC를 만듭니다.
	// Base 라이브러리를 초기화 하기 전에 HDCEx를 생성하려면 이 생성자를 사용합니다.
	HDCEx(HDC hdc);
	// 화면 크기와 같은 HDCEx를 생성합니다.
	HDCEx();
	// 지정한 크기의 HDCEx를 생성합니다.
	HDCEx(int cx, int cy);
	// 비트맵 이미지를 불러와 HDCEx에 그려놓아 생성합니다.
	HDCEx(const TCHAR* bmpPath);

	~HDCEx();
	HDCEx(HDCEx&& rhs) noexcept;

	// HDC를 특정 색으로 전부 칠합니다.
	void Fill(COLORREF color);

	// dest DC의 destX, destY 위치에 DC의 내용을 그립니다.
	void BitBlt(HDC dest, int destX, int destY);
	// 원본 DC의 srcX, srcY 위치에서부터 dest HDC의 destX, destY 위치에 DC의 내용을 그립니다.
	void BitBlt(HDC dest, int destX, int destY, int srcX, int srcY);

	// ====================================================================================================================
	// TrsBlt는 느립니다.
	// 이미지의 크기가 클 수록 처리속도는 느려집니다.
	// 만약 큰 이미지를 해당 함수로 사용하고 싶다면 비트맵의 색상 비트 수를 줄이십시오.
	// 반투명 배경색 제외: https://skmagic.tistory.com/228
	// ====================================================================================================================

	// dest DC의 destX, destY 위치에 지정한 색을 제외하여 DC의 내용을 그립니다.
	void TrsBlt(HDC dest, int destX, int destY, COLORREF rmvCol);
	// 원본 DC의 srcX, srcY 위치에서부터 dest DC의 destX, destY 위치에 지정한 색을 제외하여 DC의 내용을 그립니다.
	void TrsBlt(HDC dest, int destX, int destY, int srcX, int srcY, COLORREF rmvCol);
	// 원본 DC의 srcX, srcY 위치에서부터 dest DC의 destX, destY 위치에 지정한 색을 제외하여 cx, cy의 크기로 DC의 내용을 그립니다.
	void TrsBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol);

	// dest DC의 destX, destY 위치에 cx, cy의 크기로 DC의 내용을 그립니다.
	void StrBlt(HDC dest, int destX, int destY, int cx, int cy);
	// 원본 DC의 srcX, srcY 위치에서부터 dest DC의 destX, destY 위치에 cx, cy의 크기로 DC의 내용을 그립니다.
	void StrBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy);

	void FillBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF fillCol);
	void FillBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, COLORREF fillCol);

	void AlpBlt1(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, float alpha);
	void AlpBlt2(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, float alpha);
	void AlpBlt3(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, float alpha, COLORREF fillCol);
	void AlpBlt4(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, float alpha, COLORREF fillCol);

	// 그릴 때 이미지가 좌표의 정 중앙에 오게 하는 플래그를 설정합니다.
	void setUseBltToCenter(bool value);
	// 그릴 때 이미지를 회전할지에 대한 플래그를 설정합니다.
	void setUseRotate(bool value);
	// 이미지를 회전할 호도각을 설정합니다.
	void setRotateAngle(float radian);
	// 반전되어 저장되어 있는 HDC를 새로 만들기 위해 기존에 반전되어 저장되어 있는 HDC를 제거합니다.
	void DeleteMirorreds();

	const HDC& hdc() const;
	const HBITMAP& hBitmap() const;
	BITMAP bitmapInfo() const;

	// 변환 없이 바로 HDC로 묵시적 형변환이 가능합니다.
	operator const HDC& ();

private:
	void Init();
	void MakeMirroreds();

	// 중심에 Blt를 시도하라는 플래그가 켜져 있는 경우 중심에 이미지를 그리게 될 좌표로 변환합니다.
	// 플래그가 꺼져 있는 경우 아무 일도 하지 않습니다.
	void BltPosToCenter(int* x, int* y, int cx, int cy) const;

	// 단위행렬을 반환합니다.
	static XFORM GetIdentityMatrix(HDC hdc);

	// 회전 사용 플래그가 켜져 있을 때 hdc의 XFORM을 회전해서 그리도록 설정합니다.
	// hdc가 소유하고 있던 그래픽 모드와 XFORM을 반환합니다.
	// prev 파라미터를 NULL로 채우면 이전 설정을 반환하지 않습니다.
	// 플래그가 꺼져 있는 경우 아무 일도 일어나지 않습니다.
	void SetMatrix(HDC hdc, float x, float y, int* prevGraphicMode, XFORM* prevXForm);

	// SetMatrix가 반환한 이전 설정을 다시 hdc에 대입합니다.
	void ResetMatrix(HDC hdc, const int* prevGraphicMode, const XFORM* prefXForm);
};

inline const HDC& HDCEx::hdc() const
{
	return m_hDC;
}

inline const HBITMAP& HDCEx::hBitmap() const
{
	return m_hBitmap;
}

inline BITMAP HDCEx::bitmapInfo() const
{
	BITMAP bitmapInfo;
	GetObject(m_hBitmap, sizeof(BITMAP), &bitmapInfo);
	return bitmapInfo;
}

inline HDCEx::operator const HDC& ()
{
	return m_hDC;
}

#endif
