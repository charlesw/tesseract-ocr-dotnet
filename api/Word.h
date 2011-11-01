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
#include "RecognitionItem.h";
#include "Character.h"

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

__gc public class Word  : public RecognitionItem
{
public:
	Word();
	~Word();

public:
	// The line index for this word
	int LineIndex;

	// Blanks count
	int Blanks;

	// Some value directly copied from tessract
	int FontIndex, PointSize, Formating;

	// The text
	String* Text;
	
	// Character position
	List<Character*>* CharList;

public:	
	List<Word*>* UpdateConfidenceAndInsertTo(List<Word*>* wordList)
	{
		if (wordList == NULL)
			wordList = new List<Word*>();

		this->Confidence /= this->CharList->Count;
		wordList->Add(this);

		return wordList;
	}

public:
	String* ToString()
	{			
		return System::String::Format("{0} ({1})", Text->ToString(), Confidence.ToString());
	}

protected:
	RecognitionItem* CreateChild()
	{
		return new Character();
	}

	bool AddItem(RecognitionItem* item)
	{
		Character* ch = (Character*)item;
		CharList->Add(ch);

		return true;
	}
};



END_NAMESPACE