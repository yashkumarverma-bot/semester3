/**
 * @author YashKumarVerma / 19BCE2669
 * @for: Lab Digital Assignment 2
 * @description: Implementation of Dining Philosophers Problem using Monitors
 */

#include<iostream>
#include<vector>

using namespace std;

/** Utility function to format display as requireds **/
class console{
    public: 
    static void log(string status, string message){
        cout << "[" << status << "] :: " << message << endl;
    }

    static void log(string status, int message){
        cout << "[" << status << "] :: " << message << endl;        
    }
};


class Philosopher {
    public:
        bool left;
        bool right;
        bool takenDinner;

    Philosopher(bool left = false, bool right = false){
        this->left = left;
        this->right = right;
        this->takenDinner = false;    
    }

    bool justTakenTwoForks(){
        return this->left && this->right;
    }

    bool hasLeftAndWantsRight(){
        return this->left && !this->right;
    }

    bool hasNoForks(){
        return !this->left && !this->right;
    }
};

/** 
 * @class Fork
 * @description To handle all operating related to fork / chopstick
 **/

class Fork {
    private:
        bool taken;
    public:
    Fork(bool taken = false){
        this->taken = taken;
    }
    
    bool isTaken(){
        return this->taken;
    }
    
    void take(){
        this->taken = true;
    }

    void release(){
        this->taken = false;
    }
};

/** 
 * @class DiningPhilosophers
 * @description To handle all operating related to problem
 **/
class DiningPhilosophers{
    private:
        vector<Philosopher> philosopher;
        vector<Fork> fork;

    public:
        int completedPhilosophers;
        int totalPhilosophers;
    
    /** set initial conditions **/
    DiningPhilosophers(int totalPhilosophers = 5){
        this->completedPhilosophers = 0;
        this->totalPhilosophers = totalPhilosophers;

        for(int i=0; i<this->totalPhilosophers; i++){
            this->philosopher.push_back(Philosopher());
            this->fork.push_back(Fork());
        }   
    }

    /** start dinner by philosophers **/
    void startDinner(){
        console::log("starting", "meal");
        while(this->completedPhilosophers < this->totalPhilosophers){
            console::log("totalPhilosophers", this->totalPhilosophers);     
            console::log("completedPhilosophers", this->completedPhilosophers);

            for(int philosopherId=0; philosopherId< this->totalPhilosophers; philosopherId += 1){
                console::log("starting dinner", philosopherId);
                this->attemptToEat(philosopherId);
            }     
        }
        console::log("completing", "meal");
    }

    /** make attempts to eat **/
    void attemptToEat(int philosopherId){
        /** if dinner already taken **/
        if(this->philosopher[philosopherId].takenDinner){
            console::log("taken dinner", philosopherId);
        }

        /** then the philosopher can take dinner **/
        else if(this->philosopher[philosopherId].justTakenTwoForks()){
            console::log("taken dinner", philosopherId);
            this->philosopher[philosopherId].takenDinner = true;
        
            int otherFork = philosopherId - 1;
            if(otherFork == -1){
                otherFork = this->totalPhilosophers - 1;
            }

            /** releasing forks */
            this->fork[philosopherId].release();
            this->fork[otherFork].release();

            console::log("philosopher", philosopherId );
            console::log("released fork", philosopherId );
            console::log("released fork", otherFork );

            this->completedPhilosophers += 1;
        }

        else if(this->philosopher[philosopherId].hasLeftAndWantsRight()){
            if(philosopherId == (this->totalPhilosophers - 1)){
                if(!this->fork[philosopherId].isTaken()){
                    this->fork[philosopherId].take();
                    this->philosopher[philosopherId].right = true;
                    console::log("philosopher",philosopherId );
                    console::log("picks fork", philosopherId );
                }
                else{
                    console::log("philosopher",philosopherId );
                    console::log("waiting for fork", philosopherId );
                }
            }
            /** case of last philosopher **/
            else {
                int duplicatePhilosopherId = philosopherId;
                philosopherId -= 1;

                if(philosopherId == -1){
                    philosopherId = this->totalPhilosophers - 1;
                }

                if(!this->fork[philosopherId].isTaken()){
                    this->fork[philosopherId].take();
                    this->philosopher[duplicatePhilosopherId].right = true;
                    console::log("philosopher",philosopherId );
                    console::log("picks fork", duplicatePhilosopherId );
                }
                else{
                    console::log("philosopher",duplicatePhilosopherId );
                    console::log("waiting for fork", philosopherId );
                }
            }
        }
        else if(this->philosopher[philosopherId].hasNoForks()){
            if(philosopherId == this->totalPhilosophers - 1){
                if(!this->fork[philosopherId-1].isTaken()){
                    this->fork[philosopherId-1].take();
                    this->philosopher[philosopherId].left = true;
                    console::log("philosopher",philosopherId );
                    console::log("picks fork", philosopherId-1);
                }
                else {
                    console::log("philosopher",philosopherId );
                    console::log("waiting for fork", philosopherId-1);
                }
            }
            /** case of last philosopher **/
            else {
                if(!this->fork[philosopherId].isTaken()){
                    this->fork[philosopherId].take();
                    this->philosopher[philosopherId].left = true;
                    console::log("philosopher",philosopherId );
                    console::log("picks fork", philosopherId);
                }
                else{
                    console::log("philosopher",philosopherId );
                    console::log("waiting for fork", philosopherId);
                }
            }
        }
    }
};

/** Driver code **/
int main(){
    DiningPhilosophers diningPhilosophers = DiningPhilosophers(5);
    diningPhilosophers.startDinner();
}