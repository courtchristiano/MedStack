#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#ifndef MEDSTACK_H
#define MEDSTACK_H

class Doctor {
private:
	string Docname;
	string PractitionerType;
	string Specialty;

public:
	Doctor(string dn, string pt, string s);
	void read(istream& in);
	void write(ostream& out) const;
	string getDocname() const { return Docname; }
	string getPractitionerType() const { return PractitionerType; }
	string getSpecality() const { return Specialty; }
};

class date {
private:
	int day;
	int month;
	int year;

public:
	date(int d = 0, int m = 0, int y = 0);
	void read(istream& in);
	void write(ostream& out) const;
	int getday() const { return day; }
	int getmonth() const { return month; }
	int getyear() const { return year; }
};


class Record {
	friend class list;
private:
	int HCN;
	string firstName;
	string lastName;
	string phonenumber;
	string address;
	Doctor doctor;
	//date DOB; 
	int day, month, year;
	string type;
public:
	Record(int H = 0, string f = " ", string l = " ", string a = " ", string p = "", string t = "", string dn = " ", string pt = " ", string s = " ", int d = 0, int m = 0, int y = 0);
	void addPatient(list& patientlist);
	void updatePatient(list& patientlist);
	void updatePractitioner(list& patientlist, int HCN);
	virtual ~Record() { ; }

	int getHCN() const { return HCN; }
	string getfirstName() const { return firstName; }
	string getlastName() const { return lastName; }
	string getphonenumber() const { return phonenumber; }
	string getaddress() const { return address; }
	string gettype() const { return type; }
	Doctor getdoctor() const { return doctor; }
	int getday() { return day; } int getmonth() { return month; } int getyear() { return year; }
	//date getDOB() const { return DOB; }

	void write(ostream& out, list& patientlist) const;
};


//classes for linked lists

class node {
	friend class list;
public:
	Record* data;
	node* next;
	node(Record* x);
};

class list {
public:
	node* start;
	int count;
	int password = 1234;

	list(void);
	void push(Record* item);
	Record* front(void) const;
	int returncount(void) const;
	bool empty(void) const;
	void pop(void);
	void clear(list& patientlist);
};

class Outpatient : public Record {
	friend class list;

private:
	string ReasonForVisit;
	date NextAppointment;
	string Medications;

public:
	Outpatient(string r = "", string meds = "", int nd = 0, int nm = 0, int ny = 0, int H = 0, string f = "", string l = "", string a = "", string p = "", string t = "", string dn = "", string pt = "", string s = "", int d = 0, int m = 0, int y = 0);

	void addoutpatient(list& patientlist);
	void updateMedications(string& Medications, int HCN, list& patientlist);
	void addAppointment(list& patientlist, int HCN);
	void reason(string& rfv, list& patientlist, int HCN);

	void setMedications(const string& meds) { Medications = meds; }
	string getReasonForVisit() const { return ReasonForVisit; }
	string getMedications() const { return Medications; }
	const date& getNextAppointment() const { return NextAppointment; }

	void outwrite(ostream& out, int HCN) const;
};


class Inpatient : public Record {
private:
	date AdmissionDate;
	int RoomNumber;
	date DischargeDate;

public:

	Inpatient(int rn = 0, int ad = 0, int am = 0, int ay = 0, int dd = 0, int dm = 0, int dy = 0, int H = 0, string f = "", string l = "", string a = "", string p = "", string t = "", string dn = "", string pt = "", string s = "", int d = 0, int m = 0, int y = 0);
	void addInpatient(list& patientlist);
	void updateAdmission(list& patientlist, int HCN);
	void updateRoomNumber(list& patientlist, int HCN);
	void updateDischarge(list& patientlist, int HCN);

	int getRoomNumber() const { return RoomNumber; }
	const date& getAdmissionDate() const { return AdmissionDate; }
	const date& getDischargeDate() const { return DischargeDate; }
	void setRoomNumber(int& RM) { RoomNumber = RM; }

	void inwrite(ostream& out, int HCN) const;
};

#endif // !SYSTEM_Hv

