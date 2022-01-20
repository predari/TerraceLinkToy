#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <queue>
#include "sys/time.h"

// includes for terrace
#include <graph.h>
#include <parallel.h>
#include <util.h>
#include <io_util.h>
#include <parse_command_line.h>


using namespace graphstore;


void run_algorithm(commandLine& P) {
  auto test_id = P.getOptionValue("-t", "BFS");
  size_t rounds = P.getOptionLongValue("-rounds", 4);
  
  std::string src, dest;
  // read edges as source and destination
  struct timeval start, end;
  struct timezone tzp;
  
  // initialize graph
  uint32_t num_nodes;
  uint64_t num_edges;
  auto filename = P.getOptionValue("-f", "none");
  pair_uint *edges = get_edges_from_file_adj_sym(filename.c_str(), &num_edges, &num_nodes);
  
  Graph graph(num_nodes);

  std::vector<uint32_t> new_srcs(num_edges);
  std::vector<uint32_t> new_dests(num_edges);
  for (uint32_t i = 0; i < num_edges; i++) {
    new_srcs[i] = edges[i].x;
    new_dests[i] = edges[i].y;
  }
  auto perm = get_random_permutation(num_edges);
  
  PRINT("Inserting edges");	

  graph.add_edge_batch(new_srcs.data(), new_dests.data(), num_edges, perm);
  
  for(uint32_t i = 0; i < num_edges; i++) {
    if (!graph.is_edge(edges[i].x, edges[i].y)) {
      printf("edge (%u, %u) not found, should be\n", edges[i].x, edges[i].y);
      printf("\tdegree %u = %u\n", edges[i].x, graph.degree(edges[i].x));
    }
  }
  
  free(edges);
  new_srcs.clear();
  new_dests.clear();
	
  float size_gb = graph.get_size()/(float)1073741824;
  PRINT("Construction finished. Nodes: " << graph.get_num_vertices() <<
	" Edges: " << graph.get_num_edges() << " Size: " << size_gb << " GB");

}
 

/* 
 * ===  FUNCTION  =============================================================
 *         Name:  main
 *  Description:  
 * ============================================================================
 */
int main(int argc, char** argv) {
  srand(time(NULL));
  printf("Num workers: %ld\n", getWorkers());
  commandLine P(argc, argv, "./graph_bm [-t testname -r rounds -f file");
  run_algorithm(P);
}
