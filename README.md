```markdown
# GradeCalculator-cpp

A personal C++ console application for calculating and tracking grades **within a single class**. Supports point-based and percentage/category-based calculations with interactive menus and what-if scenarios.

Developed solo to provide more flexible grade tracking than typical online calculators. Multi-class support, GPA calculation mode, and persistent save/load functionality between sessions are planned for future implementation (see planning files for details).

## Project Overview

- Current modes: point totals and weighted categories (percentages) for one class.
- Interactive menus for adding, editing, or deleting scores and assignments within categories.
- Handles assignment names, earned/perfect scores, category weights, and letter grade scales.
- Real-time grade updates and what-if analysis (e.g., "what score do I need on the final?").

## My Implementation

Implemented solo:
- Used dynamic arrays for flexible storage of grades, perfect scores, assignment names, and categories.
- Built a robust menu system with thorough input validation.
- Performed accurate calculations for totals, percentages, and weighted averages.
- Included planning documents outlining future features (multi-class support, GPA mode, auto-save, multiple save files, data integrity checks, etc.).

## How to Build and Run

### Requirements
- G++ compiler

### Compilation
```bash
g++ gc.cpp -o "Grade Calculator"
```

### Execution
```bash
./"Grade Calculator"
```
- A sample `save.txt` is included for testing/demo purposes.
- Follow the on-screen menus to define categories and enter scores.

## Credits & Attribution

- Personal project created to address limitations of existing online grade calculators.
- Shared publicly for portfolio and demonstration purposes.

## License / Usage Note

This is an ongoing personal project. Feel free to view, learn from, or fork it — use at your own risk as some planned features (including multi-class support, GPA calculation, and full save/load) are still in development.

---

**Christopher Otto**  
Computer Science B.S. Candidate, Class of 2027  
University of Central Florida
