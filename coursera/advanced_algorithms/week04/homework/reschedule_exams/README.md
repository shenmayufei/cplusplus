# Reschedule Exams

## Issue one

```{text}
Failed case #7/46: time limit exceeded (Time used: 1.99/1.00, memory used: 21811200/536870912.)
```

Solution: Add a propagation step to optimize the performance.   Propagate the change to all neighboring nodes if one node is colored.

## Issue two

code version: e92171ca93cfc9d7352cd1a2fca10a016457684a

```{text}
Failed case #45/46: Wrong answer (Time used: 0.00/1.00, memory used: 10706944/536870912.)
```

Solution: check if two nodes connected by one edge are the same node, if is return "";

