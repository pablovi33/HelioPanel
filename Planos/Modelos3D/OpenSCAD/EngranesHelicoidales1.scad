
use <MCAD/involute_gears.scad>




//  linear_extrude(height = 40, twist = -360, scale = 0, center = true, slices = 200)


module engraneChico(){
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
    translate([0,0,10])
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
    }

}//fin module

module engraneGrande(){
  difference(){
        union(){
            
            
            linear_extrude(height = 10, twist = 7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 22);
            }
            
            rotate(-7.74)
            translate([0,0,10])
              linear_extrude(height = 10, twist = -7.74)
            projection([]){
             gear(circular_pitch = 400,
                    number_of_teeth = 62,
                    gear_thickness = 1,
                    rim_thickness = 1,
                    hub_thickness = 1,
                    bore_diameter = 22);
            }
            
            //COPLE
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
           }
            
        }//fin union
         
        
        
        
        for(i=[0:7]){
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
      }
    }//fin difference

}

//########RENDERIZADOS########



engraneChico($fn=20);

//cylinder(r=70,h=0.5);


translate([0,68.9+17.8,0])
engraneGrande();


