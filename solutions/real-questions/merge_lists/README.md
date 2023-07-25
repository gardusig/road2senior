# Problem statement

Given two sorted lists, where each node represent a starting index and finishing index, merge them into a new one.

## Example

```
L1: [1, 2] -> [3, 4] -> [5, 6] -> null
L2: [2, 3] -> [4, 5] -> [6, 7] -> null
result: [1, 7] -> null
```

```
L1: [1, 2] -> [3, 4] -> [5, 6] -> null
L2: [2, 3] -> null
result: [1, 4] -> [5, 6] -> null
```

```
L1: [1, 4] -> [7, 8] -> null
L2: [1, 3] -> [6, 9] -> null
result: [1, 4] -> [6, 9] -> null
```

```
L1: [1, 1] -> [2, 2] -> null
L2: [3, 3] -> [4, 4] -> null
result: [1, 1] -> [2, 2] -> [3, 3] -> [4, 4] -> null
```
