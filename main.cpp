
//Summary: This program creates objects called JOBs and adds them to a queue then prints the current time
//and size of the queue to a csv file

#include <iostream>
using namespace std;
#include "JOB.h"
#include <queue>
#include <random>
#include <fstream>



//Pre: none
//Post returns bool based on set probability
bool newJob() {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<> distrib(1, 101);
    return (distrib(e1) >= 30);
};

//Pre: assigned JOB
void PrintNotDone(JOB Temp) {
    cout << "-------------------" << endl;
    cout << "Job #" << Temp.getId() << endl;
    cout << Temp.getName() << endl;
    cout << "Job Total Time:"<<Temp.getTotalTime() << "seconds" << endl;
    cout << "Remaining Time:"<<Temp.getRemainingTime() << "seconds" << endl;
    cout << "Adding " << Temp.getName() <<" Job back to the queue" << endl;
    cout << "-------------------" << endl;
}

//Pre: Assigned JOB
void PrintDone(JOB Temp) {
    cout << "Job #" << Temp.getId() << endl;
    cout << Temp.getName() << "_Job Completed" << endl;
    cout << "Total Time: " << Temp.getTotalTime() << "seconds" << endl;
    cout << "Time idle: " << Temp.getRemainingTime() * -1 << "seconds" << endl;
    cout << "-------------------" << endl;
}
int main() {

    ofstream csv_file("JOBSProgram4.csv");

    if (!csv_file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }


    double ADDJOBTIME = 500;
    double TimeSec = 0;


    unsigned long id = 0;
    long SimJobs = 5;


    queue<JOB> QJ;
    for (long i = 0; i < SimJobs; i++) {
        id++;
        JOB job(id);
        QJ.push(job);
    }
    if (csv_file.is_open()) {
        csv_file << TimeSec << "," << QJ.size() << "\n";
    }



    double timeslice = 2.5;
    double TimeNotUsed = 0;
    double Time;
    while (!QJ.empty()) {
        JOB Temp(QJ.front());
        QJ.pop();
        ADDJOBTIME -= timeslice;
        if (ADDJOBTIME > 0){
            if (newJob) {
                cout << "NEW JOB ADDED" << endl;
                id++;
                JOB *newJob = new JOB(id);
                QJ.push(*newJob);
        }
        }
        Time = Temp.getRemainingTime() - timeslice;
        if (Time > 0) {
            Temp.setRemainingTime(Time);
            PrintNotDone(Temp);
            QJ.push(Temp);
        }
        else {
            Temp.setRemainingTime(Time);
            PrintDone(Temp);
            TimeNotUsed += Temp.getRemainingTime() * -1;
        }
        TimeSec += timeslice;
        csv_file << TimeSec << "," << QJ.size() << "\n";
    }

    while (ADDJOBTIME >= 0) {
        ADDJOBTIME -= timeslice;
        csv_file << TimeSec << "," << QJ.size() << "\n";
    }
    csv_file.close();
    cout << "Time idle: " << TimeNotUsed << "seconds" << endl;

    return 0;
}