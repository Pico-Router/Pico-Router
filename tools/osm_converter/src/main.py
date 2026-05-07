from pbf_parser import PbfParser
from graph_packer import GraphPacker

def main():
    osm = PbfParser()
    packer = GraphPacker()

    nodes, edges = osm.parse()
    packer.pack(nodes, edges)

if __name__ == "__main__":
    main()