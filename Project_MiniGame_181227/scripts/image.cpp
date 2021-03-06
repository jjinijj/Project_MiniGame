#include "stdafx.h"
#include "image.h"

//컴파일러 지시기 (나 라이브러리 쓸꺼야 msImg32 라이브러리)
#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL), _fileName(NULL)
{
}


image::~image()
{
}

HRESULT image::init(LPCWSTR fileName, int width, int height)
{
	return init(fileName, width, height, 1, 1);
}

HRESULT image::init(LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	// 이미지 정보 생성
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameNumX - 1;
	_imageInfo->maxFrameY = frameNumY - 1;
	_imageInfo->frameWidth = width / frameNumX;
	_imageInfo->frameHeight = height / frameNumY;

	// 파일 경로 복사
	int len;
	len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);



	// WIC를 사용하기 위한 Factory 객체 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->WICImagingFactory));
	assert(hr == S_OK);

	// 디코더 생성
	hr = _imageInfo->WICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->WICDecoder));
	assert(hr == S_OK);

	// 첫 번째 프레임을 사용할 수 있는 객체 구성
	hr = _imageInfo->WICDecoder->GetFrame(0, &_imageInfo->WICFrameDecoder);
	assert(hr == S_OK);

	// 포맷 컨버터 생성
	hr = _imageInfo->WICImagingFactory->CreateFormatConverter(&_imageInfo->WICFormatConverter);
	assert(hr == S_OK);

	// 비트맵으로 변환
	hr = _imageInfo->WICFormatConverter->Initialize(_imageInfo->WICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	// 변환된 이미지 형식을 사용하여 D2D용 비트맵 생성
	hr = D2DMANAGER->_renderTarget->CreateBitmapFromWicBitmap(_imageInfo->WICFormatConverter, NULL, &_imageInfo->bitmap);


	// 이미지가 생성되지 않았을 경우
	if (_imageInfo->bitmap == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void image::release(void)
{
	if (_imageInfo)
	{
		SAFE_DELETE(_imageInfo);
	}
}



//===================================================================
//						D2D 사용 렌더 함수
//- 카메라 이동 보정 & 범위에 들어가는 내용만 렌더
//- Left Top 기준
//===================================================================

void image::render(float alpha)
{
	render(0, 0, _imageInfo->width, _imageInfo->height, 0.f, 0.f, _imageInfo->width, _imageInfo->height, alpha);
}

void image::render(float destX, float destY, float alpha)
{
	render(destX, destY, _imageInfo->width, _imageInfo->height, 0.f, 0.f, _imageInfo->width, _imageInfo->height, alpha);
}

void image::render(float destX, float destY, int showWidth, int showHeight, float alpha)
{
	render(destX, destY, showWidth, showHeight, 0.f, 0.f, _imageInfo->width, _imageInfo->height, alpha);
}

void image::render(float destX, float destY, float sourX, float sourY, int sourWidth, int sourHeight, float alpha)
{
	render(destX, destY, sourWidth, sourHeight, sourX, sourY, sourWidth, sourHeight, alpha);
}

void image::render(float destX, float destY, int showWidth, int showHeight, float sourX, float sourY, int sourWidth, int sourHeight, float alpha)
{
	POINTFLOAT pf = GetRenderPosition(destX, destY);

	if ( _imageInfo->bitmap != NULL )
	{
		if ( !IsRnderPositionInWindow(pf, showWidth, showHeight) )
			return;

		D2D1_RECT_F dxArea	= RectF(pf.x, pf.y, pf.x + showWidth, pf.y + showHeight);
		D2D1_RECT_F dxArea2 = RectF(  sourX
									, sourY
									, sourX + sourWidth
									, sourY + sourHeight);
		D2DMANAGER->_renderTarget->DrawBitmap(_imageInfo->bitmap
													, dxArea
													, alpha
													, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
													, dxArea2);
	}
}


//===================================================================
//						프레임 이미지 렌더 함수
//- 카메라 이동 보정 & 범위에 들어가는 내용만 렌더
//- Left Top 기준
//===================================================================

void image::frameRender(float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	frameRender(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, currentFrameX, currentFrameY, alpha);
}

void image::frameRender(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float alpha)
{
	POINTFLOAT pf = GetRenderPosition(destX, destY);

	if (_imageInfo->bitmap != NULL)
	{
		if( !IsRnderPositionInWindow(pf, showWidth, showHeight) )
			return;

		D2D1_RECT_F dxArea = RectF(pf.x, pf.y, pf.x + showWidth, pf.y + showHeight);
		D2D1_RECT_F dxArea2 = RectF(  currentFrameX * _imageInfo->frameWidth
									, currentFrameY * _imageInfo->frameHeight
									, (currentFrameX + 1) * _imageInfo->frameWidth
									, (currentFrameY + 1) * _imageInfo->frameHeight);
		D2DMANAGER->_renderTarget->DrawBitmap(_imageInfo->bitmap
													, dxArea
													, alpha
													, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
													, dxArea2);
	}
}

POINTFLOAT image::GetRenderPosition(float destX, float destY)
{
	POINTFLOAT pf = { destX - CAMERA->getPosX() , destY - CAMERA->getPosY() };
	return pf;
}

bool image::IsRnderPositionInWindow(POINTFLOAT pf, float width, float height)
{
	if ( pf.x + width < 0  ) return false;
	if ( pf.y + height < 0 ) return false;
	if ( pf.x > WINSIZEX )	 return false;
	if ( pf.y > WINSIZEY )	 return false;

	return true;
}
