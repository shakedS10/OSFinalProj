#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;


typedef void (*taskFunc)(int id);

class LF;
void run(LF* lf, int id);
int num = 0;
class LF{
	private:
	    int numThreads;
		int leader;
	    mutex mtx;
		vector<thread> followers;
		queue<taskFunc> tasks;
	public:
	    LF(int numThreads){
			this->numThreads = numThreads;
			this->leader = numThreads;
			
		}

		void add_followers(){
			for (int i = 0; i < this->numThreads; ++i) {
				followers.push_back(thread([this, i] {this->run(i);}));
			}
			for (auto& t : this->followers) {
                t.join();
            }
			cout << this->numThreads << endl;
		}

		void addTask(taskFunc task){
            this->tasks.push(task);
        }

		void proccessTask(taskFunc task, int id){
			this->mtx.lock();
            task(id);
            this->mtx.unlock();
		}

		void promoteLeader(int id){
			this->mtx.lock();
			this->leader = id;
			this->mtx.unlock();
		}
		bool isLeader(int id) {return this->leader == id;}
		bool hasLeader() {return this->leader == this->followers.size();}
		void removeLeader(){
			this->mtx.lock();
			this->leader = this->followers.size();
			this->mtx.unlock();
		}
		taskFunc getTask(){
			if (this->tasks.size() == 0) return nullptr;
			taskFunc task = this->tasks.front();
			this->tasks.pop();
			return task;
		}
		void run(int id){
			while (true) {
			if (!this->hasLeader()) this->promoteLeader(id);
			if (this->isLeader(id)){
				taskFunc task = this->getTask();
				if (task != NULL) this->proccessTask(task, num++);
				else return;
				this->removeLeader();
			}
		}
}

};

// void run(LF* lf, int id){
// 	while (true) {
//         if (!lf->hasLeader()) lf->promoteLeader(id);
// 		if (lf->isLeader(id)){
// 			taskFunc task = lf->getTask();
// 			if (task != NULL) lf->proccessTask(task, num++);
// 			else return;
// 			lf->removeLeader();
// 		}
//     }
// }