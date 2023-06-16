#version 450

// @brief Vertex shader takes in vec2 in normalized space
// this normalized space goes from [-1,1] using float values
//

vec2 vertices[3] =
{
    vec2(-0.5, 0.5),
    vec2(0,-0.5),
    vec2(0.5,0.5),
};


void main()
{
    float z_axis = 1.0;
    float perspecitve_divide = 1.0;
    gl_Position = vec4(vertices[gl_VertexIndex], z_axis, perspecitve_divide);
}