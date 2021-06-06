
const Path = require('path');
const TeenPr = require('teen_process');
const Minim = require('minimist');

const C_BINARY = Path.join(__dirname, 'bin/binary');
const C_TEXT = Path.join(__dirname, 'bin/text');
const MAX_INT = 0x7fffffff;

async function timer(fn, size_input, print_sorted){
  const start = new Date();
  await fn(size_input, print_sorted);
  const duration = new Date() - start;
  console.log(`Code executed in ${duration} ms\n`);
}

function jsCreateAndSort(size_input, print_sorted){
  let v = [];
  for(var i = 0; i < size_input; i++)
    v.push(Math.floor( Math.random() * MAX_INT ));
  v.sort((a,b) => a - b);
  if(print_sorted) console.log(v);
}

async function cText(size_input, print_sorted){
  let out = await TeenPr.exec(`${C_TEXT}`,
          [ size_input ]);

  let buf = Buffer.from(out.stdout,'binary');

  let strarray = out.stdout.replace(' \n', '');
  strarray = strarray.split(' ');
  let numarray = strarray.map(x => Number(x));
  
  if( print_sorted)
    console.log(numarray);
}

async function cBinary(size_input, print_sorted){
  const out = await TeenPr.exec(`${C_BINARY}`,
          [ size_input ],
          {encoding: 'binary'});

  const buf = Buffer.from(out.stdout,'binary');
  let v = [];

  for(var i = 0; i < size_input * 4; i += 4)
    v.push(buf.readInt32LE(i));

  if(print_sorted)
    console.log(v);
}



async function main(){
  const argv = Minim(process.argv.slice(2));

  const size_input = argv.n || 10000;
  const print_sorted = argv.print || false;

  console.log(`Creating and sorting random array with ${size_input} integers, from 0 to ${MAX_INT}\n`);
  console.log('JAVASCRIPT');
  await timer(jsCreateAndSort, size_input, print_sorted);
  console.log('C-Text');
  await timer(cText, size_input, print_sorted);
  console.log('C-Binary (via buffer)');
  await timer(cBinary, size_input, print_sorted);
}

main();