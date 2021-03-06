/* 
 * Jamoma Asynchronous Object Graph Layer
 * Creates a wrapper for TTObjects that can be used to build a control graph for asynchronous message passing.
 * Copyright © 2010, Timothy Place
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#include "TTGraphObject.h"
#include "TTGraphInput.h"

#define thisTTClass			TTGraphInput
#define thisTTClassName		"graph.input"
#define thisTTClassTags		"graph, input"


TT_OBJECT_CONSTRUCTOR,
	mOwner(NULL)
{
	;
}


TTGraphInput::~TTGraphInput()
{
	;
}


TTErr TTGraphInput::setOwner(TTGraphObjectPtr newOwner)
{
	mOwner = newOwner;
	return kTTErrNone;
}


TTErr TTGraphInput::push(const TTDictionary& aDictionary)
{
	if (mOwner) {
		return mOwner->push(aDictionary);
	}
	else {
		return kTTErrGeneric;
	}
}

