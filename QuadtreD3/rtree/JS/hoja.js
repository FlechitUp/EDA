var THRESHOLD = 5;

function Point (_x, _y){
        this.x = _x;
        this.y = _y;
    /*Point(){
        x = 0;
        y = 0;
    }*/
}

function Hoja (mypoint){
     this.data = []; //data hasta que exceda el Threshold  ,
                        //contenide de data: Points
}

function Nodo(){
    this.myData = [];
    this.chidren = []; // O Nodos u hoja
    this.padre = null; //Nodo
    this.Rectangle; 
    
        this.area;
        this.pointIzqArr; //Point
        this.pointDerAba; //Point
}

Nodo.prototype.setData= function(mypoint){
    
}

function setThreshold(){
    THRESHOLD =  document.getElementById('thresoldInp').value    
    //console.log("threshold "+ threshold);
}

function primtcor(msg, acor){
    if(acor == 1){
        return console.log('%c '+msg, 'background: #222; color: #bada55');    
    }
    if(acor == 2){
        return console.log('%c '+msg, 'background: #0c8e5c; color: #f8f8f8');
    }
    if(acor == 3){
        return console.log('%c '+msg, 'background: #ff0b69; color: #f8f8f8');
    }
    else{
        console.log('%c '+msg, 'background: #b40499; color: #ffffff');
    }    
}