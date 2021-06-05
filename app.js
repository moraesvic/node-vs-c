const express = require('express');
const path = require('path');

const BIN = path.join(__dirname, 'bin/');

app.get('/', function(req, res){

});

const PORT = process.env.PORT || 5000

app.listen(PORT, function(req,res){
    console.log('Listening on port ' + PORT + '...');
});