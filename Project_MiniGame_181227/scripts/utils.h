#pragma once

#define PI 3.141592f
#define PI2 2 * PI

namespace JJINS_UTIL
{
	typedef struct tagRectFloat
	{
		float left;
		float top;
		float right;
		float bottom;
	}RECTF;


	inline const wstring MakeImageName(const WCHAR* imageName, const WCHAR* folderName = nullptr)
	{
		wstring str = L"";

		if ( nullptr != folderName )
		{
			str.append(folderName);
			str.append(L"/");
		}

		str.append(imageName);
		str.append(L".bmp");

		return str;
	}

	inline const wstring AppendInt(const WCHAR* imageName, int value)
	{
		wstring str = L"";
		
		str.append(imageName);
		str.append(to_wstring(value));

		return str;
	}

	inline bool CheckIntersectRectF(RECTF& rcf1, RECTF& rcf2)
	{
		if ( rcf2.left <= rcf1.left && rcf1.left < rcf2.right )
		{
			if ( rcf2.bottom <= rcf1.bottom && rcf1.top < rcf2.bottom)
				return true;
			else if( rcf1.bottom <= rcf2.bottom && rcf2.top < rcf1.bottom)
				return true;
		}

		return false;
	}

	// warrning
	inline RECT ConvertRECTFtoRECT(RECTF rcf)
	{
		RECT rc = {(int)rcf.left, (int)rcf.top, (int)rcf.right, (int)rcf.bottom};
		return rc;
	}
}