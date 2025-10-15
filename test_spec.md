# String Calculator Test Specification

## Test Cases

| **Test #** | **Description** | **Input** | **Expected Output / Behavior** |
|------------|-----------------|-----------|---------------------------------|
| 1 | Empty string returns 0 | `""` | `0` |
| 2 | Single number returns that number | `"1"` | `1` |
| 3 | Two numbers comma-separated | `"1,2"` | `3` |
| 4 | Multiple numbers | `"1,2,3,4"` | `10` |
| 5 | Newline as delimiter | `"1\n2,3"` | `6` |
| 6 | Invalid newline format (not required to handle) | `"1,\n"` | Invalid input – undefined behavior (not tested) |
| 7 | Custom single-character delimiter | `"//;\n1;2"` | `3` |
| 8 | Custom delimiter with pipe character | `"//|\n1|2|3"` | `6` |
| 9 | Custom multi-character delimiter | `"//[***]\n1***2***3"` | `6` |
| 10 | Custom multi-character delimiter with letters | `"//[abc]\n2abc3abc4"` | `9` |
| 11 | Multiple single-character delimiters | `"//[*][%]\n1*2%3"` | `6` |
| 12 | Multiple multi-character delimiters | `"//[***][%%%]\n1***2%%%3"` | `6` |
| 13 | One negative number | `"1,-2"` | Exception: `negatives not allowed: -2` |
| 14 | Multiple negative numbers | `"2,-4,3,-5"` | Exception: `negatives not allowed: -4, -5` |
| 15 | Number greater than 1000 is ignored | `"2,1001"` | `2` |
| 16 | Number equal to 1000 is included | `"1000,1"` | `1001` |
| 17 | Complex input: multi-delimiters, newline, ignored >1000, and negative | `"//[**][%%]\n1**2%%3\n4,1001,-5"` | Exception: `negatives not allowed: -5` |

