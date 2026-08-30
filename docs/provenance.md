# Provenance

This repository reconstructs and archives a 2018 university research
project (conference paper + code + presentation) from its original Google
Drive folder. This document distinguishes what is **original 2018
material** from what was **added or changed during 2026 curation**.

## Original (2018), unchanged

- `archive/matr_konferentsia_new_original.cpp` — the final, most complete
  historical C++ implementation (row-recalculation feature, `matr.txt`
  input, Windows-era build). Byte-for-byte as retrieved from Drive.
- `archive/cpp_drafts/` — three earlier draft implementations
  (`matr_konferentsia.cpp`, `matr_konferentsia_new.cpp`,
  `NEW_kopia_na_vsyakyi_vypadok.cpp`) documenting the algorithm's
  evolution, plus `test_read_drobove_chyslo.cpp`, a small historical unit
  test for the fraction-string parser (`a/b` tokens in `matr.txt`).
- `examples/matr.txt`, `examples/drib.txt` — the original sample input
  fixtures (transcribed verbatim as plain text; not base64-encoded since
  they were already plain text).
- `paper/thesis.docx` — the full Ukrainian thesis text
  (`Антоневич_теза_укр.docx` in the source folder), downloaded unmodified.
- `presentation/Zakhyst_5.pptx` — the original conference/defense slide
  deck (`Захист_5.pptx`), downloaded unmodified.
- `assets/20181025_143454.jpg`, `assets/20181025_143502.jpg` — conference
  photos, re-saved to strip embedded EXIF/GPS metadata (see below); pixel
  content unmodified.
- `assets/image_2018-11-19_20-57-05.png` — a results chart/diagram,
  unmodified.

## Added or changed during 2026 curation

- **`src/matr_pseudobasic.cpp`** — a portability-adjusted copy of
  `archive/matr_konferentsia_new_original.cpp`:
  - Removed `#include <windows.h>`, which was present in the original but
    never actually used (no Win32 API calls anywhere in the file) — a
    leftover from the original MSVC/Windows development environment.
  - Fixed one typo bug that prevented compilation on a standards-conformant
    compiler: `vector <doubee>` → `vector <double>` in the line building the
    solution vector `Sol`.
  - All algorithmic logic, variable names, and (mojibake) comments are
    otherwise preserved untouched — no attempt was made to "fix" the
    broken Cyrillic comment encoding, since guessing at the original bytes
    risked introducing further corruption. English explanations of what the
    code does are provided instead in `docs/algorithm.md`.
  - Verified to compile cleanly with `g++ -std=c++11 -Wall` and to run
    correctly against `examples/matr.txt`, producing output consistent with
    the historical console output described in the thesis's worked example.
- **`CMakeLists.txt`** — new, minimal build configuration (C++11) targeting
  `src/matr_pseudobasic.cpp`.
- **`README.md`, `docs/methodology.md`, `docs/algorithm.md`,
  `docs/conference.md`, `docs/provenance.md`** (this file) — new,
  written in 2026 to document and present the project; based on the
  original thesis text and conference programme.
- **`LICENSE`** — new; the original project had no stated license (typical
  for student coursework). See below.
- **`.gitignore`** — new, standard C++/CMake ignores.
- EXIF metadata (camera make/model, GPS if present, timestamps) was
  stripped from the two conference JPEG photos before committing, as a
  privacy precaution; visual content is unchanged.

## Excluded from this repository, and why

| Item | Reason |
|---|---|
| `matr_konferentsia_new.exe` | Compiled Windows binary; source is archived instead. |
| `~$*.docx` temp/lock files (3 files, 162 bytes each) | Microsoft Office lock artifacts, not real content. |
| `zbirnyk ITI2018.pdf` (~6.9 MB proceedings) | Collects papers by many unrelated authors; only cited by title in `docs/conference.md`, not republished. |
| `прикладусік.zip` (~17 MB) | A bundled example/build-artifact archive; its readable source content is already represented individually under `archive/`, and the zip itself was not worth committing raw. |
| `АНТОНЕВИЧ_NEW.docx`, `Антоневич+нью.docx` | Near-duplicate/derivative drafts of the same thesis text (largely matching slide-by-slide speaker notes for the presentation) — kept out to avoid redundant near-duplicate documents; `paper/thesis.docx` (`Антоневич_теза_укр.docx`) was selected as the canonical, most complete full-text version. |
| `моя_повна_теза.docx` | A shorter draft covering only the algorithm/theorem section, superseded by the full thesis text kept as `paper/thesis.docx`. |
| `тестування_коду.docx` | Contained only an empty numbered list (no actual content) when inspected — nothing to preserve. |
| Дідик, Копчик, Семенюк materials (several files) | Authored primarily by other students for their own separate conference submissions, sharing the same advisors (Kudin/Onyshchenko) but not the same student-author (Antonevych). Excluded per the rule that only Antonevych's own authored/co-authored work belongs in this archive. |
| Тесля Конференцiя_укр_2018.pdf | The advisor's own separate paper; not Antonevych's work. Cited only where relevant, not republished. |
| Article_Kudin_Onyshchenko | A joint article whose primary authorship could not be confirmed as including Antonevych from the available material; excluded out of caution rather than risk misattributing another author's separate work. |

## Historical context and honesty note

This project was originally built in 2018 using Windows-era C++ tooling
(the original source references `<windows.h>` and MSVC-style build habits).
It was curated into this portfolio repository in **2026** — the Git
history, README, CMake build, and documentation are all products of that
2026 curation pass, not of the original 2018 workflow. No attempt has been
made to retroactively present the original work as having used modern
tooling it did not actually use at the time.
