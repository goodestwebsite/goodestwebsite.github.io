var usarr = ["if1plus1is3"  , "user1"   , "user2"   , "user3"] ;
var psarr = ["aba"          , "123"     , "234"     , "345"  ] ;
function read(){
    // deletecookie() ;
    var usern = getCookie("username") ;
    if (usern != ""){
        // document.getElementById("showtext").innerHTML = usern ;
        return ;
    }
    var us = document.getElementById("usernameinput").value ;
    var pa = document.getElementById("password").value ;
    for (var i = 0 ; i < usarr.length ; i ++){
        if (usarr[i] == us && psarr[i] == pa){
            document.getElementById("showtext").innerHTML = "login sucessful" ;
            setcookie("username", us) ;
            return ;
        }
    }
    document.getElementById("showtext").innerHTML = "Wrong username or password";//"Wrong username or password" ;


}
function checkson(){
    if (getCookie("username") != "") document.getElementById("showtext").innerHTML = "You have already signed in!"
}
function test(){
    setcookie("username", "-1") ;
}