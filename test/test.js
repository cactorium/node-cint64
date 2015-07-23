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


});
