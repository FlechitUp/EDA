function Point (_x, _y){
        this.x = _x;
        this.y = _y;
    /*Point(){
        x = 0;
        y = 0;
    }*/
}

function Node(pointLeftTop, pointBotRig, hI, wI){
        this.PLeftTop = pointLeftTop;        
        this.PBotRig = pointBotRig;
        this.myHI = hI;
        this.myWI = wI;
        this.data = []; //data hasta que exceda el Threshold  ,
                        //contenide de data: Points
}
    
Node.prototype.setData = function (pointI){
        this.data.push(pointI);
}

Node.prototype.getPleftTop = function(){
    return this.PLeftTop.x;
}