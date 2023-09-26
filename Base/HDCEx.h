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

	// HDC�� �޾� �̿� ȣȯ�Ǵ� ũ�Ⱑ ���� ���ο� HDC�� ����ϴ�.
	// Base ���̺귯���� �ʱ�ȭ �ϱ� ���� HDCEx�� �����Ϸ��� �� �����ڸ� ����մϴ�.
	HDCEx(HDC hdc);
	// ȭ�� ũ��� ���� HDCEx�� �����մϴ�.
	HDCEx();
	// ������ ũ���� HDCEx�� �����մϴ�.
	HDCEx(int cx, int cy);
	// ��Ʈ�� �̹����� �ҷ��� HDCEx�� �׷����� �����մϴ�.
	HDCEx(const TCHAR* bmpPath);

	~HDCEx();
	HDCEx(HDCEx&& rhs) noexcept;

	// HDC�� Ư�� ������ ���� ĥ�մϴ�.
	void Fill(COLORREF color);

	// dest DC�� destX, destY ��ġ�� DC�� ������ �׸��ϴ�.
	void BitBlt(HDC dest, int destX, int destY);
	// ���� DC�� srcX, srcY ��ġ�������� dest HDC�� destX, destY ��ġ�� DC�� ������ �׸��ϴ�.
	void BitBlt(HDC dest, int destX, int destY, int srcX, int srcY);

	// ====================================================================================================================
	// TrsBlt�� �����ϴ�.
	// �̹����� ũ�Ⱑ Ŭ ���� ó���ӵ��� �������ϴ�.
	// ���� ū �̹����� �ش� �Լ��� ����ϰ� �ʹٸ� ��Ʈ���� ���� ��Ʈ ���� ���̽ʽÿ�.
	// ������ ���� ����: https://skmagic.tistory.com/228
	// ====================================================================================================================

	// dest DC�� destX, destY ��ġ�� ������ ���� �����Ͽ� DC�� ������ �׸��ϴ�.
	void TrsBlt(HDC dest, int destX, int destY, COLORREF rmvCol);
	// ���� DC�� srcX, srcY ��ġ�������� dest DC�� destX, destY ��ġ�� ������ ���� �����Ͽ� DC�� ������ �׸��ϴ�.
	void TrsBlt(HDC dest, int destX, int destY, int srcX, int srcY, COLORREF rmvCol);
	// ���� DC�� srcX, srcY ��ġ�������� dest DC�� destX, destY ��ġ�� ������ ���� �����Ͽ� cx, cy�� ũ��� DC�� ������ �׸��ϴ�.
	void TrsBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol);

	// dest DC�� destX, destY ��ġ�� cx, cy�� ũ��� DC�� ������ �׸��ϴ�.
	void StrBlt(HDC dest, int destX, int destY, int cx, int cy);
	// ���� DC�� srcX, srcY ��ġ�������� dest DC�� destX, destY ��ġ�� cx, cy�� ũ��� DC�� ������ �׸��ϴ�.
	void StrBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy);

	void FillBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF fillCol);
	void FillBlt(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, COLORREF fillCol);

	void AlpBlt1(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, float alpha);
	void AlpBlt2(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, float alpha);
	void AlpBlt3(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, float alpha, COLORREF fillCol);
	void AlpBlt4(HDC dest, int destX, int destY, int srcX, int srcY, int cx, int cy, COLORREF rmvCol, float alpha, COLORREF fillCol);

	// �׸� �� �̹����� ��ǥ�� �� �߾ӿ� ���� �ϴ� �÷��׸� �����մϴ�.
	void setUseBltToCenter(bool value);
	// �׸� �� �̹����� ȸ�������� ���� �÷��׸� �����մϴ�.
	void setUseRotate(bool value);
	// �̹����� ȸ���� ȣ������ �����մϴ�.
	void setRotateAngle(float radian);
	// �����Ǿ� ����Ǿ� �ִ� HDC�� ���� ����� ���� ������ �����Ǿ� ����Ǿ� �ִ� HDC�� �����մϴ�.
	void DeleteMirorreds();

	const HDC& hdc() const;
	const HBITMAP& hBitmap() const;
	BITMAP bitmapInfo() const;

	// ��ȯ ���� �ٷ� HDC�� ������ ����ȯ�� �����մϴ�.
	operator const HDC& ();

private:
	void Init();
	void MakeMirroreds();

	// �߽ɿ� Blt�� �õ��϶�� �÷��װ� ���� �ִ� ��� �߽ɿ� �̹����� �׸��� �� ��ǥ�� ��ȯ�մϴ�.
	// �÷��װ� ���� �ִ� ��� �ƹ� �ϵ� ���� �ʽ��ϴ�.
	void BltPosToCenter(int* x, int* y, int cx, int cy) const;

	// ��������� ��ȯ�մϴ�.
	static XFORM GetIdentityMatrix(HDC hdc);

	// ȸ�� ��� �÷��װ� ���� ���� �� hdc�� XFORM�� ȸ���ؼ� �׸����� �����մϴ�.
	// hdc�� �����ϰ� �ִ� �׷��� ���� XFORM�� ��ȯ�մϴ�.
	// prev �Ķ���͸� NULL�� ä��� ���� ������ ��ȯ���� �ʽ��ϴ�.
	// �÷��װ� ���� �ִ� ��� �ƹ� �ϵ� �Ͼ�� �ʽ��ϴ�.
	void SetMatrix(HDC hdc, float x, float y, int* prevGraphicMode, XFORM* prevXForm);

	// SetMatrix�� ��ȯ�� ���� ������ �ٽ� hdc�� �����մϴ�.
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
