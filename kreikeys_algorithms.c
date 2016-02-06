/*
 * kreikeys_algorithms.c
 *
 *  Created on: Nov 29, 2012
 *      Author: rskreikebaum
 */

#include "kreikeys_algorithms.h"

static contactManager merge(contactManager left, contactManager right);
static void split(contactManager self, contactManager* left, contactManager* right);

void mergeSort(contactManager* pAddressBook) {
	contactManager left;
	contactManager right;

	if (ContactManager.getLength(*pAddressBook) <= 1)
		return;

	split(*pAddressBook, &left, &right);
	mergeSort(&left);
	mergeSort(&right);
	free((*pAddressBook)->data);
	free(*pAddressBook);
	*pAddressBook = merge(left, right);
}

static void split(contactManager self, contactManager* left, contactManager* right) {
	int leftLength;
	int rightLength;

	leftLength = ContactManager.getLength(self) / 2;
	rightLength = ContactManager.getLength(self) - leftLength;

	ContactManager.getByIndex(self, 0);
	*left = ContactManager.createFromOld(self, leftLength);

	while (ContactManager.getIndex(self) < leftLength)
		ContactManager.getNext(self);
	
	*right = ContactManager.createFromOld(self, rightLength);
}

static contactManager merge(contactManager left, contactManager right) {
	contactManager result;
	result = ContactManager.create();
	contact lc;
	contact rc;

	while (!ContactManager.isEmpty(left) && !ContactManager.isEmpty(right)) {
		lc = ContactManager.getCur(left);
		rc = ContactManager.getCur(right);

		while (!ContactManager.isEmpty(left) && Contact.compare(ContactManager.getCur(left), rc) < 0)
			ContactManager.insertAfterCur(result, ContactManager.removeCur(left));

		lc = ContactManager.getCur(left);
		if (!lc)
			continue;
		// We need to make sure BOTH lists are not empty
		while (!ContactManager.isEmpty(right) && Contact.compare(ContactManager.getCur(right), lc) <= 0)
			ContactManager.insertAfterCur(result, ContactManager.removeCur(right));
	}

	while (!ContactManager.isEmpty(left))
		ContactManager.insertAfterCur(result, ContactManager.removeCur(left));

	while (!ContactManager.isEmpty(right))
		ContactManager.insertAfterCur(result, ContactManager.removeCur(right));
	
	// getByIndex is not supported for sublists.
	// This works because result is a brand-new list, not a sublist. I never use this function on a sublist.
	ContactManager.getByIndex(result, 0);	
	
	free(left->data);
	free(left);
	free(right->data);
	free(right);

	return result;
}
