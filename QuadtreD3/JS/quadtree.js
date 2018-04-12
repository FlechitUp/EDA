class quadTree {    
    //Point topLeft;
    //Point botRight;
    //var cantPoints = []; //[Point*] por cantidad de puntos
    //var sons = [] ;// <quadTree*> [0]arribaIzq, [1] arrDerec , [2] abajoIzq, [3]abajoDer
    //var cont;
    
    constructor(topL, botR){            
        this.cantPoints = [];
        this.sons = [];
        this.topLeft = topL; //punto
        this.botRight = botR; //punto
        this.cont = 0;
        this.myh=h;
        this.myw=w;
        for (var i=0 ; i<4 ; i++ ){
            this.sons.push(null);
        }        
    };
            
    enQuad(pointI){        
        return (pointI.x >= this.topLeft.x &&
                pointI.x <= this.botRight.x &&
                pointI.y <= this.topLeft.y &&
                pointI.y >= this.botRight.y);
    }
            
    find(pointI){
        if(!this.enQuad(pointI)){
            console.log("El punto no esta en los limites");
            return false;
        }
        if(this.findPointInvect(pointI)){
            return true;
        }
        //printLimites();
        //si esta en la izquierda
        if ((this.topLeft.x + this.botRight.x) / 2 >= pointI.x){

            if ((this.topLeft.y + this.botRight.y) / 2 <= pointI.y){   //esta arriba / en sons[0]
                console.log(" 0 - ");                
                //printLimites();
                if(this.sons[0]==null){
                    return this.findPointInvect(pointI);
                }
                return this.sons[0].find(pointI);
            }
            else{                                       //esta abajo / en sons[1]
                console.log(" 2 - ");
                //printLimites();
                if(this.sons[2]==null){
                    return this.findPointInvect(pointI);
                }
                return this.sons[2].find(pointI);
            }
        }
        else{  //esta en el lado derecho
            if ((this.topLeft.y + this.botRight.y) / 2 <= pointI.y){   //esta arriba / en sons[1]
                console.log(" 1 - ");
                //printLimites();
                if (this.sons[1] == null){
                    return this.findPointInvect(pointI);
                }
                return this.sons[1].find(pointI);;
            }
            else{                                  //esta abajo / en sons[3]
                console.log(" 3 - ");
                //printLimites();
                if (this.sons[3] == null){
                    return this.findPointInvect(pointI);
                }
                return this.sons[3].find(pointI);
            }
        }
    }
            
    findPointInvect(pointI){    
        this.cantPoints.forEach( function(d){
            //console.log("emtre");
            if(d.x == pointI.x && d.y == pointI.y){
                console.log("findPointInvect true" );
                return true;
            }    
        });
        
        /*for (var i=0; i< this.cantPoints.length ; i++){
            console.log("emfor");
            if (this.cantPoints[i].x == pointI.x && this.cantPoints[i].y == pointI.y){
                console.log("findPointInvect true" );
                return true;
            }
        }*/
        
        return false;
    }
            
    insert(pointI){
        
        if(!this.enQuad(pointI)){  //*pointI
            console.log(" punto " ,pointI.x ,",",pointI.y ," No Pertenece a quad");
            return;
        }
        else {            
           console.log("pushi ",pointI.x," , ", pointI.y);
            if(this.find(pointI) == true){
                console("Punto ya ingresado");
                return false;
            }
            else {
            //if(parseInt(this.cantPoints.length)<=threShold && this.findPointInvect(pointI) == false){   //si no encuentra el pto en el array del nodo
                //console.log("findPointInvect F  ");
                this.cantPoints.push(pointI);
                this.cont ++;
            //}
           // else{
            //alert("ok "+parseInt(this.cantPoints.length) );
            if(parseInt(this.cantPoints.length) > threShold && this.cont>threShold ){
                console.log("reordenar");
                cortarEnCuatro(this.myh,this.myw);
                //this.cantPoints.forEach(function(d,iter){                        
                  
                for(var i = 0 ; i < parseInt(this.cantPoints.length) ; i++){
                    /// si esta en el lado izquierd
                    if ((this.topLeft.x + this.botRight.x) / 2 >= this.cantPoints[i].x){    //pointI->x
                        //Si esta arriba a la izquierda
                        if ((this.topLeft.y + this.botRight.y) / 2 <= this.cantPoints[i].y){
                            console.log("  sons[0] ");
                            if (this.sons[0] == null){ //sons[0] topLeftTree
                                this.sons[0] = new quadTree(
                                    new Point(this.topLeft.x, this.topLeft.y),
                                    new Point((this.topLeft.x + this.botRight.x) / 2,
                                              (this.topLeft.y + this.botRight.y) / 2));
                            }
                            //alert("recuri");
                            return this.sons[0].insert(this.cantPoints[i]);
                        }
                            
                        // si esta en la izquierda abajo
                            else{
                                if (this.sons[2]  == null){
                                    this.sons[2]  = new quadTree(  //sons[2] botLeftTree
                                        new Point(this.topLeft.x,(this.topLeft.y + this.botRight.y) / 2),
                                        new Point((this.topLeft.x + this.botRight.x) / 2,this.botRight.y));
                                }
                                //alert("recuri");
                                return this.sons[2].insert(this.cantPoints[i]);
                            }
                        }
                        else{
                            // si esta arriba a la derecha
                            if ((this.topLeft.y + this.botRight.y) / 2 <= this.cantPoints[i].y){
                                console.log("  sons[1] ");
                                if (this.sons[1] == null){ //sons[1] topRightTree
                                    this.sons[1] = new quadTree(
                                        new Point((this.topLeft.x + this.botRight.x) /  2,this.topLeft.y),
                                        new Point(this.botRight.x,(this.topLeft.y + this.botRight.y) /  2));
                                }
                                //alert("recuri");
                                return this.sons[1].insert(this.cantPoints[i]);
                            }
                            
                            ///si esta abajo a la derecha
                            else{
                                if (this.sons[3] == null){
                                    console.log("  sons[3] ");
                                    this.sons[3] = new quadTree( //sons[3] botRightTree
                                        new Point((this.topLeft.x + this.botRight.x) / 2,   (this.topLeft.y + this.botRight.y) / 2),
                                        new Point(this.botRight.x, this.botRight.y));
                                }
                                //alert("recuri");
                                this.sons[3].insert(this.cantPoints[i]);
                            }
                        }
                    }//);
                    this.cantPoints =[];
                }
            }
            //}
        }
                
    } //(Point*)
            
    setParameters(a,b){
        this.topLeft = a;
        this.botRight = b;                
    }
    
    /*void readFile(string);*/
    printLimites(){
        console.log("Limit Quad: (", this.topLeft.x, ",",this.topLeft.y,")  (",this.botRight.x,",   ",this.botRight.y," )");
    }
}
       

function cortarEnCuatro(hI,wI){
    svg.append("line")
        .attr("x1",margin.left)
        .attr("y1",hI/2+margin.top)
        .attr("x2",wI-margin.right)
        .attr("y2",hI/2+margin.top)
        .style("stroke","red");
    svg.append("line")
        .attr("x1",wI/2+margin.left)
        .attr("y1",margin.top)
        .attr("x2",wI/2+margin.left)
        .attr("y2",hI-margin.bottom)
        .style("stroke","red");
}   