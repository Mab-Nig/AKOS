- project structure
- Makefile convention
- toolchain
- build flags
- git workflow
- requirements
- docs
- milestones

# Project Structure

``` text
/
+--os
|  +--cfg/
|  |  +--os_cfg.h
|  +--inc/
|  +--src/
|
+--plat
|  +--arch
|  |  +--<arch>
|  |     +--inc/
|  |     +--src/
|  |
|  +--dev
|     +--<vendor>
|        +--<chip>
|           +--inc/
|           +--src/
|           |  +--startup.c 
|           +--linker.ld
|
+--ext
|  +--<lib>
|     +--inc/
|     +--src/
|     +--lib/
|
+--docs/
+--notes/
|
+--README.md
```

# Milestone

- Requirement gathering / System analysis / Architecture design / Module
  design: **Apr 6, 2026**.
- Coding + Unit testing: **May 18, 2026**.
- Integration testing + System testing + Acceptance testing: **June 1,
  2026**.
