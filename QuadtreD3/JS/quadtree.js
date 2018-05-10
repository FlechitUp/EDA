var MYCOR = "red";
var MYCOR2 = "blue";
function cortar4(PLeftTop,PBotRig){
        //primtcor("limha",1);
        svg.append("line")  //horizontal
            .attr("x1", xScale(PLeftTop.x))
            .attr("y1", yScale((PBotRig.y+PLeftTop.y)/2))
            .attr("x2", xScale(PBotRig.x))
            .attr("y2", yScale((PBotRig.y+PLeftTop.y)/2))
            .style("stroke",MYCOR);
        
        svg.append("line")  //vertical
            .attr("x1", xScale((PBotRig.x+PLeftTop.x)/2))
            .attr("y1", yScale(PLeftTop.y))
            .attr("x2", xScale((PBotRig.x+PLeftTop.x)/2))
            .attr("y2", yScale(PBotRig.y))
            .style("stroke",MYCOR);   
    MYCOR = MYCOR2;
    
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

function quadTree(topL,botR,hI,wI){            
    this.RootNode = new Node(topL,botR,hI,wI);        
    this.boolHOJAS_T_F = false;
    this.sons = []; //4 hijas   contenid: quadTrees        
    for (var i=0 ; i<4 ; i++ ){
        this.sons.push(null);
    }       
}
            
    quadTree.prototype.enQuad = function(pointI){
        ///primtcor("ok",1);
        return Boolean(pointI.x >= this.RootNode.PLeftTop.x &&
            pointI.x <= this.RootNode.PBotRig.x &&
            pointI.y <= this.RootNode.PLeftTop.y &&
            pointI.y >= this.RootNode.PBotRig.y)       
        //return false;
    };
    
    /*quadTree.prototype.cortar4 = function(){
        primtcor("limha",1);
        svg.append("line")  //horizontal
            .attr("x1", xScale(this.RootNode.PLeftTop.x))
            .attr("y1", yScale((this.RootNode.PBotRig.y+this.RootNode.PLeftTop.y)/2))
            .attr("x2", xScale(this.RootNode.PBotRig.x))
            .attr("y2", yScale((this.RootNode.PBotRig.y+this.RootNode.PLeftTop.y)/2))
            .style("stroke","red");
        
        svg.append("line")  //vertical
            .attr("x1", xScale((this.RootNode.PBotRig.x+this.RootNode.PLeftTop.x)/2))
            .attr("y1", yScale(this.RootNode.PLeftTop.y))
            .attr("x2", xScale((this.RootNode.PBotRig.x+this.RootNode.PLeftTop.x)/2))
            .attr("y2", yScale(this.RootNode.PBotRig.y))
            .style("stroke","red");
        */
        
       /* 
        svg.append("line")  //horizontal
            .attr("x1", this.topLeft.x)
            .attr("y1", (this.botRight.y-this.topLeft.y)/2)
            .attr("x2", this.botRight.x)
            .attr("y2",(this.botRight.y-this.topLeft.y)/2)
            .style("stroke","red");
        
        svg.append("line")  //vertical
            .attr("x1", (this.botRight.x-this.topLeft.x)/2)
            .attr("y1", this.topLeft.y)
            .attr("x2", (this.botRight.x-this.topLeft.x)/2)
            .attr("y2", this.botRight.y)
            .style("stroke","red");*/
    //}
         
    
    quadTree.prototype.find = function(pointI){ //OUTPUT BOOL        
        if(!this.enQuad(pointI)){
            primtcor("No",2);
            return false;
        }
        else{
            primtcor("si",2);
            if(this.boolHOJAS_T_F==false){
                primtcor("No hay hojas",2);
                return this.findPointInvect(pointI);
            }
            else{
                primtcor("hay hojas",2);                
                for(var f = 0; f< this.sons.length ; f++){
                    if(this.sons[f]!=null){
                        if (this.sons[f].find(pointI)){
                            MYARRSEARCH.push(f);
                            console.log(f+" ");
                            return true;
                        }
                    }
                }return false;            
            }
        }
    }
   
            
    quadTree.prototype.findPointInvect = function(pointI){                
        for(var j = 0 ; j < this.RootNode.data.length ;  j++){
            if(this.RootNode.data[j].x == pointI.x && this.RootNode.data[j].y == pointI.y){               
                return true;
            }    
        }
        //);        
        return false;
    }
            
    quadTree.prototype.insert = function(pointI){  //OUTPUT BOOL 
        
        if (!this.enQuad(pointI)){ //si NO esta em los limites            
            primtcor("out of limit",2);
            return false;
        }
        
        else {
            if(this.findPointInvect(pointI)){  //Si lo encuentra en el vector
                //primtcor("Objeto repetido",2);
                return false;
            }  
            else {
                if (this.RootNode.data.length < threShold && this.boolHOJAS_T_F == false){  //si el array data tiene espacio y no ha creado nodos hijos
                    this.RootNode.setData(pointI);   //hacer push
                    //primtcor("push",2);
                    return true;                    
                }
                else { //si no hay espacio en el array data                    
                    //console.log("reacomodar");                    
                    cortar4(this.RootNode.PLeftTop,this.RootNode.PBotRig);                    
                    
                    
                    //d3.selectAll()
                    
                    //paso los elementos de data al sons[]
                    
                    this.RootNode.setData(pointI);   //hacer push
                    //primtcor("push paara acomodar",2);
                                
                    for(var m  = 0 ; m<this.RootNode.data.length ; m++ ){
                        var d = this.RootNode.data[m];
                        //si esta en el lado izq
                        if((this.RootNode.PBotRig.x+this.RootNode.PLeftTop.x)/2 >= this.RootNode.data[m].x ){
                            //primtcor("IZQ ",3);
                            //si esta arriba o sons[0]
                            if((this.RootNode.PLeftTop.y+this.RootNode.PBotRig.y)/2 <= d.y){
                                //primtcor("  ARR",3);
                                //si esta arribaa o sons[0]
                                if(this.sons[0]==null){
                                    //primtcor("    SONS[0] NULL",3);
                                    this.sons[0] = new quadTree(
                                        this.RootNode.PLeftTop,
                                        new Point(
                                            (this.RootNode.PBotRig.x+this.RootNode.PLeftTop.x)/2,
                                            (this.RootNode.PLeftTop.y+this.RootNode.PBotRig.y)/2),
                                        this.RootNode.myHI/2,
                                        this.RootNode.myWI/2);               
                                } 
                                //primtcor("Recurisidade [0]", 1);
                                this.sons[0].insert(d);
                            }         
                            else{  //si esta abajo o sons[2]
                                //primtcor("  ABAJO",3);
                                if(this.sons[2]==null){                             //primtcor("    SONS[2] NULL",3);
                                    this.sons[2] = new quadTree(                   new Point(
                                            this.RootNode.PLeftTop.x,
                                            (this.RootNode.PLeftTop.y+this.RootNode.PBotRig.y)/2
                                        ),
                                        new Point(
                                            (this.RootNode.PBotRig.x+this.RootNode.PLeftTop.x)/2,
                                            this.RootNode.PBotRig.y
                                        ),
                                        this.RootNode.myHI/2,
                                        this.RootNode.myWI/2
                                    );                                    
                                }
                                //primtcor("Recurividade ", 1);
                                this.sons[2].insert(d);
                            }
                        }
                        //si esta en el lado derecho
                        else{  
                            //primtcor("DER ",3);
                            //Si esta arriba o sons[1] 
                            if((this.RootNode.PLeftTop.y+this.RootNode.PBotRig.y)/2<=d.y){
                                //primtcor("  ARR",3);
                                if(this.sons[1]==null){
                                    //primtcor("    SONS[1] NULL",3);
                                    this.sons[1] = new quadTree(
                                        new Point(
                                            (this.RootNode.PBotRig.x+this.RootNode.PLeftTop.x)/2, this.RootNode.PLeftTop.y),
                                        new Point(
                                            this.RootNode.PBotRig.x,
                                            (this.RootNode.PLeftTop.y+this.RootNode.PBotRig.y)/2
                                        ),
                                        this.RootNode.myHI/2,
                                        this.RootNode.myWI/2
                                    );                                    
                                }
                                //primtcor("Recurividade ", 1);
                                this.sons[1].insert(d);
                            }
                            else{ //esta abajo o sons[3]
                                //primtcor("  ABAJO",3);
                                if(this.sons[3]==null){
                                    //primtcor("    SONS[3] NULL",3);
                                    this.sons[3] = new quadTree(
                                        new Point(
                                            (this.RootNode.PBotRig.x+this.RootNode.PLeftTop.x)/2, (this.RootNode.PLeftTop.y+this.RootNode.PBotRig.y)/2),
                                        this.RootNode.PBotRig,
                                        this.RootNode.myHI/2,
                                        this.RootNode.myWI/2
                                    );    
                                }      
                                //primtcor("Recurividade ", 1);
                                this.sons[3].insert(d);
                            }
                        }
                    //});                  
                    }
                    this.boolHOJAS_T_F = true;
                    this.RootNode.data = [];
                }
            }
        }
        
    }
/* 
function cortar4(topLeft, botRight){
    svg.append("line")  //horizontal
        .attr("x1", xScale(topLeft.x))
        .attr("y1", yScale((botRight.y+topLeft.y)/2))
        .attr("x2", xScale(botRight.x))
        .attr("y2", yScale((botRight.y+topLeft.y)/2))
        .style("stroke","red");
        
    svg.append("line")  //vertical
        .attr("x1", xScale((botRight.x+topLeft.x)/2))
        .attr("y1", yScale(topLeft.y))
        .attr("x2", xScale((botRight.x+topLeft.x)/2))
        .attr("y2", yScale(botRight.y))
        .style("stroke","red");
}

function cortarEnCuatro(hI,wI){
    svg.append("line")  //horizontal
        .attr("x1",margin.left)
        .attr("y1",hI/2+margin.top)
        .attr("x2",wI-margin.right)
        .attr("y2",hI/2+margin.top)
        .style("stroke","red");
    
    svg.append("line") //vertical
        .attr("x1",wI/2+margin.left)
        .attr("y1",margin.top)
        .attr("x2",wI/2+margin.left)
        .attr("y2",hI-margin.bottom)
        .style("stroke","red");
}  
*/