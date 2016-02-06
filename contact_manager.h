/*
 * contact_manager.h
 *
 *  Created on: Nov 16, 2012
 *      Author: rskreikebaum
 */

/*TODO:
 * Get rid of isCurFirst, isCurLast, and wentPastEnd. They're redundant.
 * Instead we should focus on using index and length to determine position
 * and find nodes. isEmpty might go too.
*/
 
#ifndef CONTACT_MANAGER_H_
#define CONTACT_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contact.h"

typedef struct contactManager_struct* contactManager;
typedef struct contactManagerData* contactManagerData;

struct contactManager_struct {
	contactManagerData data;
};

struct contactManager_type {
 	contactManager (*create) ();
 	contactManager (*createFromOld) (contactManager, int);
 	void (*destroy) (contactManager);
	contact (*getCur) (contactManager);
	contact (*getNext) (contactManager);
	contact (*getPrev) (contactManager);
 	contact (*getByIndex) (contactManager, int);
	int (*getIndex) (contactManager);
	int (*getLength) (contactManager);
	bool (*isEmpty) (contactManager);
 	void (*insertAfterCur) (contactManager, contact);
 	void (*insertBeforeCur) (contactManager, contact);
 	contact (*removeCur) (contactManager);
 	void (*deleteCur) (contactManager);
};

// Constructors and destructor
contactManager contactManager_create();
contactManager contactManager_createFromOld(contactManager self, int length);
void contactManager_destroy(contactManager self);
// Contact getter and iteration methods
contact contactManager_getCur(contactManager self);
contact contactManager_getNext(contactManager self);
contact contactManager_getPrev(contactManager self);
contact contactManager_getByIndex(contactManager self, int index);
// Metadata getter methods
int contactManager_getIndex(contactManager self);
int contactManager_getLength(contactManager self);
bool contactManager_isEmpty(contactManager self);
// Modification methods
void contactManager_insertAfterCur(contactManager self, contact input);
void contactManager_insertBeforeCur(contactManager self, contact input);
contact contactManager_removeCur(contactManager self);
void contactManager_deleteCur(contactManager self);

static struct contactManager_type ContactManager = {
	.create = contactManager_create,
	.createFromOld = contactManager_createFromOld,
	.destroy = contactManager_destroy,
	.getCur = contactManager_getCur,
	.getNext = contactManager_getNext,
	.getPrev = contactManager_getPrev,
	.getByIndex = contactManager_getByIndex,
	.getIndex = contactManager_getIndex,
	.getLength = contactManager_getLength,
	.isEmpty = contactManager_isEmpty,
	.insertAfterCur = contactManager_insertAfterCur,
	.insertBeforeCur = contactManager_insertBeforeCur,
	.removeCur = contactManager_removeCur,
	.deleteCur = contactManager_deleteCur
};

#endif /* CONTACT_MANAGER_H_ */
