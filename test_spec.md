# String Calculator Test Specification

## Test Cases

| **Test #** | **Description** | **Input** | **Expected Output / Behavior** |
|------------|-----------------|-----------|---------------------------------|
| 1 | Empty string returns 0 | `""` | `0` |
| 2 | Single number returns that number | `"1"` | `1` |
| 3 | Two numbers comma-separated | `"1,2"` | `3` |
| 4 | Multiple numbers | `"1,2,3,4"` | `10` |
| 5 | Newline as delimiter | `"1\n2,3"` | `6` |
| 6 | Custom single-character delimiter 1 | `"//;\n1;2"` | `3` |
| 7 | Custom single-character delimiter 2 | `"//|\n1|2|3"` | `6` |
| 8 | Custom multi-character delimiter | `"//[***]\n1***2***3"` | `6` |
| 9 | Custom multi-character delimiter with letters | `"//[abc]\n2abc3abc4"` | `9` |
| 10 | Multiple single-character delimiters | `"//[*][%]\n1*2%3"` | `6` |
| 11 | Multiple multi-character delimiters | `"//[***][%%%]\n1***2%%%3"` | `6` |
| 12 | One negative number | `"1,-2"` | Exception: `negatives not allowed: -2` |
| 13 | Multiple negative numbers | `"2,-4,3,-5"` | Exception: `negatives not allowed: -4, -5` |
| 14 | Number greater than 1000 is ignored | `"2,1001"` | `2` |
| 15 | Number equal to 1000 is included | `"1000,1"` | `1001` |
| 16 | Complex input: multiple delimiters, >1000, and negative | `"//[**][%%]\n1**2%%3\n4,1001,-5"` | Exception: `negatives not allowed: -5` |
| 17 | Complex input without negatives: multiple delimiters and >1000 | `"//[***][#][!!]\n1***2#3\n4!!1001"` | `10` |
