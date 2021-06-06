
const path = require('path');
const TeenPr = require('teen_process');

const C_BINARY = path.join(__dirname, 'bin/binary');
const C_TEXT = path.join(__dirname, 'bin/text');

const SIZE_INPUT = 10000000;
const MAX_INT = 0x7fffffff;
const WRITE_SORTED = false;


async function timer(fn){
  const start = new Date();
  await fn();
  const duration = new Date() - start;
  console.log(`Code executed in ${duration} ms\n`);
}

function jsCreateAndSort(){
  var v = [];
  for(var i = 0; i < SIZE_INPUT; i++)
    v.push(Math.floor( Math.random() * MAX_INT ));
  v.sort((a,b) => a - b);
  if(WRITE_SORTED) console.log(v);
}

function printasbin(str){
  /* PLEASE DON'T DO IT */
  for(var i = 0; i < str.length; i++)
    process.stdout.write(`${str.charCodeAt(i)} `);
  console.log('');
}

async function cBinary(){
  let out = await TeenPr.exec(`${C_BINARY}`,
          [ SIZE_INPUT ],
          {encoding: 'binary'});

  let buf = Buffer.from(out.stdout,'binary');

  var v = [];
  for(var i = 0; i < SIZE_INPUT * 4; i += 4)
    v.push(buf.readInt32LE(i));

  if(WRITE_SORTED)
    console.log(v);
}

async function cText(){
  let out = await TeenPr.exec(`${C_TEXT}`,
          [ SIZE_INPUT ]);

  let buf = Buffer.from(out.stdout,'binary');

  var strarray = out.stdout.replace(' \n', '');
  strarray = strarray.split(' ');
  var numarray = strarray.map(x => Number(x));
  
  if( WRITE_SORTED)
    console.log(numarray);
}

/* Sorting functions, rewritten in JS */

function insert_sort(v){
  var i, j, temp;
  for(j = 1; j < v.length; j++){
    temp = v[j];
    for(i = j-1; i >= 0 && v[i] > temp; i--)
      v[i+1] = v[i];
    v[i+1] = temp;
  }
}

/* */

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