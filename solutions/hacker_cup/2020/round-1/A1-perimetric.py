from typing import List
import heapq


MOD = 1000 * 1000 * 1000 + 7


class Width:
    def __init__(self, start_index: int):
        self.L = start_index
        self.R = start_index

    def join(self, R: int) -> None:
        self.R = max(self.R, R)

    def has_collision(self, L: int, R: int) -> None:
        return L <= self.R and R >= self.L

    def get(self) -> int:
        return (self.R - self.L) * 2


class Height:
    def __init__(self):
        self.remove_queue_index = 0
        self.remove_queue = []
        self.highest_queue = []
        heapq.heappush(self.highest_queue, 0)
        self.frequency = {
            0: 112345678912345
        }
        self.previous_peaks = 0

    def join(self, L: int, R: int, H: int) -> None:
        self.__remove_finished(L)
        self.remove_queue.append((R, H))
        previous_highest = self.__get_highest()
        if H not in self.frequency:
            self.frequency[H] = 0
        if self.frequency[H] == 0:
            heapq.heappush(self.highest_queue, -H)
        self.frequency[H] += 1
        if H > previous_highest:
            self.previous_peaks += H - previous_highest

    def get(self) -> int:
        return self.previous_peaks + self.__get_highest()

    def __remove_finished(self, start_index: int) -> None:
        while self.remove_queue_index < len(self.remove_queue):
            idx, H = self.remove_queue[self.remove_queue_index]
            if idx >= start_index:
                break
            self.frequency[H] -= 1
            self.remove_queue_index += 1
        previous_highest = self.__get_highest()
        while self.frequency[self.__get_highest()] < 1:
            heapq.heappop(self.highest_queue)
        self.previous_peaks += previous_highest - self.__get_highest()

    def __get_highest(self) -> int:
        return -self.highest_queue[0]


class Polygon:
    def __init__(self, L: int):
        self.width = Width(L)
        self.height = Height()

    def get_current_perimeter(self) -> None:
        width = self.width.get()
        height = self.height.get()
        return width + height


def solve(N: int, W: int, L: List[int], H: List[int]) -> int:
    polygons = []
    polygon = Polygon(L=L[0])
    ans = 1
    previous_perimeters = 0
    for i in range(N):
        if not polygon.width.has_collision(L[i], L[i] + W):
            previous_perimeters += polygon.get_current_perimeter()
            polygons.append(polygon)
            polygon = Polygon(L=L[i])
        polygon.width.join(L[i] + W)
        polygon.height.join(L[i], L[i] + W, H[i])
        perimeter = previous_perimeters + polygon.get_current_perimeter()
        ans = (ans * (perimeter % MOD)) % MOD
    return ans


def run_test(test_id: int) -> None:
    N, K, W = list(map(int, input().split()))
    L = list(map(int, input().split()))
    AL, BL, CL, DL = list(map(int, input().split()))
    for i in range(K, N):
        nxt_l = ((((AL * L[i - 2]) + (BL * L[i - 1]) + CL)) % DL) + 1
        L.append(nxt_l)
    H = list(map(int, input().split()))
    AH, BH, CH, DH = list(map(int, input().split()))
    for i in range(K, N):
        nxt_h = ((((AH * H[i - 2]) + (BH * H[i - 1]) + CH)) % DH) + 1
        H.append(nxt_h)
    ans = solve(N, W, L, H)
    print(f'Case #{test_id}: {ans}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
