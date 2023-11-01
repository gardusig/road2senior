from typing import Dict


def get_farthest_tree(
    trees: Dict[int, int],
    get_tree_order,
    get_next_position,
    farthest_tree_cmp
) -> Dict[int, int]:
    farthest_tree = {}
    for P in get_tree_order(trees.keys()):
        if P not in farthest_tree:
            farthest_tree[P] = P
        H = trees[P]
        nxt = get_next_position(P, H)
        if nxt not in farthest_tree:
            farthest_tree[nxt] = nxt
        farthest_tree[nxt] = farthest_tree_cmp(
            farthest_tree[nxt],
            farthest_tree[P]
        )
    return farthest_tree


def solve(trees: Dict[int, int]) -> int:
    farthest_tree_l = get_farthest_tree(
        trees=trees,
        get_tree_order=lambda keys: sorted(keys),
        get_next_position=lambda x, y: x + y,
        farthest_tree_cmp=min,
    )
    farthest_tree_r = get_farthest_tree(
        trees=trees,
        get_tree_order=lambda keys: reversed(sorted(keys)),
        get_next_position=lambda x, y: x - y,
        farthest_tree_cmp=max,
    )
    ans = 0
    for idx, L in farthest_tree_l.items():
        ans = max(ans, idx - L)
        if idx in farthest_tree_r:
            ans = max(ans, farthest_tree_r[idx] - L)
    for idx, R in farthest_tree_r.items():
        ans = max(ans, R - idx)
        if idx in farthest_tree_l:
            ans = max(ans, R - farthest_tree_l[idx])
    return ans


def run_test(test_id: int) -> None:
    N = int(input())
    trees = {}
    for _ in range(N):
        P, H = list(map(int, input().split()))
        if P in trees:
            raise Exception('unexpected input')
        trees[P] = H
    ans = solve(trees)
    print(f'Case #{test_id}: {ans}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
