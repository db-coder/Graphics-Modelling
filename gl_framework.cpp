#include "gl_framework.hpp"

extern GLfloat xrot,yrot,zrot,xpos,ypos,zpos;
extern double mouse_click_x,mouse_click_y,click_trigger;
extern bool modelling_mode,shift_pressed,save_file,load_file,move_to_centroid,start;
extern std::string filename;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {


    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_LEFT && modelling_mode==false)
      yrot -= 0.1;
    else if (key == GLFW_KEY_RIGHT && modelling_mode==false)
      yrot += 0.1;
    else if (key == GLFW_KEY_UP && modelling_mode==false)
      xrot += 0.1;
    else if (key == GLFW_KEY_DOWN && modelling_mode==false)
      xrot -= 0.1;
    else if (key == GLFW_KEY_PAGE_UP && modelling_mode==false)
      zrot += 0.1;
    else if (key == GLFW_KEY_PAGE_DOWN && modelling_mode==false)
      zrot -= 0.1;
    else if (key == GLFW_KEY_W && modelling_mode==false)
      ypos += 0.1;
    else if (key == GLFW_KEY_S && modelling_mode==false)
      ypos -= 0.1;
    else if (key == GLFW_KEY_A && modelling_mode==false)
      xpos += 0.1;
    else if (key == GLFW_KEY_D && modelling_mode==false)
      xpos -= 0.1;
    else if (key == GLFW_KEY_Z && modelling_mode==false)
      zpos += 0.1;
    else if (key == GLFW_KEY_X && modelling_mode==false)
      zpos -= 0.1;
    else if ((key == GLFW_KEY_RIGHT_SHIFT || key == GLFW_KEY_LEFT_SHIFT) && action == GLFW_PRESS)
    {
		shift_pressed=true;
    }
    else if ((key == GLFW_KEY_RIGHT_SHIFT || key == GLFW_KEY_LEFT_SHIFT) && action == GLFW_RELEASE)
    {
		shift_pressed=false;
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        printf("Modelling Mode\n");
        modelling_mode=true;
        start=true;
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS && modelling_mode==false)
    {
        move_to_centroid=true;
    }
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        std::cout<<"Inspection Mode\n";
        modelling_mode=false; 
    }  
    else if (key == GLFW_KEY_K && action == GLFW_PRESS)
    {
        std::cout<<"Enter Filename : ";
        std::getline(std::cin, filename);
        save_file=true;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS && modelling_mode==false)
    {
        std::cout<<"Enter Filename : ";
        std::getline(std::cin, filename);
        load_file=true;
    }  
}

  //Mouse Callback
  void mouse_button_callback(GLFWwindow* window, int button, int action,  int mods)
  {
  	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE ){
      click_trigger=1;
      glfwGetCursorPos (window, &mouse_click_x, &mouse_click_y);
  	}
  }
};
