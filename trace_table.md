# Trace Table – Logistics Package Sorting

## Input Data

| Package ID | Weight | Original Position |
|---|---:|---:|
| P1 | 20 | 1 |
| P2 | 15 | 2 |
| P3 | 20 | 3 |
| P4 | 10 | 4 |
| P5 | 15 | 5 |
| P6 | 20 | 6 |
| P7 | 25 | 7 |
| P8 | 10 | 8 |

---

## Merge Sort Trace

| Step | Operation | Result |
|---|---|---|
| 1 | Merge P1(20), P2(15) | P2(15), P1(20) |
| 2 | Merge P3(20), P4(10) | P4(10), P3(20) |
| 3 | Merge previous groups | P4(10), P2(15), P1(20), P3(20) |
| 4 | Merge P5(15), P6(20) | P5(15), P6(20) |
| 5 | Merge P7(25), P8(10) | P8(10), P7(25) |
| 6 | Merge previous groups | P8(10), P5(15), P6(20), P7(25) |
| 7 | Final merge | P4(10), P8(10), P2(15), P5(15), P1(20), P3(20), P6(20), P7(25) |

### Merge Sort Final Result

**P4(10) → P8(10) → P2(15) → P5(15) → P1(20) → P3(20) → P6(20) → P7(25)**

---

## Quick Sort Trace

Pivot used: **Last element**

| Step | Pivot | Result After Partition |
|---|---:|---|
| 1 | 10 | P4(10), P8(10), P3(20), P1(20), P5(15), P6(20), P7(25), P2(15) |
| 2 | 15 | P4(10), P8(10), P5(15), P2(15), P3(20), P1(20), P6(20), P7(25) |
| 3 | 20 | P4(10), P8(10), P5(15), P2(15), P3(20), P6(20), P1(20), P7(25) |
| 4 | 20 | P4(10), P8(10), P5(15), P2(15), P3(20), P6(20), P1(20), P7(25) |
| 5 | 20 | P4(10), P8(10), P5(15), P2(15), P3(20), P6(20), P1(20), P7(25) |

### Quick Sort Final Result

**P4(10) → P8(10) → P5(15) → P2(15) → P3(20) → P6(20) → P1(20) → P7(25)**

---

## Stability Verification

| Weight | Original Order | Merge Sort Order | Stable? |
|---:|---|---|---|
| 10 | P4 → P8 | P4 → P8 | Yes |
| 15 | P2 → P5 | P2 → P5 | Yes |
| 20 | P1 → P3 → P6 | P1 → P3 → P6 | Yes |
| 25 | P7 | P7 | — |

## Conclusion

Merge Sort is stable when implemented using `<=` while merging. Therefore, it preserves the original order of packages having equal weights.

Quick Sort does not guarantee stability. Hence, **Merge Sort is more suitable when maintaining the original order of equal-weight packages is important.**
