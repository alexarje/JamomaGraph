/* 
 * Jamoma Asynchronous Object Graph Layer
 * Creates a wrapper for TTObjects that can be used to build a control graph for asynchronous message passing.
 * Copyright © 2010, Timothy Place
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#ifndef __TTGRAPH_INLET_H__
#define __TTGRAPH_INLET_H__

#include "TTGraph.h"
//#include "TTGraphObject.h"
#include "TTGraphSource.h"
#include "TTGraphDescription.h"

/******************************************************************************************/

/**	This object represents a single 'inlet' to a TTGraphObject.
	TTGraphObject maintains a vector of these inlets.
*/
class TTGRAPH_EXPORT TTGraphInlet {
	TTGraphSourceVector		mSourceObjects;		///< A vector of object pointers from which we pull our source samples using the ::getAudioOutput() method.
	
public:
	TTGraphInlet()
	{
		;
	}

	~TTGraphInlet()
	{
		;
	}
	
		
	TTGraphInlet(const TTGraphInlet& original)
	{
		mSourceObjects	= original.mSourceObjects;
	}
	
	// The copy assignment constructor doesn't appear to be involved, at least with resizes, on the Mac...
	TTGraphInlet& operator=(const TTGraphInlet& source)
	{
		mSourceObjects	= source.mSourceObjects;		
		return *this;
	}
	
	
	// Graph Methods
	
	// reset
	void reset()
	{
		mSourceObjects.clear();
	}
		
	
	TTErr connect(TTGraphObjectPtr anObject, TTUInt16 fromOutletNumber)
	{
		TTUInt16 size = mSourceObjects.size();
		
		// make sure the connection doesn't already exist
		for (TTGraphSourceIter source = mSourceObjects.begin(); source != mSourceObjects.end(); source++) {
			if (source->match(anObject, fromOutletNumber))
				return kTTErrNone;
		}
		
		// create the connection
		mSourceObjects.resize(size+1);
		mSourceObjects[size].connect(anObject, fromOutletNumber);
		mSourceObjects[size].setOwner(this);
		return kTTErrNone;
	}
	
	
	TTErr drop(TTGraphObjectPtr anObject, TTUInt16 fromOutletNumber)
	{
		for (TTGraphSourceIter source = mSourceObjects.begin(); source != mSourceObjects.end(); source++) {
			if (source->match(anObject, fromOutletNumber)) {
				drop(*source);
				break;
			}
		}
		return kTTErrNone;
	}
	
	
	void drop(TTGraphSource& aSource)
	{
		TTGraphSourceIter iter = find(mSourceObjects.begin(), mSourceObjects.end(), aSource);
		
		if (iter != mSourceObjects.end())
			mSourceObjects.erase(iter);
	}
		
	
	void getDescriptions(TTGraphDescriptionVector& descs);
	
};

typedef TTGraphInlet*					TTGraphInletPtr;
typedef vector<TTGraphInlet>			TTGraphInletVector;
typedef TTGraphInletVector::iterator	TTGraphInletIter;


#endif // __TTGRAPH_INLET_H__
