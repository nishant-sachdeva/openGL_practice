#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdio.h>
#include<iostream>

namespace {
   void errorCallback(int error, const char* description) {
      fprintf(stderr, "GLFW error %d: %s\n", error, description);
   }

   GLFWwindow* initialize() {

      int glfwInitReturnValue = glfwInit();
      // This function initializes a window and sends an appropriate return Value

      
      if (!glfwInitReturnValue) {
         fprintf(stderr, "Unable to initialize GLFW\n");
         return nullptr;
      }
      // If we reach here, it means that our screen has been initialized properly

      //Following 4 functions calls set the configuration options for the window that we just made
      
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      // These two tell the version of GLFW that we would like to use
      // Version = {Major.Minor}

      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      // this gives us access to the core profile 
      // We will get access to a smaller subset without the backward compatible features that we no longer need

     
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      // This line is required on MAC OS X for the window initialization to work

      GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
      // ( Width, Height, Window_Name, {ignore} , {ignore} )
      // we will learn about the last two parameters later
      // this window is what we shall use for the other following operations

      if (!window) {
         fprintf(stderr, "Unable to create GLFW window\n");
         glfwTerminate();
         return nullptr;
      }

      glfwMakeContextCurrent(window);
      // here, we tell GLFW to make our window's context as it's main context on the present thread that it's running on



      int gladInitRes = gladLoadGL();
      if (!gladInitRes) {
         fprintf(stderr, "Unable to initialize glad\n");
         glfwDestroyWindow(window);
         glfwTerminate();
         return nullptr;
      }
      // note that OPENGL is just a specification. Different libraries have different implementations
      // Here, we shall use the one called GLAD
      // GLAD manages function pointers for OpenGL. We wnat to initialize GLAD before we call any OpenGL function


      return window;
   }
}

int main(int argc, char* argv[]) {
   glfwSetErrorCallback(errorCallback);

   GLFWwindow* window = initialize();
   if (!window) {
      return 0;
   }

   // Set the clear color to a nice green
   // can change it to any other color as well
   glClearColor(0.8f, 0.6f, 0.4f, 1.0f);

   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      // sets the color of the window to be the one as specified by the glClearColor function

      glfwSwapBuffers(window);
      // have two buffers helps us avoid rendering : We will cover this later


      glfwPollEvents();
      // checks if any events have happened { key presses etc}
   }
   // The game loop

   glfwDestroyWindow(window);
   // Destroys the window after we have closed it

   glfwTerminate();
   // clean/delete all resources that were allocated
   std::cout << glGetString(GL_VERSION) << std::endl; 
   return 0;
}