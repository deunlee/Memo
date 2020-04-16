from z3 import *

sol = Solver()


p = Bool('p')
q = Bool('q')
r = Bool('r')
s = Bool('s')
t = Bool('t')

a = Implies(p, And([q, Not(r)]))
b = Or([Not(q), Not(r)])
c = Implies(Or([p, r]), s)
d = And([t, Not(s)])
e = Implies(Not(t), Or([p, q]))

sol.add(a)
sol.add(b)
sol.add(c)
sol.add(d)
sol.add(e)

print(sol.check())
# sat(satisfiable) = 가능
# unsat = 불가능

model = sol.model()
print(model)

# https://ericpony.github.io/z3py-tutorial/guide-examples.htm
