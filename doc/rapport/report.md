# Naavimac - Project Report

## **LIST OF FEATURES**

### *Required features:*

Feature                    | Done? 
:-------------------:      | :---: 
Drawing a scene with cubes | YES   
Editing cubes (types)      | NOT YET (not complete, waiting for textures)
Create/Delete/Extrude/Dig  | SOON
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
Textured cubes                     | SOON

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
For the selection, we wanted to show only the edges of the current selected cube. It looked pretty easy to by using a simple GL_LINES.

#### Object:


### **Drawing a scene with cubes**:
### **Editing cubes (types)**:
### **Create/Delete/Extrude/Dig**:
### **Procedural generation**:
### **Dual light conditions**:
### **Improved selection (mouse picking)**:
### **Improved selection (mouse picking)**:
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