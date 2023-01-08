#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct node {
    double burstTime;
    double arivalTime;
    double priority;
    struct node *next;
};


node *header;

int Option = 0;
int modeChoice = 0;
int preemptiveModeInt = 0;
int quantum = 6;
double pID = 1.0;
double wt = 0;
double avgWT = 0;
bool menu = false;
string preemptiveModeSTR;
string schedulerMode;
ofstream output;
ifstream input;


int list_is_empty(struct node *);

void displaylist(struct node *);

struct node *newnode(double, double, double);

struct node *insertFront(struct node *, double, double, double);

struct node *insertBack(struct node *, double, double, double);

void insertAfter(struct node *, double, double, double);

struct node *sortList(struct node *);

struct node *sortPriority(struct node *);

struct node *sortArivalTime(struct node *);

int mainMenuFunction(string, string);

int schedulingModeMenu();

void roundRobinResult(struct node *);

void roundrobinSM(const node *temp);

void FCFSResult(node *temp);

void SJF_NonePreemptiveResult(node *temp);

void FCFSschedulingMethod(const node *temp);

void copyLinkedList(struct node *, struct node *);

void setOutputTXTpriority(ofstream &output, node *temp);

void OutputTXTFCFS(ofstream &output, node *temp);

void OutputTXTRoundRobin(ofstream &output, node *temp);


//main method
int main(int argc, char const *argv[]) {
string line,file;
char *p;
    input.open("Input.txt");
    if (input.is_open()){
        while( !input.eof() ){
            input>>line;
            file += line + "\n";
        }
        char * cstr = new char [file.length()+1];
        strcpy (cstr, file.c_str());

  // cstr now contains a c-string copy of file

  p = strtok (cstr,":");
  while (p!=0)
  {
    cout << p << '\n';
    p = strtok(NULL,":");
  }

  delete[] cstr;
  
    }
    cout<<file<<endl<<endl;
    cout<<p;
    header = NULL;
    int count = sizeof(p)/sizeof(p[0]);
    while( count != 0){
        header = insertFront(header,p[count],p[count - 1],p[count - 2]);
        count =- 2;
    }
/*     header = insertFront(header, 5, 4, 2);
    header = insertFront(header, 10, 3, 5);
    header = insertFront(header, 2, 2, 4);
    header = insertFront(header, 1, 1, 1);
    header = insertFront(header, 10, 0, 3);
 */
    preemptiveModeSTR.assign("OFF");
    schedulerMode.assign("NONE");


    while (menu == false) {
//load main menu
        Option = mainMenuFunction(schedulerMode, preemptiveModeSTR);

        switch (Option) {
            case 1:
                modeChoice = schedulingModeMenu();//load scheduling menu
                if (modeChoice == 1) {
                    schedulerMode.assign("FCFS Scheduler");
                }//set scheduling mode to FCFS
                else if (modeChoice == 2) {
                    schedulerMode.assign("SJF Scheduler");
                }//set scheduling mode to SJF
                else if (modeChoice == 3) {
                    schedulerMode.assign("Priority Scheduler");
                }//set scheduling mode to Priority scheduler
                else if (modeChoice == 4) {
                    schedulerMode.assign("RR Scheduler");
                }//set scheduling mode to RR
                else {
                    cout << "Enter a valid option" << endl;
                    modeChoice = schedulingModeMenu();
                }//if scheduling option doesn't exist loop the scheduling menu
                break;
            case 2:
                if (modeChoice == 1) {
                    cout << "Selected mode doesn't support Preemptive mode" << endl;
                    preemptiveModeSTR.assign("OFF");
                }//if FCFS is selected turn off preemptive mode
                else if (modeChoice == 4) {
                    cout << "Selected mode doesn't support Preemptive mode" << endl;
                    preemptiveModeSTR.assign("OFF");
                }//if SJF is selected turn off preemptive mode
                else {
                    cout << "==========[Preemptive mode(ON/OFF)]==========" << endl;
                    cout << "0) OFF" << endl;
                    cout << "1) ON" << endl;
                    cin >> preemptiveModeInt;
                    switch (preemptiveModeInt) {
                        case 1:
                            preemptiveModeSTR.assign("ON");
                            break;
                        case 0:
                            preemptiveModeSTR.assign("OFF");
                            break;
                        default:
                            cout << "Enter a valid option";

                    }//turn preemptive mode
                }
                break;//trun preemptive mode on/off
            case 3:
                if (modeChoice == 1)//FCFS scheduling
                {
                    node *temp = header;
                   
                   
                    cout << "Process scheduling method: " << schedulerMode << endl;
                    cout << "Processes waiting time: " << endl;
                    FCFSResult(temp);

                    menu = true;
                } else if (modeChoice == 2 && preemptiveModeInt == 0)//none preemptive priority scheduling
                {
                    node *temp = header;
                    sortList(temp);
                    cout << "Process scheduling method: " << schedulerMode << endl;
                    cout << "Processes waiting time: " << endl;

                    SJF_NonePreemptiveResult(temp);
                    
                   // OutputTXTFCFS(output,tempOut);
                    menu = true;
                } else if (modeChoice == 2 && preemptiveModeInt == 1) {

                }
                else if (modeChoice == 3 && preemptiveModeInt == 0)//none preemptive priority scheduling
                {
                    node *temp = header;
                    sortPriority(temp);
                    cout << "Process scheduling method: " << schedulerMode << endl;
                    cout << "Processes waiting time: " << endl;
                    FCFSResult(temp);
                    
                    menu = true;

                } else if (modeChoice == 3 && preemptiveModeInt == 1) {

                }
                else if (modeChoice == 4 && preemptiveModeInt == 0)//round robin scheduling
                     {

                    cout << "Process scheduling method: " << schedulerMode << endl;
                    cout << "Processes waiting time: " << endl;
                    node *temporary = header;
                    roundRobinResult(temporary);
                    
                    menu = true;

                }
                else {
                    cout << "Select the right options" << endl;
                    menu = false;
                }


                //menu = true;
                break;//show the result on the console
            case 4:

                if (modeChoice == 1)
                {

                    node *temp = header;
                    OutputTXTFCFS(output,temp);
                }//display FCFS to output file
                else if (modeChoice == 2 && preemptiveModeInt == 0)
                {
                    node *temp = header;
                    sortList(temp);
                    OutputTXTFCFS(output, temp);

                }//display SJF non-preemptive mode to output file
                else if (modeChoice == 2 && preemptiveModeInt == 1)
                {
                    /* code */
                }//display SJF preemptive mode to output file
               else if (modeChoice == 3 && preemptiveModeInt == 0)
                {
                    node *temp = header;
                    setOutputTXTpriority(output, temp);


                }//display priority mode to output file
                else if (modeChoice == 3 && preemptiveModeInt == 1)
                {
                    
                }//display priority preemptive mode to output file
               else if (modeChoice == 4 && preemptiveModeInt == 0)
                {
                    node *temp = header;
                    OutputTXTRoundRobin(output, temp);

                }//display round robin to output file
                else{
                    output<<"Select a scheduling mode";
                    cout<<"Select a scheduling mode";

                }//if no scheduling mode is selected open the menu
                

              
                cout << endl << "CPU Scheduling Simulator has been exited" << '\n';
                menu = true;
                exit(1);
                break;//exit the program and calculate the result
            default:
                cout << "Enter an option in the menu" << '\n';
        }//if main menu option does not exist run the loop again
    }
    output.close();
    return 0;
}

void OutputTXTRoundRobin(ofstream &output, node *temp) {
    output << "Process scheduling method: " << schedulerMode << endl;
    output << "Processes waiting time: " << endl;

    while (NULL != temp) {

        roundrobinSM(temp);
        output << "P" << pID << ".)  " << wt << endl;
        pID++;



        temp = temp->next;

    }
    pID = pID - 1;
    avgWT = avgWT / pID;
    output << "Average waiting time: " << avgWT << endl << endl;

}

void OutputTXTFCFS(ofstream &output, node *temp) {
    output << "Process scheduling method: " << schedulerMode << endl;
    output << "Processes waiting time: " << endl;

    while (NULL != temp) {

output << "P" << pID << ".)  " << wt << endl;
pID++;

FCFSschedulingMethod(temp);

temp = temp->next;

}
    pID = pID - 1;
    avgWT = avgWT / pID;
    output << "Average waiting time: " << avgWT << endl << endl;

}

void setOutputTXTpriority(ofstream &output, node *temp) {
    output << "Process scheduling method: " << schedulerMode << endl;
    output << "Processes waiting time: " << endl;


    sortPriority(temp);

    while (NULL != temp) {

        output << "P" << pID << ".)  " << wt << endl;
        pID++;

        FCFSschedulingMethod(temp);

        temp = temp->next;

    }
    pID = pID - 1;
    avgWT = avgWT / pID;
    output << "Average waiting time: " << avgWT << endl << endl;

}

void SJF_NonePreemptiveResult(node *temp) {
    output << "Process scheduling method: " << schedulerMode << endl;
    output << "Processes waiting time: " << endl;

    while (NULL != temp) {
        avgWT = wt + avgWT;

        cout << "P" << pID << ".)  " << wt << endl;
        

        output << "P" << pID << ".)  " << wt << endl;
        pID++;
        FCFSschedulingMethod(temp);
        temp = temp->next;

    }
    pID = pID - 1;
    avgWT = avgWT / pID;
    cout << "Average waiting time: " << avgWT << endl;
    output << "Average waiting time: " << avgWT << endl;
}

void FCFSResult(node *temp) {
    output << "Process scheduling method: " << schedulerMode << endl;
    output << "Processes waiting time: " << endl;

    while (NULL != temp) {
avgWT = avgWT + wt;
        cout << "P" << pID << ".)  " << wt << endl;
        

        output << "P" << pID << ".)  " << wt << endl;
        pID++;

        FCFSschedulingMethod(temp);

        temp = temp->next;

    }
    pID = pID - 1;
    avgWT = avgWT / pID;
    cout << "Average waiting time: " << avgWT << endl << endl;
    output << "Average waiting time: " << avgWT << endl << endl;
}

void FCFSschedulingMethod(const node *temp) {
    //avgWT = wt + avgWT;

    wt = wt + temp->burstTime;
}

int list_is_empty(struct node *header) {
    if (header == NULL)
        return 1;
    else
        return 0;
}

void displaylist(struct node *header) {
    struct node *Htemp;
    Htemp = header;
    //cout<<"Linked list is: ";
    while (Htemp != NULL) {
        cout << Htemp->burstTime << " ";
        cout << Htemp->arivalTime << " ";
        cout << Htemp->priority << " \n";
        Htemp = Htemp->next;
    }
    cout << endl;

}

struct node *newnode(double bt, double at, double pt) {
    struct node *temp;
    temp = (struct node *) malloc(sizeof(node));
    temp->burstTime = bt;
    temp->arivalTime = at;
    temp->priority = pt;
    temp->next = NULL;
    return temp;
}

struct node *insertFront(struct node *header, double bt, double at, double pt) {
    struct node *temp;
    temp = newnode(bt, at, pt);
    temp->next = header;
    header = temp;
    return header;
}

struct node *insertBack(struct node *header, double bt, double at, double pt) {
    struct node *temp, *Htemp;
    temp = newnode(bt, at, pt);
    if (list_is_empty(header)) {
        header = temp;
        return header;
    }
    Htemp = header;
    while (Htemp->next != NULL)
        Htemp = Htemp->next;
    Htemp->next = temp;

    return header;
}

void insertAfter(struct node *afterNode, double bt, double at, double pt) {
    struct node *temp;
    temp = newnode(bt, at, pt);
    temp->next = afterNode->next;
    afterNode->next = temp;
}

struct node *sortList(struct node *current) {
    //Node current will point to head
    struct node *index = NULL;
    int temp;

    if (list_is_empty(current)) {
        return current;
    } else {
        while (current != NULL) {
            //Node index will point to node next to current
            index = current->next;

            while (index != NULL) {
                //If current node's burst time is greater than index's node burst time, swap the burst time between them
                if (current->burstTime > index->burstTime) {
                    temp = current->burstTime;
                    current->burstTime = index->burstTime;
                    index->burstTime = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

struct node *sortPriority(struct node *current) {
    //Node current will point to head
    struct node *index = NULL;
    int tempBT, tempPT;

    if (list_is_empty(current)) {
        return current;
    } else {
        while (current != NULL) {
            //Node index will point to node next to current
            index = current->next;

            while (index != NULL) {
                //If current node's priority is greater than index's node priority, swap the priority & burst time between them
                if (current->priority > index->priority) {
                    tempBT = current->burstTime;
                    tempPT = current->priority;
                    current->burstTime = index->burstTime;
                    current->priority = index->priority;
                    index->burstTime = tempBT;
                    index->priority = tempPT;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

struct node *sortArivalTime(struct node *current) {
    //Node current will point to head
    struct node *index = NULL;
    int tempBT, tempAT, tempPT;

    if (list_is_empty(current)) {
        return current;
    } else {
        while (current != NULL) {
            //Node index will point to node next to current
            index = current->next;

            while (index != NULL) {
                //If current node's priority is greater than index's node priority, swap the priority & burst time between them
                if (current->arivalTime > index->arivalTime) {
                    tempBT = current->burstTime;
                    tempAT = current->arivalTime;
                    tempPT = current->priority;
                    current->burstTime = index->burstTime;
                    current->arivalTime = index->arivalTime;
                    current->priority = index->priority;
                    index->burstTime = tempBT;
                    index->priority = tempPT;
                    index->arivalTime = tempAT;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

int mainMenuFunction(string mode, string PEMode) {
    int menuChoice;
    cout << "==========[ CPU Scheduler Simulator ]==========" << '\n';
    cout << "1) Scheduling Mode (" << mode << ")" << '\n';
    cout << "2) Preemptive Mode (" << PEMode << ")" << '\n';
    cout << "3) Show result" << '\n';
    cout << "4) End program" << '\n' << endl;
    cout << "Select an option:  ";
    cin >> menuChoice;
    return menuChoice;
}

int schedulingModeMenu() {
    int Choice;
    cout << "******** CPU Scheduler Simulator MODE ********" << '\n';
    cout << "1) First Come First Serve (FCFS) Scheduler " << '\n';
    cout << "2) Shortest Job First (SJF) Scheduler" << '\n';
    cout << "3) Priority Scheduler" << '\n';
    cout << "4) Round Robin" << '\n' << endl;
    cout << "Select an option:  ";
    cin >> Choice;
    return Choice;
}

void roundRobinResult(struct node *temp) {
        output << "Process scheduling method: " << schedulerMode << endl;
    output << "Processes waiting time: " << endl;
    while (temp != NULL) {
        roundrobinSM(temp);

        output << "P" << pID << ".)  " << wt << endl;
        cout << "P" << pID << ".)  " << wt << endl;
        temp = temp->next;
        pID++;
        avgWT += wt;
    }
    pID = pID - 1;
    avgWT = avgWT * (1 / pID);
    cout << "Average waiting time: " << avgWT << endl;
    output << "Average waiting time: " << avgWT << endl;


}

void roundrobinSM(const node *temp) {//if current burst time is greater than quantum set waiting time to be quantum

    avgWT = wt + avgWT;
    if (temp->burstTime >= quantum) {
        // insertBack(temp,temp->burstTime - quantum,temp->arivalTime,temp->priority);

        wt = quantum;
        //   temp = temp->next;
    }

        //if current burst time is less than quantum set waiting time to be burst time
    else {
        wt = temp->burstTime;
        //     temp = temp->next;
    }
}
