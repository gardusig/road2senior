from typing import List


def bfs(source: int, N: int, incoming: List[int], outgoing: List[int], ans: List[List[int]]) -> None:
    queue = [source]
    queue_idx = 0
    visited = set()
    visited.add(source)
    while queue_idx < len(queue):
        current = queue[queue_idx]
        queue_idx += 1
        edges = []
        if current - 1 >= 0:
            edges.append(current - 1)
        if current + 1 < N:
            edges.append(current + 1)
        for nxt in edges:
            if nxt not in visited and (outgoing[current] == 'Y' and incoming[nxt] == 'Y'):
                visited.add(nxt)
                queue.append(nxt)
    for i in visited:
        ans[source][i] = 'Y'


def solve(N: int, incoming: List[int], outgoing: List[int]) -> List[List[int]]:
    ans = []
    for i in range(N):
        ans.append(['N'] * N)
    for i in range(N):
        bfs(i, N, incoming, outgoing, ans)
    return ans


def run_test(test_id: int) -> None:
    N = int(input())
    incoming = input()
    outgoing = input()
    print(f'Case #{test_id}:')
    for i in solve(N, incoming, outgoing):
        print(''.join(i))


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
