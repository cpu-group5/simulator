var rHeader = '0'.repeat(6);
function padZero(size, value) {
  return ('0'.repeat(32) + value).slice(-size);
}
function register(a){
  return rHeader + padZero(5, a[1]) + padZero(5, a[2]) + padZero(5, a[0])  + '0'.repeat(5);
};
function shift(a){
  return rHeader + '0'.repeat(5) + padZero(5, a[1]) + padZero(5, a[0]) + padZero(5, a[2])
};
function immediate(a){
  return padZero(5, a[1]) + padZero(5, a[0]) + padZero(16, a[2]);
};
function branch(a){
  return padZero(5, a[0]) + padZero(5, a[1]) + padZero(16, a[2]);
};

function f3Register(a){
  return '010001'+'10000'+padZero(5, a[2]) + padZero(5, a[1]) + padZero(5, a[0]);
};

function f2Register(a){
  return '010001'+'10000' + padZero(5, a[1])+'0'.repeat(5) + padZero(5, a[0]);
};

function cs(a){
  return '010001'+'10000' + padZero(5, a[2]) + padZero(5, a[1]) + padZero(3, a[0]) + '00' + '11';
}

module.exports = OPERATIONS = {
  'add': function (a) {
    return register(a) + '100000';
  },
  'addi': function (a) {
    return '001000' + immediate(a);
  },
  'sub': function (a) {
    return register(a) + '100010';
  },
  'and': function (a) {

  },
  'andi': function (a) {

  },
  'or': function (a) {

  },
  'ori': function (a) {

  },
  'nor': function (a) {

  },
  'sll': function (a) {

  },
  'srl': function (a) {
    return shift(a) + '000010';
  },
  'slt': function (a) {
    return register(a) + '101010';
  },
  'slti': function (a) {

  },
  'beq': function (a) {
    return '000100' + branch(a);
  },
  'bne': function (a) {
    return '000101' + branch(a);
  },
  'j': function (a) {
    return '000010' + padZero(26, a[0]);
  },
  'jal': function (a) {
    return '000011' + padZero(26, a[0]);
  },
  'jr': function (a) {
    return rHeader + padZero(5, a[0]) + '000000000000000' + '001000';
  },
  'jalr': function (a) {

  },
  'lui': function (a) {

  },
  'lw': function (a) {
    return '100011' + padZero(5, a[1]) + padZero(5, a[0]) + padZero(16, a[2]);
  },
  'sw': function (a) {
    return '101011' + padZero(5, a[1]) + padZero(5, a[0]) + padZero(16, a[2]);
  },
  'in': function (a) {
    return '01101000000' + padZero(5, a[0]) + '0000000000000000';
  },
  'out': function (a) {
    return '01101100000' + padZero(5, a[0]) + '0000000000000000';
  },
  'bt.s': function (a) {
    return  '010001' + '01000' + padZero(3, a[0]) + '01'  + padZero(16, a[1]);
  },
  'bf.s': function (a) {
    return  '010001' + '01000' + padZero(3, a[0]) + '00'  + padZero(16, a[1]);
  },
  'add.s': function (a) {
    return f3Register(a) + '000000';
  },
  'sub.s': function (a) {
    return f3Register(a) + '000001';
  },
  'mul.s': function (a) {
    return f3Register(a) + '000010'
  },
  'div.s': function (a) {
    return f3Register(a) + '000011'
  },
  'mov.s': function (a) {
    return f2Register(a) + '000110'
  },
  'neg.s': function (a) {
    return f2Register(a) + '000111'
  },
  'abs.s': function (a) {
    return f2Register(a) + '000101'
  },
  'sqrt.s': function (a) {
    return f2Register(a) + '000100'
  },
  'c.eq.s': function (a) {
    return cs(a) + '0010'
  },
  'c.lt.s': function (a) {
    return cs(a) + '1100'
  },
  'c.le.s': function (a) {
    return cs(a) + '1110'
  },
  'lw.s': function (a) {
    return '110001' + padZero(5, a[1]) + padZero(5, a[0]) + padZero(16, a[2]);
  },
  'sw.s': function (a) {
    return '111001' + padZero(5, a[1]) + padZero(5, a[0]) + padZero(16, a[2]);
  },
  'ftoi': function (a) {
    return '111000' + padZero(5, a[1]) + padZero(5, a[0]) + '0'.repeat(16);
  },
  'itof': function (a) {
    return '110000' + padZero(5, a[1]) + padZero(5, a[0]) + '0'.repeat(16);
  },
  'la': function (a) {
    return '001111'+ '00000' + padZero(5, a[0]) + padZero(32, a[1]).slice(0,16)
    + '001101' + immediate([a[0],a[0],padZero(32, a[1]).slice(16,32)]);
  },
};
