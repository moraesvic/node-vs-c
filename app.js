const Path = require('path');
const Minim = require('minimist');

const C_BINARY = Path.join(__dirname, 'C/shuffle_and_sort.so');

var ref = require("ref");
var ffi = require("ffi");

async function main(){
    const argv = Minim(process.argv.slice(2));

    const help = argv.help || false;
    if(help){
        console.log("Usage: node app.js [--js --ctxt --cbin --casync / --all] [--print / --fullprint] -n SIZE_OF_ARRAY");
        return;
    }

    let size_input = Number(argv.n) || 10000;
    let max = 0x7fffffff;

    const intPtr = ref.refType('int');
    const cLib = ffi.Library(C_BINARY, {shuffle_and_sort: 
             ['void', ['int', intPtr, 'int']]});
    const buf = Buffer.alloc(4 * size_input);
    cLib.shuffle_and_sort(size_input, buf, max);
    
    /* no need for garbage collection */
}

main();