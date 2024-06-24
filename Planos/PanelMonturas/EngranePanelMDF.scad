use <MCAD/involute_gears.scad>

//alturaEng=3;

module engrane_grande(){
    difference(){
        projection(){
        gear(circular_pitch = 400,
                number_of_teeth = 110,
                gear_thickness = alturaEng,
                rim_thickness = alturaEng,
                hub_thickness = alturaEng,
                bore_diameter = 15);
        }

       
        translate([0,-(250/2)])
        square([250,250],center=true);
        
    }
}


module engrane_grande_MDF(){
    difference(){
        translate([0,7.5])
        difference(){
            projection(){
            gear(circular_pitch = 400,
                    number_of_teeth = 110,
                    gear_thickness = alturaEng,
                    rim_thickness = alturaEng,
                    hub_thickness = alturaEng,
                    bore_diameter = 32);
            }
            
            for(f=[0:6]){
                rotate(f*30)
                translate([70,0])
                   minkowski(){
                    square([25,6],center=true);
                    circle(r=4);
                }
            }
        }

       //recorte mas de mitad
        translate([0,-(250/2)-10])
        square([250,250],center=true);
        
        
        //recorte montura
        minkowski(){
            square([80-(5*2),20-(5*2)],center=true);
            circle(r=5);
        }
        
        
        //recorte redondeo
        translate([0,-10])
        square([80,20],center=true);
        
        for(f=[0:1]){
            rotate(180*f)
            translate([100,0])
            circle(d=4.5);
        }
    }
}


!engrane_grande_MDF();


esp=2;
//alturaEng=5.5;
alturaEng=6.5+0.5;

$fn=120;


    
 
    difference(){
       
            union(){
                
                
//difference(){
                translate([0,0,01])
    union(){
        
        /*linear_extrude(height=alturaEng)
            for(f=[0:1]){
                rotate(180*f)
                translate([0,3.5])
                square(4,center=true);
            }*/
            
        translate([0,0,alturaEng])
        cylinder(d=40,h=esp);
            
            translate([0,0,-esp])
cylinder(d=40,h=esp);
            
         gear(circular_pitch = 400,
                    number_of_teeth = 16,
                    gear_thickness = alturaEng,
                    rim_thickness = alturaEng,
                    hub_thickness = alturaEng,
                    bore_diameter = 4);
    }


            //COPLE
            translate([0,0,-25])
            difference(){
                //translate([0,0,-10])
              cylinder(d=30,h=35);
              cylinder(d=8.5,h=100,center=true);
              
              
                translate([0,0,-5])
                for(i=[0:1]){
                    rotate(135*i)
                    union(){

                        translate([4+5,0,10])
                        cube([3.5,8.5,18],center=true); 
                        
                        translate([0,0,15-(9/2)])
                        rotate([90,0,90])
                        cylinder(d=4.5,h=100);

                    }
                 }
            }
        }
    
    
     //recorte tuerca
         translate([0,0,20])
        rotate([180,0,0])
        cylinder(d=15,h=26+10,$fn=6);
  }