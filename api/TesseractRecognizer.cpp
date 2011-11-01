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

#include "TesseractEngineWrapper.h"
#include "Configuration.h"
#include "Helper.h"
#include "Character.h"
#include "Word.h"


BEGIN_NAMSPACE

USING_COMMON_SYSTEM

USING_TESSERACT

USING_TESSERACT_ENGINE_WRAPPER



String* TesseractProcessor::Recognize(String* filePath)
{
	String* result = "";

	STRING text_out;

	if (_useROI && _roi != System::Drawing::Rectangle::Empty)
	{
		this->EngineAPI->SetRectangle(
			_roi.Left, _roi.Top, _roi.Width, _roi.Height);
	}

	bool succed = this->EngineAPI->ProcessPages(
		Helper::StringToPointer(filePath), null, 0, &text_out);
	
	const char* text = text_out.string();
	result = new String(text, 0, strlen(text), Encoding::UTF8);

	return result;
}

String* TesseractProcessor::Recognize(System::Drawing::Image* image)
{
	if (_apiInstance == null || image == null)
		return null;

	String* result = "";
	Pix* pix = null;

	try
	{
		pix = PixConverter::PixFromImage(image);

		result = this->Process(this->EngineAPI, pix);
	}
	catch (System::Exception* exp)
	{
		throw exp;
	}
	__finally
	{
		if (pix != null)
		{
			pixDestroy(&pix);
			pix = null;
		}
	}

	return result;
}

String* TesseractProcessor::RecognizeBinaryImage(
	unsigned char* binData, int width, int height)
{
	if (_apiInstance == null)
		return null;

	String* result = "";
	Pix* pix = null;

	try
	{
		pix = PixConverter::CreateBinaryPix(binData, width, height);

		result = this->Process(this->EngineAPI, pix);
	}
	catch (System::Exception* exp)
	{
		throw exp;
	}
	__finally
	{
		if (pix != null)
		{
			pixDestroy(&pix);
			pix = null;
		}
	}

	return result;
}

String* TesseractProcessor::RecognizeGreyImage(
	unsigned char* greyData, int width, int height)
{
	if (_apiInstance == null)
		return null;

	String* result = "";
	Pix* pix = null;

	try
	{
		pix = PixConverter::CreateGreyPix(greyData, width, height);

		result = this->Process(this->EngineAPI, pix);
	}
	catch (System::Exception* exp)
	{
		throw exp;
	}
	__finally
	{
		if (pix != null)
		{
			pixDestroy(&pix);
			pix = null;
		}
	}

	return result;
}

String* TesseractProcessor::RecognizeGreyImage(
	unsigned short* greyData, int width, int height)
{
	if (_apiInstance == null)
		return null;

	String* result = "";
	Pix* pix = null;

	try
	{
		pix = PixConverter::CreateGreyPix(greyData, width, height);

		result = this->Process(this->EngineAPI, pix);
	}
	catch (System::Exception* exp)
	{
		throw exp;
	}
	__finally
	{
		if (pix != null)
		{
			pixDestroy(&pix);
			pix = null;
		}
	}

	return result;
}

String* TesseractProcessor::Process(Pix* pix)
{
	return this->Process(this->EngineAPI, pix);
}

String* TesseractProcessor::Process(TessBaseAPI* api, Pix* pix)
{
	if (api == null || pix == null)
		return null;

	api->SetImage(pix);

	if (_useROI && _roi != System::Drawing::Rectangle::Empty)
	{
		int left = 0, top = 0, width = 0, height = 0;
		this->GetROI(
			pix->w, pix->h, left, top, width, height);
		if (width > 0 && height > 0)
		{
			api->SetRectangle(left, top, width, height);
		}
	}

	bool succed = api->Recognize(null) >= 0;

	char* text = api->GetUTF8Text();
	String* result = new String(text, 0, strlen(text), Encoding::UTF8);

	delete text;
	
	return result;
}

END_NAMESPACE