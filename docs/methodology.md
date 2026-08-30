# Methodology: The Matrix Pseudobasic Method

This document explains the mathematical method described in the original 2018
thesis, *"Матричні псевдобазисні алгоритми"* ("Matrix Pseudobasic
Algorithms"), independent of any particular code implementation. For how the
C++ program implements these ideas, see [`algorithm.md`](./algorithm.md).

## 1. Problem statement

Given a linear system

```
A u = b        (the "perturbed" / "target" system)
```

where the matrix `A` and/or the right-hand side `b` have changed from some
**known** system

```
A0 u0 = b0     (the "auxiliary" system, допоміжна система)
```

whose solution `u0` and inverse matrix `A0⁻¹` are already known — the goal is
to find the solution and inverse of the *changed* system **without fully
re-solving it from scratch**. This matters whenever a linear model
(economic, technological, engineering) needs to be re-evaluated repeatedly
after small coefficient perturbations: recomputing the full inverse every
time is wasteful when the auxiliary solution is already at hand.

## 2. Core idea: the artificial (pseudobasic) matrix

The method builds a sequence of **artificial basic matrices** — matrices
assembled from linearly independent rows ("normals of constraint
hyperplanes") drawn partly from the known auxiliary system and partly from
the perturbed system. Row by row, the auxiliary system's constraints are
iteratively **replaced** by the corresponding relaxed constraints of the
target system, following simplex-style pivoting relations. At each
iteration the **rank** and a **support condition** (умова опорності) of the
resulting intermediate matrix are checked, guaranteeing the substitution is
numerically valid before it's committed.

## 3. Governing relations (formulas 4–7)

Theorem 1 in the thesis relates:

- the pivot coefficients of the expansion of a constraint's normal vector
  over the rows of the artificial basis matrix,
- the elements of the inverse matrices,
- the basic solutions,
- and the constraint residuals (нев'язки)

in two neighboring basic solutions, through recalculation relations (4)–(7)
— a simplex-tableau-style update rule. The **support condition** for
introducing a new row's normal (with a nonzero pivot coefficient) at
position `k` of the basis matrix is that this pivot coefficient must be
non-zero — mirroring the non-degeneracy requirement of simplex pivoting.

## 4. Algorithm 1 — building the pseudobasic matrix

**Step 1.** Set up the initial matrix, combining the auxiliary system's
coefficient matrix with an identity block:

```
[ A0 | I ]
```

**Step 2.** Iterate over rows `k = 1 … m`.

- If a pivot element is (near) zero, permute rows to bring the largest
  available nonzero value into the pivot position first — otherwise the
  condition number of the working matrix explodes and the elimination
  becomes numerically unstable.

**Step 3.** At each iteration, derive the next matrix from the previous one
by elementary row operations (the standard Gauss–Jordan-style pivot step):

- the pivot row is normalized by dividing by the pivot element;
- every other row has a multiple of the pivot row subtracted, canceling its
  entry in the pivot column.

**Result.** After `m` iterations the process yields a matrix combining the
**inverse of the current basis matrix** together with the **solution
vector** of the system — formulas (3)–(4) in the thesis.

## 5. Algorithm 2 — recalculating after a row change

Once the base solution and inverse are known (Algorithm 1), the thesis
describes how to handle a change to **one row** of the system without
restarting:

**Step 1.** Take the known inverse matrix and solution (from Algorithm 1).

**Step 2.** Build an augmented matrix (7) that places the current inverse
and solution alongside the *original* system's coefficients.

**Step 3.** Substitute the chosen row `k` with its new (perturbed)
coefficients, then recompute:

- the new row via formula (8) — re-expressing the perturbed row's normal in
  terms of the current basis;
- the new right-hand-side / free term via formula (9).

**Step 4.** Perform **one** pivot iteration on the row/column at index `k`
(not a full re-run of Algorithm 1) to fold the change into the basis and
obtain the updated solution (11).

This is the computational payoff of the method: a single-row coefficient
change costs one pivot step, not a full re-solve.

## 6. Worked numerical example (from the thesis)

The thesis's model example is the 3×3 system

```
8u1 + 2u2 + 5u3 = 1
      2u2 + 3u3 = 1
4u1 +  u2 +  u3 = 1
```

(matched by [`examples/matr.txt`](../examples/matr.txt) and the
handwritten derivation photographed in
[`archive/приклад`](../archive/cpp_drafts) drafts — see
[`provenance.md`](./provenance.md)). Algorithm 1 is applied to obtain the
inverse of the coefficient matrix and the solution vector; Algorithm 2 is
then demonstrated by replacing one row and recomputing.

## 7. Terminology reference (UA → EN)

| Ukrainian term | English gloss |
|---|---|
| допоміжна система | auxiliary system |
| збурена система | perturbed system |
| штучна базисна матриця | artificial / pseudobasic basis matrix |
| умова опорності | support condition |
| ранг | rank |
| нев'язка | residual |
| основне рішення | basic solution |
| обернена матриця | inverse matrix |

## Source

This document is a faithful paraphrase of the algorithm section of
*Антоневич_теза_укр.docx* (archived as [`paper/thesis.docx`](../paper/thesis.docx)),
the confirmed full Ukrainian thesis text. See
[`provenance.md`](./provenance.md) for how this text relates to the original
Google Drive materials.
