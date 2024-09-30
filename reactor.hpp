#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>

#include <poll.h>

//#include "listener.hpp"


using namespace std;

class Reactor;
typedef void (*reactorFunc)(int fd);

class Reactor{
	private:
		int listener;
		vector<struct pollfd> pfds;
		vector<reactorFunc> funcs;
	public:
	    Reactor(int listener, reactorFunc func);

		void addFdToReactor(int fd, reactorFunc func);
		void removeFdFromReactor(int fd);

		bool readyToRead(int index);

		void call_func(int index);
		int get_listener();
		int size();

		int get_fd(int index);

		int new_poll();
		void run();
};
