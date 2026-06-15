# Population Ceiling Calculator

A command-line tool for calculating realistic medieval city population limits
based on agricultural output, region geography, and grain transit losses.

## What It Does

Given a set of geographic regions defined by hex map tiles, the tool calculates:
- Arable land and farming families per region
- Gross grain harvest accounting for soil type and yield ratios
- Surplus after taxes, spoilage, seeds, and subsistence
- Transit losses from farm to city
- Maximum urban population the supply zone can support

## Building

Requires CMake 4.2+ and a C++17 compiler (MSVC, GCC, or Clang).

```bash
cmake -B build
cmake --build build
```

## Usage

Run the executable and follow the prompts. You will be asked to input:
- Number of regions and hex width in miles
- Hex count, soil type, and rotation system per region
- Tax rates, transit distances, and toll points per region

## Planned Features
- Technology modifiers (irrigation, iron plow, watermill)
- Maritime modifier for coastal fisheries
- Port city and sea crossing transit stages
- River and coastal supply zone calculators