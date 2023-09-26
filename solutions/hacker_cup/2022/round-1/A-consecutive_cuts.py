from typing import Any, List


def get_kmp_table(values: List[Any]) -> List[int]:
    kmp = [0 for _ in range(len(values))]
    kmp[0] = 0
    last_equal_idx = 0
    for i in range(1, len(values)):
        while last_equal_idx > 0 and values[i] != values[last_equal_idx]:
            last_equal_idx = kmp[last_equal_idx-1]
        if values[i] == values[last_equal_idx]:
            last_equal_idx += 1
        kmp[i] = last_equal_idx
    return kmp


def get_first_match(N: int, source: List[Any], goal: List[Any], kmp_table: List[int]) -> int:
    goal_idx = 0
    for source_idx in range(len(source)):
        while goal_idx > 0 and source[source_idx] != goal[goal_idx]:
            goal_idx = kmp_table[goal_idx - 1]
        if source[source_idx] == goal[goal_idx]:
            goal_idx += 1
            if goal_idx == N:
                return source_idx - N + 1
    return None


def is_possible(N: int, K: int, first_match: int, goal: List[Any]) -> bool:
    if first_match == None:
        return False
    if K == 0:
        return first_match == 0
    if goal == [goal[0]] * N:
        return True
    if K == 1:
        return first_match > 0
    if N == 2:
        return (first_match > 0) == (K & 1)
    return True


def solve(N: int, K: int, source: List[Any], goal: List[Any]) -> None:
    kmp_table = get_kmp_table(goal)
    first_match = get_first_match(N, source + source, goal, kmp_table)
    return is_possible(N, K, first_match, goal)


def run_test(test_id: int) -> None:
    N, K = list(map(int, input().split()))
    source = list(map(int, input().split()))
    goal = list(map(int, input().split()))
    ans = 'YES' if solve(N, K, source, goal) else 'NO'
    print(f'Case #{test_id}: {ans}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
