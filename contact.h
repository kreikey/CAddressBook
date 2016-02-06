/*
 * contact.h
 *
 *  Created on: Nov 16, 2012
 *      Author: rskreikebaum
 */

#ifndef CONTACT_H_
#define CONTACT_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FIELDLEN 256

typedef struct contact_struct* contact;
typedef struct contactData_struct* contactData;

struct contact_struct {
 	contactData data;
	contact next;
 	contact prev;
 };

 struct contact_type {
 	contact (*create)();
 	contact (*createFromArgs) (char*, char*, char*, char*);
	const char* (*getFirstName) (const contact);		// 4 bytes
	const char* (*getLastName) (const contact);		// 4 bytes
	const char* (*getPhoneNumber) (const contact);	// 4 bytes
	const char* (*getEMail) (const contact);			// 4 bytes
	void (*setFirstName) (contact, char*);		// 4 bytes
	void (*setLastName) (contact, char*);		// 4 bytes
	void (*setPhoneNumber) (contact, char*);	// 4 bytes
	void (*setEMail) (contact, char*);			// 4 bytes
	int (*compare) (const contact, const contact);		// 4 bytes
	void (*destroy) (contact);	
 };

contact contact_create();
contact contact_createFromArgs(char* lname, char* fname, char* email, char* phnum);
const char* contact_getFirstName(const contact self);
const char* contact_getLastName(const contact self);
const char* contact_getPhoneNumber(const contact self);
const char* contact_getEMail(const contact self);
void contact_setFirstName(contact self, char* fname);
void contact_setLastName(contact self, char* lname);
void contact_setPhoneNumber(contact self, char* phnum);
void contact_setEMail(contact self, char* email);
int contact_compare(const contact self, const contact other);
void contact_destroy(contact self);

// static is key and makes this whole thing work
static struct contact_type Contact = {
 	.create = contact_create,
 	.createFromArgs = contact_createFromArgs,
 	.getFirstName = contact_getFirstName,
 	.getLastName = contact_getLastName,
 	.getPhoneNumber = contact_getPhoneNumber,
 	.getEMail = contact_getEMail,
 	.setFirstName = contact_setFirstName,
 	.setLastName = contact_setLastName,
 	.setPhoneNumber = contact_setPhoneNumber,
 	.setEMail = contact_setEMail,
 	.compare = contact_compare,
 	.destroy = contact_destroy
 };

#endif /* CONTACT_H_ */
