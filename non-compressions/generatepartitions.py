def partitions(n):
    # base case of recursion: zero is the sum of the empty list
    if n == 0:
        yield []
        return
        
    # modify partitions of n-1 to form partitions of n
    for p in partitions(n-1):
        yield [1] + p
        if p and (len(p) < 2 or p[1] > p[0]):
            yield [p[0] + 1] + p[1:]


alphabet = [-3, -1, 1, 3]

parts = list(partitions(6))
print(parts)

for part in parts:
    if len(part) != 30:
        parts.remove(part)

for part in parts:
    for num in part:
        if num not in alphabet:
            parts.remove(part)
            break

print(parts)