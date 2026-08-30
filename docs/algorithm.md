# Implementation Walkthrough: `src/matr_pseudobasic.cpp`

This document maps the C++ implementation back onto the algorithm steps
described in [`methodology.md`](./methodology.md).

## Data representation

The program represents matrices as `vector<vector<double>>`. A matrix row's
last column holds the right-hand-side / free term, so an `m × n` system is
stored as `m` rows of `n + 1` doubles.

## Input: `read_matr`

Reads `matr.txt` from the current working directory. The file format is:

```
<rows> <cols>
<row 1 coefficients...> <rhs 1>
<row 2 coefficients...> <rhs 2>
...
```

Each token may be a plain decimal or a fraction written as `a/b` (e.g.
`123/45`) — `read_matr` detects the `/` character and evaluates the
fraction manually with `atof`. The right-hand-side value of each row is
negated on read (`* (-1)`), matching the sign convention the rest of the
algorithm expects for the augmented-system free term.

`test_read_drobove_chyslo.cpp` (in `archive/cpp_drafts/`) is a small,
separate historical test program that exercises exactly this fraction
parsing against `drib.txt` — kept as a unit-test-style artifact.

## Setting up the auxiliary system: `identity_matr`, `fill_matr`

- `identity_matr` builds an `m × (m+1)` identity-augmented block (the known
  auxiliary system `Od`, corresponding to `[I | 0]`).
- `fill_matr` assembles the initial pseudobasic matrix `A[0]`: the top half
  comes from the input matrix `M`, the bottom half from the identity block
  `Od` — matching Step 1 of Algorithm 1 (`[A0 | I]`, stacked as a `2m × (m+1)`
  working matrix here since the implementation also drags the "shadow"
  system along instead of only its inverse).

## The elimination loop (`main`, the `while (k != m)` block)

Each iteration `k` derives `A[k]` from `A[k-1]` with a manual Gauss–Jordan
pivot step, computed per output column `r` (`0 … m`):

- **pivot row** (`r == k-1`): divide every entry in column `k-1` by the
  pivot element `A[k-1][k-1][k-1]`.
- **free-term column** (`r == m`): standard elimination update, with a
  `-0` → `0` normalization guard.
- **every other column**: standard elimination update
  `A[k][i][r] = A[k-1][i][r] - A[k-1][i][k-1] / pivot * A[k-1][k-1][r]`.

This is exactly Step 3 of Algorithm 1 — after `m` iterations, `A[m]`
(`NEW_M` in the code) contains the inverse matrix and the solution vector
side by side, in the same augmented layout the auxiliary system started in.

`print_matr_1` / `print_matr_2` / `print_matr_2_new` are formatting
helpers for console output (rounded display, indexed headers); they don't
affect the numerics.

`fill_Ob_matr`, `fill_Ob_matr_plus_sol`, and `fill_Vec_Sol` slice the final
augmented matrix `NEW_M` back apart into the standalone inverse matrix
`Ob`, the inverse-plus-solution block, and the solution vector `Sol`
respectively — these are pure bookkeeping/extraction steps.

## The row-recalculation feature (STEP 1 / 2 / 3, and `recalculation`)

This is the implementation of **Algorithm 2** (§5 of `methodology.md`):

- **STEP 1** — the program prompts on stdin for a row index `l` to change,
  then reads `m` new coefficients for that row into `CHANG_MATR`, an
  augmented matrix built from the original system `M` plus the current
  inverse-plus-solution block (this is matrix (7) from the thesis).
- **STEP 2** — `recalculation(CHANG_MATR, l, Ob, Sol)` recomputes the
  chosen row:
  - `multiply_line_matr` computes the row's expansion over the current
    basis (`alpha(k)` in the thesis — this is formula (8)).
  - `multiply_line_vect` computes the updated free term / residual against
    the current solution (formula (9)).
  - the row in `CHANG_MATR` is overwritten with these recalculated values.
- **STEP 3** — a **single** pivot iteration (the same elimination logic as
  the main loop, but applied only once, for row/column index `k = l + 1`)
  folds the changed row into the basis, producing `CHANG_MATR_1` — the
  updated inverse-plus-solution after the perturbation, i.e. formula (11).

Because only one pivot step runs here (instead of the full `while (k != m)`
loop), a single-row coefficient change is folded in at a fraction of the
cost of re-running Algorithm 1 from scratch — this is the practical payoff
the thesis argues for.

## Notable historical quirks (kept as-is, see `docs/provenance.md`)

- Comments are in Ukrainian, but the file's original encoding renders as
  mojibake in modern UTF-8 tools (e.g. `//иииидд...`). These are left
  untouched rather than "fixed," since guessing at the original bytes risks
  introducing new corruption; readable English narration is provided here
  and in `methodology.md` instead.
- One genuine bug — `vector<doubee>` (typo for `double`) on the line
  building the `Sol` vector — was corrected during 2026 curation so the
  file compiles; see `provenance.md`.
- `<windows.h>` was included but never used; removed during curation for
  portability (see `provenance.md`).
