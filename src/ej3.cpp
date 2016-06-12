#include <graph.h>

using namespace std;


graph solver ( graph & g1 , graph & g2 ){
	if ( g2.n >= g1.n ){
		return g1;
	}
	// Calculate co tree
	vector<cotree_node> vec_co_tree; = cotree(g1);
	// Calculate solve

	vector< vector < pair<int,vector<int> > > > dp ;

	dp = vector< vector< pair < int, vector<int> > > >(g1->n,
		vector< pair < int, char > > ( vec_co_tree.size() ,
		make_pair (0,vector<int>)));

	for (int j = vec_co_tree.size() - 1; j > 0; ++i){
		for (int i = 0; i < g1->n; ++i){

			info_cotree_node info =  vec_co_tree[j];
			// si pido 0 nodes
			if (i == 0){
				dp[0][j] = make_pair(0,vector<int>);
			 
			} else{
				// si es una hoja
				if (info.nodo.get_type() == vertex ){
					// TO_DO: cast info.nodo (cotree_node) to cotree_node_vertex 
					//si  pido 1 node
					if (i == 1){
						dp[i][1] = make_pair(0,vector<int>(n->vertex));
					}else{
						dp[i][1] = make_pair(-1,vector<int>());
					}
				}else{
					// TO_DO: cast info.nodo (cotree_node) to cotree_node_operation 

					// si le pido más nodes de los q tiene co-tree
					if (i > info.nodo->ind_cograph_size){
						dp[i][j] = make_pair(-1,vector<int>());
					// si pido exactamete la cantidad de nodes tiene el co-tree
					}else if ( i == n->ind_cograph_size ){
						int k = n.get_left_child()->ind_cograph_edge_count;
						dp[i][j] = merge_nodes(dp,i,j,k,n);
					}else {
						// pruebo combinando tomando de 1 a j y de j  a 1 en los hijos del co-tree 
						for (int k = 1; k < j; ++k){
							// si es un caso valido
							if (dp[n->left_child][k].first != -1 && )dp[n->right_child][k].first != -1){
								pair<int,vector<int> new_merge = merge_nodes(dp,i,j,k,n);
								if(new_merge.first >= dp[i][j].first){
									dp[i][j] = new_merge;
									
								}
							}


						}
					}
				}

			} 
		}
		vector <int> vec_solve_nodes = dp[0][g1->n].second;
	}

	pair<int,vector<int> > merge_nodes( vector < vector < pair<int,vector<int> > > >  &dp 
												, int i, int j, int k, cotree_node &n  ){
		vector <int> nodes = dp[n->right_child][k];
		vector <int> other_nodes = dp[n->left_child][j - k];
		
		int edges = (nodes.size() + other_nodes.size());

		if (n->cotree_operation == join){
			edges +=  nodes.size() * other_nodes.size();
		}
		nodes.insert (nodes.end(),other_nodes.begin(),other_nodes.end());
		return make_pair(edges,nodes);


	}
}