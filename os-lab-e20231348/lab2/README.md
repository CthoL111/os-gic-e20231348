# OS Lab 2 - File Management and Path Navigation Report

## Student Information
- **Name:** YAN CHANTHOL
- **ID:** e20231348
- **Environment:** Ubuntu Linux (WSL)

## Setup Configuration
- **file1:** `audit notes.txt`
- **file2:** `budget 2026.txt`
- **owner:** Legal
- **reader:** Marketing
- **third:** Engineering

## Core Milestones Verification
- **Core 1:** Company structure created under `TechCorp/` using explicit variables.
- **Core 2:** Document migration completed successfully:
  - Moved `file1` out of incoming via relative mappings (`../reports/`).
  - Moved `file2` out of incoming utilizing explicit absolute directory patterns (`$HOME/oslab-work/lab2/...`).
  - Duplicated assets perfectly across designated group directories.
- **Core 3:** Integrity verified using `cmp` byte comparison. Relative route issues parsed out correctly from reader branches.

## Path Evaluation Choice
I chose to use relative paths for localized environment shifts because they require significantly less typing and keep script sizes small. However, absolute paths are better for background automation or system cron jobs because they execute reliably regardless of what directory the process starts from.

## Optional Challenges Completed
- **Plus Milestone:** Successfully navigated complex hidden maps inside `mess/` modules using 3 parent folder directory hops (`../../../`).
- **Challenge Milestone:** Verified global shell expansion using the `*` wildcard. Noted that direct single-quotes prevent variable processing while dot extensions require clear explicit filters.
