def sum(var, start, end, expr):
    expr = expr.replace('^', '**')
    result = 0
    for i in range(int(start), int(end)+1):
        result += eval(expr.replace(var, '(' + str(i) + ')'))
    return result

def product(var, start, end, expr):
    expr = expr.replace('^', '**')
    result = 1
    for i in range(int(start), int(end)+1):
        result *= eval(expr.replace(var, '(' + str(i) + ')'))
    return result

while True:
    x = input('>>> ').split()
    if x[0] == 'sum':
        print(sum(x[1], x[2], x[3], x[4]))
    elif x[0] == 'prod':
        print(product(x[1], x[2], x[3], x[4]))
    else:
        print('Unknown')

"""
>>> prod i 1 10 i
3628800
>>> sum k 6 13 k^2
764
>>> sum k 1 5 6*k+k^2
145
>>> sum i 3 9 8
56
>>> sum i 6 13 i^2+5
804
>>> sum i -3 4 i
4
>>> prod k 1 5 5*k
375000
>>> prod i 10 20 3
177147
>>> prod i 1 3 (i+1)^i
1152
>>> prod j -2 2 j^2
0
>>> prod j -8 -2 j+1
-5040
>>> prod j -8 -2 j
-40320
"""
