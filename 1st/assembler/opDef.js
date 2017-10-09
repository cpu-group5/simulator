module.exports = OPERATIONS = {
  'add': function (a) {
    return '000000' + padZero(5, a[1]) + padZero(5, a[2]) + padZero(5, a[0]) + '00000100000';
  },
  'addi': function (a) {
    return '001000' + padZero(5, a[1]) + padZero(5, a[0]) + padZero(16, a[2]);
  },
  'sub': function (a) {
    return '000000' + padZero(5, a[1]) + padZero(5, a[2]) + padZero(5, a[0]) + '00000100010';
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
    return '00000000000' + padZero(5, a[1]) + padZero(5, a[0]) + padZero(5, a[2]) + '000010';
  },
  'slt': function (a) {

  },
  'slti': function (a) {

  },
  'beq': function (a) {
    return '000100' + padZero(5, a[0]) + padZero(5, a[1]) + padZero(16, a[2]);
  },
  'bne': function (a) {
    return '000101' + padZero(5, a[0]) + padZero(5, a[1]) + padZero(16, a[2]);
  },
  'j': function (a) {

  },
  'jal': function (a) {
    return '000011' + padZero(26, a[0]);
  },
  'jr': function (a) {
    return '000000' + padZero(5, a[0]) + '000000000000000' + '001000';
  },
  'jalr': function (a) {

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
  'bt_s': function (a) {

  },
  'bf_s': function (a) {

  },
  'add_s': function (a) {

  },
  'sub_s': function (a) {

  },
  'mul_s': function (a) {

  },
  'div_s': function (a) {

  },
  'inv_s': function (a) {

  },
  'c_s': function (a) {

  },
  'lw_s': function (a) {

  },
  'sw_s': function (a) {

  },
  'lui': function (a) {

  },
  'mov_s': function (a) {

  },
  'neg_s': function (a) {

  },
};

function padZero(size, value) {
  return ('00000000000000000000000000' + value).slice(-size);
}

function toOpCode(a, CIndex, CSize) {
  a.forEach(function (binary, index) {
    if (index !== CIndex) {
      a[index] = padZero(5, binary);
    } else {
      a[index] = padZero(CSize, binary);
    }
  });
  return a.join('');
}
