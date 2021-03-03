# Design

RenderAPI/Context - Functions to interact with underlying API. Swapping buffers, etc.
RenderPass - Encapsulated draw command. Optimize whatever is passed (for batching and minimize state changes) and allows for transparency.
Vao Vbo Ebo Shader Texture

# RenderFlow

Start Frame
Create RenderPass
Set Camera
Add object (vao, shader, transform)
Add lights
End RenderPass
End Frame
Swap buffers
