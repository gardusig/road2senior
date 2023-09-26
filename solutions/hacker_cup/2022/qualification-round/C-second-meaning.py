alphabet = ['.', '-']


def get_converted_string(N: int) -> str:
    ans = ''
    for i in range(10, -1, -1):
        ans += alphabet[(N >> i) & 1]
    return ans


def is_candidate_valid(candidate: str, codeword: str) -> bool:
    if candidate.startswith(codeword) or candidate.endswith(codeword):
        return False
    return True


def run_test(test_id: int) -> None:
    N = int(input())
    codeword = input()
    raw_candidate = 1
    answer = []
    while len(answer) < N - 1:
        candidate = get_converted_string(raw_candidate)
        if is_candidate_valid(candidate, codeword):
            answer.append(candidate)
        raw_candidate += 1
    print(f'Case #{test_id}:')
    for i in answer:
        print(i)


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
