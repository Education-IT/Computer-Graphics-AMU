#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"

#include "Box.cpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>



GLuint program;
Core::Shader_Loader shaderLoader;


Core::RenderContext sphereContext;
Core::RenderContext asteroida;
Core::RenderContext ship2;
Core::RenderContext spaceship;

glm::vec3 cameraPos = glm::vec3(-4.f, 0, 0);
glm::vec3 cameraDir = glm::vec3(1.f, 0.f, 0.f);
glm::vec3 spaceshipPos = glm::vec3(-4.f, 0, 0);
glm::vec3 spaceshipDir = glm::vec3(1.f, 0.f, 0.f);

GLuint VAO,VBO;

float aspectRatio = 1.f;
float aspectRatio2 = 1.f;

glm::vec3 lightColor = glm::vec3(0.9, 0.7, 0.8);



glm::mat4 createCameraMatrix()
{
	glm::vec3 cameraSide = glm::normalize(glm::cross(cameraDir,glm::vec3(0.f,1.f,0.f)));
	glm::vec3 cameraUp = glm::normalize(glm::cross(cameraSide,cameraDir));
	//glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);
	glm::mat4 cameraRotrationMatrix = glm::mat4({
		cameraSide.x,cameraSide.y,cameraSide.z,0,
		cameraUp.x,cameraUp.y,cameraUp.z ,0,
		-cameraDir.x,-cameraDir.y,-cameraDir.z,0,
		0.,0.,0.,1.,
		});

	cameraRotrationMatrix = glm::transpose(cameraRotrationMatrix);

	glm::mat4 cameraMatrix = cameraRotrationMatrix * glm::translate(-cameraPos);

	//cameraMatrix = glm::mat4({
	//	1.,0.,0.,cameraPos.x,
	//	0.,1.,0.,cameraPos.y,
	//	0.,0.,1.,cameraPos.z,
	//	0.,0.,0.,1.,
	//	});

	//cameraMatrix = glm::transpose(cameraMatrix);
	//return Core::createViewMatrix(cameraPos, cameraDir, up);

	return cameraMatrix;
}

glm::mat4 createPerspectiveMatrix()
{
	
	glm::mat4 perspectiveMatrix;
	float n = 0.3;
	float f = 70.;
	float a1 = glm::min(aspectRatio, 1.f);
	float a2 = glm::min(1 / aspectRatio, 1.f);
	perspectiveMatrix = glm::mat4({
		aspectRatio2,0.,0.,0.,
		0.,aspectRatio,0.,0.,
		0.,0.,(f+n) / (n - f),2*f * n / (n - f),
		0.,0.,-1.,0.,
		});

	
	perspectiveMatrix=glm::transpose(perspectiveMatrix);

	return perspectiveMatrix;
}

glm::mat4 createSpaceShipMatrix()
{
	glm::vec3 cameraSide = glm::normalize(glm::cross(spaceshipDir, glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 cameraUp = glm::normalize(glm::cross(cameraSide, spaceshipDir));
	glm::mat4 SpaceShipRotrationMatrix = glm::mat4({
		cameraSide.x,cameraSide.y,cameraSide.z,0,
		cameraUp.x,cameraUp.y,cameraUp.z ,0,
		-spaceshipDir.x,-spaceshipDir.y,-spaceshipDir.z,0,
		0.,0.,0.,1.,
		});


	glm::mat4 SpaceShipMatrix = glm::translate(spaceshipPos)  * SpaceShipRotrationMatrix  ;

	//cameraMatrix = glm::mat4({
	//	1.,0.,0.,cameraPos.x,
	//	0.,1.,0.,cameraPos.y,
	//	0.,0.,1.,cameraPos.z,
	//	0.,0.,0.,1.,
	//	});

	//cameraMatrix = glm::transpose(cameraMatrix);
	//return Core::createViewMatrix(cameraPos, cameraDir, up);

	return SpaceShipMatrix;
}


void drawObjectColor(Core::RenderContext& context, glm::mat4 modelMatrix, glm::vec3 color) {

	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 transformation = viewProjectionMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transformation);
	glUniform3f(glGetUniformLocation(program, "color"), color.x, color.y, color.z);
	Core::DrawContext(context);
}
void renderScene(GLFWwindow* window)
{
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	
	glm::mat4 transformation;
	float time = glfwGetTime();
	
	
	
	glUseProgram(program);
	glDepthMask(GL_FALSE);
	drawObjectColor(sphereContext, glm::eulerAngleZ(time / 4) * glm::translate(glm::vec3(0, 6.f, -7.f)) * glm::scale(glm::vec3(1.f)), glm::vec3(1, 1, 1));
	drawObjectColor(sphereContext, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(0, -6.f, 5.f)) * glm::scale(glm::vec3(1.f)), glm::vec3(1, 1, 1));
	drawObjectColor(sphereContext, glm::eulerAngleX(time / 6) * glm::translate(glm::vec3(15, 4.f, 4.f)) * glm::scale(glm::vec3(1.f)), glm::vec3(1, 1, 1));
	drawObjectColor(sphereContext, glm::eulerAngleX(time / 2) * glm::translate(glm::vec3(10, -4.f, 6.f)) * glm::scale(glm::vec3(1.f)), glm::vec3(1, 1, 1));
	glDepthMask(GL_TRUE);
																									
	
	drawObjectColor(ship2, createSpaceShipMatrix() * glm::translate(glm::vec3(0.f, -0.35f, -0.3f)) * glm::eulerAngleY(3.12f) * glm::scale(glm::vec3(0.006f)), glm::vec3(0.78, 0.78, 0.9));

	drawObjectColor(asteroida, glm::translate(glm::vec3(3.f, 0.f, 0.f))*glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
	
	drawObjectColor(sphereContext, glm::scale(glm::vec3(2.f)), glm::vec3(0.9, 0.9, 0.2));
	
	drawObjectColor(sphereContext, glm::eulerAngleY(-time / 4) * glm::translate(glm::vec3(3.f,0.f,0.f)) * glm::scale(glm::vec3(0.2f)), glm::vec3(1, 0.431, 0.0));
	drawObjectColor(sphereContext, glm::eulerAngleY(-time/4) * glm::translate(glm::vec3(3.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.5f, 0.f, 0.f))  * glm::scale(glm::vec3(0.1f)), glm::vec3(0.f, 0.f, 0.f));
	drawObjectColor(sphereContext, glm::eulerAngleY(-time / 4) * glm::translate(glm::vec3(3.f, 0.f, 0.f)) * glm::eulerAngleY(-time) * glm::translate(glm::vec3(-0.5f, 0.f, 0.f)) * glm::scale(glm::vec3(0.1f)), glm::vec3(0.f, 0.f, 0.f));
	drawObjectColor(sphereContext, glm::eulerAngleY(-time / 4) * glm::translate(glm::vec3(3.f, 0.f, 0.f)) * glm::eulerAngleZ(time) * glm::translate(glm::vec3(-0.5f, 0.f, 1.f)) * glm::scale(glm::vec3(0.1f)), glm::vec3(0.f, 0.f, 0.f));
	drawObjectColor(sphereContext, glm::eulerAngleY(-time / 4) * glm::translate(glm::vec3(3.f, 0.f, 0.f)) * glm::eulerAngleZ(-time) * glm::translate(glm::vec3(0.5f, 0.f, -1.f)) * glm::scale(glm::vec3(0.1f)), glm::vec3(0.f, 0.f, 0.f));
	drawObjectColor(sphereContext, glm::eulerAngleY(-time / 4) * glm::translate(glm::vec3(3.f, 0.f, 0.f)) * glm::eulerAngleX(time) * glm::translate(glm::vec3(-0.5f, 1.f, 0.f)) * glm::scale(glm::vec3(0.1f)), glm::vec3(0.f, 0.f, 0.f));
	drawObjectColor(sphereContext, glm::eulerAngleY(-time / 4) * glm::translate(glm::vec3(3.f, 0.f, 0.f)) * glm::eulerAngleX(-time) * glm::translate(glm::vec3(0.5f, -1.f, 0.f)) * glm::scale(glm::vec3(0.1f)), glm::vec3(0.f, 0.f, 0.f));

// "SATURN" =================================================================================================================================================================================================================================================================	
	drawObjectColor(sphereContext, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::scale(glm::vec3(0.5f)), glm::vec3(0.631, 0.494, 0.086));
	
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(1.f, 0.f, 0.f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-1.f, 0.f, 0.0f )) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.f, 0.f, -1.f )) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.f, 0.f, 1.f )) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));

		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.1f, 0.f, 0.9f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.3f, 0.f, 0.7f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.5f, 0.f, 0.5f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.7f, 0.f, 0.3f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.9f, 0.f, 0.1f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));

		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.1f, 0.f, -0.9f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.3f, 0.f, -0.7f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.5f, 0.f, -0.5f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.7f, 0.f, -0.3f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(0.9f, 0.f, -0.1f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));

		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.1f, 0.f, 0.9f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.3f, 0.f, 0.7f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.5f, 0.f, 0.5f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.7f, 0.f, 0.3f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.9f, 0.f, 0.1f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));

		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.1f, 0.f, -0.9f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.3f, 0.f, -0.7f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.5f, 0.f, -0.5f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
		drawObjectColor(asteroida, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(5.f, 0.f, 0.f)) * glm::eulerAngleY(time) * glm::translate(glm::vec3(-0.7f, 0.f, -0.3f)) * glm::scale(glm::vec3(0.001f)), glm::vec3(0, 0, 0));
// "SATURN" ===========================================================================================================================================================================================================================================================

	drawObjectColor(sphereContext, glm::eulerAngleY(-time / 2) * glm::translate(glm::vec3(7.f, 0.f, 0.f)) * glm::scale(glm::vec3(0.8f)), glm::vec3(0.21, 0.7, 0.839));
	drawObjectColor(sphereContext, glm::eulerAngleY(time / 5) * glm::translate(glm::vec3(9.f, 0.f, 0.f)) * glm::scale(glm::vec3(1.f)), glm::vec3(1, 0.427, 0.83));
	
	glUseProgram(0);
	glfwSwapBuffers(window);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / float(height);
	//aspectRatio = (height / float(width)) * 2;
	glViewport(0, 0, width, height);
	glOrtho(-aspectRatio, aspectRatio, -1, 1, -1, 1);
}
void loadModelToContext(std::string path, Core::RenderContext& context)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	context.initFromAssimpMesh(scene->mMeshes[0]);
}

void init(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);
	program = shaderLoader.CreateProgram("shaders/shader_4_1.vert", "shaders/shader_4_1.frag");

	loadModelToContext("./models/sphere.obj",sphereContext);
	loadModelToContext("./models/rock.obj", asteroida);
	loadModelToContext("./models/ship2.obj", ship2);
	loadModelToContext("./models/spaceship.obj", spaceship);
	printf("'space' -> to go up!");
	printf("\n'shift' -> to go down!");

}

void shutdown(GLFWwindow* window)
{
	shaderLoader.DeleteProgram(program);
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
	glm::vec3 spaceShipSide = glm::normalize(glm::cross(cameraDir, glm::vec3(0.f,1.f,0.f)));
	glm::vec3 spaceShipUp = glm::vec3(0.f, 1.f, 0.f);
	float angleSpeed = 0.0125f;
	float moveSpeed = 0.0125f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		spaceshipPos += spaceshipDir * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		spaceshipPos -= spaceshipDir * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		spaceshipPos += spaceShipSide * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		spaceshipPos -= spaceShipSide * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		spaceshipDir = glm::vec3(glm::eulerAngleY(angleSpeed) * glm::vec4(spaceshipDir, 0));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		spaceshipDir = glm::vec3(glm::eulerAngleY(-angleSpeed) * glm::vec4(spaceshipDir, 0));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		spaceshipPos += spaceShipUp*moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		spaceshipPos -= spaceShipUp * moveSpeed;

	//cameraDir = glm::normalize(-cameraPos);

	//spaceshipPos = cameraPos + 1.5 * cameraDir + glm::vec3(0.0f, -0.6f, 0.0f);
	//spaceshipDir = cameraDir;

	cameraPos = spaceshipPos - 1.35f * spaceshipDir + glm::vec3(0, 0.4, 0);
	cameraDir = spaceshipDir;


}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		renderScene(window);
		glfwPollEvents();
	}
}
//}