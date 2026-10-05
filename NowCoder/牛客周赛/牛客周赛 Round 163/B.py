from ihxnan import *

a, b = I().split()

a = int(a, 16)
b = int(b)

print("YES" if a % int(2**b) == 0 else "NO")
