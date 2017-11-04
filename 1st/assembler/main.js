OPERATIONS = require('./opDef');
fsForLabel = require('fs');
var p = console.log;
var lineCountForlabel = 0;
var labels = {};
var PC = 0;
var byteCode = '';

var lineReaderForLabel = require('readline').createInterface({
  input: require('fs').createReadStream('fib_edited.s')
});

function processLine(line) {
  var processedLine = line.replace(/,/g, '').split(/\s/);
  var instruction = processedLine[0];

  if (isLabel(instruction)) {
    registerLabel(instruction.substring(0, instruction.length - 1), PC);
  } else {
    if (instruction === 'jal') {
      byteCode += OPERATIONS[instruction]([(+labels[processedLine[1]]).toString(2)]);
    } else {
      byteCode += OPERATIONS[instruction](convertLine(processedLine.slice(1, processedLine.length)));
    }
  }
  PC++;
}

function isLabel(instruction) {
  return instruction[instruction.length - 1] === ':';
}

function registerLabel(label, PC) {
  labels[label] = PC;
}

function convertLine(argv) {
  argv.forEach(function (arg, index) {
    var numbers;
    if (!arg.match(/%r/) && arg.match(/[a-z]+/)) {
      var diff = (+labels[arg]) - PC;
      if (diff < 0) {
        argv[index] = (65536 - diff).toString(2);
      } else {
        argv[index] = diff.toString(2);
      }
    } else if (arg.match(/\d+\(%r\d+\)/)) {
      numbers = (arg.match(/\d+/g));

      argv[index] = (+numbers[1]).toString(2);
      argv.push((+numbers[0]).toString(2));
    } else if (arg.match(/%r\d+/)) {
      argv[index] = (+(arg.match(/\d+/))[0]).toString(2);
    } else if (arg.match(/-\d+/)) {
      var complement = (65536 - (+((arg.match(/\d+/))[0]))).toString(2);
      argv[index] = complement;
    } else if (arg.match(/\d+/)) {
      argv[index] = (+(arg.match(/\d+/))[0]).toString(2);
    }

  });
  return argv;
}

function processLabel(line) {
  var processedLine = line.replace(/,/g, '').split(/\s/);
  var instruction = processedLine[0];
  if (isLabel(instruction)) {
    registerLabel(instruction.substring(0, instruction.length - 1), lineCountForlabel);
  }
  lineCountForlabel++;
}

lineReaderForLabel.on('line', processLabel);

lineReaderForLabel.on('close', function () {
  var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('fib_edited.s')
  });
  lineReader.on('line', processLine);
  lineReader.on('close', function () {
    console.log(byteCode);

  });
});
