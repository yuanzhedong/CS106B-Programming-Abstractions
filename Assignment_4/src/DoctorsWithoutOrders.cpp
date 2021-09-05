/* File: DoctorsWithoutOrders.cpp
 * ---------------
 * This program determines if there is any way in which a set of doctors can attend a set of patients. The program will return a
 * true or false value, and if true, will return a schedule specifying in what way doctors can attend all patients.
 */

#include "DoctorsWithoutOrders.h"
#include "Testing/DoctorsWithoutOrdersTests.h"
using namespace std;

/* Function: patientsRec
 * -----------------------
 * This function takes as parameters (1) a hashmap of doctors, where keys represent each doctor and integers represent the hours they have
 * available, (2) a hashmap of patients, which holds the patients that haven't been assigned to a doctor yet, (3) a hashmap of chosen patients,
 * which holds the patients that have been assigned to doctors, and (4) a schedule which contains the ways in which doctors are attending
 * patients. The function return true if there is any way in which all patients can be seen by doctors.
 */
bool patientsRec(const HashMap<string, int>& doctors,
                 const HashMap<string, int>& patients,
                 const HashMap<string, int>& chosen,
                 HashMap<string, HashSet<string>>& schedule) {
    // If there are no doctors, return false
    if (doctors.isEmpty()) {
        return false;
    }
    // Base case: if patients is empty, all patients are being seen by doctors. Thus, return true and print out the schedule
    if (patients.isEmpty()) {
        return true;
    }
    // Recursive case: choose a patient, then iterate over all of the doctors and check if the doctor has enough hours to see the
    // patient. If there are enough hours, assign the patient to that doctor, update the inputs and call patientsRec again
    string patientKey = patients.front();
    int patientHrs = patients[patientKey];
    Vector<string> allDoctorKeys = doctors.keys();
    for (string docKey:allDoctorKeys) { //iterating over all doctors
        int doctorHrs = doctors[docKey];
        if (patientHrs <= doctorHrs) {
            HashMap<string, int> remainingDoc = doctors;
            remainingDoc[docKey] -= patientHrs; // update the hours available for this doctor
            HashMap<string, int> remainingPat = patients;
            remainingPat.remove(patientKey); // remove the patient from the list
            HashMap<string, int> patientsChosen = chosen;
            patientsChosen[patientKey] = patientHrs; // add that patient to the chosen list
            if (patientsRec(remainingDoc, remainingPat, patientsChosen, schedule)) {
                schedule[docKey] += patientKey; // once the function returns true, update the schedule assigning the patient to the doctor
                return true;
            }
        }
    }
    return false;
}

/* Function: canAllPatientsBeSeen
 * ------------------------------
 * This wrapper function takes as input doctors, patients and schedule. It calls patientsRec assigning an empty HashMap as chosen.
 */
bool canAllPatientsBeSeen(const HashMap<string, int>& doctors,
                          const HashMap<string, int>& patients,
                          HashMap<string, HashSet<string>>& schedule) {
    return patientsRec(doctors, patients, {}, schedule);
}

/* * * * * * Test Cases Below This Point * * * * * */

ADD_TEST("All patients can be seen if there are no patients") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Phil", 3 },
        { "Dr. Strangelove", 5 }
    };

    EXPECT(canAllPatientsBeSeen(doctors, {}, schedule));
}

/* * * * * Provided Tests Below This Point * * * * */

ADD_TEST("Provided Test: Can't schedule if a patient requires more hours than any doctor has.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Zhivago", 8 },
        { "Dr. Strange", 8 },
        { "Dr. Horrible", 8 },
    };
    HashMap<string, int> patients = {
        { "You Poor Soul", 9 },  // Needs more time than any one doctor can provide
    };

    EXPECT(!canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Can schedule if doctor has way more time than patient needs.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Wheelock", 12 },
    };
    HashMap<string, int> patients = {
        { "Lucky Patient", 8 },
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Can schedule if there's one doctor and one patient with the same hours.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Wheelock", 8 },
    };
    HashMap<string, int> patients = {
        { "Lucky Patient", 8 },
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Schedule for one doctor and one patient is correct.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. Wheelock", 8 },
    };
    HashMap<string, int> patients = {
        { "Lucky Patient", 8 },
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));

    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Dr. Wheelock", { "Lucky Patient" } }
    };
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Single doctor can see many patients.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. House", 7 },
    };
    HashMap<string, int> patients = {
        { "Patient A", 4 },
        { "Patient B", 2 },
        { "Patient C", 1 }
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));

    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Dr. House", { "Patient A", "Patient B", "Patient C" } }
    };
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Multiple doctors can see multiple patients.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Dr. House", 7  },
        { "AutoDoc",   70 }
    };
    HashMap<string, int> patients = {
        { "Patient A", 4  },
        { "Patient B", 2  },
        { "Patient C", 1  },
        { "Patient D", 40 },
        { "Patient E", 20 },
        { "Patient F", 10 }
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));

    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Dr. House", { "Patient A", "Patient B", "Patient C" } },
        { "AutoDoc",   { "Patient D", "Patient E", "Patient F" } },
    };
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Doesn't necessarily assign neediest patient to most available doctor.") {
    HashMap<string, HashSet<string>> schedule;

    HashMap<string, int> doctors = {
        { "Doctor Workaholic", 10 },
        { "Doctor Average",    8 },
        { "Doctor Lazy",       6 },
    };
    HashMap<string, int> patients = {
        { "Patient EightHour", 8 },
        { "Patient SixHour",   6 },
        { "Patient FiveHour1", 5 },
        { "Patient FiveHour2", 5 }
    };

    /* You can't make this work if you assign Patient EightHour to Doctor Workaholic.
     * The only way for this setup to work is if you give the two five-hour patients
     * to Doctor Workaholic.
     */
    HashMap<string, HashSet<string>> expectedSchedule = {
        { "Doctor Workaholic", { "Patient FiveHour1", "Patient FiveHour2" } },
        { "Doctor Average",    { "Patient EightHour" } },
        { "Doctor Lazy",       { "Patient SixHour" } }
    };

    EXPECT(canAllPatientsBeSeen(doctors, patients, schedule));
    EXPECT_EQUAL(schedule, expectedSchedule);
}

ADD_TEST("Provided Test: Can't schedule patients if there are no doctors.") {
    HashMap<string, int> patients = {
        { "You Poor Soul", 8 },
    };
    HashMap<string, HashSet<string>> schedule;
    EXPECT(!canAllPatientsBeSeen({}, patients, schedule));
}

ADD_TEST("Provided Test: Agreement in total hours doesn't mean a schedule exists (1).") {
    HashMap<string, int> doctors = {
        { "Doctor A", 3 },
        { "Doctor B", 3 },
    };
    HashMap<string, int> patients = {
        { "Patient X", 2 },
        { "Patient Y", 2 },
        { "Patient Z", 2 },
    };

    /* Notice the the total hours free (6) matches the total hours needed (6), but it's set
     * up in a way where things don't align properly.
     */
    HashMap<string, HashSet<string>> schedule;
    EXPECT(!canAllPatientsBeSeen(doctors, patients, schedule));
}

ADD_TEST("Provided Test: Agreement in total hours doesn't mean a schedule exists (2).") {
    HashMap<string, int> doctors = {
        { "Doctor A", 8 },
        { "Doctor B", 8 },
        { "Doctor C", 8 },
    };
    HashMap<string, int> patients = {
        { "Patient U", 5 },
        { "Patient V", 5 },
        { "Patient W", 5 },
        { "Patient X", 4 },
        { "Patient Y", 3 },
        { "Patient Z", 2 },
    };

    /* Notice the the total hours free (24) matches the total number of hours needed
     * (24), but the way those hours are divvied up makes things impossible. Specifically,
     * no doctor can see two of the patients who each need five hours, so they need to be
     * spread around the three doctors evenly, but then there isn't enough time for
     * anyone to see the patient who needs four hours.
     */
    HashMap<string, HashSet<string>> schedule;
    EXPECT(!canAllPatientsBeSeen(doctors, patients, schedule));
}
