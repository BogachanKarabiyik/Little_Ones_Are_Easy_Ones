#include "Main.h"

GLuint make_sp(std::string v_shader, std::string f_shader)
{
	const char* v_source = v_shader.c_str();
	const char* f_source = f_shader.c_str();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, &v_source, NULL);
	glShaderSource(fragment_shader, 1, &f_source, NULL);

	glCompileShader(vertex_shader);
	glCompileShader(fragment_shader);

	GLuint program = glCreateProgram();

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	return program;
}

GLuint load_texture(const char* path)
{
	GLuint texture_ID;
	texture_ID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture_ID == 0) std::cout << "Could not find texture file: " << path << "\n";

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return texture_ID;
}

class Vertex {
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

std::vector<Vertex> load_model(const char* model_path)
{
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warnings;
	std::string errors;

	tinyobj::LoadObj(&attributes, &shapes, &materials, &errors, model_path, 0);

	std::vector<Vertex> vertices;

	for (int i = 0; i < shapes.size(); i++) {
		tinyobj::shape_t& shape = shapes[i];
		tinyobj::mesh_t& mesh = shape.mesh;
		for (int j = 0; j < mesh.indices.size(); j++) {
			tinyobj::index_t i = mesh.indices[j];
			glm::vec3 position = {
				attributes.vertices[i.vertex_index * 3],
				attributes.vertices[i.vertex_index * 3 + 1],
				attributes.vertices[i.vertex_index * 3 + 2]
			};
			glm::vec3 normal = {
				attributes.vertices[i.normal_index * 3],
				attributes.vertices[i.normal_index * 3 + 1],
				attributes.vertices[i.normal_index * 3 + 2]
			};
			glm::vec2 texCoord = {
				attributes.vertices[i.texcoord_index * 2],
				attributes.vertices[i.texcoord_index * 2 + 1],
			};
			Vertex vert = { position, normal, texCoord };
			vertices.push_back(vert);
		}
	}

	return vertices;
}

void setup_vertices()
{
	float square[18] = {
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	float texture[12] = {
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(3, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW);
}

void init()
{
	setup_vertices();

	writing_sp = make_sp(writing_vs, writing_fs);
	obj_sp = make_sp(obj_vs, obj_fs);

	font_tex = load_texture("Assets/Font.png");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_DEPTH_TEST);
	glDrawBuffer(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void window_reshape_callback_writing(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	p_mat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	float target_width = 1280.0f;
	float target_height = 720.0f;
	float A = target_width / target_height;
	float V = (float)width / (float)height;

	if (V >= A) {
		p_mat = glm::ortho(-V / A * target_width / 2.0f, V / A * target_width / 2.0f, -target_height / 2.0f, target_height / 2.0f);
	}
	else {
		p_mat = glm::ortho(-target_width / 2.0f, target_width / 2.0f, -A / V * target_height / 2.0f, A / V * target_height / 2.0f);
	}
}

void window_reshape_callback_obj(GLFWwindow* window, int width, int height)
{
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	p_mat = glm::perspective(1.0472f, aspect, 0.1f, 5000.0f);
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSwapInterval(1);
	window_reshape_callback_writing(window, 1280, 720);
	glfwSetWindowSizeCallback(window, window_reshape_callback_writing);

	Scene initial_scene;

	init();

	Writing* head = new Writing("why u do dis!?!", 15, 24, glm::vec2(0, 0));
	Writing* head2 = new Writing("NONONO@@@##!!!", 14, 24, glm::vec2(-400, 0));
	Writing* head3 = new Writing("Saldiiiiggrr!! Durma lan! Yardimmmmmm LUTFEEEN", 46, 24, glm::vec2(-600, 100));

	head3->size_color = glm::vec4(48, 1.0, 1.0, 0.0);
	initial_scene.add_writing(head);
	initial_scene.add_writing(head2);
	initial_scene.add_writing(head3);


	glfwGetCursorPos(window, &xposOld, &yposOld);

	while (!glfwWindowShouldClose(window))
	{
		move();
		render(initial_scene);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}