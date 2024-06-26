// Ron's planetary gearbox
//
// GNU GPL v3
// Ron Aldrich
//

/*
 * To Do:
 *		Add an option for an "accessible" frame, which allows access to the sun gear's set screw.
 *		Reduce the length of teeth on the annulus gear.
 *		Switch all nut recesses to Josef Prusa's "star" recess.
 *		Separate the parts out into two plates - one with all the gear parts, and one with framework parts.
 */
 
 $fn=120;

include <more_configuration.scad>

use <involute_gears.scad>

// What type of bolt shall I use for the output?

m5_bolt_output = 0;
m6_bolt_output = 1;		
m8_bolt_output = 2;
hyena_output = 3;

output_bolt = m8_bolt_output;
//output_bolt = m6_bolt_output;

// What gear ratio shall I aim for?

40_9_ratio = 0;		// 4.444... to 1
42_10_ratio = 1;		// 4.2 to 1
40_10_ratio = 2;		// 4 to 1
38_10_ratio = 3;		// 3.8 to 1
44_12_ratio = 4;		// 3.666... to 1

gear_ratio = 40_9_ratio;

// Shall I print the entire model? Or just the output parts?

print_body = true;
print_output = true;

// You probably shouldn't modify things below here, unless you really know what you're doing.

short_bolts = false;	// print for short bolts.
open_frame = false;

output_bolt_diameter = (output_bolt == m5_bolt_output) ? m5_diameter :
                       (output_bolt == m6_bolt_output) ? m6_diameter :
                       m8_diameter;
output_bolt_head_diameter = (output_bolt == m5_bolt_output) ? m5_nut_diameter :
                            (output_bolt == m6_bolt_output) ? m6_nut_diameter :
                            m8_nut_diameter;

output_bolt_head_height = (output_bolt == m5_bolt_output) ? m5_bolt_head_height+.5 :
                          (output_bolt == m6_bolt_output) ? m6_bolt_head_height+.5 :
							 (output_bolt == m8_bolt_output) ? m8_bolt_head_height+.5 :
                       	 m8_half_nut_height+.25;

output_bolt_double_nut = (output_bolt == hyena_output) ? 1 : 0;

output_bearing = (output_bolt == m5_bolt_output) ? undefined_m5_bearing :
                 (output_bolt == m6_bolt_output) ? 106_bearing :
                 608_bearing;

output_bearing_clearance = (output_bolt == m5_bolt_output) ? undefined_m5_bearing_clearance :
                           (output_bolt == m6_bolt_output) ? 106_bearing_clearance :
                           608_bearing_clearance;

echo("output_bolt_head_height", output_bolt_head_height);

ring_teeth = (gear_ratio == 40_9_ratio) ? 31 :
             (gear_ratio == 42_10_ratio) ? 32 :
             (gear_ratio == 40_10_ratio) ? 30 :
             (gear_ratio == 38_10_ratio) ? 28 :
             (gear_ratio == 44_12_ratio) ? 32 : 28;

planet_teeth = (gear_ratio == 40_9_ratio) ? 11 :
             (gear_ratio == 42_10_ratio) ? 11 :
             (gear_ratio == 40_10_ratio) ? 10 :
             (gear_ratio == 38_10_ratio) ? 9 :
             (gear_ratio == 44_12_ratio) ? 10 : 9;

function output_bearing() = output_bearing;
function output_bearing_clearance() = output_bearing_clearance;

m3_bolt_head_height = 3;
m3_bolt_head_diameter = 6.1;

housing_size = 40;
num_planets = 3;

sun_teeth = ring_teeth-planet_teeth*2;
gear_pitch = ring_teeth/(35.5);

echo("sun_teeth", sun_teeth);
echo("ratio", ring_teeth+sun_teeth, "to", sun_teeth, "or", 1+ring_teeth/sun_teeth);

planet_angle = 360/(ring_teeth+sun_teeth);
planet_offset = (planet_teeth-floor(planet_teeth/2)*2) == 0 ? 0 : planet_angle/2;

orbit_radius=((planet_teeth+sun_teeth)/gear_pitch)/2;

echo("planet_angle", planet_angle);
echo("planet_offset", planet_offset);

vertical_clearance = 0.5;

gear_thread_height = 10;
sun_gear_hub_height = 10;
sun_gear_hub_radius = 10;
sun_gear_hub_inset = 3;
sun_bore_radius = 5.3/2;

sun_gear_radius = outer_radius(sun_teeth, gear_pitch);

planet_gear_height = 7.5;
planet_shaft_diameter = 6;
//planet_bore_clearance = .25+1;
planet_bore_clearance = .75;
planet_bore_diameter = planet_shaft_diameter+planet_bore_clearance;

planet_gear_radius = outer_radius(planet_teeth, gear_pitch);
planet_carrier_bottom_plate_height = 1;
planet_carrier_top_plate_height = output_bolt_head_height+1;
planet_carrier_height = planet_gear_height+3*vertical_clearance+planet_carrier_bottom_plate_height+planet_carrier_top_plate_height;
planet_carrier_center = [0, 0, planet_carrier_height/2];
planet_carrier_gear_center = [orbit_radius, 0, planet_carrier_bottom_plate_height+(planet_gear_height+3*vertical_clearance)/2];
planet_carrier_radius = 16;

echo("planet_carrier_height", planet_carrier_height);


gear_clearance = 0.5;
//gear_clearance = 0.9;
gear_backlash = 0.45;
gear_addendum_adjustment = 1.4;
gear_pressure_angle = 20;

x = 0;
y = 1;
z = 2;

//planetary_frame_size = [housing_size, housing_size, sun_gear_hub_inset+sun_gear_hub_height+planet_carrier_height+vertical_clearance*2-2];
planetary_frame_size = [housing_size, housing_size, 27.5];
planetary_frame_center = [0, 0, planetary_frame_size[z]/2];

motor_mount_size = [housing_size, housing_size, sun_gear_hub_inset+sun_gear_hub_height - 3];
motor_mount_center = [0, 0, motor_mount_size[z]/2];

planetary_gearbox_size = [housing_size, housing_size, planetary_frame_size[z]-motor_mount_size[z]];
planetary_gearbox_center = [0, 0, motor_mount_size[z]+planetary_gearbox_size[z]/2];

ring_gear_bottom = [0, 0, sun_gear_hub_inset+sun_gear_hub_height];

motor_shaft_hole_radius = 12;
motor_mount_hole_spacing = 1.22*25.4;
motor_mount_thickness = 4;

motor_mount_access_top = ring_gear_bottom[z]-1;
motor_mount_access_bottom = motor_mount_thickness;
motor_mount_access_height = motor_mount_access_top-motor_mount_access_bottom;
motor_mount_access_center = [0, 0, (motor_mount_access_bottom+motor_mount_access_top)/2];

sun_gear_tooth_height = 10;
sun_gear_hub_center = [0, 0, sun_gear_hub_height/2];
sun_gear_height = sun_gear_hub_height+gear_thread_height;
sun_gear_center = [0, 0, sun_gear_height/2];

cover_mount_height = 10;
cover_mount_top_height = 10;
cover_mount_center = [0, 0, planetary_frame_size[z]-(cover_mount_height+cover_mount_top_height)/2];
cover_angle = 360/ring_teeth*2;

echo("planetary_frame_height = ", planetary_frame_size[z]);

module planetary_frame()
{
	difference()
	{
		union()
		{
			if (open_frame == true)
			{
				translate(planetary_gearbox_center)
				minkowski()
				{
					cube(planetary_gearbox_size-[4, 4, 1], center=true);
					cylinder(h=1, r=2, $fn=12, center=true);
				}
			}
			else
			{
				translate(planetary_frame_center)
				minkowski()
				{
					cube(planetary_frame_size-[4, 4, 1], center=true);
					cylinder(h=1, r=2, $fn=12, center=true);
				}
			}

			if (short_bolts == true)
			{
				translate(cover_mount_center)
				rotate([0, 0, 45+cover_angle])
				minkowski()
				{
					assign(n=((housing_size/2)-2)/cos(45))
					cylinder(h=cover_mount_height, r1=n-cover_mount_height, r2=n, $fn=4, center=true);
					cylinder(h=cover_mount_top_height, r=2, $fn=12, center=true);
				}
			}
		}
		
		union()
		{
			// Ring gear.

			assign(thickness=planet_carrier_height+vertical_clearance*2+.1)
			render(convexity=10) translate(ring_gear_bottom)
			rotate([0, 0, 360/(ring_teeth*2)])
			gear(number_of_teeth=ring_teeth, diametral_pitch=gear_pitch, hub_diameter=0, bore_diameter=0, rim_thickness=thickness, gear_thickness=thickness, clearance=0, backlash=-gear_backlash, pressure_angle=gear_pressure_angle, addendum_adjustment=gear_addendum_adjustment);
			
			// Sun shaft.

			translate([0, 0, ring_gear_bottom[z]/2])
			cylinder(h=ring_gear_bottom[z]+.1, r1=motor_shaft_hole_radius, r2=sun_gear_hub_radius+.5, $fn=20, center=true);

			// Ease the top edge of the sun shaft.

			translate([0, 0, ring_gear_bottom[z]])
			cylinder(h=1, r1=sun_gear_hub_radius+.5, r2=sun_gear_hub_radius+1.5, $fn=20, center=true);

			for(i=[0:3]) rotate([0, 0, i*90])
			translate([motor_mount_hole_spacing/2, motor_mount_hole_spacing/2, 0])
			{
				translate(planetary_frame_center)
				cylinder(h=planetary_frame_size[z]+.1, r=m3_diameter/2, $fn=12, center=true);

				if (short_bolts == true)
					translate([0, 0, 20])
					cylinder(h=10, r=3, $fn=20, center=false);
			}

			if (short_bolts==true)
			{
				for(i=[0:3]) rotate([0, 0, i*90+cover_angle])
				translate([motor_mount_hole_spacing/2, motor_mount_hole_spacing/2, 0])
				rotate([0, 0, 90])
				{
					translate([0, 0, planetary_frame_size[z]-4+layer_height])
					cylinder(h=4, r=m3_diameter/2, $fn=12, center=false);

					translate([0, 0, planetary_frame_size[z]-4-m3_nut_thickness/2])
					{
						cylinder(h=m3_nut_thickness, r=m3_nut_diameter/2, $fn=6, center=true);
					
						translate([4, 0, 0])
						cube([8, m3_nut_diameter*cos(30), m3_nut_thickness], center=true);
					}

					translate([0, 0, planetary_frame_size[z]-cover_mount_height+.6])
					cylinder(h=6, r=m3_diameter/2, $fn=12, center=true);
				}	
			}	
		}
	}
}

module sun_gear()
{
	difference()
	{
		union()
		{
			translate(sun_gear_hub_center)
			cylinder(h=sun_gear_hub_height, r=sun_gear_hub_radius, $fn=20, center=true);

			assign(thickness=sun_gear_tooth_height)
			translate([0, 0, sun_gear_hub_height])
			gear(number_of_teeth=sun_teeth, diametral_pitch=gear_pitch, hub_diameter=0, hub_thickness=thickness, bore_diameter=0, rim_thickness=thickness, rim_width=0, gear_thickness=thickness, clearance=gear_clearance, backlash=gear_backlash, pressure_angle=gear_pressure_angle);
		}

altShaft=8.6;
		union()
		{  
            
            //agujero cilindro
            /*difference(){
                translate(sun_gear_center)
                //translate([0,0,altShaft])
                cylinder(h=(sun_gear_height+.1), r=sun_bore_radius, $fn=12, center=true);
                   translate([0,0,altShaft/2-1])
                cube([30,30,altShaft+2],center=true);  
                    
                
            }*/
            
            //agujero cuadrado
              //translate([0,0,altShaft])
              //cube([2.6,2.6,altShaft*2],center=true);
              //cube([3.5,3.5,(altShaft+0.2)*2],center=true);
            
            
            
            translate([0,0,-50])
              linear_extrude(height=100)
               difference(){
                   circle(d=5.2);
                   translate([0,-2])
                   translate([0,-10])
                   square([20,20],center=true);
               }
               
               cylinder(d=6,h=1.61*2,center=true);
               
      //mecanismo aprisionador
			//translate(sun_gear_hub_center+[0, sun_gear_hub_radius/2, 0])
            
			/*rotate([90, 0, 0])
			{
				cylinder(h=sun_gear_hub_radius+.1, r=m3_diameter/2, $fn=6, center=true);
				rotate([0, 0, 90])
				cylinder(h=m3_nut_thickness, r=m3_nut_diameter/2, $fn=6, center=true);
				translate([0, -3, 0])
				cube([m3_nut_diameter*cos(30), 6, m3_nut_thickness], center=true);
			}*/
		}
	}
}

module planet_gear()
{
	assign(thickness = planet_gear_height)
	difference()
	{
		render(convexity=10)
		gear(number_of_teeth=planet_teeth, diametral_pitch=gear_pitch, hub_diameter=0, hub_thickness=thickness, bore_diameter=0, rim_thickness=thickness, rim_width=0, gear_thickness=thickness, clearance=gear_clearance, backlash=gear_backlash, pressure_angle=gear_pressure_angle);
     //ajuste engrane interior
		translate([0, 0, thickness/2])
		cylinder(h=thickness+.1, r=(planet_bore_diameter)/2+0.1, $fn=30, center=true);
	}
}

planet_carrier_sun_shaft_height = planet_carrier_height-planet_carrier_top_plate_height;
planet_carrier_sun_shaft_center = [0, 0, planet_carrier_sun_shaft_height/2];
planet_carrier_sun_shaft_radius = sun_gear_radius+1;

//!planet_carrier();

module planet_carrier()
{
	z1=m3_bolt_head_height;
	z2=z1+9;

	difference()
	{
		translate(planet_carrier_center)
		cylinder(h=planet_carrier_height, r=planet_carrier_radius, $fn=40, center=true);
	
		for(i=[0:num_planets-1]) assign(a1=i*floor(360/num_planets/planet_angle)*planet_angle+planet_offset)
		{
			rotate([0, 0, a1])
			{
				rotate([0, 0, 180/num_planets])
				{
                    //agujeros tornillos
					translate([orbit_radius+1, 0, (z1+z2)/2])
					cylinder(h=z2-z1-layer_height, r=m3_diameter/2, $fn=12, center=true);
   
                    //Inicio sospecha
					//translate([orbit_radius+1, 0, (planet_carrier_height+z2)/2+.05])
		
                 //AGUJERO ORIGINAL PARA TUERCA   //cylinder(h=planet_carrier_height-z2+.1, r=m3_nut_diameter/2, $fn=6, center=true);
                    
                    //agujero modificado
     // cylinder(h=planet_carrier_height-z2+.1, r=(m3_nut_diameter/2)+0.1, $fn=20, center=true);
            
                  
                    //agujero pija
                    translate([orbit_radius+1, 0, (planet_carrier_height+z2)/2+.05])
                    cylinder(h=30, d2=1.2,d1=2, $fn=20, center=true);
                    
                    
                    cylinder(h=planet_carrier_height-z2+.1, r=m3_nut_diameter/2, $fn=6, center=true);

					translate([orbit_radius+1, 0, m3_bolt_head_height/2-.05])
					cylinder(h=m3_bolt_head_height+.1, r=m3_bolt_head_diameter/2, $fn=20, center=true);
                    
                    //fin sospecha
				}

				difference()
				{
                    //agujeros planetas
					translate(planet_carrier_gear_center)
					cylinder(h=planet_gear_height+vertical_clearance*3, r=planet_gear_radius+1.2, $fn=20, center=true);
                    //ejes de planetas
					translate(planet_carrier_gear_center)
					cylinder(h=planet_gear_height+vertical_clearance*3+.1, r=(planet_bore_diameter-planet_bore_clearance)/2, $fn=20, center=true);
					//topes ejes planetas
                    for(j=[-1, 1])
					{
						translate(planet_carrier_gear_center+[0, 0, j*(planet_gear_height+vertical_clearance*3)/2])
						cylinder(h=vertical_clearance*2, r=planet_bore_diameter/2+1.5, $fn=20, center=true);
					}
				}
			}
		}
		
        //agujero main shaft
		translate(planet_carrier_sun_shaft_center-[0, 0, .05])
		cylinder(h=planet_carrier_sun_shaft_height+.1, r=planet_carrier_sun_shaft_radius, $fn=20, center=true);


      //agujero cabeza tornillo eje
		translate([0, 0, planet_carrier_height-planet_carrier_top_plate_height+output_bolt_head_height/2-.05])
		rotate([0, 0, 30])
		cylinder(h=output_bolt_head_height+.11, r=output_bolt_head_diameter/2, $fn=6, center=true);

   //agujero tornillo eje
		translate([0, 0, planet_carrier_height-planet_carrier_top_plate_height/2])
		cylinder(h=planet_carrier_top_plate_height+.1, r=output_bolt_diameter/2, $fn=20, center=true);

      //agujero balero
		translate([0, 0, planet_carrier_height-vertical_clearance/2])
		difference()
		{
			cylinder(h=vertical_clearance, r=output_bearing[bearing_body_diameter]/2+.5);
			cylinder(h=vertical_clearance+.1, r=output_bearing[bearing_body_diameter]/2-.5);
		}

		// registration notch
		translate([-planet_carrier_radius, 0, 8.5])
		cube([2, 1, 6], center=true);
	}
}

lower_planet_carrier_size = [planet_carrier_radius*2, planet_carrier_radius*2, 8.5];
lower_planet_carrier_center = [0, 0, lower_planet_carrier_size[z]/2];


module lower_planet_carrier()
{
    
	intersection()
	{
		planet_carrier();
		translate(lower_planet_carrier_center+[0, 0, -.05])
		cube(lower_planet_carrier_size+[0, 0, .1], center=true);
	}
}

upper_planet_carrier_size = [lower_planet_carrier_size[x], lower_planet_carrier_size[y], planet_carrier_height-lower_planet_carrier_size[z]];
upper_planet_carrier_center = [0, 0, lower_planet_carrier_size[z]+upper_planet_carrier_size[z]/2];

module upper_planet_carrier(print_orientation=1)
{
	translate([0, 0, upper_planet_carrier_size[z]*print_orientation])
	rotate([180*print_orientation, 0, 0])
	translate([0, 0, -lower_planet_carrier_size[z]])
	intersection()
	{
		planet_carrier();
		translate(upper_planet_carrier_center+[0, 0, .05])
		cube(upper_planet_carrier_size+[0, 0, .1], center=true);
	}
}

cover_z0 = 0;
cover_z1 = ring_gear_bottom[z]+planet_carrier_height+vertical_clearance*2+output_bolt_double_nut*output_bolt_head_height-planetary_frame_size[z];
cover_z2 = cover_z1+output_bearing[bearing_length]-vertical_clearance;
cover_z3 = cover_z2+1;

cover_bolt_z0 = 0;
cover_bolt_z1 = 2;
cover_bolt_z2 = cover_z3;

cover_size = [housing_size, housing_size, cover_z3];
cover_center = [0, 0, cover_size[z]/2];

echo("cover height, ", cover_size[z]);

echo("total height", planetary_frame_size[z]+cover_size[z]);

function cover_height() = cover_size[z];

module cover(print_orientation=1,baseFrameMod=0,)
{
    if(baseFrameMod==1){
        minko=3;
        
        translate([0,-(cover_size[x]/2)-5+0.01,-3.5])
        difference(){
            minkowski(){
                
                rotate([90,0,0])
                translate([0,0,-2.5])
                cube([80-(minko*2),30-(minko*2),5],center=true);
                rotate([90,0,0])
                cylinder(r=minko,h=0.01,center=true);
            }
            for(f=[0:1]){
                rotate(f*180)
                translate([30,0,0])
                rotate([90,0,0])
                cylinder(d=8.3,h=100,center=true);
            }
        }
    }
    
	translate([0, 0, cover_size[z]*print_orientation])
	rotate([180*print_orientation, 0, 0])
	difference()
	{
        
        
        cham=2;
        fillet=2;
        
        if(baseFrameMod==0){
		translate(cover_center)
            minkowski()
            {
                cube(cover_size-[4, 4, 1], center=true);
                cylinder(h=1, r=2, $fn=12, center=true);
            }
        }else if(baseFrameMod==1){
        
        
        
        //translate([0,0,cover_size[z]/2])
        linear_extrude(height=cover_size[z])
        union(){
        polygon([[-cover_size[x]/2,-cover_size[y]/2+cham],[-cover_size[x]/2-cham,-cover_size[y]/2],[cover_size[x]/2+cham,-cover_size[y]/2],[cover_size[x]/2,-cover_size[y]/2+cham],[cover_size[x]/2,cover_size[y]/2-fillet],[cover_size[x]/2-fillet,cover_size[y]/2],[-cover_size[x]/2+fillet,cover_size[y]/2],[-cover_size[x]/2,cover_size[y]/2-fillet]]);
            translate([cover_size[x]/2-fillet,cover_size[y]/2-fillet])
            circle(r=2);
            translate([-cover_size[x]/2+fillet,cover_size[y]/2-fillet])
            circle(r=2);
        }
    }
        //cube(cover_size,center=true);

		*translate(cover_center)
		cube(cover_size, center=true);

		translate([0, 0, (cover_z0+cover_z1)/2-.05])
		cylinder(h=cover_z1-cover_z0+.1, r=planet_carrier_radius+1, $fn=40, center=true);

		translate([0, 0, (cover_z1+cover_z2)/2-.05])
		cylinder(h=cover_z2-cover_z1+.1, r=(output_bearing[bearing_body_diameter]+output_bearing_clearance[bearing_body_diameter])/2, $fn=30, center=true);

		translate(cover_center)
		cylinder(h=cover_size[z]+.1, r=(output_bearing[bearing_rod_diameter]+output_bearing_clearance[bearing_rod_diameter])/2, $fn=20, center=true);

		for(i=[0:3]) rotate([0, 0, i*90])
		{
			translate([motor_mount_hole_spacing/2, motor_mount_hole_spacing/2, (cover_bolt_z0+cover_bolt_z1)/2-layer_height])
			cylinder(h=(cover_bolt_z1-cover_bolt_z0)+0.75, r=m3_diameter/2, $fn=12, center=true);

			
			translate([motor_mount_hole_spacing/2, motor_mount_hole_spacing/2, (cover_bolt_z1+cover_bolt_z2)/2+.05])
			cylinder(h=cover_bolt_z2-cover_bolt_z1+.1, r=m3_bolt_head_diameter/2, $fn=12, center=true);
		}
	}
}

module planetary_plate()
{
	if (print_body == true)
	{
		planetary_frame();

		translate([15, 35, 0])
		sun_gear();

		for(i=[-1:1])
			translate([35, i*16, 0])
			planet_gear();

		translate([-15, 40, 0])
		lower_planet_carrier();
	}

	if (print_output == true)
	{
		translate([-50, 40, 0])
		upper_planet_carrier();
	
		translate([-45, 0, 0])
		cover();
	}
}

module planetary_assembled(exploded=0)
{
	translate([0, 0, sun_gear_hub_inset-exploded*24])
	rotate([0, 0, 180/sun_teeth*even(sun_teeth)])
	sun_gear();

	planetary_frame();

	*translate(ring_gear_bottom+[0, 0, vertical_clearance+exploded*24])
	lower_planet_carrier(print_orientation=0);

	translate(ring_gear_bottom+[0, 0, planet_carrier_gear_center[z]-planet_gear_height/2+exploded*36])
	{
		for(i=[0:num_planets-1]) assign(a1=i*floor(360/num_planets/planet_angle)*planet_angle+planet_offset) assign(a2=a1*ring_teeth/planet_teeth+180/planet_teeth*odd(sun_teeth))
		{
			rotate([0, 0, a1])
			translate([orbit_radius, 0, 0])
			rotate([0, 0, -a2])
			planet_gear(print_orientation=0);
		}
	}

	*translate(ring_gear_bottom+[0, 0, lower_planet_carrier_size[z]+vertical_clearance+exploded*48])
	upper_planet_carrier(print_orientation=0);

	*translate([0, 0, planetary_frame_size[z]+exploded*60])
	cover(print_orientation=0);
}

//!lower_planet_carrier(print_orientation=0);
$fn=100;


//linear_extrude(height=5.25)
/*linear_extrude(height=1.6)
    difference(){
        projection(cut=true){
        cover(print_orientation=0,baseFrameMod=0);
           
    }
     circle(d=40-4.5);
}*/

planetary_plate();

*planetary_assembled(exploded=cos($t*360)/2+.5);
*planetary_assembled(exploded=1);
*planetary_assembled();

function pitch_radius(number_of_teeth, diametral_pitch) = number_of_teeth * (180/diametral_pitch) / 360;
function outer_radius(number_of_teeth, diametral_pitch) = pitch_radius(number_of_teeth, diametral_pitch)+(1/(number_of_teeth / (pitch_radius(number_of_teeth, diametral_pitch) * 2)));
function odd(x) = x-(floor(x/2)*2);
function even(x) = 1-odd(x);