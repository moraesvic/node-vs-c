
const path = require('path');
const TeenPr = require('teen_process');

const BIN = path.join(__dirname, 'bin/main');

const SIZE_INPUT = 10;
const MAX_INT = 0x7fffffff;
const WRITE_SORTED = true;


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

async function cCreateAndSort(){
  let out = await TeenPr.exec(`${BIN}`,
          [ SIZE_INPUT ]);

  var v = [];
  var item;
  for(var i = 0; i < SIZE_INPUT * 4; i += 4){
    item = 0x00000001 * out.stdout.charCodeAt(i)
         + 0x00000100 * out.stdout.charCodeAt(i+1)
         + 0x00010000 * out.stdout.charCodeAt(i+2)
         + 0x01000000 * out.stdout.charCodeAt(i+3);
    v.push(item);
  }

  console.log(v);
  /*
  var strarray = out.stdout.replace(' \n', '');
  strarray = strarray.split(' ');
  var numarray = strarray.map(x => Number(x));
  
  if(OUTPUT_STDOUT && WRITE_SORTED) console.log(numarray);
  */
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
  console.log('C');
  await timer(cCreateAndSort);
}

main();