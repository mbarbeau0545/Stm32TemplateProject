# Contributing to STM32 Template Project

Thank you for your interest in the project. Bug fixes, hardware tests, STM32
ports, documentation improvements, and architectural feedback are welcome.

The project aims to keep application logic independent from the
microcontroller. Elements that are specific to a board or MCU must remain
isolated in the appropriate configuration layers.

## Before you start

For a significant fix, a new module, or a public API change, first open an
issue describing:

- the problem or requirement;
- the proposed solution;
- the affected boards and microcontrollers;
- the possible impact on existing APIs.

A small and straightforward fix may be submitted directly as a pull request.

## Set up the project

Clone the repository with its submodules:

```bash
git clone --recurse-submodules \
  https://github.com/mbarbeau0545/Stm32TemplateProject.git
cd Stm32TemplateProject
```

To initialize the submodules in an existing clone:

```bash
git submodule sync --recursive
git submodule update --init --recursive
```

The prerequisites and the generation, build, and flashing commands are
documented in the [README](README.md).

## Choose the correct repository

This repository is a superproject, and several of its components are Git
submodules.

- A change specific to a module tracked as a submodule must be submitted to
  that module's repository.
- The updated submodule revision may then be submitted to this repository.
- Integration changes, project configuration changes, and changes to
  components tracked directly here must be submitted to this repository.

Before modifying a path, check whether it belongs to a submodule:

```bash
git submodule status --recursive
```

Do not include unrelated changes in a contribution.

## Follow the architecture

The main project layout is:

- `src/0_Common` contains common types and generic libraries;
- `src/1_FMK/FMK_HAL` contains the framework hardware modules;
- `src/1_FMK/FMK_CFG` contains their configuration;
- `src/2_DRV` contains external component drivers;
- `src/3_APP` contains application modules and application logic;
- `src/4_PCSIM` contains the PC simulation adaptation.

Application code must use the public FMK APIs and must not directly access a
module's HAL handles. MCU- or board-specific clocks, GPIOs, IRQs, DMA channels,
pins, and HAL instances must remain in `ConfigSpecific`.

Asynchronous operations must not retain a pointer to an application buffer
after the API returns. They must use internal buffers and FIFO task
descriptors. Modules must use the public `Library/FIFO` API without directly
accessing its internal fields.

## Follow the C conventions

The complete rules are defined in [AGENTS.md](AGENTS.md). Every C or C++
contribution must follow these requirements, including:

- use the module prefix for public APIs and `s_` for local functions;
- apply the variable prefixes and type suffixes defined by the project;
- use a single `return` at the end of each function;
- store the result of a function call before testing it in a condition;
- expand all control blocks with braces on separate lines;
- place an implementation banner before every function implementation;
- number the main processing steps using English comments;
- document public APIs, typedefs, and static functions with Doxygen;
- keep lines within 80 columns whenever practical.

All new or modified project content must be written in English, including
comments, Doxygen documentation, messages, tests, and Markdown files.

New APIs must preserve backward compatibility or clearly explain any breaking
change in the pull request.

## Handle generated files

Files produced in `src/1_FMK/FMK_CFG` and `src/3_APP/APP_CFG` should be
modified through their configuration source or template whenever possible. A
contribution must state which files were generated and which configuration
was used.

After generating files, review the changes before committing them:

```bash
git status --short
git diff
```

Do not include temporary Excel files, build output, or files specific to a
local development environment.

## Build and verify

After any C or C++ change, build the project from the repository root:

```bash
pio run
```

When a change applies to a specific target, state in the pull request which
board was compiled and tested. PC simulation is useful, but it does not
replace hardware testing of interrupts, DMA, timing, and peripherals.

Before submitting the contribution, also check for whitespace errors:

```bash
git diff --check
```

Fix every warning introduced by the change. Add or update tests and
documentation whenever behavior changes.

## Prepare the pull request

Create a branch with a descriptive name, for example:

```text
fix/i2c-timeout
feature/spi-dma
docs/build-instructions
```

The pull request must describe:

- the problem and the chosen solution;
- the affected files or modules;
- the PlatformIO environments that were built;
- the boards used for hardware testing;
- the tests performed and their results;
- any known limitations or remaining work;
- the related issue, when applicable.

Keep each pull request focused. Large refactors and functional changes should
be submitted separately when they can be reviewed independently.

## Report an issue

A useful issue includes as much of the following information as possible:

- the board and exact MCU reference;
- the Git branch and revision;
- the PlatformIO configuration;
- the steps required to reproduce the problem;
- the expected and observed behavior;
- relevant build or diagnostic logs.

Never publish secrets, keys, personal data, or confidential information in an
issue.

## Contribution license

By submitting a contribution, you agree that it may be distributed under the
project's MIT License and confirm that you have the right to submit it.

Git submodules, external libraries, manufacturer documentation, and other
third-party resources retain their respective licenses and rights. The MIT
License at the repository root does not replace their terms.
