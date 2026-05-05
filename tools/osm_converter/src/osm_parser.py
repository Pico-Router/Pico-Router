from pyrosm import OSM

pbf_file = "tools/osm_converter/src/assets/sample_map.osm.pbf"

osm = OSM(pbf_file)

roads = osm.get_network(network_type="driving")

print(roads.head())