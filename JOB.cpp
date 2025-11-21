//#include <iosfwd>
//
// Created by User on 10/15/2025.
//
using namespace std;
#include <iostream>
#include "JOB.h"
#include <random>
#include <cmath>

double randJobTime(long JobType);
//Setters
void setId(long useThisId);
void setRemainingTime(double newTime);


//Getters
long getId();
string getName();
double getRemainingTime();
double getTotalTime();
//DEFAULT CTOR
JOB::JOB() {
    id = -1;
    remainingTime = 0.0;
    totalTime = 0.0;
    name = "UnKnown";
}

//Parameterized constructor
JOB::JOB(long useThisId, string name, double totalTime, double remainingTime) {
    id = useThisId;
    this->name = name;
    this->totalTime = totalTime;
    this->remainingTime = remainingTime;
}

//CTOR with assigned ID
JOB::JOB(long useThisId) {

    this->id = useThisId;

    int MAXPROB_PRINT = 20;
    int MAXPROB_COMPILE = 50;
    int MAXPROB_EMAIL = 90;
    int MAXPROB_OTHER = 100;

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<> distrib(1, 100);
    int randomJob = distrib(e1);
    double t;

    if (1 <= randomJob and randomJob <= MAXPROB_PRINT) {
        t = randJobTime(1);
        name = "PRINT";
    }
    else if (MAXPROB_PRINT < randomJob and randomJob <= MAXPROB_COMPILE) {
        t = randJobTime(2);
        name = "COMPILE";
    }
    else if (MAXPROB_COMPILE < randomJob and randomJob <= MAXPROB_EMAIL) {
        t = randJobTime(3);
        name = "EMAIL";
    }
    else if (MAXPROB_EMAIL < randomJob and randomJob <= MAXPROB_OTHER){
        t = randJobTime(4);
        name = "OTHER";
    }
    else {
        t = 0;
        name = "UNKNOWN";
    }

    totalTime = t;
    remainingTime = t;

}
// COPY CTOR
JOB::JOB(const JOB &job) {
    id = job.id;
    name = job.name;
    totalTime = job.totalTime;
    remainingTime = job.remainingTime;
}

//Pre: assigned JOB
//Post: prints id, name, totalTime, and remainingTime
ostream& operator<< (ostream& os, const JOB& obj) {
    os << "---------------------------" << endl;
    os << "ID: " << obj.id << endl;
    os << "Type: " << obj.name << endl;
    os << "Total Time: " << obj.totalTime << " Seconds" << endl;
    os << "Remaining Time: " << obj.remainingTime << " Seconds" << endl;
    os << "--------------------------" << endl;
    return os;

}

//Pre: assigned long
//Post returns t = (random number based on JobType)
double JOB::randJobTime(long JobType) {
    double t;
    switch (JobType) {
        case 1: {
            std::random_device r;
            std::default_random_engine e1(r());
            std::uniform_int_distribution<> distrib(1, 5);
            t = distrib(e1);
            break;
        }
        case 2: {
            std::random_device r;
            std::default_random_engine e1(r());
            std::uniform_int_distribution<> distrib(10, 100);
            t = distrib(e1);
            break;
        }
        case 3: {
            std::random_device r;
            std::default_random_engine e1(r());
            std::uniform_int_distribution<> distrib(3, 20);
            t = distrib(e1);
            break;
        }
        case 4: {
            std::random_device r;
            std::default_random_engine e1(r());
            std::uniform_int_distribution<> distrib(0, 45);
            t = distrib(e1);
            break;
        }
    }
    return t;
}


//Setters
void JOB::setId(long useThisId) {
    this->id = useThisId;
}
void JOB::setRemainingTime(double newTime) {
    this->remainingTime = newTime;
}


//Getters
long JOB::getId() {
    return this->id;
}
string JOB::getName() {
    return this->name;
}
double JOB::getRemainingTime() {
    return this->remainingTime;
}
double JOB::getTotalTime() {
    return this->totalTime;
}