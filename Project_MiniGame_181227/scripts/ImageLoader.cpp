#include "stdafx.h"
#include "ImageLoader.h"


ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}

HRESULT ImageLoader::init()
{
	return S_OK;
}

void ImageLoader::release()
{
}

vector<string> ImageLoader::ImageLoad( const char * loadFileName )
{
	vector<string> imgInfo;

	string fileName = "data/";
	fileName.append(loadFileName);
	fileName.append(".txt");

	imgInfo = TXTDATA->textLoadPerLine(fileName.c_str(), "//");

	int size = (int)imgInfo.size();
	for ( int ii = 0; ii < size; ++ii )
	{
		char str[128] = {};
		strcat_s(str, imgInfo[ii].c_str());
		vector<string> data = TXTDATA->charArraySeparation(str);


	}





	return vector<string>();
}
