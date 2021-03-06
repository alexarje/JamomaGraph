/* 
 * Jamoma Asynchronous Object Graph Layer
 * Creates a wrapper for TTObjects that can be used to build a control graph for asynchronous message passing.
 * Copyright © 2010, Timothy Place
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#include "TTGraphObject.h"
#include "TTGraphInlet.h"
#include "TTCallback.h"


void TTGraphInlet::getDescriptions(TTGraphDescriptionVector& descs)
{
	for (TTGraphSourceIter source = mSourceObjects.begin(); source != mSourceObjects.end(); source++) {
		TTGraphDescription	desc;
		
		source->getDescription(desc);
		descs.push_back(desc);
	}
}

