from typing import Dict


def get_frequency(s: str) -> Dict[chr, int]:
    f = {}
    for c in s:
        if c not in f:
            f[c] = 0
        f[c] += 1
    return f


def solve(s: str) -> bool:
    if s == 1:
        return True
    f = get_frequency(s)
    if len(f) != 2:
        return False
    x, y = f.keys()
    diff = abs(f[x] - f[y])
    if diff != 1:
        return False
    return True


def run_test(test_id: int) -> None:
    N = int(input())
    s = input()
    ans = solve(s)
    print(f'Case #{test_id}: {("N", "Y")[ans]}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
