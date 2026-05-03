#include <stdio.h>
#include <string.h>

#define CITIES 8

int getIndex(const char *cities[CITIES], char city[64]) {
  for (int i = 0; i < CITIES; i++) {
    if (strcmp(cities[i], city) == 0)
      return i;
  }
  return -1;
}

int findShortestPath(int graph[CITIES][CITIES]) {

  int best = 1000000;

  for (int start = 0; start < CITIES; start++) {

    int visited[CITIES] = {0};
    int current = start;
    visited[current] = 1;

    int total = 0;

    for (int step = 0; step < CITIES - 1; step++) {

      int bestCity = -1;
      int bestDist = 1000000;

      for (int j = 0; j < CITIES; j++) {
        if (!visited[j] && graph[current][j] < bestDist) {
          bestDist = graph[current][j];
          bestCity = j;
        }
      }

      if (bestCity == -1)
        break;

      visited[bestCity] = 1;
      total += bestDist;
      current = bestCity;
    }

    if (total < best)
      best = total;
  }

  return best;
}

int findLongestPath(int graph[CITIES][CITIES]) {

  int worst = 0;

  for (int start = 0; start < CITIES; start++) {

    int visited[CITIES] = {0};
    int current = start;
    visited[current] = 1;

    int total = 0;

    for (int step = 0; step < CITIES - 1; step++) {

      int nextCity = -1;
      int maxDist = -1;

      for (int j = 0; j < CITIES; j++) {
        if (!visited[j] && graph[current][j] > maxDist) {
          maxDist = graph[current][j];
          nextCity = j;
        }
      }

      if (nextCity == -1)
        break; // bezpieczeństwo
      visited[nextCity] = 1;
      total += maxDist;
      current = nextCity;
    }

    if (total > worst)
      worst = total;
  }

  return worst;
}
int main() {
  const char *cities[CITIES] = {"Tristram", "AlphaCentauri", "Snowdin",    "Tambi",
                                "Faerun",   "Norrath",       "Straylight", "Arbre"};

  // const char *cities[CITIES] = {"London", "Dublin", "Belfast"};
  int graph[CITIES][CITIES] = {0};

  FILE *file = fopen("in.txt", "r");
  char line[256];

  char city1[64], city2[64];
  int dist = 0;

  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%s %*s %s %*s %i", city1, city2, &dist);
    int index1 = getIndex(cities, city1);
    int index2 = getIndex(cities, city2);
    printf("index1: %i, index2: %i\n", index1, index2);

    if (index1 != -1 && index2 != -1) {
      graph[index1][index2] = dist;
      graph[index2][index1] = dist;
    } else
      printf("ERROR: index -1, can't find city\n");
    printf("%s to %s = %i\n", city1, city2, dist);
  }

  int shortesPath = findShortestPath(graph);
  int lonegestPath = findLongestPath(graph);
  printf("Shortest: %i, longest: %i\n", shortesPath, lonegestPath);
}
