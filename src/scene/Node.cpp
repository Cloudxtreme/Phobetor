/* Copyright 2014 Lasse Dissing
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Node.h"

Node::Node()
	: children() {}


int Node::GetNumberOfChildren() const {
	return children.size();
}

int Node::AttachChild(Spatial* child) {
	children.push_back(child);
	return children.size();
}

int Node::DetachChild(Spatial* child) {

	int index = GetIndexOfChild(child);

	if (index != -1) {
		Iterator_t pos = children.begin();
		std::advance(pos,index);
		children.erase(pos);
	}

	return children.size();	
}

void Node::DetachAllChildren() {
	children.clear();
}

bool Node::HasChild(Spatial* child) const {
	
	for (Spatial* spatial : children) {
		if (child == spatial) return true;
	}
	
	return false;
}

int Node::GetIndexOfChild(Spatial* child) const {

	for (ConstIterator_t iter = children.begin(); iter != children.end(); iter++) {
		if (child == *iter) return std::distance(children.begin(),iter);
	}

	return -1;
}

void Node::Render() {
	for (Spatial* spatial : children) {
		spatial->Render();
	}
}
