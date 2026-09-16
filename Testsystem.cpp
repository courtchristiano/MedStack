


#include "MedStack.h"

int main(void) {
	list patientlist;
	int HCN = 0; int sizechoice; string rfv = ""; string meds; string type, firstname, lastname, address, phonenumber; date Admissiondate, Dischargedate, DOB, Nextappointment;
	char mainchoice, outchoice, inchoice;
	Record record;
	int password = 1234; int RoomNumber;
	string accesscode;

	//print a menu
	while (1) {
		cout << endl << endl << "|===========================================================|" << endl;
		cout << "|	   MedStack Records INC. Healthcare Database        |" << endl;;
		cout << "|===========================================================|" << endl << endl << endl;

		//password verification to even access main menu
		cout << endl << "Please enter Database Access Code: ";
		cin >> accesscode;

		if (accesscode != "abc") {
			cout << "Password incorrect. ";
			break;
		}
		else {
			cout << endl;
			cout << "|===========================================================|" << endl;
			cout << "|                         MAIN MENU                         |" << endl;
			cout << "|===========================================================|" << endl;
			cout << "|Select an Option:                                          |" << endl;
			cout << "|                                                           |" << endl;
			cout << "| 1 |  Add and Store New Patient Record                     |" << endl;
			cout << "| 2 |  Retrieve Patient Record to Update Any Information    |" << endl;
			cout << "| 3 |  Delete/Clear Patient Record(s) (Password Protected)  |" << endl;
			cout << "| 4 |  Count Records in Database                            |" << endl;
			cout << "| 5 |  Check if Database is Empty                           |" << endl;
			cout << "| 6 |  Print a patient record                               |" << endl;
			cout << "|===========================================================|" << endl;

			cin >> mainchoice;

			//made this an add patient to test
			if (mainchoice == '1') {
				record.addPatient(patientlist);
			}
			else if (mainchoice == '2') {
				record.updatePatient(patientlist);
			}
			else if (mainchoice == '3') {
				patientlist.clear(patientlist);
				cout << "List is cleared.";
			}
			else if (mainchoice == '4') {
				patientlist.returncount();
				cout << "Amount of Records in the List: " << patientlist.returncount();
			}
			else if (mainchoice == '5') {
				if (patientlist.empty()) {
					cout << endl << "List of Records is empty." << endl;
				}
				else {
					cout << endl << "List of Records is not empty." << endl << endl;
					cout << "Would you like to check the size of the list? (Press 1 for Yes, Any Key for No):  ";
					cin >> sizechoice;
					if (sizechoice == '1') {
						patientlist.returncount();
						cout << "Amount of Records in the List: " << patientlist.returncount();
					}
					else {
						break;
					}
				}
			}
			else if (mainchoice == '6') {
				record.write(cout, patientlist);
			}
		}
	}
	return 0;
}