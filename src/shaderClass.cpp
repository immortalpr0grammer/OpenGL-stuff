#include <shaderClass.hpp>
#include <stdexcept>


// Reads a text file and returns it as a string. I just copied this over since this is just annoying
std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
    }
    std::string msg = std::string("Failed to open file: ") + filename;
    throw std::runtime_error(msg);
}

// The constructor
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    // Turning the files into strings
    std::string vertexCode = getFileContents(vertexFile);
    std::string fragmentCode = getFileContents(fragmentFile);
    // Turning the strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

     // Creating the shaders, connecting them to the source code and compiling them so the GPU understands it
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Creating the shader program, attaching the shaders to it and then link the program to the final executable
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Deleting the shaders, since we already put them in the program, so we dont need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}
// Method to activate it
void Shader::Activate() {
    glUseProgram(ID);
}
// Method to delete it
void Shader::Delete() {
    glDeleteProgram(ID);
}