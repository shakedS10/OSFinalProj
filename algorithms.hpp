#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "graph.hpp"
#include "tree.hpp"


using namespace std;



Tree prim(Graph& graph);

Tree kruskal(Graph& graph);

void removeEdge(int a, int b, Graph &graph);

void newEdge(int a, int b, Graph &graph);

void newGraph(Graph &graph, int m, int n, int fd);