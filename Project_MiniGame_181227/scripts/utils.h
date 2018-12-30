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

	inline bool CheckIntersectRect(const RECT& rc1, const RECT& rc2)
	{
		int hightL	= rc1.left	< rc2.left	? rc2.left	: rc1.left;
		int lowR	= rc1.right < rc2.right ? rc1.right : rc2.right;
		int highT	= rc1.top	< rc2.top	? rc2.top	: rc1.top;
		int lowB	= rc1.bottom< rc2.bottom? rc1.bottom: rc2.bottom;

		for ( int xx = hightL; xx <= lowR; ++xx )
		{
			for ( int yy = highT; yy <= lowB; ++yy )
			{
				return true;
			}
		}

		return false;
	}

	inline int GetIntersectOffsetX(const RECT& moveRc, const RECT& sourcRc)
	{
		int hightL	= moveRc.left	< sourcRc.left	? sourcRc.left	: moveRc.left;
		int lowR	= moveRc.right	< sourcRc.right ? moveRc.right	: sourcRc.right;

		if(moveRc.left < hightL )
			return hightL - moveRc.right;
		else if(lowR < moveRc.right )
			return lowR - moveRc.left;

		return 0;
	}

	inline int GetIntersectOffsetY(const RECT& moveRc, const RECT& sourcRc)
	{
		int highT	= moveRc.top	< sourcRc.top	? sourcRc.top	: moveRc.top;
		int lowB	= moveRc.bottom	< sourcRc.bottom? moveRc.bottom	: sourcRc.bottom;

		if(moveRc.top < highT )
			return highT - moveRc.bottom;
		else if( lowB < moveRc.bottom )
			return lowB - moveRc.top + 1;

		return 0;
	}

	inline int GetIntersectOffsetX_doNotBoard(const RECT& moveRc, const RECT& sourcRc)
	{
		int hightL	= moveRc.left	< sourcRc.left	? sourcRc.left	: moveRc.left;
		int lowR	= moveRc.right	< sourcRc.right ? moveRc.right	: sourcRc.right;

		if(moveRc.left < hightL )
			return hightL - moveRc.right - 1;
		else if(lowR < moveRc.right )
			return lowR - moveRc.left + 1;

		return 0;
	}

	inline int GetIntersectOffsetY_doNotBoard(const RECT& moveRc, const RECT& sourcRc)
	{
		int highT	= moveRc.top	< sourcRc.top	? sourcRc.top	: moveRc.top;
		int lowB	= moveRc.bottom	< sourcRc.bottom? moveRc.bottom	: sourcRc.bottom;

		if(moveRc.top < highT )
			return highT - moveRc.bottom - 1;
		else if( lowB < moveRc.bottom )
			return lowB - moveRc.top + 1;

		return 0;
	}

}