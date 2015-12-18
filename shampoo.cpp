/*
	CS475 Assignment 1

	A program which opens a window and draws the "shampoo."

	Use the arrow keys and PgUp,PgDn,
	keys to make the cube move.

	Modified from An Introduction to OpenGL Programming, 
	Ed Angel and Dave Shreiner, SIGGRAPH 2013

	Written by Parag Chaudhuri, 2015

	Further modified by: Dibyendu Mondal and Anand Bhoraskar
*/

#include "shampoo.hpp"

GLuint shaderProgram;
GLuint vbo, vao;

glm::mat4 rotation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
glm::mat4 translated_matrix;
glm::mat4 translate_to_origin_matrix;
glm::mat4 translated_back_matrix;
glm::mat4 scaled_matrix;
GLuint uModelViewMatrix;

glm::vec4 centroidPoint;

//-----------------------------------------------------------------

int num_points = 0; 
double mouse_click_z=0.0,redGradient=0.06,greenGradient=0.06,blueGradient=0.0;
const double z_increment=0.06;
//RGBA colors
glm::vec4 colors[3] = {
	glm::vec4(0.0, 0.0, 1.0, 1.0),
	glm::vec4(1.0, 0.0, 0.0, 1.0),
	glm::vec4(1.0, 1.0, 0.0, 1.0)
};

std::vector<glm::vec4> v_positions;
std::vector<glm::vec4> v_colors;
std::vector<glm::vec4> v_triangle_positions;
std::vector<glm::vec4> v_triangle_colors;


struct points
{
	float x,y,z,r,g,b;
};

std::vector<points> v;

//-----------------------------------------------------------------

void setModelView(){
		//translate origin to origin
		translate_to_origin_matrix = glm::translate(glm::mat4(1.0f),glm::vec3(-centroidPoint.x, -centroidPoint.y, -centroidPoint.z));
		translated_back_matrix = glm::translate(glm::mat4(1.0f),glm::vec3(centroidPoint.x,centroidPoint.y,centroidPoint.z));
		
		//rotate
		 rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
		 rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
		 rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
		// //back to centroid position
		// translated_matrix = glm::translate(rotation_matrix,glm::vec3(centroidPoint.x,centroidPoint.y,centroidPoint.z));

		ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
		translated_matrix = glm::translate(glm::mat4(1.0f),glm::vec3(xpos,ypos,zpos));

		// scaled_matrix = glm::scale(translated_matrix, glm::vec3(1,1,1));

		modelview_matrix =  ortho_matrix * translated_matrix * translated_back_matrix * rotation_matrix * translate_to_origin_matrix  ;

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
		// Draw 

}

void setBuffer(){
	glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec4)*(v_triangle_positions.size() + v_triangle_colors.size()), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(glm::vec4)*(v_triangle_positions.size()), &v_triangle_positions[0] );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec4)*(v_triangle_positions.size()), sizeof(glm::vec4)*(v_triangle_colors.size()), &v_triangle_colors[0] );
	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	
	GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
	glEnableVertexAttribArray( vColor );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_triangle_positions.size())) );
}

void initBuffersGL(void)
{
	
	//Ask GL for a Vertex Attribute Object (vao)
	glGenVertexArrays (1, &vao);
	//Set it as the current array to be used by binding it
	glBindVertexArray (vao);

	//Ask GL for a Vertex Buffer Object (vbo)
	glGenBuffers (1, &vbo);
	//Set it as the current buffer to be used by binding it
	glBindBuffer (GL_ARRAY_BUFFER, vbo);

	// Load shaders and use the resulting shader program
	std::string vertex_shader_file("vshader.glsl");
	std::string fragment_shader_file("fshader.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shaderProgram = csX75::CreateProgramGL(shaderList);
	glUseProgram( shaderProgram );

	setBuffer();
	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
}	

void add_point(points p){
	v.push_back(p);

	v_positions.push_back(glm::vec4(p.x,p.y,p.z,1.0));
	v_colors.push_back(glm::vec4(p.r,p.g,p.b,1.0));

	if(num_points >= 2){
		v_triangle_positions.push_back(v_positions[0]);
		v_triangle_positions.push_back(v_positions[num_points-1]);
		v_triangle_positions.push_back(v_positions[num_points]);
		v_triangle_colors.push_back(v_colors[0]);
		v_triangle_colors.push_back(v_colors[num_points-1]);
		v_triangle_colors.push_back(v_colors[num_points]);
	}
	//std::cout<<v_positions.size()<<"size"<<std::endl;
	num_points++;
}

void remove_point(){

	if(num_points){
		v_positions.pop_back();
		v_colors.pop_back();
		if (num_points >=3)
		{
			for (int i = 0; i < 3; ++i)
			{
				v_triangle_positions.pop_back();
				v_triangle_colors.pop_back();
			}		
		}
		num_points--;
	}
}

void renderGL(void)
{

	if (modelling_mode==false)
	{
		centroidPoint=centroid(v_triangle_positions);

		if (move_to_centroid)
		{
			xpos=-centroidPoint.x;
			ypos=-centroidPoint.y;
			zpos=-centroidPoint.z;
			move_to_centroid=false;
		}
		else if(load_file && !modelling_mode)
		{
			v_positions.clear();
			v_colors.clear();
			v_triangle_positions.clear();
			v_triangle_colors.clear();
			xpos=0.0,ypos=0.0,zpos=1.0,xrot=0.0,yrot=0.0,zrot=0.0;
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			num_points=0;
			//Filestream Buffer
			std::fstream file;
			file.open(filename.c_str(),std::fstream::in);
			for (int i = 0; file ; ++i)
			{
				points p;
				file>>p.x>>p.y>>p.z>>p.r>>p.g>>p.b;
				// std::cout<<p.x<<p.y<<std::endl;
				v_triangle_positions.push_back(glm::vec4(p.x,p.y,p.z,1.0));
				v_triangle_colors.push_back(glm::vec4(p.r,p.g,p.b,1.0));
				if(i%3==2)	num_points++;
			}
			file.close();
			
			load_file=false;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setBuffer();
		setModelView();
		glDrawArrays(GL_TRIANGLES, 0, v_triangle_positions.size());
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (start==true)
		{
			v_positions.clear();
			v_colors.clear();
			v_triangle_positions.clear();
			v_triangle_colors.clear();
			start=false;
			num_points=0;
			xpos=0.0,ypos=0.0,zpos=1.0,xrot=0.0,yrot=0.0,zrot=0.0;
			mouse_click_z=0.0,redGradient=0.06,greenGradient=0.06,blueGradient=0.0;
		}
		if(click_trigger)
		{
			click_trigger=0;
			if(shift_pressed)
			{
				if(num_points){
					remove_point();
					mouse_click_z-=z_increment;
					// std::cout<<num_points<<"num"<<std::endl;
				}
		// std::cout<<"size: "<<v_triangle_positions.size()<<" ";
			}
			else
			{
				// std::cout<<"size: "<<v_triangle_positions.size()<<" ";
				//std::cout<<v_triangle_positions.size();
				mouse_click_z+=z_increment;
				//std::cin>>mouse_click_z;
				points p;
				p.x = mouse_click_x/125 - 2;
				p.y = 2 - mouse_click_y/125;
				p.z = mouse_click_z;
				p.r = num_points*redGradient;
				p.g = num_points*greenGradient;
				p.b = num_points*blueGradient;
				add_point(p);
				// std::cout<<p.x<<" "<<p.y<<" "<<p.z<<" "<< num_points<<std::endl;
			}
		}
		else if(save_file && modelling_mode)
		{
			//Filestream Buffer
			std::fstream file;
			file.open(filename.c_str(),std::fstream::out);
			for (int i = 0; i < v_triangle_positions.size(); ++i)
			{
				file<<v_triangle_positions[i].x<<" "<<v_triangle_positions[i].y<<" "<<v_triangle_positions[i].z<<" "<<v_triangle_colors[i].r<<" "<<v_triangle_colors[i].g<<" "<<v_triangle_colors[i].b;
				file<<std::endl;
			}
			file.close();
			v.clear();
			// num_points=0;
			save_file=false;
		}
		setBuffer();
		setModelView();
		glDrawArrays(GL_TRIANGLES, 0, v_triangle_positions.size());
	}
		
}

int main(int argc, char** argv)
{
	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	//We want OpenGL 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//This is for MacOSX - can be omitted otherwise
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	//We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(512, 512, "CS475/CS675 Assignment1", NULL, NULL);
	if (!window)
		{
			glfwTerminate();
			return -1;
		}
	
	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	//Turn this on to get Shader based OpenGL
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err){
			//Problem: glewInit failed, something is seriously wrong.
			std::cerr<<"GLEW Init Failed : %s"<<std::endl;
		}

	//Print and see what context got enabled
	std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
	std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
	std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
	std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Mouse Callback
	glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Initialize GL state
	csX75::initGL();
	initBuffersGL();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
		{
			 
			// Render here
			renderGL();

			// Swap front and back buffers
			glfwSwapBuffers(window);
			
			// Poll for and process events
			glfwPollEvents();
		}
	
	glfwTerminate();
	return 0;
}

//-------------------------------------------------------------------------