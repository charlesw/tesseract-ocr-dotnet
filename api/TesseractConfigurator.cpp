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
// GET/SET VARIABLES
bool TesseractProcessor::GetBoolVariable(System::String* name, bool __gc* value)
{
	if (_apiInstance == NULL)
		return false;

	TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();

	bool val = false;
	bool succeed = api->GetBoolVariable(Helper::StringToPointer(name), &val);
	*value = val;

	return succeed;
}

bool TesseractProcessor::GetIntVariable(System::String* name, int __gc* value)
{
	if (_apiInstance == NULL)
		return false;

	TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();

	int val = 0;
	bool succeed = api->GetIntVariable(Helper::StringToPointer(name), &val);
	*value = val;

	return succeed;
}

bool TesseractProcessor::GetDoubleVariable(System::String* name, double __gc* value)
{
	if (_apiInstance == NULL)
		return false;

	TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();

	double val = 0;
	bool succeed = api->GetDoubleVariable(Helper::StringToPointer(name), &val);
	*value = val;

	return succeed;
}

System::String* TesseractProcessor::GetStringVariable(System::String* name)
{
	if (_apiInstance == NULL)
		return false;

	TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();

	const char *value = api->GetStringVariable(Helper::StringToPointer(name));

	return Helper::PointerToString(value);
}

bool TesseractProcessor::SetVariable(System::String* name, System::String* value)
{
	if (_apiInstance == NULL)
		return false;

	TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();
	bool succeed = api->SetVariable(Helper::StringToPointer(name), Helper::StringToPointer(value));

	return succeed;
}
// ===============================================================


END_NAMESPACE