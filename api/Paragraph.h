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
#include "TextLine.h"

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

__gc public class Paragraph : public RecognitionItem
{
public:
	Paragraph();
	~Paragraph();

protected:
	List<TextLine*>* _lines;

public:
	__property List<TextLine*>* get_Lines()
	{
		return _lines;
	}
	
protected:
	RecognitionItem* CreateChild()
	{
		return new TextLine();
	}

	bool AddItem(RecognitionItem* item)
	{
		TextLine* line = (TextLine*)item;
		_lines->Add(line);

		return true;
	}
};


END_NAMESPACE