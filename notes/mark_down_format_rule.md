# Markdown Format Rules

This document defines the formatting conventions used in this project's markdown notes.
It is intended for AI to use as a reference when converting or fixing markdown files.

---

## 1. Document Structure

- The file starts with a single `#` title, followed by a blank line.
- Major sections use `##` headings, followed by a blank line.
- Sub-sections (groupings within a section) use `**bold text**` — NOT `###` headings.
- Each `**bold text**` sub-section label is followed by a blank line before listing its items.

**Example:**

```markdown
# Getting started


## Single Task application

We have a file app.c, there are 2 parts: outside and inside main function.

**outside main func**

1. As with any C programs, you need to include...
```

---

## 2. Lists

- Use numbered lists (`1.`, `2.`, `3.`) for sequential steps.
- Use bullet lists (`-`) for non-ordered items or sub-items within a step.
- A blank line is required before a list if it follows a paragraph or heading.
- No blank line between consecutive bullet items in the same list.
- No bold labels (e.g., ~~`**Pros:**`~~) — write descriptions as plain prose sentences.

**Example:**

```markdown
3. Create a task (OSTaskCreate()) by passing 13 argument which are:
- OS_TCB
- Task name
- Address of Task code
- Actual argument that the task receives
- Prio
```

---

## 3. Code Blocks

- Always use triple backtick with a language identifier: ` ```c `.
- The code block is preceded and followed by a blank line.
- Code blocks appear after the descriptive sentence of a numbered step.
- Block comments inside code use the project's standard banner style (lines of `*`).

**Example:**

```markdown
2. Start the main function by calling BSP function that disables all interrupt then init OS.

```c
BSP_IntDisAll();
OSInit(&err);
if (err != OS_ERR_NONE) {
/* Something didn't get initialized correctly ...
*/
}
```
```

---

## 4. Inline Code

- Function names, macros, and identifiers mentioned inline in prose are written with backticks: `OSInit()`, `OS_ERR`, `app_cfg.h`.
- File names are also wrapped in backticks: `app.c`, `os.h`.

**Example:**

```markdown
- `app_cfg.h` configures the application.
- `os.h` is the main header file for μC/OS-III.
```

---

## 5. Notes and Warnings

- Important notes are written as plain prose sentences — NOT as blockquotes (`>`).
- They are placed at the end of the relevant section, on their own line with a blank line before them.

**Example:**

```markdown
If any task has the higher prio than the AppTaskStart, then it will immediately switch to its task
```

---

## 6. Spacing Rules

| Location | Rule |
|---|---|
| After `#` title | 2 blank lines before next `##` |
| After `##` heading | 1 blank line |
| After `**bold**` sub-label | 1 blank line |
| Between paragraphs | 1 blank line |
| Before/after code block | 1 blank line |
| Between numbered steps | 1 blank line |

---

## 7. What to Avoid

- Do NOT use `###` for sub-sections — use `**bold text**` instead.
- Do NOT use blockquotes (`>`) for notes.
- Do NOT use bold labels like `**Pros:**`, `**Cons:**`, `**Configuration:**` inside bullet items — write as plain text.
- Do NOT add extra punctuation at the end of list items unless it is a full sentence.
- Do NOT use `---` horizontal rules within content sections (only allowed as section separators in this rules document itself).
