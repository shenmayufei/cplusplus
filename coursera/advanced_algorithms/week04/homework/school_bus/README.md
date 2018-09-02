# School Bus

Use dynamic programming to solve the issue.

## Issue one

```{text}
Failed case #31/40: time limit exceeded (Time used: 1.09/1.00, memory used: 30752768/536870912.)
```

Solution: use `unordered_map` instead of `map`. Side effect: use a `int` as key, instead of a pair. Need a hash func
