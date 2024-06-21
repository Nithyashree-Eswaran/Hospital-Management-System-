#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

// Base class for a person
class Person {
protected:
    string name;
    int age;
public:
    Person(const string& name, int age) : name(name), age(age) {}
    virtual void display() const = 0; // Pure virtual function
};

// Patient class derived from Person
class Patient : public Person {
private:
    string disease;
public:
    Patient(const string& name, int age, const string& disease) : Person(name, age), disease(disease) {}
    void display() const override {
        cout << "Patient Name: " << name << ", Age: " << age << ", Disease: " << disease << endl;
    }
};

// Doctor class derived from Person
class Doctor : public Person {
private:
    string specialization;
public:
    Doctor(const string& name, int age, const string& specialization) : Person(name, age), specialization(specialization) {}
    void display() const override {
        cout << "Doctor Name: " << name << ", Age: " << age << ", Specialization: " << specialization << endl;
    }
};

// Appointment class
class Appointment {
private:
    shared_ptr<Patient> patient;
    shared_ptr<Doctor> doctor;
    string appointmentDate;
public:
    Appointment(shared_ptr<Patient> p, shared_ptr<Doctor> d, const string& date) 
        : patient(p), doctor(d), appointmentDate(date) {}
    void display() const {
        cout << "Appointment Date: " << appointmentDate << endl;
        patient->display();
        doctor->display();
    }
};

// Hospital Management System
class HospitalManagementSystem {
private:
    vector<shared_ptr<Patient>> patients;
    vector<shared_ptr<Doctor>> doctors;
    vector<shared_ptr<Appointment>> appointments;
public:
    void addPatient(const string& name, int age, const string& disease) {
        patients.push_back(make_shared<Patient>(name, age, disease));
    }

    void addDoctor(const string& name, int age, const string& specialization) {
        doctors.push_back(make_shared<Doctor>(name, age, specialization));
    }

    void addAppointment(const string& patientName, const string& doctorName, const string& date) {
        auto patient = findPersonByName<Patient>(patients, patientName);
        auto doctor = findPersonByName<Doctor>(doctors, doctorName);
        if (patient && doctor) {
            appointments.push_back(make_shared<Appointment>(patient, doctor, date));
        } else {
            cout << "Either patient or doctor not found!" << endl;
        }
    }

    void displayAllAppointments() const {
        for (const auto& appointment : appointments) {
            appointment->display();
        }
    }

private:
    template<typename T>
    shared_ptr<T> findPersonByName(const vector<shared_ptr<T>>& people, const string& name) const {
        for (const auto& person : people) {
            if (person->getName() == name) {
                return person;
            }
        }
        return nullptr;
    }
};

// Adding getName() methods for Patient and Doctor to find them by name
string getName() const { return name; }

int main() {
    HospitalManagementSystem hms;
    
    hms.addPatient("John Doe", 30, "Flu");
    hms.addPatient("Jane Smith", 25, "Cold");
    
    hms.addDoctor("Dr. Brown", 45, "Cardiology");
    hms.addDoctor("Dr. Green", 50, "Neurology");
    
    hms.addAppointment("John Doe", "Dr. Brown", "2023-07-20");
    hms.addAppointment("Jane Smith", "Dr. Green", "2023-07-21");
    
    hms.displayAllAppointments();
    
    return 0;
}
