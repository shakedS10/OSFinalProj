#include "reactor.hpp"

using namespace std;

Reactor::Reactor(int listener, reactorFunc func) {
	this->listener = listener;
	this->addFdToReactor(listener, func);
	
	
}

void Reactor::run(){
	for(;;) {
        cout << "waiting for command" << endl;
        int poll_count = this->new_poll();

        if (poll_count == -1) {
            cerr << "poll";
            return;
        }

        // Run through the existing connections looking for data to read
        for(int i = 0; i < this->size(); i++) {

            // Check if someone's ready to read
            if (this->readyToRead(i)) { // We got one!!
				cout << i << this->funcs.size() << this->pfds.size() << endl;
                this->call_func(i);
            } // END got ready-to-read from poll()
        } // END looping through file descriptors
    } 
}

void Reactor::addFdToReactor(int fd, reactorFunc func){
	struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    this->pfds.push_back(pfd);
	this->funcs.push_back(func);

}
void Reactor::removeFdFromReactor(int fd){
	int i = 0;
	for (; i < this->pfds.size(); i++){
		if (this->pfds[i].fd == fd) break;
	}
	this->pfds.erase(this->pfds.begin() + i);
	this->funcs.erase(this->funcs.begin() + i);
}

bool Reactor::readyToRead(int index){
	return (this->pfds[index].revents & POLLIN);
}

void Reactor::call_func(int index){
	this->funcs[index](this->pfds[index].fd);
}

int Reactor::get_listener(){
	return this->listener;
}

int Reactor::size(){
	return this->pfds.size();
}

int Reactor::get_fd(int index){
	return this->pfds[index].fd;
}

int Reactor::new_poll(){
	return poll(this->pfds.data(), this->pfds.size(), -1);
}
