def banker(available, maximum, allocation):
n = len(allocation)
need = [[maximum[i][j] - allocation[i][j]
for j in range(len(available))] for i in range(n)]
work = available.copy()
finish = [False] * n
safe = []
while len(safe) < n:
 found = False
 for i in range(n):
 if not finish[i] and all(need[i][j] <= work[j]
 for j in range(len(work))):
 for j in range(len(work)):
 work[j] += allocation[i][j]
 finish[i] = True
 safe.append(i)
 found = True
 if not found:
 break
if len(safe) == n:
 print("Safe State")
 print("Safe Sequence:", [f"P{i}" for i in safe])
else:
 print("Unsafe State")
available = [3, 3, 2]
maximum = [
[7, 5, 3],
[3, 2, 2],
[9, 0, 2],
[2, 2, 2],
[4, 3, 3]
]
allocation = [
[0, 1, 0],
[2, 0, 0],
[3, 0, 2],
[2, 1, 1],
[0, 0, 2]
]
banker(available, maximum, allocation)