# node-cint64
[![Build Status](https://travis-ci.org/cactorium/node-cint64.svg?branch=master)](https://travis-ci.org/cactorium/node-cint64)
64-bit native signed integers for Node 6 and newer! I think
we currently support most if not all native operations. This uses a C++ addon
wrapping a `int64_t` to provide exact C++ specified semantics.

**NOTE: Node 5 and older are now unsupported! The latest version that should work with those is 1.1.3**

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
// existing value. New methods may be added that modify an existing Int64 Object

// All unary operations are Int64 methods that take no arguments and return
// a new Int64 object containing the result

// All binary operations are Int64 methods that take a Number or an Int64
/ Object as its argument, and return a new Int64 Object containing the result

var c = new Int64(1);
var d = new Int64(2);

// shiftLeft() does a signed left shift.
e = c.shiftLeft(1); // e == c << 1 = 2
e = c.shiftLeft(2); // e == c << 2 = 4

// shiftRight() does a signed right shift
e = c.shiftRight(1); // e == c >> 1 = 0

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


// intoBuffer() is kind of complicated, so here's its type signature:
// #intoBuffer(Buffer b, [number dstStart, [number srcStart, [number srcEnd]])
// intoBuffer() copies the int64's bytes into the Buffer passed as b. It is
// modelled after Buffer#copy(), and throws a TypeError whenever an invalid
// argument is passed in.

var f = new Int64(new Buffer([0, 1, 2, 3, 4, 5, 6, 7]));
var buf = new Buffer(8);
c.intoBuffer(buf); // buf now contains the bytes from c in little-endian order
// buf = [0, 1, 2, 3, 4, 5, 6, 7]

// dstStart, if it is included, will set the position of the
// first byte copied into the target buffer. It defaults to zero.
buf.fill(0);
c.intoBuffer(buf, 1); // buf = [0, 0, 1, 2, 3, 4, 5, 6]

// srcStart, if it is included, will set the first byte of the int64 that will
// be copied into the buffer.
buf.fill(0);
c.intoBuffer(buf, 0, 3); // buf = [3, 4, 5, 6, 7, 0, 0, 0]

// srcEnd, if it is included, determines the last byte as (srcEnd-1), so that
// srcEnd - srcStart bytes, starting at srcStart are copied
b.fill(0);
c.intoBuffer(buf, 0, 0, 4); // buf = [0, 1, 2, 0, 0, 0, 0, 0]

```

## TODOS
- Add more tests
