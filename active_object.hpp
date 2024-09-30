#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <thread>
#include <queue>


using namespace std;

class ActiveObject;
typedef void (*taskFunc)(int id);

void run(ActiveObject* obj, int id);

class ActiveObject{
	private:
	    int id;
		thread task;
		queue<taskFunc> tasks;
		void run(int id){
			while (1){
				taskFunc func = this->getTask();
				if (func == nullptr) break;
				func(id);

			}
		}
	public:
	    ActiveObject(int id){
			this->id = id;
			
		}
		void join(){
			this->task.join();
		}
		void start(){
			int x = this->id;
			this->task = thread([this, x] {this->run(x);});
		}
		void request(taskFunc task){
			this->tasks.push(task);
		}

		taskFunc getTask(){
			if (this->tasks.size() == 0) return nullptr;
			taskFunc func = this->tasks.front();
			this->tasks.pop();
			return func;
		}



};

