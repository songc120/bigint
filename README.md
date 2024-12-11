# `bigint` - Arbitrary-Precision Integer Class

The `bigint` class provides a custom implementation of arbitrary-precision integers, allowing signed integers of unlimited range within memory.

## Internal Representation

1. Digits Storage: The number is stored as a `std::vector<uint8_t>` where each element represents a single digit (base-10).
2. Sign Representation: A bool flag (`is_negative`) tracks whether the number is negative.

## Algorithms and Concepts

### Constructor

#### Default

`bigint()` creates a positive zero.

#### From Integer

1. `bigint(int64_t n)` creates a bigint object containing the same digits and sign as integer `n`.  
2. Each digit is extracted from the least significant end by `n % 10` and pushed into the `digits` vector.  
3. Once all digits are collected, the `digits` vector is reversed.
4. The sign of bigint follows that of the original digit. \
5. E.g. `bigint a = bigint(123); bigint b = bigint(-123);`

#### From String

1. `bigint(std::string n)` creates a bigint object containing the same digits and sign as string `n`.
2. The sign is determined by the first element of string `n`.  
3. `std::invalid_argument` is thrown if the string does not contain digits after the sign. E.g. `bigint("")` or `bigint("+")` or `bigint("-")`.  
4. All the leading zeros after the sign character is ignored.
5. The constructor then iterates through each digit, convert to `uint8_t` and then push into `digits`.  Any non-digit character found would raise `std::invalid_argument`. E.g.`bigint(1.23)`.
6. E.g. `bigint("-123")` =`bigint("-000123")` = -123. `bigint("+000123")` = `bigint("000123")`= `bigint("123")` = 123;

#### Copy

`bigint(bigint(123))` created a duplicate of `bigint(123)`.

### Addition

#### Preprocessing

1. The addition function only handles integers of same sign directly. E.g. `bigint(123) + bigint(456)` or `bigint(-123) + bigint(-456)`.  
2. Integers of opposing signs would be converted into a subtraction. E.g. `bigint(-123) + bigint(456)` becomes `-(bigint(123) - bigint(456))`; `bigint(123) + bigint(-456)` becomes `bigint(123) - bigint(456)`.
3. The mutual sign of inputs is adopted in the result.

#### Method

Addition is performed digit-by-digit from the least significant to the most significant, propagating any carry:

1. Add corresponding digits from both numbers, including any carry from the previous step.

2. Store the result modulo 10 as the current digit.

3. Compute the new carry as the integer division of the sum by 10.

**Example**:  
For `bigint(1234) + bigint(567)`, the digits are:

- `4 + 7 = 11` → Store `1`, carry `1`
- `3 + 6 + 1 = 10` → Store `0`, carry `1`
- `2 + 5 + 1 = 8` → Store `8`, carry `0`
- `1` (no corresponding digit) → Store `1`

**Result**:  
`1234 + 567 = 1801`

### Subtraction

#### Preprocessing

1. The subtraction function only handles integers of same sign such that a larger absolute value minus a smaller absolute value directly. E.g. `bigint(456) - bigint(123)` or `bigint(-456) - bigint(-123)`.  
2. Incase of a smaller absolute value minus a larger absolute value, the inputs would be reversed and negated. E.g. `bigint(123) - bigint(456)` will be treated as `bigint(456) - bigint(123)`.
3. Integers of opposing signs would be converted into an addition. E.g. `bigint(-123) - bigint(456)` becomes `-(bigint(123) + bigint(456))`; `bigint(123) - bigint(-456)` becomes `bigint(123) + bigint(456)`.
4. The result would be positive if the left integer is greater than or equal to the right integer, negative otherwise.

#### Method

Subtraction follows a similar approach, handling borrowing where necessary:

1. Subtract corresponding digits, accounting for any borrow from previous steps.
2. If a digit is negative after subtraction, borrow from the next significant digit.
3. Store the result as the current digit.
4. Leading zeros are removed after the loop.

**Example**:  
For `bigint(111) - bigint(99)`, the digits are:

- `1 - 9 = -8` → Store `2`, borrow `1`
- `1 - 9 - 1 = -9` → Store `1`, borrow `1`
- `1 - 1 = 0` → Store `0`, borrow `0`

**Result**:  
`111 - 99 = 12`

### Multiplication

#### Method

Multiplication mimics the manual long multiplication algorithm used in elementary mathematics using a nested loop, where the outer loop goes through the second number from the least significant digit and the inner loop goes through the first number:

1. Multiply each digit of the first number by each digit of the second number.
2. Stores and carry digits similar to addition.
3. Account for positional shifts by appending zeros.
4. Accumulate partial products using addition.
5. If the two numbers have the same sign, the result is positive. Otherwise, the result is negative.

**Example**:  
For `123 * 45`:

- Multiply `123` by `5` → `615`
  - `3 * 5 = 15` → Store `5`, carry `1`
  - `2 * 5 + 1 = 11` → Store `1`, carry `1`
  - `1 * 5 + 1 = 6` → Store `6`, carry `0`
- Multiply `123` by `4` → `4920` (shifted by one position)
  - `3 * 4 = 12` → Store `2`, carry `1`
  - `2 * 4 + 1 = 9` → Store `9`, carry `0`
  - `1 * 4 + 0 = 4` → Store `4`, carry `0`
  - Append one zero
- Add results: `615 + 4920 = 5535`

**Result**:  
`123 * 45 = 5535`

### Negation

Negation flips the sign of the bigint.  If the number is positive, it becomes negative, and vice versa. `-bigint(123) == bigint(-123)`

### Comparison

The comparison operators (`==, !=, <, >, <=, >=`) allow for intuitive comparisons between bigint values. `<` and `==` operators are used to implement `!=, >, <=, >=`.

#### Equal to (`==`)

Checks if both the sign and digits are the same. Or if both sides are zeros. E.g. `bigint(123) == bigint(123)` is true; `bigint("0") == bigint("-0")` is true.

#### Less than (`<`)

1. First check if both sides are equal. `bigint("-0") < bigint("0")` is false.
2. Compare signs.  Positive number is always greater than negative numbers. `bigint("-10") < bigint("0")` is true.
3. For numbers with the same sign:
    - Compare digit lengths.  `bigint("-10") < bigint("-0")` is true.
    - If lengths are equal, compare digit-by-digit from most significant to least significant.`bigint("-11") < bigint("-10")` is true.

#### Other comparisons

1. Not equal to (`!=`): Reverse result of `==`. E.g. `bigint("0") != bigint("-0")` is false.
2. Greater than (`>`): `bigint(a) > bigint(b) === bigint(b) < bigint(a)`.  Reverse inputs and then use `<`. `bigint("-0") <= bigint("0")` is false.
3. Less than or equal to (`<=`):`bigint(a) <= bigint(b) === bigint(b) < bigint(a) || bigint(b) == bigint(a)`. Combines `<` and `==`. `bigint("-0") <= bigint("0")` is true.
4. Greater than or equal to (`>=`):`bigint(a) >= bigint(b) === bigint(b) > bigint(a) || bigint(b) == bigint(a)`. Combines `>` and `==`. `bigint("-0") <= bigint("0")` is true.

### Insertion

1. Add `-` to stream if the bigint is negative.
2. Then add following digit to digit.
3. E.g. `std::cout << bigint(-1234) << "\n";` should output `-1234`;`std::cout << bigint("1234") << "\n";` should output `1234`;

### Increment and Decrement

1. Pre-increment/decrement:  Add/minus `bigint(1)` to the original number.
2. Post-increment/decrement:  Make a copy to return, then add/minus `bigint(1)` to the original number;

## Tests

Test results are saved in corresponding .log files.
### Constructor Tests

1. Tests assert that the default constructor indeed creates a zero bigint object.
2. Tests assert that `bigint(int64_t some_number)` is equivalent to `bigint(std::string same_number_converted_to_string)`.
3. Tests assert that `bigint(std::string random_very_large_number_converted_to_string)` contains correct sign and digits.

### 2-Input Function Tests

1. Contains tests for operations requiring two inputs, including `+, +=, -, -=, *, *=, ==, !=, <, >, <=, >=`.
2. The input file(`unit_test_2data.txt`) is produced using python script, in the form of `input1 op input2 = expected_result`, where `input1` and `input2` are 50-digits long randomly produced signed digits in string and expected_result is pre-calculated.
3. The test function asserts `bigint(input1) op bigint(input2) == bigint(expected_result)` and for comparisons `bigint(input1) op bigint(input2) == expected_result`.

The test function also performs consistency tests using the input file:

- For addition:
  - `a + b = b + a`
  - `a + b + c = c + a + b`
  - `a - b + c = c + a - b`
  - `a - b + c = c - b + a`
  - `a - b + c = - b + a + c`
  - `a + (b + c) = (a + b) + c`
  - `a + 0 = a` and `0 + a = a`
  - `a + (-a) = 0`
- For subtraction:
  - `a - a = 0`
  - `a - b + b = a`
  - `a + b - b = a`
  - `a - b = c`
  - `a = b + c`
  - `b = a - c`
- For multiplication:
  - `a * b = b * a`
  - `a * (b * c) = (a * b) * c`
  - `a * 1 = a`
  - `1 * a = a`
  - `a * 0 = 0`
  - `0 * a = 0`

Stress tests are performed in this function as well, as the end of the input file contains one test for each operator, with both inputs being one thousand digits long.

### 1-Input Function Tests

1. Contains tests for operations requiring one input, including pre/post-increment/decrement and unary minus.
2. The input file(`unit_test_1data.txt`) is produced using python script, in the form of `left right = expected_result`, and the test function could identify input number and operation among `left` and `right`.  The input numbers are 50-digits long randomly produced signed digits in string and expected_result is pre-calculated.
3. The test function asserts `op bigint(input) == bigint(expected_result)` and for post-increment/decrements `bigint(input) op == expected_result`.

### Edge Tests

The edge test ensures special cases, especially those involving zeros are handled correctly as changing signs and length calculation can be error-prone.

### Exception Tests
The only exception possible in public functions would be invalid input to the string constructor as there is no division involved.

- `bigint(string_containing_non-digit_character)` like `bigint("1a")` or `bigint("0.5")` should throw `std::invalid_argument("bigint::bigint : Invalid character in input string: " + bad_character)`.
- `bigint("")` or `bigint("-")` or `bigint("+")` should throw `std::invalid_argument("bigint::bigint : Input string is empty.")`.