# Overview

``` text
/
+--os
|  +--cfg/
|  |  +--os_cfg.h
|  +--inc/
|  +--src/
|
+--port
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

# Description

The project is divided into 5 subdirectories:

- **`os/`**: Contains source codes and configurations of the kernel.
- **`port/`**: For porting the OS to different platforms. It includes:
  - **`arch/`**: For potential porting to different architectures like
    RISC-V, MIPS, etc.. Although only Arm is going to be supported at
    first.
  - **`dev/`**: For potential porting to different devices from
    different vendors. The folder includes **`<vendor>/<chip>`** for
    each processor.
- **`ext/`**: For potential usage of external libraries.
- **`docs/`**: Documentation.
- **`notes/`**: Development notes for team collaboration.
- **`README.md`**: Introduction and a brief guide for installation and
  usage.
