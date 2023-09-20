# Problem statement

Given an array ("stocks") with stock price on each day, consider $[L, R]$ as all the elements from $stocks[L]$ to $stocks[R]$. Count how many intervals satisfy any of these conditions:

- $stocks[L]$ is the greatest in the interval
- $stocks[R]$ is the greatest in the interval

All of these are **valid**:

- `[1]`
- `[1, 2, 3, 4]`
- `[1, 2, 2]`
- `[2, 2, 2]`
- `[4, 2, 3, 2, 4]`
- `[3, 2, 2]`

All of these are **in**valid:

- `[1, 2, 2, 1]`
- `[1, 2, 1]`
- `[1, 2, 3, 2]`

## Constraints:

- $1 <= N <= 5*10^5$
- $1 <= stocks[i] <= 10^9$
