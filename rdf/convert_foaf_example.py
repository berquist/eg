from pathlib import Path

from rdflib import Graph

__dir__ = Path(__file__).parent


if __name__ == "__main__":
    g = Graph()
    g.parse(__dir__ / "ontologies" / "foaf.owl")
    g.parse(__dir__ / "foaf_example.rdf")
    g.serialize("foaf_example_with_ontology.ttl", format="ttl")
    g.serialize("foaf_example_with_ontology.rdf", format="xml")
