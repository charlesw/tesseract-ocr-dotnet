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

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

__gc public class RectBound
{
public:
	// Bounding
	int Left;
	int Right;
	int Top;
	int Bottom;

	// User object, you can assign any value you want
	Object* Tag;

public:
	RectBound();
	~RectBound();

	RectBound(int left, int top, int right, int bottom)
	{
		Left = left;
		Top = top;
		Right = right;
		Bottom = bottom;
	}
};

END_NAMESPACE