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
#include "Block.h"

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

__gc public class DocumentLayout : public RecognitionItem
{
public:
	DocumentLayout();
	~DocumentLayout();

protected:
	List<Block*>* _blocks;

public:
	__property List<Block*>* get_Blocks()
	{
		return _blocks;
	}

public:
	String* ToString()
	{
		return System::String::Format(
			"DocumentLayout: {0} blocks", _blocks->Count.ToString());
	}

protected:
	PageIteratorLevel GetPageIteratorLevel()
	{
		return PageIteratorLevel::RIL_BLOCK;
	}

	PageIteratorLevel GetNextPageIteratorLevel()
	{
		return PageIteratorLevel::RIL_BLOCK;
	}

	RecognitionItem* CreateChild()
	{
		return new Block();
	}

	bool AddItem(RecognitionItem* item)
	{
		Block* block = (Block*)item;
		_blocks->Add(block);

		return true;
	}
};

END_NAMESPACE