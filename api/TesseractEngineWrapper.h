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
#include "..\api\baseapi.h"
#include "CommonStructureWrapper.h"
#include "Word.h"
#include "DocumentLayout.h"

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

USING_TESSERACT

USING_TESSERACT_ENGINE_WRAPPER

__gc public class TesseractProcessor : public IDisposable
{	
private:
	String* _dataPath;
	String* _lang;
	int _ocrEngineMode;

protected:
	bool _useROI;
	System::Drawing::Rectangle _roi;

	void GetROI(int imageWidth, int imageHeight, 
		int &left, int &top, int &width, int &height)
	{
		left = (_roi.Left >=0 ? _roi.Left : 0);
		top = (_roi.Top >= 0 ? _roi.Top : 0);
		
		int right = (_roi.Right < imageWidth ? _roi.Right : (imageWidth - 1));
		int bottom = (_roi.Bottom < imageHeight ? _roi.Bottom : (imageHeight - 1));

		width = right - left + 1;
		height = bottom - top + 1;
	}

public:	
	__property bool get_UseROI()
	{
		return _useROI;
	}

	__property void set_UseROI(bool useROI)
	{
		_useROI = useROI;
	}

	__property System::Drawing::Rectangle get_ROI()
	{
		return _roi;
	}
	
	__property void set_ROI(System::Drawing::Rectangle roi)
	{
		_roi = roi;
	}

private:
	System::IntPtr _apiInstance;
private:
	__property TessBaseAPI* get_EngineAPI()
	{
		if (_apiInstance == null)
			return null;

		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();

		return api;
	}

public:	
	TesseractProcessor();
	~TesseractProcessor();

public:
	void Dispose()
	{
		Dispose(TRUE);
	}

protected:
	virtual void Dispose(bool disposing)
	{
		if (disposing)
		{
			InternalFinally();
		}
	}

public:
	String* GetTesseractEngineVersion();

	bool Init();
	bool Init(String* dataPath, String* lang, int ocrEngineMode);

	void Clear();
	void ClearResults();
	void ClearAdaptiveClassifier();

	void End();

public:
	bool GetBoolVariable(System::String* name, bool __gc* value);
	bool GetIntVariable(System::String* name, int __gc* value);
	bool GetDoubleVariable(System::String* name, double __gc* value);
	System::String* GetStringVariable(System::String* name);

	bool SetVariable(System::String* nam, System::String* value);

	void DisableThresholder();
	void UseThresholder();
private:
	void InitializeWorkingSpace();
	void InitializeEngineAPI();

	void InternalFinally();



public:
	//
	// Recognize text from image file
	//
	String* Recognize(String* filePath);

	//
	// Recognize text from image
	//
	String* Recognize(System::Drawing::Image* image);

	//
	// Recognize text from binary image
	//
	String* RecognizeBinaryImage(unsigned char* binData, int width, int height);

	//
	// Recognize text from grey image (8-bits per pixel)
	//
	String* RecognizeGreyImage(unsigned char* greyData, int width, int height);

	//
	// Recognize text from grey image (depth: 8bpp, internal_format: 16 bits per pixel)
	//
	String* RecognizeGreyImage(unsigned short* greyData, int width, int height);




private:
	String* Process(Pix* pix);
	String* Process(TessBaseAPI* api, Pix* pix);




public:
	//
	// Initialize tesseract for page-layout analysis
	//
	bool InitForAnalysePage();

	//
	// Set page-layout segmentation mode
	//
	bool SetPageSegMode(ePageSegMode psm);

	//
	// AnalyseLayout interfaces
	//
	DocumentLayout* AnalyseLayout(System::Drawing::Image* image);
	DocumentLayout* AnalyseLayoutBinaryImage(unsigned char* binData, int width, int height);
	DocumentLayout* AnalyseLayoutGreyImage(unsigned char* greyData, int width, int height);
	DocumentLayout* AnalyseLayoutGreyImage(unsigned short* greyData, int width, int height);





private:
	DocumentLayout* AnalyseLayout(Pix* pix);
	DocumentLayout* AnalyseLayout(TessBaseAPI* api, Pix* pix);
};

END_NAMESPACE