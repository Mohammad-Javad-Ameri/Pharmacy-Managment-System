#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void mainMenu();
void pharmacistPage();
int pharmacistIdCheck(char idEntry[10]);
void logIn();
void signUp();
void pharmacistAccess();
void addMedicine();
int medIdCheck(char medIdEntry[10]);
void deleteMedicine();
void updateMedicine();
void searchMedicine();
void findID();
void findName();
void addpatient();
int patientIdCheck(char idEntry[10]);
void logInpatient();
void signUppatient();
void PatientPage();
void viewAll();
void purchase();
void readReceipts();

int main()
{
	mainMenu();
}

struct pharmacist
{
	char pharmacistID[10];
	char pharmacistName[30];
}ph;

struct medicine
{
	char medicineID[10];
	char medicineName[30];
	float price;
	int quantity;
}md;

struct patient
{
	char patientID[10];
	char patientName[30];
}pa;

void mainMenu()
{
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Pharmacy Management System                      \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Log in as pharmacist\n");      // the main menu of the system
	printf("2. Patient page\n");
	printf("3. Exit\n");
	printf("\n________________________________________________________________\n");
	printf("\n Select one option: ");

	switch (getche())
	{
	case '1':
		pharmacistPage();
		break;
	case '2':
		addpatient();
		break;
	case '3':
		exit(1);
	default:
		printf("\nInvalid Entry!\n\n");
		system("PAUSE");
		system("CLS");
		mainMenu();
	}
}

void pharmacistPage()
{
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                   Pharmacy pharmacist Access                        \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Log in\n");
	printf("2. Add an pharmacist\n");
	printf("3. Go back to Main menu\n");
	printf("\n________________________________________________________________\n");
	printf("\n Select one option: ");
	switch (getche())
	{
	case '1':
		logIn();
		break;
	case '2':
			signUp();
		break;
	case '3':
		mainMenu();
	default:
		printf("\nInvalid Entry!\n\n");
		system("PAUSE");
		system("CLS");
		pharmacistPage();
	}
}

int pharmacistIdCheck(char idEntry[10])
{
	FILE* fav;
	fav = fopen("pharmacist.txt", "r");
	while (!feof(fav))
	{
		fread(&ph, sizeof(ph), 1, fav);
		if (strcmp(idEntry, ph.pharmacistID) == 0)
		{
			fclose(fav);
			return 1;
		}
	}
	fclose(fav);
	return 0;
}

void logIn()
{
	char idEntry[10];
	int checkId;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Pharmacy Management System                      \n");
	printf("\n________________________________________________________________\n\n");
	printf(" Type pharmacist ID: ");
	scanf("%s", &idEntry);
	checkId = pharmacistIdCheck(idEntry);
	if (checkId == 0)
	{
		printf("\n This ID is not available!\n");
		system("PAUSE");
		system("CLS");
		pharmacistPage();
	}
	else
		pharmacistAccess();
}

void signUp()
{
	int idCheck3;
	char pharmacistRead[10];
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                     pharmacist sign up                             \n");
	printf("\n________________________________________________________________\n\n");
	FILE* fpharmacist;
	fpharmacist = fopen("pharmacist.txt", "a+");
	printf("\n Assign pharmacist ID: ");
	scanf("%s", &pharmacistRead);
	idCheck3 = pharmacistIdCheck(pharmacistRead);
	if (idCheck3 == 1)
		printf("\nThis ID already exists\n");
	else
	{
		strcpy(ph.pharmacistID, pharmacistRead);
		printf("\n Enter name: ");
		scanf("%s", &ph.pharmacistName);
		fwrite(&ph, sizeof(ph), 1, fpharmacist);
		fclose(fpharmacist);
		printf("\n\n pharmacist registered successfully, ");
	}
	system("PAUSE");
	system("CLS");
	pharmacistPage();
}

void pharmacistAccess()
{
    system("CLS");
	printf(" Welcome , %s", ph.pharmacistName);
	printf("\n________________________________________________________________\n");
	printf("\n                     pharmacist Access Page                          \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Add a new medicine\n");
	printf("2. Delete an existing medicine\n");
	printf("3. Update an existing medicine\n");
	printf("4. Search for an existing medicine\n");
	printf("5. Reports\n");
	printf("6. Back to the main menu\n");
	printf("\n Enter an option: ");
	switch (getche())
	{
	case '1':
		addMedicine();
		break;
	case '2':
		deleteMedicine();
		break;
	case '3':
		updateMedicine();
		break;
	case '4':
		searchMedicine();
		break;
	case '5':
		readReceipts();
		break;
	case '6':
		mainMenu();
		break;
	default:
		printf("\n Invalid Entry\n");
		system("PAUSE");
		system("CLS");
	}
	pharmacistAccess();
}

void addMedicine()
{
	int medCheck;
	char idChecking[10];
	FILE* addMed;
	addMed = fopen("medicine.txt", "a+");
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                       Add Medicine                             \n");
	printf("\n________________________________________________________________\n\n");
	printf("\nAssign a medicine ID: ");
	scanf("%s", &idChecking);
	medCheck = medIdCheck(idChecking);
	if (medCheck == 1)
		printf("\nThis ID is already assigned\n");
	else
	{
		strcpy(md.medicineID, idChecking);
		printf("\nEnter medicine name: ");
		scanf("%s", &md.medicineName);
		printf("\nEnter price per unit: ");
		scanf("%f", &md.price);
		printf("\nEnter quantity received (in unit): ");
		scanf("%i", &md.quantity);
		fwrite(&md, sizeof(md), 1, addMed);
		fclose(addMed);
		printf("\n Medicine Added successfully\n");
	}
	system("PAUSE");
	system("CLS");
	pharmacistAccess();
}

int medIdCheck(char medIdEntry[10])
{
	FILE* fav1;
	fav1 = fopen("medicine.txt", "r");
	while (!feof(fav1))
	{
		fread(&md, sizeof(md), 1, fav1);
		if (strcmp(medIdEntry, md.medicineID) == 0)
		{
			fclose(fav1);
			return 1;
		}
	}
	fclose(fav1);
	return 0;
}

void deleteMedicine()
{
	int returnedValue;
	char readMed[10];
	FILE* deleteMed;
	FILE* tempDMed;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                      Delete Medicine                           \n");
	printf("\n________________________________________________________________\n\n");
	printf("Enter Medicine ID: ");
	scanf("%s", &readMed);
	returnedValue = medIdCheck(readMed);
	if (returnedValue == 0)
	{
		printf("\nThe entered ID is not available\n");
		system("PAUSE");
		system("CLS");
		pharmacistAccess();
	}
	else
	{
		deleteMed = fopen("medicine.txt", "r");
		tempDMed = fopen("medicine temp.txt", "w");
		while (fread(&md, sizeof(md), 1, deleteMed))
			if (strcmp(md.medicineID, readMed) != 0)
				fwrite(&md, sizeof(md), 1, tempDMed);
		fclose(deleteMed);
		fclose(tempDMed);
		deleteMed = fopen("medicine.txt", "w");
		tempDMed = fopen("medicine temp.txt", "r");
		while (fread(&md, sizeof(md), 1, tempDMed))
			fwrite(&md, sizeof(md), 1, deleteMed);
		printf("\n Medicine record deleted successfully\n");
		system("PAUSE");
		system("CLS");
		pharmacistAccess();
	}
}

void updateMedicine()
{
	char medIdRead1[10];
	int medIdCheck1;
	FILE* mainFile;
	FILE* tempFile;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                      pharmacist Medicine                           \n");
	printf("\n________________________________________________________________\n\n");
	printf("Enter medicine ID: ");
	scanf("%s", medIdRead1);
	medIdCheck1 = medIdCheck(medIdRead1);
	if (medIdCheck1 == 0)
	{
		printf("No record of this medicine ID found\n");
		system("PAUSE");
		system("CLS");
		pharmacistAccess();
	}
	else
	{
		mainFile = fopen("medicine.txt", "r");
		tempFile = fopen("medicine temp.txt", "w");
		while (fread(&md, sizeof(md), 1, mainFile))
		{
			if (strcmp(md.medicineID, medIdRead1) != 0)
				fwrite(&md, sizeof(md), 1, tempFile);
			else
			{
				printf("\nEnter the updated information below\n\n");
				printf("\nEnter medicine name: ");
				scanf("%s", &md.medicineName);
				printf("\nEnter price per unit: ");
				scanf("%f", &md.price);
				printf("\nEnter quantity received (in unit): ");
				scanf("%i", &md.quantity);
				fwrite(&md, sizeof(md), 1, tempFile);
			}
		}
		fclose(mainFile);
		fclose(tempFile);
		mainFile = fopen("medicine.txt", "w");
		tempFile = fopen("medicine temp.txt", "r");
		while (fread(&md, sizeof(md), 1, tempFile))
			fwrite(&md, sizeof(md), 1, mainFile);
		fclose(mainFile);
		fclose(tempFile);
	}
	printf("\nMedicine record Updated successfully\n");
	system("PAUSE");
	system("CLS");
	pharmacistAccess();
}

void searchMedicine()
{
	char searchId, searchName;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                      Search Medicine                           \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Search by ID\n");
	printf("Enter your preference: ");
	switch (getche())
	{
	case '1':
		findID();
		break;
	case '2':
printf("\nInvalid Entry!\n");
		system("PAUSE");
		system("CLS");
		searchMedicine();
		break;
	default:
	{
		printf("\nInvalid Entry!\n");
		system("PAUSE");
		system("CLS");
		searchMedicine();
	}
	}
	return;
}

void findID()
{
	FILE* searchId;
	char seaMedId[10];
	int seaMedCheck;
	printf("\n________________________________________________________________\n");
	printf("Enter medicine ID: ");
	scanf("%s", seaMedId);
	seaMedCheck = medIdCheck(seaMedId);
	if (seaMedCheck == 0)
	{
		printf("\nNo record found of the ID provided\n");
		system("PAUSE");
		system("CLS");
		return;
	}
	else
	{
		searchId = fopen("medicine.txt", "r");
		while (fread(&md, sizeof(md), 1, searchId))
		{
			if (stricmp(md.medicineID, seaMedId) == 0)
			{
				printf("\nMedicine ID=\t\t\t%s", md.medicineID);
				printf("\nMedicine Name=\t\t\t%s", md.medicineName);
				printf("\nMedicine price=\t\t\tRM %0.2f", md.price);
				printf("\nQuantity in stock=\t\t%d", md.quantity);
				fclose(searchId);
				printf("\n\n");
				system("PAUSE");
				system("CLS");
				return;
			}
		}
	}
}

void addpatient()
{
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                   Pharmacy patient Access                        \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Log in\n");
	printf("2. Add an patient\n");
	printf("3. Go back to Main menu\n");
	printf("\n________________________________________________________________\n");
	printf("\n Select one option: ");
	switch (getche())
	{
	case '1':
		logInpatient();
		break;
	case '2':
			signUppatient();
		break;
	case '3':
		mainMenu();
	default:
		printf("\nInvalid Entry!\n\n");
		system("PAUSE");
		system("CLS");
		addpatient();
	}
}
int patientIdCheck(char idEntry6[10])
{
	FILE* fav4;
	fav4 = fopen("patient.txt", "r");
	while (!feof(fav4))
	{
		fread(&pa, sizeof(pa), 1, fav4);
		if (strcmp(idEntry6, pa.patientID) == 0)
		{
			fclose(fav4);
			return 1;
		}
	}
	fclose(fav4);
	return 0;
}

void logInpatient()
{
	char idEntry2[10];
	int checkId3;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Pharmacy Management System                      \n");
	printf("\n________________________________________________________________\n\n");
	printf(" Type patient ID: ");
	scanf("%s", &idEntry2);
	checkId3 = patientIdCheck(idEntry2);
	if (checkId3 == 0)
	{
		printf("\n This ID is not available!\n");
		system("PAUSE");
		system("CLS");
		addpatient();
	}
	else
		PatientPage();
}

void signUppatient()
{
	int idCheck4;
	char patientRead[10];
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                     patient sign up                             \n");
	printf("\n________________________________________________________________\n\n");
	FILE* fpatient;
	fpatient = fopen("patient.txt", "a+");
	printf("\n Assign patient ID: ");
	scanf("%s", &patientRead);
	idCheck4 = patientIdCheck(patientRead);
	if (idCheck4 == 1)
		printf("\nThis ID already exists\n");
	else
	{
		strcpy(pa.patientID, patientRead);
		printf("\n Enter name: ");
		scanf("%s", &pa.patientName);
		fwrite(&pa, sizeof(pa), 1, fpatient);
		fclose(fpatient);
		printf("\n\n patient registered successfully, ");
	}
	system("PAUSE");
	system("CLS");
	addpatient();
}


void PatientPage()
{
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Pharmacy Management System             |Patient\n");
	printf("\n________________________________________________________________\n\n");
	printf("1. View all medicines\n");
	printf("2. Search for a medicine\n");
	printf("3. Buy products\n");
	printf("4. Back to the main menu.\n");
	printf("\n________________________________________________________________\n");
	printf("\n Select one option: ");
	switch (getche())
	{
	case '1':
		viewAll();
		break;
	case '2':
		searchMedicine();
		break;
	case '3':
		purchase();
		break;
	case '4':
		mainMenu();
		break;
	default:
		printf("\n Invalid choice\n");
	}
	system("PAUSE");
	system("CLS");
	PatientPage();
}

void viewAll()
{
	FILE* view;
	system("CLS");
	printf("\n_________________________________________________________________________________\n");
	printf("\n                               View all products                        |Customer\n");
	printf("\n_________________________________________________________________________________\n");
	view = fopen("medicine.txt", "r");
	if (view == 0)
		printf("\n\nNo record of medicines found\n");
	else
	{
		printf("Medicine ID\tMedicine Name\t Price   \tIn-Stock");
		printf("\n_________________________________________________________________________________\n");
		while (fread(&md, sizeof(md), 1, view))
			printf("\n     %s\t\t     %s\t\t  %.2f\t\t   %i\t\t", md.medicineID, md.medicineName, md.price, md.quantity);
		printf("\n_________________________________________________________________________________\n\n");

	}
	return;
}

void purchase()
{
	time_t timer;
	struct tm* tm_info;
	char idRead4[10], receipt[200] = "", buffer[10] = "", buffer1[30];
	int count = 0, quantityWanted, returnedValue2;
	float total, total1 = 0;
	viewAll();
	strcat(receipt, "\n\nProduct\tPrice\tQuantity\t\tTotal\t\tPatient\n\n");
	while (1)
	{
		printf("\nEnter the ID of the product you want to buy or 0 to cancel: ");
		scanf("%s", &idRead4);
		returnedValue2 = medIdCheck(idRead4);
		if ((strcmp(idRead4, "0") == 0) && count > 0)
			break;
		else if ((strcmp(idRead4, "0") == 0) && count == 0)
		{
			printf("\nYou haven't chosen any products\n");
			system("PAUSE");
			system("CLS");
			PatientPage();
		}
		else
		{
			if (returnedValue2 == 1)
			{
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer1, 26, "%Y-%m-%d %H:%M:%S", tm_info);
			printf("\nEnter the quantity of this product you want: ");
			scanf("%d", &quantityWanted);
			if(quantityWanted > md.quantity ){
                    printf("Please Attention to in-stock medicines");
                    }
                    else
            {

			total = md.price * quantityWanted;
			total1 += total;
			strcat(receipt, md.medicineName);
			strcat(receipt, "\t");
			gcvt(md.price, 5, buffer);
			strcat(receipt, buffer);
			strcat(receipt, "\t\t");
			itoa(quantityWanted, buffer, 10);
			strcat(receipt, buffer);
			strcat(receipt, "\t\t");
			gcvt(total, 5, buffer);
			strcat(receipt, buffer);
			strcat(receipt, "\t\t");
			strcat(receipt, pa.patientName);
			strcat(receipt, "\n");

			}
			}
		}
		count++;
	}
	strcat(receipt, "\nTime: ");
	strcat(receipt, buffer1);
	strcat(receipt, "\n");
	printf("%s", receipt);
	printf("\nTotal price = RM %.2f\n\n", total1);
	FILE* saveReceipt;
	saveReceipt = fopen("receipts.txt", "a+");
	fwrite(receipt, sizeof(receipt), 1, saveReceipt);
	fclose(saveReceipt);
	system("PAUSE");
	system("CLS");
	PatientPage();
}

void readReceipts()
{
	char receipt[200];
	FILE* readReceipts;
	readReceipts = fopen("receipts.txt", "r");
	if (readReceipts == 0)
		printf("\nThere is no record of any purchase yet\n");
	else
	{
		while (fread(&receipt, sizeof(receipt), 1, readReceipts))
			printf("%s\n__________________________________________________________________\n\n", receipt);
	}
	system("PAUSE");
	system("CLS");
	pharmacistAccess();
}
