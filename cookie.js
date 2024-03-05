function setcookie(cookiename, cookievalue){
  document.cookie = cookiename + "=" + cookievalue + ";path=/" ;
}
function deletecookie(){
  document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
}
function getCookie(cname) {
  let name = cname + "=";
  let ca = document.cookie.split(';');
  for(let i = 0; i < ca.length; i++) {
    let c = ca[i];
    while (c.charAt(0) == ' ') {
      c = c.substring(1);
    }
    if (c.indexOf(name) == 0) {
      return c.substring(name.length, c.length);
    }
  }
  return "";
}
function getusername(){
  if (getCookie("username") == "") document.getElementById("username").innerHTML = "not signed in" ;
  else document.getElementById("username").innerHTML = "Signed in as : " + getCookie("username") ;
  return getCookie("username") ;
}
// thanks to https://www.w3schools.com/js/js_cookies.asp