#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
using namespace std;

int menuFunction(string,string);
int modeMenuFunction();

int main(int argc, char const *argv[]) {

    int Option;
    int modeChoice;
    int preemptiveModeInt;
    bool menu = false;
    string preemptiveModeSTR;
    string schedulerMode;
    preemptiveModeSTR.assign("OFF");
    schedulerMode.assign("NONE");
    while (menu == false) {

        Option = menuFunction(schedulerMode,preemptiveModeSTR);

        switch (Option) {
            case 1:
                    modeChoice = modeMenuFunction();
                if(modeChoice == 1){
                    schedulerMode.assign("FCFS Scheduler");
                }
                else if(modeChoice == 2){
                    schedulerMode.assign("SJF Scheduler");
                }
                else if(modeChoice == 3){
                    schedulerMode.assign("Priority Scheduler");
                }
                else if(modeChoice == 4){
                    schedulerMode.assign("RR Scheduler");
                }
                else {
                    cout << "Enter a valid option"<<endl;
                modeChoice = modeMenuFunction();
                }
                break;
            case 2:
                if (modeChoice == 1){
                      preemptiveModeSTR.assign("OFF");
                }else
                {
                    cout<<"==========[Preemptive mode(ON/OFF)]=========="<<endl;
                    cout<<"1) ON"<<endl;
                    cout<<"2) OFF"<<endl;
                    cin>>preemptiveModeInt;
                    switch (preemptiveModeInt) {
                        case 1:
                            preemptiveModeSTR.assign("ON");
                            break;
                        case 2:
                            preemptiveModeSTR.assign("OFF");
                            break;
                        default:
                            cout<<"Enter a valid option";

                    }
                }
                break;
            case 3:
                break;
            case 4:
                cout << endl <<"CPU Scheduling Simulator has been exited" << '\n';
                exit(1);
                break;
            default:
                cout << "Enter an option in the menu" << '\n';
                menu=true;
        }
    }
    return 0;
}

int menuFunction(string mode,string PEMode){
    int menuChoice;
    cout << "==========[ CPU Scheduler Simulator ]==========" << '\n';
    cout << "1) Scheduling Mode (" <<mode<<")"<< '\n';
    cout << "2) Preemptive Mode (" <<PEMode<<")"<< '\n';
    cout << "3) Show result" << '\n';
    cout << "4) End program" << '\n' << endl;
    cout <<"Select an option:  ";
    cin >> menuChoice;
    return menuChoice;
}

int modeMenuFunction(){
    int Choice;
    cout << "******** CPU Scheduler Simulator MODE ********" << '\n';
    cout << "1) First Come First Serve (FCFS) Scheduler "<< '\n';
    cout << "2) Shortest Job First (SJF) Scheduler" << '\n';
    cout << "3) Priority Scheduler" << '\n';
    cout << "4) Round Robin" << '\n' << endl;
    cout <<"Select an option:  ";
    cin >> Choice;
    return Choice;
}
