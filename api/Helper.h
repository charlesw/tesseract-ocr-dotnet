/**
Copyright 2011, Cong Nguyen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#pragma once

#include "Configuration.h"

#include <windows.h>
#include "..\api\baseapi.h"
#include "..\cutil\callcpp.h"
#include "..\wordrec\chop.h"
#include "..\ccmain\tessedit.h"
#include "..\ccmain\tessvars.h"
#include "..\classify\baseline.h"
#include "..\classify\mfoutline.h"
#include "..\classify\normmatch.h"
#include "..\classify\intmatcher.h"
#include "..\classify\speckle.h"
#include "..\dict\permute.h"
#include "..\ccstruct\publictypes.h"
#include "leptprotos.h"

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

USING_TESSERACT

class Helper
{
public:
	Helper();
	~Helper();

public:
	static char* StringToPointer(String* s)
	{
		if (s == 0)
			return NULL;

		char* str = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s).ToPointer());

		return str;
	}

	static String* PointerToString(const char* str)
	{
		if (str == NULL)
			return NULL;

		return new String(str);
	}
};






class PixConverter
{
public:
	static Pix* CreateBinaryPix(unsigned char* binData, int width, int height)
	{
		Pix* pix = NULL;
		try
		{		
			pix = pixCreate(width, height, 1);
			
			l_uint32* pixData = pixGetData(pix);
			int wpl = pixGetWpl(pix);
			l_uint32 wtmp = 0;
			int index = 0;
			for (int y=0; y<height; y++)
			{
				wtmp = 0;
				int startLineWIndex = y * wpl;

				int bitIndex = 0;
				for (int x = 0; x < width; x++, index++)
				{
					if (bitIndex == 32)
					{
						pixData[startLineWIndex + ((x - 1) >> 5)] = wtmp;
						bitIndex = 0;
						wtmp = 0;
					}

					wtmp = wtmp | (binData[index] << (31 - bitIndex));

					bitIndex++;
				}

				if (bitIndex > 0)
				{
					pixData[startLineWIndex + (width - 1) >> 5] = wtmp;
				}
			}
		}
		catch (Exception* exp)
		{
			throw exp;
		}
		__finally
		{			
		}

		return pix;
	}

	static Pix* CreateGreyPix(unsigned char* greyData, int width, int height)
	{
		Pix* pix = NULL;
		try
		{		
			pix = pixCreate(width, height, 8);
			
			l_uint32* pixData = pixGetData(pix);
			int wpl = pixGetWpl(pix);
			l_uint32 wtmp = 0;
			int index = 0;
			for (int y=0; y<height; y++)
			{
				unsigned char* line = (unsigned char*)(pixData + y * wpl);
				for (int x = 0; x < width; x++, index++)
				{
					line[x] = greyData[index];
				}
			}
		}
		catch (Exception* exp)
		{
			throw exp;
		}
		__finally
		{			
		}

		return pix;
	}

	static Pix* CreateGreyPix(ushort* greyData, int width, int height)
	{
		Pix* pix = NULL;
		try
		{		
			pix = pixCreate(width, height, 8);
			
			l_uint32* pixData = pixGetData(pix);
			int wpl = pixGetWpl(pix);
			l_uint32 wtmp = 0;
			int index = 0;
			for (int y=0; y<height; y++)
			{
				unsigned char* line = (unsigned char*)(pixData + y * wpl);
				for (int x = 0; x < width; x++, index++)
				{
					line[x] = (unsigned char)greyData[index];
				}
			}
		}
		catch (Exception* exp)
		{
			throw exp;
		}
		__finally
		{			
		}

		return pix;
	}

	static Pix* PixFromImage(System::Drawing::Image* image)
	{
		Pix* pix = NULL;

		MemoryStream* mmsTmp = NULL;
		unsigned char srcTmp __gc[] = NULL;
		unsigned char* dstTmp = NULL;

		try
		{		
			/**
			Use memeory stream is easy solution, but poor effective.
			**/
			mmsTmp = new MemoryStream();
			image->Save(mmsTmp, System::Drawing::Imaging::ImageFormat::Tiff);

			int length = mmsTmp->Length;

			srcTmp = mmsTmp->GetBuffer();
			dstTmp = new unsigned char[length];
			System::Runtime::InteropServices::Marshal::Copy(srcTmp, 0, dstTmp, length);
			
			pix = pixReadMem(dstTmp, length);		
		}
		catch (Exception* exp)
		{
			throw exp;
		}
		__finally
		{
			if (mmsTmp != NULL)
			{
				mmsTmp->Close();
				mmsTmp = NULL;
			}

			if (srcTmp != NULL)
			{
				delete srcTmp;
				srcTmp = NULL;
			}

			if (dstTmp != NULL)
			{
				delete dstTmp;
				dstTmp = NULL;
			}
		}

		return pix;
	}
};






class TesseractConverter
{
public:
	static OcrEngineMode ParseOcrEngineMode(int oem)
	{
		return (OcrEngineMode)oem;
	}

	static PageIteratorLevel ParsePageLevel(int pageLevel)
	{
		return (PageIteratorLevel)pageLevel;
	}

	static PageSegMode ParsePageSegMode(int psm)
	{
		return (PageSegMode)psm;
	}
};

END_NAMESPACE
