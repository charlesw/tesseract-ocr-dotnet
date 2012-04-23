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

// ===============================================================
// CONTRUCTORS AND DESTRUCTORS
TesseractProcessor::TesseractProcessor()
{
	InitializeWorkingSpace();

	_useROI = false;
}

TesseractProcessor::~TesseractProcessor()
{
	InternalFinally();
}
// ===============================================================



// ===============================================================
// INITIALIZE CLASS
void TesseractProcessor::InitializeWorkingSpace()
{
	InitializeEngineAPI();
}
	
void TesseractProcessor::InitializeEngineAPI()
{
	if (_apiInstance == null)
	{
		TessBaseAPI* api = new TessBaseAPI();

		if (api == NULL)
		{
			throw new System::Exception(
				"Failed to create TessBaseAPI instance!");
		}

		_apiInstance = api;
	}
	else
	{
		this->Clear();
	}
}

void TesseractProcessor::InternalFinally()
{
	if (_apiInstance != NULL)
	{
		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();

		api->End();

		delete api;
		api = null;

		_apiInstance = NULL;
	}
}
// ===============================================================


// ===============================================================
// MAIN INITIALIZE TESSERACT AND WRAPPER MAIN METHODS
bool TesseractProcessor::Init()
{
	bool bSucced = false;

	if (_apiInstance != NULL)
	{
		bSucced = this->Init(NULL, "eng", 3);
	}

	return bSucced;
}

bool TesseractProcessor::Init(String* dataPath, String* lang, int ocrEngineMode)
{
	bool bSucced = false;

	// Append required trailing slash if missing
	String* separator = (System::IO::Path::DirectorySeparatorChar).ToString();
	if(!dataPath->EndsWith(separator))
	{
		dataPath = System::String::Concat(dataPath, separator);
	}

	_dataPath = dataPath;
	_lang = lang;
	_ocrEngineMode = ocrEngineMode;

	if (_apiInstance != NULL)
	{
		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();
		bSucced = api->Init(
			Helper::StringToPointer(dataPath), 
			Helper::StringToPointer(lang),
			TesseractConverter::ParseOcrEngineMode(ocrEngineMode)) >= 0;
	}

	return bSucced;
}

String* TesseractProcessor::GetTesseractEngineVersion()
{
	if (_apiInstance != NULL)
	{
		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();
		return Helper::PointerToString(api->Version());
	}

	return NULL;
}


void TesseractProcessor::Clear()
{
	if (_apiInstance != NULL)
	{
		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();
		api->Clear();
	}
}

void TesseractProcessor::ClearResults()
{
	if (_apiInstance != NULL)
	{	
		this->Clear(); //should call _apiInstance->ClearResults(), but it is internal function.
	}
}

void TesseractProcessor::ClearAdaptiveClassifier()
{
	if (_apiInstance != NULL)
	{
		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();
		api->ClearAdaptiveClassifier();
	}
}

void TesseractProcessor::End()
{
	if (_apiInstance != NULL)
	{
		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();
		api->End();
	}
}
// ===============================================================

END_NAMESPACE