#ifndef OVERLAY_H
#define OVERLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <camera.h>

// Call once after window creation (and after GLAD is loaded)
void overlay_init(GLFWwindow* window);

// Call before glfwSwapBuffers(window)
// Draws the camera info panel (uses draw_text internally)
void overlay_draw(GLFWwindow* window, const Camera* cam);

// --- General-purpose text drawing ---

// Draw text at pixel position (x, y) with the given RGBA color.
// Origin is top-left of the screen. y is the TOP of the text.
// scale: pixel size of each font pixel (1.0 = 1px per pixel, 2.0 = 2x, etc.)
void draw_text(GLFWwindow* window, const char* text, float x, float y,
               float r, float g, float b, float a, float scale);

// Measure the pixel width of a string at a given scale (useful for right-aligning).
float text_width(const char* text, float scale);

// Height of a single line of text at a given scale.
float text_height(float scale);

#endif