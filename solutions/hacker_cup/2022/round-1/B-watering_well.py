from collections import defaultdict
from typing import Dict, List, Tuple


MOD = 1000 * 1000 * 1000 + 7


def solve(N: int, Q: int, tree_coordinate: List[Dict[int, int]], queries: List[Tuple[int, int]]) -> int:
    ans = 0
    tree_accum = [0] * 2
    for coordinate_idx in range(2):
        for tree_idx, qty in tree_coordinate[coordinate_idx].items():
            ans += Q * qty * tree_idx * tree_idx
            ans %= MOD
            tree_accum[coordinate_idx] += tree_idx * qty
            tree_accum[coordinate_idx] %= MOD
    for query_idx in range(Q):
        for coordinate_idx in range(2):
            query = queries[query_idx][coordinate_idx]
            ans += N * query * query
            ans -= 2 * tree_accum[coordinate_idx] * query
            ans %= MOD
    ans = (ans + MOD) % MOD
    return ans


def run_test(test_id: int) -> None:
    N = int(input())
    tree_coordinates = []
    for _ in range(2):
        tree_coordinates.append(defaultdict(lambda: 0))
    for _ in range(N):
        coordinates = list(map(int, input().split()))
        for idx in range(len(coordinates)):
            tree_coordinates[idx][coordinates[idx]] += 1
    Q = int(input())
    queries = []
    for _ in range(Q):
        queries.append(list(map(int, input().split())))
    ans = solve(N, Q, tree_coordinates, queries)
    print(f'Case #{test_id}: {ans}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
