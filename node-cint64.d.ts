export type CInt64 = {
    constructor(value: number);
    shiftLeft(signedBits: number): CInt64;
    shiftRight(signedBits: number): CInt64;
    xor(other: CInt64): CInt64;
    xor(other: number): CInt64;
    not(other: CInt64): CInt64;
    not(other: number): CInt64;
    and(other: CInt64): CInt64;
    and(other: number): CInt64;
    or(other: CInt64): CInt64;
    or(other: number): CInt64;
    neg(): CInt64;
    eq(other: CInt64): boolean;
    eq(other: number): boolean;
    toNumber(): number;
    };
