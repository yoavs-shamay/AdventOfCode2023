import networkx as nx

file = open("in.txt", 'r')
parsed = []
graph = {}
for line in file:
    line = line[:-1]
    parts = line.split(': ')
    name = parts[0]
    p2 = parts[1].split(' ')
    for x in p2:
        if name not in graph:
            graph[name] = []
        graph[name].append(x)
        if x not in graph:
            graph[x] = []
        graph[x].append(x)
file.close()
G = nx.Graph()
for x in graph.keys():
    G.add_node(x)
for a,b in graph.items():
    for c in b:
        G.add_edge(a, c)
res = nx.k_edge_components(G,k=4)
res = sorted(map(sorted, res))
print(len(res), len(res[0])*len(res[1]))