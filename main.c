/*
 ============================================================================
 Name        : RKreikebaumAddressBook.c
 Author      : Rick Kreikebaum
 Version     : 4.0
 Copyright   : Copyright 2012, 2015
 Description : An Address Book program. It can add, delete, and get a contact.
	 It can get a certain field of a contact. It can get the number of contacts.
	 It can load a list of contacts from a file. It can save a list of contacts
	 to a file. It can edit a contact. And it can MergeSort a list of contacts too.
	 It can also print the whole list of contacts, and print them in reverse order.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact_manager.h"
#include "kreikeys_algorithms.h"
#include "kreikeys_io.h"

void addContact(contactManager addressBook, int ndx, char* contactString);
void deleteContact(contactManager addressBook, int ndx);
void getContact(contactManager addressBook, int ndx);
void getField(contactManager addressBook, int ndx, char* fieldName);
void getNumContacts(contactManager addressBook);
void loadFile(contactManager addressBook, char* filePath);
void saveToFile(contactManager addressBook, char* filePath);
void editContact(contactManager addressBook, int ndx, char* fieldName, char* fieldNewValue);

int main(void) {
	char inputBuf[BUFSIZ+1];
	char param1[BUFSIZ+1];
	char param2[BUFSIZ+1];
	char param3[BUFSIZ+1];
	int ndx;

	setvbuf(stdout, NULL, _IONBF, 0);
	contactManager addressBook = ContactManager.create();
	printf("Ready\n");

	do {
		fgets(inputBuf, BUFSIZ, stdin);
		sanitize(inputBuf);
		switch(inputBuf[0]) {
		case 'a':
			ndx = atoi(fgets(param1, BUFSIZ, stdin));
			fgets(param2, BUFSIZ, stdin);
			sanitize(param2);		/* sanitize the string by getting rid of trailing whitespace */
			addContact(addressBook, ndx, param2);
			break;
		case 'd':
			ndx = atoi(fgets(param1, BUFSIZ, stdin));
			deleteContact(addressBook, ndx);
			break;
		case 'g':
			ndx = atoi(fgets(param1, BUFSIZ, stdin));
			getContact(addressBook, ndx);
			break;
		case 'f':
			ndx = atoi(fgets(param1, BUFSIZ, stdin));
			fgets(param2, BUFSIZ, stdin);
			sanitize(param2);
			getField(addressBook, ndx, param2);
			break;
		case 'n':
			getNumContacts(addressBook);
			break;
		case 'l':
			fgets(param1, BUFSIZ, stdin);
			sanitize(param1);
			loadFile(addressBook, param1);
			break;
		case 's':
			fgets(param1, BUFSIZ, stdin);
			sanitize(param1);
			saveToFile(addressBook, param1);
			break;
		case 'e':
			ndx = atoi(fgets(param1, BUFSIZ, stdin));
			fgets(param2, BUFSIZ, stdin);
			sanitize(param2);
			fgets(param3, BUFSIZ, stdin);
			sanitize(param3);
			editContact(addressBook, ndx, param2, param3);
			break;
		case 'o':
			mergeSort(&addressBook);
			printf("Sorted\n");
			break;
		case 'p':
			printContactManager(addressBook);
			break;
		case 'r':
			printContactManagerReverse(addressBook);
			break;
		case 'q':
			break;
		default:
			printf("Unrecognized command. Valid commands: a, d, g, f, n, l, s, e, o, p, r, q\n");
		}
	} while(inputBuf[0] != 'q');

	ContactManager.destroy(addressBook);

	printf("Complete\n");
	return EXIT_SUCCESS;
}

void addContact(contactManager addressBook, int ndx, char* contactString) {
	contact c;

	c = parseContactString(contactString);
	if (c == NULL)
		return;
	if (ndx > ContactManager.getLength(addressBook))
		return;
	if (ndx == ContactManager.getLength(addressBook) && ndx != 0) {
		ContactManager.getByIndex(addressBook, (ndx - 1));
		ContactManager.insertAfterCur(addressBook, c);
	}
	else {
		ContactManager.getByIndex(addressBook, ndx);
		ContactManager.insertBeforeCur(addressBook, c);
	}
}
void deleteContact(contactManager addressBook, int ndx) {
	contact c;

	c = ContactManager.getByIndex(addressBook, ndx);
	if (c != NULL)
		ContactManager.deleteCur(addressBook);
}
void getContact(contactManager addressBook, int ndx) {
	contact c;

	c = ContactManager.getByIndex(addressBook, ndx);

	if (c != NULL)
		printContact(c);
}
void getField(contactManager addressBook, int ndx, char* fieldName) {
	contact c;
	char* string;

	c = ContactManager.getByIndex(addressBook, ndx);
	if (c != NULL) {
		if (strcmp(fieldName, "lastName") == 0)
			printf("%s\n", Contact.getLastName(c));
		else if (strcmp(fieldName, "firstName") == 0)
			printf("%s\n", Contact.getFirstName(c));
		else if (strcmp(fieldName, "email") == 0)
			printf("%s\n", Contact.getEMail(c));
		else if (strcmp(fieldName, "phoneNumber") == 0)
			printf("%s\n", Contact.getPhoneNumber(c));
		else {
			printf("field not found\n");
		}
	}
}
void getNumContacts(contactManager addressBook) {
	printf("%d\n", ContactManager.getLength(addressBook));
}
void loadFile(contactManager addressBook, char* filePath) {
	FILE* inputFile;
	char buffer[BUFSIZ+1];
	contact c;

	inputFile = fopen(filePath, "r");

	if (inputFile == NULL)		/* simple error handling */
		return;

	fgets(buffer, BUFSIZ, inputFile);

	while (!feof(inputFile)) {
		fgets(buffer, BUFSIZ, inputFile);
		if (feof(inputFile))
			continue;
		sanitize(buffer);
		c = parseContactString(buffer);
		if (c != NULL)
			ContactManager.insertAfterCur(addressBook, c);
	}

	fclose(inputFile);
}
void saveToFile(contactManager addressBook, char* filePath) {
	FILE* outputFile;
	char* string;
	contact c;

	outputFile = fopen(filePath, "w");

	if (outputFile == NULL)
		return;

	fprintf(outputFile, "lastName,firstName,email,phoneNumber\r\n");

	ContactManager.getByIndex(addressBook, 0);

	do {
		c = ContactManager.getCur(addressBook);
		if (c == NULL)
			break;
		printContactToFile(c, outputFile);
		ContactManager.getNext(addressBook);
	} while (ContactManager.getIndex(addressBook) > 0);

	fclose(outputFile);
}
void editContact(contactManager addressBook, int ndx, char* fieldName, char* fieldNewValue) {
	contact c;

	c = ContactManager.getByIndex(addressBook, ndx);

	if (c != NULL) {
		if (strcmp(fieldName, "lastName") == 0)
			Contact.setLastName(c, fieldNewValue);
		else if (strcmp(fieldName, "firstName") == 0)
			Contact.setFirstName(c, fieldNewValue);
		else if (strcmp(fieldName, "email") == 0)
			Contact.setEMail(c, fieldNewValue);
		else if (strcmp(fieldName, "phoneNumber") == 0)
			Contact.setPhoneNumber(c, fieldNewValue);
	}
}
