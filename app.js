const Path = require('path');
const TeenPr = require('teen_process');
const Minim = require('minimist');
const { once } = require('events');

const C_BINARY = Path.join(__dirname, 'bin/binary');
const C_TEXT = Path.join(__dirname, 'bin/text');

/* Maximum value for the integers in the array */
const MAX_INT = 0x7fffffff;

/* Number of entries to show in shortPrint() */
const HEAD = 5;
const TAIL = 5;

/* ANSI escape codes for pretty-printing */
const TERM_RED = "\x1b[0;31m";
const TERM_BOLD_RED = "\x1b[1;31m";
const TERM_RESET = "\x1b[0;0m";

/* Internal control codes */
const NOPRINT    = 0;
const SHORTPRINT = 1;
const FULLPRINT  = 2;

function shortPrint(v){
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

function fullPrint(v){
  console.log('[%s', TERM_RED);
  for(let i = 0; i < v.length; i++)
    console.log('  %d', v[i]);
  console.log('%s]', TERM_RESET);
}

async function timer(fn, size_input, print_sorted){
  const start = new Date();
  const v = await fn(size_input);
  const duration = new Date() - start;
  if(print_sorted === SHORTPRINT) 
    shortPrint(v); 
  else if(print_sorted === FULLPRINT)
    fullPrint(v);
  console.log(`Code executed in ${duration} ms\n`);
  return duration;
}

function jsCreateAndSort(size_input){
  let v = [];
  for(var i = 0; i < size_input; i++)
    v.push(Math.floor( Math.random() * MAX_INT ));
  v.sort((a,b) => a - b);

  return v;
}

async function cText(size_input){
  let out = await TeenPr.exec(`${C_TEXT}`,
          [ size_input ]);
  let v = out.stdout.replace(' \n', '').split(' ').map(x => Number(x));  
  return v;
}

async function cBinary(size_input){
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

async function asyncCBinary(size_input){
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
  if(help){
    console.log("Usage: node app.js [--js --ctxt --cbin --casync / --all] [--print / --fullprint] -n SIZE_OF_ARRAY");
    return;
  }

  let size_input = Number(argv.n) || 10000;
  let print_sorted = NOPRINT;
  if(argv.print)
    print_sorted = SHORTPRINT;
  if(argv.fullprint)
    print_sorted = FULLPRINT;

  let js = argv.js || false;
  let ctxt = argv.ctxt || false;
  let cbin = argv.cbin || false;
  let casync = argv.casync || false;
  let all = argv.all || false;

  if(!js && !ctxt && !cbin && !casync && !all)
    all = true;

  if(all){
    js = true; ctxt = true; cbin = true; casync = true; }

  console.log(`Creating and sorting random array with ${size_input} integers, from 0 to ${MAX_INT}`);
  console.log(`We are running in ${process.env.NODE_ENV || "development"} mode.\n`);
  
  let jstime;
  let ctxttime = cbintime = casynctime = Infinity;

  if(js){
    console.log('JAVASCRIPT');
    jstime = await timer(jsCreateAndSort, size_input, print_sorted); }
  if(ctxt){
    console.log('C-Text');
    ctxttime = await timer(cText, size_input, print_sorted); }
  if(cbin){
    console.log('C-Binary (via buffer)');
    cbintime = await timer(cBinary, size_input, print_sorted); }
  if(casync){
    console.log('async C-Binary (via buffer)');
    casynctime = await timer(asyncCBinary, size_input, print_sorted); }

  if(process.env.NODE_ENV == 'production' && js && (ctxt || cbin || casync)){
    let ratio = Math.round(Math.min(ctxttime, cbintime, casynctime)
                  / jstime * 100.0);
    console.log(`${TERM_BOLD_RED}Best C processed in ${ratio}% of JS's time${TERM_RESET}`);
  }
}

main();