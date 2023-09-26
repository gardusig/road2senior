from typing import List


def contains_tree(rows: int, columns: int, canvas: List[str]) -> bool:
    for row in range(rows):
        for column in range(columns):
            if canvas[row][column] == '^':
                return True
    return False


def is_canvas_possible(rows: int, columns: int, canvas: List[str]) -> bool:
    if min(rows, columns) == 1:
        return not contains_tree(rows, columns, canvas)
    return True


def run_test(test_id: int) -> None:
    rows, columns = list(map(int, input().split()))
    canvas = ['' for _ in range(rows)]
    for row in range(rows):
        canvas[row] = input()
    possible = is_canvas_possible(rows, columns, canvas)
    if not possible:
        print(f'Case #{test_id}: Impossible')
        return
    print(f'Case #{test_id}: Possible')
    if contains_tree(rows, columns, canvas):
        for row in range(rows):
            canvas[row] = '^' * columns
    for row in range(rows):
        for column in range(columns):
            print(canvas[row][column], end='')
        print()


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
