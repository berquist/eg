from pathlib import Path

from rdflib import Graph

__dir__ = Path(__file__).parent


if __name__ == "__main__":
    g = Graph()
    g.parse(__dir__ / "ontologies" / "22-rdf-syntax-ns.owl.ttl")
    g.serialize("22-rdf-syntax-ns-roundtrip.owl.ttl", format="ttl")
    g.serialize("22-rdf-syntax-ns-roundtrip.owl", format="xml")
