var Int64 = require('../build/Release/node-cint64.node').Int64;

var assert = require('assert');

describe('Int64', function() {
    describe('#new', function() {
        it('should return a new Int64 object', function() {
            assert.equal(typeof (new Int64(7)), 'object');
        });
    });

    describe('#toNumber()', function() {
        it('should return a Number', function() {
            assert.equal(typeof (new Int64(7).toNumber()), 'number');
        });
        it('should return a Number equal to the int64', function() {
            assert.equal(5, new Int64(5).toNumber());
        });
    });

    describe('#add()', function() {
        it('should return the addition of its operands', function() {
            assert.equal(2, new Int64(1).add(1).toNumber());
        });
    });

    describe('#sub()', function() {
        it('should return the subtraction of its operands', function() {
            assert.equal(1, new Int64(2).sub(1).toNumber());
        });
    });

    describe('#mul()', function() {
        it('should return the subtraction of its operands', function() {
            assert.equal(2, new Int64(2).mul(1).toNumber());
        });
    });

    describe('#div()', function() {
        it('should return the division of its operands', function() {
            assert.equal(2, new Int64(8).div(3).toNumber());
        });
    });

    describe('#mod()', function() {
        it('should return the modulus of its operands', function() {
            assert.equal(2, new Int64(8).div(3).toNumber());
        });
    });

    describe('#neg()', function() {
        it('should return the negation of its operand', function() {
            assert.equal(-2, new Int64(2).neg().toNumber());
        });
    });

    describe('#and()', function() {
        it('should return the AND of its operands', function() {
            assert.equal(0, new Int64(2).and(1).toNumber());
            assert.equal(1, new Int64(3).and(1).toNumber());
            assert.equal(7, new Int64(-1).and(7).toNumber());
        });
    });

    describe('#or()', function() {
        it('should return the OR of its operands', function() {
            assert.equal(3, new Int64(2).or(1).toNumber());
            assert.equal(3, new Int64(3).or(1).toNumber());
            assert.equal(-1, new Int64(-1).or(7).toNumber());
        });
    });

    describe('#xor()', function() {
        it('should return the XOR of its operands', function() {
            assert.equal(3, new Int64(2).xor(1).toNumber());
            assert.equal(2, new Int64(3).xor(1).toNumber());
            assert.equal(-8, new Int64(-1).xor(7).toNumber());
        });
    });

    describe('#toString()', function() {
        it('should return the string value of its operands', function() {
            assert.equal('ff', new Int64(255).toString(16));
            assert.equal('255', new Int64(255).toString());
            assert.equal('17', new Int64(17).toString(10));
            assert.equal('111', new Int64(7).toString(2));
        });
    });


    describe('#intoBuffer()', function() {
        // TODO: Refactor out initialization code
        it('should copy the integer into a Buffer', function() {
            var a = new Buffer([-3, -2, -1, 0, 1, 2, 3, 4]);
            var b = new Buffer(8);
            var testInt = new Int64(a);
            testInt.intoBuffer(b);
            for (var i = 0; i < a.length && i < b.length; i++) {
                assert.equal(b[i], a[i]);
            }
        });
        it('should not write outside of the Buffer', function() {
            var a = new Buffer([4, 3, 2, 1, 0, -1, -2, -3]);
            var b = new Buffer(7);
            var testInt = new Int64(a);
            testInt.intoBuffer(b);
            // This shouldn't crash, essentially
            for (var i = 0; i < a.length && i < b.length; i++) {
                assert.equal(b[i], a[i]);
            }
        });
        it('should write starting at an offset if given one', function() {
            var a = new Buffer([-3, -2, -1, 0, 1, 2, 3, 4]);
            var b = new Buffer(17);
            var testInt = new Int64(a);
            testInt.intoBuffer(b);
            testInt.intoBuffer(b, 9);
            // This shouldn't crash, essentially
            for (var i = 0; i < a.length; i++) {
                assert.equal(b[i], a[i]);
                assert.equal(b[i+9], a[i]);
            }
        });
        it('should only write the bytes given in the source range', function() {
            // var a = new Buffer([4, 3, 2, 1, 0, -1, -2, -3]);
            var a = new Buffer([-3, -2, -1, 0, 1, 2, 3, 4]);
            var b = new Buffer(4);
            var testInt = new Int64(a);
            testInt.intoBuffer(b, 0, 4, 8);
            for (var i = 0; i < b.length; i++) {
                assert.equal(b[i], a[i+4]);
            }
        });
        it('should only write the bytes given in the source range', function() {
            // var a = new Buffer([4, 3, 2, 1, 0, -1, -2, -3]);
            var a = new Buffer([-3, -2, -1, 0, 1, 2, 3, 4]);
            var b = new Buffer(4);
            b[0] = 100;

            var testInt = new Int64(a);
            testInt.intoBuffer(b, 1, 4, 7);
            for (var i = 0; i < 3; i++) {
                assert.equal(b[i+1], a[i+4]);
            }
            assert.equal(b[0], 100);
        });
        it('should range check its inputs', function() {
            var testInt = new Int64(7);
            var b = new Buffer(0);
            assert.throws(function() {
                testInt.intoBuffer(b, -1);
            }, TypeError);
            assert.throws(function() {
                testInt.intoBuffer(b, 0, -1);
            }, TypeError);
        });
    });
});
