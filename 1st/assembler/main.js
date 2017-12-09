OPERATIONS = require('./opDef');
fsForLabel = require('fs');
var p = console.log;
var inputFile = process.argv[2]
var lineCountForlabel = 0;
var labels = {};
var data = [];
var PC = 0;
var byteCode = '';
var byteData = '';
var InLabelSection = false;
var InTextSection = false;
var InDataSection = false;

function processLine(line) {
  var processedLine = line.replace(/^\s+/,'').replace(/,/g, '').split(/\s/);
  var instruction = processedLine[0];
  if(instruction === '.global'){
    InTextSection = true;
    return;
  }
  if (InTextSection) {
    if (isComment(instruction)) {
      return;
    }
    if (isLabel(instruction)) {
    } else {
      if (instruction === 'j'||instruction === 'jal' || instruction === 'la') {
        byteCode += OPERATIONS[instruction](convertLine(processedLine.slice(1, processedLine.length),true));
      } else {
        if(OPERATIONS[instruction]===undefined){p(instruction);}
        else{
          byteCode += OPERATIONS[instruction](convertLine(processedLine.slice(1, processedLine.length)));
        }
      }
      PC++;
      if(instruction === 'la'){
        PC++;
      }
    }
  }
}

function isComment(instruction) {
  return instruction[0] === '#';
}

function isLabel(instruction) {
  return instruction[instruction.length - 1] === ':';
}

function registerLabel(label, PC) {
  labels[label] = PC;
}

function convertLine(argv,direct) {
  var numbers;
  if(direct){
    argv.forEach(function (arg, index) {
      if (!arg.match(/%(r|f)/) && arg.match(/[a-z]+/)) {
        argv[index] = (+labels[arg]).toString(2);
      } else if (arg.match(/\d+\(%r\d+\)/)) {
        numbers = (arg.match(/\d+/g));
        argv[index] = (+numbers[1]).toString(2);
        argv.push((+numbers[0]).toString(2));
      } else if (arg.match(/%(r|f)\d+/)) {
        argv[index] = (+(arg.match(/\d+/))[0]).toString(2);
      } else if (arg.match(/-\d+/)) {
        var complement = (65536 - (+((arg.match(/\d+/))[0]))).toString(2);
        argv[index] = complement;
      } else if (arg.match(/\d+/)) {
        argv[index] = (+(arg.match(/\d+/))[0]).toString(2);
      }
    });
    }
  else{
  argv.forEach(function (arg, index) {
    if (!arg.match(/%(r|f)/) && arg.match(/[a-z]+/)) {
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
    } else if (arg.match(/%(r|f)\d+/)) {
      argv[index] = (+(arg.match(/\d+/))[0]).toString(2);
    } else if (arg.match(/-\d+/)) {
      var complement = (65536 - (+((arg.match(/\d+/))[0]))).toString(2);
      argv[index] = complement;
    } else if (arg.match(/\d+/)) {
      argv[index] = (+(arg.match(/\d+/))[0]).toString(2);
    }

  });}
  return argv;
}
function processData(line){
  var processedLine = line.replace(/^\s+/,'').replace(/,/g, '').split(/\s/);
  var token = processedLine[0];
  if(token === '.align'){
    InDataSection = true;
    return;
  } else if(InDataSection && token === '.section') {
    InDataSection = false;
  }
  if (InDataSection) {
    if(isLabel(token)){
      token = token.slice(0, token.length - 1);
      data.push({label: token, data:[]});
    } else {
      data[data.length-1].data.push(+token);
    }
  }
  return 0;
}
function processLabel(line) {
  var processedLine = line.replace(/^\s+/,'').replace(/,/g, '').split(/\s/);
  var instruction = processedLine[0];
  if(instruction === '.global'){
    InLabelSection = true;
    return;
  }
  if (InLabelSection) {
    if (isComment(instruction)) {
      return;
    }
    if (isLabel(instruction)) {
      registerLabel(instruction.substring(0, instruction.length - 1), lineCountForlabel);
    }else {
      lineCountForlabel++;
      if (instruction === 'la') {
        lineCountForlabel++;
      }
    }
  }
}
function writeData(){
  data.forEach(function(pair){
    pair.data.forEach(function(data){
      byteData += ('0'.repeat(32)+(data).toString(2)).slice(-32);
    })
  });
  require('fs').writeFile(inputFile.replace('.s','') + '_data.dat', byteData, function(err) {
    if(err) {
      return console.log(err);
    }
  });
}
function makeData(){
  var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream(inputFile)
  });
  lineReader.on('line', processData);
  lineReader.on('close', makeLabel);
}
function makeLabel(){
  var count = 0;
  data.forEach(function(pair){
    registerLabel(pair.label,count);
    count += pair.data.length;
  });
  var lineReaderForLabel = require('readline').createInterface({
    input: require('fs').createReadStream(inputFile)
  });
  lineReaderForLabel.on('line', processLabel);
  lineReaderForLabel.on('close',makeText);
}
function makeText() {
  p(labels);
  var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream(inputFile)
  });
  lineReader.on('line', processLine);
  lineReader.on('close', function () {
    writeData();
    require('fs').writeFile(inputFile.replace('.s','') + '_text.dat', byteCode+'1'.repeat(32), function(err) {
      if(err) {
        return console.log(err);
      }
    });
  });
}
 makeData();
function cheack32(){
    if(OPERATIONS[instruction](convertLine(processedLine.slice(1, processedLine.length))).length!==32){
      p(`${instruction} is wrong`);
    }
}
