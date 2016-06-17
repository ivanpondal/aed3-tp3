#include "ej3.h"
#include "../framework/structures/adj_list_graph.h"

using namespace std;

graph<int>* solver(graph<int>& g1, graph<int>& g2) {
	if (g2.n() >= g1.n()) {
		return &g1;
	}

	// Calculate cotree
	cotree_node* cotree = generate_cotree(g1);
	vector<info_cotree_node> vec_cotree = vectorize(cotree);

	// Calculate solution
	struct subsolution {
		int edge_count;
		vector<int> vertices;
	};

	vector<vector<subsolution>> dp(
		vec_cotree.size(),
		vector<subsolution>(g2.n() + 1)
	);

	for (uint i = 0; i < vec_cotree.size(); i++) {
		info_cotree_node current_info = vec_cotree[i];

		for (uint j = 0; j <= g2.n(); j++) {
			// si pido 0 nodos
			if (j == 0) {
				dp[i][j] = {0, vector<int>()};
			}
			else {
				// si es una hoja
				if (current_info.node->get_type() == leaf) {
					cotree_node_leaf* current_node =
						(cotree_node_leaf*) current_info.node;

					// si pido 1 nodo
					if (j == 1) {
						dp[i][j] = {0, {current_node->get_vertex()}};
					}
					else {
						dp[i][j] = {-1, vector<int>()};
					}
				}
				else {
					cotree_node_operation* current_node =
						(cotree_node_operation*) current_info.node;

					// si le pido más nodos de los que tiene el cotree
					if (j > current_node->get_vertex_count()) {
						dp[i][j] = {-1, vector<int>()};
					}
					// si pido exactamente la cantidad de nodos que tiene el cotree
					else if (j == current_node->get_vertex_count()) {
						uint left_vertex_count =
							current_node->get_left_child()->get_vertex_count();
						uint right_vertex_count =
							current_node->get_right_child()->get_vertex_count();

						subsolution left_subsolution =
							dp[current_info.left_child_index][left_vertex_count];
						subsolution right_subsolution =
							dp[current_info.right_child_index][right_vertex_count];

						int current_edge_count;
						if (current_node->get_operation() == join) {
							current_edge_count = left_subsolution.edge_count +
								right_subsolution.edge_count +
								left_vertex_count * right_vertex_count;
						}
						else {
							current_edge_count = left_subsolution.edge_count +
								right_subsolution.edge_count;
						}

						vector<int> current_vertices = left_subsolution.vertices;
						current_vertices.insert(
							current_vertices.end(),
							right_subsolution.vertices.begin(),
							right_subsolution.vertices.end()
						);
						dp[i][j] = {current_edge_count, current_vertices};
					}
					else {
						// pruebo combinando tomando de 1 a i y de i a 1 en
						// los hijos del co-tree
						int best_edge_count = -1;

						for (uint k = 0; k <= j; k++) {
							subsolution left_subsolution =
								dp[current_info.left_child_index][j - k];
							subsolution right_subsolution =
								dp[current_info.right_child_index][k];

							int current_edge_count;
							// si es un caso válido
							if (left_subsolution.edge_count != -1
								&& right_subsolution.edge_count != -1)
							{
								if (current_node->get_operation() == join) {
									current_edge_count =
										left_subsolution.edge_count +
										right_subsolution.edge_count +
										k * (j - k);
								}
								else {
									current_edge_count =
										left_subsolution.edge_count +
										right_subsolution.edge_count;
								}

								if (current_edge_count > best_edge_count) {
									best_edge_count = current_edge_count;
									vector<int> current_vertices =
										left_subsolution.vertices;
									current_vertices.insert(
										current_vertices.end(),
										right_subsolution.vertices.begin(),
										right_subsolution.vertices.end()
									);
									dp[i][j] =
										{current_edge_count, current_vertices};
								}
							}
						}
					}
				}
			}
		}
	}

	vector<int> solution_vertices = dp[vec_cotree.size() - 1][g2.n()].vertices;
}
