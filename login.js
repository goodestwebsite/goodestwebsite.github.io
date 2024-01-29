<script src="/cookie.js"></script>

function logout(){
    deletecookie() ;
    if (getCookie("username") == -1) document.getElementById("sign").innerHTML = "You haven't signed in!" ;
    else document.getElementById("sign").innerHTML = "Sucessfully logged out." ;
}