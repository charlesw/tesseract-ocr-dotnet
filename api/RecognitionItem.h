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
#include "CommonStructureWrapper.h"
#include "RectBound.h"
#include "..\ccstruct\publictypes.h"
#include "pageiterator.h"
#include "Helper.h"


BEGIN_NAMSPACE

USING_COMMON_SYSTEM

USING_TESSERACT

__gc public class RecognitionItem : public RectBound
{
public:
	// confidence : 0 = perfect; 255 = reject, over 160 = bad reco
	// This value is sensitive to Tesseract variable tessedit_write_ratings and tessedit_zero_rejection
	// After many test I found tessedit_write_ratings=true give the best result, this is the default mode
	Double Confidence;

public:
	RecognitionItem();
	~RecognitionItem();

	RecognitionItem(int left, int top, int right, int bottom)
		: RectBound(left, top, right, bottom)
	{
		Confidence = 0;
	}

	RecognitionItem(Double confidence, int left, int top, int right, int bottom)
		: RectBound(left, top, right, bottom)
	{
		Confidence = confidence;
	}

protected:
	Color _color;
	Pen* _pen;
public:
	__property Pen* get_DrawingPen()
	{
		if (_pen == null)
			_pen = new Pen(_color, 1.0f);

		return _pen;
	}

	void Draw(System::Drawing::Graphics* grph)
	{
		Pen* pen = this->DrawingPen;
		grph->DrawLine(pen, Left, Top, Right, Top);
		grph->DrawLine(pen, Right, Top, Right, Bottom);
		grph->DrawLine(pen, Right, Bottom, Left, Bottom);
		grph->DrawLine(pen, Left, Bottom, Left, Top);
	}

protected:
	ePageLevel _pageLevel;
protected:
	virtual PageIteratorLevel GetPageIteratorLevel()
	{
		return TesseractConverter::ParsePageLevel(_pageLevel);
	}

	virtual PageIteratorLevel GetNextPageIteratorLevel()
	{
		return TesseractConverter::ParsePageLevel((int)_pageLevel + 1);
	}

protected:
	virtual RecognitionItem* CreateChild()
	{
		return null;
	}		

	virtual bool AddItem(RecognitionItem* item)
	{
		return false;
	}

public:	
	virtual void CollectResult(PageIterator* pageIterator)
	{
		int left = 0, top = 0, right = 0, bottom = 0;
		RecognitionItem* child = this->CreateChild();
		if (child == null) // it is lowest level
		{			
			pageIterator->BoundingBox(
				this->GetPageIteratorLevel(), &left, &top, &right, &bottom);
			Left = left; Top = top; Right = right; Bottom = bottom;

			return;
		}
		
		PageIteratorLevel curLevel = this->GetPageIteratorLevel();
		PageIteratorLevel nextLevel = this->GetNextPageIteratorLevel();

		pageIterator->BoundingBox(curLevel, &left, &top, &right, &bottom);
		Left = left; Top = top; Right = right; Bottom = bottom;		

		if (pageIterator->IsAtBeginningOf(nextLevel))
		{
			// get the first item
			child->CollectResult(pageIterator);
			this->AddItem(child);

			if (pageIterator->IsAtFinalElement(curLevel, nextLevel))
				return;

			// get remaining items			
			while (pageIterator->Next(nextLevel))
			{
				child = this->CreateChild();
				child->CollectResult(pageIterator);
				this->AddItem(child);

				if (pageIterator->IsAtFinalElement(curLevel, nextLevel))
					break;
			}
		}
	}
};



END_NAMESPACE