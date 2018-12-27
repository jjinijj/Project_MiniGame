#pragma once
#include "singletonBase.h"
class ImageLoader : public singletonBase<ImageLoader>
{
private:
	enum eElementType
	{
		eElement_ImageName,
		eElement_FileName,
		eElement_Format,
		eElement_Width,
		eElement_Height,
		eElement_FrameX,
		eElement_FrameY,

		eElement_None,
		eElement_Count = eElement_None,
	};


public:
	ImageLoader();
	~ImageLoader();

	HRESULT init();
	void release();

	//txt에 있는 이미지 정보들 load 
	vector<string> ImageLoad( const char* loadFileName );
};

