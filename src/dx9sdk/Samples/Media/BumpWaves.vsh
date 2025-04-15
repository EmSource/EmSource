vs.1.1

dcl_position v0
dcl_texcoord v1

m4x4 oPos, v0, c3 ; transform position to the projection space

; Compute vertex position in the camera space - this is our texture coordinates
dp4 r0.x, v0, c0 
dp4 r0.y, v0, c1 
dp4 r0.z, v0, c2 

; Do the rest of texture transform (first part was combined with the camera matrix) 
rcp r0.z, r0.z 
mad oT1.x, r0.x, r0.z, c8.x 
mad oT1.y, r0.y, r0.z, c8.y 

mov oT0.xy, v1     ; Copy input texture coordinates for the stage 0;
