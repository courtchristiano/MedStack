//file system.cpp
#include "MedStack.h"

//Implementation of Doctor
Doctor::Doctor(string dn, string pt, string s) {
	Docname = dn; PractitionerType = pt; Specialty = s;
	//general constructor
}
void Doctor::read(istream& in) {
	cout << "Doctor Name: " << endl;
	in >> Docname;
	cout << "Practitioner Type: " << endl;
	in >> PractitionerType;
	cout << "Specality: " << endl;
	in >> Specialty;
	//read function prompts user to enter doctor information
}
void Doctor::write(ostream& out) const {
out << "====================================================="<<endl;
out << "|                  DOCTOR INFORMATION               |" <<endl;
out << "=====================================================" << endl;
out << "|            Doctor: Dr. " << Docname << endl;
out << "| Practitioner Type: " << PractitionerType << endl;
out << "|         Specialty: " << Specialty << endl;
out << "=====================================================" << endl;
	//general write function
}


//Implementation of date
date::date(int d, int m, int y) {
	day = d; month = m; year = y;
	//general constructor
}
void date::read(istream& in) {
	char temp;
	//before we print this we will say "DOB or appointment or whatever is necessary"
	in >> day >> temp >> month >> temp >> year;

	//prompts user to enter date information
}
void date::write(ostream& out) const {
	out << day << "/" << month << "/" << year << endl;
	//prints information
}


//Implementation of Record
Record::Record(int H, string f, string l, string a, string p, string t, string dn, string pt, string s, int d, int m, int y) : doctor(dn, pt, s) {
	HCN = H; firstName = f; lastName = l; address = a; phonenumber = p; type = t; day = d; month = m; year = y;
	//general constructor
}

void Record::addPatient(list& patientlist) {
	string firstName, lastName, address, phonenumber, type;
	int HCN = 0;
	Doctor doctor("", "", "");
	//date DOB;
	int day = 0, month = 0, year = 0; char temp;

	// Step 1: Get the patient's HCN
	cout << "Enter Patient HCN: " << endl;
	cin >> HCN;

	// Step 2: Check if the patient already exists in the list
	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
		if (HCN == ptr->data->getHCN()) {
			cout << "Patient already in database" << endl;
			return; // Exit the function if the patient already exists
		}
	}

	// Step 3: Create a new Record for the patient
	Record* newPatient = new Record();

	// Step 4: Collect patient information
	cout << "Enter patient first name and last name (example: John Appleseed): " << endl;
	cin >> firstName >> lastName;
	newPatient->firstName = firstName;
	newPatient->lastName = lastName;

	cout << "Enter patient phone number with no spaces (example: 5551234567): " << endl;
	cin >> phonenumber;
	newPatient->phonenumber = phonenumber;

	// Clear input buffer before using getline
	cin.ignore();  // Clear the newline character left in the buffer

	cout << "Enter Patient Address with no spaces (example: 250BluejayLane): " << endl;
	getline(cin, address);
	newPatient->address = address;

	// Step 5: Collect doctor information
	doctor.read(cin);  // Assuming doctor.read() sets doctor attributes correctly
	newPatient->doctor = doctor;

	cout << "Enter Date of Birth (example: for June 10th 1992, enter 10/6/1992): " << endl;
	//newPatient->DOB.read(cin);
	//cout << "DOB entered: " << newPatient->DOB.getday() << "/" << newPatient->DOB.getmonth() << "/" << newPatient->DOB.getyear() << endl;
	cin >> day >> temp >> month >> temp >> year;

	// Step 6: Collect patient type (inpatient or outpatient)
	cout << "Enter patient type (inpatient or outpatient): ";
	cin >> type;
	newPatient->type = type;

	// Step 7: Check the patient type and create appropriate object
	if (newPatient->type == "inpatient" || newPatient->type == "Inpatient") {
		// Create and add an inpatient record
		Inpatient* inpatientPatient = new Inpatient(0, 0, 0, 0, 0, 0, 0, HCN, firstName, lastName, address, phonenumber, type, doctor.getDocname(), doctor.getPractitionerType(), doctor.getSpecality(), day, month, year);
		inpatientPatient->addInpatient(patientlist); // Add to the list
	}
	else if (newPatient->type == "outpatient" || newPatient->type == "Outpatient") {
		// Create and add an outpatient record
		Outpatient* outpatientPatient = new Outpatient(" ", "", 0, 0, 0, HCN, firstName, lastName, address, phonenumber, type, doctor.getDocname(), doctor.getPractitionerType(), doctor.getSpecality(), day, month, year);
		outpatientPatient->addoutpatient(patientlist); 
	}
	else {
		cout << "Invalid Type!" << endl;
	}
}

void Record::updatePatient(list& patientlist) {
	int HCN = 0; string Medications, rfv;
	char Choice;

	cout << "Enter HCN: ";
	cin >> HCN; //to search by HCN

	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) { //Linear search

		if (ptr->data->getHCN() == HCN) { //if HCN found

			cout << "|===========================================================|" << endl;
			cout << "|                   UPDATE RECORD MENU                      |" << endl;
			cout << "|===========================================================|" << endl;
			cout << "|Select an Option:                                          |" << endl;
			cout << "|                                                           |" << endl;
			cout << "|  1 |  Update First Name                                   |" << endl;
			cout << "|  2 |  Update Last Name                                    |" << endl;
			cout << "|  3 |  Update Phone Number                                 |" << endl;
			cout << "|  4 |  Update Address                                      |" << endl;
			cout << "|  5 |  Update Medications                                  |" << endl;
			cout << "|  6 |  Update Next Appointment                             |" << endl;
			cout << "|  7 |  Update Reason For Visit                             |" << endl;
			cout << "|  8 |  Update Room Number                                  |" << endl;
			cout << "|  9 |  Update Dishcharge Date                              |" << endl;
			cout << "|  A |  Update Admission Date                               |" << endl;
			cout << "|  B |  Update Patient Practitioner                         |" << endl;
			cout << "|===========================================================|" << endl;
			cin >> Choice; //choose what to update

			if (Choice == '1') {
				cout << "Enter new first name: ";
				cin >> ptr->data->firstName; //change data for firstname
				cout << "First name (for HCN: " << HCN << ") has been updated to: " << ptr->data->firstName << endl << endl;
				return;
			}
			else if (Choice == '2') {
				cout << "Enter new last name: ";
				cin >> ptr->data->lastName; //change data for lastname
				cout << endl << "Last name (for HCN: " << HCN << ") has been updated to:" << ptr->data->lastName << endl << endl;
				return;
			}
			else if (Choice == '3') {
				cout << "Enter New phonenumber (no spaces): ";
				cin >> ptr->data->phonenumber; //change data for phone number
				cout << "Phone number (for HCN: " << HCN << ") has been updated to: " << ptr->data->phonenumber << endl << endl;
				return;
			}
			else if (Choice == '4') {
				cout << "Enter new address: ";
				cin >> ptr->data->address; //change data for address
				cout << "Patient address rre(for HCN: " << HCN << ")has been updated to: " << ptr->data->address << endl << endl;
				return;
			}
			else if (Choice == '5') {
				if (ptr->data->type == "Outpatient" || ptr->data->type == "outpatient") {
					Outpatient* outpatientPtr = static_cast<Outpatient*>(ptr->data);
					outpatientPtr->updateMedications(Medications, HCN, patientlist);
				}
				else {
					cout << "Patient is not an outpatient";
				}
			}
			else if (Choice == '6') {
				if (ptr->data->type == "Outpatient" || ptr->data->type == "outpatient") {
					Outpatient* outpatientPtr = static_cast<Outpatient*>(ptr->data);
					outpatientPtr->addAppointment(patientlist, HCN);
				}
				else {
					cout << "Patient is not an outpatient";
				}
			}
			else if (Choice == '7') {
				if (ptr->data->type == "Outpatient" || ptr->data->type == "outpatient") {
					Outpatient* outpatientPtr = static_cast<Outpatient*>(ptr->data);
					outpatientPtr->reason(rfv, patientlist, HCN);
				}
				else {
					cout << "Patient is not an outpatient";
				}
			}
			else if (Choice == '8') {
				if (ptr->data->type == "Inpatient" || ptr->data->type == "inpatient") {
					Inpatient* inpatientPtr = static_cast<Inpatient*>(ptr->data);
					inpatientPtr->updateRoomNumber(patientlist, HCN);
				}
				else {
					cout << "Patient is not an inpatient";
				}
			}
			else if (Choice == '9') {
				if (ptr->data->type == "Inpatient" || ptr->data->type == "inpatient") {
					Inpatient* inpatientPtr = static_cast<Inpatient*>(ptr->data);
					inpatientPtr->updateDischarge(patientlist, HCN);
				}
				else {
					cout << "Patient is not an inpatient";
				}
			}
			else if (Choice == 'a' || Choice == 'A') {
				if (ptr->data->type == "Inpatient" || ptr->data->type == "inpatient") {
					Inpatient* inpatientPtr = static_cast<Inpatient*>(ptr->data);
					inpatientPtr->updateAdmission(patientlist, HCN);
				}
				else {
					cout << "Patient is not an inpatient";
				}
			}
			else if (Choice == 'b' || Choice == 'B') {
				ptr->data->updatePractitioner(patientlist, HCN);
			}
		}
	}
}

void Record::updatePractitioner(list& patientlist, int HCN) {
	//use doctor.read(cin) to read new practitoner
	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) { //search
		if (ptr->data->getHCN() == HCN) { //if HCN matches
			ptr->data->doctor.read(cin); //update doctor info
		}
	}
}

void Record::write(ostream& out, list& patientlist) const {
	bool found = false;
	int HCN;

	// Step 1: Ask for the patient's HCN
	cout << "Enter HCN: ";
	cin >> HCN;

	// Step 2: Traverse through the list to find the patient
	node* current = patientlist.start;

	while (current != NULL) {
		// Step 3: If the patient's HCN matches
		if (current->data->getHCN() == HCN) {
			found = true;

			// Print the patient's basic details
			
			out << endl;
			out << "====================================================="<<endl;
			out << "|             PRINTING PATIENT RECORD               |"<<endl;
			out << "====================================================="<<endl;
			out << "|          Full Name: " << current->data->lastName << ", " << current->data->firstName << endl;
			out << "| Health Card Number: " << current->data->HCN << endl;
			out << "|       Home Address: " << current->data->address << endl;
			out << "|       Phone Number: " << current->data->phonenumber << endl;
			out << "|      Date of Birth: " << current->data->getday() << "/" << current->data->getmonth() << "/" << current->data->getyear();
			current->data->doctor.write(out);

			// Step 4: Check for patient type (Inpatient/Outpatient)
			if (current->data->type == "inpatient" || current->data->type == "Inpatient") {
				Inpatient* inpatientPtr = (Inpatient*)current->data;  // Cast to Inpatient directly
				inpatientPtr->inwrite(out, HCN);  // Call the inwrite function for inpatient
			}
			else if (current->data->type == "outpatient" || current->data->type == "Outpatient") {
				Outpatient* outpatientPtr = (Outpatient*)current->data;  // Cast to Outpatient directly
				outpatientPtr->outwrite(out, HCN);  // Call the outwrite function for outpatient
			}
			else {
				out << "Invalid patient type!" << endl;
			}

			out << "---------------------------" << endl;
			break;  // We found the patient, so no need to keep searching
		}
		current = current->next;  // Move to the next patient in the list
	}

	// Step 5: If no patient was found with the given HCN
	if (!found) {
		cout << "Patient with HCN " << HCN << " not found." << endl;
	}
}


//Implementation of Outpatient
Outpatient::Outpatient(string r, string meds, int nd, int nm, int ny, int H, string f, string l, string a, string p, string t, string dn, string pt, string s, int d, int m, int y) : NextAppointment(nd, nm, ny), Record(H, f, l, a, p, t, dn, pt, s, d, m, y) {
	ReasonForVisit = r; Medications = meds;
}

void Outpatient::addoutpatient(list& patientlist) {
	int HCN; string firstName, lastName, address, phonenumber, type, reasonforvisit, medications; date NextAppointment;

	cout << "Enter Reason For Visit: " << endl;
	cin >> reasonforvisit;
	cin.ignore();
	cout << "Enter Patient Medications: " << endl;
	cin >> medications;
	cout << "Enter Next Appointment Date" << endl;
	NextAppointment.read(cin);

	Outpatient* newoutpatient = new Outpatient(reasonforvisit, medications, NextAppointment.getday(), NextAppointment.getmonth(), NextAppointment.getyear(), this->getHCN(), this->getfirstName(), this->getlastName(), this->getaddress(), this->getphonenumber(), this->gettype(), this->getdoctor().getDocname(), this->getdoctor().getPractitionerType(), this->getdoctor().getSpecality(), this->getday(), this->getmonth(), this->getyear());

	patientlist.push(newoutpatient);
}

void Outpatient::updateMedications(string& Medications, int HCN, list& patientlist) {
	string newmeds;

	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
		//search
		if (ptr->data->getHCN() == HCN) {
			//Outpatient* outpatientPtr = static_cast<Outpatient*>(&ptr->data);
			Outpatient* outpatientPtr = dynamic_cast<Outpatient*>(ptr->data);
			cout << "Enter Updated Medication";
			cin >> newmeds;
			outpatientPtr->setMedications(newmeds); //updates medications
			cout << "New Medication Updated Successfully!";
		}
	}
}

void Outpatient::addAppointment(list& patientlist, int HCN) {
	//search by HCN 
	//Use date.read(cin) to read next appointment date
	cout << "Enter HCN of Patient" << endl;
	cin >> HCN;

	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {

		if (ptr->data->getHCN() == HCN) {
			cout << "Enter new appointment date: " << endl;
			NextAppointment.read(cin);
		}
	}
}

void Outpatient::reason(string& rfv, list& patientlist, int HCN) {
	string reason;

	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
		if (ptr->data->getHCN() == HCN) {
			cout << "Enter Patients Reason for visit: ";
			cin >> reason;
			reason += rfv; //append reason for visit on to string
			cout << "Added successfully! " << endl;
		}
	}
}



void Outpatient::outwrite(ostream& out, int HCN) const {
	out << "Patient Medications: " << getMedications() << endl;
	cout << " ";
	out << "Patient Reason For Visit: " << getReasonForVisit() << endl;
	cout << " ";
	out << endl << "Patients Next Appointment: ";
	getNextAppointment().write(out);
	cout << " ";
}


//Implementation of Inpatient

Inpatient::Inpatient(int rn, int ad, int am, int ay, int dd, int dm, int dy, int H, string f, string l, string a, string p, string t, string dn, string pt, string s, int d, int m, int y) : AdmissionDate(ad, am, ay), DischargeDate(dd, dm, dy), Record(H, f, l, a, p, t, dn, pt, s, d, m, y) {
	RoomNumber = rn;
}

void Inpatient::addInpatient(list& patientlist) {
	int RoomNumber, HCN; string firstName, lastName, address, phonenumber, type;
	Doctor doctor(" ", "", "");
	date AdmissionDate, DischargeDate, DOB;

	// Collect Inpatient-specific information
	cout << "Enter patients room number: ";
	cin >> RoomNumber;
	cout << "Enter patient admission date: ";
	AdmissionDate.read(cin);
	cout << "Enter patient discharge date: ";
	DischargeDate.read(cin);

	// Create an Inpatient object using the data
	Inpatient* newInpatient = new Inpatient(RoomNumber, AdmissionDate.getday(), AdmissionDate.getmonth(), AdmissionDate.getyear(), DischargeDate.getday(), DischargeDate.getmonth(), DischargeDate.getyear(), this->getHCN(), this->getfirstName(), this->getlastName(), this->getaddress(), this->getphonenumber(), this->gettype(), this->getdoctor().getDocname(), this->getdoctor().getPractitionerType(), this->getdoctor().getSpecality(), this->getday(), this->getmonth(), this->getyear());

	// Add the Inpatient to the patient list
	patientlist.push(newInpatient);

	cout << endl << "------Inpatient Record Added Successfully!------ " << endl << endl;
}

void Inpatient::updateAdmission(list& patientlist, int HCN) {

	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
		if (ptr->data->getHCN() == HCN) {
			cout << "Enter Admission Date: " << endl;
			AdmissionDate.read(cin);
			cout << "Admission date added successfully! " << endl;
		}
	}
}
void Inpatient::updateRoomNumber(list& patientlist, int HCN) {
	int newRoomNumber;

	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
		if (ptr->data->getHCN() == HCN) {
			Inpatient* inpatientPtr = dynamic_cast<Inpatient*>(ptr->data);
			cout << "Enter new room number";
			cin >> newRoomNumber;
			inpatientPtr->setRoomNumber(newRoomNumber);
			cout << "New room number added successfully!";
		}

	}
}

void Inpatient::updateDischarge(list& patientlist, int HCN) {

	for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
		if (ptr->data->getHCN() == HCN) {
			cout << "Enter Discharge Date: " << endl;
			DischargeDate.read(cin);
			cout << "Discharge date added successfully! " << endl;
		}
	}
}


void Inpatient::inwrite(ostream& out, int HCN) const {
	out << "Patient Room Number: " << getRoomNumber();
	out << " " << endl << "Patient Admission Date: ";
	AdmissionDate.write(out);
	out << " " << endl << "Patient Discharge Date: ";
	DischargeDate.write(out);
	cout << " ";
}

//Implementation of node and list

node::node(Record* x) : data(x), next(NULL) {}

list::list(void) {
	start = NULL;
	count = 0;
}

void list::push(Record* item) {
	node* newNode = new node(item);  // Create a new node to store the Record pointer

	if (start == nullptr) {
		start = newNode;  // If the list is empty, make newNode the start
	}
	else {
		node* temp = start;
		while (temp->next != nullptr) {
			temp = temp->next;  // Traverse to the end of the list
		}
		temp->next = newNode;  // Add the new node to the end
	}
	count++;  // Increment the count of records in the list
}

Record* list::front(void) const {
	return start->data;
}

int list::returncount(void) const {
	return count;
}

bool list::empty(void) const {
	return (count == 0);
}

void list::pop(void) {
	node* ptr = start;
	start = start->next;
	delete ptr;
	count--;
}

void list::clear(list& patientlist) {
	int temp; char choice = '0'; int HCN;
	cout << "Enter Password: ";
	cin >> temp;

	if (temp == password) {
		cout << "Select 1 to search and delete a patient" << endl;
		cout << "Select 2 to clear the whole list" << endl;
		cin >> choice;
		if (choice == '1') {
			cin.ignore();
			cout << "Enter the HCN of the patient";
			cin >> HCN;
			for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
				if (HCN == ptr->data->getHCN()) {
					node* temp = ptr;
					delete temp->data;
					delete temp;
					count--;
				}
				else {
					cout << "Patient is not in database";
				}
			}
		}
		else if (choice == '2') {
			for (node* ptr = patientlist.start; ptr != NULL; ptr = ptr->next) {
				node* temp = ptr;
				delete temp->data;
				delete temp;
			}
		}
	}
}

