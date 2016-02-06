/*
 * contact_manager.c
 *
 *  Created on: Nov 16, 2012
 *      Author: rskreikebaum
 */

#include "contact_manager.h"

static void extract(contactManager self, contact exNode);

// Data Types
struct contactManagerData {
	contact cur;
	int length;
	int index;
};

// Public methods
// Create and destroy
contactManager contactManager_create() {
	contactManager self = malloc(sizeof(struct contactManager_struct));
	self->data = malloc(sizeof(struct contactManagerData));
	self->data->cur = NULL;
	self->data->length = 0;
	self->data->index = 0;

	return self;
}

contactManager contactManager_createFromOld(contactManager self, int length) {
	// This creates a sublist from an existing ContactManager.
	// getPrev and getNext will gladly go out of bounds on the first and last node, respectively.
	// The sublist has its own size information, which must be less than the size of the original list.
	// The new sublist starts at the cur pointer of the current list. 

	// Handle error case where length of sublist is greater than length of original.
	if (length > self->data->length) {
		// printf ("Error. Length of sublist is greater than length of original.\n");
		return NULL;
	}
	contactManager addressBookSlice = contactManager_create();
	addressBookSlice->data->length = length;
	addressBookSlice->data->cur = self->data->cur;
	return addressBookSlice;
}

void contactManager_destroy(contactManager self) {
	while (self->data->cur != NULL)
		ContactManager.deleteCur(self);

	free(self->data);
	free(self);
}

// Contact getter and iteration methods
contact contactManager_getCur(contactManager self) {
	// Gets the current contact
	return self->data->cur;
}

contact contactManager_getNext(contactManager self) {
	if (self->data->cur != NULL) {
		self->data->cur = self->data->cur->next;
		self->data->index++;

		if (self->data->index == self->data->length) {
			self->data->index = 0;
			// sublists go out of bounds when you getNext() on their last node
		}
	}
	return self->data->cur;
}

contact contactManager_getPrev(contactManager self) {
	if (self->data->cur != NULL) {
		if (self->data->index == 0)		// looping to the end is NOT supported for sublists!
			self->data->index = (self->data->length - 1);
		else
			self->data->index--;
		self->data->cur = self->data->cur->prev;
	}
	return self->data->cur;
}

contact contactManager_getByIndex(contactManager self, int target) {
	int ndx;
	int len;
	int forwardDistance;
	int backwardDistance;

	if (target < 0 || target >= self->data->length)
		return NULL;

	ndx = self->data->index;
	len = self->data->length;

	if (target >= ndx) {
		forwardDistance = target - ndx;
		backwardDistance = ndx + len - target;
	} else {
		forwardDistance = len - ndx + target;
		backwardDistance = ndx - target;
	}

	if (forwardDistance < backwardDistance) {
		// printf("iterating forwards\n");
		while (self->data->index != target)
			ContactManager.getNext(self);
		// printf("done\n\n");
	} else {
		// printf("iterating backwards\n");
		while (self->data->index != target) {
			ContactManager.getPrev(self);
		}
		// printf("done\n\n");
	}

	return self->data->cur;
}

// Metadata getter methods
int contactManager_getIndex(contactManager self) {
	return self->data->index;
}

int contactManager_getLength(contactManager self) {
	return self->data->length;
}

bool contactManager_isEmpty(contactManager self) {
	if (self->data->length == 0)
		return true;
	else
		return false;
}

// Modification and creation methods
void contactManager_insertAfterCur(contactManager self, contact input) {
	if (self->data->length == 0) {
		input->next = input;
		input->prev = input;
		self->data->cur = input;
	} else {
		input->prev = self->data->cur;
		input->next = self->data->cur->next;
		input->prev->next = input;
		input->next->prev = input;
		self->data->index++;
	}
	self->data->length++;
	self->data->cur = self->data->cur->next;
}

void contactManager_insertBeforeCur(contactManager self, contact input) {
	if (self->data->length == 0) {
		input->next = input;
		input->prev = input;
		self->data->cur = input;
	} else {
		input->next = self->data->cur;
		input->prev = self->data->cur->prev;
		input->prev->next = input;
		input->next->prev = input;
	}
	self->data->length++;
	self->data->cur = self->data->cur->prev;
}

contact contactManager_removeCur(contactManager self) {
	contact temp = self->data->cur;

	if (self->data->length == 0)
		return NULL;
	else if (self->data->index == (self->data->length - 1)) {
		if (self->data->length == 1) {
			self->data->cur = NULL;
		} else {
			self->data->cur = temp->prev;
			self->data->index--;
		}
	}
	else {
		self->data->cur = temp->next;
	}

	self->data->length--;

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->prev = NULL;
	temp->next = NULL;

	return temp;
}

void contactManager_deleteCur(contactManager self) {
	contact temp;

	temp = contactManager_removeCur(self);
	if (temp != NULL)
		Contact.destroy(temp);
}
