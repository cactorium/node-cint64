# node-cint64
64-bit native signed integers for Node! Currently highly experimental! I think
we currently support most if not all native operations. This uses a C++ addon
wrapping a `int64_t` to provide exact C++ specified operations.

## Installation
`npm install node-cint64`

### Usage
```
var Int64 = require('node-cint64').Int64;

// Int64 can take either a Number or a Buffer. If you insert a buffer, it will
// load the first 8 bytes of the buffer in little-endian order into an int64_t
// (buf[0] will be the lowest 8 bits, buf[7] the highest)
var a = new Int64(7);

// A Javascript Number can store 32-bits, so you can use bitshifts and an or
// to load all 64 bits in two operations
var b = new Int64(4294967295).shiftLeft(32).or(new Int64(4294967295)); // === -1

// All instructions currently allocate a new int64 instead of modifying the
// existing value. This might be changed in the future.

// All unary operations are Int64 methods that take no arguments and return
// a new Int64 object containing the result

// All binary operations are Int64 methods that take a Number or an Int64
/ Object as its argument, and return a new Int64 Object containing the result

var c = new Int64(1);
var d = new Int64(2);

// shiftLeft() does a signed left shift.
// NOTE: C++ seems to have a wrap around on the shift parameter so that
// a.shiftLeft(64) returns the original number
e = c.shiftLeft(1); // e == c << 1 = 2
e = c.shiftLeft(64); // e == c << 64 = 1
e = c.shiftLeft(65); // e == c << 1 = 2 again

// shiftRight() does a signed right shift. This appears to have the same wraparound
// as shiftLeft()
e = c.shiftRight(1); // e == c >> 1 = 0
e = c.shiftRight(65); // e == c >> 65 = 0 again

// not() returns an inverted version of the original number
var e = c.not(); // e == ~c == -2

// and(), or(), and xor() perform their respective binary operation on the operands.
e = c.and(d); // e == 1 & 2 == 0
e = c.or(d); // e == 1 | 2 == 3
e = c.xor(d); // e == 1 ^ 2 == 3

// add(), sub(), mul(), and div() perform standard addition, subtraction,
// multiplication, and division, respectively
e = c.add(d); // e == c + d == 3
e = c.sub(d); // e == c - d == -1
e = c.mul(d); // e == c * d == 2
e = c.div(d); // e == c / d == 0

// mod() returns the modulus of a with respect to b
e = c.mod(d); // e == c % d == 1

// neg() negates the number
e = c.neg(); // e == -c == -1

// abs() returns the absolute value of a number
e = c.abs(); // e == abs(c) == 1

// Int64 also has the standard set of comparison functions, each of which is an
// Int64 method that takes a Number or Int64 Object and does a comparison, and
// returns the result as a Boolean
e = c.gt(e); // e == (c > d) == false
e = c.geq(e); // e == (c >= d) == false
e = c.lt(e); // e == (c < d) == true
e = c.leq(e); // e == (c <= d) == true
e = c.eq(e); // e == (c == d) == false
e = c.neq(e); // e == (c != d) == true

// Of course, to really use these operations there needs to be a way to convert
// the int64 back into Javascript-usable values. So currently there are two
// operations that return Javascript intepretations of the int64 value,
// toNumber(), and toString()

// toNumber() returns a Number containing the floating-point version of the int64
e = c.toNumber(); // e === 1

// toString() takes an optional Number that determines the base of the result,
// and converts the int64 into a String representing the number in that base.
// The base can be anything in the range [2, 64], and the output will be using
// the standard base64 set of characters to represent digits. If the number
// if negative, there will be a negative sign prepended to it.
e = c.toString(10); // e === '1'

```

## TODOS
- Add tests
- Integrate with Travis CI
