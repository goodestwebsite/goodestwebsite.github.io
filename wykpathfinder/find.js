const paths = new Map([
    ["109", ["110", "Main Building stair(1/f)"]],
    ["110", ["109", "111"]],
    ["111", ["110", "112"]],
    ["112", ["111", "113"]],
    ["113", ["112", "114"]],
    ["114", ["113", "115"]],
    ["115", ["114", "116"]],
    ["116", ["115", "Main - Law Ting Pong Building stair(1/f)"]],
    ["Main - Law Ting Pong Building stair(1/f)", ["116"]],
    ["Main Building stair(1/f)", ["109"]]
]) ;



function load(){
    const arr = Array.from(paths.keys()) ;
    for (var i = 0 ; i < arr.length ; i += 1){
        var z = document.createElement("option");
        z.setAttribute("value", arr[i]);
        var t = document.createTextNode(arr[i]);
        z.appendChild(t);
        document.getElementById("start").appendChild(z);
    }
    for (var i = 0 ; i < arr.length ; i += 1){
        var z = document.createElement("option");
        z.setAttribute("value", arr[i]);
        var t = document.createTextNode(arr[i]);
        z.appendChild(t);
        document.getElementById("destination").appendChild(z);
    }
}
function findpath(){
    var st=(document.getElementById("start").value) ;
    var en=(document.getElementById("destination").value) ;
    var q=[] ;
    document.getElementById("route").innerHTML = st ;
    var visited = new Map() ;
    var s = new Map() ;
    s.set(st, st) ;
    q.push(st) ;
    visited.set(st, 1) ;
    while (q.length >= 1){
        var x = q[0] ;
        q.splice(0, 1) ;
        var i=0, pth=paths.get(x) ;
        while (i < pth.length){
            if (visited.get(pth[i]) != 1){
                visited.set(pth[i], 1) ;
                s.set(pth[i], s.get(x) + " -> <br>" + pth[i]) ;
                q.push(pth[i]) ;
            }
            i += 1 ;
        }
    }
    document.getElementById("route").innerHTML = s.get(en) ;
    
}