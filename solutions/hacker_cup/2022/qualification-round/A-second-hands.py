from typing import List


def is_possible(N: int, K: int, parts: List[int]) -> bool:
    frequency = {}
    for part in parts:
        if part not in frequency:
            frequency[part] = 0
        frequency[part] += 1
    available = [K] * 2
    for value in frequency.values():
        if value > 2:
            return False
        for i in range(value):
            if available[i] < 1:
                return False
            available[i] -= 1
        if available[0] < available[1]:
            available[0], available[1] = available[1], available[0]
    return True


def run_test(test_id: int) -> None:
    N, K = list(map(int, input().split()))
    parts = list(map(int, input().split()))
    answer = 'YES' if is_possible(N, K, parts) else 'NO'
    print(f'Case #{test_id}: {answer}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
