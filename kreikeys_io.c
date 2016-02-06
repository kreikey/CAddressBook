/*
 * kreikeys_io.c
 *
 *  Created on: Nov 30, 2012
 *      Author: rskreikebaum
 */

#include "kreikeys_io.h"
#include <ctype.h>

void printContact(const contact self) {
	printf("%s,", Contact.getLastName(self));
	printf("%s,", Contact.getFirstName(self));
	printf("%s,", Contact.getEMail(self));
	printf("%s\n", Contact.getPhoneNumber(self));
}
void printContactToFile(const contact self, FILE* outputFile) {
	fprintf(outputFile, "%s,", Contact.getLastName(self));
	fprintf(outputFile, "%s,", Contact.getFirstName(self));
	fprintf(outputFile, "%s,", Contact.getEMail(self));
	fprintf(outputFile, "%s\n", Contact.getPhoneNumber(self));
}
contact parseContactString(char* string) {
	char* firstName;
	char* lastName;
	char* email;
	char* phoneNumber;
	contact c = NULL;

	lastName = strtok(string, ",");
	firstName = strtok(NULL, ",");
	email = strtok(NULL, ",");
	phoneNumber = strtok(NULL, ",");
	if (firstName && lastName && email && phoneNumber)
		c = Contact.createFromArgs(lastName, firstName, email, phoneNumber);

	return c;
}
void printCompareContacts(contact c1, contact c2) {
	int cmpResult;
	cmpResult = Contact.compare(c1, c2);
//	cmpResult = compareTo(c1, c2);

	if (cmpResult < 0) {
		printContact(c1);
		printf("<\n");
		printContact(c2);
	}
	else if (cmpResult > 0) {
		printContact(c1);
		printf(">\n");
		printContact(c2);
	}
	else {
		printContact(c1);
		printf("=\n");
		printContact(c2);
	}
	printf("\n");
}
void printContactManager(contactManager self) {
	printf("----------------------------------\n");
	ContactManager.getByIndex(self, 0);
	do {
		printContact(ContactManager.getCur(self));
		ContactManager.getNext(self);
	} while(ContactManager.getIndex(self) > 0);
	printf("----------------------------------\n");
}
void printContactManagerReverse(contactManager self) {
	printf("----------------------------------\n");
	ContactManager.getByIndex(self, 0);
	ContactManager.getPrev(self);
	do {
		printContact(ContactManager.getCur(self));
		ContactManager.getPrev(self);
	} while(ContactManager.getIndex(self) < (ContactManager.getLength(self) - 1));
	printf("----------------------------------\n");	
}
void sanitize(char* string) {
	int ndx = strlen(string) - 1;

	while (isspace(string[ndx]) && (ndx >= 0)) {		// Is it safe to have a null string?
		string[ndx] = '\0';
		ndx--;
	}
}
