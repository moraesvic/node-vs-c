
const Path = require('path');
const TeenPr = require('teen_process');
const Minim = require('minimist');
const { once } = require('events');

const C_BINARY = Path.join(__dirname, 'bin/binary');
const C_TEXT = Path.join(__dirname, 'bin/text');
const MAX_INT = 0x7fffffff;
const HEAD = 10;
const TAIL = 10;

const TERM_RED = "\x1b[31m";
const TERM_RESET = "\x1b[0m";

function printLongArray(v){
  let head = v.slice(0, HEAD);
  let tail = v.slice(v.length - TAIL, v.length);

  console.log('[%s', TERM_RED);
  for(let i = 0; i < head.length; i++)
    console.log('  %d', head[i]);

  console.log('%s  ... %d elements ... %s', TERM_RESET,
              v.length - HEAD - TAIL, TERM_RED);

  for(let i = 0; i < tail.length; i++)
    console.log('  %d', tail[i]);

  console.log('%s]', TERM_RESET);
}

function printFullArray(v){
  console.log('[%s', TERM_RED);
  for(let i = 0; i < v.length; i++)
    console.log('  %d', v[i]);
  console.log('%s]', TERM_RESET);
}

async function timer(fn, size_input, print_sorted){
  const start = new Date();
  const v = await fn(size_input, print_sorted);
  const duration = new Date() - start;
  if(print_sorted)  printLongArray(v); 
  console.log(`Code executed in ${duration} ms\n`);
}

function jsCreateAndSort(size_input, print_sorted){
  let v = [];
  for(var i = 0; i < size_input; i++)
    v.push(Math.floor( Math.random() * MAX_INT ));
  v.sort((a,b) => a - b);

  return v;
}

async function cText(size_input, print_sorted){
  let out = await TeenPr.exec(`${C_TEXT}`,
          [ size_input ]);
  let v = out.stdout.replace(' \n', '').split(' ').map(x => Number(x));  
  return v;
}

async function asyncCText(size_input, print_sorted){
  const proc = TeenPr.spawn(`${C_TEXT}`, [ size_input ]);

  var v = [];
  var temp = ''
  
  proc.stdout.on('data', (data) => {
    let str = data.toString();
    let strArray = str.replace(' \n', '').split(' ');

    strArray[0] = temp + strArray[0];
    
    if(str[str.length - 1] !== ' ' && str[str.length - 1] !== '\n'){
      temp = strArray[strArray.length - 1];
      strArray.splice(strArray.length - 1);
    }
    else
      temp = '';

    for(let i = 0; i < strArray.length; i++)
      if(strArray[i] == '')
        strArray.splice(i,i--);

    let numarray = strArray.map(x => Number(x));
    v = v.concat(numarray);
  });
  
  await once(proc.stdout, 'close');
  return v;
}

async function cBinary(size_input, print_sorted){
  const out = await TeenPr.exec(`${C_BINARY}`,
          [ size_input ],
          {encoding: 'binary',
           isBuffer: true});

  const buf = out.stdout;
  let v = [];
  for(var i = 0; i < buf.length; i += 4)
    v.push(buf.readInt32LE(i));

  return v;
}

async function asyncCBinary(size_input, print_sorted){
  const proc = TeenPr.spawn(`${C_BINARY}`, [ size_input ]);

  let v = [];
  
  proc.stdout.on('data', (data) => {
    for(let i = 0; i < data.length; i += 4)
      v.push(data.readInt32LE(i));
  });

  await once(proc.stdout, 'close');
  return v;
}

async function main(){
  const argv = Minim(process.argv.slice(2));

  const help = argv.help || false;
  const size_input = argv.n || 10000;

  if(help || typeof(size_input) !== Number){
    console.log("Usage: node app.js [--js --ctxt --cbin --casync / --all] -n SIZE_OF_ARRAY");
    return;
  }

  
  const print_sorted = argv.print || false;

  var js = argv.js || false;
  var ctxt = argv.ctxt || false;
  var cbin = argv.cbin || false;
  var casync = argv.casync || false;
  var all = argv.casync || false;

  if(!js && !ctxt && !cbin && !casync && !all)
    all = true;

  if(all){
    js = true; ctxt = true; cbin = true; casync = true;
  }


  console.log(`Creating and sorting random array with ${size_input} integers, from 0 to ${MAX_INT}`);
  console.log(`We are running in ${process.env.NODE_ENV || "development"} mode.\n`);
  
  if(js){
    console.log('JAVASCRIPT');
    await timer(jsCreateAndSort, size_input, print_sorted); }
  if(ctxt){
    console.log('C-Text');
    await timer(cText, size_input, print_sorted); }
  if(cbin){
    console.log('C-Binary (via buffer)');
    await timer(cBinary, size_input, print_sorted);
  }
  if(casync){
    console.log('async C-Binary (via buffer)');
    await timer(asyncCBinary, size_input, print_sorted);
  }
}

main();