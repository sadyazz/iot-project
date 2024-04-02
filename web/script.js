function promijeniSvjetlo(idSvjetla) {
    var svjetlo = document.getElementById(idSvjetla);
    if (svjetlo.src.endsWith("light-off.png")) {
        svjetlo.src = "img/light-on.png";
    } else {
        svjetlo.src = "img/light-off.png";
    }

    //document.getElementById('light1').src='img/light-on.png';
}