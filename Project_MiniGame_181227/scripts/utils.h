#pragma once

#define PI 3.141592f
#define PI2 2 * PI

namespace JJINS_UTIL
{
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
}