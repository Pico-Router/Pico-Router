import argparse
from pbf_parser import PbfParser
from graph_packer import GraphPacker

def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("--config", default="config.json", help="path to config.json file")
    
    return parser.parse_args()

    

def main():
    args = parse_arguments()

    osm = PbfParser(args.config)
    packer = GraphPacker(args.config)

    nodes, edges = osm.parse()
    packer.pack(nodes, edges)

if __name__ == "__main__":
    main()