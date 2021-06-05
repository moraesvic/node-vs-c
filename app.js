const express = require('express');
const path = require('path');
const ChildPr = require('childprocess');

const app = express();
const BIN = path.join(__dirname, 'bin/');

/* https://stackoverflow.com/questions/20643470/execute-a-command-line-binary-with-node-js */

app.get('/', function(req, res){
  res.send('ok');
});

const PORT = process.env.PORT || 5000

app.listen(PORT, function(req,res){
    console.log('Listening on port ' + PORT + '...');
});