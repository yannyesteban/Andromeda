//
// Created by yanny on 23/1/2020.
//

#include "Cube3D.h"
#include "Application.h"

Cube3D::Cube3D() {

}

Cube3D::~Cube3D() {

}

void Cube3D::init() {
    sh =  new ShadersManager();

    if(2>10) {
        sh->setVS("shaders/solid_vs.glsl");
        sh->setFS("shaders/solid_fs.glsl");
        sh->addAttrib({0, 3, "vPosition"});
    }else{
        sh->setVS("shaders/Cube3D_vs.glsl");
        sh->setFS("shaders/Cube3D_fs.glsl");
        sh->addAttrib({0, 3, "vPosition"});
        sh->addAttrib({1, 3, "vColor"});
        sh->addAttrib({2, 3, "vNormal"});
    }

    sh->Program();
    MVPid = sh->getUniformLocation("MVP");

    Mid = sh->getUniformLocation("M");
    Vid = sh->getUniformLocation("V");
    Pid = sh->getUniformLocation("P");

    _LOGE("apect %d, %d, %d, %d", MVPid, Mid, Vid, Pid);
}

void Cube3D::render(glm::mat4 MVP) {
    this->MVP = MVP;
    glUseProgram(sh->programObject);



    glm::mat4 projection;
    projection = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, -10.0f, 10.0f);
    glUniformMatrix4fv(Pid, 1, GL_FALSE, &projection[0][0]);

    // Camera matrix
    glm::mat4 view       = glm::lookAt(
            glm::vec3(0,0,5), // Camera is at (4,3,-3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );



    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    Model = glm::scale(Model,glm::vec3(1.0f * Application::YAspect, 1.0f * Application::XAspect, 1.0f));
    //_LOGE("apect %f, %f %d, %d, %d",Application::XAspect,Application::YAspect, Mid, Vid, Pid);
    static GLfloat dd= 0;

    if(dd>360){
        dd = 0;
    }
    dd=dd+2.0;
    float radians = dd;
    Model = glm::rotate(Model,glm::radians(360-dd),glm::vec3(1.0,0.0,0.0));
    Model = glm::rotate(Model,glm::radians(radians),glm::vec3(0.0,1.0,1.0));

    glUniformMatrix4fv(Mid, 1, GL_FALSE, &Model[0][0]);

    glUniformMatrix4fv(Vid, 1, GL_FALSE, &view[0][0]);
    MVP = projection * view * Model ;


    glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);
    //_LOGE("glBindAttribLocation MVPid: %d", MVPid);
    GLint textColor = glGetUniformLocation(sh->programObject, "textColor");
    //glUniform4f(textColor, color.x, color.y, color.z, color.w);
    glUniform4f(textColor, 0.2, 0.522, 1.0, color.w);
    GLfloat vVertices_[] = {
            posX,       posY,         posZ,
            posX+width, posY,         posZ,
            posX+width, posY+height,  posZ,
            posX,       posY+height,  posZ,
    };

    GLushort  indices_[] = {0,1,2,0,2,3};

    GLfloat vVertices__[] = {
            // FRONT
            posX,       posY,         posZ, // 0
            posX+width, posY,         posZ, // 1
            posX+width, posY+height,  posZ, // 2
            posX,       posY+height,  posZ, // 3

            // BACK
            posX,       posY,         posZ-depth, // 4
            posX+width, posY,         posZ-depth, // 5
            posX+width, posY+height,  posZ-depth, // 6
            posX,       posY+height,  posZ-depth, // 7

            // RIGHT
            posX+width, posY,         posZ, // 8==1
            posX+width, posY,         posZ-depth, // 9==5
            posX+width, posY+height,  posZ-depth, // 10==6
            posX+width, posY+height,  posZ, // 11==2

            // TOP
            posX,       posY+height,  posZ, // 12==3
            posX+width, posY+height,  posZ, // 13==2
            posX+width, posY+height,  posZ-depth, // 14==6
            posX,       posY+height,  posZ-depth, // 15==7

            // LEFT
            posX,       posY,         posZ-depth, // 16==4
            posX,       posY,         posZ, // 17==0
            posX,       posY+height,  posZ, // 18==3
            posX,       posY+height,  posZ-depth, // 19==7

            // BOTTOM
            posX,       posY,         posZ-depth, // 20==4
            posX+width, posY,         posZ-depth, // 21==5
            posX+width, posY,         posZ, // 22==1
            posX,       posY,         posZ, // 23==0
    };

    //posX = posX-width/2;
    //posY = posY-height/2;
    //posZ = posZ-depth/2;

    GLfloat sX = width /2;
    GLfloat sY = height /2;
    GLfloat sZ = depth /2;

    GLfloat vVertices[] = {
            // FRONT
            -sX, -sY,  sZ, // 0
             sX, -sY,  sZ, // 1
             sX,  sY,  sZ, // 2
            -sX,  sY,  sZ, // 3

            // BACK
            -sX, -sY,  -sZ, // 4
             sX, -sY,  -sZ, // 5
             sX,  sY,  -sZ, // 6
            -sX,  sY,  -sZ, // 7

            // RIGHT
            sX, -sY,  sZ, // 1 8==1
            sX, -sY,  -sZ, // 5 9==5
            sX,  sY,  -sZ, // 6 10==6
            sX,  sY,  sZ, // 2 11==2

            // TOP
            -sX,  sY,  sZ, // 3 12==3
            sX,  sY,  sZ, // 2 13==2
            sX,  sY,  -sZ, // 6 // 14==6
            -sX,  sY,  -sZ, // 7 15==7

            // LEFT
            -sX, -sY,  -sZ, // 4 16==4
            -sX, -sY,  sZ, // 0 17==0
            -sX,  sY,  sZ, // 3 18==3
            -sX,  sY,  -sZ, // 7 19==7

            // BOTTOM
            -sX, -sY,  -sZ, // 4 20==4
            sX, -sY,  -sZ, // 5 21==5
            sX, -sY,  sZ, // 1 // 22==1
            -sX, -sY,  sZ, // 0 // 23==0
    };

    GLfloat normals[] = {
            // FRONT
            0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
            // BACK
            0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,
            // RIGHT
            1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,
            // TOP
            0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,
            // LEFT
            -1.0, 0.0, 0.0,-1.0, 0.0, 0.0,-1.0, 0.0, 0.0,-1.0, 0.0, 0.0,
            // BOTTOM
            0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,
    };

    GLfloat normals2[] = {
            // FRONT
            0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
            // BACK
            0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
            // RIGHT
            0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
            // FRONT
            0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
            // BACK
            0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
            // RIGHT
            0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
    };


    GLfloat colors[] = {
            1.0, 0.5, 0.0,
            1.0, 0.5, 0.0,
            1.0, 0.5, 0.0,
            1.0, 0.5, 0.0,

            1.0, 0.7, 0.0,
            1.0, 0.7, 0.0,
            1.0, 0.7, 0.0,
            1.0, 0.7, 0.0,

            0.2, 0.3, 1.0,
            0.2, 0.3, 1.0,
            0.2, 0.3, 1.0,
            0.2, 0.3, 1.0,

            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,

            0.2, 0.3, 1.0,
            0.2, 0.3, 1.0,
            0.2, 0.3, 1.0,
            0.2, 0.3, 1.0,

            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,



    };
    GLushort  indices[] = {
            0,1,2,0,2,3,
            5,4,7,5,7,6,
            8,9,10,8,10,11,

            12,13,14,12,14,15,
            16,17,18,16,18,19,
            20,21,22,20,22,23



    };


    GLint numIndices = 36;//6;
    GLint numVertices = 24;//4;

    //numIndices = 6;
    //numVertices = 4;
    GLint vtxStride = (3)*sizeof(GLfloat);
    GLuint offset = 0;

    // vboIds[0] – used to store vertex attribute data
    // vboIds[1] – used to store element indices
    glGenBuffers(4, vboIds);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, vtxStride * numVertices, vVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vtxStride, (const void*)offset);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, vtxStride * numVertices, colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vtxStride, (const void*)offset);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, vtxStride * numVertices, normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vtxStride, (const void*)offset);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numIndices, indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

void Cube3D::end() {
    glDeleteBuffers(4, vboIds);
}




/*
// create VBOs
glGenBuffers(1, &vboId);    // for vertex buffer
glGenBuffers(1, &iboId);    // for index buffer

size_t vSize = sizeof vertices;
size_t nSize = sizeof normals;
size_t cSize = sizeof colors;
size_t tSize = sizeof texCoords;

// copy vertex attribs data to VBO
glBindBuffer(GL_ARRAY_BUFFER, vboId);
glBufferData(GL_ARRAY_BUFFER, vSize+nSize+cSize+tSize, 0, GL_STATIC_DRAW); // reserve space
glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, vertices);                  // copy verts at offset 0
glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, normals);               // copy norms after verts
glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize, cSize, colors);          // copy cols after norms
glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize+cSize, tSize, texCoords); // copy texs after cols
glBindBuffer(GL_ARRAY_BUFFER, 0);

// copy index data to VBO
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/