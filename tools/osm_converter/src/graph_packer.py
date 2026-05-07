import ctypes
import cppyy
from typing import Dict

class GraphPacker:
    """
    Handles the conversion of Pyrosm DataFrames into a binary C++ Graph.
    """
    
    # Scale factor to turn float Lat/Lon into int32 space
    COORD_SCALE = 1e7

    def __init__(self, max_nodes: int = 10000, max_edges: int = 20000):
        self.max_nodes = max_nodes
        self.max_edges = max_edges
        # Single source of truth for the Graph instance
        self.graph = cppyy.gbl.pathfind.Graph()
        self._osm_to_local: Dict[int, int] = {}

    def bake(self, nodes_df, edges_df, output_path: str):
        """Main entry point to transform and save the graph."""
        self._map_ids(nodes_df)
        self._populate_nodes(nodes_df)
        self._populate_edges(nodes_df, edges_df)
        self._serialize(output_path)

    def _map_ids(self, nodes_df):
        """Maps 64-bit OSM IDs to internal 0-indexed IDs."""
        if len(nodes_df) > self.max_nodes:
            raise ValueError(f"Too many nodes: {len(nodes_df)} exceeds {self.max_nodes}")
        self._osm_to_local = {osm_id: i for i, osm_id in enumerate(nodes_df['id'])}

    def _populate_nodes(self, nodes_df):
        """Fills the fixed-size C++ node array."""
        for i, row in nodes_df.iterrows():
            node = self.graph.nodes[i]
            node.x = int(row['lon'] * self.COORD_SCALE)
            node.y = int(row['lat'] * self.COORD_SCALE)
            node.first_edge_index = 0

    def _populate_edges(self, nodes_df, edges_df):
        """Fills the fixed-size C++ edge array using an adjacency list pattern."""
        edge_ptr = 1  # 0 is the null sentinel
        grouped = edges_df.groupby('u')

        for i, row in nodes_df.iterrows():
            osm_id = row['id']
            if osm_id not in grouped.groups:
                continue

            node_edges = grouped.get_group(osm_id)
            self.graph.nodes[i].first_edge_index = edge_ptr
            
            for j, (_, edge) in enumerate(node_edges.iterrows()):
                if edge_ptr >= self.max_edges:
                    raise IndexError(f"Edge limit {self.max_edges} exceeded.")
                
                target_local = self._osm_to_local.get(edge['v'])
                if target_local is None:
                    continue
                
                # Access the C++ struct directly via cppyy
                cpp_edge = self.graph.edges[edge_ptr]
                cpp_edge.target_node_id = target_local
                cpp_edge.cost = int(edge['length'])
                
                # Linking logic
                is_last = (j == len(node_edges) - 1)
                cpp_edge.next_edge_index = 0 if is_last else edge_ptr + 1
                
                edge_ptr += 1

    def _serialize(self, output_path: str):
        """Writes the raw memory of the C++ Graph object to disk."""
        addr = cppyy.addressof(self.graph)
        size = cppyy.sizeof(self.graph)
        
        # Cast the memory address to a ctypes buffer for writing
        buffer = (ctypes.c_char * size).from_address(addr)
        with open(output_path, "wb") as f:
            f.write(buffer)
        
        print(f"✅ Success: {size} bytes written to {output_path}")