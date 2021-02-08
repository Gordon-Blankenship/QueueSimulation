/** 02/05/2021 - Program01
 *  Single Queue vs Multiple Queue Simulation
 *  by Tre Blankenship
 *  IT 279 Sec001
 * 
 *  This program is to show the average wait times
 *  for fast food registers is faster when fed
 *  by a single queue as opposed to multiple queues
 *  feeding an according register
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Queue.h"

struct Register{
    CustomerData cust;
    bool isInUse = false;

    Register(){}
    Register(CustomerData c) : cust(c), isInUse(true) {}
};

int main(int argc, char **argv){
    
    // Initializing maximum time between customers (maxBetween),
    // maximum time it takes for service (maxService),
    // and the random seed for simulation
    int maxBetween = atoi(argv[1]);
    int maxService = atoi(argv[2]);
    int randomSeed = 0;

    if(argc > 3){
        randomSeed = atoi(argv[3]);
    }
    if(randomSeed){
        srand(randomSeed);
    }
    else{
        srand(time(nullptr));
    }

    // Creating files to dump in
    std::ofstream outfile1("singleline.txt");
    std::ofstream outfile2("multiplelines.txt");
    
    // Initializing register queues
    Queue *q1 = new Queue(); // Single line -> 3 registers

    Queue *multQ[3] = { new Queue(), new Queue(), new Queue() }; // => keep track of who's feeding who

    Register registersS[3]; // fed by q1
    Register registersM[3]; // [0] fed by q2, [1] fed by q3, [2] fed q4

    double avgWaitS = 0;
    double avgWaitM = 0;
    int maxWaitS = 0;
    int maxWaitM = 0;
    int maxLineLS = 0;
    int maxLineLM = 0;

    int custAmount = 1; // Keep track of customer number
    int beginTime = rand() % maxBetween + 1; // Arrival of 1st customer
    int custServTime = rand() % maxService + 1;
    int nextCustArr = (rand() % maxBetween + 1) + beginTime;

    CustomerData customer(custAmount, beginTime, custServTime);
    // Single Sim
    registersS[0].cust = customer;
    registersS[0].cust.serviceTime += beginTime;
    registersS[0].isInUse = true;
    // Multiple Sim
    registersM[0].cust = customer;
    registersM[0].cust.serviceTime += beginTime;
    registersM[0].isInUse = true;

    outfile1<<"Customer "<<(custAmount)<<" arrived at "<<(beginTime)<<"\n"; // 1st customer arrived
    outfile2<<"Customer "<<(custAmount)<<" arrived at "<<(beginTime)<<"\n";

    outfile1<<"Customer "<<(custAmount)<<" served by "<<(1)<<" starting at "<<(beginTime)<<"\n"; // 1st customer receiving help
    outfile2<<"Customer "<<(custAmount)<<" served by "<<(1)<<" starting at "<<(beginTime)<<"\n";

    for(int i = beginTime; i <= 720; i++){
        // Check if service is complete at any register
        for(int j = 0; j < 3; j++){
            // Single Queue Simulation
            if(registersS[j].isInUse == true){
                if(i == (registersS[j].cust.serviceTime)){ // Service is complete, remove from register
                    outfile1<<"Customer "<<registersS[j].cust.customerNumber<<" departed at "<<(i)<<"\n";
                    registersS[j].cust = CustomerData();
                    registersS[j].isInUse = false;
                    if(q1->isEmpty() == false){
                        registersS[j].cust = q1->dequeue();
                        int waitTime = i - registersS[j].cust.arrivalTime;
                        avgWaitS += waitTime;
                        if(waitTime >= maxWaitS){
                            maxWaitS = waitTime;
                        }
                        registersS[j].cust.serviceTime += i;
                        registersS[j].isInUse = true;
                        outfile1<<"Customer "<<(registersS[j].cust.customerNumber)<<" served by "<<(j+1)<<
                        " starting at "<<(i)<<"\n";
                    }
                }
            }
            // Multi Queue Simulation
            if(registersM[j].isInUse){
                if(i == (registersM[j].cust.serviceTime)){ // Service is complete, remove from register
                    outfile2<<"Customer "<<registersM[j].cust.customerNumber<<" departed at "<<(i)<<"\n";
                    registersM[j].cust = CustomerData();
                    registersM[j].isInUse = false;
                    if(multQ[j]->isEmpty() == false){
                        registersM[j].cust = multQ[j]->dequeue();
                        int waitTime = i - registersM[j].cust.arrivalTime;
                        avgWaitM += waitTime;
                        if(waitTime >= maxWaitM){
                            maxWaitM = waitTime;
                        }
                        registersM[j].cust.serviceTime += i;
                        registersM[j].isInUse = true;
                        outfile2<<"Customer "<<(registersM[j].cust.customerNumber)<<" served by "<<(j+1)<<
                        " starting at "<<(i)<<"\n";
                    }
                }
            }
        }
        // Check if the next customer has arrived, if so then create a new arrival
        // time and create a new customer with parameters custAmount, arrivalTime,
        // and servTime;
        if((i - nextCustArr) == 0){
            custAmount++;
            int newService = rand() % maxService + 1;
            CustomerData newCustomerS(custAmount, i, newService);
            CustomerData newCustomerM(custAmount, i, newService);
            nextCustArr = (rand() % maxBetween + 1) + i;
            outfile1<<"Customer "<<custAmount<<" arrived at "<<i<<"\n";
            outfile2<<"Customer "<<custAmount<<" arrived at "<<i<<"\n";
            bool cust1Helped = false;
            bool cust2Helped = false;
            // Loop through registers
            for(int k = 0; k < 3; k++){
                // Single Queue check
                if(!registersS[k].isInUse && cust1Helped == false){
                    registersS[k].cust = newCustomerS;
                    registersS[k].cust.serviceTime += i;
                    registersS[k].isInUse = true;
                    cust1Helped = true;
                    outfile1<<"Customer "<<registersS[k].cust.customerNumber<<" served by "<<k+1<<" starting at "<<i<<"\n";
                }
                if(k == 2 && cust1Helped == false){
                    q1->enqueue(newCustomerS);
                    int qSize = q1->getSize();
                    if(qSize > maxLineLS){
                        maxLineLS = qSize;
                    }
                }
                // Multi Queue check
                if(!registersM[k].isInUse && cust2Helped == false){
                    registersM[k].cust = newCustomerM;
                    registersM[k].cust.serviceTime += i;
                    registersM[k].isInUse = true;
                    cust2Helped = true;
                    outfile2<<"Customer "<<registersM[k].cust.customerNumber<<" served by "<<k+1<<" starting at "<<i<<"\n";
                }
                if(k == 2 && cust2Helped == false){
                    int shortest = 0;
                    for(int f = 1; f < 3; f++){
                        if(multQ[f]->getSize() < multQ[shortest]->getSize()){
                            shortest = f;
                        }
                    }
                    multQ[shortest]->enqueue(newCustomerM);
                    int totalSize = 0;
                    for(int x = 0; x < 3; x++){
                        totalSize += multQ[x]->getSize();
                    }
                    if(totalSize > maxLineLM){
                        maxLineLM = totalSize;
                    }
                }
            }
        }

    }

    outfile1<<"\n";
    outfile1<<"Average wait time: "<<std::setprecision(1)<<std::fixed<<(avgWaitS / custAmount)<<"\n";
    outfile1<<"Maximum wait time: "<<maxWaitS<<"\n";
    outfile1<<"Maximum line length: "<<maxLineLS<<"\n";

    outfile2<<"\n";
    outfile2<<"Average wait time: "<<std::setprecision(1)<<std::fixed<<(avgWaitM / custAmount)<<"\n";
    outfile2<<"Maximum wait time: "<<maxWaitM<<"\n";
    outfile2<<"Maximum line length: "<<maxLineLM<<"\n";

    outfile1.close();
    outfile2.close();
    
    // Clear our memory
    delete q1;
    for(Queue *q : multQ){
        delete q;
    }
    
    return 0;
}