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

public __value enum eOcrEngineMode : int
{
	OEM_TESSERACT_ONLY = 0,				// Run Tesseract only - fastest
	OEM_CUBE_ONLY = 1,					// Run Cube only - better accuracy, but slower
	OEM_TESSERACT_CUBE_COMBINED = 2,	// Run both and combine results - best accuracy
	OEM_DEFAULT = 3						// Specify this mode when calling init_*(),
										// to indicate that any of the above modes
										// should be automatically inferred from the
										// variables in the language-specific config,
										// command-line configs, or if not specified
										// in any of the above should be set to the
										// default OEM_TESSERACT_ONLY.
};

public __value enum ePageSegMode : int
{
	PSM_OSD_ONLY = 0,				///< Orientation and script detection only.
	PSM_AUTO_OSD = 1,				///< Automatic page segmentation with orientation and
									///< script detection. (OSD)
	PSM_AUTO_ONLY = 2,				///< Automatic page segmentation, but no OSD, or OCR.
	PSM_AUTO = 3,					///< Fully automatic page segmentation, but no OSD.
	PSM_SINGLE_COLUMN = 4,			///< Assume a single column of text of variable sizes.
	PSM_SINGLE_BLOCK_VERT_TEXT = 5,	///< Assume a single uniform block of vertically
									///< aligned text.
	PSM_SINGLE_BLOCK = 6,			///< Assume a single uniform block of text. (Default.)
	PSM_SINGLE_LINE = 7,			///< Treat the image as a single text line.
	PSM_SINGLE_WORD = 8,			///< Treat the image as a single word.
	PSM_CIRCLE_WORD = 9,			///< Treat the image as a single word in a circle.
	PSM_SINGLE_CHAR = 10,			///< Treat the image as a single character.

	PSM_COUNT = 11					///< Number of enum entries.
};

public __value enum ePageLevel : int
{
	RIL_BLOCK = 0,     // Block of text/image/separator line.
	RIL_PARA = 1,      // Paragraph within a block.
	RIL_TEXTLINE = 2,  // Line within a paragraph.
	RIL_WORD = 3,      // Word within a textline.
	RIL_SYMBOL = 4,    // Symbol/character within a word.
	RIL_NOTSUPPORTED = 5
};

__gc public class CommonStructureWrapper
{
public:
	CommonStructureWrapper();
	~CommonStructureWrapper();
};

END_NAMESPACE
