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
#include "RecognitionItem.h"
#include "Paragraph.h"
#include "pageiterator.h"

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

USING_TESSERACT

__gc public class Block : public RecognitionItem
{

public:
	Block();
	~Block();

protected:
	List<Paragraph*>* _paragraphs;

public:
	__property List<Paragraph*>* get_Paragraphs()
	{
		return _paragraphs;
	}
		
protected:
	RecognitionItem* CreateChild()
	{
		return new Paragraph();
	}

	bool AddItem(RecognitionItem* item)
	{
		Paragraph* paragraph = (Paragraph*)item;
		_paragraphs->Add(paragraph);

		return true;
	}
};


END_NAMESPACE
