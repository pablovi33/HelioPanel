
use <MCAD/involute_gears.scad>




//  linear_extrude(height = 40, twist = -360, scale = 0, center = true, slices = 200)


module engraneChico(){
    
   difference(){
    union(){    
        linear_extrude(height = 14, twist = -30)
        projection([]){

             gear(circular_pitch = 400,
                    number_of_teeth = 16,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 22);
            


        }


        rotate(30)
        translate([0,0,14])
        linear_extrude(height = 14, twist = 30)
        projection([]){

             gear(circular_pitch = 400,
                    number_of_teeth = 16,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 22);
            


        }

      


        //COPLE
        //translate([0,0,15+8])
        difference(){
          cylinder(d=30,h=40);
          cylinder(d=8.5,h=100,center=true);
          
          
            translate([0,0,23])
            for(i=[0:1]){
                rotate(135*i)
                union(){
                   // translate([4+5,0,-10])
                    //cube([3.5,8.5,18],center=true);  
                    
                    translate([4+5,0,10])
                    cube([3.5,8.5,18],center=true); 
                    
                    translate([0,0,15-(9/2)])
                    rotate([90,0,90])
                    cylinder(d=4.5,h=100);
                    
                 //    translate([0,0,-15+(9/2)])
                  //  rotate([90,0,90])
                  //  cylinder(d=4.5,h=100);
                }
             }
        }
    }
    
     //recorte tuerca
         translate([0,0,-10])
        cylinder(d=15,h=26*2,$fn=6,center=true);
  }

}//fin module

module engraneChicoGiro(){
    
   difference(){
    union(){    
        linear_extrude(height = 14, twist = -30)
        projection([]){

             gear(circular_pitch = 400,
                    number_of_teeth = 16,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 22);
            


        }


        rotate(30)
        translate([0,0,14])
        linear_extrude(height = 14, twist = 30)
        projection([]){

             gear(circular_pitch = 400,
                    number_of_teeth = 16,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 22);
            


        }

      


        //COPLE
        //translate([0,0,15+8])
        difference(){
          cylinder(d=30,h=40);
          cylinder(d=8.5,h=100,center=true);
          
          
            translate([0,0,23])
            for(i=[0:1]){
                rotate(135*i)
                union(){
                   // translate([4+5,0,-10])
                    //cube([3.5,8.5,18],center=true);  
                    
                    translate([4+5,0,10])
                    cube([3.5,8.5,18],center=true); 
                    
                    translate([0,0,15-(9/2)])
                    rotate([90,0,90])
                    cylinder(d=4.5,h=100);
                    
                 //    translate([0,0,-15+(9/2)])
                  //  rotate([90,0,90])
                  //  cylinder(d=4.5,h=100);
                }
             }
        }
    }
    
    //recorte tuerca
         //translate([0,0,-10])
        //cylinder(d=15,h=26*2,$fn=6,center=true);
    cylinder(d=15,h=(28-3)*2,$fn=6,center=true);
  }

}//fin module



module engraneChicoEleva(){
    
    difference(){
            union(){
              translate([0,0,-10])
            linear_extrude(height = 10, twist = -30)
                projection([]){

                     gear(circular_pitch = 400,
                            number_of_teeth = 16,
                            gear_thickness = 1,
                            rim_thickness = 1,
                            hub_thickness = 1,
                            bore_diameter = 22);
                    


                }


            rotate(30)
          
            linear_extrude(height = 10, twist = 30)
                projection([]){

                     gear(circular_pitch = 400,
                            number_of_teeth = 16,
                            gear_thickness = 1,
                            rim_thickness = 1,
                            hub_thickness = 1,
                            bore_diameter = 22);
                    


                }

          


            //COPLE
            translate([0,0,-25])
            difference(){
              cylinder(d=30,h=35);
              cylinder(d=8.5,h=100,center=true);
              
              
                translate([0,0,-5])
                for(i=[0:1]){
                    rotate(135*i)
                    union(){
                       // translate([4+5,0,-10])
                        //cube([3.5,8.5,18],center=true);  
                        
                        translate([4+5,0,10])
                        cube([3.5,8.5,18],center=true); 
                        
                        translate([0,0,15-(9/2)])
                        rotate([90,0,90])
                        cylinder(d=4.5,h=100);
                        
                     //    translate([0,0,-15+(9/2)])
                      //  rotate([90,0,90])
                      //  cylinder(d=4.5,h=100);
                    }
                 }
            }
        }
    
    
     //recorte tuerca
         translate([0,0,20])
        rotate([180,0,0])
        cylinder(d=15,h=26+10,$fn=6);
  }

}//fin module

module engraneGrande(){
    //pitch radius 68.8889
  difference(){
        union(){
            
            
            linear_extrude(height = 14, twist = 7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 8.3);
            }
            
            rotate(-7.74)
            translate([0,0,14])
              linear_extrude(height = 14, twist = -7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 8.3);
            }
            
         /*   //COPLE
        translate([0,0,15])
        difference(){
          cylinder(d=30,h=30,center=true);
          cylinder(d=8.5,h=60,center=true);
          
          
            for(i=[0:1]){
                rotate(90*i)
                union(){
                   // translate([4+5,0,-10])
                    //cube([3.5,8.5,18],center=true);  
                    
                    translate([4+5,0,10])
                    cube([3.5,8.5,18],center=true); 
                    
                    translate([0,0,15-(9/2)])
                    rotate([90,0,90])
                    cylinder(d=4.5,h=100);
                    
                 //    translate([0,0,-15+(9/2)])
                  //  rotate([90,0,90])
                  //  cylinder(d=4.5,h=100);
                }
             }
           }*/
            
        }//fin union
         
        
        
        
        /*for(i=[0:7]){
            rotate(45*i)
            translate([0,0,-50])
            linear_extrude(height=100)
            minkowski(){    
                difference(){
                   circle(r=51);  
                   //circle(r=20);
                    orilla=15;
                    translate([0,-orilla])
                   rotate(45)
                  square([300,300]);
                    
                  translate([-150,-300+orilla])
                  square([300,300]);
                    
                   translate([-300,-150])
                  square([300,300]);
                    
                    
                }
               circle(r=8);
            }
      }*/
      
      /*translate([0,27,-50])
      linear_extrude(height=100)
      difference(){
          translate([0,50+10])
          square([200,100],center=true);
          circle(d=22);
      }*/
      
      translate([0,200+27+20,0])
      cube([400,400,400],center=true);
      
      //perfil 2020
      translate([0,20+27,14
      ])
      cube([200,40,20],center=true);
      
      //abertura extra rect
      
      translate([0,60,0])
      cube([70,120,100],center=true);
      
      //abertura central
      cylinder(r=48.26+1,h=100,center=true);
      
      
      
      
      for(g=[0:1]){
          translate([0,27+10,0])
          rotate(g*180)
          translate([45,0,0])
          cylinder(d=4.5,h=100,center=true);
      }
    }//fin difference

}


module engraneGrandeGiro(){
     //pitch radius 68.8889
  difference(){
        union(){
            
            
            linear_extrude(height = 14, twist = 7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 8.5);
            }
            
            rotate(-7.74)
            translate([0,0,14])
              linear_extrude(height = 14, twist = -7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 8.5);
            }
            
           
        
                for(h=[0:3]){
                    rotate(45*h)
                    minkowski(){
                    cube([90,2,10],center=true);
                    cylinder(d=30,h=0.01,center=true);
                }
                cylinder(d=100,h=10,center=true);
            }
            
            //punta
            
            translate([0,0,14*2])
            cylinder(d1=28,d2=14,h=8);
            
        }//fin union
         
        
                for(g=[0:1]){
                    rotate(180*g)
                    translate([45,0,0])
                    union(){
                        cylinder(d=8.5,h=100,center=true);
                        translate([0,0,14-2.5])
                        cylinder(d=20,h=20);
                    }
                }
                
                //eje central
                 cylinder(d=8.5,h=100,center=true);
        
           
    }//fin difference
}

module engraneGrandeEleva(){
    //pitch radius 68.8889
  difference(){
        union(){
            
             translate([0,0,-10])
            linear_extrude(height = 10, twist = 7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 8.3);
            }
            
            rotate(-7.74)
           
              linear_extrude(height = 10, twist = -7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 8.3);
            }
            
         /*   //COPLE
        translate([0,0,15])
        difference(){
          cylinder(d=30,h=30,center=true);
          cylinder(d=8.5,h=60,center=true);
          
          
            for(i=[0:1]){
                rotate(90*i)
                union(){
                   // translate([4+5,0,-10])
                    //cube([3.5,8.5,18],center=true);  
                    
                    translate([4+5,0,10])
                    cube([3.5,8.5,18],center=true); 
                    
                    translate([0,0,15-(9/2)])
                    rotate([90,0,90])
                    cylinder(d=4.5,h=100);
                    
                 //    translate([0,0,-15+(9/2)])
                  //  rotate([90,0,90])
                  //  cylinder(d=4.5,h=100);
                }
             }
           }*/
            
            minkBas=3;
            translate([0,-2.5+27,0])
            minkowski(){
                cube([170-(2*minkBas),5,20-(2*minkBas)],center=true);
                rotate([90,0,0])
                cylinder(r=minkBas,h=0.01);
            }
            
            //apoyoExtratornillos
            translate([0,-2.5+27,0])
             for(g=[0:1]){

                  rotate([0,g*180,])
                  translate([75,0,0])
              rotate([90,0,0])
              cylinder(d=8,h=6.5,center=true);
              }
            
        }//fin union
         
        
        
       
      
      translate([0,200+27+20-20,0])
      cube([400,400,400],center=true);
        
        
        
        //recorte a interior de panel
       // translate([0,0,200+14+10])
      //cube([400,400,400],center=true);
      
      //perfil 2020
      translate([0,20+27,14
      ])
      cube([200,40,20],center=true);
      
        
        //recorte tuerca
         translate([0,0,-10])
        cylinder(d=15,h=20,$fn=6,center=true);
        
        
    
      
      
      
      //abertura central
      //cylinder(r=48.26+1,h=100,center=true);
      
       
       
       for(g=[0:1]){

          rotate([0,g*180,])
          translate([75,0,0])
      rotate([90,0,0])
      cylinder(d=4.5,h=100,center=true);
      }
      
      
      
       
       //apoyos cilindros OLD
   
      /*
      for(g=[0:1]){
          translate([0,27+10,0])
          rotate(g*180)
          translate([45,0,0])
          cylinder(d=4.5,h=100,center=true);
      }*/
      
      
    }//fin difference

}

//########RENDERIZADOS########


$fn=200;

//engraneChico($fn=200);

//cylinder(r=70,h=0.5);

//engraneGrandeGiro();

//translate([0,68.9+17.8,0])
//engraneGrandeEleva();

//engraneChicoEleva();

//translate([20,0,0])
engraneChicoGiro();

