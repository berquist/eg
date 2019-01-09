from functools import partial

from graphviz import Digraph


g = Digraph("test_edgewidths")

g.edge("1", "10", penwidth="1")
g.edge("1", "11", penwidth="1.1")
g.edge("1", "12", penwidth="1.2")
g.edge("1", "13", penwidth="1.3")
g.edge("1", "14", penwidth="1.4")
g.edge("1", "15", penwidth="1.5")
g.edge("1", "16", penwidth="1.6")
# g.edge("2", "10")
# g.edge("2", "11")
# g.edge("2", "12")
# g.edge("2", "13")
# g.edge("2", "14")
# g.edge("2", "15")
# g.edge("2", "16")
edges = [
    ("2", "10"),
    ("2", "11"),
    ("2", "12"),
    ("2", "13"),
    ("2", "14"),
    ("2", "15"),
    ("2", "16"),
]

for l_from, l_to in edges:
    penwidth = f"{2 * float(l_to) % 10:.3f}"
    g.edge(l_from, l_to, penwidth=penwidth)


_min = 0.05
_max = 2.15

# - Every weight smaller than 0.0 should be assigned _min
# - For weights between 0.0 and the largest, map a linear interpolation from 0.0 to _max to between _min and _max

edges = [
    ("3", "A", -3),
    ("3", "B", -2),
    ("3", "C", -1),
    ("3", "D", 0),
    ("3", "E", 1),
    ("3", "F", 2),
    ("3", "G", 3),
    ("3", "H", 4),
    ("3", "I", 5),
]

max_weight = max([edge[2] for edge in edges])

def _interp(x1, x2, y1, y2, xx):
    yy = ((xx - x1) * (y2 - y1) / (x2 - x1)) + y1
    return yy

interp = partial(_interp, 0.0, max_weight, _min, _max)

def penwidth(weight):
    if weight <= 0.0:
        return _min
    else:
        return interp(weight)


for l_from, l_to, weight in edges:
    if weight <= 0.0:
        g.edge(l_from, l_to, str(weight), penwidth=str(_min))
    else:
        # penwidth = _interp(0.0, max_weight, _min, _max, weight)
        penwidth = interp(weight)
        g.edge(l_from, l_to, str(weight), penwidth=f"{penwidth:.3f}")
        

print(g.source)
g.render(format="pdf")
