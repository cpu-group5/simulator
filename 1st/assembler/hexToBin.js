var raw = process.argv[2].split(' ');
var hex = '0x' + raw.reverse().join('');
console.log(hex);
console.log(('0'.repeat(32) + (+hex).toString(2)).slice(-32));
