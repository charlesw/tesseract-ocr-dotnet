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
#include "pageiterator.h"


BEGIN_NAMSPACE

USING_COMMON_SYSTEM

USING_TESSERACT

USING_TESSERACT_ENGINE_WRAPPER

bool TesseractProcessor::InitForAnalysePage()
{
	try
	{
		this->EngineAPI->InitForAnalysePage();
		return true;
	}
	catch(System::Exception* exp)
	{
		throw exp;
	}
}

bool TesseractProcessor::SetPageSegMode(ePageSegMode psm)
{
	try
	{
		this->EngineAPI->SetPageSegMode(TesseractConverter::ParsePageSegMode(psm));
		return true;
	}
	catch(System::Exception* exp)
	{
		throw exp;
	}
}

DocumentLayout* TesseractProcessor::AnalyseLayout(System::Drawing::Image* image)
{
	if (image == null) return null;

	Pix* pix = null;
	try
	{
		pix = PixConverter::PixFromImage(image);

		return AnalyseLayout(pix);
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
}

DocumentLayout* TesseractProcessor::AnalyseLayoutBinaryImage(
	unsigned char* binData, int width, int height)
{
	Pix* pix = null;
	try
	{
		pix = PixConverter::CreateBinaryPix(binData, width, height);

		return AnalyseLayout(pix);
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
}

DocumentLayout* TesseractProcessor::AnalyseLayoutGreyImage(
	unsigned char* greyData, int width, int height)
{
	Pix* pix = null;
	try
	{
		pix = PixConverter::CreateGreyPix(greyData, width, height);

		return AnalyseLayout(pix);
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
}

DocumentLayout* TesseractProcessor::AnalyseLayoutGreyImage(
	unsigned short* greyData, int width, int height)
{
	Pix* pix = null;
	try
	{
		pix = PixConverter::CreateGreyPix(greyData, width, height);

		return AnalyseLayout(pix);
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
}

DocumentLayout* TesseractProcessor::AnalyseLayout(Pix* pix)
{
	if (pix == null) return null;

	TessBaseAPI* api = this->EngineAPI;
	if (api == null) return null;
	
	return this->AnalyseLayout(api, pix);
}

DocumentLayout* TesseractProcessor::AnalyseLayout(TessBaseAPI* api, Pix* pix)
{
	DocumentLayout* doc = new DocumentLayout();	

	PageIterator* pageIterator = null;
	
	try
	{
		api->SetImage(pix);
		pageIterator = api->AnalyseLayout();
		
		PageIterator* tmp = pageIterator;
		doc->CollectResult(tmp);
		tmp = null;
	}
	__finally
	{
		SAFE_DELETE(pageIterator);
	}

	return doc;
}

END_NAMESPACE