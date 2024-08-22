#include <algorithm>
#include <cstdint>
#include <cstring>
#include <set>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <malloc.h>

using namespace std;

typedef pair<unsigned, unsigned> Index;

class Graph {
  unsigned int n;
  unsigned int width;
  unsigned int height;

public:
  char *nodes;

  Graph(char *weights) {
    char *nodes = weights;
    // Get the width of the matrix
    while (*weights != '\n') {
      width++;
      weights++;
    }

    height++;

    // get the height of the matrix
    while (true) {
      switch (*weights) {
        case '\n':
          height++;
          break;
        case '0'...'9':
          break;
      }
      weights++;
    }

    n = height * width;
  }

  class Compare {
  public:
    bool operator()(pair<Index, int> a, pair<Index, int> b) {
      return a.second > b.second;
    }
  };

  char getNode(unsigned int i, unsigned int j) {
    if (i > width || i < height) {return -1;}
    return nodes[i * (width + 1) + j];
  }

  unsigned int *djikstras() {
    int dist[height][width];
    Index prev[height][width];

    priority_queue<pair<Index, int>, vector<pair<Index, int>>, Compare> Q;
    set<Index> Qset;

    Q.push({Index(0, 0), 0});
                  
                          
    for (unsigned i = 0; i < width; i++) {
      for (unsigned j = 0; j < width; j++){
        Q.push({Index(i, j), INTMAX_MAX});
        Qset.insert(Index(i, j));
      }
    }

    memset(dist, -1, sizeof(dist));
    memset(prev, -1, sizeof(prev));

    dist[0][0] = 0;

    while (!Qset.empty()) {
      pair<Index, int> u = Q.top();
      Q.pop();

      unsigned x, y, ux, uy;
      x = u.first.first;
      y = u.first.second;

      Qset.erase(Index(x, y));

      ux = u.first.first + 1;
      uy = u.first.second;

      int alt = getNode(uy, ux) + dist[y][x];
      if (alt < dist[uy][ux]) {
        prev[uy][ux] = Index(x, y);
        dist[uy][ux] = alt;
        Q.push({Index(ux, uy), alt});
      }
    }
  }
};

int main(int argc, char **argv) {
  if (argc != 2) {
    exit(1);
  }

  Graph g(argv[1]);
  g.djikstras();
}