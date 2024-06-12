#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)

//GOLBAL VARIABLE FOR LOGIN DETAIL
char login[11];
char member_ID[11];

typedef struct {
	char from[30], to[30];
}location;

typedef struct {
	char trainID[20];
	location loc;
	int startTime, arriveTime, seat;
	char day[50];
	char status[20];
}Train;

struct Booking {
	int booking_id;
	char memberID[11];
	char train_id[20];
	int seat_number;
};

typedef struct {
	char staffID[11],
		name[51],
		password[21],
		password_recovery[21],
		position[51],
		email[31];
}staff;

typedef struct {
	char memberID[11], name[51], password[51], passwordRcry[51], gender;
	int contactNum;
}member;

//DING WEI JIE//
void staffPwsRecovery();
void staffLogin();
void addStaff();
void delStaff();
void editStaff();
void searchStaff();
void displayStaff();
void staffMenu();
void staffMain();
void returnStaffMenu(char page[]);

//BRYAN LOW CHUN KAI//
void memberLogin();
void memberAdd();
void memberMenu();
void searchMember();
void mainMember();
void memberPasswRcv();
void editProfile(member* list);
void deleteMember(member* list);
void memberHelp();

//KOK SIONG JET//
void staffEditBooking();
void book_ticket();
void find_booking();
void cancel_ticket();
void change_ticket();
void check_seat_availability();
void view_ticket();

//LEE ZI YONG//
void addSchedule();
void editSchedule();
void dltSchedule();
void displaySchedule();
void daySchedule(char day[]);
void searchSchedule();
void updateStatus();

void main();
void mainMenu();
void thankyou();


void main() {
	mainMenu();
	system("pause");
}

void mainMenu() {
	int choose;

	printf("=======================================\n");
	printf(" FFFFF  A     SSSS  TTTTT  K   K  L     \n");
	printf(" F     A A   S        T    K  K   L     \n");
	printf(" FFF  AAAAA   SSS     T    KK     L     \n");
	printf(" F   A     A     S    T    K  K   L     \n");
	printf(" F   A     A  SSSS    T    K   K  LLLLL \n");	
	printf("=======================================\n");
	printf("---------------------------------------\n");
	printf("1)STAFF\n");
	printf("2)MEMBER\n");
	printf("3)EXIT\n");
	printf("---------------------------------------\n");
	printf("ENTER YOUR CHOOSE(1,2 OR 3):");
	scanf("%d", &choose);
	rewind(stdin);

	while (choose < 1 || choose > 3)
	{
		printf("INVALID CHOOSE ! PLEASE CHOOSE EITHER 1 OR 2 OR 3 ONLY\n\a");

		printf("RE-ENTER YOUR CHOOSE(1,2 OR 3): ");
		rewind(stdin);
		scanf("%d", &choose);

	}

	switch (choose)
	{
	case 1:
		system("cls");
		staffMain();
		break;
	case 2:
		system("cls");
		mainMember();
		break;
	default:
		thankyou();
	}
}

void thankyou() {
	system("cls");
	printf("==================================================\n");
	printf("  _   _                 _                         \n");
	printf(" | |_| |__   __ _ _ __ | | __  _   _  ___  _   _  \n");
	printf(" | __| '_ \ / _` | '_ \| |/ / | | | |/ _ \| | | | \n");
	printf(" | |_| | | | (_| | | | |   <  | |_| | (_) | |_| | \n");
	printf("  \__|_| |_|\__,_|_| |_|_|\_\  \__, |\___/ \__,_| \n");
	printf("                               |___/              \n");
	printf("==================================================\n");
	exit(-1);
}

//DING WEI JIE //

void staffMain() {
	int choose;

	printf("===================================\n");
	printf("               STAFF            \n");
	printf("===================================\n");
	printf("-----------------------------------\n");
	printf("1)LOGIN\n");
	printf("2)FORGET PASSWORD\n");
	printf("3)RETURN TO MAIN MENU\n");
	printf("4)EXIT\n");
	printf("-----------------------------------\n");
	printf("ENTER YOUR CHOOSE( 1,2 ,3 OR 4 ):");
	scanf("%d", &choose);
	rewind(stdin);

	while (choose < 1 || choose > 4)
	{
		printf("INVALID CHOOSE ! PLEASE CHOOSE EITHER 1 OR 2 OR 3 OR 4 ONLY\n\a");

		printf("RE-ENTER YOUR CHOOSE( 1,2 ,3 OR 4 ): ");
		scanf("%d", &choose);
		rewind(stdin);
	}

	switch (choose)
	{
	case 1:
		system("cls");
		staffLogin();
		break;
	case 2:
		system("cls");
		staffPwsRecovery();
		break;
	case 3:
		system("cls");
		mainMenu();
		break;
	default:
		thankyou();
	}

	system("pause");

}

void staffLogin() {

	staff login_staff[10];
	char position[31], staffID[11];
	char login_staffID[11];
	char login_password[21];
	int numStaff = 0;
	int found = 0;
	int i;

	FILE* staffFile;

	staffFile = fopen("staff.txt", "r");

	if (!staffFile)
	{
		printf("ERROR TO OPEN FILE !!!!!\nPLEASE CONTACT PERSON INCHARGE");
		exit(-1);
	}

	while (!feof(staffFile))
	{
		fscanf(staffFile, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n", login_staff[numStaff].staffID, login_staff[numStaff].name, login_staff[numStaff].password, login_staff[numStaff].password_recovery, login_staff[numStaff].position, login_staff[numStaff].email);
		numStaff++;
	}

	fclose(staffFile);

	printf("=================================================================\n");
	printf("                         STAFF LOGIN\n");
	printf("=================================================================\n");
	printf("-----------------------------------------------------------------\n");
	printf("ENTER YOUR STAFF ID(ENTER -1 TO EXIT STAFF LOGIN PAGE):");
	rewind(stdin);
	gets(login_staffID);
	//COMPARE IF FOUND -1 RETURN BACK TO STAFF MAIN PAGE
	if (strcmp(login_staffID, "-1") == 0) {
		system("cls");
		staffMain();
	}
	printf("ENTER YOUR PASSWORD                                   :");
	rewind(stdin);
	gets(login_password);

	for (i = 0; i < numStaff; i++)
	{
		if (strcmp(login_staffID, login_staff[i].staffID) == 0) {
			if (strcmp(login_password, login_staff[i].password) == 0) {
				found = 1;
				strcpy(staffID, login_staff[i].staffID);
				strcpy(position, login_staff[i].position);
				strcpy(login, staffID);
				system("cls");
				staffMenu();
			}
		}
	}

	while (!found) {
		printf("Wrong staff or password!!\n");
		printf("RE-ENTER YOUR STAFF ID(ENTER -1 TO EXIT STAFF LOGIN PAGE):");
		rewind(stdin);
		gets(login_staffID);
		if (strcmp(login_staffID, "-1") == 0) {
			system("cls");
			staffMain();
		}
		printf("RE-ENTER YOUR PASSWORD:");
		rewind(stdin);
		gets(login_password);

		for (i = 0; i < numStaff; i++)
		{
			if (strcmp(login_staffID, login_staff[i].staffID) == 0) {
				if (strcmp(login_password, login_staff[i].password) == 0) {
					strcpy(staffID, login_staff[i].staffID);
					strcpy(position, login_staff[i].position);
					system("cls");
					strcpy(login, staffID);
					staffMenu();
					found++;
				}
			}
		}
	}
}

void staffPwsRecovery() {
	staff reset_pws;
	staff data[15];
	char password[11];
	FILE* staffFile;
	int numStaff = 0;

	staffFile = fopen("staff.txt", "r");

	if (!staffFile) {
		printf("UNABLE TO OPEN FILE !!!!!\\n");
		exit(-1);
	}

	while (!feof(staffFile)) {
		fscanf(staffFile, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n", data[numStaff].staffID, data[numStaff].name, data[numStaff].password, data[numStaff].password_recovery, data[numStaff].position, data[numStaff].email);
		numStaff++;
	}

	fclose(staffFile);

	printf("=================================================================\n");
	printf("                        PASSWORD RECOVERY\n");
	printf("=================================================================\n");
	printf("-----------------------------------------------------------------\n");
	printf("ENTER YOUR STAFF ID         :");
	rewind(stdin);
	scanf("%[^\n]", reset_pws.staffID);

	if (strcmp("-1", reset_pws.staffID) == 0) {
		system("cls");
		staffMain();
	}

	rewind(stdin);
	printf("ENTER YOUR PASSWORD RECOVERY:");
	scanf("%[^\n]", reset_pws.password_recovery);

	if (strcmp("-1", reset_pws.password_recovery) == 0) {
		system("cls");
		staffMain();
	}

	staffFile = fopen("staff.txt", "w");

	if (!staffFile) {
		printf("UNABLE TO OPEN FILE FOR WRITING !!!!!\\n");
		exit(-1);
	}

	for (int i = 0; i < numStaff; i++) {
		//IF THE STAFF ID AND PASSWORD RECCOVERY BOTH ARE TRUE ALLOW USER RESET THIER PASSWORD
		if (strcmp(reset_pws.staffID, data[i].staffID) == 0 && strcmp(reset_pws.password_recovery, data[i].password_recovery) == 0) {
			printf("ENTER YOUR NEW PASSWORD     :");
			rewind(stdin);
			gets(password);
			fprintf(staffFile, "%s#%s$%s?%s>%s&%s\n", data[i].staffID, data[i].name, password, data[i].password_recovery, data[i].position, data[i].email);

		}
		else {
			fprintf(staffFile, "%s#%s$%s?%s>%s&%s\n", data[i].staffID, data[i].name, data[i].password, data[i].password_recovery, data[i].position, data[i].email);
		}
	}
	fclose(staffFile);

	system("cls");
	staffMain();
}

void staffMenu() {
	int choose;
	char option;
	system("pause");
	printf("===============================\n");
	printf("          STAFF MENU        \n");
	printf("===============================\n");
	printf("-------------------------------\n");
	printf("1) ADD STAFF\n");
	printf("2) SEARCH STAFF\n");
	printf("3) EDIT STAFF DETAIL\n");
	printf("4) DELETE STAFF\n");
	printf("5) DISPLAY STAFF\n");
	printf("6) DISPLAY TRAIN SCHEDULE\n");
	printf("7) ADD TRAIN SCHEDULE\n");
	printf("8) EDIT TRAIN SHCEDULE\n");
	printf("9) UPDATE TRAIN STATUS\n");
	printf("10)DELETE SCHEDULE\n");
	printf("11)EDIT TICKET BOOKING\n");
	printf("12)LOG OUT\n");
	printf("-------------------------------\n");
	printf("ENTER YOUR CHOOSE ( 1 - 12 ) :");
	scanf("%d", &choose);
	rewind(stdin);

	while (choose < 1 || choose > 12)
	{
		printf("INVALID CHOOSE ! PLEASE CHOOSE 1 UNTIL 11\n\a");
		printf("RE-ENTER YOUR CHOOSE ( 1 - 12 ) :");
		scanf("%d", &choose);
		rewind(stdin);
	}

	switch (choose)
	{
	case 1:
		system("cls");
		addStaff();
		break;
	case 2:
		system("cls");
		searchStaff();
		break;
	case 3:
		system("cls");
		editStaff();
		break;
	case 4:
		system("cls");
		delStaff();
		break;
	case 5:
		system("cls");
		displayStaff();
		break;
	case 6:
		system("cls");
		displaySchedule();
		break;
	case 7:
		system("cls");
		addSchedule();
		break;
	case 8:
		system("cls");
		editSchedule();
		break;
	case 9:
		system("cls");
		updateStatus();
		break;
	case 10:
		system("cls");
		dltSchedule();
		break;
	case 11:
		system("cls");
		staffEditBooking();
		break;
	default:
		system("cls");
		strcpy(login, "\0");
		staffMain();
	}
}

void addStaff() {
	char option;
	char position[31];
	staff addStaff, check[15];
	FILE* staffFile;
	int numStaff = 0;
	int i = 0;
	int found = 0;
	staffFile = fopen("staff.txt", "r");
	if (!staffFile)
	{
		printf("ERROR TO OPEN FILE !!!!!\nPLEASE CONTACT PERSON INCHARGE");
		exit(-1);
	}
	while (!feof(staffFile))
	{
		fscanf(staffFile, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n", check[numStaff].staffID, check[numStaff].name, check[numStaff].password, check[numStaff].password_recovery, check[numStaff].position, check[numStaff].email);
		numStaff++;
	}

	fclose(staffFile);

	staffFile = fopen("staff.txt", "a");

	do
	{
		printf("===============================================\n");
		printf("                  ADD STAFF\n");
		printf("===============================================\n");
		printf("ENTER -1 AT ANY PROMPT TO RETURN BACK TO MENU!!\n");
		printf("===============================================\n");
		do {
			printf("ENTER STAFF ID        :");
			rewind(stdin);
			scanf("%[^\n]", addStaff.staffID);
			returnStaffMenu(addStaff.staffID);
			for (int i = 0; i < numStaff; i++)
			{
				if (strcmp(addStaff.staffID, check[i].staffID) == 0)
				{
					found = 1;
					printf("STAFF ID ALREADY EXIST!!!PLEASE RE-ENTER STAFF ID\n");
					break;
				}
				else
				{
					found = 0;
				}
			}
		} while (found);
		rewind(stdin);
		printf("ENTER NAME            :");
		scanf("%[^\n]", addStaff.name);
		returnStaffMenu(addStaff.name);
		rewind(stdin);
		printf("ENTER PASSWORD        :");
		scanf("%[^\n]", addStaff.password);
		if (strcmp(addStaff.password, "-1") == 0) {
			system("cls");
			staffMenu();
		}
		rewind(stdin);
		printf("ENTER PASSWORD RECOVER:");
		scanf("%[^\n]", addStaff.password_recovery);
		returnStaffMenu(addStaff.password_recovery);
		rewind(stdin);
		printf("ENTER POSITION        :");
		scanf("%[^\n]", addStaff.position);
		returnStaffMenu(addStaff.position);
		rewind(stdin);
		printf("ENTER EMAIL           :");
		scanf("%[^\n]", addStaff.email);
		returnStaffMenu(addStaff.email);
		rewind(stdin);
		fprintf(staffFile, "%s#%s$%s?%s>%s&%s\n", addStaff.staffID, addStaff.name, addStaff.password, addStaff.password_recovery, addStaff.position, addStaff.email);
		fclose(staffFile);
		printf("===============================================\n");
		printf("DO YOU WANT TO ADD MORE Staff( Y / N ):");
		scanf("%c", &option);
		if (option == 'N' || option == 'n')
		{
			system("cls");
			staffMenu();
		}
	} while (option == 'Y' || option == 'y');


}

void delStaff() {
	FILE* staffFile;
	staffFile = fopen("staff.txt", "r");
	staff data[15];
	char selected[11];
	int numStaff = 0;
	int i;

	if (!staffFile)
	{
		printf("ERROR TO OPEN FILE !!!!!\nPLEASE CONTACT PERSON INCHARGE");
		exit(-1);
	}
	printf("=======================================================================================================================\n");
	printf("                                                     DELETE STAFF\n");
	printf("=======================================================================================================================\n");
	printf("STAFF ID\tNAME\t\tPASSWORD\tPASSWORD RECOVERY\tPOSITION\t\tEMAIL\n");
	printf("=======================================================================================================================\n");

	while (!feof(staffFile))
	{
		fscanf(staffFile, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n", data[numStaff].staffID, data[numStaff].name, data[numStaff].password, data[numStaff].password_recovery, data[numStaff].position, data[numStaff].email);
		printf("%-10s\t%-16s%-12s\t%-18s\t%-20s\t%-20s\n", data[numStaff].staffID, data[numStaff].name, data[numStaff].password, data[numStaff].password_recovery, data[numStaff].position, data[numStaff].email);
		numStaff++;
	}

	fclose(staffFile);


	printf("\n\nSELECT THE STAFF ID TO DELETE (ENTER -1 TO RETURN TO STAFF MAIN MENU): ");
	gets(selected);

	returnStaffMenu(selected);

	while (strcmp(login, selected) == 0) {
		printf("YOU UNABLE TO DELETE THIS STAFF!!!\n");
		printf("\n\nRE-SELECT THE STAFF ID TO DELETE:");
		rewind(stdin);
		gets(selected);
		returnStaffMenu(selected);
	}

	staffFile = fopen("staff.txt", "w");
	//THIS LOOP WILL SKIP THE SPECIFY STAFF ID HAVE BEEN SELECT AND CONTINUE  SAVE  OTHER NOT BEEN SELECT
	for (i = 0; i < numStaff; i++)
	{
		if (strcmp(selected, data[i].staffID) == 0)
		{
			continue;
		}
		else {
			fprintf(staffFile, "%s#%s$%s?%s>%s&%s\n", data[i].staffID, data[i].name, data[i].password, data[i].password_recovery, data[i].position, data[i].email);
		}

	}
	fclose(staffFile);
	system("cls");
	staffMenu();
}

void editStaff() {
	FILE* staffFile;
	int numStaff = 0;
	char selected[15];
	staff data[15];
	char option[3];
	int found = 0;

	staffFile = fopen("staff.txt", "r");

	if (!staffFile) {
		printf("Unable to open file!!");
		return;
	}

	printf("=======================================================================================================================\n");
	printf("                                                  EDIT STAFF DETAILS\n");
	printf("=======================================================================================================================\n");
	printf("=======================================================================================================================\n");
	printf("STAFF ID\tNAME\t\tPASSWORD\tPASSWORD RECOVERY\tPOSITION\t\tEMAIL\n");
	printf("=======================================================================================================================\n");

	while (fscanf(staffFile, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n",
		data[numStaff].staffID, data[numStaff].name, data[numStaff].password,
		data[numStaff].password_recovery, data[numStaff].position, data[numStaff].email) == 6) {
		if (strcmp(login, data[numStaff].staffID) != 0) {
			printf("%-10s\t%-16s%-12s\t%-18s\t%-20s\t%-20s\n", data[numStaff].staffID,
				data[numStaff].name, data[numStaff].password, data[numStaff].password_recovery,
				data[numStaff].position, data[numStaff].email);
		}
		numStaff++;
	}

	fclose(staffFile);

	printf("\n\nSELECT THE STAFF ID TO EDIT(-1 TO RETURN TO MENU): ");
	gets(selected);

	returnStaffMenu(selected);
	system("cls");

	for (int i = 0; i < numStaff; i++) {
		if (strcmp(selected, data[i].staffID) == 0) {
			found = 1;
			printf("===========================================\n");
			printf("                BEFORE EDIT\n");
			printf("===========================================\n");
			printf("STAFF ID         :%s\n", data[i].staffID);
			printf("NAME             :%s\n", data[i].name);
			printf("PASSWORD         :%s\n", data[i].password);
			printf("PASSWORD RECOVERY:%s\n", data[i].password_recovery);
			printf("POSITION         :%s\n", data[i].position);
			printf("EMAIL            :%s\n", data[i].email);
			printf("-------------------------------------------\n");

			do {
				printf("===============================================\n");
				printf("                     EDIT\n");
				printf("===============================================\n");
				printf("ENTER -1 AT ANY PROMPT TO RETURN BACK TO MENU!!\n");
				printf("===============================================\n");
				printf("ENTER NAME             :");
				gets(data[i].name);
				returnStaffMenu(data[i].name);
				printf("ENTER PASSWORD         :");
				gets(data[i].password);
				returnStaffMenu(data[i].password);
				printf("ENTER PASSWORD RECOVERY:");
				gets(data[i].password_recovery);
				returnStaffMenu(data[i].password);
				printf("ENTER POSITION         :");
				gets(data[i].position);
				returnStaffMenu(data[i].position);
				printf("ENTER EMAIL            :");
				gets(data[i].email);
				returnStaffMenu(data[i].email);
				printf("----------------------------------------------\n");
				printf("DO YOU WANT TO CHANGE THIS DETAIL (Y/N)(-1 TO RETURN TO STAFF MENU):");
				gets(option); 
				returnStaffMenu(option);
			} while (strcmp(option, "N") == 0 || strcmp(option, "n") == 0);

			if (strcmp(option, "Y") == 0 || strcmp(option, "y") == 0) {
				staffFile = fopen("staff.txt", "w");

				if (!staffFile) {
					printf("Unable to open file!!");
					exit(-1);
				}
				//RESAVE ALL THE STAFF DETAIL AND THE SELECT STAFF DETAIL BEEN EDIT ALSO WILL SAVE
				for (int j = 0; j < numStaff; j++) {
					fprintf(staffFile, "%s#%s$%s?%s>%s&%s\n", data[j].staffID, data[j].name,data[j].password, data[j].password_recovery, data[j].position, data[j].email);
				}

				fclose(staffFile);
				system("cls");
				staffMenu();
			}
		}
	}

	if (!found) {
		printf("Staff ID not found!\n");
	}
}

void searchStaff() {
	staff searchStaff[21];
	FILE* staffFile;
	char search[51];
	int numStaff = 0;
	int i;
	int found = 0;

	staffFile = fopen("staff.txt", "r");

	if (!staffFile)
	{
		printf("ERROR TO OPEN FILE !!!!!\nPLEASE CONTACT PERSON INCHARGE");
		exit(-1);
	}

	while (!feof(staffFile))
	{
		fscanf(staffFile, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n", searchStaff[numStaff].staffID, searchStaff[numStaff].name, searchStaff[numStaff].password, searchStaff[numStaff].password_recovery, searchStaff[numStaff].position, searchStaff[numStaff].email);
		numStaff++;
	}

	fclose(staffFile);
	do
	{
		found = 0;
		printf("ENTER STAFF NAME FOR SEARCH THIER DETAILS(ENTER -1 TO RETUN BACK TO STAFF MAIN MENU:");
		rewind(stdin);
		gets(search);
		returnStaffMenu(search);
		printf("\n===================================================\n");
		printf("\t\tSTAFF DETAILS\n");
		printf("===================================================\n");

		for (i = 0; i < numStaff; i++)
		{
			//CAMPARE THE SELECTED STAFF ID AND THE STRUCTURE ARRAY HAVE SAME STAFF ID 
			if (strcmp(searchStaff[i].name, search) == 0)
			{
				printf("STAFF ID\t\t: %s\n", searchStaff[i].staffID);
				printf("STAFF NAME\t\t: %s\n", searchStaff[i].name);
				printf("STAFF PASSWORD\t\t: %s\n", searchStaff[i].password);
				printf("STAFF PASSWORD RECOVERY : %s\n", searchStaff[i].password_recovery);
				printf("STAFF POSITION\t\t: %s\n", searchStaff[i].position);
				printf("STAFF EMAIL\t\t: %s\n", searchStaff[i].email);
				printf("===================================================\n\n");
				found = 1;
				break;
			}
		}

		if(!found)
		{
			printf("NO RECORD FOUND!!!!\n\n");
		}
	} while (strcmp(search, "-1") != 0);
}

void displayStaff() {
	FILE* staffFile;
	char option[3];
	staff data;
	staffFile = fopen("staff.txt", "r");

	if (!staffFile) {
		printf("Unable to open file!!");
	}

	printf("=======================================================================================================================\n");
	printf("\t\t\t\t\tSTAFF DETAILS\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("STAFF ID\tNAME\t\tPASSWORD\tPASSWORD RECOVERY\tPOSITION\t\tEMAIL\n");
	printf("=======================================================================================================================\n");
	while (
		
		!feof(staffFile)) {
		fscanf(staffFile, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n", data.staffID, data.name, data.password, data.password_recovery, data.position, data.email);
		printf("%-10s\t%-16s%-12s\t%-18s\t%-20s\t%-20s\n", data.staffID, data.name, data.password, data.password_recovery, data.position, data.email);
	}
	printf("=======================================================================================================================\n");
	printf("ENTER -1 TO RETUN BACK TO STAFF MAIN MENU:");
	rewind(stdin);
	gets(option);
	returnStaffMenu(option);

	fclose(staffFile);
}

void returnStaffMenu(char page[]) {
	if (strcmp(page, "-1") == 0) {
		system("cls");
		staffMenu();
	}//THIS FUNCTION MINUMAN THE FUNCTION FOR RETURN BACK TO STAFF MENU
}

//BRYAN LOW CHUN KAI //

void mainMember() {
	int menu;

	printf("==============================================\n");
	printf("\tMEMBER\n");
	printf("==============================================\n");
	printf("1)LOG IN\n");
	printf("2)REGISTER ACCOUNT\n");
	printf("3)FORGET PASSWORD\n");
	printf("4)QUIT\n");
	printf("==============================================\n");
	printf("ENTER YOUR CHOOSE(1,2,3 OR 4):");
	scanf("%d", &menu);
	while (menu < 1 || menu > 4)
	{
		printf("INVALID CHOOSE ! PLEASE CHOOSE EITHER 1 OR 2 OR 3 OR 4 ONLY\n");
		printf("RE-ENTER YOUR CHOOSE( 1 , 2 , 3 OR 4 ): ");
		rewind(stdin);
		scanf("%d", &menu);
	}

	switch (menu) {
	case 1:
		system("cls");
		memberLogin();
		break;
	case 2:
		system("cls");
		memberAdd();
		break;
	case 3:
		system("cls");
		memberPasswRcv();
	default:
		thankyou();
	}
}

void memberLogin() {
	member list[10];
	char login_memberID[11], login_Mpassword[21];
	int numMember = 0, i, validate = 0;

	FILE* fileMember;
	fileMember = fopen("member.txt", "r");

	if (!fileMember) {
		printf("Error! Unable to open file.\nPlease contact Customer Service.\n");
		exit(-1);
	}

	while (!feof(fileMember)) {
		fscanf(fileMember, "%[^$]$%[^#]#%[^?]?%[^@]@%c%d\n", list[numMember].memberID, list[numMember].name, list[numMember].password, list[numMember].passwordRcry, &list[numMember].gender, &list[numMember].contactNum);
		numMember++;
	}

	printf("==============================================\n");
	printf("\tMEMBER LOGIN ACCOUNT\n");
	printf("==============================================\n");
	rewind(stdin);
	printf("ENTER MEMBER ID:");
	scanf("%[^\n]", &login_memberID);
	if (strcmp(login_memberID, "-1") == 0) {
		system("cls");
		mainMenu();
	}
	rewind(stdin);
	printf("ENTER PASSWORD :");
	scanf("%[^\n]", &login_Mpassword);
	if (strcmp(login_Mpassword, "-1") == 0) {
		system("cls");
		mainMenu();
	}
	//validate id and password,if so access to memberMenu//
	for (i = 0; i < numMember; i++) {
		if (strcmp(login_memberID, list[i].memberID) == 0) {
			if (strcmp(login_Mpassword, list[i].password) == 0) {
				validate = 1;
				strcpy(member_ID, list[i].memberID);
				system("cls");
				fclose(fileMember);
				memberMenu();
			}
		}
	}
	//if no found allows users to input again //
	while (!validate)
	{
		rewind(stdin);
		printf("Wrong memberID or password!!\nRE-ENTER MEMBER ID (Enter -1 for return to home page):");
		scanf("%[^\n]", &login_memberID);
		rewind(stdin);
		if (strcmp(login_memberID, "-1") == 0) {
			system("cls");
			mainMenu();
		}
		rewind(stdin);

		printf("RE-ENTER PASSWORD:");
		scanf("%[^\n]", &login_Mpassword);

		for (i = 0; i < numMember; i++) {
			if (strcmp(login_memberID, list[i].memberID) == 0) {
				if (strcmp(login_Mpassword, list[i].password) == 0) {
					validate = 1;
					strcpy(member_ID, list[i].memberID);
					system("cls");
					fclose(fileMember);
					memberMenu();
				}
			}
		}
	}
	fclose(fileMember);
	system("cls");
	memberMenu();
}

void memberAdd() {
	//check is for validate is the id already exist,if no can add to file
	member list, check[20];
	FILE* fileMember;
	int numMember = 0;
	int found = 0;
	fileMember = fopen("member.txt", "r");

	if (fileMember == NULL)
	{
		printf("Error!!unable to open file!");
		exit(-1);
	}
	while (!feof(fileMember))
	{
		fscanf(fileMember, "%[^$]$%[^#]#%[^?]?%[^@]@%c%d\n", check[numMember].memberID, check[numMember].name, check[numMember].password, check[numMember].passwordRcry, &check[numMember].gender, &check[numMember].contactNum);
		numMember++;
	}

	printf("==============================================\n");
	printf("\t	REGISTER ACCOUNT\n");
	printf("==============================================\n");

	do {
		rewind(stdin);
		printf("Enter your ID:");
		scanf("%[^\n]", &list.memberID);
		if (strcmp(list.memberID, "-1") == 0) {
			system("cls");
			mainMember();
		}
		for (int i = 0; i < numMember; i++)
		{
			if (strcmp(list.memberID, check[i].memberID) == 0)
			{
				found = 1;
				printf("MEMBER ID ALREADY EXIST!!!PLEASE RE-ENTER MEMBER ID\n");
				break;
			}
			else
			{
				found = 0;
			}
		}
	} while (found);

	fclose(fileMember);
	rewind(stdin);
	printf("Enter your name:");
	scanf("%[^\n]", &list.name);

	rewind(stdin);
	printf("Enter your password:");
	scanf("%[^\n]", &list.password);

	rewind(stdin);
	printf("Enter your recovery key(e.g. your favourite thing):");
	scanf("%[^\n]", &list.passwordRcry);
	rewind(stdin);
	printf("Enter your gender (F or M):");
	scanf("%c", &list.gender);
	list.gender = toupper(list.gender);
	rewind(stdin);
	while (list.gender != 'M' && list.gender != 'F')
	{
		printf("Re-Enter your gender (F or M):");
		scanf("%c", &list.gender);
		rewind(stdin);
		list.gender = toupper(list.gender);
		rewind(stdin);
	}

	rewind(stdin);
	printf("Enter your phone number:");
	scanf("%d", &list.contactNum);
	fileMember = fopen("member.txt", "a");

	if (fileMember == NULL)
	{
		printf("Error!!unable to open file!");
		exit(-1);
	}
	fprintf(fileMember, "%s$%s#%s?%s@%c0%d\n", list.memberID, list.name, list.password, list.passwordRcry, list.gender, list.contactNum);

	printf("Register Successful!!\n\n");
	fclose(fileMember);
	system("cls");
	mainMember();
}

void memberMenu() {
	printf("==============================================\n");
	printf("                 MEMBER MENU \n");
	printf("==============================================\n");
	member list[10];
	int numMember = 0;
	FILE* fileMember;
	fileMember = fopen("member.txt", "r");

	if (!fileMember) {
		printf("Error! Unable to open and read file.\nPlease contact Customer Service.\n");
		exit(-1);
	}

	fscanf(fileMember, "%[^$]$%[^#]#%[^?]?%[^@]@%c%d\n", list[numMember].memberID, list[numMember].name, list[numMember].password, list[numMember].passwordRcry, &list[numMember].gender, &list[numMember].contactNum);
	numMember++;

	fclose(fileMember);

	int choose;
	//option for users to select action
	printf("1)  EDIT PROFILE\n");
	printf("2)  SEARCH MEMBER\n");
	printf("3)  BOOKING TICKET\n");
	printf("4)  SEARCH BOOKING\n");
	printf("5)  EDIT TICKET\n");
	printf("6)  CANCEL TICKET\n");
	printf("7)  DISPLAY TICKET BOOKING\n");
	printf("8)  SEARCH TRAIN SEAT AVAILABILITY\n");
	printf("9)  SEARCH TRAIN SCHEDULE\n");
	printf("10) DISPLAY WEEK SCHEDULE\n");
	printf("11) CONTACT STAFF\n");
	printf("12) DELETE ACCOUNT\n");
	printf("13) LOG OUT\n");
	printf("==============================================\n");
	printf("ENTER YOUR OPTION (1-13):");
	rewind(stdin);
	scanf("%d", &choose);

	while (choose < 1 || choose > 13) {
		printf("INVALID OPTION!PLEASE CHOOSE 1 - 13\n");
		printf("ENTER YOUR OPTION (1-13):");
		rewind(stdin);
		scanf("%d", &choose);
	}

	switch (choose)
	{
	case 1:
		system("cls");
		editProfile(list);
		break;
	case 2:
		system("cls");
		searchMember();
		break;
	case 3:
		system("cls");
		book_ticket();
		break;
	case 4:
		system("cls");
		find_booking();
		break;
	case 5:
		system("cls");
		change_ticket();
		break;
	case 6:
		system("cls");
		cancel_ticket();
		break;
	case 7:
		system("cls");
		view_ticket();
		break;
	case 8:
		system("cls");
		check_seat_availability();
		break;
	case 9:
		system("cls");
		searchSchedule();
		break;
	case 10:
		system("cls");
		displaySchedule();
		break;
	case 11:
		system("cls");
		memberHelp();
		break;
	case 12:
		system("cls");
		deleteMember(list);
		break;
	default:
		strcpy(member_ID, "\0");
		system("cls");
		mainMenu();
	}
}

void editProfile(member* list) {
	// pass parameter to here
	int numMember = 0;
	int changeCho, chgNum, cfmNum;
	char newChange[41], cfmChange[41];

	FILE* fileMember;
	FILE* editMember;
	fileMember = fopen("member.txt", "r");

	if (!fileMember) {
		printf("Error! Unable to open and read file.\nPlease contact Customer Service.\n");
		exit(-1);
	}

	while (!feof(fileMember)) {
		fscanf(fileMember, "%[^$]$%[^#]#%[^?]?%[^@]@%c%d\n", list[numMember].memberID, list[numMember].name, list[numMember].password, list[numMember].passwordRcry, &list[numMember].gender, &list[numMember].contactNum);
		numMember++;
	}
	fclose(fileMember);
	//loop and found the same id,if so stop at the row and allow user to edit detail,and allow to exit loop when changecho=5
	for (int i = 0; i < numMember; i++) {
		if (strcmp(list[i].memberID, member_ID) == 0) {
			printf("==============================================\n");
			printf("\tMEMBER PROFILE\n");
			printf("==============================================\n");
			printf("User Name        :%s\n", list[i].name);
			printf("Gender           :%c\n", list[i].gender);
			printf("Password         :%s\n", list[i].password);
			printf("Password Recovery:%s\n", list[i].passwordRcry);
			printf("Contact Number   :(+60)%d\n", list[i].contactNum);
			printf("==============================================\n");
			printf("Which is the one you wanna update?\n");
			printf("1.User Name\n");
			printf("2.Password\n");
			printf("3.Contact Number\n");
			printf("4.Password Recovery\n");
			printf("5.Back to previous page\n");
			printf("==============================================\n");
			printf("Enter your option (1-5):");
			rewind(stdin);
			scanf("%d", &changeCho);
			while (changeCho < 1 || changeCho > 5) {
				printf("Invalid Option. Select again between 1-5:\n");
				printf("Enter your option (1-5):");
				rewind(stdin);
				scanf("%d", &changeCho);
			}
			if (changeCho == 1) {
				printf("Enter new username (-1 back to main page):");
				rewind(stdin);
				scanf("%s", newChange);
				if (strcmp(newChange, "-1") == 0) {
					system("cls");
					memberMenu();
				}
				printf("Confirm your username :");
				rewind(stdin);
				scanf("%s", cfmChange);
				if (strcmp(newChange, cfmChange) == 0) {
					strcpy(list[i].name, newChange);
					system("cls");
					printf("Your username has been changed successfully\n\n");
				}
				else {
					printf("Failed to change username. Please try again.\n\n");
				}
			}
			else if (changeCho == 2) {
				printf("Enter new password (-1 back to main page):");
				rewind(stdin);
				scanf("%s", newChange);
				if (strcmp(newChange, "-1") == 0) {
					system("cls");
					memberMenu();
				}
				printf("Confirm your new password :");
				rewind(stdin);
				scanf("%s", cfmChange);
				if (strcmp(newChange, cfmChange) == 0) {
					strcpy(list[i].password, newChange);
					system("cls");
					printf("Your password has been changed successfully\n\n");
				}
				else {
					printf("Failed to change password. Please try again.\n\n");
				}
			}
			else if (changeCho == 3) {
				printf("Enter new contact number (-1 back to main page):");
				rewind(stdin);
				scanf("%d", &chgNum);
				if (chgNum == -1) {
					system("cls");
					memberMenu();
				}
				printf("Confirm your contact number :");
				rewind(stdin);
				scanf("%d", &cfmNum);
				if (chgNum == cfmNum) {
					list[i].contactNum = chgNum;
					printf("Your contact number has been changed successfully\n\n");
				}
				else {
					printf("Failed to change contact. Please try again.\n\n");
				}
			}
			else if (changeCho == 4) {
				printf("Enter new password recovery (-1 back to main page):");
				rewind(stdin);
				scanf("%s", newChange);
				if (strcmp(newChange, "-1") == 0) {
					system("cls");
					memberMenu();
				}
				printf("Confirm your new recovery :");
				rewind(stdin);
				scanf("%s", cfmChange);
				if (strcmp(newChange, cfmChange) == 0) {
					strcpy(list[i].passwordRcry, newChange);
					system("cls");
					printf("Your password has been changed successfully\n\n");
				}
				else {
					printf("Failed to change password. Please try again.\n\n");
				}
			}
			else if (changeCho == 5) {
				system("cls");
				memberMenu();
			}
		}
	}

	editMember = fopen("member.txt", "w");
	if (!editMember) {
		printf("Error! Unable to open file.\nPlease contact Customer Service.\n");
		exit(-1);
	}

	for (int i = 0; i < numMember; i++) {
		fprintf(editMember, "%s$%s#%s?%s@%c%d\n", list[i].memberID, list[i].name, list[i].password, list[i].passwordRcry, list[i].gender, list[i].contactNum);
	}

	fclose(editMember);
	editProfile(list);
}

void memberPasswRcv() {
	member resetPw;
	member memberInfo[20];
	int numMember = 0;
	FILE* fileMember;
	fileMember = fopen("member.txt", "r");
	if (!fileMember) {
		printf("Error! Unable to open file.\nPlease contact Customer Service.\n");
		exit(-1);
	}
	while (!feof(fileMember)) {
		fscanf(fileMember, "%[^$]$%[^#]#%[^?]?%[^@]@%c%d\n", memberInfo[numMember].memberID, memberInfo[numMember].name, memberInfo[numMember].password, memberInfo[numMember].passwordRcry, &memberInfo[numMember].gender, &memberInfo[numMember].contactNum);
		numMember++;
	}
	fclose(fileMember);
	fileMember = fopen("member.txt", "w");
	if (!fileMember) {
		printf("Error! Unable to open file.\nPlease contact Customer Service.\n");
		exit(-1);
	}

	printf("==============================================\n");
	printf("\tMEMBER PASSWORW RECOVERY\n");
	printf("==============================================\n");

	rewind(stdin);
	printf("ENTER YOUR MEMBER ID :");
	scanf("%[^\n]", resetPw.memberID);
	rewind(stdin);
	printf("ENTER YOUR PASSWORD RECOVERY:");
	scanf("%[^\n]", resetPw.passwordRcry);

	if (!fileMember) {
		printf("Error! Unable to open file.\nPlease contact Customer Service.\n");
		exit(-1);
	}
	//found the id and passwordRcry at the same row,if so allows user to change a new password 
	for (int i = 0; i < numMember; i++) {
		if (strcmp(resetPw.memberID, memberInfo[i].memberID) == 0) {
			if (strcmp(resetPw.passwordRcry, memberInfo[i].passwordRcry) == 0) {
				char changePw[21], reply;
				rewind(stdin);
				printf("Enter your New Password:");
				scanf("%[^\n]", changePw);
				rewind(stdin);
				printf("==============================================\n");
				printf("New Password: %s\n", changePw);
				printf("==============================================\n");
				printf("Comfirm to change?(Y for comfirm):");
				scanf("%c", &reply);
				if (reply == 'y' || reply == 'Y') {
					strcpy(memberInfo[i].password, changePw);
					printf("Your password has been changed successfully\n\n\n\n");
				}
			}
		}
		fprintf(fileMember, "%s$%s#%s?%s@%c%d\n", memberInfo[i].memberID, memberInfo[i].name, memberInfo[i].password, memberInfo[i].passwordRcry, memberInfo[i].gender, memberInfo[i].contactNum);
	}

	fclose(fileMember);
	system("cls");
	mainMenu();
}

void deleteMember(member* list) {
	FILE* fileMember;
	FILE* delMember;
	int numMember = 0;
	char option;

	fileMember = fopen("member.txt", "r");
	if (!fileMember) {
		printf("Error! Unable to open and read file.\nPlease contact Customer Service.\n");
		exit(-1);
	}

	while (!feof(fileMember)) {
		fscanf(fileMember, "%[^$]$%[^#]#%[^?]?%[^@]@%c%d\n", list[numMember].memberID, list[numMember].name, list[numMember].password, list[numMember].passwordRcry, &list[numMember].gender, &list[numMember].contactNum);
		numMember++;
	}
	fclose(fileMember);

	delMember = fopen("member.txt", "w");
	if (!delMember) {
		printf("Error! Unable to open file for writing.\nPlease contact Customer Service.\n");
		exit(-1);
	}
	//found the same id,and stop at the rows and waiting user comfirmation .If yes for print other user data into file,if no return to memberMenu
	for (int i = 0; i < numMember; i++) {
		if (strcmp(member_ID, list[i].memberID) == 0) {
			printf("==============================================\n");
			printf("\tMEMBER PROFILE\n");
			printf("==============================================\n");
			printf("User Name        :%s\n", list[i].name);
			printf("Gender           :%c\n", list[i].gender);
			printf("Password         :%s\n", list[i].password);
			printf("Password Recovery:%s\n", list[i].passwordRcry);
			printf("Contact Number   :(+60)%d\n", list[i].contactNum);
			printf("==============================================\n");
			printf("Are you confirm to delete account?(Y/N):");
			rewind(stdin);
			scanf("%c", &option);
			if (option == 'y' || option == 'Y')
			{
				for (int i = 0; i < numMember; i++) {
					if (strcmp(member_ID, list[i].memberID) != 0) {
						fprintf(delMember, "%s$%s#%s?%s@%c%d\n", list[i].memberID, list[i].name, list[i].password, list[i].passwordRcry, list[i].gender, list[i].contactNum);
					}
				}
				fclose(delMember);
				system("cls");
				printf("Member with ID %s has been successfully deleted.\n", member_ID);
				strcpy(member_ID, "\0");
				mainMenu();
			}

			else {
				for (int i = 0; i < numMember; i++) {
					fprintf(fileMember, "%s$%s#%s?%s@%c%d\n", list[i].memberID, list[i].name, list[i].password, list[i].passwordRcry, list[i].gender, list[i].contactNum);
				}
				fclose(delMember);
				system("cls");
				printf("Account deletion cancelled.\n");
				memberMenu();
			}
		}
	}
	fclose(delMember);
}

void searchMember() {
	member searchMember[21];
	FILE* memberFile;
	char search[51];
	int numMember = 0;
	int i;
	int found = 0;

	memberFile = fopen("member.txt", "r");

	if (!memberFile)
	{
		printf("ERROR TO OPEN FILE !!!!!\nPLEASE CONTACT PERSON INCHARGE");
		exit(-1);
	}

	while (!feof(memberFile))
	{
		fscanf(memberFile, "%[^$]$%[^#]#%[^?]?%[^@]@%c%d\n", searchMember[numMember].memberID, searchMember[numMember].name, searchMember[numMember].password, searchMember[numMember].passwordRcry, &searchMember[numMember].gender, &searchMember[numMember].contactNum);
		numMember++;
	}

	fclose(memberFile);
	do
	{
		found = 0;
		printf("ENTER MEMBER NAME FOR SEARCH THEIR DETAILS(ENTER -1 TO RETUN BACK TO MENU:");
		rewind(stdin);
		gets(search);
		if (strcmp(search, "-1") == 0) {
			system("cls");
			memberMenu();
		}
		printf("===============================================================================\n");
		printf("\t\MEMBER DETAILS\n");
		printf("===============================================================================\n");

		for (i = 0; i < numMember; i++)
		{
			if (strcmp(searchMember[i].name, search) == 0)
			{
				printf("MEMBER ID                : %s\n", searchMember[i].memberID);
				printf("MEMBER NAME              : %s\n", searchMember[i].name);
				printf("MEMBER GENDER            : %c\n", searchMember[i].gender);
				printf("MEMBER CONTACT           : %d\n", searchMember[i].contactNum);
				printf("===============================================================================\n\n");
				found = 1;
				break;
			}
		}

		if (!found) {
			printf("NO RECORD FOUND!!!!\n\n");
		}
	} while (strcmp(search, "-1") != 0);
	system("cls");
	memberMenu();
}

void memberHelp() {
	int option;
	staff login_staff[10];
	int numStaff = 0;

	FILE* stafflist;
	stafflist = fopen("staff.txt", "r");

	if (!stafflist) {
		printf("Error! Unable to open and read file.\nPlease contact Customer Service.\n");
		exit(-1);
	}

	while (!feof(stafflist)) {
		fscanf(stafflist, "%[^#]#%[^$]$%[^?]?%[^>]>%[^&]&%s\n", login_staff[numStaff].staffID, login_staff[numStaff].name, login_staff[numStaff].password, login_staff[numStaff].password_recovery, login_staff[numStaff].position, login_staff[numStaff].email);
		numStaff++;
	}
	printf("==============================================\n");
	printf("                STAFF CONTACT\n");
	printf("==============================================\n");
	printf("PLEASE CONTANT STAFF IF FACING SOME PROBLEM\n");
	printf("==============================================\n");
	printf("NAME           POSITION      EMAIL\n");
	printf("==============================================\n");
	for (int i = 0; i < numStaff; i++) {
		printf("%-15s%-14s%-20s\n", login_staff[i].name, login_staff[i].position, login_staff[i].email);
	}
	printf("==============================================\n");
	fclose(stafflist);

	printf("PRESS -1 TO BACK TO MENU :");
	rewind(stdin);
	scanf("%d", &option);
	if (option == -1)
	{
		system("cls");
		memberMenu();
	}

}

// KOK SIONG JET //

//Function to book train tickets
void book_ticket() {
	int booking, booking_seat;
	FILE* fp, * add;
	FILE *bookingID;
	int temp = 0;
	int count = 0;
	char option;
	struct Booking bookingData,dataID;
	bookingData.booking_id = 0;
	Train display[10];

	int id =0 ;
	//Open the file that contain train schedule
	fp = fopen("train.bin", "rb");
	bookingID = fopen("booking_data.bin", "rb");
	if( fp == NULL|| bookingID == NULL) {
		printf("File not exist");
		exit(-1);
	}

	//Generate booking ID

	while(fread(&dataID, sizeof(struct Booking), 1, bookingID) != 0) {
		id = dataID.booking_id + 1;
	}
	fclose(bookingID);

	printf("==========================================================================\n");
	printf("                                TRAIN SCHEDULE\n");
	printf("==========================================================================\n");
	printf(" NO. TRAIN_ID     FROM         TO           TIME         DAY          \n");
	printf("==========================================================================\n");

	//Display the train schedule
	while (fread(&display[count], sizeof(Train), 1, fp) != 0) {
		printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s\n", count, display[count].trainID, display[count].loc.from, display[count].loc.to, display[count].startTime, display[count].arriveTime, display[count].day);
		display[count].seat;
		count++;
	}
	fclose(fp);

	//Prompt user to select a train ticket and number of seats to book
	printf("==========================================================================\n");
	printf("                                 Book Ticket\n");
	printf("==========================================================================\n");
	printf("BOOKING ID :%d\n", id);
	printf("ENTER THE NO. TO BOOKING THE TICKET(0 - %d )(ENTER -1 TO GO BACK MENU) : ", count - 1);
	scanf("%d", &booking);
	rewind(stdin);
	if (booking == -1)
	{
		system("cls");
		memberMenu();
	}

	//Validate user input for booking selection
	while (booking < 0 || booking >= count) {
		printf("SCHEDULE NOT EXIST\n");
		printf("ENTER THE NO. TO BOOKING THE TICKET (0 - %d ) : ", count - 1);
		rewind(stdin);
		scanf("%d", &option);
	}

	//Prompt user for number of seats to book
	printf("HOW MANY SEAT TO BOOKING:");
	rewind(stdin);
	scanf("%d", &booking_seat);

	printf("=====================================================================\n");
	printf("ARE YOU CONFITM TO BOOKING (Y/N):");
	scanf(" %c", &option);
	if (option == 'Y' || option == 'y') {
		//Open file for writing
		fp = fopen("train.bin", "wb");
		add = fopen("booking_data.bin", "ab");

		if (fp == NULL || add == NULL) {
			printf("File not exist");
			exit(-1);
		}

		//Update seat availability and write booking data
		for (int i = 0; i < count; i++) {
			if (i == booking) {
				temp = display[booking].seat;
				temp -= booking_seat;
				display[booking].seat = temp;
				strcpy(bookingData.train_id, display[i].trainID);
				bookingData.booking_id = id;
				strcpy(bookingData.memberID, member_ID);
				bookingData.seat_number = booking_seat;
				fwrite(&display[i], sizeof(Train), 1, fp);
				fwrite(&bookingData, sizeof(bookingData), 1, add);
			}
			else
			{
				fwrite(&display[i], sizeof(Train), 1, fp);

			}
		}

		fclose(fp);
		fclose(add);
	}
	system("cls");
	memberMenu();
}

//Function to find booking details
void find_booking() {
	int booking;
	int count = 0;
	char choose;
	struct Booking bookingData;
	struct Booking find[10];
	int found = 0;

	FILE* fp;
	fp = fopen("booking_data.bin", "rb");



	if (fp == NULL) {
		printf("File not exist");
		exit(-1);
	}

	while (fread(&bookingData, sizeof(bookingData), 1, fp) != 0) {
		find[count].booking_id = bookingData.booking_id;
		strcpy(find[count].memberID, bookingData.memberID);
		strcpy(find[count].train_id, bookingData.train_id);
		find[count].seat_number = bookingData.seat_number;
		count++;
	}
	fclose(fp);

	do
	{
		system("cls");
		printf("==========================================================================\n");
		printf("                                SEARCH BOOKING\n");
		printf("==========================================================================\n");
		printf("ENTER THE BOOKING ID (ENTER -1 TO GO BACK MENU):");
		scanf("%d", &booking);
		if (booking == -1)
		{
			memberMenu();
		}
		printf("==========================================================================\n");

		for (int i = 0; i < count; i++) {
			if (find[i].booking_id == booking && strcmp(find[i].memberID, member_ID) == 0) {
				printf("==========================================================================\n");
				printf("                                BOOKING DETAIL\n");
				printf("==========================================================================\n");
				printf("Booking ID : %d\n", find[i].booking_id);
				printf("Member ID  : %s\n", find[i].memberID);
				printf("Train ID   : %s\n", find[i].train_id);
				printf("Seat Number: %d\n", find[i].seat_number);
				printf("==========================================================================\n");
				found = 1;
				break;
			}
		}
		if (!found) {
			printf("NO TICKTE FOUND!!!\n");
			break;
		}	
		printf("DO YOU WANT TO SEARH OTHER TICKET DETAILS(Y/N):");
		rewind(stdin);
		scanf("%c",&choose);
		if (choose == 'N' || choose == 'n')
		{
			system("cls");
			memberMenu();
		}
	} while (choose=='Y'||choose=='y');
}

void cancel_ticket() {
	int trainCount = 0;
	int cancelCount = 0;
	struct Booking bookingData;
	struct Booking cancel[100];
	Train trainData;
	Train data[100];
	FILE* bookingFile;
	FILE* train;
	int option;
	FILE* trainFile;

	bookingFile = fopen("booking_data.bin", "rb");
	trainFile = fopen("train.bin", "rb");

	if (bookingFile == NULL || trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}
	printf("=================================================================================\n");
	printf("                                 BOOKING\n");
	printf("=================================================================================\n");
	printf(" NO. BOOKING ID  TRAIN ID   FROM       TO          TIME        DAYS         SEAT \n");
	printf("=================================================================================\n");


	while (fread(&trainData, sizeof(trainData), 1, trainFile) != 0)
	{
		/*
		data[trainCount].arriveTime = trainData.arriveTime;
		data[trainCount].startTime = trainData.startTime;
		strcpy(data[trainCount].loc.from, trainData.loc.from);
		strcpy(data[trainCount].loc.to, trainData.loc.to);
		strcpy(data[trainCount].trainID, trainData.trainID);
		strcpy(data[trainCount].day, trainData.day);
		strcpy(data[trainCount].status, trainData.status);
		data[trainCount].seat = trainData.seat;*/
		data[trainCount] = trainData;
		trainCount++;
	}

	while (fread(&bookingData, sizeof(bookingData), 1, bookingFile) != 0)
	{
		/*
		cancel[cancelCount].booking_id = bookingData.booking_id;
		strcpy(cancel[cancelCount].memberID, bookingData.memberID);
		strcpy(cancel[cancelCount].train_id, bookingData.train_id);
		cancel[cancelCount].seat_number = bookingData.seat_number;*/
		cancel[cancelCount] = bookingData;
		int match = 0;
		for (int i = 0; i < trainCount; i++)
		{
			if (strcmp(data[i].trainID, cancel[cancelCount].train_id) != 0)
			{
				match = 1;
				break;
			}
		}

		if (match)
		{
			printf("%2d  %10d   %-10s %-11s%-11s %d-%d   %-10s   %d\n",
				cancelCount,
				cancel[cancelCount].booking_id,
				cancel[cancelCount].train_id,
				data[cancelCount].loc.from,
				data[cancelCount].loc.to,
				data[cancelCount].startTime,
				data[cancelCount].arriveTime,
				data[cancelCount].day,
				cancel[cancelCount].seat_number);
		}

		cancelCount++;
	}

	printf("====================================================================================\n");
	fclose(bookingFile);
	fclose(trainFile);
	printf("Enter the No. to select the booking for cancel:");
	scanf("%d", &option);
	if (option == -1)
	{
		system("cls");
		memberMenu();
	}
	if (option < 0 || option >= cancelCount) {
		printf("Invalid option.\n");
		printf("Enter the No. to select the booking for cancel:");
		scanf("%d", &option);
		if (option == -1)
		{
			system("cls");
			memberMenu();
		}
	}

	for (int i = 0; i < trainCount; i++) {
		if (strcmp(data[i].trainID, cancel[option].train_id) == 0) {
			data[i].seat += cancel[option].seat_number;
			break;
		}
	}

	bookingFile = fopen("booking_data.bin", "wb");
	if (bookingFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	for (int i = 0; i < cancelCount; i++)
	{
		if (i != option) {
			fwrite(&cancel[i], sizeof(bookingData), 1, bookingFile);
		}
	}

	fclose(bookingFile);

	trainFile = fopen("train.bin", "wb");
	if (trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	fwrite(&data, sizeof(Train), trainCount, trainFile);

	fclose(trainFile);
	system("cls");
	memberMenu();
}

void change_ticket() {
	int trainCount = 0;
	int cancelCount = 0;
	struct Booking bookingData;
	struct Booking cancel[100];
	Train trainData;
	Train data[100];
	FILE* bookingFile;
	FILE* trainFile;
	int option;
	char choose[11];
	int temp = 0;

	bookingFile = fopen("booking_data.bin", "rb");
	trainFile = fopen("train.bin", "rb");

	if (bookingFile == NULL || trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	printf("=================================================================================\n");
	printf("                                 BOOKING\n");
	printf("=================================================================================\n");
	printf(" NO. BOOKING ID  TRAIN ID   FROM       TO          TIME        DAYS         SEAT \n");
	printf("=================================================================================\n");

	while (fread(&trainData, sizeof(trainData), 1, trainFile) != 0)
	{
		/*data[trainCount].arriveTime = trainData.arriveTime;
		data[trainCount].startTime = trainData.startTime;
		strcpy(data[trainCount].loc.from, trainData.loc.from);
		strcpy(data[trainCount].loc.to, trainData.loc.to);
		strcpy(data[trainCount].trainID, trainData.trainID);
		strcpy(data[trainCount].day, trainData.day);
		strcpy(data[trainCount].status, trainData.status);
		data[trainCount].seat = trainData.seat;*/
		data[trainCount] = trainData;
		trainCount++;
	}

	while (fread(&bookingData, sizeof(bookingData), 1, bookingFile) != 0)
	{
		/*
		cancel[cancelCount].booking_id = bookingData.booking_id;
		strcpy(cancel[cancelCount].memberID, bookingData.memberID);
		strcpy(cancel[cancelCount].train_id, bookingData.train_id);
		cancel[cancelCount].seat_number = bookingData.seat_number;*/
		cancel[cancelCount] = bookingData;

		int match = 0;
		for (int i = 0; i < trainCount; i++)
		{
			if (strcmp(data[i].trainID, cancel[cancelCount].train_id) != 0)
			{
				match = 1;
				break;
			}
		}

		if (match)
		{
			printf("%2d  %10d   %-10s %-11s%-11s %d-%d   %-10s   %d\n",
				cancelCount,
				cancel[cancelCount].booking_id,
				cancel[cancelCount].train_id,
				data[cancelCount].loc.from,
				data[cancelCount].loc.to,
				data[cancelCount].startTime,
				data[cancelCount].arriveTime,
				data[cancelCount].day,
				cancel[cancelCount].seat_number);
		}

		cancelCount++;
	}


	printf("=================================================================================\n");
	fclose(bookingFile);
	fclose(trainFile);

	printf("ENTER NO. TO CHANGE TICKET (ENTER -1 TO MENU): ");
	scanf("%d", &option);
	if (option == -1)
	{
		system("cls");
		memberMenu();
	}
	if (option < 0 || option >= cancelCount) {
		printf("Invalid option.\n");
		printf("Enter the No. For Change Ticket: ");
		scanf("%d", &option);
		if (option == -1)
		{
			system("cls");
			memberMenu();
		}
	}

	bookingFile = fopen("booking_data.bin", "wb");
	trainFile = fopen("train.bin", "wb");

	if (bookingFile == NULL || trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	printf("=============================================================================\n");

	for (int i = 0; i < cancelCount; i++) {
		if (i == option) {
			printf("%d\n", cancel[i].booking_id);
			printf("DO YOU WANT ADD MORE SEAT OR REDUCE SEAT: ");
			scanf("%s", choose);

			for (int j = 0; j < strlen(choose); j++) {
				choose[j] = toupper(choose[j]);
			}

			if (strcmp("ADD", choose) == 0) {
				printf("The train current available seat: %d\n", data[option].seat);
				printf("How many seats you want to add: ");
				scanf("%d", &temp);

				while (temp > data[option].seat) {
					printf("The number to add can't be bigger than the train available seats!\n");
					printf("How many seats you want to add: ");
					scanf("%d", &temp);
				}

				cancel[option].seat_number += temp;

				for (int j = 0; j < trainCount; j++) {
					if (strcmp(cancel[option].train_id, data[j].trainID) == 0) {
						data[j].seat -= temp;
						break;
					}
				}
			}
			else {
				printf("How many seats you want to reduce: ");
				scanf("%d", &temp);

				while (temp > cancel[option].seat_number) {
					printf("The number to reduce can't be bigger than your current seats!\n");
					printf("How many seats you want to reduce: ");
					scanf("%d", &temp);
				}

				cancel[option].seat_number -= temp;

				for (int j = 0; j < trainCount; j++) {
					if (strcmp(cancel[option].train_id, data[j].trainID) == 0) {
						data[j].seat += temp;
						break;
					}
				}
			}

			strcpy(bookingData.memberID, cancel[option].memberID);
			strcpy(bookingData.train_id, cancel[option].train_id);
			bookingData.booking_id = cancel[option].booking_id;
			bookingData.seat_number = cancel[option].seat_number;
			fwrite(&bookingData, sizeof(bookingData), 1, bookingFile);
		}
		else {
			strcpy(bookingData.memberID, cancel[i].memberID);
			strcpy(bookingData.train_id, cancel[i].train_id);
			bookingData.booking_id = cancel[i].booking_id;
			bookingData.seat_number = cancel[i].seat_number;
			fwrite(&bookingData, sizeof(bookingData), 1, bookingFile);
		}
	}

	fwrite(data, sizeof(Train), trainCount, trainFile);

	fclose(bookingFile);
	fclose(trainFile);
	system("cls");
	memberMenu();
}

void check_seat_availability() {
	Train trainData;
	FILE* trainFile;
	char trainID[20];
	int found = 0;
	int option;

	trainFile = fopen("train.bin", "rb");

	if (trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	printf("==========================================================================\n");
	printf("                              TRAIN SCHEDULE\n");
	printf("==========================================================================\n");
	printf("TRAIN_ID     FROM          TO            TIME          DAY           \n");
	printf("==========================================================================\n");

	while (fread(&trainData, sizeof(Train), 1, trainFile) != 0) {
		printf("%-13s%-13s %-13s %d-%-8d %-13s\n",
			trainData.trainID,
			trainData.loc.from,
			trainData.loc.to,
			trainData.startTime,
			trainData.arriveTime,
			trainData.day);
	}

	printf("==========================================================================\n");
	printf("ENTER THE TRAIN ID FOR CHECH SEAT AVAILABILITY (ENTER '-1' TO MENU): ");
	rewind(stdin);
	scanf("%s", trainID);
	rewind(trainFile);
	if (strcmp(trainID, "-1") == 0) {
		fclose(trainFile);
		system("cls");
		memberMenu();
	}

	printf("\n==========================================================================\n");
	printf("                        AVAILABLE SEATS FOR TRAINS\n");
	printf("==========================================================================\n");
	printf("TRAIN_ID      FROM          TO            TIME          DAY       SEAT\n");
	printf("==========================================================================\n");

	while (fread(&trainData, sizeof(Train), 1, trainFile) != 0) {
		if (strcmp(trainData.trainID, trainID) == 0) {
			printf("%-13s%-13s%-13s%-04d-%04d%-13s%4d\n",
				trainData.trainID,
				trainData.loc.from,
				trainData.loc.to,
				trainData.startTime,
				trainData.arriveTime,
				trainData.day,
				trainData.seat);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf(" No train found with ID %s\n", trainID);
	}

	printf("==========================================================================\n");
	printf("ENTER '-1' TO MENU): ");
	scanf("%d", &option);
	fclose(trainFile);
	if (option == -1)
	{
		system("cls");
		memberMenu();
	}
}

void view_ticket() {
	int trainCount = 0;
	int bookingCount = 0;
	struct Booking bookingData;
	struct Booking bookings[100];
	Train trainData;
	Train trains[100];
	FILE* bookingFile;
	FILE* trainFile;
	int option;

	bookingFile = fopen("booking_data.bin", "rb");
	trainFile = fopen("train.bin", "rb");

	if (bookingFile == NULL || trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	while (fread(&trainData, sizeof(Train), 1, trainFile) != 0) {
		trains[trainCount++] = trainData;
	}

	while (fread(&bookingData, sizeof(struct Booking), 1, bookingFile) != 0) {
		if (strcmp(bookingData.memberID, member_ID) == 0) {
			bookings[bookingCount++] = bookingData;
		}
	}

	fclose(bookingFile);
	fclose(trainFile);

	if (bookingCount == 0) {
		printf("No bookings found for the current member ID.\n");
		system("cls");
		memberMenu();

	}

	printf("==============================================================================\n");
	printf("                                 BOOKING\n");
	printf("==============================================================================\n");
	printf(" NO. BOOKING ID  TRAIN ID   FROM       TO          TIME        DAYS     SEAT \n");
	printf("==============================================================================\n");

	for (int i = 0; i < bookingCount; i++) {
		int match = 0;
		for (int j = 0; j < trainCount; j++) {
			if (strcmp(bookings[i].train_id, trains[j].trainID) == 0) {
				printf("%2d  %10d   %-10s %-11s%-11s %d-%d   %-10s   %d\n",
					i,
					bookings[i].booking_id,
					bookings[i].train_id,
					trains[j].loc.from,
					trains[j].loc.to,
					trains[j].startTime,
					trains[j].arriveTime,
					trains[j].day,
					bookings[i].seat_number);
				match = 1;
				break;
			}
		}
	}
	printf("==============================================================================\n");
	printf("ENTER (-1) TO MENU): ");
	scanf("%d", &option);
	fclose(trainFile);
	if (option == -1)
	{
		system("cls");
		memberMenu();
	}
}

void staffEditBooking() {
	int trainCount = 0;
	int bookingCount = 0;
	struct Booking bookingData;
	struct Booking bookings[100];
	Train trainData;
	Train data[100];
	FILE* bookingFile;
	FILE* trainFile;
	int option;
	char choose[11];
	int temp = 0;

	bookingFile = fopen("booking_data.bin", "rb");
	trainFile = fopen("train.bin", "rb");

	if (bookingFile == NULL || trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	printf("==========================================================================================\n");
	printf("                                 ALL BOOKINGS\n");
	printf("==========================================================================================\n");
	printf(" NO. BOOKING ID  MEMBER ID  TRAIN ID   FROM       TO        TIME        DAYS     SEAT \n");
	printf("==========================================================================================\n");

	while (fread(&trainData, sizeof(trainData), 1, trainFile) != 0) {
		data[trainCount].arriveTime = trainData.arriveTime;
		data[trainCount].startTime = trainData.startTime;
		strcpy(data[trainCount].loc.from, trainData.loc.from);
		strcpy(data[trainCount].loc.to, trainData.loc.to);
		strcpy(data[trainCount].trainID, trainData.trainID);
		strcpy(data[trainCount].day, trainData.day);
		strcpy(data[trainCount].status, trainData.status);
		data[trainCount].seat = trainData.seat;
		trainCount++;
	}

	while (fread(&bookingData, sizeof(bookingData), 1, bookingFile) != 0) {
		bookings[bookingCount].booking_id = bookingData.booking_id;
		strcpy(bookings[bookingCount].memberID, bookingData.memberID);
		strcpy(bookings[bookingCount].train_id, bookingData.train_id);
		bookings[bookingCount].seat_number = bookingData.seat_number;

		int match = 0;
		for (int i = 0; i < trainCount; i++) {
			if (strcmp(data[i].trainID, bookings[bookingCount].train_id) == 0) {
				match = 1;
				break;
			}
		}

		if (match) {
			printf("%2d  %10d   %-10s %-10s %-11s%-9s %d-%d   %s   %d\n",
				bookingCount,
				bookings[bookingCount].booking_id,
				bookings[bookingCount].memberID,
				bookings[bookingCount].train_id,
				data[bookingCount].loc.from,
				data[bookingCount].loc.to,
				data[bookingCount].startTime,
				data[bookingCount].arriveTime,
				data[bookingCount].day,
				bookings[bookingCount].seat_number);
		}

		bookingCount++;
	}

	printf("==========================================================================================\n");
	fclose(bookingFile);
	fclose(trainFile);

	printf("Enter the No. For Change Ticket: ");
	scanf("%d", &option);
	if (option == -1)
	{
		system("cls");
		memberMenu();
	}
	if (option < 0 || option >= bookingCount) {
		printf("Invalid option.\n");
		printf("Enter the No. For Change Ticket: ");
		scanf("%d", &option);
		if (option == -1)
		{
			system("cls");
			memberMenu();
		}
	}

	bookingFile = fopen("booking_data.bin", "wb");
	trainFile = fopen("train.bin", "wb");

	if (bookingFile == NULL || trainFile == NULL) {
		printf("File not exist");
		exit(-1);
	}

	printf("==========================================================================================\n");

	for (int i = 0; i < bookingCount; i++) {
		if (i == option) {
			printf("DO YOU WANT ADD MORE SEAT OR REDUCE SEAT: ");
			scanf("%s", choose);

			for (int j = 0; j < strlen(choose); j++) {
				choose[j] = toupper(choose[j]);
			}

			if (strcmp("ADD", choose) == 0) {
				printf("The train current available seat: %d\n", data[option].seat);
				printf("How many seats you want to add: ");
				scanf("%d", &temp);

				while (temp > data[option].seat) {
					printf("The number to add can't be bigger than the train available seats!\n");
					printf("How many seats you want to add: ");
					scanf("%d", &temp);
				}

				bookings[option].seat_number += temp;

				for (int j = 0; j < trainCount; j++) {
					if (strcmp(bookings[option].train_id, data[j].trainID) == 0) {
						data[j].seat -= temp;
						break;
					}
				}
			}
			else {
				printf("How many seats you want to reduce: ");
				scanf("%d", &temp);

				while (temp > bookings[option].seat_number) {
					printf("The number to reduce can't be bigger than your current seats!\n");
					printf("How many seats you want to reduce: ");
					scanf("%d", &temp);
				}

				bookings[option].seat_number -= temp;

				for (int j = 0; j < trainCount; j++) {
					if (strcmp(bookings[option].train_id, data[j].trainID) == 0) {
						data[j].seat += temp;
						break;
					}
				}
			}

			strcpy(bookingData.memberID, bookings[option].memberID);
			strcpy(bookingData.train_id, bookings[option].train_id);
			bookingData.booking_id = bookings[option].booking_id;
			bookingData.seat_number = bookings[option].seat_number;
			fwrite(&bookingData, sizeof(bookingData), 1, bookingFile);
		}
		else {
			strcpy(bookingData.memberID, bookings[i].memberID);
			strcpy(bookingData.train_id, bookings[i].train_id);
			bookingData.booking_id = bookings[i].booking_id;
			bookingData.seat_number = bookings[i].seat_number;
			fwrite(&bookingData, sizeof(bookingData), 1, bookingFile);
		}
	}
	fwrite(data, sizeof(Train), trainCount, trainFile);

	fclose(bookingFile);
	fclose(trainFile);
	system("cls");
	staffMenu();
}

// LEE ZI YONG //
void addSchedule() {
	char ans[30], c1;
	int day;
	int status;
	FILE* add;
	Train atrain;

	do {
		system("cls");
		//capture admin input
		printf("===================================\n");
		printf("|        ADD TRAIN SCHEDULE       |\n");
		printf("===================================\n");
		printf("Train ID         : ");
		rewind(stdin);
		scanf("%[^\n]", &atrain.trainID);
		returnStaffMenu(atrain.trainID);
		printf("Departure Station: ");
		rewind(stdin);
		scanf("%[^\n]", &atrain.loc.from);
		returnStaffMenu(atrain.loc.from);
		printf("Arrival Station  : ");
		rewind(stdin);
		scanf("%[^\n]", &atrain.loc.to);
		returnStaffMenu(atrain.loc.to);
		printf("Departure Time (HHMM): ");
		rewind(stdin);
		scanf("%d", &atrain.startTime);
		printf("Arrival Time (HHMM)  : ");
		rewind(stdin);
		scanf("%d", &atrain.arriveTime);
		//makesure the time admin insert is reasonable
		while ((atrain.arriveTime - atrain.startTime) < 0)
		{
			printf("\nINVALID TIME THE ARRIVAL TIME CAN NOT EARLY THAN DEPARTURE TIME!!\n");
			printf("Departure Time (MMHH): ");
			rewind(stdin);
			scanf("%d", &atrain.startTime);

			printf("Arrival Time (MMHH)  : ");
			rewind(stdin);
			scanf("%d", &atrain.arriveTime);
		}
		printf("Available Seat   : ");
		rewind(stdin);
		scanf("%d", &atrain.seat);
		printf("\n==============================\n");
		printf("              DAYS        \n");
		printf("==============================\n");
		printf("0	-	SUNDAY\n");
		printf("1	-	MONDAY\n");
		printf("2	-	TUESDAY\n");
		printf("3	-	WEDNESDAY\n");
		printf("4	-	THUESDAY\n");
		printf("5	-	FRIDAY\n");
		printf("6	-	SATURDAY\n");
		printf("==============================\n");
		printf("Day  (0 - 6)     : ");
		rewind(stdin);
		scanf("%d", &day);
		//makesure admin chooing a correct choice
		while (day < 0 || day>6)
		{
			printf("INVALID INPUT RE-ENTER!\n");
			printf("Day  (0 - 6)     : ");
			rewind(stdin);
			scanf("%d", &day);
		}
		//select day
		switch (day)
		{
		case 1:
			strcpy(atrain.day, "MONDAY");
			break;
		case 2:
			strcpy(atrain.day, "TUESDAY");
			break;
		case 3:
			strcpy(atrain.day, "WEDNESDAY");
			break;
		case 4:
			strcpy(atrain.day, "THUESDAY");
			break;
		case 5:
			strcpy(atrain.day, "FRIDAY");
			break;
		case 6:
			strcpy(atrain.day, "SATURDAY");
			break;
		default:
			strcpy(atrain.day, "SUNDAY");
		}
		//choose status
		printf("\n=====================\n");
		printf("        STATUS        \n");
		printf("=====================\n");
		printf("1	-	ON BOARD\n");
		printf("2	-	ON SCHEDULE\n");
		printf("3	-	DELAY\n");
		printf("4	-	CANCEL\n");
		printf("5	-	NONE\n");
		printf("=====================\n");
		printf("STATUS  (1 - 5)     : ");
		rewind(stdin);
		scanf("%d", &status);
		while (status < 1 || status>5)
		{
			printf("INVALID INPUT RE-ENTER!\n");
			printf("STATUS  (1 - 5)     : ");
			rewind(stdin);
			scanf("%d", &status);
		}
		switch (status)
		{
		case 1:
			strcpy(atrain.status, "ON BOARD");
			break;
		case 2:
			strcpy(atrain.status, "ON SCHEDULE");
			break;
		case 3:
			strcpy(atrain.status, "DELAY");
			break;
		case 4:
			strcpy(atrain.status, "CANCEL");
			break;
		default:
			strcpy(atrain.status, "NONE");
		}
		//display to admin the data key in 
		printf("\n===================================\n");
		printf("|      CONFIRM  TRAIN SCHEDULE     |\n");
		printf("===================================\n");
		printf("\nTRAIN ID         :%s\n", atrain.trainID);
		printf("DEPARTURE FROM   :%s\n", atrain.loc.from);
		printf("ARRIVE TO        :%s\n", atrain.loc.to);
		printf("DEPARTURE TIME   :%d\n", atrain.startTime);
		printf("ARRIVAL TIME     :%d\n", atrain.arriveTime);
		printf("AVAILABILITY SEAT:%d\n", atrain.seat);
		printf("DAYS             :%s\n", atrain.day);
		printf("STATUS           :%s\n", atrain.status);
		printf("Confirm to add in? (y/n): ");
		rewind(stdin);
		scanf("%c", &c1);
		if (c1 == 'y' || c1 == 'Y') {
			add = fopen("train.bin", "ab");

			if (add == NULL) {
				printf("File not exist");
				exit(-1);
			}

			fwrite(&atrain, sizeof(atrain), 1, add);
			fclose(add);
			system("cls");
			staffMenu();
		}
		if (c1 == 'N' || c1 == 'n') {
			system("cls");
			staffMenu();
		}
	} while (1);
	system("cls");
	staffMenu();
}

void editSchedule() {
	int count = 0;
	int detect = 0;
	int option, opedit, quit;
	char confirm;

	FILE* editTrain;
	FILE* search;
	search = fopen("train.bin", "rb");

	Train edit[100];

	if (search == NULL) {
		printf("File not exist");
		exit(-1);
	}
	printf("==========================================================================\n");
	printf("                                TRAIN SCHEDULE\n");
	printf("==========================================================================\n");
	printf(" NO. TRAIN_ID     FROM         TO           TIME         DAY          SEAT\n");
	printf("==========================================================================\n");
	printf("\n");
	//display all schedule that exist 
	while (fread(&edit[count], sizeof(Train), 1, search) != 0) {
		printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%4d\n", count, edit[count].trainID, edit[count].loc.from, edit[count].loc.to, edit[count].startTime, edit[count].arriveTime, edit[count].day, edit[count].seat);
		printf("\n");
		count++;
	}
	fclose(search);
	printf("==========================================================================\n");
	//admin select to edit
	printf("ENTER THE NO. TO SELECT TRAIN SCHEDULE FOR EDIT (0 - %d )(ENTER -1 GO BACK MENU): ", count - 1);
	scanf("%d", &option);
	if (option == -1)
	{
		system("cls");
		staffMenu();
	}

	while (option < 0 || option >= count) {
		printf("\n");
		printf("SCHEDULE NOT EXIST\n");
		printf("ENTER THE NO. TO SELECT TRAIN SCHEDULE FOR EDIT (0 - %d )(ENTER -1 TO RETURN MENU)) : ", count - 1);
		scanf("%d", &option);
		//back to staff Menu
		if (option == -1)
		{
			system("cls");
			staffMenu();
		}
	}
	//ask admin what he want to edit
	if (option != -1) {
		system("cls");
		printf("==========================================================================\n");
		printf("                                  EDIT DATA\n");
		printf("==========================================================================\n");
		printf(" NO. TRAIN_ID     TO           FROM         TIME         DAY          SEAT\n");
		printf("==========================================================================\n");
		printf("\n");
		printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%4d\n", option, edit[option].trainID, edit[option].loc.from, edit[option].loc.to, edit[option].startTime, edit[option].arriveTime, edit[option].day, edit[option].seat);
		printf("\n");
		do {
			printf("--------------------------------------------------------------------------\n");
			printf("                               SELECT TO EDIT\n");
			printf("==========================================================================\n");
			printf("1.DEPARTURE STATION\n");
			printf("2.ARRIVAL STATION\n");
			printf("3.TIME\n");
			printf("4.DAY\n");
			printf("5.SEAT\n");
			printf("6.BACK\n");
			printf("==========================================================================\n");
			printf("SELECT A OPTION TO EDIT : ");
			scanf("%d", &opedit);
			while (opedit < 0 || opedit > 6)
			{
				printf("INVALID OPTION ! PLEASE TRY AGAIN...\n");
				printf("SELECT A OPTION TO EDIT : ");
				rewind(stdin);
				scanf("%d", &opedit);

			}
			system("cls");
			printf("==========================================================================\n");
			printf("                                   EDIT  \n");
			printf("==========================================================================\n");
			switch (opedit) {
			case 1:
				printf("ENTER DEPARTURE STATION : ");
				rewind(stdin);
				scanf("%[^\n]", &edit[option].loc.from);
				for (int i = 0; i < 50; i++) {
					edit[option].loc.from[i] = toupper(edit[option].loc.from[i]);
				}
				break;
			case 2:
				printf("ENTER ARRIVAL STATION : ");
				rewind(stdin);
				scanf("%[^\n]", &edit[option].loc.to);
				for (int i = 0; i < 50; i++) {
					edit[option].loc.to[i] = toupper(edit[option].loc.to[i]);
				}
				break;
			case 3:
				printf("ENTER DEPARTURE TIME : ");
				scanf("%4d", &edit[option].startTime);
				printf("ENTER ARRIVAL TIME   : ");
				scanf("%4d", &edit[option].arriveTime);
				break;
			case 4:
				printf("\n==============================\n");
				printf("              DAYS        \n");
				printf("==============================\n");
				printf("0	-	SUNDAY\n");
				printf("1	-	MONDAY\n");
				printf("2	-	TUESDAY\n");
				printf("3	-	WEDNESDAY\n");
				printf("4	-	THUESDAY\n");
				printf("5	-	FRIDAY\n");
				printf("6	-	SATURDAY\n");
				printf("==============================\n");
				printf("ENTER DAY : ");
				rewind(stdin);
				scanf("%[^\n]", &edit[option].day);
				break;
			case 5:
				printf("ENTER SEAT : ");
				rewind(stdin);
				scanf("%d", &edit[option].seat);
				break;
			default:
				system("cls");
				staffMenu();
			}

			printf("==========================================================================\n");
			printf("                               CONFIRM EDIT DATA\n");
			printf("==========================================================================\n");
			printf(" NO. TRAIN_ID     TO           FROM         TIME         DAY          SEAT\n");
			printf("==========================================================================\n");
			printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%4d\n", option, edit[option].trainID, edit[option].loc.from, edit[option].loc.to, edit[option].startTime, edit[option].arriveTime, edit[option].day, edit[option].seat);
			printf("--------------------------------------------------------------------------\n");
			printf("Are you confirm to edit this (y/n) : ");
			rewind(stdin);
			scanf("%c", &confirm);
			//display what admin edit and asking for confirmation
			confirm = tolower(confirm);
			if (confirm == 'y') {

				editTrain = fopen("train.bin", "wb");

				if (editTrain == NULL) {
					printf("File not exist");
					exit(-1);
				}

				for (int a = 0; a < count; a++) {
					fwrite(&edit[a], sizeof(Train), 1, editTrain);
				}

				fclose(editTrain);
				staffMenu();
				break;
			}
			system("cls");
		} while (confirm == 'n');
	}
}

void updateStatus() {
	int count = 0;
	int detect = 0;
	int option, status, quit;
	char confirm;

	FILE* search;
	search = fopen("train.bin", "rb");

	Train edit[100];
	Train change;

	if (search == NULL) {
		printf("File not exist");
		exit(-1);
	}
	printf("=========================================================================================\n");
	printf("                                         UPDATE STATUS\n");
	printf("=========================================================================================\n");
	printf(" NO. TRAIN_ID     TO           FROM         TIME         DAY          SEAT         STATUS\n");
	printf("=========================================================================================\n");
	printf("\n");
	//display all schedule that exist 
	while (fread(&edit[count], sizeof(Train), 1, search) != 0) {
		printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%4d%15s\n", count, edit[count].trainID, edit[count].loc.from, edit[count].loc.to, edit[count].startTime, edit[count].arriveTime, edit[count].day, edit[count].seat, edit[count].status);
		printf("\n");
		count++;
	}
	fclose(search);
	printf("=========================================================================================\n");
	//admin select to edit
	printf("ENTER THE NO. TO SELECT TRAIN SCHEDULE FOR EDIT (0 - %d )(ENTER -1 GO BACK MENU): ", count - 1);
	scanf("%d", &option);
	if (option == -1)
	{
		system("cls");
		staffMenu();
	}

	while (option < 0 || option >= count) {
		printf("\n");
		printf("SCHEDULE NOT EXIST\n");
		printf("ENTER THE NO. TO SELECT TRAIN SCHEDULE FOR EDIT (0 - %d )(ENTER -1 TO RETURN MENU)) : ", count - 1);
		scanf("%d", &option);
		//back to staff Menu
		if (option == -1)
		{
			system("cls");
			staffMenu();
		}
	}
	//ask admin what he want to edit
	if (option != -1) {
		system("cls");
		printf("=========================================================================================\n");
		printf("                                        EDIT STATUS\n");
		printf("=========================================================================================\n");
		printf(" NO. TRAIN_ID     TO           FROM         TIME         DAY          SEAT         STATUS\n");
		printf("=========================================================================================\n");
		printf("\n");
		printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%4d%15s\n", option, edit[option].trainID, edit[option].loc.from, edit[option].loc.to, edit[option].startTime, edit[option].arriveTime, edit[option].day, edit[option].seat, edit[option].status);

		printf("\n========================================================================================\n");
		printf("                                        CHOOSE STATUS        \n");
		printf("=========================================================================================\n");
		printf("1	-	ON BOARD\n");
		printf("2	-	ON SCHEDULE\n");
		printf("3	-	DELAY\n");
		printf("4	-	CANCEL\n");
		printf("5	-	NONE\n");
		printf("=========================================================================================\n");
		printf("STATUS  (1 - 5)     : ");
		rewind(stdin);
		scanf("%d", &status);
		while (status < 1 || status>5)
		{
			printf("INVALID INPUT RE-ENTER!\n");
			printf("STATUS  (1 - 5)     : ");
			rewind(stdin);
			scanf("%d", &status);
		}
		switch (status)
		{
		case 1:
			strcpy(change.status, "ON BOARD");
			break;
		case 2:
			strcpy(change.status, "ON SCHEDULE");
			break;
		case 3:
			strcpy(change.status, "DELAY");
			break;
		case 4:
			strcpy(change.status, "CANCEL");
			break;
		default:
			strcpy(change.status, "NONE");
		}

		do {
			//display to admin the data key in 
			system("cls");
			printf("\n==================================\n");
			printf("|        CONFIRM  CHANGING       |\n");
			printf("==================================\n");
			printf("\nTRAIN ID         :%s\n", edit[option].trainID);
			printf("DEPARTURE FROM   :%s\n", edit[option].loc.from);
			printf("ARRIVE TO        :%s\n", edit[option].loc.to);
			printf("DEPARTURE TIME   :%d\n", edit[option].startTime);
			printf("ARRIVAL TIME     :%d\n", edit[option].arriveTime);
			printf("AVAILABILITY SEAT:%d\n", edit[option].seat);
			printf("DAYS             :%s\n", edit[option].day);
			printf("STATUS           :%s\n", change.status);
			printf("Are you confirm to update status (y/n) : ");
			rewind(stdin);
			scanf("%c", &confirm);
			confirm = tolower(confirm);
			if (confirm == 'n') {
				system("cls");
				updateStatus();
				break;
			}

			else if (confirm == 'y') {
				FILE* editTrain;

				editTrain = fopen("train.bin", "wb");

				strcpy(edit[option].status, change.status);

				if (editTrain == NULL) {
					printf("File not exist");
					exit(-1);
				}

				for (int a = 0; a < count; a++) {
					fwrite(&edit[a], sizeof(Train), 1, editTrain);

				}
				fclose(editTrain);
				system("cls");
				staffMenu();
			}
		} while (confirm != 'n' && confirm != 'y');
	}
}

void dltSchedule() {
	int count = 0;
	int option, quit;
	char vali;

	FILE* dlt;
	FILE* display;
	display = fopen("train.bin", "rb");

	Train edit[100];

	if (display == NULL) {
		printf("File not exist");
		exit(-1);
	}
	//choose a record to delete
	system("cls");
	printf("==========================================================================\n");
	printf("                                TRAIN SCHEDULE\n");
	printf("==========================================================================\n");
	printf(" NO. TRAIN_ID     FROM         TO           TIME         DAY          SEAT\n");
	printf("==========================================================================\n");
	while (fread(&edit[count], sizeof(Train), 1, display) != 0) {
		printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%4d\n", count, edit[count].trainID, edit[count].loc.from, edit[count].loc.to, edit[count].startTime, edit[count].arriveTime, edit[count].day, edit[count].seat);
		count++;
	}
	printf("==========================================================================\n");
	fclose(display);
	do {
		printf("SELECT NO. FOR DELETE THE TRAIN SCHEDULE (0 - %d )(ENTER -1 GO BACK MENU): ", count - 1);
		scanf("%d", &option);
		if (option == -1) {
			system("cls");
			staffMenu();
		}
		while (option < 0 || option >= count) {
			printf("SCHEDULE NOT EXIST\n");
			printf("SELECT NO. FOR DELETE THE TRAIN SCHEDULE (0 - %d ) : ", count - 1);
			scanf("%d", &option);
		}
		printf("==========================================================================\n");
		printf("                               CONFIRM DELETE DATA\n");
		printf("==========================================================================\n");
		printf(" NO. TRAIN_ID     TO           FROM         TIME         DAY          SEAT\n");
		printf("==========================================================================\n");
		printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%4d\n", option, edit[option].trainID, edit[option].loc.from, edit[option].loc.to, edit[option].startTime, edit[option].arriveTime, edit[option].day, edit[option].seat);
		printf("--------------------------------------------------------------------------\n");
		//ask for confirmation
		printf("Are you confirm to delete? (y/n) : ");
		rewind(stdin);
		scanf("%c", &vali);
		vali = tolower(vali);


		if (vali == 'y') {
			system("cls");

			dlt = fopen("train.bin", "wb");

			if (dlt == NULL) {
				printf("File not exist");
				exit(-1);
			}

			for (int a = 0; a < count; a++) {
				if (strcmp(edit[a].trainID, edit[option].trainID) != 0) {
					fwrite(&edit[a], sizeof(Train), 1, dlt);
				}
			}

			fclose(dlt);
			system("cls");
			staffMenu();
			break;
		}
	} while (vali = 'n');
	system("cls");
	staffMenu();
}

void displaySchedule() {
	int choice;
	char day[30];
	//choose day of week too filter
	printf("=========================================================================================\n");
	printf("                                WEEKLY SCHEDULE LIST      \n");
	printf("=========================================================================================\n");
	printf("1)MONDAY\n");
	printf("2)TUESDAY\n");
	printf("3)WEDNESDAY\n");
	printf("4)THURSDAY\n");
	printf("5)FRIDAY\n");
	printf("6)SATURDAY\n");
	printf("7)SUNDAY\n");
	printf("8)BACK\n");
	printf("=========================================================================================\n");
	printf("Choose the option :");
	scanf("%d", &choice);

	while (choice > 8 || choice < 1) {
		printf("Invalid option, Please Try Again.\n");
		printf("Choose the option :");
		scanf("%d", &choice);
	}
	//send user choice to display function
	switch (choice) {
	case 1:
		strcpy(day, "MONDAY");
		system("cls");
		daySchedule(day);
		break;
	case 2:
		strcpy(day, "TUESDAY");
		system("cls");
		daySchedule(day);
		break;
	case 3:
		strcpy(day, "WEDNESDAY");
		system("cls");
		daySchedule(day);
		break;
	case 4:
		strcpy(day, "THURSDAY");
		system("cls");
		daySchedule(day);
		break;
	case 5:
		strcpy(day, "FRIDAY");
		system("cls");
		daySchedule(day);
		break;
	case 6:
		strcpy(day, "SATURDAY");
		system("cls");
		daySchedule(day);
		break;
	case 7:
		strcpy(day, "SUNDAY");
		system("cls");
		daySchedule(day);
		break;
	case 8:
		if (member_ID[0] != '\0')
		{
			system("cls");
			memberMenu();
		}
		else
		{
			system("cls");
			staffMenu();
		}
	}
}

void daySchedule(char day[]) {
	int count = 0, choice;

	FILE* view;
	view = fopen("train.bin", "rb");
	Train vtrn;

	if (view == NULL) {
		printf("File not exist");
		exit(-1);
	}

	printf("=========================================================================================\n");
	printf("                                    %-10s SCHEDULE\n", day);
	printf("=========================================================================================\n");
	printf(" NO. TRAIN_ID     FROM         TO           TIME         DAY          SEAT         STATUS\n");
	printf("=========================================================================================\n");
	printf("\n");
	while (fread(&vtrn, sizeof(vtrn), 1, view) != 0) {
		if (strcmp(day, vtrn.day) == 0) {
			++count;
			printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%-13d%s\n", count, vtrn.trainID, vtrn.loc.from, vtrn.loc.to, vtrn.startTime, vtrn.arriveTime, vtrn.day, vtrn.seat, vtrn.status);
			printf("\n");
		}
	}
	printf("=========================================================================================\n");
	fclose(view);

	if (count == 0) {
		printf("There is no Train on %s...\n", day);
	}
	printf("\n");

	do {
		printf("Press 1 back to Day Selection : ");
		scanf("%d", &choice);

		if (choice == 1) {
			system("cls");
			displaySchedule();
			break;
		}
	} while (choice != 1);
	system("cls");
	memberMenu();
}

void searchSchedule() {
	int choice;
	char result[30];

	do {
		FILE* searching;
		Train search;
		int count = 0;

		searching = fopen("train.bin", "rb");

		if (searching == NULL) {
			printf("File not exist");
			exit(-1);
		}
		//search with departure station 
		system("cls");
		printf("=========================================================================================\n");
		printf("                                    SEARCH TRAIN  SCHEDULE        \n");
		printf("=========================================================================================\n");
		printf("TYPE \"-1\" FOR BACK\n");
		printf("SEARCH DEPARTURE STATION: ");
		rewind(stdin);
		scanf("%[^\n]", result);

		if (strcmp(result, "-1") == 0) {
			fclose(searching);
			system("cls");
			memberMenu();
			break;
		}
		for (int i = 0; i < strlen(result); i++) {
			result[i] = toupper(result[i]);
		}

		printf("=========================================================================================\n");
		printf("                                     SEARCH RESULT\n");
		printf("=========================================================================================\n");
		printf(" NO. TRAIN_ID     FROM         TO           TIME         DAY          SEAT         STATUS\n");
		printf("=========================================================================================\n");

		rewind(searching); // Rewind the file pointer to the beginning

		while (fread(&search, sizeof(search), 1, searching) != 0) {
			if (strcmp(result, search.loc.from) == 0) {
				++count;
				printf("[%2d] %-13s%-13s%-13s%d-%-8d%-13s%-13d%s\n", count, search.trainID, search.loc.from, search.loc.to, search.startTime, search.arriveTime, search.day, search.seat, search.status);
			}
		}
		printf("=========================================================================================\n");
		fclose(searching);

		if (count == 0) {
			printf("%s isn't exist...\n", result);
		}

		printf("Press 1 back to Search : ");
		scanf("%d", &choice);

	} while (choice == 1);
	system("cls");
	memberMenu();
}