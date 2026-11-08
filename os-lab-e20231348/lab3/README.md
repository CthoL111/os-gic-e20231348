# Lab 3 — Wildcards, Hard Links and Symbolic Links: individual report

Student name/ID: YAN CHANTHOL / e20231348
Ubuntu username: gic-yan-chanthol
My values (oslab values lab3): name = silver, tag = saved, v1 = 292, v2 = 349
Files: evidence/wildcards.txt, evidence/links.txt, evidence/replacement.txt, evidence/checkpoint.txt, evidence/plus.txt, evidence/challenge.txt

## What I Saw

| State | What cat printed for the hard link | What cat printed for the symbolic link | What readlink printed |
|---|---|---|---|
| Before the rename | version 292 | version 292 | silver.txt |
| After the rename, before the repair | version 292 | cat: silver-soft.txt: No such file or directory | silver.txt |
| After a new file took the old name | version 292 | version 349 | silver.txt |
| After my repair | version 292 | version 292 | silver-saved.txt |

My repair (the two commands I wrote):
```bash
ln -sf "silver-saved.txt" "silver-soft.txt"
# Note: I used 'ln -sf' directly to force the link update. 
# While this works effectively, the handout's two-step method (running 'rm --' first) 
# is safer because it ensures you only remove a link you own without accidentally 
# replacing a regular data file.
```

## Explanation

During the experiment, the hard link `silver-hard.txt` and the original `silver.txt` initially shared the exact same inode number (18875082). When `silver.txt` was renamed to `silver-saved.txt`, the hard link continued to point directly to inode 18875082, preserving access to the original data block. On the other hand, the symbolic link `silver-soft.txt` stores only the text path string "silver.txt", meaning the OS performs a fresh lookup by name each time it is accessed. When a brand-new `silver.txt` file was created under a new inode (18875109), the symbolic link's lookup immediately routed to it to print version 349, while the hard link remained anchored to the old data at inode 18875082 to print version 292. I was most surprised that the symbolic link seamlessly revived itself without manual reconfiguration just because a new file took over its targeted path name.

## What My Tests Do Not Prove

Running `cat` on the links only proves what text content is stored inside the files, but it does not prove the actual structural relationship between them. For instance, seeing `version 292` from both files cannot prove that a hard link exists—the file could just be a separate copy—and only the matching inode numbers shown by `ls -li` can verify they share the same physical data.

## Plus / Challenge Extensions (Optional)

### Plus Wildcard Observations
* `notes/"$name"[12].txt` matches exactly one character (`1` or `2`) immediately following the name string, successfully expanding to `silver1.txt` and `silver2.txt` while leaving out `silver12.txt`.
* `notes/"$name"[!1]*` looks for one character following the name string that is explicitly not a `1`, followed by anything else. This successfully matches `silver.log` (since `.` is not `1`) and `silver2.txt`, while excluding both `silver1.txt` and `silver12.txt`.

### Challenge Multi-Link Life Cycle
* **Initial State:** When one data store is given three directory references (`one.txt`, `two.txt`, `three.txt`), all three present a link count of **3**.
* **First Removal (`one.txt`):** The link count tracking drops down to **2** on the remaining files, and the underlying text data remains intact and completely readable.
* **Second Removal (`two.txt`):** The link count drops down to **1** on the final remaining reference `three.txt`, while the file content still remains accessible. 
* **Data Persistence:** The physical data blocks are not immediately destroyed by file removals; they persist safely on the storage volume until the link count reaches **0** and no running application processes hold the file open.
