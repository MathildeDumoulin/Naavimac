# Naavimac - Project Report

## **LIST OF FEATURES**

### *Required features:*

Feature                    | Done? 
:-------------------:      | :---: 
Drawing a scene with cubes | YES   
Editing cubes (types)      | NOT YET (not complete, waiting for colored cubes)
Create/Delete/Extrude/Dig  | YES
Procedural generation      | NOT YET
Dual light conditions      | SOON

### *Optionnal features:*

Feature                            | Done? 
:-------------------:              | :---: 
Improved selection (mouse picking) | YES   
Painting tool                      | NO
Sculpting tool                     | NO
Loading/Saving map                 | NOT YET
Loading 3D Models                  | NO
Spatial discretization             | NO
Textured cubes                     | ALMOST DONE

### *Our features:*

Feature                | Done? 
:-------------------:  | :---: 
Nothing for now

____________________________________

## **FEATURES IN DETAIL**

### **Preamble**:

#### Cube Primitive:
The first thing we had to do for this project was to draw a cube with OpenGL.
Because we already knew the cube will be textured, we decided to create it with 24 vertices (4 per face). Of course, as we are doing indexed rendering, we also needed 36 indexes per cube.

Instead of thinking too much about the vertices' position in 3D space and their normals, we decided to create only one face with homogeneous coordinates and then, to use 6 different matrices to place this face in the right space. Then, we just had to push the vertices and indexes attributes inside our cube primitive.

#### CubeEdges Primitive:
For the selection, we wanted to show only the edges of the current selected cube. It looked pretty easy to do by using a simple GL_LINES. But how to deal with its thickness since drawing wide lines (using glLineWidth with a value of more than 1.0) seems to be a deprecated feature, because not supported by every GPU?
The goal is indeed to draw rectangles instead of lines so we decided to try something. After several hours looking for a solution to this problem, testing some unsuccessful things with the vertex shader, we tried to experiment with the Geometry Shader.

Note: Geometry Shader is know to be very slow. We use it only for drawing 24 triangles (12 edges).

Here is the idea: 

From 8 points ("real" vertices of the Cube Primitive), we submit 12 lines to the Geometry Shader. It takes the Clip-Space position of both points composing a line. It calculates the direction of the line (simple vector) and its normal. Then, it applies the normal to each point in both "plus and minus" direction to generate two new vertices.

DESSSSIIINNNN

Finally, OpenGL draws two triangles which form the new "line" on the screen.
To be honest, we did not succeed to get exactly what we wanted since the cube corners are straight, the lines make some aliasing and the thickness is not consistent (on the screen) wherever the camera is. However, doing that was an interesting step discovering more and more how the 3D pipeline really works.

#### Object:
The Object Class is really simple. Its goal is to get vertices and indexes data and to push it into the GPU Buffers (creating a VBO and a IBO).

Like this, we can easily create a Cube Object from a Cube Primitive :
```cpp
Object cubeObj = Object(Cube());
```

#### Instance:
The Instance Class is one of the more important. It firstly binds Object Buffers inside a Vertex Array Object. And above all, it defines a new Buffer (vec3 - position in world) sent to the GPU to allow Instanced Rendering.

How to create an instance?
```cpp
Instance cube(1, cubeObj); // First parameter defines the number of instance, second parameter is the Object "form" we want to draw.
```

Main methods:
```cpp
drawInstances(const Scene&, const ShadingProgram&, GLenum mode); // Draw all the instances
addInstance(const vec3&); // Add a new position inside the buffer
removeInstance(const vec3&); // Remove a specific position from the buffer
```

### **Drawing a scene with cubes**:
Now, we know how to draw several cubes. Great! We still need to deal with the different types of cube. The idea is pretty simple, let's take a look at the CubeList class!

```cpp
enum CubeType {
    NONE, DIRT, WATER
};

class CubeList {
    private:
        std::vector<CubeType> m_world;
        std::map<CubeType, std::shared_ptr<Instance>> m_instances;

        // Some other privates methods we do not care here...

    public:
        CubeList(const Object& obj);
        ~CubeList() = default;

        void type(const glm::vec3& vec, const CubeType& newType); //Setter
        const CubeType type(const glm::vec3& vec) const; //Getter

        std::shared_ptr<Instance> instance(const CubeType& type);
};  
```

To define the type, we use an enum. We thought using a strategy design pattern but it was not so appropriate in this context.

The Class has two member attributes: 
- **m_world** is a simple array of CubeType. It describes every single cube in the world (even non existing cubes). Like this, we can instantly know what is the CubeType corresponding of a specific position (dealing with a bit of index-position conversion behind it). If there is no cube, the CubeType is : NONE.

- **m_instances** is a map of Instance pointers (smart pointers, to be accurate). The key to find the good instance is the CubeType corresponding. Like this, we have as many instances as CubeTypes (minus one because of the NONE type).

Why doing this way? *2 reasons:*
- Let us imagine the world is very big but only a few cubes are really drawn, it would take a lot of memory to have a structure containing a position (vec3) AND a type for each single possible cube of the world since only a few ones are really existing.
- To make the Instanced Rendering work, we need to send the position of the specific cubes in a buffer. So, having several arrays (one per type) ready to send to the GPU is essential.

### **Editing cubes (types)**:
TO DO !

### **Create/Delete/Extrude/Dig**:
These functions are directly linked to the CubeType. Indeed, to **Create** a cube, we simply change its type from *NONE* to *SOMETHING* and vice-versa to **Delete** a cube.

Extrude/Dig : TO DO !

### **Procedural generation**:
TO DO !

### **Dual light conditions**:
TO DO !

### **Improved selection (mouse picking)**:
To allow the mouse selection, we did some cheating OpenGL hacks.
The idea is very simple and absolutely not optimized:

When we press the Right Mouse Button, we draw the scene a first time but with smaller cubes (just a bit smaller, we will see later why) and we transform the Mouse coordinates from Screen Space to World Space. To get the appropriate depth, we use the glReadPixels function.

Like this, we have floating points coordinates, so we make them round.
Then, we check if the current position in World Space corresponds to a not-NONE cube. If so, we update the position of the selection to this cube. If not, we calculate a new position in the same direction (camera/mouse) and we arbitrarily place it 10 cubes in "front" of the camera. 

Now, why drawing smaller cubes?

The normal way to do that kind of mouse picking object is to attribute a different color to each object and to get the color picked by the mouse to retrieve the corresponding object. Pretty simple.
BUT since we do not draw our cubes from only one buffer, it is more complicated to give to each object a specific color (often based on an ID). It is possible to generate a color from the cube position but it seems to be quite limited (maximum of 256^3 cubes??).

So doing the way we do, it works pretty well and it is pretty easy to understand. The only problem comes with the depth value. Sometimes, where you expect something like 1.500 or less, you get 1.504 and it makes the round operation wrong. The cube selected is not the good one. The solution is to draw the cubes just a bit smaller and like this, the round operation works well every time (because the faces of the cube are closer to the gravity center).

### **Painting tool**:
### **Sculpting tool**:
### **Loading/Saving map**:
### **Loading 3D Models**:
### **Spatial discretization**:
### **Textured cubes**:

____________________________________

## **DIFFICULTIES**

____________________________________

## **INDIVIDUAL FEELINGS**