#version 120
attribute vec3 vertex_position;
void main(){
    gl_Position = vec4(vertex_position , 1.);
    gl_PointSize = 50.0f;
  
  
    
}