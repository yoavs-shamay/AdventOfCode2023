import sympy

file = open("in.txt", 'r')
parsed = []
for line in file:
    parts = line.split('@')
    p1 = parts[0].split(',')
    p2 = parts[1].split(',')
    cur = [[int(x) for x in p1], [int(x) for x in p2]]
    parsed.append(cur)
file.close()
x, y, z, vx, vy, vz = sympy.symbols("a, b, c, d, e, f", integer=True)
eqs = []
parts = {(-x * vy + vx * y): [], (-z * vy + vz * y): []}
for hail in parsed:
    x0 = hail[0][0]
    y0 = hail[0][1]
    z0 = hail[0][2]
    vx0 = hail[1][0]
    vy0 = hail[1][1]
    vz0 = hail[1][2]
    parts[-x * vy + vx * y].append(x * vy0 + x0 * vy - x0 * vy0 - vx0 * y - y0 * vx + vx0 * y0)
    parts[-z * vy + vz * y].append(z * vy0 + z0 * vy - z0 * vy0 - vz0 * y - y0 * vz + vz0 * y0)

for b in parts.values():
    for i in range(1, len(b)):
        eqs.append(sympy.Eq(b[i - 1], b[i]))
sol = sympy.solve(eqs,[x,y,z,vx,vy,vz])
print(sol[x]+sol[y]+sol[z])
