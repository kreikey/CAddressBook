/*
 * contact.c
 *
 *  Created on: Nov 22, 2015
 *      Author: rskreikebaum
 */

#include "contact.h"
#define FIELDLEN 256

struct contactData_struct {	// The struct is 256*4 = 1024 bytes long, which is a multiple of four, so it's byte-aligned
	char lastName[FIELDLEN];
	char firstName[FIELDLEN];
	char eMail[FIELDLEN];
	char phoneNumber[FIELDLEN];
};

// Public

contact contact_create() {
	contact self = malloc(sizeof(struct contact_struct));
	self->data = malloc(sizeof(struct contactData_struct));
	self->next = NULL;
	self->prev = NULL;

	return self;
}

contact contact_createFromArgs(char* lname, char* fname, char* email, char* phnum) {
	contact self = contact_create();

	contact_setLastName(self, lname);
	contact_setFirstName(self, fname);
	contact_setEMail(self, email);
	contact_setPhoneNumber(self, phnum);

	return self;
}

const char* contact_getFirstName(const contact self) {
	static char firstName[FIELDLEN];
	strcpy(firstName, self->data->firstName);
	return firstName;
	// return self->data->firstName;
}

int contact_compare(const contact self, const contact other) {
	int result;

	result = strcmp(self->data->lastName, other->data->lastName);
	if (result == 0)
		result = strcmp(self->data->firstName, other->data->firstName);
	// if (result == 0)
	// 	result = strcmp(self->data->eMail, other->data->eMail);
	// if (result == 0)
	// 	result = strcmp(self->data->phoneNumber, other->data->phoneNumber);
	return result;

}

const char* contact_getLastName(const contact self) {
	static char lastName[FIELDLEN];
	strcpy(lastName, self->data->lastName);
	return lastName;
	// return self->data->lastName;
}

const char* contact_getPhoneNumber(const contact self) {
	static char phoneNumber[FIELDLEN];
	strcpy(phoneNumber, self->data->phoneNumber);
	return phoneNumber;
	// return self->data->phoneNumber;
}

const char* contact_getEMail(const contact self) {
	static char eMail[FIELDLEN];
	strcpy(eMail, self->data->eMail);
	return eMail;
	// return self->data->eMail;
}

void contact_setFirstName(contact self, char* fname) {
	strcpy(self->data->firstName, fname);
}

void contact_setLastName(contact self, char* lname) {
	strcpy(self->data->lastName, lname);
}

void contact_setPhoneNumber(contact self, char* phnum) {
	strcpy(self->data->phoneNumber, phnum);
}

void contact_setEMail(contact self, char* email) {
	strcpy(self->data->eMail, email);
}

void contact_destroy(contact self) {
	free(self->data);
	free(self);
}