# Valgrind Testing Suite for cub3D

This self-contained directory has everything you need to test cub3D projects for memory leaks.

## Quick Start

From the cub3D project root:
```bash
./valgrind_check.sh              # Full test (save + interactive modes)
./valgrind_check.sh --quick      # Quick validation (recommended for CI)
./valgrind_check.sh --help       # See all options
```

Or from anywhere:
```bash
cd /path/to/any/cub3D
/path/to/this/valgrind_logs/valgrind_check.sh --quick
```

## What's Included

- `valgrind_check.sh` - Unified testing script (all modes)
- `README.md` - This file
- `VALGRIND_RESULTS.txt` - Latest test results summary
- Generated log files (ignored by git)

## Usage Modes

### Quick Mode (--quick)
Fast validation of your code, ignores MLX library blocks:
```bash
./valgrind_check.sh --quick
```
- ✓ Tests parser and memory management
- ✓ Ignores "still reachable" from MLX
- ✓ No log files created
- ✓ Perfect for quick checks

### Full Mode (default)
Comprehensive testing with detailed logs:
```bash
./valgrind_check.sh
```
- ✓ Tests both save and interactive modes
- ✓ Creates detailed log files
- ✓ Timestamps all results
- ✓ Complete coverage

### Individual Modes
```bash
./valgrind_check.sh --save         # Only save mode
./valgrind_check.sh --interactive  # Only interactive mode
```

## File Naming Convention

- `full_<mode>_<timestamp>.log` - Complete valgrind output with verbose details
- `console_<mode>_<timestamp>.log` - Console output during test
- `summary_<timestamp>.txt` - Human-readable summary of results
- `*_leaks.log` - Detailed leak reports (only created if leaks detected)
- `*_errors.log` - Detailed error reports (only created if errors detected)

## Using on Other Projects

Just copy the entire `valgrind_logs/` folder to any cub3D project:
```bash
cp -r valgrind_logs /path/to/other/cub3D/
cd /path/to/other/cub3D
./valgrind_check.sh --quick
```

All logs will be saved in the valgrind_logs folder automatically.
