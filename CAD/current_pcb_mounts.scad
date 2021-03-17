// CAD script for the mounting hardware for the current measurement PCB
// Alan Reed 2021

// Current PCB dimensions
current_pcb_length = 31.5;
current_pcb_width = 13.1;
current_pcb_height = 1;
current_pcb_hole_offset_length = 17;
current_pcb_hole_offset_width = 2.9/2 + 0.6;
current_pcb_hole_diameter = 2.9;

// Current PCB spacer dimensions
current_pcb_spacer_height = 2;
current_pcb_input_offset = 5- current_pcb_length / 2;
current_pcb_sense_offset = current_pcb_length / 2 - 3;
current_pcb_contact_width = 8;
current_pcb_contact_length = 3;

// Current PCB mounting clamp dimensions
current_pcb_clamp_length = 8;
current_pcb_clamp_height = 5;
current_pcb_nut_diameter = 6;
current_pcb_nut_height = 1.5;
current_pcb_clamp_cutout_width = 6;
current_pcb_clamp_cutout_height = 2;

// This module generates its children in the positions of the current measurement PCB mounting holes
module current_pcb_holes(){
    for(i = [-current_pcb_width/2 + current_pcb_hole_offset_width, current_pcb_width/2 - current_pcb_hole_offset_width]){
        translate([current_pcb_length/2 - current_pcb_hole_offset_length, i, 0]){
            children();
        }
    }
}

// This module approximates the current measurement PCB, for testing fit
module current_pcb(){
    difference(){
        cube([current_pcb_length, current_pcb_width, current_pcb_height], center=true);
        
        current_pcb_holes(){
            cylinder(d=current_pcb_hole_diameter, h=10, center=true, $fn=20);
        }
    }
}

// This module generates a spacer for supporting the current PCB against the side of the enclosure
module current_pcb_spacer(){
    difference(){
        cube([current_pcb_length, current_pcb_width, current_pcb_spacer_height], center=true);
        
        current_pcb_holes(){
            cylinder(d=current_pcb_hole_diameter, h=10, center=true, $fn=20);
        }
        
        translate([current_pcb_input_offset, 0, 0]){
            cube([current_pcb_contact_length, current_pcb_contact_width, current_pcb_spacer_height * 2], center=true);
        }
        translate([current_pcb_sense_offset, 0, 0]){
            cube([current_pcb_contact_length, current_pcb_contact_width, current_pcb_spacer_height * 2], center=true);
        }
    }
}

// This module generates a clamp to allow the current PCB to be bolted down without the nuts damaging the components on the board
module current_pcb_clamp(){
    difference(){
        cube([current_pcb_clamp_length, current_pcb_width, current_pcb_clamp_height], center=true);
        
        translate([0, 0, current_pcb_clamp_cutout_height/2 - current_pcb_clamp_height/2 - 0.5]){
            cube([current_pcb_clamp_length + 1, current_pcb_clamp_cutout_width, current_pcb_clamp_cutout_height + 1], center=true);
        }
        
        for(i = [-current_pcb_width/2 + current_pcb_hole_offset_width, current_pcb_width/2 - current_pcb_hole_offset_width]){
            translate([0, i, 0]){
                cylinder(d=current_pcb_hole_diameter, h=10, center=true, $fn=20);
                translate([0, 0, current_pcb_clamp_height/2 - current_pcb_nut_height/2]){
                    cylinder(d=current_pcb_nut_diameter, h=current_pcb_nut_height, center=true, $fn=6);
                }
            }
        }
    }
}
//current_pcb();
current_pcb_clamp();
//current_pcb_spacer();