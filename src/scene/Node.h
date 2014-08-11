/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include <Phobetor.h>
#include "Spatial.h"

class Node: public Spatial {


public:
								Node();

	int							GetNumberOfChildren() const;
	int							AttachChild(Spatial* child);
	int							DetachChild(Spatial* child);
	void						DetachAllChildren();
	bool						HasChild(Spatial* child) const;
	const std::list<Spatial*>	GetChildren() const;

	virtual SpatialType			GetSpatialType() const;
	
	
protected:

	virtual void		UpdateWorldData();

	int 				GetIndexOfChild(Spatial* child) const;

	std::list<Spatial*> children;

	typedef std::list<Spatial*>::const_iterator ConstIterator_t;
	typedef std::list<Spatial*>::iterator Iterator_t;


};

#endif //__SCENE_NODE_H__
