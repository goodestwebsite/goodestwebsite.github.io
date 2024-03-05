function read(){
    // console.log("oklol") ;
    var fs = require('fs')
    // document.getElementById("x").innerHTML="ok" ;
    fs.appendFile('test.txt', 'f aefesfcf tex', function (err) {
        if (err) throw err;
        console.log('Updated!');
    });
}
