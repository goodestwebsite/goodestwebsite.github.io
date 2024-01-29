function read(){
    var fs = require('fs')
    document.getElementById("x").innerHTML="ok" ;
    fs.writeFile('test.txt', 'Append tex', function (err) {
        if (err) throw err;
        console.log('Updated!');
    });
}
