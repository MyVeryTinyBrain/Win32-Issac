#include "BaseStdafx.h"
#include "TextRenderer.h"
#include "Camera2D.h"
#include "Transform.h"
#include "HDCEx.h"
#include "Renderer2DTag.h"

void TextRenderer::LateAwake()
{
    m_fixedSize = true;

    m_len = 0;
    m_text = NULL;
    m_color = RGB(0, 0, 0);
    m_fontSize = 20;
    m_fontWidth = 0; // Auto
    m_alignment = TextRendererAlignment::LeftMiddle;
    m_fontName = NULL;

    m_createdFontSizeX = 0;
    m_createdFontSizeY = 0;
    m_createFontAngle = 0;
    m_createdFontWidth = 0;
    m_fontNameChanged = false;
    m_font = NULL;

    setRenderTag(RD_TAG_UI);
}

void TextRenderer::Render(Camera2D* cam)
{
    if (m_text == NULL)
        return;

    Vector2 worldPos = transform()->position();
    float worldAng = transform()->angle();
    Vector2 worldSz = transform()->size();

    Vector2 winSpacePos = cam->worldToCameraMatrix() * worldPos;
    float winSpaceAng = worldAng - cam->transform()->angle();
    Vector2 size = { 1,1 };
    if (!m_fixedSize)
        size = transform()->size();

    const float fontSizeX = m_fontSize * size.x * 0.5f;
    const float fontSizeY = m_fontSize * size.y;
    Vector2 adjustment = {};
    int alignment = CreateAlignmentNumber(fontSizeY, &adjustment);

    CreateMyFont(fontSizeX, fontSizeY, winSpaceAng, m_fontWidth);
    HFONT oldFont = (HFONT)SelectObject(*cam->hDCEx(), m_font);
    COLORREF prevColor = SetTextColor(*cam->hDCEx(), m_color);
    int prevBkMode = SetBkMode(*cam->hDCEx(), TRANSPARENT);
    int prevAlign = SetTextAlign(*cam->hDCEx(), alignment);
    TextOut(
        *cam->hDCEx(),
        (int)winSpacePos.x, (int)(winSpacePos.y - adjustment.y),
        m_text,
        m_len
    );
    SelectObject(*cam->hDCEx(), oldFont);
    SetTextColor(*cam->hDCEx(), prevColor);
    SetBkMode(*cam->hDCEx(), prevBkMode);
    SetTextAlign(*cam->hDCEx(), prevAlign);
}

void TextRenderer::OnDestroy()
{
    Renderer2D::OnDestroy();

    BASE_SAFE_DELETE_ARR(m_text);
    BASE_SAFE_DELETE_ARR(m_fontName);
    if (m_font)
    {
        DeleteObject(m_font);
        m_font = NULL;
    }
}

const size_t& TextRenderer::length() const
{
    return m_len;
}

void TextRenderer::setText(const TCHAR* text)
{
    BASE_SAFE_DELETE_ARR(m_text);
    if (text == NULL)
    {
        m_len = 0;
        m_text = NULL;
        return;
    }

    m_len = _tcslen(text);
    m_text = new TCHAR[m_len + 1];
    _tcscpy_s(m_text, m_len + 1, text);
}

const TCHAR* TextRenderer::text() const
{
    return m_text;
}

void TextRenderer::setColor(const COLORREF& Color)
{
    m_color = Color;
}

const COLORREF& TextRenderer::color() const
{
    return m_color;
}

void TextRenderer::setFontSize(const float& FontSize)
{
    m_fontSize = FontSize;
}

const float& TextRenderer::fontSize() const
{
    return m_fontSize;
}

const bool& TextRenderer::fixedSize() const
{
    return m_fixedSize;
}

void TextRenderer::setAlignment(const TextRendererAlignment& Alignment)
{
    m_alignment = Alignment;
}

void TextRenderer::setFixedSize(const bool& enable)
{
    m_fixedSize = enable;
}

const TextRendererAlignment& TextRenderer::alignment() const
{
    return m_alignment;
}

void TextRenderer::CreateMyFont(const float& sizeX, const float& sizeY, const float& angle, const float& width)
{
    if (sizeX == m_createdFontSizeX && 
        sizeY == m_createdFontSizeY && 
        angle == m_createFontAngle &&
        width == m_createdFontWidth &&
        m_fontNameChanged == false)
        return;

    if (m_font)
    {
        DeleteObject(m_font);
        m_font = NULL;
    }

    m_createdFontSizeX = sizeX;
    m_createdFontSizeY = sizeY;
    m_createFontAngle = angle;
    m_createdFontWidth = width;
    m_fontNameChanged = false;

    m_font = CreateFont(
        (int)(m_createdFontSizeY),
        (int)(m_createdFontSizeX),
        (int)(angle * RAD2DEG * 10.0f),
        (int)(angle * RAD2DEG * 10.0f),
        (int)width,
        0,
        0,
        FW_DONTCARE,
        /*ANSI_CHARSET*/DEFAULT_CHARSET,
        OUT_CHARACTER_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        VARIABLE_PITCH | FF_ROMAN,
        m_fontName
    );
}

void TextRenderer::setFontWidth(const float& Width)
{
    m_fontWidth = Width;
}

const float& TextRenderer::fontWidth() const
{
    return m_fontWidth;
}

void TextRenderer::setFontName(const TCHAR* fontName)
{
    if (m_fontName == NULL && fontName == NULL)
        return;
    if (m_fontName != NULL && fontName != NULL && !_tcscmp(m_fontName, fontName))
        return;

    BASE_SAFE_DELETE_ARR(m_fontName);

    if (fontName == NULL)
    {
        m_fontName = NULL;
    }
    else
    {
        size_t len = _tcslen(fontName);
        m_fontName = new TCHAR[len + 1];
        _tcscpy_s(m_fontName, len + 1, fontName);
    }

    m_fontNameChanged = true;
}

const TCHAR* TextRenderer::fontName() const
{
    return m_fontName;
}

int TextRenderer::CreateAlignmentNumber(const float& fontSizeY, Vector2* pAdjustment)
{
    switch (m_alignment)
    {
        case TextRendererAlignment::LeftTop:
            return TA_LEFT | TA_TOP;
        case TextRendererAlignment::CenterTop:
            return TA_CENTER | TA_TOP;
        case TextRendererAlignment::RightTop:
            return TA_RIGHT | TA_TOP;

        case TextRendererAlignment::LeftBottom:
            return TA_LEFT | TA_BOTTOM;
        case TextRendererAlignment::CenterBottom:
            return TA_CENTER | TA_BOTTOM;
        case TextRendererAlignment::RightBottom:
            return TA_RIGHT | TA_BOTTOM;

        case TextRendererAlignment::LeftMiddle:
            *pAdjustment = { 0,fontSizeY * 0.5f };
            return TA_LEFT | TA_TOP;
        case TextRendererAlignment::CenterMiddle:
            *pAdjustment = { 0,fontSizeY * 0.5f };
            return TA_CENTER | TA_TOP;
        case TextRendererAlignment::RightMiddle:
            *pAdjustment = { 0,fontSizeY * 0.5f };
            return TA_RIGHT | TA_TOP;

        default:
            *pAdjustment = { 0,fontSizeY * 0.5f };
            return TA_RIGHT | TA_TOP;
    }
}
