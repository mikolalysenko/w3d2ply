W3DView is a viewer that can view W3D model files including materials, lighting, textures, alpha blending/shaders, animation and other features.

W3DView is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version. See the file COPYING for more details.

A W3D file is a 3d model file containing model information to be rendered and interpreted by the WW3D engine created by Westwood Studios and used in the PC computer game Command and Conquer Renegade. A W3D file contaists of a number of chunks, each chunk contains either sub-chunks or data. My W3D Viewer interpretes the following main types of data:
Meshes (which hold information on a single object within a model)
Hierarchies (which hold the skelleton of a model)
Animations (which hold information about making the skelleton move so it will animate)
HLODs (which hold information linking meshes to bones
and HModels (which are an earlier variant of the HLOD)
Several other things may be present in the file but they are ignored by my program.
read the code (specificly loader.c and w3d_file.h) to see more about the internal representation of data on a W3D file.
The origonal W3D files that come with C&C Renegade were created using a custom plugin created by westwood studios in conjunction with 3D Studio MAX (a powerfull 3D rendering program, see http://www4.discreet.com/3dsmax/).
There is also a special lightweight free version of 3D Studio MAX called GMAX (http://www.discreet.com/products/gmax/) that is specificly for use by people modifying games.
There is a GMAX Gamepack (that is based on the custom 3D studio plugin mentioned above) that can export to a W3D file. This is how "fan-made" models are created.

The W3D format and the WW3D engine use *.DDS (DirectDrawSurface) files and *.TGA (Truevision Targa) for textures. DDS is a microsoft format invented for use with DirectX that supports various forms of compression and alpha channels. TGA is a format invented by Truevision that supports RLE compressed and uncompressed images. My program supports textures in both formats. Various paint programs and utillities (such as Photoshop via a plugin and the microsoft Direct X Texture utillity) can produce these files.

Double click w3dview.exe.
A window will open.
Enter all the w3d files to load (order doesnt matter) followed by the string NULL.
Enter in the initial zoom value (sutable values given for each w3d file in the sample list below)
For vechicles in vehicle mode, you want a bigger zoom value so you can see the vehicles as they move.
If the model is a vehicle, it will now ask you to enter in a speed. Enter a speed in scale meters per second.
Then enter a value for the suspension travel, all vechicles have a number that looks acceptable listed in the samples list.
The model will then display. If it has animation, it will play the animation in a loop. (some animations were designed not to loop and will therefore not look quite correct when looping)
Once in the program, the folowing keys are available.
The number keys 1,2,3,4,5 and 6 change the view to view from one of the 6 faces of a virtual cube.
The z and Z (thats shift-z) keys change the zoom level.
The s and S (thats shift-s) keys change the speed of the vechicle when in vehicle mode, each press with change the speed by 1 scale meter per second
The v key starts vehicle mode. The vechicle will start moving forwards and the wheels (or more specificly the wheel bones) will move as appropriate.
The arrow keys will move the model up/down/left/right in the viewport.

This program does not interpret all features of the W3D file format. (due to time and my skills with OpenGL)
Specificly, the folowing missing features/"defects" are noticable in the sample models: (all are not bugs, all are due to the way w3d works and/or features I was unable to implement)
In order to render correctly, alpha-blended polygons should be sorted from back to front.
I was unable to implement this, therefore some models with alpha-blended polygons may display some alpha polygons incorrectly  from some angles (for example the muzzle flash on the GDI Humvee and the wheels on the Old GDI Humvee)
Due to how vehicle models work, when not in vehicle mode, the wheels are show tucked right up into the model. This is how they are supposed to be, the suspension number is what makes the wheels go down to the correct height.
Some models use an environemt map for reflection purposes. (such as the windows on the GDI humvee and many models with bits of shiny metal such as pipes) Due to time and skills, I was unable to implement environment maps.
Some models use meshes aligned to always face the camera. This feature is unimplemented due to lack of time (its used on at least the GDI humvee muzzle flash) so the mesh will be drawn but it wont face the camera from all angles, only from one angle.
Some models use multi-pass meshes where the same mesh has multiple materials/blend settings/textures/etc applied to it. Currently, my program doesnt correctly handle this. It does make an attempt to render both sets of settings but due to a lack of time, it doesnt handle them correctly. But the settings that are rendered are (on the sample models), are the base settings (as opposed to any detail settings added on top).

This is a list of all the sample w3d files, sutable settings to use plus any notes about things that dont look 100%.
Playing with the zoom, view and move keys can get a better view of some files (for example if a model is not visible, try viewing from other angles)
Models that specify a suspension value are vechicles that can be viewed in vechicle mode.

beachgrass.w3d
Some beach grass
Zoom value: 10

bulletshell_1.w3d
A bullet
Zoom value: 1

dr_3.w3d
A locked door
Zoom value: 10

dsp_drumstack1.w3d
A palet with metal drums stacked on it
Zoom value: 5

dsp_ivbagclear.w3d
A IV bag on a stand (like with a drip)
Zoom value: 5

dsp_mtibtriple.w3d
Some crystals of Tiberium
Zoom value: 2

dsp_pingpong.w3d
A Ping-Pong table
Zoom value: 5

dsp_sockpole.w3d
A windsock
Zoom value: 10

dsp_sodamachine.w3d
A soda machine
Zoom value: 10

dsp_tvmonitor.w3d
A TV set
Zoom value: 5

dsp_vending.w3d
A snack machine
Zoom value: 10

f_cm_rifl.w3d
A magazine from an Auto Rifle
Zoom value: 1

f_ga_rock_fire.w3d
Rocket Launcher fire animation.
Load thius with f_gm_rock.w3d to see the animation.

f_gm_lsrr.w3d
A Laser Rifle
Zoom value: 2

f_gm_rifl.w3d
An Auto Rifle
Zoom value: 2

f_gm_rock.w3d
A Rocket Launcher
Zoom value: 3

gd_tower.w3d
A guard tower
Zoom value: 20

hnd_arm_door.w3d
A door
Zoom value: 5

hnd_scrn.w3d
A monitor screen
Zoom value: 5

humve1l1.w3d
An old GDI Humvee
Zoom value: 10
Use 0.25 for the suspension.
Due to the alpha blending issue mentioned above, the wheels on this model dont render properly.

lvl-srdefenses2.w3d
A large desert level.
Zoom value: 1000
Warning, this model is very large and may not render on slower/older machines

mct_nod.w3d
A Nod Master Control Terminal.
Zoom value: 5

mgagd_ag_5.w3d
A Purchase Control Terminal from the GDI Advanced Guard Tower.
Zoom value: 20
You will need to use the arrow keys and zoom and view keys to move this model into the field of view and get acceptable detail.

mgagd_tv.w3d
A computer screen
Zoom value: 5
You will need to use the arrow keys and zoom and view keys to move this model into the field of view and get acceptable detail.

mgsilo_ext.w3d
GDI Silo Exterior
Zoom value: 40

mnatr_lift.w3d
An Elevator
Zoom value: 10

mnhnd_elev01.w3d
An Elevator
Zoom value: 20

mnhnd_int_lm001.w3d
The interior of the Hand Of Nod
Zoom value: 50

mnsilo_ext.w3d
Nod Silo Exterior
Zoom value: 40

mp_glacierts.w3d
A level set inside a glacier
Zoom value: 500
Warning, this model is very large and may not render on slower/older machines

p_keycrd_red.w3d
A Keycard
Zoom value: 2

plxy_door.w3d
A door
Zoom value: 10

pwr_glass_door.w3d
A door
Zoom value: 10

pwr_rnd_door.w3d
A door
Zoom value: 10

ref_belt01.w3d
A conveyer belt from a Tiberium Refinery
Zoom value: 15

ref_crusher.w3d
A Tiberium Crusher from a Tiberium Refinery
Zoom value: 10

ref_mon.w3d
A monitor screen
Zoom value: 5

ref_tib_dump.w3d
The Tiberium Dump Arms from a Tiberum Refinery
Zoom value: 40
Warning, this model is very large and may not render on slower/older machines

sroilpump.w3d
An Oil Pump
Zoom value: 50
Warning, this model is very large and may not render on slower/older machines

swing_light.w3d
A ceiling light
Zoom value: 5

tiberium.w3d
Some Tiberium
Zoom value: 5

v_gdi_apc.w3d
A GDI Armoured Personell Carrier
Zoom value: 10
Use 0.35 for the suspension

v_gdi_gboat.w3d
A GDI Gunboat
Zoom value: 100

v_gdi_humvee.w3d
A GDI Humvee
Zoom value: 10
Use 0.55 for the suspension

v_gdi_mammth.w3d
A Mammoth Tank
Zoom value: 10
Use 0.15 for the suspension

v_gdi_orca.w3d
A GDI Orca
Zoom value: 10
The game treats this as a vehicle even though it doesnt actually have wheels, there is special logic (that I didnt re-create) for helicoptors. Use whatever value for the suspension and press v to make it "fly" across the screen as though it was driving.

v_nod_cannon.w3d
A Nod Cannon Emplacement
Zoom value: 5

v_nod_flame.w3d
A Nod Flame Tank
Zoom value: 15
Use 0.15 for the suspension

v_nod_stealth.w3d
A Nod Stealth Tank
Zoom value: 10
Use 0.15 for the suspension

v_nod_turret.w3d
A Nod Turret
Zoom value: 10

v_pickup01.w3d
A Pickup Truck
Zoom Value: 10
Use 0.25 for the suspension

wep#construct.w3d
The Vehicle Construction Arms from the GDI Weapons Factory
Zoom Value: 30

See the comments in the code for information on the function of each piece of code.

The devil.lib, ilu.lib, ilut.lib, devil.dll, ilut.dll and ilu.dll plus the .h files in the il folder are part of the DevIL image library and are (C) whoever wrote that library.
animation.c, bone.c, defs.c, loader.c, lod.c, matrix.c, mesh.c and w3dview.c are (C) 2004 Jonathan Wilson.
animation.h, bone.h, defs.h, loader.h, lod.h, matrix.h, mesh.h, w3d.h and w3dstruct.h are (C) 2004 Jonathan Wilson
bittype.h is (C) 2002-2004 Jonathan Wilson and is based on information provided by Westwood Studios.
w3d_file.h is (C) Westwood Studios but has been modified by me to compile fine in straight C code.
All other code (GLUT, OpenGL, Windows, the Visual C++ runtime library etc) is (C) whoever wrote it.

Thanks to the fine people at Westwood Studios (such as Greg Hjelstrom) for providing the information I needed on W3D files and how they work. In particular, thanks to Greg Hjelstrom for getting the w3d_file.h released to the public in the first place. 
Thanks also to SomeRhino and others in the renegade modding community for providing needed information on the W3D files and the WW3D engine.
Thanks to the people on IRC (particularly efnet #OpenGL) and the people on usenet comp.graphics.api.opengl for providing information on OpenGL and how to do the stuff I needed to do.
Thanks to skywing of the ReactOS project for providing the Direct3D hook stuff I used to interregate the WW3D engine and find out settings for the default lighting, the projection matrix and the 6-faces-of-a-cube rotation model-view matricies plus other things.

Thanks to AircraftKiller, SomeRhino and Westwood Studios for creating/providing the sample W3D files and textures provided with W3DView.

Small note:
The program as included on the CD will compile with Borland C++ in the labs however the provided executable is compiled with Visual C++ 7.1 due to me not having enough time to find a copy of Borland C++ to compile it with. Should compilation with Borland C++ be required, use the provided w3dview.ide file.

The program should run straight from the CD on any system with a reasonable graphics card and CPU and with OpenGL and GLUT32.dll installed. It has been tested on Windows XP but should run fine on older windows versions.

All sample models have been tested and work on my system. Had I had more time, I would have added support for more features (in fact, I may do so in the future once I release the code for others to share)
