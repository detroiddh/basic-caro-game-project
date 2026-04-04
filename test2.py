def a(b):
    b.append(2)

def d(b):
    b += 1

c = [1,2,3]
e = 2
a(c)
d(e)
print(c)
print(e)