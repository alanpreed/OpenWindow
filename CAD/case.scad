// CAD script for the case and lid of the OpenWindow enclosure
// Alan Reed 2021

// Dimensions of the items contained within the enclosure
// OpenWindow PCB
pcb_length = 65;
pcb_width = 70;
pcb_height = 1;
pcb_hole_diameter = 2.5;
pcb_hole_inset = 5;
// Incoming connections terminal block
terminalblock_length = 23.4;
terminalblock_width = 67.7;
terminalblock_height = 16.2;
terminalblock_hole_diameter = 3.5;
terminalblock_hole_inset = 9.5;
// Relays
relays_length = 52.9;
relays_width = 60.8;
relays_height = 30.8;
// Current measurement PCB
current_pcb_length = 31.5;
current_pcb_width = 13.1;
current_pcb_height = 1;
current_pcb_hole_offset_length = 17;
current_pcb_hole_offset_width = 2.9/2 + 0.6;
current_pcb_hole_diameter = 2.5;

// Main box dimensions
pcb_standoff_height = terminalblock_height + 2;
box_contents_padding = 0.5;
box_length = pcb_length + 2 * box_contents_padding + 10;
box_width = pcb_width +relays_width + 2*box_contents_padding;
box_height = 20 + pcb_standoff_height;
box_wall_thickness = 1.5;

// Relay support block on the box lid
box_lid_relay_support_length = 8;
box_lid_relay_support_width = 45;
box_lid_relay_support_height = box_height - relays_height + 2;
box_lid_relay_support_offset = 22;

// Cable entry grommet dimensions
grommet_diameter = 12.7;
grommet_height = grommet_diameter/2 + 5;

// Lid cantilever clip dimensions
clip_length = 7;
clip_hook_length = 3;
clip_thickness = 2;
clip_width = 5;
clip_spine_width = 2;
clip_spine_depth = 2;
clip_depth = 1;

// This module generates its children in the positions of the main PCB mounting holes
module pcb_holes(){
    pcb_hole_locations = [[pcb_length / 2 - pcb_hole_inset, pcb_width / 2 - pcb_hole_inset, 0],
               [-(pcb_length / 2 - pcb_hole_inset), pcb_width / 2 - pcb_hole_inset, 0],
               [-(pcb_length / 2 - pcb_hole_inset), -(pcb_width / 2 - pcb_hole_inset), 0],
               [pcb_length / 2 - pcb_hole_inset, -(pcb_width / 2 - pcb_hole_inset), 0]];
    
    for(i=pcb_hole_locations){
        translate(i){
            children();
        }
    }
    
}

// This module approximates the main PCB, for testing fit in the box
module pcb(show_board = true){
    union(){
        difference(){
            cube([pcb_length, pcb_width, pcb_height], center=true);
            pcb_holes(){
                cylinder(d = pcb_hole_diameter, h = pcb_height * 3, center=true, $fn=10);
            }
        }
    }
}

// This module generates its children in the positions of the current measurement PCB mounting holes
module current_pcb_holes(){
    for(i = [-current_pcb_width/2 + current_pcb_hole_offset_width, current_pcb_width/2 - current_pcb_hole_offset_width]){
        translate([current_pcb_length/2 - current_pcb_hole_offset_length, i, 0]){
            children();
        }
    }
}

// This module approximates the current measurement PCB, for testing fit in the box
module current_pcb(){
    difference(){
        cube([current_pcb_length, current_pcb_width, current_pcb_height], center=true);
        
        current_pcb_holes(){
            cylinder(d=current_pcb_hole_diameter, h=10, center=true, $fn=20);
        }
    }
}

// This module generates its children in the positions of the terminal block mounting holes
module terminalblock_holes(){
    for(i=[-(terminalblock_width/2 - terminalblock_hole_inset), terminalblock_width/2 - terminalblock_hole_inset]){
        translate([0, i, 0])
        {
            children();
        }
    }
}

// This module approximates the terminal block, for testing fit in the box
module terminalblock(){
    difference(){
        cube([terminalblock_length, terminalblock_width, terminalblock_height], center=true);
        
        terminalblock_holes(){
            cylinder(d=terminalblock_hole_diameter, h=2*terminalblock_height, center=true, $fn=10);
        }
    }
}

// This module approximates the relays, for testing fit in the box
module relays(){
    translate([relays_length/2, relays_width/2, relays_height/2]){
        cube([relays_length, relays_width, relays_height], center=true);
    }
}

// Triangular prism module for use creating the cantilever clips
// from https://en.wikibooks.org/wiki/OpenSCAD_User_Manual/Primitive_Solids#polyhedron
module triangular_prism(l, w, h){
   polyhedron(
           points=[[0,0,0], [l,0,0], [l,w,0], [0,w,0], [0,w,h], [l,w,h]],
           faces=[[0,1,2,3],[5,4,3,2],[0,4,5,1],[0,3,4],[5,2,1]]
   );
}

// This module generates a cantilever clip, as used on the enclosure lid
module clip(with_spine = true){
    union(){
        cube([clip_thickness, clip_width, clip_length], center=true);
        
        translate([clip_depth, 0, clip_length/2 - clip_hook_length / 2]){
            rotate([0, 0, 90]){
                translate([-clip_width/2, -clip_thickness/2, -clip_hook_length/2]){
                    triangular_prism(clip_width, clip_depth, clip_hook_length);
                }
            }
        }
        if(with_spine){
            translate([ - clip_spine_depth, 0, 0]){
                rotate([0, 0, -90]){
                    translate([-clip_spine_width/2, -clip_thickness/2, -clip_length/2]){
                        triangular_prism(clip_spine_width, clip_spine_depth, clip_length);
                    }
                }
            }
        }
    }
}

// This module generates a hole and countersink for an m2.5 bolt
module bolt_m25(){
    countersink_depth = 1.4;
    diameter = 2.5;
    union(){
        rotate_extrude(angle=360, $fn=20){
            polygon([[0,0], [0, countersink_depth], [diameter/2, countersink_depth], [2.25, 0]]);
        }
        translate([0, 0, countersink_depth/2]){
            cylinder(r=diameter/2, h=20, $fn=20);
            
        }
    }
}

// This module generates the body of the box, without mounting holes
module box_border(){
    translate([0, 0, box_height/2]){
        difference(){
            
            // Hollowed out box
            union(){
                difference(){
                    translate([0,0,-box_wall_thickness/2]){
                        // Expand length and width by 2x wall, but height by only 1x as lid is separate 
                        cube([box_length + 2*box_wall_thickness, box_width + 2*box_wall_thickness, box_height + box_wall_thickness], center=true);
                    }
                    translate([0, 0, box_wall_thickness]){
                        cube([box_length, box_width, box_height + box_wall_thickness * 2], center=true);
                    }
                }
            }
        
            // Clip holes
            clip_hole_size = [box_wall_thickness * 3,clip_width, clip_hook_length];
            
            translate([0,0,box_height/2-(clip_length - clip_hook_length) - clip_hook_length/2]){
                translate([box_length/2,0, 0]){
                    translate([0, 3 * box_width/8, 0]){
                        cube(clip_hole_size, center=true);
                    }
                    translate([0, -3 * box_width/8, 0]){
                        cube(clip_hole_size, center=true);
                    }
                }
                mirror([1, 0, 0]){
                    translate([box_length/2,0, 0]){
                        translate([0, 3 * box_width/8, 0]){
                            cube(clip_hole_size, center=true);
                        }
                        translate([0, -3 * box_width/8, 0]){
                            cube(clip_hole_size, center=true);
                        }
                    }
                }
            }
        }
    }
}

// This module generates the lid for the enclosure
module box_lid(){
    union(){
        cube([box_length + 2*box_wall_thickness, box_width + 2*box_wall_thickness, box_wall_thickness], center=true);
        
        // Lid lip
        translate([0, 0, -box_wall_thickness]){
            difference(){
                cube([box_length, box_width, box_wall_thickness], center=true);
                cube([box_length - 2*box_wall_thickness, box_width - 2*box_wall_thickness, 2*box_wall_thickness], center=true);
            }
        }
        // Lid clips
        translate([0,0,-clip_length/2 - box_wall_thickness / 2]){
            translate([box_length/2 - clip_thickness / 2,0, 0]){
                translate([0, 3 * box_width/8, 0]){
                    rotate([180, 0, 0]){
                        clip();
                    }
                }
                translate([0, -3 * box_width/8, 0]){
                    rotate([180, 0, 0]){
                        clip();
                    }
                }
            }
            mirror([1, 0, 0]){
                translate([box_length/2 - clip_thickness / 2,0, 0]){
                    translate([0, 3 * box_width/8, 0]){
                        rotate([180, 0, 0]){
                            clip();
                        }
                    }
                    translate([0, -3 * box_width/8, 0]){
                        rotate([180, 0, 0]){
                            clip();
                        }
                    }
                }
            }
        }
        
        // Relay support block
        translate([-box_length/2 + box_lid_relay_support_length/2 + box_lid_relay_support_offset, -box_width/2 + relays_width/2 +box_contents_padding, -box_lid_relay_support_height/2 - box_wall_thickness/2]){
            cube([box_lid_relay_support_length, box_lid_relay_support_width, box_lid_relay_support_height], center=true);
        }
        
        // Strengthening ribs
        translate([0, 0, -box_wall_thickness]){
            for(i =[-box_width/4, 0, box_width/4]){
                translate([0, i, 0]){
                    cube([box_length, box_wall_thickness, box_wall_thickness], center=true);
                }
            }
            
            for(i =[-box_length/6, box_length/6]){
                translate([i, 0, 0]){
                    cube([box_wall_thickness, box_width, box_wall_thickness], center=true);
                }
            }
        }
    }
}

// This module generates the main body of the enclosure, by adding the bolt holes and cable entry hole
// to the box_border module
module box(){
    difference(){
        box_border();
        translate([-box_length/2 + box_contents_padding, -box_width/2 + box_contents_padding, 0]){
            translate([0, relays_width, -box_wall_thickness]){
                // Countersunk bolt holes for PCB and terminal block
                translate([pcb_length/2, pcb_width/2, 0]){
                    pcb_holes(){
                        bolt_m25();
                    }
                }
                translate([relays_length / 2, terminalblock_width/2, 0]){
                    terminalblock_holes(){
                        bolt_m25();
                    }
                    
                    // Cable entry hole
                    translate([0, 0, grommet_height]){
                        rotate([0, 90, 0]){
                            cylinder(d=grommet_diameter, h=box_width/2, center=true);
                        }
                    }
                }
            }
            translate([current_pcb_length/2 + relays_length - 20, -current_pcb_height/2 - box_wall_thickness, box_height - current_pcb_width/2 -box_wall_thickness - 0.5]){
                rotate([-90, 180, 0]){
                    current_pcb_holes(){
                        bolt_m25();
                    }
                }
            }
        }
    }
}


// Draw box and lid
box();

translate([0, 0, box_height + box_wall_thickness/2 + 20]){
    box_lid();
}

// Box contents, to demonstrate fit
if(false){
    translate([-box_length/2 + box_contents_padding, -box_width/2 + box_contents_padding, 0]){
        relays();
        translate([0, relays_width, 0]){
            translate([pcb_length/2, pcb_width/2, pcb_standoff_height + pcb_height/2]){
                pcb();
            }
            translate([relays_length / 2, terminalblock_width/2, terminalblock_height/2]){
                terminalblock();
            }
        }
        translate([current_pcb_length/2 + relays_length - 20, 0, box_height - current_pcb_width/2 -box_wall_thickness - 0.5]){
            rotate([90, 180, 0]){
                current_pcb();
            }
        }
    }
}