import json
from pyrosm import OSM

class PbfParser:
    """
    Handles the extraction of essential map geometries from protobuf file.
    """
    def __init__(self, config_path="/workspaces/pico-router/config.json"):
        with open(config_path, 'r') as f:
            config = json.load(f)
        
        self.pbf_path = config["osm_pbf_path"]
    
    def parse(self):
        """Main entry point parse protobut file into GeoPandas dataframe"""
        osm = OSM(self.pbf_path)
        nodes, edges = osm.get_network(network_type="driving", nodes=True)
        
        return nodes, edges
