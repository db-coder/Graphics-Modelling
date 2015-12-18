/*
  A program which opens a window and draws the "color cube."

  Use the arrow keys and PgUp,PgDn, 
  keys to make the cube move.

  Written by - 
               Parag Chaudhuri
  Further modified by: Dibyendu Mondal and Anand Bhoraskar
*/
#ifndef _SHAMPOO_HPP_
#define _SHAMPOO_HPP_



// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "centroidFunctions.cpp"

// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=1.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
// Modeling mode on/off
bool modelling_mode=true,shift_pressed=false,save_file=false,load_file=false, move_to_centroid=false, start=false;
// Mouse Click Values
double mouse_click_x,mouse_click_y,click_trigger=0;
//Filename
std::string filename;
//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;

//-------------------------------------------------------------------------

#endif
