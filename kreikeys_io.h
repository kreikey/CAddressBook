/*
 * kreikeys_io.h
 *
 *  Created on: Nov 30, 2012
 *      Author: rskreikebaum
 */

#ifndef KREIKEYS_IO_H_
#define KREIKEYS_IO_H_

#include "contact.h"
#include "contact_manager.h"

void printContact(const contact self);
void printContactToFile(const contact self, FILE* outputFile);
contact parseContactString(char* string);
void printCompareContacts(contact c1, contact c2);
void printContactManager(contactManager self);
void printContactManagerReverse(contactManager self);
void sanitize(char* string);

#endif /* KREIKEYS_IO_H_ */
