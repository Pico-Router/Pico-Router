from pyrosm import OSM
from config_loader import ConfigLoader

class PbfParser:
    """
    Handles the extraction of essential map geometries from protobuf file.
    """
    def __init__(self, config_name="config.json"):
        config = ConfigLoader.load_config(config_name)
        self.pbf_path = config["osm_pbf_path"]
    
    def parse(self):
        osm = OSM(self.pbf_path)
        nodes, edges = osm.get_network(network_type="driving", nodes=True)
        
        return nodes, edges
