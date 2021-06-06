
const path = require('path');
const TeenPr = require('teen_process');

const C_BINARY = path.join(__dirname, 'bin/binary');
const C_TEXT = path.join(__dirname, 'bin/text');

const SIZE_INPUT = 1000;
const MAX_INT = 0x7fffffff;
const WRITE_SORTED = false;

async function timer(fn){
  const start = new Date();
  await fn();
  const duration = new Date() - start;
  console.log(`Code executed in ${duration} ms\n`);
}

function jsCreateAndSort(){
  let v = [];
  for(var i = 0; i < SIZE_INPUT; i++)
    v.push(Math.floor( Math.random() * MAX_INT ));
  v.sort((a,b) => a - b);
  if(WRITE_SORTED) console.log(v);
}

async function cBinary(){
  const out = await TeenPr.exec(`${C_BINARY}`,
          [ SIZE_INPUT ],
          {encoding: 'binary'});

  const buf = Buffer.from(out.stdout,'binary');
  let v = [];

  for(var i = 0; i < SIZE_INPUT * 4; i += 4)
    v.push(buf.readInt32LE(i));

  if(WRITE_SORTED)
    console.log(v);
}

async function cText(){
  let out = await TeenPr.exec(`${C_TEXT}`,
          [ SIZE_INPUT ]);

  let buf = Buffer.from(out.stdout,'binary');

  let strarray = out.stdout.replace(' \n', '');
  strarray = strarray.split(' ');
  let numarray = strarray.map(x => Number(x));
  
  if( WRITE_SORTED)
    console.log(numarray);
}

async function main(){
  console.log(`Creating and sorting random array with ${SIZE_INPUT} integers, from 0 to ${MAX_INT}\n`);
  console.log('JAVASCRIPT');
  await timer(jsCreateAndSort);
  console.log('C-Text');
  await timer(cText);
  console.log('C-Binary (via buffer)');
  await timer(cBinary);
}

main();