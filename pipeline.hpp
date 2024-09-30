#include "active_object.hpp"

typedef void (*taskFunc)(int id);

class PipeLine{
public:
    vector<ActiveObject> pipes;
	int n;
	PipeLine(int n){
		this->n = n;
		for (int i = 0; i < n; i++){
			this->pipes.push_back(ActiveObject(i));
		}
	}

	void start(taskFunc func){
		for (int i = 0; i < this->n; i++){
			this->pipes[i].request(func);
			this->pipes[i].start();
		}
	}

	void join(){
        for (int i = 0; i < this->n; i++){
            this->pipes[i].join();
        }
    }
};